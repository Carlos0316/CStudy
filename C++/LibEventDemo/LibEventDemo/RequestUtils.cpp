#include "stdafx.h"
#include "HttpRequest.h"
#include "RequestUtils.h"
#include "EventHttpWorker.h";
#include "ReqWorkerFactory.h"

RequestUtils::RequestUtils()
{
	m_worker = ReqWorkerFactory::createWorker();
}

RequestUtils::~RequestUtils()
{
	delete m_worker;
}

RequestUtils* RequestUtils::getInstance()
{
	static RequestUtils sInstance;
	return &sInstance;
}

void RequestUtils::doRequest(int method, HttpRequest *request)
{
	m_worker->doRequest(request);
}