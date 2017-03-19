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

	
#ifdef WIN32
	typedef __int64                     int64;
#else
	typedef int64_t                     int64;
#endif
	typedef unsigned long long          uint64;
	typedef wchar_t						wchar;
	typedef unsigned char				uchar;
	typedef char						int8;
	typedef unsigned char				uint8;
	typedef short						int16;
	typedef unsigned short				uint16;
	typedef int							int32;
	typedef unsigned int				uint32;
	typedef float						float32;
	typedef double						float64;
	
#define S_SAFE_DELETE(a) if( a ){ delete a;a=NULL; }
#define S_SAFE_RELEASE(a) if( a ){ a->Release(); }
	
#define S_USE_PRINT

#define STRCMP strcmp
#define STRCPY strcpy
#define ATOF atof
#define ATOI atoi
#define ATOL atol

#ifdef WIN32
#define SSleep(ms) Sleep(ms)
#else
#define SSleep(ms) usleep(ms)
#endif

#define RAND rand

#ifdef ASSERT
#undef ASSERT
#endif 
#define ASSERT assert

typedef vector< std::string > StringVector;
typedef vector< std::string >::iterator StringIter;
typedef vector< int32 > IntVector;
typedef vector< int32 >::iterator IntIter;



#define MAX_THREAD 4

#pragma pack(push, 1)

// 包头大小设置为4个字节，表示后面body的长度   
#define PACKAGE_HEADER_SIZE 4

struct NetMsgSS // s to s
{
	NetMsgSS(int32 _protocol) :protocol(_protocol)
	{
		sessid = fepsid = /*uid = */0;
	}

	int32 protocol;	// 协议  
	int64 sessid;	// fep上，玩家socket的SLONGID，也是SocketID的64位类型  
	int32 fepsid;	// 从哪个FepServer发出去的ServerID
	//int64 uid;		// 玩家的UID，当玩家有选择角色成功后，该值才不为0 

};

struct NetMsgC // s to c
{
	NetMsgC(int32 _protocol) :protocol(_protocol)
	{

	}

	int32 protocol;
};

#pragma pack(pop)

#endif
