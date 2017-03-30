#ifndef __HTTP_WORKER_H__
#define __HTTP_WORKER_H__

#include "HttpRequest.h"

class HttpWorker
{
public:

	virtual void doRequest(HttpRequest *request) = 0;
};
#endif
