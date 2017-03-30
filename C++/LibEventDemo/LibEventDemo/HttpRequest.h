#ifndef __HTTP_REQUEST_H__
#define __HTTP_REQUEST_H__

#include "RequestCallback.h"

#define METHOD_GET    101
#define METHOD_POST 102

class HttpRequest
{
public:
	char *url;
	int method;
	char *params;
	RequestCallback *callback;
};
#endif
