#ifndef  __REQUEST_CALLBACK_H__
#define __REQUEST_CALLBACK_H__

class RequestCallback
{
public:

	virtual void onResponse(char *response) = 0;

	virtual void onError(int errorCode) = 0;
};
#endif