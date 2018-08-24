#ifndef _BASE_DEFINE_H_
#define _BASE_DEFINE_H_
#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <stdint.h>
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

typedef int64_t UID;

#ifndef S_SAFE_DELETE
#define S_SAFE_DELETE(x) { if (NULL != x) { delete (x); (x) = NULL; } }
#endif

#ifndef SAFE_DELETE
#define SAFE_DELETE(x) { if (NULL != x) { delete (x); (x) = NULL; } }
#endif

#ifndef S_SAFE_RELEASE
#define S_SAFE_RELEASE(a) if( a ){ a->Release(); }
#endif // !1

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(a) if( a ){ a->Release(); }
#endif // !1

#define S_USE_PRINT
#define STRCMP strcmp
#define STRCPY strcpy
#define SPRINTF sprintf
#define RAND rand
#define ATOF atof
#define ATOI atoi
#define ATOL atol

#ifndef ASSERT
#define ASSERT assert
#endif 

//
//	标志位设置 
//
#define INSERT_FLAG(value, query_flags)	{(value) |= (query_flags);}
#define REMOVE_FLAG(value, query_flags)	{(value) &= ~(query_flags);}
#define HAS_FLAG(value, query_flags)		( ((value) & (query_flags)) != 0 ? true : false )

// 64位操作 
#define MAKE_PAIR64(l, h)  uint64_t( uint32_t(l) | ( uint64_t(h) << 32 ) )
#define PAIR64_HIPART(x)   (uint32_t)((uint64_t(x) >> 32) & 0x00000000FFFFFFFFLL)
#define PAIR64_LOPART(x)   (uint32_t)(uint64_t(x)         & 0x00000000FFFFFFFFLL)
#define MAKE_MAPSCENEID(mapid,sceneid)  MAKE_PAIR64(mapid, sceneid)
#define MAKE_FLATZONEID(flatid,zoneid)	MAKE_PAIR64(flatid, zoneid)
#define MAKE_FZMSID(msid,fzid)			MAKE_PAIR64(msid,fzid)

// 32位操作 
#define MAKE_PAIR32(l, h)  uint32_t( uint16_t(l) | ( uint32_t(h) << 16 ) )
#define PAIR32_HIPART(x)   (uint16_t)((uint32_t(x) >> 16) & 0x0000FFFF)
#define PAIR32_LOPART(x)   (uint16_t)(uint32_t(x)         & 0x0000FFFF)
			//日志前缀 
#define  __PRINT_MSG__ __FUNCTION__ << " " << __FILE__ << ":" << __LINE__ 

#ifdef _MSC_VER
#	define SERVER_DECL __declspec(dllexport)
#	define SCRIPT_DECL __declspec(dllimport)
#	define TWP_DLL_EXPORT extern "C" __declspec(dllexport)
#	define TWP_DLL_DECL __declspec(dllexport)
#else
#	define SERVER_DECL
#	define SCRIPT_DECL
#	define TWP_DLL_EXPORT extern "C"
#endif

#pragma pack(push,1)

/*
* 通用值类型
*/
union ValueType
{
	ValueType()
	{
		memset(this, 0, sizeof(*this));
	}

	template<typename T>
	ValueType(T v)
	{
		if (!(sizeof(*this) < sizeof(T)))
		{
			memcpy(this, &v, sizeof(T));
		}
	}
	template<typename T>
	void operator+=(const T& v)
	{
		ValueType tmpType(v);
		nInt8 += tmpType.nInt8;
		nInt16 += tmpType.nInt16;
		nInt32 += tmpType.nInt32;
		nInt64 += tmpType.nInt64;
		nUint8 += tmpType.nUint8;
		nUint16 += tmpType.nUint16;
		nUint32 += tmpType.nUint32;
		nUint64 += tmpType.nUint64;
	}

	int8_t		nInt8;
	int16_t		nInt16;
	int32_t		nInt32;
	int64_t		nInt64;
	uint8_t		nUint8;
	uint16_t	nUint16;
	uint32_t	nUint32;
	uint64_t	nUint64;
};

typedef std::vector< std::string > StringVector;
typedef std::vector< std::string >::iterator StringIter;

typedef std::vector< int32_t > IntVector;
typedef std::vector< int32_t >::iterator IntIter;

// 数据库表 
enum ETableType
{
	E_TABLE_NULL = 0,
	E_TABLE_USER,
	E_TABLE_QUEST,
};

// 请求登录到ws的通用数据结构 
struct LoginData2Ws
{
	LoginData2Ws()
	{
	}
	char arrServerAddr[32]; // 服务器地址 
	int32_t nServerPort;		// 端口 
	int32_t nServerID;		// 服务器标识ID 
};

// 服务器信息 
struct t_ServerReg
{
	t_ServerReg()
	{
		id = 0;
	}

	int32_t id;
};

typedef std::vector<t_ServerReg> ServerInfoDataVecType;


// 协议号范围管理 
enum
{
	PRO_C2S = 100000,
	PRO_S2S = 200000,
};

// 角色类型 
enum ERoleType
{
	E_ROLE_TYPE_NULL,
	E_ROLE_TYPE_1,
	E_ROLE_TYPE_2,
	E_ROLE_TYPE_3,
	E_ROLE_TYPE_4,
	E_ROLE_TYPE_MAX,
};


// 进入场景条件参数
struct stEnterSceneParam
{
	int32_t nSubIdx; // 动态地图唯一ID 
	int32_t nPram1;
	int32_t nPram2;
	stEnterSceneParam()
	{
		memset(this, 0, sizeof(*this));
	}
};


/* 定时常用定义 */
#define __INTERAVAL_ONE_SECOND__	(nSrvTime % 5 == 0)
#define __INTERAVAL_TWO_SECOND__	(nSrvTime % 10 == 0)
#define __INTERAVAL_THREE_SECOND__  (nSrvTime % 15 == 0)
#define __INTERAVAL_FOUR_SECOND__	(nSrvTime % 20 == 0)
#define __INTERAVAL_FIVE_SECOND__	(nSrvTime % 25 == 0)
#define __INTERAVAL_ONE_MINUTE__	(nSrvTime % 300 == 0)

#define MAX_LOAD_ALL_UID 1000 

	/* 变长结构定义 */
#define BUFFER_MSG(msg,size) char buffmsg[65535]; \
memcpy(buffmsg, (const char*)(msg), (size));

enum EnterType
{
	ENTER_TYPE_ONLINE_FIRST = 0,	/* 首次进入 */
	ENTER_TYPE_SCENE_CHANGE,		/* 更改场景 */
	ENTER_TYPE_OFFLINE_SYNC,		/* 下线转入离线场景 */
	ENTER_TYPE_OFFLINE_LOAD,		/* 离线数据加载 */
};

#pragma pack(pop)


#endif







