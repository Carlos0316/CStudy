#include "stdafx.h"
#include "HttpRequest.h"
#include "RequestUtils.h"
#include "EventHttpWorker.h";
#include "HttpWorker.h"
#include "HttpWorkers.h"

RequestUtils::RequestUtils()
{
}

RequestUtils::~RequestUtils()
{
}

RequestUtils* RequestUtils::getInstance()
{
	static RequestUtils sInstance;
	return &sInstance;
}

void RequestUtils::doRequest(int method, HttpRequest *request)
{
	HttpWorker *worker = HttpWorkers::newEventWorker();
	worker->doRequest(request);
}