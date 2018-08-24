/*
 *
 *	Detail: Mysql数据库配置类
 *   
 * Copyright (c) Created by hzd 2014-4-21.All rights reserved
 *
 */

#ifndef SWA_NETCONFIG_H_
#define SWA_NETCONFIG_H_

#include <stdio.h>

#include <map>
#include <set>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <utility>

#ifdef WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <mswsock.h>
#include <Windows.h>
#else
#include <stdint.h>
#endif

#include <boost/timer.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/container/set.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

using namespace boost::system;
using namespace boost::asio::ip;
using namespace boost::asio;

typedef wchar_t						wchar;
typedef unsigned char				uchar;
typedef float						float32;
typedef double						float64;
	
#ifndef S_SAFE_DELETE
#define S_SAFE_DELETE(x) { if (NULL != x) { delete (x); (x) = NULL; } }
#endif

#ifndef S_SAFE_DELETE_VEC
#define S_SAFE_DELETE_VEC(x) { if (NULL != x) { delete [] (x); (x) = NULL; } }
#endif
	
#define S_USE_PRINT

#define STRCMP strcmp
#define STRCPY strcpy
#define ATOF atof
#define ATOI atoi
#define ATOL atol
#define RAND rand

typedef vector< std::string > StringVector;
typedef vector< std::string >::iterator StringIter;
typedef vector< int32_t > IntVector;
typedef vector< int32_t >::iterator IntIter;

#define MAX_THREAD 4

#pragma pack(push, 1)

// 包头大小设置为4个字节，表示后面body的长度   
#define PACKAGE_HEADER_SIZE		4		
#define PACKAGE_BODY_MAX_SIZE	4092
#define PACKAGE_MAX_SIZE		4096

struct BaseMsg
{
	BaseMsg()
	{
		protocol = 0;
	}
	union // 协议 
	{
		uint32_t protocol;	// 协议 
		struct
		{
			uint16_t cmd;
			uint16_t cmdType;
		};
	};
};

struct NetMsgSS : public BaseMsg
{
	NetMsgSS(uint32_t _protocol)
	{
		protocol = _protocol;
		clientSessID = fepServerID = 0;
	}
	NetMsgSS(uint16_t _cmd,uint16_t _cmdType) 
	{
		cmd = _cmd; cmdType = _cmdType;
		clientSessID = fepServerID = 0;
	}
	uint64_t clientSessID;	// fep上，玩家socket的SLONGID，也是SocketID的64位类型  
	uint32_t fepServerID;	// 从哪个FepServer发出去的ServerID
};

struct NetMsgC : public BaseMsg
{
	NetMsgC(int32_t _protocol)
	{
		protocol = _protocol;
	}
	NetMsgC(uint16_t _cmd, uint16_t _cmdType) 
	{
		cmd = _cmd; cmdType = _cmdType;
	}
};

struct PbMsgWeb : public BaseMsg
{
	PbMsgWeb()
	{
	}
	PbMsgWeb(int32_t _protocol)
	{
		protocol = _protocol;
	}
	PbMsgWeb(uint16_t _cmd, uint16_t _cmdType)
	{
		cmd = _cmd; cmdType = _cmdType;
	}
	char data[0];
};

struct PbMsgWebSS : public BaseMsg
{
	PbMsgWebSS()
	{
		clientSessID = fepServerID = 0;
	}
	PbMsgWebSS(int32_t _protocol)
	{
		protocol = _protocol;
		clientSessID = fepServerID = size = 0;
	}
	PbMsgWebSS(uint16_t _cmd, uint16_t _cmdType)
	{
		cmd = _cmd; cmdType = _cmdType;
		clientSessID = fepServerID = size = 0;
	}
	uint64_t clientSessID;	// fep上，玩家socket的SLONGID，也是SocketID的64位类型  
	uint32_t fepServerID;	// 从哪个FepServer发出去的ServerID
	int32_t size;
	char data[0];
};

enum {
	MAX_RCV_LEN = 96 * 1024, // 1M, experimental val.
							 //MAX_SEND_SIZE = 1024 * 300 // 300K, we have verification code
	MAX_SEND_SIZE = 96 * 1024 // boost bug, no more than 64K
};

struct DataBuffer
{
	uint8_t* data_all;
	uint32_t data_len;
	DataBuffer* next;
	DataBuffer(const uint8_t* _data, int32_t _len) :data_all(NULL), data_len(0), next(NULL)
	{
		data_len = PACKAGE_HEADER_SIZE + _len;
		data_all = new uint8_t[data_len];
		memcpy(data_all, &_len, PACKAGE_HEADER_SIZE);
		memcpy(data_all + PACKAGE_HEADER_SIZE, _data, _len);
	}

	~DataBuffer()
	{
		delete [] data_all;
		next = NULL;
	}
};

#pragma pack(pop)

#endif
