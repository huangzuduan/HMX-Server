#ifndef MyRequestHandlerFactory_INCLUDED_1
#define MyRequestHandlerFactory_INCLUDED_1

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"

using namespace Poco::Net;
using namespace Poco::Util;

class MyHttpServer;
//-----------------------------------------
class MyRequestHandlerFactory : public HTTPRequestHandlerFactory
{
public:
	MyRequestHandlerFactory(MyHttpServer* httpServer);
	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest &req);
private:
	MyHttpServer* _httpServer;
};

#endif // HTTPServerTest_INCLUDED
