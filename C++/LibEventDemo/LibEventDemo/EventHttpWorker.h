#ifndef __EVENT_HTTP_WORKER_H__
#define __EVENT_HTTP_WORKER_H__

 #include "HttpWorker.h"

#include "event2/event-config.h"
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/http.h>
#include <event2/http_struct.h>
#include <event2/keyvalq_struct.h>
#include <event2/thread.h>

#include "Thread.h"

class EventHttpWorker : public HttpWorker, public Thread
{
public:
	EventHttpWorker();
	~EventHttpWorker();

	void doRequest(HttpRequest *request);

	virtual void run();
private:
	struct event_base *m_evbase;

	HttpRequest *m_request;

	void doGet(HttpRequest *request);

	void doPost(HttpRequest *request);

	static void httpRequestCallback(struct evhttp_request *req, void *arg);
};
#endif