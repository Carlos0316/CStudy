#include "stdafx.h"
#include "ReqWorkerFactory.h"
#include "EventHttpWorker.h"

HttpWorker* ReqWorkerFactory::createWorker()
{
	return new EventHttpWorker();
}