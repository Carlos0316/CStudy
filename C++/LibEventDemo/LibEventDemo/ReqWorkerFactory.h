#ifndef __REQ_WORKER_FACTORY_H__
#define __REQ_WORKER_FACTORY_H__

#include "HttpWorker.h"

class ReqWorkerFactory
{
public:
	static HttpWorker* createWorker();
private:

	ReqWorkerFactory();
};
#endif
