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

#include "MyHttpServer.h"
#include "StringUtils.h"
#include "GameService.h"
#include "SceneRoomMgr.h"
#include "MyRequestHandlerFactory.h"
#include "AdminRequestHandler.h"

unsigned char ToHex(unsigned char x)
{
	return  x > 9 ? x + 55 : x + 48;
}

unsigned char FromHex(unsigned char x)
{
	unsigned char y;
	if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
	else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
	else if (x >= '0' && x <= '9') y = x - '0';
	else assert(0);
	return y;
}

std::string UrlEncode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (isalnum((unsigned char)str[i]) ||
			(str[i] == '-') ||
			(str[i] == '_') ||
			(str[i] == '.') ||
			(str[i] == '~'))
			strTemp += str[i];
		else if (str[i] == ' ')
			strTemp += "+";
		else
		{
			strTemp += '%';
			strTemp += ToHex((unsigned char)str[i] >> 4);
			strTemp += ToHex((unsigned char)str[i] % 16);
		}
	}
	return strTemp;
}

std::string UrlDecode(const std::string& str)
{
	std::string strTemp = "";
	size_t length = str.length();
	for (size_t i = 0; i < length; i++)
	{
		if (str[i] == '+') strTemp += ' ';
		else if (str[i] == '%')
		{
			assert(i + 2 < length);
			unsigned char high = FromHex((unsigned char)str[++i]);
			unsigned char low = FromHex((unsigned char)str[++i]);
			strTemp += high * 16 + low;
		}
		else strTemp += str[i];
	}
	return strTemp;
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
	uint64_t timeInt = GetKeyValueInt64("time", params);
	uint64_t userIdInt = GetKeyValueInt64("userid", params);

	if (sign == "" || timeInt == 0)
	{
		return 2;
	}

	int ret = GameService::getMe().CheckMd5(userIdInt, timeInt, sign.c_str());
	if ( ret != 0 )
	{
		return 2;
	}

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

uint32_t MyHttpServer::GetKeyValueInt32(const std::string& keyName, const std::map<std::string, std::string>& params)
{
	std::string valueStr = GetKeyValueStr(keyName, params);
	uint32_t valueInt = 0;
	StringUtils::toUInt32(valueStr, valueInt);
	return valueInt;
}

uint64_t MyHttpServer::GetKeyValueInt64(const std::string& keyName, const std::map<std::string, std::string>& params)
{
	std::string valueStr = GetKeyValueStr(keyName,params);
	uint64_t valueInt = 0;
	StringUtils::toUInt64(valueStr, valueInt);
	return valueInt;
}

void MyHttpServer::getRequestArgs(const HTTPServerRequest &req, std::map<std::string, std::string>& params, bool needDecode)
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
			if (needDecode)
			{
				value = UrlDecode(value);
			}
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
	cout << "HttpServer started,port=" << _serverPort << endl;

	waitForTerminationRequest();  // wait for CTRL-C or kill

	cout << endl << "HttpServer Shutting down..." << endl;
	s.stop();

	return Application::EXIT_OK;
}