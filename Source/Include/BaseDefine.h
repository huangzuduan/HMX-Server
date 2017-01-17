#ifndef _BASE_DEFINE_H_
#define _BASE_DEFINE_H_
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <assert.h>
#include <map>
#include <set>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <sstream>
#include <memory>
#include <utility>
#include <functional>

#ifdef WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#include <mswsock.h>
#include <Windows.h>
#else
#include <stdint.h>
#endif
	
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


	typedef int64	UID;

#include <boost/timer.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/container/set.hpp>
#include <boost/thread/thread.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/std/utility.hpp>

	
#define S_SAFE_DELETE(a) if( a ){ delete a;a=NULL; }
#define S_SAFE_RELEASE(a) if( a ){ a->Release(); }
	
#define S_USE_PRINT
#define STRCMP strcmp
#define STRCPY strcpy
#define SPRINTF sprintf
#define RAND rand
#define ATOF atof
#define ATOI atoi
#define ATOL atol

#ifdef ASSERT
#undef ASSERT
#endif 
#define ASSERT assert

#ifdef WIN32
#define SSleep(ms) Sleep(ms)
#else
#define SSleep(ms) usleep(ms)
#endif

#define INSERT_FLAG(value, query_flags)	{(value) |= (query_flags);}
#define REMOVE_FLAG(value, query_flags)	{(value) &= ~(query_flags);}
#define HAS_FLAG(value, query_flags)	( ((value) & (query_flags)) != 0 ? true : false )

#endif







