//
// HTTPServerTest.cpp
//
// $Id: //poco/1.4/Net/testsuite/src/HTTPServerTest.cpp#1 $
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//

#include "MyHTTPServer.h"
#include "StringUtils.h"
#include "GameService.h"
#include "UserEditRequestHandler.h"


MyRequestHandlerFactory::MyRequestHandlerFactory(MyHttpServer* httpServer):_httpServer(httpServer)
{

}

HTTPRequestHandler* MyRequestHandlerFactory::createRequestHandler(const HTTPServerRequest &req)
{
	const std::string& uri = req.getURI();
	H::logger->info("收到HTTP请求:%s", uri.c_str());
	if (uri.find("/SendRoomCard") == 0 )
	{
		//return new SendRoomCardRequestHandler(_httpServer);
	}
	else if (uri.find("/UserEdit") == 0)
	{
		return new UserEditRequestHandler(_httpServer);
	}
	return NULL;
}

MyHttpServer::MyHttpServer(const std::string& servername, uint16_t port)
	:_serverName(servername)
	,_serverPort(port)
	,m_usNo(10000)
{

}

void MyHttpServer::start()
{
	std::vector<std::string> args;
	args.push_back(_serverName);
	boost::thread t(boost::bind(&MyHttpServer::run, this, args));
	boost::this_thread::yield();
	t.swap(serviceThread);	
}

void MyHttpServer::doRequest()
{

}

int MyHttpServer::checkAuth(const std::map<std::string, std::string>& params)
{
	if (params.empty())
	{
		return 1;
	}

	std::string sign = GetKeyValueStr("sign",params);
	uint64_t timeInt = GetKeyValueInt("time", params);
	uint64_t userIdInt = GetKeyValueInt("userid", params);

	if (sign == "" || timeInt == 0)
	{
		return 2;
	}

	// 不同的业务做不同的校验处理

	return 0;
}

std::string MyHttpServer::GetKeyValueStr(const std::string& keyName, const std::map<std::string, std::string>& params)
{
	for (std::map<std::string, std::string>::const_iterator it = params.begin(); it != params.end(); ++it)
	{
		std::string key = it->first;
		std::string value = it->second;
		if (key == keyName)
		{
			return value;
		}
	}
	return "";
}

uint64_t MyHttpServer::GetKeyValueInt(const std::string& keyName, const std::map<std::string, std::string>& params)
{
	std::string valueStr = GetKeyValueStr(keyName,params);
	uint64_t valueInt = 0;
	StringUtils::toUInt64(valueStr, valueInt);
	return valueInt;
}

void MyHttpServer::getRequestArgs(const HTTPServerRequest &req, std::map<std::string, std::string>& params)
{
	std::string uri = req.getURI();
	int spiOff = uri.find_first_of('?');
	if (spiOff < 0)
		return ;

	std::string argStr = uri.substr(spiOff + 1);
	std::vector<std::string> vecArgs;
	stringtok(vecArgs, argStr, "&");
	for (std::vector<std::string>::iterator it = vecArgs.begin(); it != vecArgs.end(); ++it)
	{
		std::string& keyValues = *it;
		std:vector<std::string> pairKV;
		stringtok(pairKV, keyValues, "=");
		if (pairKV.size() == 2)
		{
			std::string key = pairKV[0];
			std::string value = pairKV[1];
			params.insert(std::make_pair(key,value));
		}
	}
}

HTTPRequestHandler* MyHttpServer::getRequestHandler(uint64_t handlerNo)
{
	std::map<uint64_t, HTTPRequestHandler*>::iterator it = m_mapRequsetHandler.find(handlerNo);
	if ( it != m_mapRequsetHandler.end())
	{
		return it->second;
	}
	return NULL;
}

void MyHttpServer::putRequestHandler(uint64_t handlerNo, HTTPRequestHandler* req)
{
	m_mapRequsetHandler.insert(std::make_pair(handlerNo, req));
}

void MyHttpServer::removeRequestHandler(uint64_t handlerNo)
{
	std::map<uint64_t, HTTPRequestHandler*>::iterator it = m_mapRequsetHandler.find(handlerNo);
	if (it != m_mapRequsetHandler.end())
	{
		delete it->second;
		m_mapRequsetHandler.erase(it);
	}
}


int MyHttpServer::main(const vector<string>& args)
{
	HTTPServer s(new MyRequestHandlerFactory(this), ServerSocket(_serverPort), new HTTPServerParams);

	s.start();
	cout << endl << "Server started" << endl;

	waitForTerminationRequest();  // wait for CTRL-C or kill

	cout << endl << "Shutting down..." << endl;
	s.stop();

	return Application::EXIT_OK;
}