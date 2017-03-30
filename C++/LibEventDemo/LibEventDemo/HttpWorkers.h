#ifndef __HTTP_WORKERS_H__
#define __HTTP_WORKERS_H__

#include "HttpWorker.h"

class HttpWorkers
{
public:
	static HttpWorker* newEventWorker();
private:

	HttpWorkers();
};
#endif
