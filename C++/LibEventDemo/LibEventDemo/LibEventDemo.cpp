// LibEventDemo.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include "RequestCallback.h"
#include "HttpRequest.h"
#include "RequestUtils.h"
#include <iostream>

using namespace std;

char *POST_URL = "http://sdk.matchvs.com/v1/gateway/query";
char *POST_PARAMS = "gameid=1000&channel=migu-debug";
char *GET_URL = "http://testopen.matchvs.com/wc3/getBattleFields.do?gameID=100011&versionID=1";

class MyReqCallback : public RequestCallback
{
	void MyReqCallback::onResponse(char *response)
	{
		cout << "request callback : " << endl;
		cout << response << endl;
	}

	void MyReqCallback::onError(int errorCode)
	{
		cout << "request error : " << errorCode << endl;
	}
};

int main(int argc, char *argv[])
{
	HttpRequest *request = new HttpRequest();
	request->url = POST_URL;
	request->params = POST_PARAMS;
	request->method = METHOD_POST;
	request->callback = new MyReqCallback();

	RequestUtils::getInstance()->doRequest(METHOD_POST, request);

	//HttpRequest *request = new HttpRequest();
	//request->url = GET_URL;
	//request->method = METHOD_GET;
	//request->callback = new MyReqCallback();

	//RequestUtils::getInstance()->doRequest(METHOD_GET, request);

	delete request;
	request = NULL;

	while (true)
	{

	}
	return 0;
}