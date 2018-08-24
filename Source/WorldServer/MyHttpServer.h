//
// HTTPServerTest.h
//
// $Id: //poco/1.4/Net/testsuite/src/HTTPServerTest.h#1 $
//
// Definition of the HTTPServerTest class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef HTTPServerTest_INCLUDED_1
#define HTTPServerTest_INCLUDED_1

//#include "Single.h"

#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Util/ServerApplication.h"
#include <iostream>
#include <string>
#include <vector>

#include "SrvEngine.h"

using namespace Poco::Net;
using namespace Poco::Util;

class MyHttpServer : public ServerApplication
{
public:
	MyHttpServer(const std::string& servername, uint16_t port);
	void start();
	void doRequest();

	int checkAuth(const std::map<std::string, std::string>& params);
	std::string GetKeyValueStr(const std::string& keyName, const std::map<std::string, std::string>& params);
	uint32_t GetKeyValueInt32(const std::string& keyName, const std::map<std::string, std::string>& params);
	uint64_t GetKeyValueInt64(const std::string& keyName, const std::map<std::string, std::string>& params);
	void getRequestArgs(const HTTPServerRequest &req, std::map<std::string,std::string>& params,bool needDecode = false);

	HTTPRequestHandler* getRequestHandler(uint64_t handlerNo);
	void putRequestHandler(uint64_t handlerNo, HTTPRequestHandler* req);
	void removeRequestHandler(uint64_t handlerNo);

	uint64_t getNewNo() { return m_usNo++; }

protected:

	int main(const vector<string>& args);

private:
	std::string _serverName;
	uint16_t _serverPort;
	boost::thread serviceThread;

	uint64_t m_usNo;
	std::map<uint64_t, HTTPRequestHandler*> m_mapRequsetHandler;
};

#endif // HTTPServerTest_INCLUDED
