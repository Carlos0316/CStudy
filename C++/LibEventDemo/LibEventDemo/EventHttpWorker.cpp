#include "stdafx.h"
#include "EventHttpWorker.h"

EventHttpWorker::EventHttpWorker()
{
#if defined(WIN32)  || defined(__WIN32__) || defined(_WIN32) || defined(_WIN64) || defined(__WINDOWS__)
	WSADATA wsa_data;
	WSAStartup(0x0201, &wsa_data);
	evthread_use_windows_threads();
#else
	evthread_use_pthreads();
#endif

	m_evbase = event_base_new();
}

EventHttpWorker::~EventHttpWorker()
{
	event_base_free(m_evbase);

#ifdef WIN32
	WSACleanup();
#endif

	delete m_evbase;
	delete m_request;
}

void EventHttpWorker::doRequest(HttpRequest *request)
{
	m_request = new HttpRequest();
	m_request->url = request->url;
	m_request->params = request->params;
	m_request->method = request->method;
	m_request->callback = request->callback;

	start();
}

void EventHttpWorker::run()
{
	switch (m_request->method)
	{
	case METHOD_GET:
		doGet(m_request);
		break;
	case METHOD_POST:
		doPost(m_request);
		break;
	}
}

void EventHttpWorker::doGet(HttpRequest *request)
{
	struct evhttp_uri *uri = evhttp_uri_parse(request->url);
	char *host = (char *)evhttp_uri_get_host(uri);
	int port = evhttp_uri_get_port(uri);
	struct evhttp_connection *conn = evhttp_connection_base_new(m_evbase, NULL, host, (port == -1 ? 80 : port));
	struct evhttp_request *req = evhttp_request_new(httpRequestCallback, request);

	evhttp_add_header(req->output_headers, "Host", host);

	const char *query = evhttp_uri_get_query(uri);
	const char *path = evhttp_uri_get_path(uri);
	size_t len = (query ? strlen(query) : 0) + (path ? strlen(path) : 0) + 1;
	char *path_query = NULL;
	if (len > 1) {
		path_query = (char *)calloc(len, sizeof(char));
		sprintf(path_query, "%s?%s", path, query);
	}

	evhttp_make_request(conn, req, EVHTTP_REQ_GET, path_query ? path_query : "/");

	event_base_dispatch(m_evbase);

	evhttp_uri_free(uri);
	evhttp_connection_free(conn);
	evhttp_request_free(req);
}

void EventHttpWorker::doPost(HttpRequest *request)
{
	struct evhttp_uri *uri = evhttp_uri_parse(request->url);
	char *host = (char *)evhttp_uri_get_host(uri);
	int port = evhttp_uri_get_port(uri);
	struct evhttp_connection *conn = evhttp_connection_base_new(m_evbase, NULL, host, (port == -1 ? 80 : port));
	struct evhttp_request *req = evhttp_request_new(httpRequestCallback, request);

	evhttp_add_header(req->output_headers, "Host", host);
	evhttp_add_header(req->output_headers, "Content-Type", "application/x-www-form-urlencoded");

	const char *data = request->params;
	evbuffer_add(req->output_buffer, data, strlen(data));

	const char *path = evhttp_uri_get_path(uri);
	evhttp_make_request(conn, req, EVHTTP_REQ_POST, path ? path : "/");

	event_base_dispatch(m_evbase);

	evhttp_uri_free(uri);
	evhttp_connection_free(conn);
	evhttp_request_free(req);
}

void EventHttpWorker::httpRequestCallback(struct evhttp_request *req, void *arg)
{
	HttpRequest *request = (HttpRequest *)arg;
	switch (req->response_code)
	{
	case HTTP_OK:
	{
		struct evbuffer* buf = evhttp_request_get_input_buffer(req);
		size_t len = evbuffer_get_length(buf);

		char *json = (char *)malloc(len + 1);
		memcpy(json, evbuffer_pullup(buf, -1), len);
		json[len] = '\0';
		if (request->callback)
		{
			request->callback->onResponse(json);
		}

		free(json);
		break;
	}
	default:
	{
		if (request->callback)
		{
			request->callback->onError(req->response_code);
		}
		break;
	}
	}
}