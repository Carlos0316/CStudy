#ifndef __REQEUST_UTILS_H__
#define __REQEUST_UTILS_H__

#include "HttpWorker.h"
#include "HttpRequest.h"

class RequestUtils
{
public:
	static RequestUtils* getInstance();
	void doRequest(int method, HttpRequest *request);
private:
	HttpWorker *m_worker;

	RequestUtils();
	~RequestUtils();
};
#endif