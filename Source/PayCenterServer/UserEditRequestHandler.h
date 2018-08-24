#pragma once

#include "Poco/Net/HTTPRequestHandler.h"

class MyHttpServer;

using namespace Poco::Net;

class UserEditRequestHandler : public HTTPRequestHandler
{
public:
	UserEditRequestHandler(MyHttpServer* httpServer);
	virtual void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp);
private:
	MyHttpServer* _httpServer;
};
