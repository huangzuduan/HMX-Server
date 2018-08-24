
#ifndef _INC_CSCOMMON_H_
#define _INC_CSCOMMON_H_

/**
 * \brief 定义空的指令
 *
 * 负责服务器内部交换使用，和客户端交互的指令需要另外定义
 * 
 */


/**
 * \brief 定义基本类型
 *
 * 
 */
//#define _MSGPARSE_

#define _X86
#define BGDWIN32
#define XMD_H
#ifdef WIN32
#define __LCC__
#endif

#include <string>
#include <assert.h>
#include <memory.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdint.h>

#include <map>
#include <set>
#include <list>
#include <queue>
#include <vector>
#include <string>
#include <utility>
#include <fstream>
#include <limits>  
#include <math.h>
#include <stdarg.h>
#include <stack>
#include <iostream>

#include <libxml/parser.h>
#include <iconv.h>
#include <libxml/xmlstring.h>
#include <time.h>

#include "UnorderedSet.h"
#include "UnorderedMap.h"

#define __CAT(x)    #x

#ifndef S_SAFE_DELETE
#define S_SAFE_DELETE(x) { if (NULL != x) { delete (x); (x) = NULL; } }
#endif

#ifndef S_SAFE_DELETE_VEC
#define S_SAFE_DELETE_VEC(x) { if (NULL != x) { delete [] (x); (x) = NULL; } }
#endif

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
#include <boost/unordered_map.hpp> 
#include <boost/thread/thread.hpp>
#include <boost/pool/object_pool.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>

using namespace std;
using namespace boost::system;
using namespace boost::asio::ip;
using namespace boost::asio;

typedef float						float32;
typedef double						float64;

typedef signed short SWORD;
typedef long int SDWORD;

typedef unsigned long       DWORD;
typedef int                 BOOL;
typedef unsigned char       BYTE;
typedef unsigned short      WORD;

#ifdef _MSC_VER
typedef unsigned __int64 QWORD;
typedef signed __int64 SQWORD;
#else //_MSC_VER
typedef unsigned long long QWORD;
typedef signed long long SQWORD;
#endif //_MSC_VER

#define S_USE_PRINT

#define STRCMP strcmp
#define STRCPY strcpy
#define ATOF atof
#define ATOI atoi
#define ATOL atol

#ifdef WIN32
#define STRNICMP(a,b,len) strnicmp(a,b,len)
#else 
#define STRNICMP(a,b,len) strncasecmp(a,b,len)
#endif

#define RAND rand

#define SERVER_TIMEOUT				300  // 5分钟内未收到连接的任何数据，则会断开连接
#define IO_UPDTATE_TIME				50   // IO事件，业务定时回调ms 
#define TIMETICK_UPDATE_TIME		1000 // 滴嗒器的更新时间
#define MAIN_LOOP_TIME				100  // 主线程调协时间(空闲线程)

/**
 * \brief 名字的最大长度
 */
#define MAX_NAMESIZE 32

 /**
 * \brief 最大角色数量
 */
#define MAX_ROLENUM 4

/**
 * \brief 账号最大长度
 */
#define MAX_ACCNAMESIZE  48

/**
 * \brief IP地址最大长度
 *
 */
#define MAX_IP_LENGTH  16

/**
 * \brief 网关最大容纳用户数目
 *
 */
#define MAX_GATEWAYUSER 4000  

/**
 * \brief 密码最大长度
 *
 */
#define MAX_PASSWORD  16

/**
 * \brief 屏宽
 */
#define SCREEN_WIDTH 13

/**
 * \brief 屏高
 */
#define SCREEN_HEIGHT 19

/**
* \brief sky 最大孔数量
*/
#define SOCKET_MAXNUM	6

//[Shx Add] 商店广告
#define MAX_SHOPADV		32

//sky 战场国家的特殊判断ID
#define BATTLEFIELD_SCENE_ID	100

#define MAX_MAP_PATH 250 

#define MAX_SQL_FIELD 100

#define MAX_BUFFERSIZE 10000

/* 常用常量定义 */
#define MAX_ACCOUNT_LENG  32		/* 平台账号最大长度 */
#define MAX_PASSWORD_LENG  32		/* 平台密码最大长度 */
#define MAX_NAME_LEN	32			/* 昵称最大长度 */
#define MAX_ROLE_TYPE_COUNT  4		/* 一个平台帐号最多允许创建角色数量 */
#define MAX_CHAT_MSG_LENGTH  128	/* 聊天内容最大长度 */
#define MAX_ENCRYPTSIZE  32			/* 密钥长度 */
#define MAX_SERVERINFO_LIST  32		/* 最大服务器数量(除ws外) */
#define MAX_CHAR_WORLD_MSG_LENGTH  64	/* 聊天最多可以说64个字符 */
#define MAX_SKILL_COUNT  5			/* 技能最大数量 */
#define MAX_QUEST_LIST_COUNT  10	/* 最大接受任务数量 */
#define MAX_BINARY_SIZE 4096		/* 每个数据表最大的二进制大小(不可修改) */
#define MAX_BORADCAST_MSG 4096		/* 广播消息最大数据 */
#define MAX_SOCKET_BUFFER 4096		/* 创建消息容器 */

/**
 * \brief 连接线程池的状态标记位
 *
 */
enum{
  state_none    =  0,          /**< 空的状态 */
  state_maintain  =  1            /**< 维护中，暂时不允许建立新的连接 */
};

#define MAX_CHATINFO  256

/**
 * \brief 数字密码
 */
#define MAX_NUMPASSWORD  32

//sky 队伍最大人数
#define MAX_TEAM_NUM	10

//Shx 套装最大组成部分数
#define MAX_SUIT_NUM	10

//sky 队员离线或者跨场景状态
#define MEMBER_BEING_OFF 0xffffffff

//sky ROLL选择的等待时间(秒级)
#define ROLL_MAX_TIME	60

/**
 * \brief 性别
 */
enum
{
  MALE  = 0,
  FEMALE  = 1
};

/**
 * \brief 五行属性
 */
enum
{
  FIVE_METAL = 0,    /// 金
  FIVE_WOOD = 1,    /// 木
  FIVE_SOIL = 2,    /// 土
  FIVE_WATER = 3,    /// 水
  FIVE_FIRE = 4,    /// 火
  FIVE_NONE = 5      /// 无
};

//sky 前期保持兼容(后期去掉)
enum
{
	PROFESSION_NONE = 0,
	PROFESSION_1	= 1,    //侠客
	PROFESSION_2	= 2,    //侠女
	PROFESSION_3	= 3,    //箭侠
	PROFESSION_4	= 4,    //箭灵
	PROFESSION_5	= 5,    //天师
	PROFESSION_6	= 6,    //美女
	PROFESSION_7	= 7,    //法师
	PROFESSION_8	= 8,    //仙女
};

// sky 新的职业枚举
enum
{
  JOB_NULL		= 0,		//无业
  JOB_FIGHTER	= 1,		//战士
  JOB_THIEVES	= 2,		//盗贼
  JOB_MASTER	= 3,		//法师
  JOB_PASTOR	= 4,		//牧师
};
// sky end

#define ZEBRA_CLIENT_VERSION    20060807

#define ROBOT_START_ID	100000
#define ROBOT_END_ID	100099

inline void mymemcpy(void* pDst, DWORD dwDstSize, void* pScr, DWORD dwCpSize )
{
	if(dwCpSize>dwDstSize)
	{
		assert(0);
		printf("内存操作将越界\n");
		return;
	}
	memcpy(pDst,pScr,dwCpSize);
}

#define memcpyC(d,s,size,dsize) mymemcpy((void*)(d),dsize,(void*)(s),size)

#ifndef HAVE_BZERO
#define bzero(p,s)      memset(p,0,s)
#define bcopy(s,d,ss,ds) memcpyC(d,s,ss,ds)
#endif //HAVE_BZERO


/**
 * \brief 定义家族的基本结构
 *
 */
#pragma pack(1)

namespace SeptDef
{

//#define DWORD CREATE_SEPT_NEED_ITEM_ID    = 0  // 建立家族所需要的道具ID 为0表示不需要
const DWORD CREATE_SEPT_NEED_PRICE_GOLD = 10;  // 建立家族需要金钱20两
const DWORD CREATE_SEPT_NEED_LEVEL     = 1;  // 建立家族需要的人物等级
const DWORD JOIN_SEPT_NEED_LEVEL    = 1;  // 加入家族需要的人物等级
const DWORD PER_LEVEL_MAN_NUM    = 100;    // 每级别增加人数
const DWORD DESTROYTIME          = 60;// 30*24*60*60; //投票有效期 一个月的秒数
const DWORD  CREATE_SEPT_NEED_MAN_NUM = 15;    // 建立家族
    
struct stSeptInfo                      // 数据库读取结构，请不要随意修改，修改注意更新所有代码
{
  DWORD    dwSeptID;                    // 家族的ID
  char    name[MAX_NAMESIZE+1];       // 家族名称
  DWORD    dwCharID;                   // 会长的角色ID
  char    masterName[MAX_NAMESIZE+1];    // 会长的名字
  BYTE    byVote;          // 投票标志为1表示处于投票期间
  DWORD    dwCrTime;        // 家族创立时间
  DWORD     dwRepute;        // 声望
  DWORD     dwCountryID;        // 家族所属国家（以族长国籍为根据）
  DWORD     dwUnionID;        // 家族所属帮会
  DWORD     dwLevel;        // 家族等级
  DWORD     dwSpendGold;        // 家族消费金币
  DWORD     dwIsExp;        // 是否领取家族经验
  char    note[254+1];        // 家族介绍
  DWORD    calltimes;        // 令牌使用次数
  DWORD    calldaytime;        // 令牌使用天数
  DWORD    normalexptime;        // 令牌使用天数
  char		ExterData[512];			// Shx Add 权限和职位
};

struct stSeptMemberInfo                      // 数据库读取结构，请不要随意修改，修改注意更新所有代码
{
  DWORD  dwCharID;        // 会员角色ID
  char  name[MAX_NAMESIZE+1];      // 会员角色名称    
  char    aliasname[MAX_NAMESIZE+1];    // 别名
  WORD    wdOccupation;        // 会员的职业
  WORD	nRight;				//职位序号.
};

}

// 客户端当前状态 
enum ClientStatus
{
	CS_INVALID = 0,
	CS_LOGIN_ING,			//	登录中 
	CS_LOGIN_OK,			//	登录完成 
	CS_REGISTER_ING,		//  注册中 
	CS_REGISTER_OK,			//	注册成功 
	CS_LOADDATA_ING,		//	初始化数据中 
	CS_LOADDATA_OK,			//	初始化数据完成 
	CS_IN_GAME,			//	进入游戏(选择或注册角色后) 
	CS_RES_OK,			//	前端资源加载完成 
};


// 服务器类型定义 
enum EServerType
{
	ESERVER_TYPE_NULL = 0,
	ESERVER_TYPE_CLIENT = 0,
	ESERVER_TYPE_FEP = 1,
	ESERVER_TYPE_LS = 2,
	ESERVER_TYPE_WS = 3,
	ESERVER_TYPE_SS = 4,
	ESERVER_TYPE_DP = 5,
	ESERVER_TYPE_LOG = 6,
	ESERVER_TYPE_MAX,
};

// session 类型 
enum ESessionType
{
	ESESSION_TYPE_NULL = 0,
	ESESSION_TYPE_CLINET,
	ESESSION_TYPE_SERVER,
};

/// 移动方向的定义
enum {
	_DIR_UP = 0,/// 向上
	_DIR_UPRIGHT = 1,/// 右上
	_DIR_RIGHTUP = 1,/// 右上
	_DIR_RIGHT = 2,/// 向右
	_DIR_RIGHTDOWN = 3,/// 右下
	_DIR_DOWNRIGHT = 3,/// 右下
	_DIR_DOWN = 4,/// 向下
	_DIR_DOWNLEFT = 5,/// 左下
	_DIR_LEFTDOWN = 5,/// 左下
	_DIR_LEFT = 6,/// 向左
	_DIR_LEFTUP = 7,/// 左上
	_DIR_UPLEFT = 7,/// 左上
	_DIR_WRONG = 8    /// 错误方向
};

enum
{
	NPC_TYPE_HUMAN = 0,///人型
	NPC_TYPE_NORMAL = 1,/// 普通类型
	NPC_TYPE_BBOSS = 2,/// 大Boss类型
	NPC_TYPE_LBOSS = 3,/// 小Boss类型
	NPC_TYPE_BACKBONE = 4,/// 精英类型
	NPC_TYPE_GOLD = 5,/// 黄金类型
	NPC_TYPE_TRADE = 6,/// 买卖类型
	NPC_TYPE_TASK = 7,/// 任务类型
	NPC_TYPE_GUARD = 8,/// 士兵类型
	NPC_TYPE_PET = 9,/// 宠物类型
	NPC_TYPE_BACKBONEBUG = 10,/// 精怪类型
	NPC_TYPE_SUMMONS = 11,/// 召唤类型
	NPC_TYPE_TOTEM = 12,/// 图腾类型
	NPC_TYPE_AGGRANDIZEMENT = 13,/// 强化类型
	NPC_TYPE_ABERRANCE = 14,/// 变异类型
	NPC_TYPE_STORAGE = 15,/// 仓库类型
	NPC_TYPE_ROADSIGN = 16,/// 路标类型
	NPC_TYPE_TREASURE = 17,/// 宝箱类型
	NPC_TYPE_WILDHORSE = 18,/// 野马类型
	NPC_TYPE_MOBILETRADE = 19,/// 流浪小贩
	NPC_TYPE_LIVENPC = 20,/// 生活npc（不战斗，攻城时消失）
	NPC_TYPE_DUCKHIT = 21,/// 蹲下才能打的npc
	NPC_TYPE_BANNER = 22,/// 旗帜类型
	NPC_TYPE_TRAP = 23,/// 陷阱类型
	NPC_TYPE_MAILBOX = 24,///邮箱
	NPC_TYPE_AUCTION = 25,///拍卖管理员
	NPC_TYPE_UNIONGUARD = 26,///帮会守卫
	NPC_TYPE_SOLDIER = 27,///士兵，只攻击外国人
	NPC_TYPE_UNIONATTACKER = 28,///攻方士兵
	NPC_TYPE_SURFACE = 29,/// 地表类型
	NPC_TYPE_CARTOONPET = 30,/// 替身宝宝
	NPC_TYPE_PBOSS = 31,/// 紫色BOSS
	NPC_TYPE_RESOURCE = 32, /// 资源类NPC

							//sky添加
							NPC_TYPE_GHOST = 999,  /// 元神类NPC
							NPC_TYPE_ANIMON = 33,   /// 动物类怪物
							NPC_TYPE_GOTO = 34,	///传送点
							NPC_TYPE_RESUR = 35,	///复活点
							NPC_TYPE_UNFIGHTPET = 36, ///非战斗宠物
							NPC_TYPE_FIGHTPET = 37, ///战斗宠物
							NPC_TYPE_RIDE = 38, ///坐骑
							NPC_TYPE_TURRET = 39, /// 炮塔
							NPC_TYPE_BARRACKS = 40, /// 兵营
							NPC_TYPE_CAMP = 41,		/// 基地
};

enum
{
	NPC_ATYPE_NEAR = 1,/// 近距离攻击
	NPC_ATYPE_FAR = 2,/// 远距离攻击
	NPC_ATYPE_MFAR = 3,/// 法术远程攻击
	NPC_ATYPE_MNEAR = 4,/// 法术近身攻击
	NPC_ATYPE_NOACTION = 5,    /// 无攻击动作
	NPC_ATYPE_ANIMAL = 6  /// 动物类
};

/**
* \brief 用于偏移计算的坐标值
*/
struct zAdjust
{
	int x;    /**< 横坐标*/
	int y;    /**< 纵坐标*/
};

/**
* \brief 场景坐标
*/
struct zPos
{
	DWORD x;    /**< 横坐标*/
	DWORD y;    /**< 纵坐标*/
				/**
				* \brief 构造函数
				*
				*/
	zPos()
	{
		x = 0;
		y = 0;
	}
	/**
	* \brief 构造函数
	*
	*/
	zPos(const DWORD x, const DWORD y)
	{
		this->x = x;
		this->y = y;
	}
	/**
	* \brief 拷贝构造函数
	*
	*/
	zPos(const zPos &pos)
	{
		x = pos.x;
		y = pos.y;
	}
	/**
	* \brief 赋值操作符号
	*
	*/
	zPos & operator= (const zPos &pos)
	{
		x = pos.x;
		y = pos.y;
		return *this;
	}
	/**
	* \brief 重载+运算符号
	*
	*/
	const zPos & operator+ (const zPos &pos)
	{
		x += pos.x;
		y += pos.y;
		return *this;
	}
	/**
	* \brief 重载+运算符号
	* 对坐标进行修正
	*/
	const zPos & operator+ (const zAdjust &adjust)
	{
		x += adjust.x;
		y += adjust.y;
		return *this;
	}
	/**
	* \brief 重载+=运算符号
	*
	*/
	const zPos & operator+= (const zPos &pos)
	{
		x += pos.x;
		y += pos.y;
		return *this;
	}
	/**
	* \brief 重载+=运算符号
	* 对坐标进行修正
	*/
	const zPos & operator+= (const zAdjust &adjust)
	{
		x += adjust.x;
		y += adjust.y;
		return *this;
	}
	/**
	* \brief 重载-运算符号
	*
	*/
	const zPos & operator- (const zPos &pos)
	{
		x -= pos.x;
		y -= pos.y;
		return *this;
	}
	/**
	* \brief 重载-运算符号
	* 对坐标进行修正
	*/
	const zPos & operator- (const zAdjust &adjust)
	{
		x -= adjust.x;
		y -= adjust.y;
		return *this;
	}
	/**
	* \brief 重载-=运算符号
	*
	*/
	const zPos & operator-= (const zPos &pos)
	{
		x -= pos.x;
		y -= pos.y;
		return *this;
	}
	/**
	* \brief 重载-=运算符号
	* 对坐标进行修正
	*/
	const zPos & operator-= (const zAdjust &adjust)
	{
		x -= adjust.x;
		y -= adjust.y;
		return *this;
	}
	/**
	* \brief 重载==逻辑运算符号
	*
	*/
	const bool operator== (const zPos &pos) const
	{
		return (x == pos.x && y == pos.y);
	}
	/**
	* \brief 重载>逻辑运算符号
	*
	*/
	const bool operator> (const zPos &pos) const
	{
		return (x > pos.x && y > pos.y);
	}
	/**
	* \brief 重载>=逻辑运算符号
	*
	*/
	const bool operator>= (const zPos &pos) const
	{
		return (x >= pos.x && y >= pos.y);
	}
	/**
	* \brief 重载<逻辑运算符号
	*
	*/
	const bool operator< (const zPos &pos) const
	{
		return (x < pos.x && y < pos.y);
	}
	/**
	* \brief 重载<=逻辑运算符号
	*
	*/
	const bool operator<= (const zPos &pos) const
	{
		return (x <= pos.x && y <= pos.y);
	}
	/**
	* \brief 以自身为中心点，获取到另外一个坐标的方向
	* \param pos 另外一个坐标点
	* \return 方向
	*/
	const int getDirect(const zPos &pos) const
	{
		if (x == pos.x && y > pos.y)
		{
			return _DIR_UP;
		}
		else if (x < pos.x && y > pos.y)
		{
			return _DIR_UPRIGHT;
		}
		else if (x < pos.x && y == pos.y)
		{
			return _DIR_RIGHT;
		}
		else if (x < pos.x && y < pos.y)
		{
			return _DIR_RIGHTDOWN;
		}
		else if (x == pos.x && y < pos.y)
		{
			return _DIR_DOWN;
		}
		else if (x > pos.x && y < pos.y)
		{
			return _DIR_DOWNLEFT;
		}
		else if (x > pos.x && y == pos.y)
		{
			return _DIR_LEFT;
		}
		else if (x > pos.x && y > pos.y)
		{
			return _DIR_LEFTUP;
		}

		return _DIR_WRONG;
	}
};

/**
 * \brief 定义门派的基本结构
 *
 */
namespace School
{

#define MAX_BULLETIN_CHAR_NUMBER 1000          // 公告牌上允许的最大字符数
#define MAX_PRENTICE 20              // 一个人最多可以招收的徒弟数目
#define TEACHER_LEVEL 30            // 招收徒弟需要等级
#define CREATE_SCHOOL_REQUEST_LEVEL 60      // 创建门派等级需要 60
#define CREATE_SCHOOL_REQUEST_ITEM_ID 684      // 创建门派需要道具目前为天羽令
#define CREATE_SCHOOL_REQUEST_PRICE_GOLD 100000 // 创建门派需要的金钱数目
#define FIRST_LAYER_PRENTICE_REQUEST_LEVEL 50   // 创建门派者的第一层徒弟需要的角色级别
#define SECOND_LAYER_PRENTICE_REQUEST_LEVEL 40  // 创建门派者的第二层徒孙需要的角色级别

struct stSchoolInfo
{
  DWORD dwSchoolID;
  char  name[MAX_NAMESIZE+1];
  DWORD dwMasterSerialID;
  DWORD  size;
};
  
struct stSchoolMemberInfo
{
  DWORD dwSerialID;
  DWORD dwMasterID;
  DWORD dwPreSerialID;
  DWORD dwCharID;
  char  name[MAX_NAMESIZE+1];
  WORD  wdLevel;
  DWORD dwJoinTime;
  WORD  wdDegree;
  DWORD dwLastTime;
  DWORD dwSchoolID;
  BYTE  byTag;
  WORD  wdOccupation;
  DWORD master_total;
  DWORD master_balance;
  DWORD prentice_lastlevel;
  DWORD prentice_total;
};

}

#pragma pack()

/**
 * \brief 定义帮会的基本结构
 *
 */
#pragma pack(1)

namespace UnionDef
{

#define WD2BA(wd,ba)       \
do                         \
{                          \
  ba[0]= (wd >>8)&0xFF;     \
  ba[1]= wd& 0xFF;         \
}while(false)

#define BA2WD(ba,wd)      \
do                        \
{                          \
    wd   = ba[0];              \
    wd <<= 8;          \
    wd  |= ba[1];            \
}while(false)
    
#define SETMEMBERPOWER(ba) Cmd::set_state(ba,Cmd::GENERAL)

#define SETMASTERPOWER(ba)                \
do                                        \
{                                         \
  Cmd::set_state(ba,Cmd::CHANGE_ALIAS);   \
  Cmd::set_state(ba,Cmd::ADD_MEMBER);     \
  Cmd::set_state(ba,Cmd::FIRE_MEMBER);    \
  Cmd::set_state(ba,Cmd::GENERAL);        \
  Cmd::set_state(ba,Cmd::MASTER);        \
  Cmd::set_state(ba,Cmd::DARE);        \
  Cmd::set_state(ba,Cmd::NOTIFY);        \
}while(false)

#define SETSECONDPOWER(ba)                \
do                                        \
{                                         \
  Cmd::set_state(ba,Cmd::CHANGE_ALIAS);   \
  Cmd::set_state(ba,Cmd::ADD_MEMBER);     \
  Cmd::set_state(ba,Cmd::FIRE_MEMBER);    \
  Cmd::set_state(ba,Cmd::GENERAL);        \
  Cmd::set_state(ba,Cmd::NOTIFY); \
}while(false)

#define SETMEMBERPOWER_WD(WD) \
do                            \
{                             \
  BYTE temp[2];               \
  temp[0] = 0x00;      \
  temp[1] = 0x00;      \
  SETMEMBERPOWER(temp);       \
  BA2WD(temp,WD);             \
}while(false)


#define SETMASTERPOWER_WD(WD) \
do                            \
{                             \
  BYTE temp[2];               \
  temp[0] = 0x00;      \
  temp[1] = 0x00;      \
  SETMASTERPOWER(temp);       \
  BA2WD(temp,WD);             \
}while(false)


const DWORD CREATE_UNION_NEED_PRICE_GOLD = 50000; // 建立帮会需要金钱10万
const DWORD CREATE_UNION_NEED_ITEM_ID    = 684;     // 建立帮会所需要的道具ID 天羽令
const DWORD CREATE_UNION_NEED_LEVEL      = 45;      // 建立帮会需要的人物等级
const DWORD DESTROYTIME        = 30*24*60*60; //投票有效期 一个月的秒数
const DWORD CREATE_UNION_NEED_VOTE       =  2;
const DWORD CREATE_UNION_NEED_MAN_NUM    =30;  // 帮会成立需要人数
    
#define DEFAULTMASTERALIAS "帮主"
#define DEFAULTMEMBERALIAS "帮众"

struct stUnionInfo             // 数据库读取结构，请不要随意修改，修改注意更新所有代码
{
  DWORD    dwUnionID;        // 帮会的ID
  char    name[MAX_NAMESIZE+1];       // 帮会名称
  DWORD    dwCharID;                   // 帮主的角色ID
  char    masterName[MAX_NAMESIZE+1];    // 帮主的名字
  BYTE    byVote;          // 签名标志为1表示处于签名期间
  DWORD    dwCrTime;        // 帮会创立时间
  WORD    wdLevel;                        // 帮会级别
  QWORD    qwExp;                       // 帮会经验
  DWORD     dwMana;          // 帮会威望
  DWORD    dwCountryID;        // 所属国家
  DWORD    dwActionPoint;        // 帮会行动力
  DWORD     dwMoney;        // 帮会资金
  char    note[254+1];        // 帮会介绍
  DWORD    calltimes;        // 令牌使用次数
};

struct stUnionMemberInfo                      // 数据库读取结构，请不要随意修改，修改注意更新所有代码
{
  DWORD  dwCharID;          // 会员角色ID
  char  name[MAX_NAMESIZE+1];        // 会员角色名称    
  char    aliasname[MAX_NAMESIZE+1];       // 会员别名
  WORD    wdPower;          // 会员权限
  WORD    wdOccupation;          // 会员的职业
  DWORD   dwSeptID;          // 会员所属家族
};

}

#pragma pack()

#ifdef _MSC_VER
#pragma warning(disable:4200)
#endif //_MSC_VER

class SceneUser;
struct zLiveSkillB;

typedef DWORD tItemThisID;
#define INVALID_THISID 0xffffffff

// 道具的类型
enum enumItemType
{
  ItemType_None,

  ItemType_Resource = 16,//16代表原料类

  ItemType_Leechdom,//17代表药品类
  ItemType_FoodRes,//18代表食物原料类
  ItemType_Food,  //19代表食物类
  ItemType_Tools,  //20代表劳动工具类
  ItemType_Arrow,  //21代表配合弓使用的箭支类
  ItemType_BattleHorse,//22战马
  ItemType_Pack,  //23代表包裹类
  ItemType_Money,  //24代表金钱类
  ItemType_Scroll,//25代表转移卷轴类
  ItemType_Move,  //26代表特殊移动道具类
  ItemType_LevelUp,//27代表道具升级需要的材料类
  ItemType_CaptureWeapon,//28代表驯服宠物用武器
  ItemType_Union,//29代表创建帮会需要的道具.
  ItemType_Tonic,//30表示自动补药类道具.
  ItemType_Gift,//31代表礼品类物品.
  ItemType_Other,
  ItemType_MASK = 33,//33代表蒙面巾
  ItemType_Quest = 34,
  ItemType_HORSE = 35,
  ItemType_SOULSTONE = 37,//37代表魂魄石类
  ItemType_Wedding = 38,//38代表婚礼类
  ItemType_Change = 41,//41 代表合成道具
  ItemType_Auto = 42,//42 代表自动练功
  ItemType_SkillUp = 43,//43 代表技能升级道具
  ItemType_Book = 44,//44代表书籍
  ItemType_Store = 45,//45 代表仓库
  ItemType_Renew = 46,//46 代表洗点道具
  ItemType_Repair = 47,//47代表修复宝石类
  ItemType_DoubleExp = 52,//52代表双倍经验类型
  ItemType_Honor = 53,//53代表荣誉之星类型
  ItemType_TONG = 54,//帮主令  
  ItemType_FAMILY = 55,//家族令
  ItemType_Adonment = 56,//56代表装饰品
  ItemType_SpecialBook = 57,//57代表特殊书籍
  ItemType_GreatLeechdom = 58,//58大计量药品
  ItemType_ClearProperty = 59,//59洗点道具
  ItemType_UseSkill = 60,// 附带技能类道具
  ItemType_Amulet = 61,// 护身符类道具
  ItemType_GreatLeechdomMp = 62,//62大计量自动补兰道具
  ItemType_KING = 65,//国王令

  ItemType_DoubleExpZ =  66,  //中级经验倍率物品
  ItemType_DoubleExpC =  67,  //初级经验倍率物品
  ItemType_DoubleExpG = 68,   //高级经验倍率物品

  ItemType_Blade =104,		// sky 104代表单手刀
  ItemType_Sword =105,		// sky 105代表左手剑
  ItemType_Axe =106,		// sky 106代表双手类武器
  ItemType_Hammer =107,		// sky 107代表匕首类武器
  ItemType_Staff =108,		// sky 108代表飞标类武器
  ItemType_Crossbow =109,	// sky 109代表法杖类武器
  ItemType_Fan =110,		// sky 110代表盾牌类
  ItemType_Stick =111,		// sky 111预留武器位
  ItemType_Shield =112,		// sky 112预留武器位

  ItemType_ClothBody =101,  // sky 101代表布质服装
  ItemType_Helm =113,		//sky 113代表角色头盔类(布)
  ItemType_Caestus =114,	//sky 114代表角色腰带类(布)
  ItemType_Cuff = 115,		//sky 115代表角色护腕类(布)
  ItemType_Shoes = 116,		//sky 116代表角色鞋子类(布)

  tyItemType_Shoulder = 131,		//131代表角色肩膀（布）
  tyItemType_Gloves = 132,			//132代表角色手套（布）
  tyItemType_Pants = 133,  			//133代表角色裤子（布）

  ItemType_Necklace = 117,	//sky 117代表角色项链类
  ItemType_Fing = 118,		//sky 118代表角色戒指类

  /*sky 新增板和皮类型防具支持*/
  ItemType_FellBody =102,			//sky 102代表皮甲类服装
  ItemType_Helm_Paper = 119,		//sky 119代表角色头盔类(皮)
  ItemType_Caestus_Paper =120,		//sky 120代表角色腰带类(皮)
  ItemType_Cuff_Paper = 121,		//sky 121代表角色护腕类(皮)
  ItemType_Shoes_Paper = 122,		//sky 122代表角色鞋子类(皮)
  ItemType_Shoulder_Paper = 134,    //sky 134代表角色肩膀（皮）
  ItemType_Gloves_Paper = 135,		//sky 135代表角色手套（皮）
  ItemType_Pants_Paper = 136,		//sky 136代表角色裤子（皮）

  ItemType_MetalBody =103,			//sky 103代表板甲类服装
  ItemType_Helm_Plate = 123,		//sky 123代表角色头盔类(板)
  ItemType_Caestus_Plate =124,		//sky 124代表角色腰带类(板)
  ItemType_Cuff_Plate = 125,		//sky 125代表角色护腕类(板)
  ItemType_Shoes_Plate = 126,		//sky 126代表角色鞋子类(板)

  ItemType_FashionBody = 127,  //119代表时装
  ItemType_HighFashionBody = 128, //124代表高级时装（SKY新增）
  ItemType_Flower = 129,  //120代表鲜花,采集手套...
  ItemType_BMW = 130,  //119代表宝马

  ItemType_Shoulder_Plate = 137,    //sky 137代表角色肩膀（板）
  ItemType_Gloves_Plate = 138,		//sky 138代表角色手套（板）
  ItemType_Pants_Plate = 139,		//sky 139代表角色裤子（板）

  //lxb begin 08.12.29
  ItemType_Bangle = 140,				//手镯
  ItemType_Jade = 141,				//玉佩
  ItemType_Manteau = 142,				//披风
  ItemType_Earrings=143,				//耳环	//Shx Add;
  //lxb end  
  ItemType_Building = 199,	//sky  建筑物品
  ItemType_SkillItem = 200, //sky  技能物品
  ItemType_MAX		 = 256, //sky  不可用最大值

};

#define BOW_ARROW_ITEM_TYPE 21

namespace Object
{

enum {
  INVALID_LOC = (DWORD) -1,
  INVALID_TAB = (DWORD) -1,
  INVALID_X = (WORD) -1,
  INVALID_Y = (WORD) -1,
};

}

#pragma pack(1)

struct stObjectLocation{

private:
  DWORD dwLocation;  // 格子类型
  DWORD dwTableID;  // 包袱ID
  WORD  x;
  WORD  y;

  friend class Package;
public:
  stObjectLocation() 
    : dwLocation(Object::INVALID_LOC),dwTableID(Object::INVALID_TAB),
    x(Object::INVALID_X),y(Object::INVALID_Y)
  {

  }

  stObjectLocation(const stObjectLocation& loc) 
    : dwLocation(loc.dwLocation),dwTableID(loc.dwTableID),x(loc.x),y(loc.y)
  {

  }

  stObjectLocation(DWORD loc,DWORD tab,WORD _x,WORD _y) 
    : dwLocation(loc),dwTableID(tab),x(_x),y(_y)
  {

  }
  
  void operator = (const stObjectLocation& loc)
  {
    dwLocation =loc.dwLocation;
    dwTableID = loc.dwTableID;
    x = loc.x;
    y = loc.y;
  }
  
  bool operator == (const stObjectLocation & st) const
  {
    return dwLocation == st.dwLocation && dwTableID == st.dwTableID && x == st.x && y == st.y;
  }

  bool operator != (const stObjectLocation & st) const
  {
    return !(*this == st);
  }

  DWORD tab() const
  {
    return dwTableID;
  }

  void tab(DWORD t) 
  {
    dwTableID = t;
  }

  DWORD loc() const
  {
    return dwLocation;
  }

  WORD xpos() const
  {
    return x;
  }

  WORD ypos() const
  {
    return y;
  }
};

struct oskill
{
  DWORD id;
  BYTE level;
  BYTE count;
  BYTE maxcount;
  BYTE other;
};

//lxb begin 08.12.30
const DWORD INVALID_HOLE = 0xffffffff;	//没有孔
const DWORD EMPTY_HOLE = 0;	//孔是空的
//lxb end

const BYTE HOLE_ACTIVVATED_OFF = 0;

//sky 新增宝石等相关结构
typedef struct Gem_Pop 
{
	bool	M_State;	//激活状态(true:激活 false:未激活)
	DWORD	GemID;		//宝石ID用来在客户端显示宝石的图标

	WORD	gem_str;	//力量
	WORD	gem_inte;	//智力
	WORD	gem_dex;	//敏捷
	WORD	gem_spi;	//精神
	WORD	gem_con;	//耐力
	WORD	gem_def;	//物理防御
	WORD	gem_mdef;	//魔法防御
	WORD	gem_dhpp;	//物理免伤
	WORD	gem_dmpp;	//魔法免伤
	WORD	gem_atk;	//物理攻击力
	WORD	gem_mkt;	//魔法攻击力

} GemPop;
//sky 宝石结构 end


typedef struct _Object
{
	 DWORD qwThisID;   //物品唯一id
	 DWORD dwObjectID;  ////物品类别id
	 char strName[MAX_NAMESIZE + 1]; //名称
	 
	 stObjectLocation pos;  // 位置
	 DWORD dwNum;  // 数量
	 BYTE upgrade;//物品升级等级
	 BYTE kind;  //物品类型,0普通,1蓝色,2绿装,4紫装,8橙装
	 DWORD exp;  //道具经验
	 
	 WORD needlevel;        // 需要等级

	 DWORD maxhp;          // 最大生命值
	 DWORD maxmp;          // 最大法术值
	 DWORD maxsp;          // 最大体力值

	 DWORD pdamage;        // 最小攻击力
	 DWORD maxpdamage;      // 最大攻击力
	 DWORD mdamage;        // 最小法术攻击力
	 DWORD maxmdamage;      // 最大法术攻击力

	 DWORD pdefence;        // 物防
	 DWORD mdefence;        // 魔防
	 BYTE damagebonus;      // 伤害加成 x% from 道具基本表
	 BYTE damage;        // 增加伤害值x％ from 神圣装备表
	   
	 WORD akspeed;        // 攻击速度
	 WORD mvspeed;        // 移动速度
	 WORD atrating;        // 命中率
	 WORD akdodge;        // 躲避率

	 DWORD color;        // 颜色  

	 WORD str;  // 力量
	 WORD inte;  // 智力
	 WORD dex;  // 敏捷
	 WORD spi;  // 精神
	 WORD con;  // 体质
	 
	 WORD fivetype;  // 五行属性
	 WORD fivepoint; // 五行属性
	 
	 WORD hpr;  // 生命值恢复----
	 WORD mpr;  // 法术值恢复----
	 WORD spr;  // 体力值恢复----

	 WORD holy;  //神圣一击  
	 WORD bang;  //重击

	 WORD pdam;  // 增加物理攻击力----
	 WORD pdef;  // 增加物理防御力----
	 WORD mdam;  // 增加魔法攻击力----
	 WORD mdef;  // 增加魔法防御力----
	 
	 WORD poisondef; //抗毒增加
	 WORD lulldef; //抗麻痹增加
	 WORD reeldef; //抗眩晕增加
	 WORD evildef; //抗噬魔增加
	 WORD bitedef; //抗噬力增加
	 WORD chaosdef; //抗混乱增加
	 WORD colddef; //抗冰冻增加
	 WORD petrifydef; //抗石化增加
	 WORD blinddef; //抗失明增加
	 WORD stabledef; //抗定身增加
	 WORD slowdef; //抗减速增加
	 WORD luredef; //抗诱惑增加

	 WORD durpoint; //恢复装备耐久度点数
	 WORD dursecond; //恢复装备耐久度时间单位

	 struct skillbonus {
	   WORD id; //技能 id
	   WORD point; // 技能点数
	 } skill[10]; //技能加成

	 struct skillsbonus {
	   WORD id; //技能 id
	   WORD point; // 技能点数
	 } skills;  //全系技能加成

	 WORD poison; //中毒增加
	 WORD lull; //麻痹增加
	 WORD reel; //眩晕增加
	 WORD evil; //噬魔增加
	 WORD bite; //噬力增加
	 WORD chaos; //混乱增加
	 WORD cold; //冰冻增加
	 WORD petrify; //石化增加
	 WORD blind; //失明增加
	 WORD stable; //定身增加
	 WORD slow; //减速增加
	 WORD lure; //诱惑增加

	 //lxb begin 08.12.30
	 WORD giddy;		//眩晕
	 WORD coma;		//昏迷
	 WORD halt;		//定身
	 WORD dread;		//恐惧
	 WORD slowdown;	//减速
	 WORD banish;	//放逐

	 WORD giddy_def;		//防眩晕
	 WORD coma_def;		//防昏迷
	 WORD halt_def;		//防定身
	 WORD dread_def;		//防恐惧
	 WORD slowdown_def;	//防减速
	 WORD banish_def;	//防放逐
	 //lxb end
	 
	 struct leech
	 {
	   BYTE odds;    //x
	   WORD effect;  //y
	 };
	 leech hpleech; //x%吸收生命值y
	 leech mpleech; //x%吸收法术值y
	 
	 BYTE hptomp; //转换生命值为法术值x％
	 BYTE dhpp; //物理伤害减少x%  
	 BYTE dmpp; //法术伤害值减少x%    

	 BYTE incgold; //增加金钱掉落x%
	 BYTE doublexp; //x%双倍经验    
	 BYTE mf; //增加掉宝率x%
	 
	 BYTE bind;  //装备是否绑定

	 union {
	   BYTE _five_props[5];
	   struct {
	     //五行套装相关属性
	     BYTE dpdam; //物理伤害减少%x
	     BYTE dmdam; //法术伤害减少%x
	     BYTE bdam; //增加伤害x%
	     BYTE rdam; //伤害反射%x
	     BYTE ignoredef; //%x忽视目标防御
	   };
	 };

	 WORD fiveset[5]; //五行套装,按顺序排列

	 //...
	 BYTE width;  //宽度
	 BYTE height; //高度
	 WORD dur;    //当前耐久
	 WORD maxdur; //最大耐久
	 
	 GemPop Hsocket[SOCKET_MAXNUM]; //sky 宝石孔
	 DWORD price;     //价格
	 DWORD cardpoint; //点卡

	 char maker[MAX_NAMESIZE + 1]; //打造者

	 //Sky新增自由加点结构
	struct Freedom_Attribute {
		WORD Surplus_Attribute;	//当前剩余属性点
		//用于洗点用的记录
		WORD str_Attribute;		// 力量已经加过的自由点
		WORD inte_Attribute;	// 智力已经加过的自由点
		WORD dex_Attribute;		// 敏捷已经加过的自由点
		WORD spi_Attribute;		// 精神已经加过的自由点
		WORD con_Attribute;		// 体质已经加过的自由点

	} Freedom;

//[Shx Add 套装属性]************************************
//#pragma pack(1)
	struct Suit_Attribute
	{
		struct __Attr
		{
			BYTE eRequire;		//激活条件
			BYTE eKey;			//激活属性			
			WORD eValue;		//值			
		};

		char	Suit_name[MAX_NAMESIZE + 1];	//套装名称;
		WORD	Suit_ID;	//套装ID;
		BYTE	nPart;
		BYTE    nEffect;
		DWORD	PartList[MAX_SUIT_NUM];	//套装成员ID;
		__Attr	EffectList[MAX_SUIT_NUM];
	} SuitAttribute;
//#pragma pack(4)
	//End 套装属性;
}t_Object;

#pragma pack()

namespace Object
{
  static stObjectLocation INVALID_POS;
}

//#define BINARY_VERSION   0
//#define BINARY_VERSION   20051018
//#define BINARY_VERSION  20051225
//#define BINARY_VERSION     20060124
#define BINARY_VERSION     20060313

struct ZlibObject
{
  DWORD   version;
  DWORD  count;
  BYTE data[0];
  ZlibObject()
  {
    count = 0;
    version = 0;
  }
};

struct SaveObject
{
  union
  {
    struct 
    {
      DWORD createtime;
      DWORD dwCreateThisID;  
    };
    QWORD createid;
  };
  // */
  t_Object object;
};

/**
 * \brief 技能压缩结构
 */
struct ZlibSkill
{
  DWORD count;
  BYTE data[0];
  ZlibSkill()
  {
    count = 0;
  }
};

/**
 * \brief 技能存档单元
 */
struct SaveSkill
{
  DWORD type;
  DWORD level;
};

/**
 * \brief 技能分类
 *
 */
enum SkillType
{
  SKILL_TYPE_DAMAGE = 1, ///直接伤害
  SKILL_TYPE_RECOVER, ///恢复系
  SKILL_TYPE_BUFF, ///增益效果
  SKILL_TYPE_DEBUFF, ///负面效果
  SKILL_TYPE_SUMMON, ///召唤
  SKILL_TYPE_RELIVE  ///复活
};

struct LiveSkill
{
public:
  WORD id; //技能标识
  WORD level; //等级
  DWORD point; //等级后值,小点

  enum {
    DEFAULT_START_LEVEL  = 1,//生活技能默认开始等级
    WORKING_TIME = 5,//工作时间
    ADVANCE_WORK_BONUS = 500,//获得物品概率加成
    MIN_NEED_SP = 4,
    MAX_NEED_SP = 8,
    ADVANCE_LEVEL = 22,//进阶技能需要等级
    ODDS_BENCHMARK = 10000,
  };

  enum {
    BASIC_WORK = 1,
    MAKE_WORK = 2,
    ADVANCE_WORK = 3,
  };

  int bonus(SceneUser* user,int points = 0);
  int bonus_items(SceneUser* user,zLiveSkillB* base_skill);
  static int bonus_exp(SceneUser* user,DWORD exp);
  
  static int consume_sp();
  
  const static int odds[];
};

#pragma pack(1)

typedef struct _Skill
{
  DWORD  skillid;          //技能ID
  DWORD  level;            //技能等级
//  DWORD  maxlevel;          //技能等级
//  DWORD  nextlevel;          //需要角色等级
//  DWORD  needtype;          // 需要职业
//  DWORD  five;            // 五行属性
//  DWORD  firstfive;          // 最初五行点数
  //DWORD  nextfive;          // 五行点数
}t_Skill;
#pragma pack()

namespace SkillDef
{
  enum ATTACK_TYPE
  {
    AttackNear = 0,
    AttackFly = 1,
    AttackDirect = 2
  };

  enum
  {
    AttackNine = 1,
    AttackEight = 2,
    AttackThree = 3,
    AttackFive_1 = 4,
    AttackFive_2 = 5,
    AttackFive_3 = 6,
    AttackCross = 7

  };
  enum   SKILL_STATUS
  {
    SKILL_default,//0默认为错误类型
    SKILL_dvalue,//伤害值
    SKILL_reflect,//反弹
    SKILL_sdam,//技能攻击力
    SKILL_mdam,//法术攻击力
    SKILL_maxmp,//法术值上限
    SKILL_mpspeed,//法术值回复速度
    SKILL_mppersist,//法术值持续
    SKILL_mp,     //法术值
    SKILL_mpdef, //法术防御
    SKILL_sp,     //体力值
    SKILL_maxsp,//体力值上限
    SKILL_sppersist,//体力值持续
    SKILL_spspeed,//体力值回复速度
    SKILL_hp,     //生命值
    SKILL_maxhp, //生命值上限
    SKILL_hppersist,//生命值持续
    SKILL_hpspeed,//生命值回复速度
    SKILL_mvspeed,//移动速度
    SKILL_pdam,   //物理攻击力
    SKILL_atrating,//命中率
    SKILL_skillrating,//技能命中率
    SKILL_akdodge,//闪避率
    SKILL_cancel,//状态消除
    SKILL_aspeed,//攻击速度
    SKILL_relive,//复活
    SKILL_hitback,//击退
    SKILL_change,//攻击目标变为施法者
    SKILL_topet,//变为随机小动物
    SKILL_dam2ddef,//攻防转换
    SKILL_poison,//中毒状态
    SKILL_petrify,//石化状态
    SKILL_blind,//失明状态
    SKILL_chaos,//混乱状态
    SKILL_cold,//冰冻状态
    SKILL_palsy,//麻痹状态
    SKILL_bleeding,//流血状态
    SKILL_sevenp,//降低陷入七大状态几率
    SKILL_coldp,//减少陷入冰冻状态几率
    SKILL_poisonp,//减少陷入中毒状态几率
    SKILL_petrifyp,//减少陷入石化状态几率
    SKILL_blindp,//减少陷入失明状态几率
    SKILL_chaosp,//减少陷入混乱状态几率
    SKILL_mgspeed,//减少技能施放间隔
    SKILL_cancelatt //不能攻击施法者
  };

//sky  技能目标定义
#define TARGET_SELF 1      //自己
#define TARGET_FRIEND 2		//友方
#define TARGET_ENEMY 4		//敌人
#define TARGET_NPC 8		//NPC
#define TARGET_TERRASURFACE 16	//地表
#define TARGET_PET 32			//宠物
#define TARGET_SUMMON 64		//召唤兽

// sky 技能中心点定义
#define SKILL_CENTER_TYPE_SELF  2
#define SKILL_CENTER_TYPE_MOUSE 1

#define SKILLINVALID 0 
#define SERVER_SKILL_ATTACK_NORMAL 78		//单手武器普通攻击
#define	SERVER_SKILL_DAGGER_ATTACK_NORMAL 79 //双持武器(匕首)普通攻击
#define	SERVER_SKILL_DART_ATTACK_NORMAL 80	//飞镖武器普通攻击
#define	SERVER_SKILL_HANDS_ATTACK_NORMAL 77	//双手武器普通攻击
#define MAX_SKILLLEVEL 10

};

template <typename T>
class SingletonFactory
{
  public:
    static T* Instance()
    {
      return new T();
    }
};

template <typename T,typename MANA = SingletonFactory<T> > 
class Singleton
{
  private:
    /**
     * \brief 拷贝构造函数，没有实现，禁用掉了
     *
     */
    Singleton(const Singleton&);

    /**
     * \brief 赋值操作符号，没有实现，禁用掉了
     *
     */
    const Singleton & operator= (const Singleton &);
  protected:

    static T* ms_Singleton;
    Singleton( void )
    {
    }

    ~Singleton( void )
    {
    }

  public:
  
    static void delMe(void)
    {//可以在子类的destoryMe中被调用
      if (ms_Singleton)
      {
        delete ms_Singleton;
        ms_Singleton = 0;
      }
    }

	static T* Instance(void)
	{
		if (!ms_Singleton)
		{
			ms_Singleton = MANA::Instance();
		}

		return ms_Singleton;
	}

    static T& getMe(void)
    {
      return *Instance();
    }

};

template <typename T,typename MANA>
T* Singleton<T,MANA>::ms_Singleton = 0;

/**
 * \brief 定义人物角色相关信息
 */


#pragma pack(1)

#define HAIRTYPE_MASK  0xff000000    /// 头发发型
#define HAIRRGB_MASK  0x00ffffff    /// 头发颜色
const int exploit_arg = 100;      // 功勋值同比放大系数

//---------------------------------
#define LEVELUP_HP_N      15
#define LEVELUP_MP_N      1
#define LEVELUP_SP_N      5

#define LEVELUP_RESUMEHP_N    0
#define  LEVELUP_RESUMEMP_N    0
#define LEVELUP_RESUMESP_N    0

#define LEVELUP_ATTACKRATING_N  1
#define LEVELUP_ATTACKDODGE_N  1

#define LEVELUP_MOVESPEED_N    0
#define LEVELUP_ATTACKSPEED_N  0

#define LEVELUP_PDAMAGE_N    0
#define LEVELUP_MDAMAGE_N    0
#define LEVELUP_PDEFENCE_N    0
#define LEVELUP_MDEFENCE_N    0

#define LEVELUP_BANG_N    0
//----------------------------------
#define BASEDATA_M_HP      500
#define BASEDATA_M_MP      60
#define BASEDATA_M_SP      100

#define BASEDATA_M_RESUMEHP    1
#define  BASEDATA_M_RESUMEMP    1
#define BASEDATA_M_RESUMESP    1

#define BASEDATA_M_ATTACKRATING  1
#define BASEDATA_M_ATTACKDODGE  1

#define BASEDATA_M_MOVESPEED  0
#define BASEDATA_M_ATTACKSPEED  0

#define BASEDATA_M_PDAMAGE    11
#define BASEDATA_M_MDAMAGE    11
#define BASEDATA_M_PDEFENCE    1
#define BASEDATA_M_MDEFENCE    1

#define BASEDATA_M_BANG    1
//----------------------------------
#define BASEDATA_F_HP      500
#define BASEDATA_F_MP      60
#define BASEDATA_F_SP      90

#define BASEDATA_F_RESUMEHP    1
#define  BASEDATA_F_RESUMEMP    1
#define BASEDATA_F_RESUMESP    1

#define BASEDATA_F_ATTACKRATING  1
#define BASEDATA_F_ATTACKDODGE  1

#define BASEDATA_F_MOVESPEED  0
#define BASEDATA_F_ATTACKSPEED  0

#define BASEDATA_F_PDAMAGE    11
#define BASEDATA_F_MDAMAGE    11
#define BASEDATA_F_PDEFENCE    1
#define BASEDATA_F_MDEFENCE    1

#define BASEDATA_F_BANG    1
//----------------------------------

struct CharBase
{
  DWORD accid;            /// 账号
  DWORD id;              /// 角色编号
  char  name[MAX_NAMESIZE + 1];    /// 角色名称
  WORD  type;              /// 性别
  WORD  level;            /// 角色等级
  WORD  face;              /// 头像
  DWORD hair;              /// 头发，发型和颜色
  DWORD bodyColor;              /// 光身颜色
  DWORD goodness;            /// 善恶度
  DWORD mapid;            /// 角色所在地图编号
  char  mapName[MAX_NAMESIZE + 1];  /// 角色所在地图名称
  DWORD x;              /// 角色所在坐标x
  DWORD y;              /// 角色所在坐标y
  DWORD unionid;            /// 帮会ID
  DWORD schoolid;            /// 门派ID
  DWORD septid;            /// 家族ID
  DWORD hp;              /// 当前生命值
  DWORD mp;              /// 当前法术值
  DWORD sp;              /// 当前体力值
  QWORD exp;              /// 当前经验值
  char OldMap[MAX_MAP_PATH];	///sky 移动到新地图前的老地图位置数据
  WORD  skillpoint;          /// 技能点数
  WORD  points;            /// 未分配人物属性点数
  DWORD  country;            /// 国家
  DWORD  consort;              /// 配偶
 
  QWORD forbidtalk;          ///禁言
  DWORD bitmask;            /// 标志掩码
  DWORD onlinetime;          /// 在线时间统计
  union {
    struct {
      WORD wdCon;  //体质
      WORD wdStr;  //体力
      WORD wdDex;  //敏捷
      WORD wdInt;  //智力
      WORD wdMen;  //精神
    };
    WORD wdProperty[5];
  };
  WORD reliveWeakTime;      /// 复活虚弱剩余时间
  DWORD useJob;        // sky 角色职业(数据库位置使用原文采"GRACE"段)
  DWORD exploit;        /// 功勋值
  char tiretime[36+1];      /// 疲劳时间标记
  DWORD offlinetime;        /// 上次下线时间
  DWORD fivetype;          /// 五行类型
  DWORD fivelevel;        /// 五行点数
  DWORD pkaddition;        /// 善恶追加值
  DWORD money;        /// 当前银子,只存储维护,不能使用
  DWORD answerCount;      /// 当天答题次数
  DWORD honor;        //荣誉值
  DWORD maxhonor;        //最大荣誉值
  DWORD gomaptype;      //跳地图类型
  DWORD msgTime;        //下次发送GM留言的时间
  DWORD accPriv;      //帐号权限
  DWORD gold;          /// 金币
  DWORD ticket;         //点券数
  DWORD createtime;      /// 角色创建时间
  DWORD goldgive;        /// 金币冲值赠品数量
  BYTE petPack;        /// 宠物包裹大小
  DWORD petPoint;        /// 奖励的宠物修炼时间
  DWORD levelsept;      /// 离开家族的时间
  DWORD punishTime;      /// 杀人被抓的时间，分钟为单位
  DWORD trainTime;      /// 在练级地图逗留的时间
  DWORD  zs;                   ///转生次数
  DWORD doubletime;          ///双倍物品剩余时间
};

struct CharState
{
  DWORD maxhp;            /// 最大生命值 *
  DWORD resumehp;            /// 生命值恢复 *
  DWORD maxmp;            /// 最大法术值 *
  DWORD resumemp;            /// 法术值恢复 *
  DWORD maxsp;                     /// 最大体力值 *
  DWORD resumesp;                  /// 体力恢复值 *

  DWORD pdamage;                   /// 最小物理攻击力 *
  DWORD maxpdamage;          /// 最大物理攻击力 *
  DWORD mdamage;            /// 最小法术攻击力 *
  DWORD maxmdamage;          /// 最大法术攻击力 *
  DWORD pdefence;            /// 物理防御力 *
  DWORD mdefence;            /// 法术防御力 *
  QWORD nextexp;            /// 升级经验值 *
  WORD  attackspeed;          /// 攻击速度 *
  WORD  movespeed;          /// 移动速度 *
  SWORD  attackrating;        /// 攻击命中 *
  SWORD  attackdodge;          /// 攻击躲避 *
  WORD  bang;              /// 重击 *
  WORD  charm;                     /// 魅力值 *
  BYTE  attackfive;          /// 攻击五行 *
  BYTE  defencefive;          /// 防御五行 *
  union {
    struct {
      WORD wdCon;  //体质
      WORD wdStr;  //体力
      WORD wdDex;  //敏捷
      WORD wdInt;  //智力
      WORD wdMen;  //精神
    };
    WORD wdProperty[5];
  };

  DWORD stdpdamage;          /// 标准物理攻击力
  DWORD stdmdamage;          /// 标准法术攻击力
  DWORD stdpdefence;          /// 标准物理防御力
  DWORD stdmdefence;          /// 标准法术防御力
  WORD  stdbang;            /// 标准重击率
};

#ifdef _TEST_DATA_LOG
struct CharTest
{
  DWORD upgrade_time;//升级时间
  DWORD upgrade_usetime;//本级使用时间
  DWORD death_times;//死亡次数
  DWORD hp_leechdom;//使用生命值药品个数
  DWORD mp_leechdom;//使用法术值药品个数
  DWORD sp_leechdom;//使用体力值药品个数
  DWORD get_money;//得到银子数
  DWORD get_heigh;//得到高级装备个数
  DWORD get_socket;//得到带孔装备个数
  DWORD get_material;//得到原料个数
  DWORD get_stone;//得到宝石个数
  DWORD get_scroll;//得到卷轴个数
  DWORD money;//当前银子数
};
#endif

struct CharSave
{
  CharBase   charbase;
  DWORD    dataSize;
  char     data[0];
};

#define MAX_TEMPARCHIVE_SIZE 0x10000
struct TempArchiveMember
{
  DWORD type;
  DWORD size;
  char data[0];
};

enum TempArchiveType
{
  TEAM,//队伍
  ENTRY_STATE,//队伍
  PET,//宠物
  SAFETY_STATE,// 临时关闭密码保护
  ITEM_COOLTIME,// sky 物品冷却时间
};

struct BinaryArchiveMember
{
  DWORD type;
  DWORD size;
  char data[0];
};

enum BinaryArchiveType
{
  BINARY_DOUBLE_EXP_OBJ,///双倍经验道具
  BINARY_TONG_OBJ,///帮会令牌类道具
  BINARY_KING_OBJ,///国王令牌类道具
  BINARY_FAMILY_OBJ,///家族令牌类道具
  BINARY_CHANGE_COUNTRY_TIME,/// 最后一次叛国的时间
  BINARY_SAFETY,/// 是否进行财产保护
  BINARY_GIVE_MATARIAL_NUM,//道具卡兑换材料的组数
  BINARY_CARD_NUM,     //道具卡张数
  BINARY_SAFETY_SETUP,/// 保护设置
  BINARY_MAX, ///最大数值(占位用)
};

const WORD  MAX_LEVEL      = 150;          /// 最大角色等级
const DWORD MAX_GOODNESS    = 9999;          /// 最大善恶度
const DWORD MAX_HP      = 999999;        /// 最大生命值
const DWORD MAX_RESUMEHP    = 1000;          /// 生命值恢复
const DWORD MAX_MP      = 999999;        /// 最大法术值
const DWORD MAX_RESUMEMP    = 1000;          /// 法术值恢复
const DWORD MAX_SP      = 999999;        /// 最大体力值
const DWORD MAX_RESUMESP    = 1000;          /// 体力值恢复
const DWORD MAX_PDAMAGE      = 999999;        /// 最大物理攻击力
const DWORD MAX_RDAMAGE      = 999999;        /// 最大远程攻击力
const DWORD MAX_TDAMAGE     = 999999;        /// 最大仙术攻击力
const DWORD MAX_MDAMAGE      = 999999;        /// 最大法术攻击力
const DWORD MAX_PDEFENCE    = 999999;        /// 最大物理防御力
const DWORD MAX_MDEFENCE    = 999999;        /// 最大法术防御力
#ifdef _MSC_VER
const QWORD MAX_EXP      = 9999999999i64;
#else //!_MSC_VER
const QWORD MAX_EXP      = 9999999999LL;      /// 最大经验值
#endif //_MSC_VER
const WORD  MAX_ATTACKSPEED    = 100;          /// 攻击速度
const WORD  MAX_MAGICSPEED    = 100;          /// 施法速度
const WORD  MAX_MOVESPEED    = 200;          /// 移动速度
const WORD  MAX_ATTACKRATING    = 999;          /// 攻击命中
const WORD  MAX_ATTACKDODGE    = 999;          /// 攻击躲避
const WORD  MAX_MAGICRATING    = 999;          /// 法术命中
const WORD  MAX_MAGICDODGE    = 999;          /// 法术躲避
const WORD  MAX_LUCKY      = 999;          /// 幸运值
const WORD  MAX_METAL      = 999;          /// 金
const WORD  MAX_WOOD      = 999;          /// 木
const WORD  MAX_WATER      = 999;          /// 水
const WORD  MAX_FIRE      = 999;          /// 火
const WORD  MAX_SOIL      = 999;          /// 土
const WORD  MAX_METALRESISTANCE    = 10000;        /// 金系抵抗
const WORD  MAX_WOODRESISTANCE    = 10000;        /// 木系抵抗
const WORD  MAX_WATERRESISTANCE    = 10000;        /// 水系抵抗
const WORD  MAX_FIRERESISTANCE    = 10000;        /// 火系抵抗
const WORD  MAX_SOILRESISTANCE    = 10000;        /// 土系抵抗
const WORD  MAX_POINTS      = 1500;          /// 点数

const DWORD PUBLIC_COUNTRY = 6;

///得到另一只手
#define otherHand(hand)         ((hand)^3)

///得到另一只手镯
#define otherBangle(bangle)     ((bangle)^1)

namespace Cmd{

//BEGIN_ONE_CMD

/// 空指令
const BYTE NULL_USERCMD      = 0;
/// 登陆指令
const BYTE LOGON_USERCMD    = 1;
/// 时间指令
const BYTE TIME_USERCMD      = 2;
/// 数据指令
const BYTE DATA_USERCMD      = 3;
/// 道具指令
const BYTE PROPERTY_USERCMD    = 4;
/// 地图指令
const BYTE MAPSCREEN_USERCMD    = 5;
/// 移动指令
const BYTE MOVE_USERCMD      = 6;
/// 建造指令
const BYTE BUILD_USERCMD    = 8;
/// 打造指令
const BYTE MAKEOBJECT_USERCMD    = 10;
/// 复活指令
const BYTE RELIVE_USERCMD    = 12;
/// 聊天指令
const BYTE CHAT_USERCMD      = 14;
/// 离开指令
const BYTE LEAVEONLINE_USERCMD    = 15;
/// 交易指令
const BYTE TRADE_USERCMD    = 17;
/// 魔法指令
const BYTE MAGIC_USERCMD    = 18;
/// 帮会指令
const BYTE UNION_USERCMD    = 21;
/// 国家指令
const BYTE COUNTRY_USERCMD    = 22;
/// 任务指令
const BYTE TASK_USERCMD      = 23;
/// 选择指令
const BYTE SELECT_USERCMD    = 24;
//  社会关系指令
const BYTE RELATION_USERCMD        = 25;
//  门派关系指令
const BYTE SCHOOL_USERCMD    = 26;
//  家族关系指令
const BYTE SEPT_USERCMD      = 27;
// 战斗指令
const BYTE DARE_USERCMD                 = 28;
// 宠物指令
const BYTE PET_USERCMD                  = 29;
// 获取服务器列表
const BYTE PING_USERCMD      = 30;
// 金币指令
const BYTE GOLD_USERCMD      = 31;
// 答题指令
const BYTE QUIZ_USERCMD      = 32;
// NPC争夺战指令
const BYTE NPCDARE_USERCMD    = 33;
// 与GM工具交互的指令
const BYTE GMTOOL_USERCMD    = 34;
// 邮件指令
const BYTE MAIL_USERCMD      = 35;
// 拍卖指令
const BYTE AUCTION_USERCMD    = 36;
// 卡通宠物指令
const BYTE CARTOON_USERCMD    = 37;
// 股票指令
const BYTE STOCK_SCENE_USERCMD    = 38;
const BYTE STOCK_BILL_USERCMD    = 39;
// 投票指令
const BYTE VOTE_USERCMD      = 40;
// 军队指令
const BYTE ARMY_USERCMD      = 41;
// 护宝任务指令
const BYTE GEM_USERCMD      = 42;
// 监狱系统指令
const BYTE PRISON_USERCMD    = 43;
// 礼官指令
const BYTE GIFT_USERCMD      = 44;
// 国家同盟指令
const BYTE ALLY_USERCMD      = 45;
// 小游戏指令
const BYTE MINIGAME_USERCMD    = 46;
// 推荐人系统指令
const BYTE RECOMMEND_USERCMD  = 47;
// 财产保护系统指令
const BYTE SAFETY_USERCMD    = 48;
//箱子指令
const BYTE SAFETY_COWBOX = 49;

//转生指令

const BYTE TURN_USERCMD = 50;

const BYTE HOTSPRING_USERCMD = 51;

const BYTE REMAKEOBJECT_USERCMD	= 52;

//训马指令 [sky]
const BYTE HORSETRAINING_USERCMD	= 53;

//自由加点指令 [sky]
const BYTE SURPLUS_ATTRIBUTE_USERCMD	= 54;

// sky 战场-副本-竞技场指令
const BYTE ARENA_USERCMD	= 55;

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 空指令定义开始
//////////////////////////////////////////////////////////////
const BYTE NULL_USERCMD_PARA = 0;
struct stNullUserCmd{
  stNullUserCmd()
  {
    dwTimestamp=0;
  }
  union{
    struct {
      BYTE  byCmd;
      BYTE  byParam;
    };
    struct {
      BYTE  byCmdType;
      BYTE  byParameterType;
    };
  };
  //BYTE  byCmdSequence;
  DWORD  dwTimestamp;
};
//////////////////////////////////////////////////////////////
// 空指令定义结束
//////////////////////////////////////////////////////////////

enum enumMapDataType{
  MAPDATATYPE_NPC,
  MAPDATATYPE_USER,
  MAPDATATYPE_BUILDING,
  MAPDATATYPE_ITEM,
  MAPDATATYPE_PET
};

struct MapData_ItemHeader {
  WORD size;// 数量
  BYTE type;// 类型  enumMapDataType
};

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 登陆指令定义开始
//////////////////////////////////////////////////////////////
struct stLogonUserCmd : public stNullUserCmd
{
  stLogonUserCmd()
  {
    byCmd = LOGON_USERCMD;
  }
};

/// 客户端验证版本
const BYTE USER_VERIFY_VER_PARA = 1;
const DWORD GAME_VERSION = 1999;
struct stUserVerifyVerCmd  : public stLogonUserCmd
{
  stUserVerifyVerCmd()
  {
    byParam = USER_VERIFY_VER_PARA;
    version = GAME_VERSION;
  }

  DWORD version;
};

/// 客户端登陆登陆服务器
const BYTE USER_REQUEST_LOGIN_PARA = 2;
struct stUserRequestLoginCmd : public stLogonUserCmd
{
  stUserRequestLoginCmd()
  {
    byParam = USER_REQUEST_LOGIN_PARA;
  }
  char pstrName[MAX_ACCNAMESIZE];    /**< 帐号 */
  char pstrPassword[MAX_PASSWORD];  /**< 用户密码 */
  WORD game;              /**< 游戏类型编号，目前一律添0 */
  WORD zone;              /**< 游戏区编号 */
  char jpegPassport[7];        /**< 图形验证码 */
};

enum{
  LOGIN_RETURN_UNKNOWN,   /// 未知错误
  LOGIN_RETURN_VERSIONERROR, /// 版本错误
  LOGIN_RETURN_UUID,     /// UUID登陆方式没有实现
  LOGIN_RETURN_DB,     /// 数据库出错
  LOGIN_RETURN_PASSWORDERROR,/// 帐号密码错误
  LOGIN_RETURN_CHANGEPASSWORD,/// 修改密码成功
  LOGIN_RETURN_IDINUSE,   /// ID正在被使用中
  LOGIN_RETURN_IDINCLOSE,   /// ID被封
  LOGIN_RETURN_GATEWAYNOTAVAILABLE,/// 网关服务器未开
  LOGIN_RETURN_USERMAX,   /// 用户满
  LOGIN_RETURN_ACCOUNTEXIST, /// 账号已经存在
  LOGON_RETURN_ACCOUNTSUCCESS,/// 注册账号成功

  LOGIN_RETURN_CHARNAMEREPEAT,/// 角色名称重复
  LOGIN_RETURN_USERDATANOEXIST,/// 用户档案不存在
  LOGIN_RETURN_USERNAMEREPEAT,/// 用户名重复
  LOGIN_RETURN_TIMEOUT,   /// 连接超时
  LOGIN_RETURN_PAYFAILED,   /// 计费失败
  LOGIN_RETURN_JPEG_PASSPORT, /// 图形验证码输入错误
  LOGIN_RETURN_LOCK,         /// 帐号被锁定
  LOGIN_RETURN_WAITACTIVE, /// 帐号待激活
  LOGIN_RETURN_NEWUSER_OLDZONE      ///新账号不允许登入旧的游戏区 
};
/// 登陆失败后返回的信息
const BYTE SERVER_RETURN_LOGIN_FAILED = 3;
struct stServerReturnLoginFailedCmd : public stLogonUserCmd
{
  stServerReturnLoginFailedCmd()
  {
    byParam = SERVER_RETURN_LOGIN_FAILED;
  }
  BYTE byReturnCode;      /**< 返回的子参数 */
} ;

/// 登陆成功，返回网关服务器地址端口以及密钥等信息
const BYTE SERVER_RETURN_LOGIN_OK = 4;
struct stServerReturnLoginSuccessCmd : public stLogonUserCmd 
{
  stServerReturnLoginSuccessCmd()
  {
    byParam = SERVER_RETURN_LOGIN_OK;
  }

  DWORD dwUserID;
  DWORD loginTempID;
  char pstrIP[MAX_IP_LENGTH];
  WORD wdPort;

  union{
    struct{
      BYTE randnum[58];
      BYTE keyOffset;  // 密匙在 key 中的偏移
    };
    BYTE key[256];  // 保存密匙，整个数组用随机数填充
  };
};

/// 客户登陆网关服务器发送账号和密码
const BYTE PASSWD_LOGON_USERCMD_PARA = 5;
struct stPasswdLogonUserCmd : public stLogonUserCmd
{
  stPasswdLogonUserCmd()
  {
    byParam = PASSWD_LOGON_USERCMD_PARA;
  }

  DWORD loginTempID;
  DWORD dwUserID;
  char pstrName[MAX_ACCNAMESIZE];    /**< 帐号 */
  char pstrPassword[MAX_PASSWORD];
};

/// 请求创建账号
const BYTE ACCOUNT_LOGON_USERCMD_PARA = 7;
struct stAccountLogonUserCmd : public stLogonUserCmd 
{
  stAccountLogonUserCmd()
  {
    byParam = ACCOUNT_LOGON_USERCMD_PARA;
  }

  char strName[MAX_ACCNAMESIZE];
  char strPassword[MAX_PASSWORD];
};

/// 请求更改密码
const BYTE PASSWORD_LOGON_USERCMD_PARA = 9;
  struct stPasswordLogonUserCmd : public stLogonUserCmd {
    stPasswordLogonUserCmd()
    {
      byParam = PASSWORD_LOGON_USERCMD_PARA;
    }

    char strName[MAX_ACCNAMESIZE];
    char strPassword[MAX_PASSWORD];
    char strNewPassword[MAX_PASSWORD];
  };

/// 请求返回选择人物界面
const BYTE BACKSELECT_USERCMD_PARA = 10;
struct stBackSelectUserCmd : public stLogonUserCmd
{
  stBackSelectUserCmd()
  {
    byParam = BACKSELECT_USERCMD_PARA;
  }
};

/// 发送图形验证码到客户端
const BYTE JPEG_PASSPORT_USERCMD_PARA = 11;
struct stJpegPassportUserCmd : public stLogonUserCmd
{
  stJpegPassportUserCmd()
  {
    byParam = JPEG_PASSPORT_USERCMD_PARA;
    size = 0;
  }
  WORD size;
  BYTE data[0];
};
// [ranqd] Add 服务器状态
enum SERVER_STATE 
{
	STATE_SERVICING	=	0, // 维护
	STATE_NOMARL	=	1, // 正常
	STATE_GOOD		=	2, // 良好
	STATE_BUSY		=	3, // 繁忙
	STATE_FULL		=	4, // 爆满
};
// [ranqd] Add 服务器类型
enum SERVER_TYPE
{
	TYPE_GENERAL		=	0, // 普通
	TYPE_PEACE		=	1,     // 和平
};

//发送国家信息
struct  Country_Info
{
  DWORD id;//国家id
  BYTE  enableRegister; //允许注册为1 不允许为0
  BYTE  enableLogin;    //允许登陆为1 不允许为0
  BYTE  Online_Statue;  // [ranqd] add 在线情况 参考 enum SERVER_STATE 
  BYTE  type;           // [ranqd] add 服务器类型 参考 enum SERVER_TYPE
  char pstrName[MAX_NAMESIZE + 1];//国家名称
  Country_Info()
  {
    enableRegister = 0;
    enableLogin = 0;
  }
};
const BYTE SERVER_RETURN_COUNTRY_INFO = 12;
struct stCountryInfoUserCmd : public stLogonUserCmd
{
  stCountryInfoUserCmd()
  {
    byParam = SERVER_RETURN_COUNTRY_INFO;
    size = 0;
  }
  WORD size;
  Country_Info countryinfo[0];
};
// [ranqd] add 用户选择服务器命令
const BYTE CLIENT_SELETCT_COUNTRY = 13;
struct stSelectCountryUserCmd : public stLogonUserCmd
{
	stSelectCountryUserCmd()
	{
		byParam = CLIENT_SELETCT_COUNTRY;
		id = 0;
	}
	DWORD id;  // 选择的国家id 
};
//////////////////////////////////////////////////////////////
// 登陆指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 时间指令定义开始
//////////////////////////////////////////////////////////////
struct stTimerUserCmd : public stNullUserCmd
{
  stTimerUserCmd()
  {
    byCmd = TIME_USERCMD;
  }
};

/// 网关向用户发送游戏时间
const BYTE GAMETIME_TIMER_USERCMD_PARA = 1;
struct stGameTimeTimerUserCmd : public stTimerUserCmd 
{
  stGameTimeTimerUserCmd()
  {
    byParam = GAMETIME_TIMER_USERCMD_PARA;
  }

  QWORD qwGameTime;      /**< 游戏时间 */
};

/// 网关向用户请求时间
const BYTE REQUESTUSERGAMETIME_TIMER_USERCMD_PARA = 2;
struct stRequestUserGameTimeTimerUserCmd : public stTimerUserCmd
{
  stRequestUserGameTimeTimerUserCmd()
  {
    byParam = REQUESTUSERGAMETIME_TIMER_USERCMD_PARA;
  }

};

/// 用户向网关发送当前游戏时间
const BYTE USERGAMETIME_TIMER_USERCMD_PARA  = 3;
struct stUserGameTimeTimerUserCmd : public stTimerUserCmd
{
  stUserGameTimeTimerUserCmd()
  {
    byParam = USERGAMETIME_TIMER_USERCMD_PARA;
  }

  DWORD dwUserTempID;      /**< 用户临时ID */
  QWORD qwGameTime;      /**< 用户游戏时间 */
};

/// 用户ping命令(服务器原样返回)
const BYTE PING_TIMER_USERCMD_PARA = 4;
struct stPingTimeTimerUserCmd : public stTimerUserCmd
{
  stPingTimeTimerUserCmd()
  {
    byParam = PING_TIMER_USERCMD_PARA;
  }

};
//////////////////////////////////////////////////////////////
/// 时间指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 数据指令定义开始
//////////////////////////////////////////////////////////////
/// 定义人物状态
enum {
  USTATE_DEATH    = 0,//  死亡
  USTATE_UNARM =1,// 缴械
  USTATE_SUNDERARMOR =2,//破甲
  USTATE_BRANDISH =3,//刀光剑影
  USTATE_IMPREGNABLE =4,//固若金汤
  USTATE_CELENRITY_CHOP =5,//大卸八块
  USTATE_PHYSICS_ECHO =6 ,//物理反射
  USTATE_MAGIC_ECHO =7,//魔法反射
  USTATE_FURY =8,//狂暴
  USTATE_CRACK =9,//地裂斩
  USTATE_BOUNCE =10,//撞击
  USTATE_SEVER_MUSCLE =11,//断筋
  USTATE_BELLOW =12,//狮子吼
  USTATE_HALE_AND_HEARTY =13,//宝刀不老
  USTATE_GALLOW =14,//破胆
  USTATE_TERRIFIC =15,//翻江倒海
  USTATE_SANGUINARY =16,//嗜血
  USTATE_OFFER =17,//献祭
  USTATE_BOMB =18,//火蛋
  USTATE_WINDMILL =19,//风火轮
  USTATE_BLAZE_SHIELD =20,//火盾
  USTATE_EMBLAZE =21,//点燃
  USTATE_WISDOM =22,//智慧祷言
  USTATE_ICY_WATER =23,//冰霜结界
  USTATE_FROST =24,//冰冻
  USTATE_DECELERATE =25,//冰减速
  USTATE_ICE_SHIELD =26,//冰盾
  USTATE_SPUNK =27,//精神祷言
  USTATE_REJUVENATION =28,//回春
  USTATE_MAGIC_SHIELD =29,//护盾
  USTATE_INVINCIBLE =30,//无敌
  USTATE_GROW_ON =31,//伤害加深
  USTATE_VAMPIRE =32,//吸血
  USTATE_DREAD =33,//恐惧
  USTATE_MUM =34,//沉默
  USTATE_WEAKNESS =35,//虚弱
  USTATE_PAIN =36,//痛苦
  USTATE_COMA =37,//昏迷
  USTATE_BANISH =38,//放逐
  USTATE_ENTHRALL_TOXICANT =39,//迷魂散
  USTATE_TOXICANT =40,//致伤毒药
  USTATE_DEADLINESS_TOXICANT =41,//致命毒药
  USTATE_ABLEPSIA =42,//石灰粉
  USTATE_LULL_TOXICANT =43,//麻痹毒药
  USTATE_INCISE =44,//切割
  USTATE_AT_FULL_SPLIT =45,//玩命
  USTATE_ALERTNESS =46,//机敏
  USTATE_SCOUR =47,//疾跑

  //sky 新增建筑类NPC的建造状态(建筑类NPC专用)
  NPCSTATE_MAKE = 100,

  //sky 保持兼容
  USTATE_WAR				 = 265,
  USTATE_HIDE				 = 266,
  USTATE_PK					 = 267,
  USTATE_GUARD				 = 268, //新人保护状态
  USTATE_TOGETHER_WITH_TIGER = 269,
  USTATE_TOGETHER_WITH_DRAGON = 270,
  USTATE_DAOJISHI      = 271,
  USTATE_RELIVEWEAK    = 272,
  USTATE_START_QUEST   = 273,
  USTATE_FINISH_QUEST  = 274,
  USTATE_DOING_QUEST   = 275,
  USTATE_SITDOWN	   = 276,	//坐下
  USTATE_PRIVATE_STORE = 277,	//摆摊
  USTATE_ULTRA_EQUIPMENT = 278,
  USTATE_TEAM_ATTACK_ONE_DIM = 279,
  USTATE_TEAM_ATTACK_FLOW_CLOUD = 280,
  USTATE_TEAM_ATTACK_BIRD_FLAG = 281,

  USTATE_EXP_125       = 283, //经验1.25倍率状态
  USTATE_EXP_150       = 284, //经验1.50倍率状态
  USTATE_EXP_175       = 285, //经验1.75倍率状态
  //sky 新增战斗状态
  USTATE_PVE	= 286,	//sky PVE状态
  USTATE_PVP	= 287,	//sky PVP状态
  USTATE_RIDE	= 288,	//sky 骑马状态
  USTATE_SOUL	= 289,	//sky 灵魂状态

  MAX_STATE = 320                         /// 最大状态数
};

/// 定义善恶度
enum
{
  GOODNESS_0    = -120 & 0x0000FFFF,//英雄
  GOODNESS_1    = -60 & 0x0000FFFF, //侠士
  GOODNESS_2_1  = 0,       //普通1
  GOODNESS_2_2  = 0xFF000000,   //普通2
  GOODNESS_3    = 60,       //歹徒
  GOODNESS_4    = 120,       //恶徒
  GOODNESS_5    = 180,       //恶魔
  GOODNESS_6    = 300,       //魔头
  GOODNESS_7    = 10000,     //叛国
  
  GOODNESS_ATT  = 0x00010000,   //主动伤害别人
  GOODNESS_DEF  = 0x00010000 << 1        //自卫方
};

///定义善恶度结束

/// 检查某个状态是否设置
inline bool isset_state(const BYTE *state,const int teststate)
{
  return 0 != (state[teststate / 8] & (0xff & (1 << (teststate % 8))));
}

/// 设置某个状态
inline void set_state(BYTE *state,const int teststate)
{
  state[teststate / 8] |= (0xff & (1 << (teststate % 8)));
}

/// 清除某个状态
inline void clear_state(BYTE *state,const int teststate)
{
  state[teststate / 8] &= (0xff & (~(1 << (teststate % 8))));
}

struct t_MapBuildingData{
  DWORD dwMapBuildingTempID;      /**< 建筑物的临时ID */
  DWORD dwBuildingDataID;        /**< 建筑物的数据ID */
  DWORD x;
  DWORD y;
  DWORD dwContract;          /**< 地契编号 */
  char pstrName[MAX_NAMESIZE + 1];    /**< 建筑物的名称 */
  char pstrUserName[MAX_NAMESIZE + 1];  /**< 建筑物的所有者名称 */
};

struct t_MapObjectData {
  DWORD dwMapObjectTempID;        /**< 物品的临时ID */
  DWORD dwObjectID;                       /**< 物品的数据ID */
  char pstrName[MAX_NAMESIZE + 1];      /**<  物品名 */
  DWORD x;
  DWORD y;
  DWORD wdNumber;                         /**< 数量 */
  WORD  wdLevel;                          /**< 等级 */
  BYTE upgrade;
  BYTE kind;
  DWORD dwOwner;
  //sky 物品拾取保护者的名字
  char	 strName[MAX_NAMESIZE+1];
};

//宠物的类型
enum petType
{
  PET_TYPE_NOTPET			= 0,//不是宠物
  PET_TYPE_RIDE				= 1,//坐骑
  PET_TYPE_PET				= 2,//宠物
  PET_TYPE_SUMMON			= 3,//召唤兽
  PET_TYPE_TOTEM			= 4,//图腾
  PET_TYPE_GUARDNPC			= 5,//要护卫的npc
  PET_TYPE_SEMI				= 6,//半宠物，跟主人同生同死，AI完全没关系
  PET_TYPE_CARTOON			= 7,//卡通宝宝
  PET_TYPE_TURRET			= 8	//sky 炮塔
};

struct t_NpcData {
	DWORD MaxHp;				//sky Npc最大HP
	DWORD NowHp;				//sky Npc当前HP
	DWORD dwMapNpcDataPosition;  /**< npc的数据位置 */
	DWORD dwNpcDataID;      /**< npc的数据ID */
	WORD  movespeed;    /// 移动速度

	BYTE byDirect;        /**< Npc的方向 */
	BYTE level;///等级
};
struct t_MapNpcData :public t_NpcData
{
  BYTE byState[(MAX_STATE + 7) / 8];      /**< Npc的状态 */
};
struct t_MapNpcDataState :public t_NpcData
{
  t_MapNpcDataState()
  {
    num=0;
  }
  BYTE num;     ///带状态的数量
  WORD state[0];    ///状态列表
};

struct t_MapPetData {
  DWORD tempID;//npc的临时ID

  char name[MAX_NAMESIZE + 1]; //npc的名称
  BYTE masterType;  ///主人的类型  0：玩家 1：npc
  DWORD masterID;  ///主人的id -1：没有主人
  char masterName[MAX_NAMESIZE + 1];///主任的名字
  BYTE pet_type;//宠物类型
};

struct t_MapUserSculpt{
  DWORD dwHorseID;          /// 马牌编号
  DWORD dwHairID;            /// 头发类型
  DWORD dwBodyID;            /// 身体物品ID
  DWORD dwLeftHandID;          /// 左手物品ID
  DWORD dwRightHandID;        /// 右手物品ID
};

//队伍标志
enum{
  TEAD_STATE_NONE,
  TEAD_STATE_MEMBER,
  TEAM_STATE_LEADER,
};

/// 用户本身的数据，不包括状态
struct t_UserData
{
  DWORD dwUserTempID;          //// 用户临时ID

  char  name[MAX_NAMESIZE + 1];    /// 角色名称
  WORD  type;              /// 职业类型
  //WORD  sex;              /// 性别
  WORD  face;              /// 头象
  DWORD goodness;            /// 善恶度

  t_MapUserSculpt sculpt;
  DWORD dwHairRGB;          /// 头发颜色0xffrrggbb
  DWORD dwBodyColorSystem;      /// 衣服系统颜色0xffrrggbb
  DWORD dwBodyColorCustom;      /// 衣服定制颜色0xffrrggbb
  DWORD dwLeftWeaponColor;      /// 左手武器颜色0xffrrggbb
  DWORD dwRightWeaponColor;      /// 右手武器颜色0xffrrggbb
  WORD  attackspeed;          /// 攻击速度
  WORD  movespeed;          /// 移动速度
  BYTE country;            /// 国家
  DWORD dwChangeFaceID;        //易容后的NPC的类型ID
  //BYTE live_skills[6];         //生活技能等级
  BYTE level;              //Level : 1(<10)   11(>=10)
  DWORD exploit;        // 功勋值
  DWORD useJob;        // sky 角色职业
  
  DWORD dwUnionID;      // 帮会ID
  DWORD dwSeptID;        // 家族ID
  
  char  caption[MAX_NAMESIZE + 1];    // 顶部头衔（某城城主或某国国王）
  DWORD dwTeamState;          // 队伍状态
  DWORD dwArmyState;      //1为队长，2为将军,0为未加入军队
};

struct t_MapUserData : public t_UserData 
{
  BYTE state[(MAX_STATE + 7) / 8];  /// 角色状态
};
struct t_MapUserDataState : public t_UserData 
{
  t_MapUserDataState()
  {
    num=0;
  }
  BYTE num;     ///带状态的数量
  WORD state[0];    ///状态列表
};

struct t_MainUserData 
{
  DWORD dwUserTempID;        /// 用户临时ID
  WORD  level;          /// 角色等级
  DWORD hp;            /// 当前生命值
  DWORD maxhp;          /// 最大生命值
  DWORD resumehp;          /// 生命值恢复
  DWORD mp;            /// 当前法术值
  DWORD maxmp;          /// 最大法术值
  DWORD resumemp;          /// 法术值恢复
  DWORD sp;            /// 当前体力值
  DWORD maxsp;          /// 最大体力值
  DWORD resumesp;          /// 体力值恢复
  DWORD pdamage;          /// 最小物理攻击力
  DWORD maxpdamage;        /// 最大物理攻击力
  DWORD mdamage;          /// 最小法术攻击力
  DWORD maxmdamage;        /// 最大法术攻击力
  DWORD pdefence;          /// 物理防御力
  DWORD mdefence;          /// 法术防御力
  QWORD exp;            /// 当前经验值
  QWORD nextexp;          /// 升级经验值
  WORD  attackrating;        /// 攻击命中
  WORD  attackdodge;        /// 攻击躲避
  WORD  bang;            /// 重击
  WORD  charm;          /// 魅力值
  DWORD  zs;             /// 转身
  union {
    struct {
      WORD wdCon;  //体质
      WORD wdStr;  //体力
      WORD wdDex;  //敏捷
      WORD wdInt;  //智力
      WORD wdMen;  //精神
    };
    WORD wdProperty[5];
  };
  WORD  skillPoint;                   /// 技能点数
  WORD  points;                       /// 点数
  DWORD country;            /// 国家
  WORD  pkmode;                       /// pk模式


  DWORD stdpdamage;          /// 标准物理攻击力
  DWORD stdmdamage;          /// 标准法术攻击力
  DWORD stdpdefence;          /// 标准物理防御力
  DWORD stdmdefence;          /// 标准法术防御力
  WORD  stdbang;            /// 标准重击率
  union {
    struct {
      WORD wdStdCon;  //体质
      WORD wdStdStr;  //体力
      WORD wdStdDex;  //敏捷
      WORD wdStdInt;  //智力
      WORD wdStdMen;  //精神
    };
    WORD wdStdProperty[5];
  };
  WORD wdTire; /// 疲劳状态 0为非 1为疲劳
  DWORD fivetype;  ///五行类型
  DWORD fivepoint;///五行点数
  DWORD honor;///荣誉值
  DWORD maxhonor;///最大荣誉值
  DWORD gold;  ///金币数
  DWORD ticket; //点券数
  DWORD bitmask;          /// 角色掩码
};

struct stDataUserCmd : public stNullUserCmd
{
  stDataUserCmd()
  {
    byCmd = DATA_USERCMD;
  }
};

/// 主用户数据
const BYTE MAIN_USER_DATA_USERCMD_PARA = 1;
  struct stMainUserDataUserCmd : public stDataUserCmd {
    stMainUserDataUserCmd()
    {
      byParam = MAIN_USER_DATA_USERCMD_PARA;
    }

    t_MainUserData data;
  };
/*
enum {
  DECTYPE_POWER, /// 体力
  DECTYPE_STRENGTH,/// 力量
  DECTYPE_INTELLECTUALITY,/// 智力
  DECTYPE_CORPOREITY,/// 体质
  DECTYPE_DEXTERITY      /// 敏捷
};
/// 减少剩余点数，增加到体力等中
const BYTE DECREMAINDER_DATA_USERCMD_PARA = 2;
  struct stDecRemainderDataUserCmd : public stDataUserCmd{
    stDecRemainderDataUserCmd()
    {
      byParam = DECREMAINDER_DATA_USERCMD_PARA;
    }

    BYTE byDecType;        **< 加点类型 *
  };

*/

/// 设置用户生命和魔法
const BYTE SETHPANDMP_DATA_USERCMD_PARA = 3;
  struct stSetHPAndMPDataUserCmd : public stDataUserCmd{
    stSetHPAndMPDataUserCmd()
    {
      byParam = SETHPANDMP_DATA_USERCMD_PARA;
    }

    DWORD dwHP;          /**< HP */
    DWORD dwMP;          /**< MP */
    //DWORD dwSP;          /**< SP */
  };

enum {
  MAP_SETTING_RIDE  = 0x00000001,/// 大陆可以骑马
  MAP_SETTING_WEATHER  = 0x00000002  /// 大陆有雨雪天气变化
};
/// 地图信息
const BYTE MAPSCREENSIZE_DATA_USERCMD_PARA = 28;
  struct stMapScreenSizeDataUserCmd : public stDataUserCmd{
    stMapScreenSizeDataUserCmd()
    {
      byParam = MAPSCREENSIZE_DATA_USERCMD_PARA;
    }

    DWORD width;    /**< 场景宽 */
    DWORD height;    /**< 场景高 */
    char pstrMapName[MAX_NAMESIZE + 1];  /**< 大陆名称 */
    char pstrFilename[MAX_NAMESIZE + 1];  /**< 文件名称 */
    DWORD setting;        /**< 大陆标志 */
    DWORD rgb;          /**< 颜色标志0x00rrggbb */
    char pstrGroupName[MAX_NAMESIZE + 1];  /**< 服务器组名称 */
    char pstrCountryName[MAX_NAMESIZE + 1];  /**< 国家名称 */
    char pstrCityName[MAX_NAMESIZE + 1];  /**< 城市名称 */
    int mainRoleX;  
    int mainRoleY;
    short npc_count;
    struct {
      DWORD id,x,y;
    } npc_list[0];
  };

//客户端加载地图完成
const BYTE LOADMAPOK_DATA_USERCMD_PARA = 29;
  struct stLoadMapOKDataUserCmd : public stDataUserCmd{
    stLoadMapOKDataUserCmd()
    {
      byParam = LOADMAPOK_DATA_USERCMD_PARA;
    }
  };

/// 角色的等级排名
const BYTE LEVELDEGREE_DATA_USERCMD_PARA = 30;
  struct stLevelDegreeDataUserCmd : public stDataUserCmd{
    stLevelDegreeDataUserCmd()
    {
      byParam = LEVELDEGREE_DATA_USERCMD_PARA;
    }
    WORD degree; // 1-2000名
  };

/// 发送特征码文件
const BYTE STAMP_DATA_USERCMD_PARA = 51;
struct stStampDataUserCmd : public stDataUserCmd
{
  bool check;//是否进行外挂检测
  DWORD size;
  BYTE bin[0];//特征码文件
  stStampDataUserCmd()
  {
    byParam = STAMP_DATA_USERCMD_PARA;

    check = false;
    size = 0;
  }
};

/// 客户端进行外挂检测
const BYTE STAMP_CHECK_USERCMD_PARA = 52;
struct stStampCheckUserCmd : public stDataUserCmd
{
  DWORD flag;//0 关; 1 开
  stStampCheckUserCmd()
  {
    byParam = STAMP_CHECK_USERCMD_PARA;

    flag = 0;
  }
};

/// 发送当前合并版本号
const BYTE MERGE_VERSION_CHECK_USERCMD_PARA = 53;
struct stMergeVersionCheckUserCmd : public stDataUserCmd
{
  stMergeVersionCheckUserCmd()
  {
    byParam = MERGE_VERSION_CHECK_USERCMD_PARA;
    dwMergeVersion = 0;
  }

  DWORD dwMergeVersion;
};

/// 发送初始化信息结束
const BYTE ENDOFINITDATA_DATA_USERCMD_PARA = 255;
  struct stEndOfInitDataDataUserCmd : public stDataUserCmd{
    stEndOfInitDataDataUserCmd()
    {
      byParam = ENDOFINITDATA_DATA_USERCMD_PARA;
    }
  };

//////////////////////////////////////////////////////////////
/// 数据指令定义完成
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 地图数据指令定义开始
//////////////////////////////////////////////////////////////
  struct stMapScreenUserCmd : public stNullUserCmd{
    stMapScreenUserCmd()
    {
      byCmd = MAPSCREEN_USERCMD;
    }
  };


/// 地图上增加人物
const BYTE ADDUSER_MAPSCREEN_USERCMD_PARA = 10;
  struct stAddUserMapScreenUserCmd : public stMapScreenUserCmd {
    stAddUserMapScreenUserCmd()
    {
      byParam = ADDUSER_MAPSCREEN_USERCMD_PARA;
    }
    t_MapUserData data;
  };

/// 地图上面删除人物
const BYTE REMOVEUSER_MAPSCREEN_USERCMD_PARA = 11;
  struct stRemoveUserMapScreenUserCmd : public stMapScreenUserCmd{
    stRemoveUserMapScreenUserCmd()
    {
      byParam = REMOVEUSER_MAPSCREEN_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */
  };

/// 用户请求其他用户数据
const BYTE REQUESTUSERDATA_MAPSCREEN_USERCMD_PARA = 12;
  struct stRequestUserDataMapScreenUserCmd : public stMapScreenUserCmd{
    stRequestUserDataMapScreenUserCmd()
    {
      byParam = REQUESTUSERDATA_MAPSCREEN_USERCMD_PARA;
    }

    WORD size;
    DWORD dwUserTempID[0];  //临时编号列表(DWORD)
  };

/// 用户骑马
const BYTE RIDE_MAPSCREEN_USERCMD_PARA = 13;
struct stRideMapScreenUserCmd : public stMapScreenUserCmd
{
  stRideMapScreenUserCmd()
  {
    byParam = RIDE_MAPSCREEN_USERCMD_PARA;
  }

  DWORD dwUserTempID;      /**< 用户临时ID */
  BYTE bySwitch;        /**< 骑马开关：１是骑马，０是下马 */
};

/// 刷新角色状态
const BYTE REFRESHSTATE_MAPSCREEN_USERCMD_PARA = 14;
struct stRefreshStateMapScreenUserCmd : public stMapScreenUserCmd{
  stRefreshStateMapScreenUserCmd()
  {
    byParam = REFRESHSTATE_MAPSCREEN_USERCMD_PARA;
    bzero(state,sizeof(state));
  }
  DWORD dwUserTempID;      /**< 用户临时ID */
  BYTE state[(MAX_STATE + 7) / 8];  /// 角色状态
  
};

/// 定义物品动作类型
enum{
    OBJECTACTION_DROP,/// 掉落物品
      OBJECTACTION_UPDATE,/// 更新物品数据
};
/// 在地图上增加物品
const BYTE ADDMAPOBJECT_MAPSCREEN_USERCMD_PARA = 20;
  struct stAddMapObjectMapScreenUserCmd  : public stMapScreenUserCmd{
    stAddMapObjectMapScreenUserCmd()
    {
      byParam = ADDMAPOBJECT_MAPSCREEN_USERCMD_PARA;
      bzero(&data,sizeof(data));
    }
    BYTE  action;
    t_MapObjectData data;
  };

/// 在地图上删除物品
const BYTE REMOVEMAPOBJECT_MAPSCREEN_USERCMD_PARA = 21;
  struct stRemoveMapObjectMapScreenUserCmd  : public stMapScreenUserCmd{
    stRemoveMapObjectMapScreenUserCmd()
    {
      byParam = REMOVEMAPOBJECT_MAPSCREEN_USERCMD_PARA;
    }
    DWORD dwMapObjectTempID;  /**< 物品的临时ID */
  };

/// 在地图上增加建筑物
const BYTE ADDMAPBUILDING_MAPSCREEN_USERCMD_PARA = 30;
  struct stAddMapBuildingMapScreenUserCmd : public stMapScreenUserCmd{
    stAddMapBuildingMapScreenUserCmd()
    {
      byParam = ADDMAPBUILDING_MAPSCREEN_USERCMD_PARA;
    }

    t_MapBuildingData data;
  };


/// 在地图上删除建筑物
const BYTE REMOVEMAPBUILDING_MAPSCREEN_USERCMD_PARA = 31;
  struct stRemoveMapBuildingMapScreenUserCmd : public stMapScreenUserCmd{
    stRemoveMapBuildingMapScreenUserCmd()
    {
      byParam = REMOVEMAPBUILDING_MAPSCREEN_USERCMD_PARA;
    }

    DWORD dwMapBuildingTempID;  /**< 建筑物的临时ID */
  };

///人物使用易容术
const BYTE CHANGEFACE_MAPSCREEN_USERCMD_PARA = 32;
  struct stChangeFaceMapScreenUserCmd : public stMapScreenUserCmd{
    stChangeFaceMapScreenUserCmd()
    {
      byParam = CHANGEFACE_MAPSCREEN_USERCMD_PARA;
    }

    DWORD  dwUserTempID;    //用户临时ID
        DWORD  dwChangeFaceID;    //易容后的NPC的类型ID
  };

/// 在地图上增加NPC
const BYTE ADDMAPNPC_MAPSCREEN_USERCMD_PARA = 50;
  struct stAddMapNpcMapScreenUserCmd : public stMapScreenUserCmd{
    stAddMapNpcMapScreenUserCmd()
    {
      byParam = ADDMAPNPC_MAPSCREEN_USERCMD_PARA;
    }

    t_MapNpcData data;
  };

/// 在地图上删除NPC
const BYTE REMOVEMAPNPC_MAPSCREEN_USERCMD_PARA = 51;
  struct stRemoveMapNpcMapScreenUserCmd : public stMapScreenUserCmd{
    stRemoveMapNpcMapScreenUserCmd()
    {
      byParam = REMOVEMAPNPC_MAPSCREEN_USERCMD_PARA;
    }
    DWORD dwMapNpcDataPosition;  /**< npc的数据位置 */
  };

/// 请求Npc数据
const BYTE REQUESTMAPNPCDATA_MAPSCREEN_USERCMD_PARA = 52;
  struct stRequestMapNpcDataMapScreenUserCmd : public stMapScreenUserCmd{
    stRequestMapNpcDataMapScreenUserCmd()
    {
      byParam = REQUESTMAPNPCDATA_MAPSCREEN_USERCMD_PARA;
    }

    WORD size;
    DWORD dwNpcTempID[0];  //临时编号列表(DWORD)
  };

/// Npc血槽
const BYTE NPCHP_MAPSCREEN_USERCMD_PARA = 53;
  struct stNPCHPMapScreenUserCmd : public stMapScreenUserCmd{
    stNPCHPMapScreenUserCmd()
    {
      byParam = NPCHP_MAPSCREEN_USERCMD_PARA;
    }
//BEGIN_MUTABLE_VARS
    DWORD dwMapNpcDataPosition;  /**< npc的数据位置 */
    DWORD dwHP;          /**< HP */
    DWORD dwMaxHP;        /**< MaxHP */
//END_MUTABLE_VARS
  };

// NPC 人物 位置信息
struct stNpcPosition{
  DWORD dwTempID;        //目标编号
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
};

// NPC 人物 TEMPID信息
struct stNpcTempID{
  DWORD dwTempID;        //目标编号
};

/// 对9屏用户和NPC
const BYTE ALL_MAPSCREEN_USERCMD_PARA = 54;
  struct stAllMapScreenUserCmd : public stMapScreenUserCmd{
    stAllMapScreenUserCmd()
    {
      byParam = ALL_MAPSCREEN_USERCMD_PARA;
    }

    MapData_ItemHeader mdih;
    stNpcTempID psi[0];
  };

struct t_MapUserDataPos :public t_MapUserData
{
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
};
struct t_MapUserDataPosState :public t_UserData
{
/*
  t_MapUserDataPosState()
  {
    num=0;
  } 
// */
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
  BYTE num;     ///带状态的数量
  WORD state[1];    ///状态列表
};
struct t_MapNpcDataPos :public t_MapNpcData
{
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
};
struct t_MapNpcDataPosState :public t_NpcData
{
/*
  t_MapNpcDataPosState()
  {
    num=0;
  } 
// */
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
  BYTE num;     ///带状态的数量
  WORD state[1];    ///状态列表
};
struct t_MapBuildingDataPos :public t_MapBuildingData
{
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
};

// 地图数据打包发送
const BYTE MAPDATA_MAPSCREEN_USERCMD_PARA = 55;
  struct stMapDataMapScreenUserCmd : public stMapScreenUserCmd{
    stMapDataMapScreenUserCmd()
    {
      byParam = MAPDATA_MAPSCREEN_USERCMD_PARA;
    }

    MapData_ItemHeader mdih;
    union
    {
      t_MapUserDataPos mud[1];
      t_MapNpcDataPos mnd[1];
      t_MapBuildingDataPos mbd[1];
      t_MapPetData mpd[1];
    };
  };

#define SELECTED_HPMP_PROPERTY_USERCMD_PARA 56//通知选择自己的玩家hp和mp的变化
struct stRTSelectedHpMpPropertyUserCmd : public stMapScreenUserCmd
{
  stRTSelectedHpMpPropertyUserCmd()
  {
    byParam = SELECTED_HPMP_PROPERTY_USERCMD_PARA;
  }
  BYTE byType;//enumMapDataType
//BEGIN_MUTABLE_VARS
  DWORD dwTempID;//临时编号
  DWORD dwHP;//当前血
  DWORD dwMaxHp;//最大hp
  DWORD dwMP;//当前mp
  DWORD dwMaxMp;//最大mp
//END_MUTABLE_VARS  
};
/// sky 修改为跟改地图上物品保护(消息不再是只删除拉有可能只是要跟改保护对象)
const BYTE CLEAR_OBJECTOWNER_MAPSCREEN_USERCMD_PARA = 58;
struct stClearObjectOwnerMapScreenUserCmd  : public stMapScreenUserCmd{
	stClearObjectOwnerMapScreenUserCmd()
	{
		byParam = CLEAR_OBJECTOWNER_MAPSCREEN_USERCMD_PARA;
		tempid = 0;  //sky为0的时候就是要删除这个物品的保护
		strName[0] = 0;
	}
	DWORD dwMapObjectTempID;  /**< 物品的临时ID */
	DWORD tempid;
	char  strName[MAX_NAMESIZE+1];
};
/// 在地图上增加NPC和坐标
const BYTE ADDMAPNPC_AND_POS_MAPSCREEN_USERCMD_PARA = 59;
struct stAddMapNpcAndPosMapScreenUserCmd : public stMapScreenUserCmd{
	stAddMapNpcAndPosMapScreenUserCmd()
	{
		byParam = ADDMAPNPC_AND_POS_MAPSCREEN_USERCMD_PARA;
	}

	t_MapNpcDataPos data;
};

/// 地图上增加人物和坐标
const BYTE ADDUSER_AND_POS_MAPSCREEN_USERCMD_PARA = 60;
  struct stAddUserAndPosMapScreenUserCmd : public stMapScreenUserCmd {
    stAddUserAndPosMapScreenUserCmd()
    {
      byParam = ADDUSER_AND_POS_MAPSCREEN_USERCMD_PARA;
    }
    t_MapUserDataPos data;
  };
/// 批量删除NPC指令
const BYTE BATCHREMOVENPC_MAPSCREEN_USERCMD_PARA = 61;
  struct stBatchRemoveNpcMapScreenUserCmd : public stMapScreenUserCmd {
    stBatchRemoveNpcMapScreenUserCmd()
    {       
      byParam = BATCHREMOVENPC_MAPSCREEN_USERCMD_PARA;
    }
    WORD  num;
    DWORD   id[0];
  };

/// 批量删除USER指令
const BYTE BATCHREMOVEUSER_MAPSCREEN_USERCMD_PARA = 62;
  struct stBatchRemoveUserMapScreenUserCmd : public stMapScreenUserCmd {
    stBatchRemoveUserMapScreenUserCmd()
    {       
      byParam = BATCHREMOVEUSER_MAPSCREEN_USERCMD_PARA;
    }
    WORD  num;
    DWORD   id[0];
  };
/// 设置角色状态
const BYTE SETSTATE_MAPSCREEN_USERCMD_PARA = 63;
struct stSetStateMapScreenUserCmd : public stMapScreenUserCmd{
  stSetStateMapScreenUserCmd()
  {
    byParam = SETSTATE_MAPSCREEN_USERCMD_PARA;
  }
  BYTE  type;    /**<类型 enumMapDataType*/
  DWORD  dwTempID;      /**< 用户临时ID */
  WORD  wdState;  /// 需要设置的状态
};
/// 取消角色状态
const BYTE CLEARSTATE_MAPSCREEN_USERCMD_PARA = 64;
struct stClearStateMapScreenUserCmd : public stMapScreenUserCmd{
  stClearStateMapScreenUserCmd()
  {
    byParam = CLEARSTATE_MAPSCREEN_USERCMD_PARA;
  }
  BYTE  type;    /**<类型 enumMapDataType*/
  DWORD  dwTempID;      /**< 用户临时ID */
  WORD  wdState;  /// 需要取消的状态
};
/// 在地图上增加Npc和宠物数据
const BYTE ADDMAPNPCPET_MAPSCREEN_USERCMD_PARA = 65;
  struct stAddMapNpcPetMapScreenUserCmd : public stMapScreenUserCmd{
    stAddMapNpcPetMapScreenUserCmd()
    {
      byParam = ADDMAPNPCPET_MAPSCREEN_USERCMD_PARA;
    }

    t_MapNpcDataPos data;
    t_MapPetData pet; 
  };
/// 在地图上增加宠物数据
const BYTE ADDMAPPET_MAPSCREEN_USERCMD_PARA = 66;
  struct stAddMapPetMapScreenUserCmd : public stMapScreenUserCmd{
    stAddMapPetMapScreenUserCmd()
    {
      byParam = ADDMAPPET_MAPSCREEN_USERCMD_PARA;
    }

    t_MapPetData pet; 
  };
/// 设置角色善恶值
const BYTE GOODNESS_MAPSCREEN_USERCMD_PARA = 67;
struct stGoodnessStateMapScreenUserCmd : public stMapScreenUserCmd{
  stGoodnessStateMapScreenUserCmd()
  {
    byParam = GOODNESS_MAPSCREEN_USERCMD_PARA;
  }
  DWORD  dwTempID;      /**< 用户临时ID */
  DWORD  dwGoodness;  /// 善恶值
};
/// 地图上增加人物
const BYTE ADDUSER_MAPSCREEN_STATE_USERCMD_PARA = 68;
  struct stAddUserMapScreenStateUserCmd : public stMapScreenUserCmd {
    stAddUserMapScreenStateUserCmd()
    {
      byParam = ADDUSER_MAPSCREEN_STATE_USERCMD_PARA;
    }
    t_MapUserDataState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };
/// 在地图上增加NPC
const BYTE ADDMAPNPC_MAPSCREEN_STATE_USERCMD_PARA = 69;
  struct stAddMapNpcMapScreenStateUserCmd : public stMapScreenUserCmd{
    stAddMapNpcMapScreenStateUserCmd()
    {
      byParam = ADDMAPNPC_MAPSCREEN_STATE_USERCMD_PARA;
    }
    t_MapNpcDataState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };
/// 地图上增加人物和坐标
const BYTE ADDUSER_AND_POS_MAPSCREEN_STATE_USERCMD_PARA = 70;
  struct stAddUserAndPosMapScreenStateUserCmd : public stMapScreenUserCmd {
    stAddUserAndPosMapScreenStateUserCmd()
    {
      byParam = ADDUSER_AND_POS_MAPSCREEN_STATE_USERCMD_PARA;
    }
    t_MapUserDataPosState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };
/// 在地图上增加NPC和坐标
const BYTE ADDMAPNPC_AND_POS_MAPSCREEN_STATE_USERCMD_PARA = 71;
  struct stAddMapNpcAndPosMapScreenStateUserCmd : public stMapScreenUserCmd{
    stAddMapNpcAndPosMapScreenStateUserCmd()
    {
      byParam = ADDMAPNPC_AND_POS_MAPSCREEN_STATE_USERCMD_PARA;
    }
    t_MapNpcDataPosState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };
/// 在地图上增加Npc和宠物数据
const BYTE ADDMAPNPCPET_MAPSCREEN_STATE_USERCMD_PARA = 72;
  struct stAddMapNpcPetMapScreenStateUserCmd : public stMapScreenUserCmd{
    stAddMapNpcPetMapScreenStateUserCmd()
    {
      byParam = ADDMAPNPCPET_MAPSCREEN_STATE_USERCMD_PARA;
    }

    t_MapPetData pet; 
    t_MapNpcDataPosState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };


// 地图数据打包发送
const BYTE MAPDATA_MAPSCREEN_STATE_USERCMD_PARA = 73;
  struct stMapDataMapScreenStateUserCmd : public stMapScreenUserCmd{
    stMapDataMapScreenStateUserCmd()
    {
      byParam = MAPDATA_MAPSCREEN_STATE_USERCMD_PARA;
    }

    MapData_ItemHeader mdih;
    union
    {
      t_MapUserDataPosState mud[1];
      t_MapNpcDataPosState mnd[1];
      t_MapBuildingDataPos mbd[1];
      t_MapPetData mpd[1];
    };
  };


/*
/// 刷新宠物信息
const BYTE ADD_PET_MAPSCREEN_USERCMD_PARA = 61;
  struct stAddPetMapScreenUserCmd : public stMapScreenUserCmd {
    stAddPetMapScreenUserCmd()
    {
      byParam = ADD_PET_MAPSCREEN_USERCMD_PARA;
    }
    BYTE size;
    t_MapPetData data[0];
  };
  */
//////////////////////////////////////////////////////////////
/// 地图数据指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 魔法指令定义开始
//////////////////////////////////////////////////////////////
  struct stMagicUserCmd : public stNullUserCmd{
    stMagicUserCmd()
    {
      byCmd = MAGIC_USERCMD;
    }
  };

/// 定义攻击类型
enum ATTACKTYPE{
  ATTACKTYPE_U2U,/// 用户攻击用户
  ATTACKTYPE_U2N,/// 用户攻击Npc
  ATTACKTYPE_N2U,/// Npc攻击用户
  ATTACKTYPE_U2B,/// 用户攻击建筑
  ATTACKTYPE_U2P,/// 用户攻击点
  ATTACKTYPE_N2N  /// Npc攻击Npc
};

enum AniTypeEnum
{
Ani_Null = 0,

  Ani_Wait,Ani_Stand = Ani_Wait,// 站立
  Ani_Walk,     // 走
  Ani_Run,     // 跑

  Ani_Attack,     // 攻击
  Ani_Attack2,   // 攻击2
  Ani_Attack3,   // 攻击3

  Ani_Magic,     // 魔法攻击
  Ani_Magic2,     // 魔法攻击2
  Ani_Magic3,     // 魔法攻击3

  Ani_Bow,     // 射箭
  Ani_Bow2,     // 努攻击

  Ani_Hurt,     // 受伤(被击)
  Ani_Die,     // 死亡

  Ani_Sit,     // 打坐

  Ani_Ride_Wait,   // 骑马站立
  Ani_Ride_Walk,   // 骑马走
  Ani_Ride_Run,   // 骑马跑

  Ani_Ride_Attack, // 骑马攻击
  Ani_Ride_Magic,   // 骑马施法

  Ani_Ride_Hurt,   // 受伤(被击)
  Ani_Ride_Die,   // 骑马死亡

  Ani_Appear,     // 出现(重生)

  Ani_Attack_Stand, // 攻击站立
  Ani_Attack2_Stand, // 攻击2站立
  Ani_Attack3_Stand, // 攻击2站立

  Ani_Magic_Stand, // 魔法攻击站立
  Ani_Magic2_Stand, // 魔法2攻击站立
  Ani_Magic3_Stand, // 魔法3攻击站立

  Ani_Bow_Stand,   // 弓箭攻击站立
  Ani_Bow2_Stand,   // 努攻击站立

  Ani_Ride_Attack_Stand,// 骑马攻击站立
  Ani_Ride_Magic_Stand,// 骑马施法站立

  Ani_Back,     // 后退
  Ani_Ride_Back,   // 骑马后退

  Ani_Ride_Bow,   // 骑马射箭
  Ani_Ride_Bow_Stand, // 骑马射箭站立

  Ani_Fly_Walk,   // 飞行慢速
  Ani_Fly_Run,   // 飞行快速

  Ani_Fly_Hurt,   // 飞行被击
  Ani_Fly_Die,   // 飞行死亡

  Ani_Gather,     // 采药

  Ani_FirstRun,   // 第一次走

  Ani_Idle0,
  Ani_Idle1,
  Ani_Idle2,
  Ani_Idle3,

  Ani_Gather_Stand,
  Ani_OpenBox_Stand,
  Ani_Num
};

/// 攻击指令
const BYTE MAGIC_USERCMD_PARA = 5;
struct stAttackMagicUserCmd : public stMagicUserCmd{

  stAttackMagicUserCmd()
  {
    byParam = MAGIC_USERCMD_PARA;
  }

//BEGIN_MUTABLE_VARS
  DWORD dwUserTempID;      /**< 攻击临时编号 */
  DWORD dwDefenceTempID;    /**< 防御临时编号 */

  WORD wdMagicType;      /**< 魔法编号 */

  WORD xDes;          /**< 目标点 */
  WORD yDes;          /**< 目标点 */
//END_MUTABLE_VARS  
  
  BYTE byDirect;        /**< 攻击方向 */
  BYTE byAttackType;      /**< 攻击类型：ATTACKTYPE_U2U,ATTACKTYPE_U2N,ATTACKTYPE_N2U */
  BYTE byAction;        // 攻击动作  AniTypeEnum ( Ani_Null 为不确定的，由客户端确定 )
  DWORD dwTempIDList[1];    // 攻击目标列表
};

enum {
  RTMAGIC_FAILURE,/// 攻击失败
  RTMAGIC_DUCK,/// 防御闪避
  RTMAGIC_FREEZE,/// 冰冻
  RTMAGIC_SPEEDUP,/// 加速
  RTMAGIC_POISON,/// 中毒
  RTMAGIC_PLAGUE,/// 瘟疫
  RTMAGIC_LANDIFICATION,/// 石化
  RTMAGIC_VAMPIRE,/// 吸血
  RTMAGIC_VAMPIREMAGIC,/// 吸魔
  RTMAGIC_HIDE,/// 隐身
  RTMAGIC_BLANKSCREEN,/// 黑屏
  RTMAGIC_SUCCESS,/// 攻击成功
  RTMAGIC_ATTACKED,/// 被击
  RTMAGIC_DEFENCE      /// 格挡
};

/// 攻击返回给自己
const BYTE RTMAGIC_USERCMD_PARA = 6;
struct stRTMagicUserCmd : public stMagicUserCmd{

  stRTMagicUserCmd()
  {
    byParam = RTMAGIC_USERCMD_PARA;
  }

  DWORD dwUserTempID;      /**< 目标临时编号 */
  BYTE byTarget;        /**< 目标类型：enumMapDataType */
  BYTE byRetcode;        /**< 返回代码：RTMAGIC_SUCCESS,RTMAGIC_FAILURE... */
  BYTE byDirect;        /**< 方向 */
  BYTE bySrc;          /**< 攻击者类型：enumMapDataType */

  DWORD dwSrcTempID;      /**< 攻击者临时编号 */

  DWORD dwHP;          // 当前血
  SDWORD sdwHP;          /**< 扣血 */
  BYTE byLuck;        //幸运，为1表示这是幸运攻击，为0表示普通攻击结果
};

enum enumPopEffect
{
  POP_HP,
  POP_MP,
  POP_NUM,
};

/// 返回目标坐标伤血通知
const BYTE OBJECT_HPMP_POP_PARA = 11;
struct stObjectHpMpPopUserCmd : public stMagicUserCmd{

  stObjectHpMpPopUserCmd()
  {
    byParam = OBJECT_HPMP_POP_PARA;
  }

  DWORD dwUserTempID;      /**< 目标临时编号 */
  BYTE byTarget;        /**< 目标类型：enumMapDataType */

  int vChange;        /**< >0 :加    <0 :扣*/
  enumPopEffect  type;
};

/// 返回目标坐标
const BYTE RTMAGIC_POS_USERCMD_PARA  = 12;
struct stRTMagicPosUserCmd : public stMagicUserCmd{

  stRTMagicPosUserCmd()
  {
    byParam = RTMAGIC_POS_USERCMD_PARA;
  }
  BYTE byTarget;        /**< 目标类型：enumMapDataType */
  stNpcPosition pos;
};

/// 防御方后退
const BYTE BACKOFF_USERCMD_PARA  = 7;
  struct stBackOffMagicUserCmd : public stMagicUserCmd {
    stBackOffMagicUserCmd()
    {
      byParam = BACKOFF_USERCMD_PARA;
    }

    DWORD dwTempID;        /**< 防御方临时编号 */
    BYTE byType;        /**< 目标类型 enumMapDataType */
    BYTE byDirect;        /**< 后退的方向 */
    DWORD x;
    DWORD y;
  };

/// 攻击Npc得到经验
const BYTE OBTAINEXP_USERCMD_PARA = 8;
  struct stObtainExpUserCmd : public stMagicUserCmd{
    stObtainExpUserCmd()
    {
      byParam = OBTAINEXP_USERCMD_PARA;
    }

    DWORD dwTempID;        /**< 经验值来源临时编号 */
    BYTE byType;        /**< 经验值来源 enumMapDataType */
    DWORD dwExp;        /**< 得到的经验 */
    QWORD dwUserExp;      /**< 人物当前经验值的经验 */
  };

/// Npc死亡
const BYTE NPCDEATH_USERCMD_PARA = 9;
  struct stNpcDeathUserCmd : public stMagicUserCmd{
    stNpcDeathUserCmd()
    {
      byParam = NPCDEATH_USERCMD_PARA;
    }

    DWORD dwNpcTempID;      /**< Npc临时编号 */
  };

/// 人物等级提升
const BYTE LEVELUP_USERCMD_PARA  = 10;
  struct stLevelUpUserCmd : public stMagicUserCmd{
    stLevelUpUserCmd()
    {
      byParam = LEVELUP_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时编号 */
  };

//PK模式切换
enum {
  PKMODE_NORMAL,//和平模式
  PKMODE_ENTIRE,//全体模式
  PKMODE_TEAM,//组队模式
  PKMODE_TONG,//帮会模式
  PKMODE_SEPT,//家族模式
  //  PKMODE_SCHOOL,//师门模式
  PKMODE_COUNTRY,//国家模式
  //  PKMODE_CHALLENGE,//挑战模式
  PKMODE_GOODNESS,//善恶模式
  PKMODE_ALLY,//国家联盟
  PKMODE_MAX,//最大值
};

const BYTE PKMODE_USERCMD_PARA = 20;
  struct stPKModeUserCmd : public stMagicUserCmd{
    stPKModeUserCmd()
    {
      byParam = PKMODE_USERCMD_PARA;
    }
    BYTE byPKMode;
  };
const BYTE OBJECT_EXP_USERCMD_PARA = 22;
  struct stObjectExpUserCmd : public stMagicUserCmd{
    stObjectExpUserCmd()
    {
      byParam = OBJECT_EXP_USERCMD_PARA;
    }
    DWORD id;  
    DWORD exp;  
  };

enum enmUnStateType{
  UN_STATE_COMBIN,
  UN_STATE_CHANGE_FACE,
  UN_STATE_TEAM_ATTACK_BIRD = USTATE_TEAM_ATTACK_BIRD_FLAG,
  UN_STATE_TEAM_ATTACK_FLOW = USTATE_TEAM_ATTACK_FLOW_CLOUD,
  UN_STATE_TEAM_ATTACK_ONE_DIM = USTATE_TEAM_ATTACK_ONE_DIM,
  UN_STATE_NUM
};

//解除合体状态
const BYTE UNCOMBIN_USERCMD_PARA = 23;
  struct stUnCombinUserCmd : public stMagicUserCmd{
    stUnCombinUserCmd()
    {
      byParam = UNCOMBIN_USERCMD_PARA;
    }
    enum enmUnStateType type;
  };

//燃放焰火
const BYTE FIREWORK_USERCMD_PARA = 24;
struct stFireWorkUserCmd : public stMagicUserCmd{
  stFireWorkUserCmd()
  {
    byParam = FIREWORK_USERCMD_PARA;
  }

  QWORD qwObjectTempID;  //焰火道具ID
  BYTE byType;    //
  DWORD dwUserID;    //焰火燃放者ID
  DWORD dwFireID;    //焰火ID
};

//时间同步消息
const BYTE TIMESYNC_USERCMD_PARA = 25;
struct stTimeSyncUserCmd : public stMagicUserCmd{
  stTimeSyncUserCmd()
  {
    byParam = TIMESYNC_USERCMD_PARA;
  }

  time_t serverTime;  //服务器时间
};

//GM command: Switch character obstacle state
const BYTE SWITCH_CHARACTER_OBSTACLE_USERCMD_PARA      = 26;
struct stSwitchCharacterObstacleUserCmd : public stMagicUserCmd{
       stSwitchCharacterObstacleUserCmd()
       {
               byParam = SWITCH_CHARACTER_OBSTACLE_USERCMD_PARA;
       }

       bool bOn;               //true: Use obstacle
};
/// 攻击返回给其他人
const BYTE RT_OTHER_MAGIC_USERCMD_PARA = 27;
struct stRTOtherMagicUserCmd : public stMagicUserCmd{

  stRTOtherMagicUserCmd()
  {
    byParam = RT_OTHER_MAGIC_USERCMD_PARA;
  }

  BYTE byTarget;        /**< 目标类型：enumMapDataType */
  DWORD dwUserTempID;      /**< 目标临时编号 */
  BYTE bySrc;          /**< 攻击者类型：enumMapDataType */
  DWORD dwSrcTempID;      /**< 攻击者临时编号 */
};

//////////////////////////////////////////////////////////////
/// 魔法指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 复活指令定义开始
//////////////////////////////////////////////////////////////
  struct stReliveUserCmd : public stNullUserCmd{
    stReliveUserCmd()
    {
      byCmd = RELIVE_USERCMD;
    }
  };

/// 主用户死亡指令
const BYTE MAINUSERDEATH_RELIVE_USERCMD_PARA = 1;
  struct stMainUserDeathReliveUserCmd : public stReliveUserCmd{
    stMainUserDeathReliveUserCmd()
    {
      byParam = MAINUSERDEATH_RELIVE_USERCMD_PARA;

      dwUserTempID = 0;
      deathType = 0;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */
    DWORD deathType;
  };

/// 主用户复活指令
const BYTE MAINUSERRELIVE_RELIVE_USERCMD_PARA = 2;
  struct stMainUserReliveReliveUserCmd : public stReliveUserCmd{
    stMainUserReliveReliveUserCmd()
    {
      byParam = MAINUSERRELIVE_RELIVE_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */

    DWORD x,y;          // 坐标
  };

//复活方式
enum
{
  ReliveHome,//回城复活
  ReliveMoney,//金钱复活
  ReliveSkill,//技能复活
  ReliveBattle,	//sky 战场复活
  Relive_1_min,//追捕凶犯1分钟
  Relive_5_min,//追捕凶犯5分钟
  Relive_10_min//追捕凶犯10分钟
};
/// 死亡动画播放完毕
const BYTE OK_RELIVE_USERCMD_PARA = 3;
  struct stOKReliveUserCmd : public stReliveUserCmd{
    stOKReliveUserCmd()
    {
      byParam = OK_RELIVE_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */
    BYTE  byType;        /**< 复活方式 */
  };
//////////////////////////////////////////////////////////////
/// 复活指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 用户移动指令定义开始
//////////////////////////////////////////////////////////////
  struct stMoveUserCmd : public stNullUserCmd{
    stMoveUserCmd()
    {
      byCmd = MOVE_USERCMD;
    }
  };


/// 用户移动
const BYTE USERMOVE_MOVE_USERCMD_PARA = 2;
  struct stUserMoveMoveUserCmd : public stMoveUserCmd {
    stUserMoveMoveUserCmd()
    {
      byParam = USERMOVE_MOVE_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时编号 */

    BYTE byDirect;        /**< 移动方向 */
    BYTE bySpeed;        /**< 移动速度 */
    WORD x;          /**< 目的坐标 */
    WORD y;
  };

/// 网关向主用户发送的瞬移指令
const BYTE USERINSTANTJUMP_MOVE_USERCMD_PARA = 10;
  struct stUserInstantJumpMoveUserCmd : public stMoveUserCmd{
    stUserInstantJumpMoveUserCmd()
    {
      byParam = USERINSTANTJUMP_MOVE_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */

    DWORD dwNextScreenPosition;  /**< 人所到达的屏位置 */
    WORD wdNextOffsetX;      /**< 人所到达的屏的偏移X */
    WORD wdNextOffsetY;      /**< 人所到达的屏的偏移Y */
  };

/// 用户进入地图指令命令
/// 目前只应用于进出总坛
const BYTE USERGOTOMAP_MOVE_USERCMD_PARA = 12;
struct stUserGotoMapMoveUserCmd : public stMoveUserCmd
{
  stUserGotoMapMoveUserCmd()
  {
    byParam = USERGOTOMAP_MOVE_USERCMD_PARA;
  }
  WORD IsBackToCity;
  DWORD dwMapType;
  char mapName[MAX_NAMESIZE + 1];
};

/// Npc移动指令
const BYTE NPCMOVE_MOVE_USERCMD_PARA = 20;
  struct stNpcMoveMoveUserCmd : public stMoveUserCmd{
    stNpcMoveMoveUserCmd()
    {
      byParam = NPCMOVE_MOVE_USERCMD_PARA;
    }

    DWORD dwNpcTempID;      /**< Npc临时编号 */

    BYTE byDirect;        /**< 移动方向 */
    BYTE bySpeed;        /**< 移动的速度 */
    WORD x;          /**< 目的坐标 */
    WORD y;
  };

/// 请求获取大陆列表
const BYTE REQUESTLANDMASS_MOVE_USERCMD_PARA = 30;
  struct stRequestLandMassMoveUserCmd : public stMoveUserCmd{
    stRequestLandMassMoveUserCmd()
    {
      byParam = REQUESTLANDMASS_MOVE_USERCMD_PARA;
    }
  };

struct t_LandMass {
  BYTE groupName[MAX_NAMESIZE + 1];   /**< 大陆名称 */
  BYTE countryName[MAX_NAMESIZE + 1]; /**< 国家名称 */
  BYTE cityName[MAX_NAMESIZE + 1];    /**< 城市名称 */
  WORD wdOnlineUser;          /**< 大陆在线人数 */
  BYTE byAvailable;           /**< 大陆是否可用 */
  DWORD price;        // 跳转费用
};

/// 服务器返回大陆列表
const BYTE RESPONSELANDMASS_MOVE_USERCMD_PARA = 31;
  struct stResponseLandMassMoveUserCmd : public stMoveUserCmd{
    stResponseLandMassMoveUserCmd()
    {
      byParam = RESPONSELANDMASS_MOVE_USERCMD_PARA;
    }

    int size;
    //列表
  };

/// 跳转大陆
const BYTE LANDMASSJUMP_MOVE_USERCMD_PARA = 32;
  struct stLandMassJumpMoveUserCmd : public stMoveUserCmd{
    stLandMassJumpMoveUserCmd()
    {
      byParam = LANDMASSJUMP_MOVE_USERCMD_PARA;
    }
  };

/// 坐下起来指令，至于是坐下还是起来跟当前状态有关
const BYTE SITDOWN_MOVE_USERCMD_PARA = 33;
  struct stSitDownMoveUserCmd : public stMoveUserCmd{
    stSitDownMoveUserCmd()
    {
      byParam = SITDOWN_MOVE_USERCMD_PARA;
    }
  };
//////////////////////////////////////////////////////////////
/// 用户移动指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 选择指令定义开始
//////////////////////////////////////////////////////////////
struct stSelectUserCmd : public stNullUserCmd
{
  stSelectUserCmd()
  {
    byCmd = SELECT_USERCMD;
  }
};

/**
 * \brief 角色状态标志位
 *
 */
#define CHARBASE_OK			1	///已经登陆过游戏
#define CHARBASE_FORBID		2	///角色被封
#define CHARBASE_VIP		4	///收费用户(充过值)
#define CHARBASE_EXP125		8	///1.25倍经验状态
#define CHARBASE_EXP150		16	///1.50倍经验状态
#define CHARBASE_EXP175		32	///1.75倍经验状态
#define CHARBASE_DITAO		64	///地之套装效果
#define CHARBASE_TIANTAO	128	///天之套装效果
#define CHARBASE_SHENTAO	256	///神之套装效果
/// 最大角色信息个数
const WORD MAX_CHARINFO = 2;
/// 角色信息
struct SelectUserInfo
{
  DWORD id;            /// 角色编号
  char  name[MAX_NAMESIZE+1];    /// 角色名称
  WORD	JobType;			//[shx Add 职业]
  WORD type;            /// 角色类型
  WORD level;            /// 角色等级
  DWORD mapid;          /// 角色所在地图编号
  char  mapName[MAX_NAMESIZE+1];  /// 角色所在地图名称
  WORD country;          ///  国家ID
  WORD face;
  WORD hair;             /// [shx Add] 发型
  char OldMap[MAX_MAP_PATH];	///sky 移动到该地图前的地图位置
  char  countryName[MAX_NAMESIZE+1];  /// 国家名称
  DWORD bitmask;          /// 角色掩码
};

const BYTE USERINFO_SELECT_USERCMD_PARA = 1;
struct stUserInfoUserCmd : public stSelectUserCmd
{
  stUserInfoUserCmd()
  {
    byParam = USERINFO_SELECT_USERCMD_PARA;
    bzero(charInfo,sizeof(charInfo));
    size = 0;
  }
  SelectUserInfo charInfo[MAX_CHARINFO];
  WORD size;
  BYTE data[0];
};

// 判断头象的性别
inline bool IsMaleFace(int face)
{
  return (face & 0x1) == 1;
}

inline bool IsFemaleFace(int face)
{
  return !IsMaleFace(face);
}

inline int getCharTypeByFace(int face)
{
  if (IsMaleFace(face)) return PROFESSION_1;
  return PROFESSION_2;
}

/// 请求创建用户档案
const BYTE CREATE_SELECT_USERCMD_PARA = 2;
struct stCreateSelectUserCmd : public stSelectUserCmd
{
  stCreateSelectUserCmd()
  {
    byParam = CREATE_SELECT_USERCMD_PARA;
  }

  char strUserName[MAX_NAMESIZE + 1];  /**< 用户名字  */
  WORD	JobType;			//[shx Add 职业]
  WORD  Face;               //[shx Add 头像]
  WORD charType;
  BYTE byHairType;      /**< 头发类型 */
  DWORD byRGB;        /**< 颜色RGB */
  WORD country;        /**< 国家ID */
  WORD five;          /**< 五行主属性 */
};

/// 请求登陆
const BYTE LOGIN_SELECT_USERCMD_PARA = 3;
struct stLoginSelectUserCmd : public stSelectUserCmd
{
  stLoginSelectUserCmd()
  {
    byParam = LOGIN_SELECT_USERCMD_PARA;
  }

  DWORD charNo;
  char jpegPassport[7];        /**< 图形验证码 */
};

/// 请求删除帐号
const BYTE DELETE_SELECT_USERCMD_PARA = 4;
struct stDeleteSelectUserCmd : public stSelectUserCmd
{
  stDeleteSelectUserCmd()
  {
    byParam = DELETE_SELECT_USERCMD_PARA;
    bzero(numPassword,sizeof(numPassword));
  }

  DWORD  charNo;
  char  numPassword[MAX_NUMPASSWORD];
};

/// 请求检查角色名
const BYTE CHECKNAME_SELECT_USERCMD_PARA = 5;
struct stCheckNameSelectUserCmd : public stSelectUserCmd
{
  stCheckNameSelectUserCmd()
  {
    byParam = CHECKNAME_SELECT_USERCMD_PARA;
    name[0] = 0;
    err_code = 0;
  }

  char name[MAX_NAMESIZE + 1];  /**< 用户名字  */
  BYTE err_code; //返回时的信息 0 没有错误 1 名字重复 2 名字包含不合法的内容
};

/// 返回删除角色失败
const BYTE RETURN_DELETE_SELECT_USERCMD_PARA = 6;
struct stReturnDeleteSelectUserCmd : public stSelectUserCmd
{
  stReturnDeleteSelectUserCmd()
  {
    byParam = RETURN_DELETE_SELECT_USERCMD_PARA;
  }

  char name[MAX_NAMESIZE + 1];  /**< 角色名字  */
  BYTE err_code; //返回时的信息 1: 您是帮主，请解散帮会后再删除角色
                 //             2: 您是师尊，请解散师门后再删除角色
                 //             3: 您是族长，请解散家族后再删除角色
           //             4: 操作异常，请重试
};

/// 请求国家列表
const BYTE REQUEST_COUNTRY_SELECT_USERCMD_PARA = 7;
struct stRequestSelectUserCmd : public stSelectUserCmd
{
  stRequestSelectUserCmd()
  {
    byParam = REQUEST_COUNTRY_SELECT_USERCMD_PARA;
  }

};
/// 请求删除帐号时数字密码错误
const BYTE DELETE_ERROR_SELECT_USERCMD_PARA = 8;
struct stDeleteErrorSelectUserCmd : public stSelectUserCmd
{
  stDeleteErrorSelectUserCmd()
  {
    byParam = DELETE_ERROR_SELECT_USERCMD_PARA;
  }

};
//////////////////////////////////////////////////////////////
// 选择指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 用户属性指令定义开始
//////////////////////////////////////////////////////////////

  struct stPropertyUserCmd : public stNullUserCmd{
    stPropertyUserCmd()
    {
      byCmd = PROPERTY_USERCMD;
    }
  };

/// 定义装备格子类型
enum {
  EQUIPCELLTYPE_NONE=0,/// 不能装备
  EQUIPCELLTYPE_HELM=1,/// 头盔
  EQUIPCELLTYPE_BODY=2,/// 服装
  EQUIPCELLTYPE_HANDR=3,/// 右手
  EQUIPCELLTYPE_HANDL=4,/// 左手
  EQUIPCELLTYPE_NECKLACE=5,/// 项链
  EQUIPCELLTYPE_GLOVES=6,/// 手套,手镯
  EQUIPCELLTYPE_RING=7,/// 戒指
  EQUIPCELLTYPE_BELT=8,/// 腰带
  EQUIPCELLTYPE_SHOES=9,/// 鞋子
  EQUIPCELLTYPE_OTHER=10,/// 特殊物品,比如马牌
  EQUIPCELLTYPE_PACKAGE=11,/// 装备的包裹
  EQUIPCELLTYPE_MAKE=12,/// 合成、升级，镶嵌的包裹
  EQUIPCELLTYPE_ADORN=13,/// 装饰品
  //[xq]加几个类型
  EQUIPCELLTYPE_TROUSERS=14,				//裤子
  EQUIPCELLTYPE_GLOVE=15,				//手套
  EQUIPCELLTYPE_CUFF=16,				//护腕
  EQUIPCELLTYPE_MANTEAU=17,					//披风
  EQUIPCELLTYPE_SHOULDER=18,				//肩膀
  EQUIPCELLTYPE_BOWLDER=19,			//玉佩
  EQUIPCELLTYPE_FASHION=20,				//时装
  EQUIPCELLTYPE_AUTOADDBLOOD=21				//自动加血
};

enum{
  EQUIPCELLTYPE_LEFT,///左边
  EQUIPCELLTYPE_RIGHT,///右边
};

/// 定义装备动作类型
enum{
  EQUIPACTION_INIT,/// 初始装备
  EQUIPACTION_MOVE,/// 移动装备
  EQUIPACTION_SHATTER,/// 装备损坏
  EQUIPACTION_OBTAIN,/// 装备获得
  EQUIPACTION_DROP,/// 装备丢弃
  EQUIPACTION_REFRESH,/// 刷新装备
};

/// 定义物品格子类型
enum{
  OBJECTCELLTYPE_NONE,/// 不是格子，用于丢弃或捡到物品
  OBJECTCELLTYPE_COMMON,/// 普通物品格子
  OBJECTCELLTYPE_EQUIP,/// 装备
  OBJECTCELLTYPE_MOUSE,/// 鼠标
  OBJECTCELLTYPE_TRADE,/// 自己的交易格子
  OBJECTCELLTYPE_OTHERTRADE,/// 对方的交易格子
  OBJECTCELLTYPE_BANK,/// 银行
  OBJECTCELLTYPE_SELL,/// 卖
  OBJECTCELLTYPE_STORE,/// 仓库
  OBJECTCELLTYPE_EQUIPSHOW,/// 非自己穿着的装备
  OBJECTCELLTYPE_PACKAGE,/// 包裹的格子
  OBJECTCELLTYPE_MAKE,/// 合成、升级，镶嵌的格子
  OBJECTCELLTYPE_MYSHOP,/// 自己摊位的格子
  OBJECTCELLTYPE_OTHERSSHOP,/// 别的玩家摊位的格子
  OBJECTCELLTYPE_MAIL,/// 邮件系统的格子
  OBJECTCELLTYPE_COUNTRY_SAVEBOX,/// 国家倉库
  OBJECTCELLTYPE_PET,/// 宠物包裹
};

/// 定义升级格子类型
enum {
  MAKECELLTYPE_EQUIP=0, /// 被合成、升级，镶嵌的物品
  MAKECELLTYPE_MATERIAL1=1,/// 材料1
  MAKECELLTYPE_MATERIAL2=2,/// 材料2
  MAKECELLTYPE_MATERIAL3=3,/// 材料3
  MAKECELLTYPE_MATERIAL4=4,/// 材料4
};

/// 定义升级格子类型
enum {
  UPGRADECELLTYPE_UPER=0,/// 被升级的物品
  UPGRADECELLTYPE_JEWEL1=1,/// 升级宝石格子1
  UPGRADECELLTYPE_JEWEL2=2,/// 升级宝石格子2
};

/// 用户道具数据
#define ADDUSEROBJECT_PROPERTY_USERCMD_PARAMETER 1
  struct stAddObjectPropertyUserCmd : public stPropertyUserCmd{
    stAddObjectPropertyUserCmd()
    {
      byParam = ADDUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    BYTE byActionType;      /**< 物品动作类型 */
    t_Object object;      /**< 物品数据 */
  };

/// 删除道具数据
#define REMOVEUSEROBJECT_PROPERTY_USERCMD_PARAMETER 2
  struct stRemoveObjectPropertyUserCmd : public stPropertyUserCmd {
    stRemoveObjectPropertyUserCmd()
    {
      byParam = REMOVEUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
  };

/// 交换（移动）用户物品
#define SWAPUSEROBJECT_PROPERTY_USERCMD_PARAMETER 3
  struct stSwapObjectPropertyUserCmd : public stPropertyUserCmd{
    stSwapObjectPropertyUserCmd()
    {
      byParam = SWAPUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    stObjectLocation  dst;  /**< 物品目的位置 如果目的位置上有物品，则交换*/
  };

/// 分裂物品指令（客户端自动减少源物品的数量）
#define SPLITUSEROBJECT_PROPERTY_USERCMD_PARAMETER 4
  struct stSplitObjectPropertyUserCmd : public stPropertyUserCmd{
    stSplitObjectPropertyUserCmd()
    {
      byParam = SPLITUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    DWORD qwNewThisID;      /**< 新物品的唯一ID */
    DWORD dwNum;        /**< 分裂的数量 */
    stObjectLocation  dst;  /**< 物品目的位置*/
  };

/// 合并物品
#define UNIONUSEROBJECT_PROPERTY_USERCMD_PARAMETER 5
  struct stUnionObjectPropertyUserCmd : public stPropertyUserCmd{
    stUnionObjectPropertyUserCmd()
    {
      byParam = UNIONUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwSrcThisID;      /**< 源物品唯一ID */
    DWORD qwDstThisID;      /**< 目标物品唯一ID */
  };

/// 设置格子中的物品数量（用于合并物品）
#define REFCOUNTOBJECT_PROPERTY_USERCMD_PARAMETER 6
  struct stRefCountObjectPropertyUserCmd : public stPropertyUserCmd{
    stRefCountObjectPropertyUserCmd()
    {
      byParam = REFCOUNTOBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    DWORD dwNum;        /**< 数量 */
  };

/// 用户使用物品
#define USEUSEROBJECT_PROPERTY_USERCMD_PARAMETER 7
  struct stUseObjectPropertyUserCmd : public  stPropertyUserCmd{
    stUseObjectPropertyUserCmd()
    {
      byParam = USEUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
	  preUseUserID = 0;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    DWORD dwNumber;        /**< 使用的数量 */
	DWORD preUseUserID;	   /**< sky 被使用物品方 */
  };

/// 用户捡地图上的物品
#define PICKUPITEM_PROPERTY_USERCMD_PARA 8
  struct stPickUpItemPropertyUserCmd : public stPropertyUserCmd {
    stPickUpItemPropertyUserCmd()
    {
      byParam = PICKUPITEM_PROPERTY_USERCMD_PARA;
    }

    DWORD x;
    DWORD y;
  };

#define FOUNDITEM_PROPERTY_USERCMD_PARA  9
  struct stFoundItemPropertyUserCmd : public stPropertyUserCmd {
    stFoundItemPropertyUserCmd()
    {
      byParam = FOUNDITEM_PROPERTY_USERCMD_PARA;
    }

    DWORD up_id;  //待打造物品ID,物品唯一id
    DWORD count; //材料个数
    struct material{
      DWORD gem_id; //材料id,类别id
      BYTE gem_level; //材料等级
      BYTE gem_num; //材料数量
    } list[0];
  };

#define UPGRADEITEM_PROPERTY_USERCMD_PARA 10
  struct stUpgradeItemPropertyUserCmd : public stPropertyUserCmd {
    stUpgradeItemPropertyUserCmd() 
    {
      byParam = UPGRADEITEM_PROPERTY_USERCMD_PARA;
    }
    BYTE location; //位置，0 左手 1 右手
  };

#define COMPOSEITEM_PROPERTY_USERCMD_PARA 11
  struct stComposeItemPropertyUserCmd : public stPropertyUserCmd {
    stComposeItemPropertyUserCmd()
    {
      byParam = COMPOSEITEM_PROPERTY_USERCMD_PARA;
    }
    BYTE per_num; //单次合成数量
    BYTE location; //位置，0 左手 1 右手
  };

enum enumGameAccelKeyType{
  GameAccelKeyType_None = 0,
  GameAccelKeyType_Item,// 使用物品
  GameAccelKeyType_Skill,// 技能
  GameAccelKeyType_Face,// 表情
  GameAccelKeyType_Num,
};

#define MAIN_ACCESS_KEY_NUM    12
#define MAIN_ACCESS_KEY_GROUP  4
struct stGameAccelKey {
  BYTE szAccelKey[4];
  enumGameAccelKeyType type;
  DWORD dwID;
  BYTE mGroup;
  stGameAccelKey()
  {
    mGroup = MAIN_ACCESS_KEY_GROUP;
  }
};
// 更新用户快捷键
const BYTE ACCELKEY_PROPERTY_USERCMD_PARA = 12;
  struct stAccekKeyPropertyUserCmd : public stPropertyUserCmd{
    stAccekKeyPropertyUserCmd()
    {
      byParam = ACCELKEY_PROPERTY_USERCMD_PARA;
    }
    WORD  accelNum;
    BYTE  activeGroup;
    stGameAccelKey accelKeys[0];
  };
/// 添加用户技能数据
#define ADDUSERSKILL_PROPERTY_USERCMD_PARA 13
struct stAddUserSkillPropertyUserCmd : public stPropertyUserCmd
{
  stAddUserSkillPropertyUserCmd()
  {
    byParam = ADDUSERSKILL_PROPERTY_USERCMD_PARA;
  }

  DWORD dwSkillID;      /**< 技能ID */
  WORD wdLevel;        /**< 技能等级 */
  WORD wdUpNum;        /**< 技能等级提升点数 */
  DWORD dwExperience;      /**< 当前经验 */
  DWORD dwMaxExperience;    /**< 升级经验 */
};

/// 技能升级指令
#define UPGRADEUSERSKILL_PROPERTY_USERCMD_PARA 14
struct stUpgradeUserSkillPropertyUserCmd : public stPropertyUserCmd
{
  stUpgradeUserSkillPropertyUserCmd()
  {
    byParam = UPGRADEUSERSKILL_PROPERTY_USERCMD_PARA;
  }

  DWORD dwSkillID;      /**< 技能ID */
  WORD wdLevel;        /**< 技能等级 */
};

/// 删除用户技能
#define REMOVEUSERSKILL_PROPERTY_USERCMD_PARAMETER 15
struct stRemoveUserSkillPropertyUserCmd : public stPropertyUserCmd
{
  stRemoveUserSkillPropertyUserCmd()
  {
    byParam = REMOVEUSERSKILL_PROPERTY_USERCMD_PARAMETER;
  }

  DWORD dwSkillID;        /**< 用户技能编号 */
};

/// 系统设置指令 
enum  enumUserSetting          
{       
  USER_SETTING_TEAM = 8,  // 允许组队标志
  USER_SETTING_TRADE,     // 允许交易标志
  USER_SETTING_AUTOFINDPATH,// 自动寻路
  USER_SETTING_FAMILY,    // 允许加入家族标志
  USER_SETTING_UNION,     // 允许加入帮会标志

  USER_SETTING_SHOW_HEADPORTRAIT,//显示小头像
  USER_SETTING_SHOW_MIMIMAP,//显示小地图
  USER_SETTING_AUTO_KILL_SUMMON,//自动打怪
  USER_SETTING_SHOW_PLAYERNAME,//显示玩家名字
  USER_SETTING_SHOW_HELPTIP,//显示帮助教程
  USER_SETTING_SHOW_ALLMINIMAP,//小地图全显示
  USER_SETTING_SHOW_ITEM,//地面显示物品

  USER_SETTING_SHOW_COUNTRYNAME,//显示国家名称
  USER_SETTING_SHOW_UNIONNAME,//显示帮会名称
  USER_SETTING_SHOW_SEPTNAME,//显示家族名称
  USER_SETTING_SHOW_OFFICENAME,//显示官职
  USER_SETTING_SHOW_GRACENAME,//显示文采

  USER_SETTING_CHAT_NINE,//公聊
  USER_SETTING_CHAT_COUNTRY,//国家
  USER_SETTING_CHAT_AREA,//区域
  USER_SETTING_CHAT_WHISPER,//密聊
  USER_SETTING_CHAT_UNION,//帮会
  USER_SETTING_CHAT_TEAM,//组队
  USER_SETTING_CHAT_FAMILY,//家族
  USER_SETTING_CHAT_PRIVATE,//私聊
  USER_SETTING_CHAT_FRIEND,//好友
  USER_SETTING_CHAT_SCHOOL,//师门
  USER_SETTING_CHAT_WORLD,//世界
  //USER_SETTING_CHAT_ALL,//全部

  USER_SETTING_HELP_MOVE,             //移动
  USER_SETTING_HELP_NPC,              //NPC
  USER_SETTING_HELP_NPCDIALOG,        //NPC对话
  USER_SETTING_HELP_ATTACK,           //攻击
  USER_SETTING_HELP_PK,               //PK
  USER_SETTING_HELP_CLEARREDNAME,     //消除红名
  USER_SETTING_HELP_TASK,             //任务
  USER_SETTING_HELP_RIGHTBTN,         //右键选项
  USER_SETTING_HELP_TRADE,            //交易
  USER_SETTING_HELP_TEAM,             //组队
  USER_SETTING_HELP_MEMBERHEAD,       //队员头像
  USER_SETTING_HELP_ACCELKEY,         //快捷使用物品
  USER_SETTING_HELP_PACK,             //包裹
  USER_SETTING_HELP_EQUIP,            //如何装备物品
  USER_SETTING_HELP_EXPACK,           //额外包裹
  USER_SETTING_HELP_SKILL,            //技能
  USER_SETTING_HELP_ADDPROPPOINT,     //加点属性
  USER_SETTING_HELP_STUDY,            //学习
  USER_SETTING_HELP_AUTO_FIND_PATH,//自动寻路
  USER_SETTING_HELP_ITEM_LINK, //物品链接
  USER_SETTING_HELP_PRIVATE_CHAT, //悄悄话
  USER_SETTING_HELP_MATERIAL_COMPOSE,//原料合成
  USER_SETTING_HELP_SOULSTONEL_COMPOSE,//魂魄合成
  USER_SETTING_HELP_SOULSTONE_MAKE,//魂魄镶嵌
  USER_SETTING_HELP_ITEM_UPGRID, //道具升级
  USER_SETTING_HELP_ATTACK_MODE_CHANGE,//攻击模式切换
  USER_SETTING_HELP_CHAT,     //聊天
  USER_SETTING_HELP_SELECT,   //选择目标
  USER_SETTING_HELP_ALT_SELECT_NPC,//alt选中npc

  USER_SETTING_FRIEND,     // 允许加为好友
  USER_SETTING_SCHOOL,     // 允许加入师门标志

  USER_SETTING_MINIGAME,// 允许小游戏
  USER_SETTING_EFFECT      // 开关特效
};

struct stSystemSettings
{
  BYTE bySettings[20];  // 使用 set_state 设置标志
  DWORD dwChatColor[8];  //颜色设置
};

#define SYSTEMSETTINGS_PROPERTY_USERCMD_PARA 16
struct stSystemSettingsUserCmd : public stPropertyUserCmd
{
  stSystemSettingsUserCmd()
  {
    byParam = SYSTEMSETTINGS_PROPERTY_USERCMD_PARA;
  }
  stSystemSettings data;
};

enum{
  PROPERTY_CON = 0,//体质
  PROPERTY_STR = 1,//力量
  PROPERTY_DEX = 2,//敏捷
  PROPERTY_INT = 3,//智力
  PROPERTY_MEN = 4  //精神
};

/// 分配用户属性点数
#define DISTRIBUTEUPOINT_PROPERTY_USERCMD_PARA 17
struct stDistributePointPropertyUserCmd : public stPropertyUserCmd
{
  stDistributePointPropertyUserCmd()
  {
    byParam = DISTRIBUTEUPOINT_PROPERTY_USERCMD_PARA;
  }
  WORD type;

};

// 增加技能点数
#define ADDSKILLPOINT_PROPERTY_USERCMD 18
struct stAddSkillPointPropertyUserCmd : public stPropertyUserCmd
{
  stAddSkillPointPropertyUserCmd()
  {
    byParam = ADDSKILLPOINT_PROPERTY_USERCMD;
  }
  DWORD dwSkillID;
};

/// 清除用户属性点数
#define CLEARPOINT_PROPERTY_USERCMD_PARA 19
struct stClearPointPropertyUserCmd : public stPropertyUserCmd
{
  stClearPointPropertyUserCmd()
  {
    byParam = CLEARPOINT_PROPERTY_USERCMD_PARA;
  }
  DWORD dwItemID;
};

/// 清除用户技能点数
#define CLEARUSERSKILLPOINT_PROPERTY_USERCMD_PARAMETER 20
struct stClearUserSkillPointPropertyUserCmd : public stPropertyUserCmd
{
  stClearUserSkillPointPropertyUserCmd()
  {
    byParam = CLEARUSERSKILLPOINT_PROPERTY_USERCMD_PARAMETER;
  }
  DWORD dwItemID;
};

/*
#define MAKE_ODDS_PROPERTY_USERCMD_PARA 19
struct stMakeOddsPropertyUserCmd : public stPropertyUserCmd
{
  stMakeOddsPropertyUserCmd()
  {
    byParam = MAKE_ODDS_PROPERTY_USERCMD_PARA;
  }
  
  DWORD odds;
};

#define MAKE_SELECT_PROPERTY_USERCMD_PARA 20
struct stMakeSelectPropertyUserCmd : public stPropertyUserCmd
{
  stMakeSelectPropertyUserCmd()
  {
    byParam = MAKE_SELECT_PROPERTY_USERCMD_PARA;
  }
  
  DWORD id; //物品id
};
*/
#define COMPOSE_SOUL_STONE_PROPERTY_USERCMD_PARA 21
struct stComposeSoulStonePropertyUserCmd : public stPropertyUserCmd {
  stComposeSoulStonePropertyUserCmd()
  {
    byParam = COMPOSE_SOUL_STONE_PROPERTY_USERCMD_PARA;
  }
  BYTE location; //位置，0 左手 1 右手

};

#define ENCHASEL_PROPERTY_USERCMD_PARA 22
struct stEnchasePropertyUserCmd : public stPropertyUserCmd {
  stEnchasePropertyUserCmd()
  {
    byParam = ENCHASEL_PROPERTY_USERCMD_PARA;
  }
  BYTE location; //位置，0 左手 1 右手
};

#define HOLE_PROPERTY_USERCMD_PARA 23
struct stHolePropertyUserCmd : public stPropertyUserCmd {
  stHolePropertyUserCmd()
  {
    byParam = HOLE_PROPERTY_USERCMD_PARA;
  }
  DWORD up_id; //待打孔装备id,物品唯一id
  DWORD gem_id; //天魔石id，物品类别id
  BYTE gem_level; //天魔石等级
  BYTE gem_num; //天魔石数量
};

enum enumHairStyle
{
  HairStype_1,//粗旷型
  HairStype_2,//潇洒型
  HairStype_3,//豪放型
  HairStype_4,//靓丽型
  HairStype_5,//清秀型
  HairStype_6//高贵型
};
enum enumHairColor
{
  HairColor_black = 0x00001900,//黑色
  HairColor_drink = 0x00C9004C,//酒红
  HairColor_purple = 0x009300DD//酱紫
};

#define DECOMPOSE_PROPERTY_USERCMD_PARA 24
struct stDecomposePropertyUserCmd : public stPropertyUserCmd {
  stDecomposePropertyUserCmd()
  {
    byParam = DECOMPOSE_PROPERTY_USERCMD_PARA;
  }
  DWORD up_id; //待分解装备id,物品唯一id
};

#define BODYCOLOR_PROPERTY_USERCMD_PARA 25//衣服换色
struct stBodyColorPropertyUserCmd : public stPropertyUserCmd
{
  stBodyColorPropertyUserCmd()
  {
    byParam = BODYCOLOR_PROPERTY_USERCMD_PARA;
  }
  DWORD dwBodyColorCustom;//换色的颜色
};

#define HAIR_PROPERTY_USERCMD_PARA 26//换发型
struct stHairPropertyUserCmd : public stPropertyUserCmd
{
  stHairPropertyUserCmd()
  {
    byParam = HAIR_PROPERTY_USERCMD_PARA;
  }
  BYTE byHairType;//头发发型
  DWORD dwHairColor;//头发颜色值
};

#define SELECT_PROPERTY_USERCMD_PARA 27//选中某个对象
struct stSelectPropertyUserCmd : public stPropertyUserCmd
{
  stSelectPropertyUserCmd()
  {
    byParam = SELECT_PROPERTY_USERCMD_PARA;
  }
  BYTE byType;//enumMapDataType
  DWORD dwTempID;//临时编号
  BYTE byOldType;//enumMapDataType
  DWORD dwOldTempID;//临时编号
};

#define SELECT_MAINUSER_PROPERTY_USERCMD_PARA 29//请求观察选中人的属性
struct stSelectMainUserPropertyUserCmd : public stPropertyUserCmd
{
  stSelectMainUserPropertyUserCmd()
  {
    byParam = SELECT_MAINUSER_PROPERTY_USERCMD_PARA;
  }
  BYTE byType;//enumMapDataType
  DWORD dwTempID;//临时编号
};

enum enumEquipType{
  Equip_head,
  Equip_necklace,
  Equip_body,
  Equip_handL,
  Equip_handR,
  Equip_belt,
  Equip_ringL,
  Equip_ringR,
  Equip_bangleL,
  Equip_bangleR,
  Equip_boots,
  Equip_others1,
  Equip_others2,
  Equip_others3,
  Equip_others4,
  Equip_others5
};
struct EquipedObject
{
  BYTE byWhere;//位置enumEquipType
  t_Object object;//物品

};
#define SELECT_RETURN_MAINUSER_PROPERTY_USERCMD_PARA 30//回答观察选中人的属性
struct stSelectReturnMainUserPropertyUserCmd : public stPropertyUserCmd
{
  stSelectReturnMainUserPropertyUserCmd()
  {
    byParam = SELECT_RETURN_MAINUSER_PROPERTY_USERCMD_PARA;
  }
  DWORD dwTempID;//临时编号
  t_MainUserData mainuser_data;
  t_MapUserData mapuser_data;
  DWORD dwSize; //已装备物品个数
  EquipedObject object_data[0];
};

//耐久度变化
const BYTE DURABIILTY_USERCMD_PARA = 31;
  struct stDurabilityUserCmd : public stPropertyUserCmd{
    stDurabilityUserCmd()
    {
      byParam = DURABIILTY_USERCMD_PARA;
    }
    DWORD dwThisID;  /*装备ID */
    DWORD dwDur;  /*当前耐久度*/
    DWORD dwMaxDur;  /*最大耐久度*/
  };

#define SELECT_RETURN_STATES_PROPERTY_USERCMD_PARA 32//被选中人的状态
struct stSelectReturnStatesPropertyUserCmd : public stPropertyUserCmd
{
  stSelectReturnStatesPropertyUserCmd()
  {
    byParam = SELECT_RETURN_STATES_PROPERTY_USERCMD_PARA;
  }
  BYTE byType;//enumMapDataType
  DWORD dwTempID;//临时编号
  DWORD size;//状态个数
  struct
  {
    DWORD state;
    union{
      struct{
        WORD result;//数值
        WORD time;//时间
      };
      DWORD value;
    };
  }states[0];
};

//清除技能
const BYTE CLEARSKILL_USERCMD_PARA = 33;
  struct stClearSkillUserCmd : public stPropertyUserCmd{
    stClearSkillUserCmd()
    {
      byParam = CLEARSKILL_USERCMD_PARA;
    }
  };

#define FACE_PROPERTY_USERCMD_PARA 34//更换头像
struct stFacePropertyUserCmd : public stPropertyUserCmd
{
  stFacePropertyUserCmd()
  {
    byParam = FACE_PROPERTY_USERCMD_PARA;
  }
  DWORD dwFace;//目标头像类型
};
#define HONOR_TO_PKVALUE_PROPERTY_USERCMD_PARA 35//荣誉点洗pk值
struct stHonorToPkValuePropertyUserCmd : public stPropertyUserCmd
{
  stHonorToPkValuePropertyUserCmd()
  {
    byParam = HONOR_TO_PKVALUE_PROPERTY_USERCMD_PARA;
  }
};
// 使用血如意和玉如意时需要发送地图信息下去
const BYTE SCROLL_MAP_PROPERTY_USERCMD_PARA = 36;
  struct stScrollMapPropertyUserCmd : public stPropertyUserCmd{
    stScrollMapPropertyUserCmd()
    {
      byParam = SCROLL_MAP_PROPERTY_USERCMD_PARA;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    DWORD  size;
    struct
    {
      char strMapName[MAX_NAMESIZE + 1];
    }mapname[0];
    
  };

/// 清除用户属性点数只限5点
#define CLEARPOINT_LIMIT_PROPERTY_USERCMD_PARA 37
struct stClearPointLimitPropertyUserCmd : public stPropertyUserCmd
{
  stClearPointLimitPropertyUserCmd()
  {
    byParam = CLEARPOINT_LIMIT_PROPERTY_USERCMD_PARA;
  }
  QWORD qwThisID;
  BYTE  byProperty;
};

// 请求增值地图列表
const BYTE REQUEST_INC_MAP_PROPERTY_USERCMD_PARA = 38;
  struct stRequestIncMapPropertyUserCmd : public stPropertyUserCmd{
    stRequestIncMapPropertyUserCmd()
    {
      byParam = REQUEST_INC_MAP_PROPERTY_USERCMD_PARA;
    }
  };

enum horseState
{
  HORSE_STATE_PUTUP,//收起
  HORSE_STATE_FOLLOW,//跟随
  HORSE_STATE_RIDE  //骑乘
};

enum horseSkill
{
  HORSE_SKILL_DEF_UP = 1,//提高物防魔防
  HORSE_SKILL_PATK_UP,//提高物攻
  HORSE_SKILL_MATK_UP,//提高魔攻
  HORSE_SKILL_HP_UP,//提高生命上限
  HORSE_SKILL_MP_UP,//提高魔法上限
  HORSE_SKILL_DMG_UP,//附加伤害
  HORSE_SKILL_DMG_DOWN,//减少自身伤害
};

//马的数据
struct t_HorseData
{
  DWORD id;    //npcid
  char name[MAX_NAMESIZE + 1];//名字
  DWORD lv;    //等级
  WORD str;    //力量
  WORD intel;    //智力
  WORD dex;    //敏捷
  WORD men;    //精神
  WORD con;    //体质
  WORD speed;    //速度
  BYTE pdam;    //增加物理攻击力%
  BYTE pdef;    //增加物理防御力%
  BYTE mdam;    //增加魔法攻击力%
  BYTE mdef;    //增加魔法防御力%
  WORD maxhp;    //最大HP
  WORD maxmp;    //最大MP
  DWORD callTime;    //召唤间隔
  horseState state;  //马的状态
  WORD poisonRes;    //抗毒
  WORD lullRes;    //抗麻痹
  WORD faintRes;    //抗晕眩
  WORD chaosRes;    //抗混乱
  WORD freezeRes;    //抗冰冻
  WORD petrifyRes;  //抗石化
  WORD blindRes;    //抗失明
  WORD slowRes;    //抗减速
  DWORD horseid;    //马的id（道具id）

  //[sky 增加马匹训练相关变量]
  WORD horseXLlevel;  //马匹训练等级
  DWORD horseXLtime;  //马匹训练剩余时间
};

#define SELECT_RETURN_HORSE_PROPERTY_USERCMD_PARA 39//回答观察选中人的属性
struct stSelectReturnHorsePropertyUserCmd : public stPropertyUserCmd
{
  stSelectReturnHorsePropertyUserCmd()
  {
    byParam = SELECT_RETURN_HORSE_PROPERTY_USERCMD_PARA;
  }
  t_HorseData data;
};

#define GO_TRAIN_PROPERTY_USERCMD_PARA 40//请求进入练级地图
struct stGoTrainPropertyUserCmd : public stPropertyUserCmd
{
  stGoTrainPropertyUserCmd()
  {
    byParam = GO_TRAIN_PROPERTY_USERCMD_PARA;
  }
  DWORD level;//去第几层
};

//#ifndef _MSC_VER
/// 批量添加用户道具数据
#define ADDUSEROBJECT_LIST_PROPERTY_USERCMD_PARAMETER 41
  struct stAddObjectListPropertyUserCmd : public stPropertyUserCmd{
    stAddObjectListPropertyUserCmd()
    {
      byParam = ADDUSEROBJECT_LIST_PROPERTY_USERCMD_PARAMETER;
      num=0;
	  TabNum = 0;
    }
	BYTE TabNum; //sky 用户可使用的包袱页数
    WORD num;
    struct
    {
      BYTE byActionType;      /**< 物品动作类型 */
      t_Object object;      /**< 物品数据 */
    }list[0];
  };
//#endif //_MSC_VER

/*can not be processed by make cmd */#define RESPONSE_PROPERTY_USERCMD_PARA 0x81
struct stResponsePropertyUserCmd : public stPropertyUserCmd
{
  stResponsePropertyUserCmd()
  {
    byParam = RESPONSE_PROPERTY_USERCMD_PARA;
  }
  
  BYTE kind; //类别，1:合成 2:打造 3:升级
  BYTE status; //结果 0 成功 非0 失败
};

//////////////////////////////////////////////////////////////
// 用户属性指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 用户聊天指令定义开始
//////////////////////////////////////////////////////////////

struct stChatUserCmd : public stNullUserCmd
{
  stChatUserCmd()
  {
    byCmd = CHAT_USERCMD;
  }
};

enum enumChatType{
  CHAT_TYPE_PRIVATE  = 1,/// 私聊频道
  CHAT_TYPE_NINE,/// 轻聊频道
  CHAT_TYPE_TEAM,         /// 队伍频道
  CHAT_TYPE_FRIEND,       /// 好友频道
  CHAT_TYPE_GM,           /// GM聊频道
  CHAT_TYPE_SYSTEM,       /// 系统频道
  CHAT_TYPE_UNION,        /// 帮会频道
  CHAT_TYPE_POP,          /// 弹出式系统提示
  CHAT_TYPE_PERSON,       /// 个人频道
  CHAT_TYPE_WHISPER,      ///悄悄话
  CHAT_TYPE_WHISPERTOME,///悄悄话
  CHAT_TYPE_COUNTRY,      /// 国家频道
  CHAT_TYPE_AREA,///区域频道
  CHAT_TYPE_FAMILY,       /// 家族频道

  CHAT_TYPE_FRIEND_AFFICHE,/// 好友公告
  CHAT_TYPE_UNION_AFFICHE,/// 帮会公告
  CHAT_TYPE_OVERMAN_AFFICHE,/// 师门公告
  CHAT_TYPE_FAMILY_AFFICHE,/// 家族公告

  CHAT_TYPE_FRIEND_PRIVATE,/// 好友私聊
  CHAT_TYPE_UNION_PRIVATE,/// 帮会私聊
  CHAT_TYPE_OVERMAN_PRIVATE,/// 师门私聊
  CHAT_TYPE_FAMILY_PRIVATE,/// 家族私聊

  CHAT_TYPE_NPC,///npc说话

  CHAT_TYPE_EMOTION,///表情
  CHAT_TYPE_SHOPADV,///摆摊广告
  CHAT_TYPE_WORLD,///世界频道
  CHAT_TYPE_OVERMAN,/// 师门频道
  CHAT_TYPE_AUTO,/// 自动回复
  CHAT_TYPE_COUNTRY_PK,/// 外国人入侵PK消息
  CHAT_TYPE_BLESS_MSG,/// 个人祝福消息
  CHAT_TYPE_COUNTRY_MARRY,/// 结婚消息广播
  CHAT_TYPE_ERROR_GM,///发送到GM工具的警告信息
  CHAT_TYPE_MINIGAME  /// 玩小游戏聊天
};


enum enumSysInfoType{
  INFO_TYPE_SYS   =       1,/// 系统信息、GM信息，在聊天窗口
  INFO_TYPE_GAME, /// 游戏信息，屏幕左上
  INFO_TYPE_STATE,        /// 状态转换，屏幕左上
  INFO_TYPE_FAIL,         /// 失败信息，屏幕左上
  INFO_TYPE_EXP,  /// 特殊信息,获得经验、物品，在人物头上
  INFO_TYPE_MSG,  /// 弹出用户确认框的系统消息
  INFO_TYPE_KING, /// 国王发出的聊天消息
  INFO_TYPE_CASTELLAN,/// 城主发出的聊天消息
  INFO_TYPE_EMPEROR,/// 皇帝发出的聊天消息
  INFO_TYPE_SCROLL,/// 屏幕上方滚动的系统信息
  INFO_TYPE_ADDFRIEND,/// 加好友任务显示和动画播放
  INFO_TYPE_BREAKFRIEND,/// 割袍断义任务显示和动画播放
  INFO_TYPE_SKYROCKET1,/// 焰火类型1
  INFO_TYPE_SKYROCKET2,/// 焰火类型2
  INFO_TYPE_ATT_FLAG,/// 旗子被攻击
};

#define ALL_CHAT_USERCMD_PARAMETER 1
struct stTradeObject
{
  DWORD dwObjectID;
  DWORD dwObjectTempID;
  char strName[MAX_NAMESIZE + 1];
  BYTE upgrade;                         // 等级
  BYTE kind;      //物品类型,0普通,1蓝色,2金色,4神圣,8套装
};

///客户端发送到服务器的消息
struct  stChannelChatUserCmd: public stChatUserCmd
{
  DWORD dwType;      /**< 消息类型 */
  DWORD dwSysInfoType;    /**< 系统消息的类型 */ //表情类型
  DWORD dwCharType;    /**< 角色类型 */
  DWORD dwChannelID;
  DWORD dwFromID;      ///发送者的ID,是临时id
  DWORD dwChatTime;      // 谈话时间
  BYTE size;        // 物品数量
  char pstrName[MAX_NAMESIZE + 1];  /**< 名字 */ 
  char pstrChat[MAX_CHATINFO + 1];  /**< 对话 */
  stTradeObject tobject_array[0]; // 交易物品列表
  stChannelChatUserCmd()
  {
    bzero(pstrChat,sizeof(pstrChat));
    bzero(pstrName,sizeof(pstrName));
    byParam = ALL_CHAT_USERCMD_PARAMETER;
    dwChannelID=0;
    dwSysInfoType =1;
    dwCharType = 1;
    size = 0;
  }
};
struct  stServerChannelChatUserCmd: public stChatUserCmd
{
  DWORD dwType;      /**< 消息类型 */
  DWORD dwSysInfoType;    /**< 系统消息的类型 */ //表情类型
  DWORD dwCharType;    /**< 角色类型 */
  DWORD dwChannelID;
  DWORD dwFromID;      ///发送者的ID,是临时id
  DWORD dwChatTime;      // 谈话时间
  BYTE size;        // 物品数量
  char info[0];
  stServerChannelChatUserCmd()
  {
    byParam = ALL_CHAT_USERCMD_PARAMETER;
    dwChannelID=0;
    dwSysInfoType =1;
    dwCharType = 1;
    size = 0;
  }
};

// 解散队伍
#define REMOVE_TEAM_USERCMD_PARA 2
struct stRemoveTeamUserCmd : public stChatUserCmd
{
  stRemoveTeamUserCmd()
  {
    byParam = REMOVE_TEAM_USERCMD_PARA;
  }
};

// 添加队员，刷新队员数据 指令
#define ADD_TEAMMEMBER_USERCMD_PARA 3
struct stTeamMemberData
{
  char pstrName[MAX_NAMESIZE + 1];  // 队员名字
  BYTE byHead;          // 是否是队长
  DWORD dwTempID;          //成员tempid
  DWORD dwMaxHealth;        // HP
  DWORD dwHealth;
  DWORD dwMaxMp;          //MP
  DWORD dwMp;
  WORD wdFace;          //肖像
};
struct stAddTeamMemberUserCmd: public stChatUserCmd
{
  stAddTeamMemberUserCmd()
  {
    byParam = ADD_TEAMMEMBER_USERCMD_PARA;
  }
  DWORD dwTeamID;          // 队伍ID
  DWORD dwHeadID;			//sky 队长ID
  stTeamMemberData data;
};

// 删除队员指令
#define REMOVE_TEAMMEMBER_USERCMD_PARA 4
struct stRemoveTeamMemberUserCmd: public stChatUserCmd
{
  stRemoveTeamMemberUserCmd()
  {
    byParam = REMOVE_TEAMMEMBER_USERCMD_PARA;
  }
  DWORD dwTeamID;          // 队伍ID
  char pstrName[MAX_NAMESIZE + 1];  // 队员名字
  //DWORD dwTempID;          //队员tempid
};

/**
 * 队伍模式
 */
enum
{
  TEAM_NORMAL,//普通模式
  TEAM_HONOR,//荣誉模式
  TEAM_MAX,//无效模式
};
// 请求组队指令,该指令需要发给被请求者
 #define REQUEST_TEAM_USERCMD_PARA 5
 struct stRequestTeamUserCmd: public stChatUserCmd
{
  stRequestTeamUserCmd()
  {
    byParam = REQUEST_TEAM_USERCMD_PARA;
  }
  DWORD dwAnswerUserID;    // 回答者ID,返回给客户端是请求者ID
  DWORD dwTeamMode;      // 队伍模式
};

// 回答组队指令
#define ANSWER_TEAM_USERCMD_PARA 6
struct stAnswerTeamUserCmd: public stChatUserCmd
{
  stAnswerTeamUserCmd()
  {
    byParam = ANSWER_TEAM_USERCMD_PARA;
  }
  DWORD dwRequestUserID;    // 请求者ID
  DWORD dwAnswerUserID;    // 回答者ID
  BYTE  byAgree;        // 是否同意
  DWORD dwTeamMode;      // 队伍模式
};

#define CREATE_CHANNEL_USERCMD_PARAMETER 7
struct  stCreateChannelUserCmd: public stChatUserCmd
{
  DWORD dwChannelID;
  DWORD dwClientID;
  char name[MAX_NAMESIZE + 1];
  char name2[MAX_NAMESIZE + 1];

  stCreateChannelUserCmd()
  {
    byParam = CREATE_CHANNEL_USERCMD_PARAMETER;
  }
};

#define INVITE_CHANNEL_USERCMD_PARAMETER 8
struct  stInvite_ChannelUserCmd: public stChatUserCmd
{
  DWORD dwChannelID;
  char name[MAX_NAMESIZE + 1];
  DWORD   dwCharType;

  stInvite_ChannelUserCmd()
  {
    byParam = INVITE_CHANNEL_USERCMD_PARAMETER;
  }
};

#define JOIN_CHANNEL_USERCMD_PARAMETER 9
struct  stJoin_ChannelUserCmd: public stChatUserCmd
{
  DWORD dwChannelID;
  char name[MAX_NAMESIZE + 1];

  stJoin_ChannelUserCmd()
  {
    byParam = JOIN_CHANNEL_USERCMD_PARAMETER;
  }
};

#define LEAVE_CHANNEL_USERCMD_PARAMETER 10
struct  stLeave_ChannelUserCmd: public stChatUserCmd
{
  DWORD dwChannelID;
  char name[MAX_NAMESIZE + 1];

  stLeave_ChannelUserCmd()
  {
    byParam = LEAVE_CHANNEL_USERCMD_PARAMETER;
  }
};

#define REQUEST_TEAMMEMBER_POSITION_USERCMD_PARA 11

// 请求队员位置
struct stRequestTeamMemberPosition : public stChatUserCmd
{
  stRequestTeamMemberPosition()
  {
    byParam = REQUEST_TEAMMEMBER_POSITION_USERCMD_PARA;
  }
};
// 服务器返回队员位置
#define RETURN_TEAMMEMBER_POSITION_USERCMD_PARA 11
struct stTeamMemberPosition
{
  char szName[MAX_NAMESIZE + 1];
  char szMapName[MAX_NAMESIZE + 1];
  int x,y;
};
struct stReturnTeamMemberPosition : public stChatUserCmd
{
  stReturnTeamMemberPosition()
  {
    byParam = RETURN_TEAMMEMBER_POSITION_USERCMD_PARA;
  }
  DWORD size;
  stTeamMemberPosition memberPos[0];
};

#define QUESTION_OBJECT_USERCMD_PARA 12
struct stQuestionObject : public stChatUserCmd
{
  stQuestionObject()
  {
    byParam = QUESTION_OBJECT_USERCMD_PARA;
  }
  
  char name[MAX_NAMESIZE + 1];  /**< 物品拥有者的名字 */
  DWORD dwObjectTempID;          /// 物品临时ID
};

#define RETURN_QUESTION_OBJECT_USERCMD_PARA 13
struct stReturnQuestionObject : public stChatUserCmd
{
  stReturnQuestionObject()
  {
    byParam = RETURN_QUESTION_OBJECT_USERCMD_PARA; 
  }
  
  char name[MAX_NAMESIZE + 1];  /**< 物品拥有者的名字 */
  t_Object object;               /// 物品资料
};

// 队员离线消息                
#define TEAMMEMBER_OFFLINE_USERCMD_PARA 14
struct stTeamMemberOfflineUserCmd : public stChatUserCmd
{                                       
        stTeamMemberOfflineUserCmd()
        {               
                byParam = TEAMMEMBER_OFFLINE_USERCMD_PARA; 
        }       
        DWORD dwTempID;                                 //队员tempid
};

// 设置自动消息                
#define AUTO_REPLY_USERCMD_PARA 15
struct stAutoReplyUserCmd : public stChatUserCmd
{                                       
        stAutoReplyUserCmd()
        {               
                byParam = AUTO_REPLY_USERCMD_PARA; 
        }
  char text[MAX_CHATINFO];
};

enum
{
  TEAM_EXP_MODE_NORMAL,//普通分配经验模式
  TEAM_EXP_MODE_SPECIAL,//特殊分配经验模式
};
enum
{
  TEAM_OBJ_MODE_NORMAL,		//普通物品分配模式
  TEAM_OBJ_MODE_SPECIAL,	//轮流物品分配模式
  TEAM_OBJ_MODE_CAPTAIN,	//sky 队长分配模式
};

// 请求(设置)队伍经验分配模式
#define EXPMODE_TEAMMEMBER_USERCMD_PARA 16
struct stExpModeTeamMemberUserCmd: public stChatUserCmd
{
  stExpModeTeamMemberUserCmd()
  {
    byParam = EXPMODE_TEAMMEMBER_USERCMD_PARA;
  }
  BYTE byType;
};
// 请求(设置)队伍物品分配模式
#define OBJMODE_TEAMMEMBER_USERCMD_PARA 17
struct stObjModeTeamMemberUserCmd: public stChatUserCmd
{
  stObjModeTeamMemberUserCmd()
  {
    byParam = OBJMODE_TEAMMEMBER_USERCMD_PARA;
  }
  BYTE byType;
};
// 设置组队模式
#define TEAM_MODE_USERCMD_PARA 18
struct stTeamModeUserCmd: public stChatUserCmd
{
  stTeamModeUserCmd()
  {
    byParam = TEAM_MODE_USERCMD_PARA;
  }
  BYTE byType;
};
// 刷新队员HP,MP 指令
#define FRESH_TEAMMEMBER_USERCMD_PARA 19
struct stFreshTeamMemberUserCmd: public stChatUserCmd
{
  stFreshTeamMemberUserCmd()
  {
    byParam = FRESH_TEAMMEMBER_USERCMD_PARA;
  }
  DWORD dwTempID;          //成员tempid
  DWORD dwMaxHealth;        // HP
  DWORD dwHealth;
  /*
   * 这里为了防止8自己对齐,将DWORD改成WORD,如果不够,可以将数据改成3字节的也可以,不会增加流量
   */
  WORD dwMaxMp;          //MP
  WORD dwMp;
};

// 检测到非法用户
#define DIRTY_USER_USERCMD_PARA 20
enum DIRTYUSER_TYPE{
    DIRTYUSER_DLL_CALL = 1,// 外部DLL调用本进程函数，一般外挂用户
    DIRTYUSER_DEBUGGER = 2,// 启用调试器调试本进程，可能是外挂制作者
};
struct stDirtyUserUserCmd : public stChatUserCmd
{
    stDirtyUserUserCmd()
    {
        byParam = DIRTY_USER_USERCMD_PARA;
    }
    BYTE type;
};
// 回答组队指令
#define ANSWER_NAME_TEAM_USERCMD_PARA 21
struct stAnswerNameTeamUserCmd: public stChatUserCmd
{
  stAnswerNameTeamUserCmd()
  {
    byParam = ANSWER_NAME_TEAM_USERCMD_PARA;
  }
  char byRequestUserName[MAX_NAMESIZE + 1];    // 请求者名字
  char byAnswerUserName[MAX_NAMESIZE + 1];    // 回答者名字
  BYTE  byAgree;        // 是否同意
  DWORD dwTeamMode;      // 队伍模式
};
// 请求组队指令,该指令需要发给被请求者
 #define REQUEST_NAME_TEAM_USERCMD_PARA 22
 struct stRequestNameTeamUserCmd: public stChatUserCmd
{
  stRequestNameTeamUserCmd()
  {
    byParam = REQUEST_NAME_TEAM_USERCMD_PARA;
  }
  char byAnswerUserName[MAX_NAMESIZE + 1];    // 回答者名字,返回给客户端是请求者名字
  DWORD dwTeamMode;      // 队伍模式
};
 #define REQUEST_COUNTRY_HELP_USERCMD_PARA 23
 struct stRequestCountryHelpUserCmd: public stChatUserCmd
{
  stRequestCountryHelpUserCmd()
  {
    byParam = REQUEST_COUNTRY_HELP_USERCMD_PARA;
  }
  char mapName[MAX_NAMESIZE + 1];    //请求支援的地图名称
  WORD x;
  WORD y;
};
 #define KILL_FOREIGNER_USERCMD_PARA 24
 struct stKillForeignerUserCmd: public stChatUserCmd
{
  stKillForeignerUserCmd()
  {
    byParam = KILL_FOREIGNER_USERCMD_PARA;
  }
  char heroName[MAX_NAMESIZE + 1];  //英雄人物
  char mapName[MAX_NAMESIZE + 1];    //立功地图
};

 // BOSS刷新提示消息
#define REFRESH_BOSS_USERCMD_PARA 25
 struct stRefreshBossUserCmd: public stChatUserCmd
{
  stRefreshBossUserCmd()
  {
    byParam = REFRESH_BOSS_USERCMD_PARA;
  }
  DWORD npcid;
  BYTE country; //国家
  char mapName[MAX_NAMESIZE + 1];    //BOSS刷新的地图名称
  BYTE time;     // 剩余的刷新时间，如果为0表示刷出
  //WORD x;
  //WORD y;
};

 // BOSS被杀提示消息
#define KILL_BOSS_USERCMD_PARA 26
 struct stKillBossUserCmd: public stChatUserCmd
{
  stKillBossUserCmd()
  {
    byParam = KILL_BOSS_USERCMD_PARA;
  }
  DWORD npcid;
  char name[MAX_NAMESIZE + 1];    //玩家名称
  char mapName[MAX_NAMESIZE + 1];    //BOSS刷新的地图名称
  WORD x;
  WORD y;
};


// sky新增跟换队长消息
#define REMOVE_TEAM_GHAGELEADER_USERCMD_PARA 27
 struct stRemoveTeamChangeLeaderUserCmd: public stChatUserCmd
 {
	 stRemoveTeamChangeLeaderUserCmd()
	 {
		 byParam = REMOVE_TEAM_GHAGELEADER_USERCMD_PARA;
	 }
	 char LeaderName[MAX_NAMESIZE + 1];			// 新队长ID
 };

//////////////////////////////////////////////////////////////
// 用户聊天指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 交易指令定义开始
//////////////////////////////////////////////////////////////
struct stTradeUserCmd : public stNullUserCmd
{
  stTradeUserCmd()
  {
    byCmd = TRADE_USERCMD;
  }
};

#define REQUEST_TRADE_USERCMD_PARAMETER 0
struct stRequestTradeUserCmd :public stTradeUserCmd
{
  stRequestTradeUserCmd()
  {
    byParam = REQUEST_TRADE_USERCMD_PARAMETER;
  }
  DWORD dwAskerTempID;  /**< 请求者 */
  DWORD dwAnswerTempID;  /**< 回答者 */
};

/// 回应交易请求
#define ANSWER_TRADE_USERCMD_PARAMETER 1
struct stAnswerTradeUserCmd:public stTradeUserCmd
{
  stAnswerTradeUserCmd()
  {
    byParam = ANSWER_TRADE_USERCMD_PARAMETER;
  }

  BYTE byAgree;        /**< 是否同意交易 */
  DWORD dwAskerTempID;  /**< 请求者 */
  DWORD dwAnswerTempID;  /**< 回答者 */
};

/// 开始交易
#define BEGIN_TRADE_USERCMD_PARAMETER 2
struct stBeginTradeUserCmd:public stTradeUserCmd
{
  stBeginTradeUserCmd()
  {
    byParam = BEGIN_TRADE_USERCMD_PARAMETER;
  }
  DWORD dwAskerTempID;  /**< 请求者 */
  DWORD dwAnswerTempID;  /**< 回答者 */
};

/// 确定交易
#define COMMIT_TRADE_USERCMD_PARAMETER 5
struct stCommitTradeUserCmd:public stTradeUserCmd
{
  stCommitTradeUserCmd()
  {
    byParam = COMMIT_TRADE_USERCMD_PARAMETER;
  }
  DWORD dwUserTempID;
};

/// 取消交易
#define CANCEL_TRADE_USERCMD_PARAMETER 6
struct stCancelTradeUserCmd:public stTradeUserCmd
{
  stCancelTradeUserCmd()
  {
    byParam = CANCEL_TRADE_USERCMD_PARAMETER;
  }
  DWORD dwUserTempID;
};

/// 交易完成
#define FINISH_TRADE_USERCMD_PARAMETER 7
struct stFinishTradeUserCmd:public stTradeUserCmd
{
  stFinishTradeUserCmd()
  {
    byParam = FINISH_TRADE_USERCMD_PARAMETER;
  }
};

/// 添加交易物品
#define ADD_OBJECT_TRADE_USERCMD_PARAMETER 8
struct stAddObjectTradeUserCmd:public stTradeUserCmd
{
  stAddObjectTradeUserCmd()
  {
    byParam = ADD_OBJECT_TRADE_USERCMD_PARAMETER;
  }
  DWORD user_id; //用户临时id
//  DWORD object_id; //物品唯一id
  t_Object object; //物品数据
  BYTE x;  //物品放置位置x坐标
  BYTE y; //物品放置位置y坐标
};

/// 删除交易物品
#define REMOVE_OBJECT_TRADE_USERCMD_PARAMETER 9
struct stRemoveObjectTradeUserCmd:public stTradeUserCmd
{
  stRemoveObjectTradeUserCmd()
  {
    byParam = REMOVE_OBJECT_TRADE_USERCMD_PARAMETER;
  }
  DWORD user_id; //用户临时id
  DWORD object_id; //物品唯一id
};

/// 访问Npc
#define VISITNPC_TRADE_USERCMD_PARAMETER 10
struct stVisitNpcTradeUserCmd:public stTradeUserCmd
{
  stVisitNpcTradeUserCmd()
  {
    byParam = VISITNPC_TRADE_USERCMD_PARAMETER;
    menuTxt[0] = '\0';
    byReturn = 0;
  }
  DWORD dwNpcTempID;
  BYTE byReturn;
  char menuTxt[1];
};

/// 买物品
#define BUYOBJECT_NPCTRADE_USERCMD_PARAMETER 11
struct stBuyObjectNpcTradeUserCmd:public stTradeUserCmd
{
  stBuyObjectNpcTradeUserCmd()
  {
    byParam = BUYOBJECT_NPCTRADE_USERCMD_PARAMETER;

    dwObjectID = 0;
    dwNum = 1;
    itemLevel = 0;
  }
  DWORD dwObjectID;
  DWORD dwNum;
  BYTE itemLevel;
};

/// 卖物品
#define SELLOBJECT_NPCTRADE_USERCMD_PARAMETER 12
struct stSellObjectNpcTradeUserCmd:public stTradeUserCmd
{
  stSellObjectNpcTradeUserCmd()
  {
    byParam = SELLOBJECT_NPCTRADE_USERCMD_PARAMETER;
  }
  DWORD qwThisID;        /**< 物品唯一ID */
};

/// 修理物品
#define REPAIROBJECT_NPCTRADE_USERCMD_PARAMETER 13
struct stRepairObjectNpcTradeUserCmd:public stTradeUserCmd
{
  stRepairObjectNpcTradeUserCmd()
  {
    byParam = REPAIROBJECT_NPCTRADE_USERCMD_PARAMETER;
  }
  DWORD id;  //修理物品id，全部修理时为0
  DWORD gem_id;  //修复宝石的唯一id，普通修理填0
};

/// 卖马
#define SELLHORSE_NPCTRADE_USERCMD_PARAMETER 14
struct stSellHorseNpcTradeUserCmd:public stTradeUserCmd
{
  stSellHorseNpcTradeUserCmd()
  {
    byParam = SELLHORSE_NPCTRADE_USERCMD_PARAMETER;
  }

  BYTE action; //action 0:卖,action 1: 放逐
};

/// 仓库信息
#define STORE_INFO_NPCTRADE_USERCMD_PARAMETER 15
struct stStoreInfoNpcTradeUserCmd:public stTradeUserCmd
{
  stStoreInfoNpcTradeUserCmd()
  {
    byParam = STORE_INFO_NPCTRADE_USERCMD_PARAMETER;
  }
  
  BYTE page; //页数
};

/// 开始摆摊
#define START_SELL_USERCMD_PARAMETER 16
struct stSellTradeUserCmd:public stTradeUserCmd
{
  stSellTradeUserCmd()
  {
    byParam = START_SELL_USERCMD_PARAMETER;
  }
};

/// 完成摆摊
#define FINISH_SELL_USERCMD_PARAMETER 17
struct stFinishSellUserCmd:public stTradeUserCmd
{
  stFinishSellUserCmd()
  {
    byParam = FINISH_SELL_USERCMD_PARAMETER;
  }
};

/// 添加物品
#define ADD_OBJECT_SELL_USERCMD_PARAMETER 18
struct stAddObjectSellUserCmd:public stTradeUserCmd
{
  stAddObjectSellUserCmd()
  {
    byParam = ADD_OBJECT_SELL_USERCMD_PARAMETER;
  }
  t_Object object; //物品数据
  DWORD price; //物品价钱
  BYTE x;  //物品放置位置x坐标
  BYTE y; //物品放置位置y坐标
};

/// 删除物品
#define REMOVE_OBJECT_SELL_USERCMD_PARAMETER 19
struct stRemoveObjectSellUserCmd:public stTradeUserCmd
{
  stRemoveObjectSellUserCmd()
  {
    byParam = REMOVE_OBJECT_SELL_USERCMD_PARAMETER;
  }
  DWORD object_id; //物品唯一id
};

/// 请求某人的摆摊信息
#define REQUEST_SELL_INFO_USERCMD_PARAMETER 20
struct stRequestSellInfoUserCmd:public stTradeUserCmd
{
  stRequestSellInfoUserCmd()
  {
    byParam = REQUEST_SELL_INFO_USERCMD_PARAMETER;
  }
  DWORD temp_id; //用户临时ID
};

/// 请求购买物品
#define REQUEST_SELL_BUY_USERCMD_PARAMETER 21
struct stRequestSellBuyUserCmd:public stTradeUserCmd
{
  stRequestSellBuyUserCmd()
  {
    byParam = REQUEST_SELL_BUY_USERCMD_PARAMETER;
  }
  DWORD temp_id; //用户临时ID
  DWORD object_id; //物品唯一ID
};

/// 修改仓库密码
#define UPDATE_STORE_PASS_USERCMD_PARAMETER 22
struct stUpdateStorePassUserCmd:public stTradeUserCmd
{
  stUpdateStorePassUserCmd()
  {
    byParam = UPDATE_STORE_PASS_USERCMD_PARAMETER;
  }
  char oldpass[8]; //旧密码
  char newpass[8]; //新密码
};

/// 能否摆摊
#define CAN_SELL_USERCMD_PARAMETER 23
struct stCanSellTradeUserCmd:public stTradeUserCmd
{
  stCanSellTradeUserCmd()
  {
    byParam = CAN_SELL_USERCMD_PARAMETER;
  }
  BYTE status; // 0 success,1 fail
};

enum
{
  STORN = 1,//升级宝石
  SIVER =2,//银
  SILK  =3,//丝绸
  CRYSTAL =4,//水晶
  EBONY  =5,//乌木
  YINGPI =6,//硬皮
};
/// 领赠品品精致升级宝石
#define GOLD_GIVE_USERCMD_PARAMETER 24
struct stGoldGiveTradeUserCmd:public stTradeUserCmd
{
  stGoldGiveTradeUserCmd()
  {
    byParam = GOLD_GIVE_USERCMD_PARAMETER;
  }
  BYTE type;
};
/// 金币修理物品
#define REPAIROBJECT_GOLD_NPCTRADE_USERCMD_PARAMETER 25
struct stRepairObjectGoldNpcTradeUserCmd:public stTradeUserCmd
{
  stRepairObjectGoldNpcTradeUserCmd()
  {
    byParam = REPAIROBJECT_GOLD_NPCTRADE_USERCMD_PARAMETER;
  }
  DWORD id;  //修理物品id，全部修理时为0
};
/// 请求精致升级宝石个数
#define REQUEST_GOLD_GIVE_USERCMD_PARAMETER 26
struct stRequestGoldGiveTradeUserCmd:public stTradeUserCmd
{
  stRequestGoldGiveTradeUserCmd()
  {
    byParam = REQUEST_GOLD_GIVE_USERCMD_PARAMETER;
  }
};
/// 返回精致升级宝石个数
#define RETURN_GOLD_GIVE_USERCMD_PARAMETER 27
struct stReturnGoldGiveTradeUserCmd:public stTradeUserCmd
{
  stReturnGoldGiveTradeUserCmd()
  {
    byParam = RETURN_GOLD_GIVE_USERCMD_PARAMETER;
  }
  DWORD Storn_num;//宝石个数
  DWORD Matarial_num; //材料组数
  DWORD Card_num;    //道具卡张数
};

//#ifndef _MSC_VER
/// 批量添加物品
#define ADD_OBJECT_SELL_LIST_USERCMD_PARAMETER 28
struct stAddObjectSellListUserCmd:public stTradeUserCmd
{
  stAddObjectSellListUserCmd()
  {
    byParam = ADD_OBJECT_SELL_LIST_USERCMD_PARAMETER;
    num=0;
  }
  WORD num;
  struct
  {
    t_Object object; //物品数据
    DWORD price; //物品价钱
    BYTE x;  //物品放置位置x坐标
    BYTE y; //物品放置位置y坐标
  }list[0];
};
//#endif //_MSC_VER

/// 用户请求添加物品id列表
#define REQUEST_ADD_OBJECT_SELL_USERCMD_PARAMETER 29
struct stRequestAddObjectSellUserCmd:public stTradeUserCmd
{
  stRequestAddObjectSellUserCmd()
  {
    byParam = REQUEST_ADD_OBJECT_SELL_USERCMD_PARAMETER;
    num=0;
  }
  WORD num;
  struct
  {
    DWORD qwThisID; //物品id
    DWORD price; //物品价钱
    BYTE x;  //物品放置位置x坐标
    BYTE y; //物品放置位置y坐标
  }list[0];
};

// [Shx Add 修改摆摊广告， 上下行通用]
#define UPDATE_SHOP_ADV_USERCMD_PARAMETER 30
struct stUpdateShopAdvcmd:public stTradeUserCmd
{
	stUpdateShopAdvcmd()
	{
		byParam = UPDATE_SHOP_ADV_USERCMD_PARAMETER;	
		size    = 0;
	}
	WORD size;
	struct stAdv
	{
		DWORD dwID;		//上行 时无用
		char strShopAdv[MAX_SHOPADV];
	} Datas[0];
};

//[Shx Add 交易时通知对方修改金钱]
#define UPDATE_TRADE_MONEY_USERCMD	31
struct stUpdateTradeMoneycmd:public stTradeUserCmd
{
	stUpdateTradeMoneycmd()
	{
		byParam = UPDATE_TRADE_MONEY_USERCMD;
	}
	DWORD dwMyID;
	DWORD dwOtherID;
	DWORD dwMoney;
};

/*
/// 领赠品材料
#define MATARIAL_GIVE_USERCMD_PARAMETER 30
struct stMatarialgiveTradeUserCmd:public stTradeUserCmd
{
        stMatarialgiveTradeUserCmd()
        {
                byParam = MATARIAL_GIVE_USERCMD_PARAMETER;
        }
};

#define REQUEST_MATARIAL_GIVE_USERCMD_PARAMETER 31
struct stRequestMatarialGiveTradeUserCmd:public stTradeUserCmd
{
        stRequestGoldGiveTradeUserCmd()
        {
                byParam = REQUEST_GOLD_GIVE_USERCMD_PARAMETER;
        }
};

#define RETURN_MATARIAl_GIVEL_USERCMD_PARAMETER 32
struct stReturnMatarialGiveTradeUserCmd:public stTradeUserCmd
{
        stReturnGoldGiveTradeUserCmd()
        {
                byParam = RETURN_GOLD_GIVE_USERCMD_PARAMETER;
        }
        DWORD num;//个数
};
*/

//////////////////////////////////////////////////////////////
// 交易指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 帮会指令定义开始
//////////////////////////////////////////////////////////////

struct stUnionUserCmd : public stNullUserCmd
{
  stUnionUserCmd()
  {
    byCmd = UNION_USERCMD;
  }
};

/// 帮会创建前的用户状态检查消息
const BYTE UNION_STATUS_CHECK_PARA = 1;
struct stUnionStatusCheckCmd  : public stUnionUserCmd
{
  stUnionStatusCheckCmd()
  {
    byParam = UNION_STATUS_CHECK_PARA;
  }
};

// 帮会创建命令
const BYTE CREATE_UNION_PARA = 2;
struct stCreateUnionCmd: public stUnionUserCmd
{
  stCreateUnionCmd()
  {
    byParam = CREATE_UNION_PARA;
  }
  char UnionName[MAX_NAMESIZE + 1];  // 帮会名称
};

// 帮会创建成功通知指令
const BYTE SERVER_RETURN_UNION_CREATE_FAILED = 3;
struct stServerReturnUnionCheckCmd : public stUnionUserCmd
{
  stServerReturnUnionCheckCmd()
  {
    byParam = SERVER_RETURN_UNION_CREATE_FAILED;
  }
};

struct stUnionRember{
  char  memberName[MAX_NAMESIZE + 1];      // 帮会成员名称
  char  aliasname[MAX_NAMESIZE + 1];      // 成员别名[职务名称]
  WORD  level;          // 成员等级
  BYTE  byOnline;                          // 成员在线标志 0 为不在线 非0为在线
  WORD  occupation;        // 职业类型
  DWORD exploit;          // 功勋值
  char  septName[MAX_NAMESIZE + 1];      // 所属家族
  BYTE  bySeptMaster;        // 0不是族长，1是族长
};

// 服务器返回帮会成员列表，及请求者的个人帮会信息
const BYTE ALL_UNION_MEMBER_PARA = 5;
struct stAllUnionMemberCmd : public stUnionUserCmd
{
  stAllUnionMemberCmd()
  {
    byParam = ALL_UNION_MEMBER_PARA;
  }
  WORD size;                     // 数量
  stUnionRember memberList[0];   // 成员列表
};


// 帮会的权限定义
enum UNIONPOWER {
  CHANGE_ALIAS,      // 改变称号
  ADD_MEMBER,        // 招收成员
  FIRE_MEMBER,       // 开除成员
  GENERAL,           // 普通会员
  MASTER,  // 帮主权限
  SECOND,  // 副帮主权限
        DARE,  // 发起或接受帮会战
  NOTIFY,  // 发公告
};


// 返回帮会成员的个人信息
const BYTE RETURN_UNION_MEMBER_INFO_PARA = 6;
struct stReturnUnionMemberInfoCmd : public stUnionUserCmd
{
  stReturnUnionMemberInfoCmd()
  {
    byParam = RETURN_UNION_MEMBER_INFO_PARA;
  }

  char alias[MAX_NAMESIZE + 1];      // 消息接收者的别名
  BYTE byPower[2];                    // 消息接收者的权限信息
};

enum UNION_ADD_MEMBER{
      QUESTION,  // 发出邀请某人的询问
      ANSWER_YES,// 确认邀请
      ANSWER_NO          // 否定邀请
};

// 邀请他人加入帮会
const BYTE ADD_MEMBER_TO_UNION_PARA = 7;  // 这个消息由客户端发到服务端是邀请某人，由服务端发到客户端是询问某人是否接受邀请
struct stAddMemberToUnionCmd : public stUnionUserCmd
{
  stAddMemberToUnionCmd()
  {
    byParam = ADD_MEMBER_TO_UNION_PARA;
  }
  char   memberName[MAX_NAMESIZE + 1];   // 被邀请的人
  DWORD memberID;                   // 被邀请人ID
  char   unionName[MAX_NAMESIZE + 1];    // 工会名称
  BYTE   byState;                    // 参见 enum UNION_ADD_MEMBER
};

// 开除帮会成员
const BYTE FIRE_MEMBER_FROM_UNION_PARA = 8;
struct stFireMemberFromUnionCmd : public stUnionUserCmd
{
  stFireMemberFromUnionCmd()
  {
    byParam = FIRE_MEMBER_FROM_UNION_PARA ;
  }
  char memberName[MAX_NAMESIZE + 1];
};

enum{
  UNION_MEMBER_STATUS_ONLINE,// 帮会成员上线
  UNION_MEMBER_STATUS_OFFLINE,// 帮会成员下线
  UNION_MEMBER_STATUS_FIRE, // 帮会成员被开除
  UNION_MEMBER_STATUS_NEWMEMBER,// 新增加帮会成员
  UNION_MEMBER_STATUS_ALIASCHANGE    // 成员别名改变
};

// 服务端更新帮会成员状态及信息通知消息 状态见上表
const BYTE BROADCAST_MEMBER_INFO_PARA = 10;
struct stBroadcastMemberInfo : public stUnionUserCmd
{
  stBroadcastMemberInfo()
  {
    byParam = BROADCAST_MEMBER_INFO_PARA;
    level = 0;
    bzero(name,sizeof(name));
    bzero(septName, sizeof(septName));
    bySeptMaster = 0;
  }
  BYTE byStatus;          // 成员状态
  char name[MAX_NAMESIZE + 1];      // 成员名称
  char aliasname[MAX_NAMESIZE + 1];      // 成员别名
  WORD wdOccupation;        // 成员职业
  WORD level;          // 成员等级
  DWORD exploit;          // 功勋值
  char  septName[MAX_NAMESIZE + 1];      // 所属家族
  BYTE bySeptMaster;        // 0,不是族长，1为族长
};

// 服务器端发送帮会信息
const BYTE UNION_BASE_INFO_PARA = 11;
struct stUnionBaseInfoCmd : public stUnionUserCmd
{
  stUnionBaseInfoCmd()
  {
    byParam = UNION_BASE_INFO_PARA;
  }
  char  unionName[MAX_NAMESIZE + 1];         // 帮会名称
  char  master[MAX_NAMESIZE + 1];        // 帮会会长
  WORD  wdLevel;                       // 帮会级别
  QWORD qwExp;                         // 帮会经验
  char  note[255];            // 帮会介绍
  DWORD dwMana;        // 帮会威望
  DWORD dwAction;        // 行动力
};

// 帮会成员申请退会
const BYTE UNIONMEMBER_LEAVE_UNION_PARA = 12;
struct stUnionMemberLeaveUnionCmd : public stUnionUserCmd
{
  stUnionMemberLeaveUnionCmd()
  {
    byParam = UNIONMEMBER_LEAVE_UNION_PARA;
  }
};

struct stUnionVoteRecord{
  char unionName [MAX_NAMESIZE + 1];
  char master[MAX_NAMESIZE + 1];
  WORD wdVoteNumber;
  char note[255];
};

// 帮会投票列表
const BYTE VOTELIST_UNION_PARA = 13;
struct stVoteListUnionCmd : public stUnionUserCmd
{
  stVoteListUnionCmd()
  {
    byParam = VOTELIST_UNION_PARA;
  }
  char unionName[MAX_NAMESIZE + 1];
  DWORD dwSize;
  BYTE flag; // 0为消息头1为后续消息
  stUnionVoteRecord data[0];
};

// 帮会投票消息
const BYTE VOTE_UNION_PARA = 14;
struct stVoteUnionCmd : public stUnionUserCmd
{
  stVoteUnionCmd()
  {
    byParam = VOTE_UNION_PARA;
  }
  char unionName[MAX_NAMESIZE + 1];
  BYTE bySuccess;   // 为1为成功 为0为失败
};

// 帮会设置帮会说明
const BYTE NOTE_UNION_PARA = 15;
struct stNoteUnionCmd : public stUnionUserCmd
{
  stNoteUnionCmd()
  {
    byParam = NOTE_UNION_PARA;
  }
  char noteBuf[255];
};

// 帮会成员别名设置
const BYTE CHANGE_UNION_MEMBER_ALIASNAME_PARA = 16;
struct stChangeUnionMemberAliasName : public stUnionUserCmd
{
  stChangeUnionMemberAliasName()
  {
    byParam = CHANGE_UNION_MEMBER_ALIASNAME_PARA;
  }

  char name[MAX_NAMESIZE + 1];             // 帮众姓名
  char aliasname[MAX_NAMESIZE + 1];        // 帮众别名
};

// 进入城主的帮会领地
const BYTE ENTER_UNION_CITY_AREA_PARA = 17;
struct stEnterUnionCityArea : public stUnionUserCmd
{
  stEnterUnionCityArea()
  {
    byParam = ENTER_UNION_CITY_AREA_PARA;
  }
};

enum
{
  QUESTION_UNION_MEMBER_POWER,// 请求发送权限
  RESPOND_UNION_MEMBER_POWER,//  返回某帮众权限
  SET_UNION_MEMBER_POWER,//  设置某帮众权限
};

// 请求(设置)帮众权限
const BYTE UNION_MEMBER_POWER_PARA = 18;
struct stUnionMemberPower : public stUnionUserCmd
{
  stUnionMemberPower()
  {
    byParam = UNION_MEMBER_POWER_PARA;
  }
  
  char name[MAX_NAMESIZE + 1]; // 帮众姓名
  BYTE byPower[2]; // 权限
  BYTE byType; // 消息类型
};

enum
{
  QUESTION_CITY_HOLD,// 查询城市所属
  QUESTION_CITY_DARE,// 当天城市争夺战
};

// 查询问城市帮会信息
const BYTE QUESTION_UNION_CITY_INFO_PARA = 19;
struct stQuestionUnionCityInfo : public stUnionUserCmd
{
  stQuestionUnionCityInfo()
  {
    byParam = QUESTION_UNION_CITY_INFO_PARA;
  }
  
  BYTE byType;  
};

enum
{
  COUNTRY_UNION_SORT,// 本国帮会排行榜
  WORLD_UNION_SORT,// 世界帮会排行榜
};

// 查询家族排行榜（根据声望）
const BYTE REQ_UNION_SORT_PARA = 20;
struct stReqUnionSort : public stUnionUserCmd
{
  stReqUnionSort()
  {
    byParam = REQ_UNION_SORT_PARA;
    byType = COUNTRY_UNION_SORT;
  }
  
  BYTE byType;
};

struct stUnionSortInfo
{
  char  unionName[MAX_NAMESIZE + 1];         // 帮会名称
  DWORD dwMana;        // 帮会威望
  DWORD dwOrder;        // 帮会排名
  DWORD dwCountryID;      // 国家ID
};

// 返回帮会排行榜（根据威望）
const BYTE RTN_UNION_SORT_PARA = 21;
struct stRtnUnionSort : public stUnionUserCmd
{
  stRtnUnionSort()
  {
    byParam = RTN_UNION_SORT_PARA;
    dwSize = 0;
  }
  
  BYTE byType;
  DWORD dwSize;
  stUnionSortInfo data[0];
};

// 帮会资金捐献
const BYTE CONTRIBUTE_UNION_PARA = 22;
struct stContributeUnion : public stUnionUserCmd
{
  stContributeUnion()
  {
    byParam = CONTRIBUTE_UNION_PARA;
  }
  
  DWORD dwMoney;
};

// 帮会资金查询
const BYTE REQ_UNION_MONEY_PARA = 23;
struct stReqUnionMoney : public stUnionUserCmd
{
  stReqUnionMoney()
  {
    byParam = REQ_UNION_MONEY_PARA;
  }
};

struct stUnionRecord{
  char unionName [MAX_NAMESIZE + 1];
  char master[MAX_NAMESIZE + 1];
  char note[255];
};

// 帮会投票列表
const BYTE LIST_UNION_PARA = 24;
struct stListUnionCmd : public stUnionUserCmd
{
  stListUnionCmd()
  {
    byParam = LIST_UNION_PARA;
  }
  DWORD dwSize;
  BYTE flag; // 0为消息头1为后续消息
  stUnionRecord data[0];
};

// 请求加入帮会消息
const BYTE REQUEST_JOIN_UNION_PARA = 25;
struct stRequestJoinUnionCmd : public stUnionUserCmd
{
  stRequestJoinUnionCmd()
  {
    byParam = REQUEST_JOIN_UNION_PARA;
  }
  char name[MAX_NAMESIZE + 1]; //发给服务器的时候填对方会长的名字，服务器发出来的时候填的是请求人的名字
  BYTE status;
};

// 放弃占领城市
const BYTE REQUEST_ABJURATION_CITY_PARA = 26;
struct stRequestAbjurationCitynCmd : public stUnionUserCmd
{
  stRequestAbjurationCitynCmd()
  {
    byParam = REQUEST_ABJURATION_CITY_PARA;
  }
};

// 请求帮会名称
const BYTE REQ_UNION_NAME_PARA = 27;
struct stReqUnionNameCmd : public stUnionUserCmd
{
  stReqUnionNameCmd()
  {
    byParam = REQ_UNION_NAME_PARA;
    dwUnionID = 0;
  }

  DWORD dwUnionID;
};

// 返回帮会名称
const BYTE RTN_UNION_NAME_PARA = 28;
struct stRtnUnionNameCmd : public stUnionUserCmd
{
  stRtnUnionNameCmd()
  {
    byParam = RTN_UNION_NAME_PARA;
    bzero(name,MAX_NAMESIZE);
    dwUnionID = 0;
  }

  DWORD dwUnionID;
  char name[MAX_NAMESIZE + 1];
};

// 请求帮会名称列表
const BYTE REQ_UNION_NAME_LIST_PARA = 29;
struct stReqUnionNameLlistCmd : public stUnionUserCmd
{
  stReqUnionNameLlistCmd()
  {
    byParam = REQ_UNION_NAME_LIST_PARA;
    num=0;
  }
  BYTE num;
  DWORD dwUnionID[0];
};

// 返回帮会名称列表
const BYTE RTN_UNION_NAME_LIST_PARA = 30;
struct stRtnUnionNameListCmd : public stUnionUserCmd
{
  stRtnUnionNameListCmd()
  {
    byParam = RTN_UNION_NAME_LIST_PARA;
    num=0;
  }
  BYTE num;
  struct
  {
    DWORD dwUnionID;
    char name[MAX_NAMESIZE + 1];
  } list[0];
};

// 城主任命捕头
#define APPOINT_CITY_CATCHER_PARA  31
struct stAppointCityCatcherCmd : public stUnionUserCmd
{
  stAppointCityCatcherCmd()
  {
    byParam = APPOINT_CITY_CATCHER_PARA;
    bzero(name,sizeof(name));
  }

  char name[MAX_NAMESIZE + 1];
};

// 撤消捕头
#define CANCEL_CITY_CATCHER_PARA  32
struct stCancelCityCatcherCmd : public stUnionUserCmd 
{
  stCancelCityCatcherCmd()
  {
    byParam = CANCEL_CITY_CATCHER_PARA;
  }
};

//////////////////////////////////////////////////////////////
// 帮会指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 国家指令定义开始
//////////////////////////////////////////////////////////////

struct stCountryUserCmd : public stNullUserCmd
{
  stCountryUserCmd()
  {
    byCmd = COUNTRY_USERCMD;
  }
};

// 变更国籍
const BYTE CHANGE_COUNTRY_PARA = 1;
struct stChangeCountryCmd : public stCountryUserCmd
{
    stChangeCountryCmd()
    {
      byParam = CHANGE_COUNTRY_PARA;
    }

    DWORD dwToCountryID; // 变更到国家的ID
};

enum 
{
  REQUEST_BATTLEFIELD_COUNTRY_LIST,// 请求战场列表
  REQUEST_DARE_COUNTRY_LIST,// 请求战场列表
};

// 请求战场列表
const BYTE REQUEST_DARE_COUNTRY_PARA =2;
struct stRequestDareCountryCmd : public stCountryUserCmd
{
  stRequestDareCountryCmd()
  {
    byParam = REQUEST_DARE_COUNTRY_PARA;
  }

  BYTE byType; // 0,请求战场列表，1，请求挑战列表
};

struct stCountryInfo
{
  DWORD dwID;   // 国家ID
  BYTE  byType;  // 0,参战国，1，第三方国
};

// 返回战场列表
const BYTE RETURN_DARE_COUNTRY_PARA = 3;
struct stReturnDareCountryCmd : public stCountryUserCmd
{
  stReturnDareCountryCmd()
  {
    byParam = RETURN_DARE_COUNTRY_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize; // 战场个数
  BYTE  byType; // 0,战场列表，挑战列表
  
  stCountryInfo country_list[0]; //战场国家ID数组
};

// 请求传送到指定战场
const BYTE TRANS_DARE_COUNTRY_PARA = 4;
struct stTransDareCountryCmd : public stCountryUserCmd
{
  stTransDareCountryCmd()
  {
    byParam = TRANS_DARE_COUNTRY_PARA;
    dwCountryID = 0;
  }

  DWORD dwCountryID;
};

// 请求国战挑战
const BYTE DARE_COUNTRY_FORMAL_PARA = 5;
struct stDareCountryFormalCmd : public stCountryUserCmd
{
  stDareCountryFormalCmd()
  {
    byParam = DARE_COUNTRY_FORMAL_PARA;
  }

  DWORD dwCountryID; // 要挑战的国家
};

enum
{
  DARE_RECORD_RESULT,// 对战结果记录
  DARE_RECORD_STAT,// 对战结果统计
  DARE_RECORD_PLAN,// 当天对战安排
};

// 请求记录
const BYTE REQUEST_DARE_RECORD_PARA = 6;
struct stRequestDareRecordCmd : public stCountryUserCmd
{
  stRequestDareRecordCmd()
  {
    byParam = REQUEST_DARE_RECORD_PARA;
  }

  BYTE byType;  // 查询类型
};

struct stDareResult
{
  DWORD  dareTime;      // 对战时间
  DWORD  attCountry;    // 挑战国ID
  DWORD  defCountry;    // 防御国ID
  BYTE   byResult;      // 0,挑战国胜(攻陷对方皇城)，1,挑战国败(时间到了，却未攻陷)，2,防御国反攻成功(攻陷挑战国皇城)
  char   attKingName[MAX_NAMESIZE + 1];
  char   defKingName[MAX_NAMESIZE + 1];
};

// 对战结果
const BYTE RETURN_DARE_RECORD_RESULT_PARA = 7;
struct stReturnDareRecordResultCmd : public stCountryUserCmd
{
  stReturnDareRecordResultCmd()
  {
    byParam = RETURN_DARE_RECORD_RESULT_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize;
  stDareResult dare_result[0];
};

struct stDareStat
{
  DWORD dwCountry;  // 国家ID
  DWORD dwFormalWin;  // 正式国战胜利次数
  DWORD dwFormalFail;  // 正式国战失败次数
  DWORD dwAnnoyWin;  // 骚扰国战胜利次数
  DWORD dwAnnoyFail;  // 骚扰国战失败次数
};
// 对战统计
const BYTE RETURN_DARE_RECORD_STAT_PARA =8;
struct stReturnDareRecordStatCmd : public stCountryUserCmd
{
  stReturnDareRecordStatCmd()
  {
    byParam = RETURN_DARE_RECORD_STAT_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize;
  stDareStat dare_stat[0];
};

struct stDarePlan
{
  DWORD planTime;
  DWORD attCountry;  // 挑战国
  DWORD defCountry;  // 防御国
};

// 对战计划
const BYTE RETURN_DARE_RECORD_PLAN_PARA =9;
struct stReturnDareRecordPlanCmd : public stCountryUserCmd
{
  stReturnDareRecordPlanCmd()
  {
    byParam = RETURN_DARE_RECORD_PLAN_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize;
  stDarePlan dare_plan[0];
};

// 叛国（变为无国籍）
const BYTE CANCEL_COUNTRY_PARA = 10;
struct stCancelCountryCmd : public stCountryUserCmd
{
    stCancelCountryCmd()
    {
      byParam = CANCEL_COUNTRY_PARA;
    }
};

// 申请加入国籍
const BYTE APPLY_COUNTRY_PARA = 11;
struct stApplyCountryCmd : public stCountryUserCmd
{
    stApplyCountryCmd()
    {
      byParam = APPLY_COUNTRY_PARA;
    }

    DWORD dwToCountryID; // 申请加入的国籍
};

/// 税率查询
const BYTE TAX_COUNTRY_PARA = 12;
struct stTaxCountryUserCmd:public stCountryUserCmd
{
  stTaxCountryUserCmd()
  {
    byParam = TAX_COUNTRY_PARA;
  }
  DWORD dwCountry;
  BYTE byTax; 
};

/// 国库查询
const BYTE FISK_COUNTRY_PARA = 13;
struct stFiskCountryUserCmd:public stCountryUserCmd
{
  stFiskCountryUserCmd()
  {
    byParam = FISK_COUNTRY_PARA;
    qwGold = 0;
    qwMaterial = 0;  
    qwStock = 0;
  }
  
  DWORD dwCountry;
  QWORD qwGold; 
  QWORD qwMaterial; // 物资
  QWORD qwStock;    // 原料
};

/// 税率设置
const BYTE SETTAX_COUNTRY_PARA = 14;
struct stSetTaxCountryUserCmd:public stCountryUserCmd
{
  stSetTaxCountryUserCmd()
  {
    byParam = SETTAX_COUNTRY_PARA;
  }
  DWORD dwCountry;
  BYTE byTax; 
};

struct stCountryStar
{
  DWORD dwCountry;
  DWORD dwStar;
};

/// 设置国家星号
const BYTE UPDATE_COUNTRY_STAR = 15;
struct stUpdateCountryStarCmd : public stCountryUserCmd
{
  stUpdateCountryStarCmd()
  {
    byParam = UPDATE_COUNTRY_STAR;
    dwSize = 0;
  }
  DWORD dwSize;
  stCountryStar data[0];
};


/// 国家捐献
const BYTE CONTRIBUTE_COUNTRY_MATERIAL = 16;
struct stContributeCountryMaterialCmd : public stCountryUserCmd
{
  stContributeCountryMaterialCmd()
  {
    byParam = CONTRIBUTE_COUNTRY_MATERIAL;
    itemID = 0;
  }
  DWORD itemID;
};

/// 国战状态设置
const BYTE SETCOUNTRY_DARE_PARA = 17;
struct stSetCountryDareUserCmd:public stCountryUserCmd
{       
  stSetCountryDareUserCmd()
  {
    byParam = SETCOUNTRY_DARE_PARA;
    dwCountry = 0;
    byStatus = 0;
    byResult = 0;
  }

  
  DWORD dwCountry; // 敌对国家ID
  BYTE  byStatus; // 1为进入国战，0为退出国战
  BYTE  byResult; // 对战结果，1为胜方，0为失败方,当byStatus为0时，该字段有意义
};      

/// 更新国王信息
const BYTE UPDATE_COUNTRY_KING = 18;
struct stUpdateCountryKingUserCmd : public stCountryUserCmd
{
  stUpdateCountryKingUserCmd()
  {
    byParam = UPDATE_COUNTRY_KING;
    bzero(kingName,sizeof(kingName));
    isEmperor = 0;
  }
  char   kingName[MAX_NAMESIZE + 1];
  BYTE   isEmperor; // 0不是皇帝所在国,1是皇帝所在国
};

enum
{
  ANSWER_COUNTRY_DARE_QUESTION,
  ANSWER_COUNTRY_DARE_NO,
  ANSWER_COUNTRY_DARE_YES
};
/// 国战应答
const BYTE ANSWER_COUNTRY_DARE_PARA= 19;
struct stAnswerCountryDareUserCmd : public stCountryUserCmd
{
  stAnswerCountryDareUserCmd()
  {
    byParam = ANSWER_COUNTRY_DARE_PARA;
    byStatus = ANSWER_COUNTRY_DARE_QUESTION;
  }
  
  BYTE byStatus;
};

/// 选择要在国战时传送到边境的玩家等级
const BYTE SELECT_TRANS_LEVEL= 20;
struct stSelectTransLevelUserCmd : public stCountryUserCmd
{
  stSelectTransLevelUserCmd()
  {
    byParam = SELECT_TRANS_LEVEL;
    dwLevel = 0;
  }

  DWORD dwLevel;//大于等于该等级
};

//国王禁言一个玩家
#define FORBID_TALK_COUNTRY_PARA 21
struct stForbidTalkCountryUserCmd : public stCountryUserCmd
{
  stForbidTalkCountryUserCmd()
  {
    byParam = FORBID_TALK_COUNTRY_PARA;
    bzero(name,MAX_NAMESIZE);
  }
  char name[MAX_NAMESIZE + 1];
};

enum
{
  WAIT_TECH_TYPE = 1,// 投票选出的科技，等待国王选择官员
  ACTIVE_TECH_TYPE = 2,// 正在进行升级
  FINISH_TECH = 3,// 已经完成升级，可以打造相应装备(包括等级大于0的所有状态的科技)
};

// 获取指定类型科技列表
#define REQ_TECH_PARA 22
struct stReqTechUserCmd : public stCountryUserCmd
{
  stReqTechUserCmd()
  {
    byParam = REQ_TECH_PARA;
    dwType = 0;
  }
  
  DWORD dwType; // 1为等研究的科技，2，正在升级的科技,3，已完成的科技
};

struct stTechItem
{
  DWORD dwOption;
  char  szOptionDesc[MAX_NAMESIZE + 1];
  char  szResearchName[MAX_NAMESIZE + 1];
  DWORD dwLevel;
  DWORD dwProgress;
};

// 返回指定类型科技列表
#define RTN_TECH_PARA 23
struct stRtnTechUserCmd : public stCountryUserCmd
{
  stRtnTechUserCmd()
  {
    byParam = RTN_TECH_PARA;
    dwSize = 0;
    dwType = 0;
  }
  
  DWORD dwType;
  DWORD dwSize;
  stTechItem data[0];
};

// 获取待选官员列表
#define REQ_WAIT_OFFICIAL_PARA 24
struct stReqWaitOfficialUserCmd : public stCountryUserCmd
{
  stReqWaitOfficialUserCmd()
  {
    byParam = REQ_WAIT_OFFICIAL_PARA;
  }
};

struct stWaitOfficialItem
{
  DWORD dwCharID;
  char  szName[MAX_NAMESIZE + 1];
};

// 返回待选官员列表
#define RTN_WAIT_OFFICIAL_PARA 25
struct stRtnWaitOfficialUserCmd : public stCountryUserCmd
{
  stRtnWaitOfficialUserCmd()
  {
    byParam = RTN_WAIT_OFFICIAL_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize;
  stWaitOfficialItem data[0];
};

// 设置科技研究员
#define SET_TECH_SEARCH_PARA 26
struct stSetTechSearchUserCmd : public stCountryUserCmd
{
  stSetTechSearchUserCmd()
  {
    byParam = SET_TECH_SEARCH_PARA;
    dwOption = 0;
    dwCharID = 0;
  }

  DWORD dwOption;
  DWORD dwCharID;
};

// 提升科技完成度
#define UP_TECH_DEGREE_PARA 27
struct stUpTechDegreeUserCmd : public stCountryUserCmd
{
  stUpTechDegreeUserCmd()
  {
    byParam = UP_TECH_DEGREE_PARA;
    dwOption = 0;
  }

  DWORD dwOption;
};

enum
{
  QUESTION_CONFIRM_SEARCHER,// 询问是否同意成为研究员
  YES_CONFIRM_SEARCHER,// 同意成为研究员
  NO_CONFIRM_SEARCHER // 不同意成为研究员
};

// 询问是否同意成为研究员
#define CONFIRM_SEARCHER_PARA 28
struct stConfirmSearcherUserCmd : public stCountryUserCmd
{
  stConfirmSearcherUserCmd()
  {
    byParam = CONFIRM_SEARCHER_PARA;
    byStatus = QUESTION_CONFIRM_SEARCHER;
    dwOption = 0;
  }
      
  DWORD dwOption;  // 科技ID  
  BYTE byStatus;
};

// 该国人不能登陆
#define  DISENABLEL_OGIN_COUNTRY_PARA  29 
enum  FALSE_COUNTRY_STATUS
{
  FALSE_REGISTER_COUNTRY,//return when register fail 
  FALSE_LOGIN_COUNTRY     // return when login fail 
};
struct stDisableLoginCountryCmd : public stCountryUserCmd
{
  stDisableLoginCountryCmd()
  {
    byParam = DISENABLEL_OGIN_COUNTRY_PARA;
  }
  FALSE_COUNTRY_STATUS status;
};

// 取消科技研究员
#define CANCEL_TECH_SEARCH_PARA 30
struct stCancelTechSearchUserCmd : public stCountryUserCmd
{
  stCancelTechSearchUserCmd()
  {
    byParam = CANCEL_TECH_SEARCH_PARA;
    dwOption = 0;
  }

  DWORD dwOption;
};

// 申请国战反攻
#define ANTI_DARE_COUNTRY_FORMAL_PARA  31
struct stAntiDareCountryFormalCmd : public stCountryUserCmd
{
  stAntiDareCountryFormalCmd()
  {
    byParam = ANTI_DARE_COUNTRY_FORMAL_PARA;
  }

  DWORD dwCountryID; // 要挑战的国家
};

// 发布国家公告
#define COUNTRY_NOTE_PARA  32
struct stCountryNoteCmd : public stCountryUserCmd
{
  stCountryNoteCmd()
  {
    byParam = COUNTRY_NOTE_PARA;
  }

  char note[255];
};

// 请求国家公告
#define REQ_COUNTRY_NOTE_PARA  33
struct stReqCountryNoteCmd : public stCountryUserCmd
{
  stReqCountryNoteCmd()
  {
    byParam = REQ_COUNTRY_NOTE_PARA;
  }
};

// 国王处罚玩家
#define KING_PUNISH_COUNTRY_PARA  34
struct stKingPunishCountryCmd : public stCountryUserCmd
{
  stKingPunishCountryCmd()
  {
    byParam = KING_PUNISH_COUNTRY_PARA;
  }
  char name[MAX_NAMESIZE + 1];//指定玩家名字
  DWORD method;//处罚方式 1:禁言 2:关监狱
};

// 皇帝处罚玩家
#define EMPEROR_PUNISH_COUNTRY_PARA  35
struct stEmperorPunishCountryCmd : public stCountryUserCmd
{
  stEmperorPunishCountryCmd()
  {
    byParam = EMPEROR_PUNISH_COUNTRY_PARA;
  }
  char name[MAX_NAMESIZE + 1];//指定玩家名字
  DWORD method;//处罚方式 1:禁言 2:关监狱
};

// 请求大将军的信息
#define REQ_GEN_COUNTRY_PARA  36
struct stReqGenCountryCmd : public stCountryUserCmd
{
  stReqGenCountryCmd()
  {
    byParam = REQ_GEN_COUNTRY_PARA;
  }
};

// 返回大将军的信息
#define RET_GEN_COUNTRY_PARA  37
struct stRetGenCountryCmd : public stCountryUserCmd
{
  stRetGenCountryCmd()
  {
    byParam = RET_GEN_COUNTRY_PARA;
  }
  DWORD level;
  DWORD exp;
  DWORD maxExp;
};

// 任命捕头
#define APPOINT_CATCHER_PARA  38
struct stAppointCatcherCmd : public stCountryUserCmd
{
  stAppointCatcherCmd()
  {
    byParam = APPOINT_CATCHER_PARA;
    bzero(name,sizeof(name));
  }

  char name[MAX_NAMESIZE + 1];
};

// 撤消捕头
#define CANCEL_CATCHER_PARA  39
struct stCancelCatcherCmd : public stCountryUserCmd
{
  stCancelCatcherCmd()
  {
    byParam = CANCEL_CATCHER_PARA;
  }
};

// 任命外交官
#define APPOINT_DIPLOMAT_PARA  40
struct stAppointDiplomatCmd : public stCountryUserCmd
{
  stAppointDiplomatCmd()
  {
    byParam = APPOINT_DIPLOMAT_PARA;
    bzero(name,sizeof(name));
  }

  char name[MAX_NAMESIZE + 1];
};

// 撤消外交官
#define CANCEL_DIPLOMAT_PARA  41
struct stCancelDiplomatCmd : public stCountryUserCmd
{
  stCancelDiplomatCmd()
  {
    byParam = CANCEL_DIPLOMAT_PARA;
  }
};

// 查询国家强弱
#define REQUEST_COUNTRY_POWER_PARA  42
struct stRequestCountryPowerCmd : public stCountryUserCmd
{
  stRequestCountryPowerCmd()
  {
    byParam = REQUEST_COUNTRY_POWER_PARA;
  }
};

// 返回国家强弱
#define RETURN_COUNTRY_POWER_PARA  43
struct stReturnCountryPowerCmd : public stCountryUserCmd
{
  stReturnCountryPowerCmd()
  {
    byParam = RETURN_COUNTRY_POWER_PARA;
  }
  BYTE country[2];
};

// 领取每日皇帝的奖励
#define REQ_DAILY_EMPEROR_MONEY 44
struct stReqDailyEmperorMoneyCmd : public stCountryUserCmd
{
  stReqDailyEmperorMoneyCmd()
  {
    byParam = REQ_DAILY_EMPEROR_MONEY;
  }
};

// 请求国王排行榜
#define REQ_KING_LIST_PARA  45
struct stReqKingListCmd : public stCountryUserCmd
{
  stReqKingListCmd()
  {
    byParam = REQ_KING_LIST_PARA;
  }
};

struct _KingListItem
{
  char  king_name[MAX_NAMESIZE + 1]; // 国王名称
  WORD  online_time; //在线时间 单位为小时
  DWORD country_id; // 国家ID
};

// 返回国王排行榜
#define RTN_KING_LIST_PARA  46
struct stRtnKingListCmd : public stCountryUserCmd
{
  stRtnKingListCmd()
  {
    byParam = RTN_KING_LIST_PARA;
    size = 0;
  }
  BYTE size;
  _KingListItem data[0];
};
 
// 请求城市占领者
#define REQ_CITY_OWNER_LIST_PARA  47
struct stReqCityOwnerListCmd : public stCountryUserCmd
{
  stReqCityOwnerListCmd()
  {
    byParam = REQ_CITY_OWNER_LIST_PARA;
  }
};

// 返回城市占领者列表
#define RTN_CITY_OWNER_LIST_PARA  48
struct stRtnCityOwnerListCmd : public stCountryUserCmd
{
  stRtnCityOwnerListCmd()
  {
    byParam = RTN_CITY_OWNER_LIST_PARA;
    size = 0;
  }
  WORD size;
  struct
  {
    char cityName[MAX_NAMESIZE + 1];
    char unionName[MAX_NAMESIZE + 1];
  }list[0];
};
 
// 请求城市占领者
#define REQ_NPC_OWNER_LIST_PARA  49
struct stReqNpcOwnerListCmd : public stCountryUserCmd
{
  stReqNpcOwnerListCmd()
  {
    byParam = REQ_NPC_OWNER_LIST_PARA;
  }
};
// 返回城市占领者
#define RTN_NPC_OWNER_LIST_PARA  50
struct stRtnNpcOwnerListCmd : public stCountryUserCmd
{
  stRtnNpcOwnerListCmd()
  {
    byParam = RTN_NPC_OWNER_LIST_PARA;
    size=0;
  }
  WORD size;
  struct
  {
    DWORD npcID;//npc的数据id
    char mapName[MAX_NAMESIZE + 1];//地图名称
    WORD x;    //所在位置
    WORD y;    //所在位置
    char septName[MAX_NAMESIZE + 1];//占领的家族名称
  }list[0];
};
//////////////////////////////////////////////////////////////
// 国家指令定义结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// 投票指令定义开始
//////////////////////////////////////////////////////////////
enum
{
  TECH_VOTE // 科技投票
};

struct stVoteUserCmd : public stNullUserCmd
{
    stVoteUserCmd()
    {
        byCmd = VOTE_USERCMD;
    }
};

// 请求投票列表
#define REQUEST_VOTE_LIST_PARA 1
struct stRequestVoteListUserCmd : public stVoteUserCmd
{
  stRequestVoteListUserCmd()
  {
    byParam = REQUEST_VOTE_LIST_PARA;
    byType = TECH_VOTE;
  }

  BYTE byType; // 投票类型
};

struct stVoteItem
{
  DWORD dwOption; // 选项编号
  DWORD dwBallot; // 选项当前投票数
  char  szOptionDesc[MAX_NAMESIZE + 1];
};

// 返回投票列表
#define RETURN_VOTE_LIST_PARA 2
struct stReturnVoteListUserCmd : public stVoteUserCmd
{
  stReturnVoteListUserCmd()
  {
    byParam = RETURN_VOTE_LIST_PARA;
    dwSize = 0;
    byType = TECH_VOTE;
    dwVoteID = 0;
  }

  DWORD dwVoteID;
  BYTE byType;
  DWORD dwSize;
  stVoteItem data[0];
};

// 提交投票
#define COMMIT_VOTE_PARA 3
struct stCommitVoteUserCmd : public stVoteUserCmd
{
  stCommitVoteUserCmd()
  {
    byParam = COMMIT_VOTE_PARA;
    dwVoteID = 0;
    dwOption = 0;
  }

  DWORD dwVoteID; // 该次投票的ID
  DWORD dwOption; // 该次提交的选项
};
//////////////////////////////////////////////////////////////
// 投票指令定义结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// 军队指令定义开始
//////////////////////////////////////////////////////////////
struct stArmyUserCmd : public stNullUserCmd
{
    stArmyUserCmd()
    {
        byCmd = ARMY_USERCMD;
    }
};

// 创建军队
#define CREATE_ARMY_PARA 1
struct stCreateArmyUserCmd : public stArmyUserCmd
{
  stCreateArmyUserCmd()
  {
    byParam = CREATE_ARMY_PARA;
    bzero(armyName,sizeof(armyName));
    bzero(genName,sizeof(genName));
  }

  char armyName[8+1]; // 军队名称限定为4个汉字
  char genName[MAX_NAMESIZE + 1];
};

// 请求待选将军列表
#define REQ_WAIT_GEN_PARA 2
struct stReqWaitGenUserCmd : public stArmyUserCmd
{
  stReqWaitGenUserCmd()
  {
    byParam = REQ_WAIT_GEN_PARA;
  }
};

struct stWaitGenItem
{
  DWORD dwCharID;
  char  szName[MAX_NAMESIZE + 1];
};

// 返回候选将军列表
#define RTN_WAIT_GEN_PARA 3
struct stRtnWaitGenUserCmd : public stArmyUserCmd
{
  stRtnWaitGenUserCmd()
  {
    byParam = REQ_WAIT_GEN_PARA;
    dwSize = 0;
  }

  DWORD dwSize;
  stWaitGenItem data[0];
};

enum
{
  QUESTION_ARMY_GEN,// 询问是否愿意成为将军
  YES_ARMY_GEN,// 同意成为将军
  NO_ARMY_GEN,// 拒绝成为将军
};

// 询问是否同意成为将军
#define REQ_ARMY_GEN_PARA 4
struct stReqArmyGenUserCmd : public stArmyUserCmd
{
  stReqArmyGenUserCmd()
  {
    byParam = REQ_ARMY_GEN_PARA;
    byStatus = QUESTION_ARMY_GEN;
  }

  BYTE byStatus;
  
};

enum
{
  COUNTRY_ARMY_LIST,// 用于国家对话框，显示全国军队列表
  CITY_ARMY_LIST,// 用于NPC对话，显示本城军队列表
};
// 请求军队列表
#define REQ_ARMY_LIST_PARA 5
struct stReqArmyListUserCmd : public stArmyUserCmd
{
  stReqArmyListUserCmd()
  {
    byParam = REQ_ARMY_LIST_PARA;
    byType = COUNTRY_ARMY_LIST;
  }

  BYTE byType;
};

struct stArmyBaseInfo
{
  DWORD dwArmyID;
  char  name[MAX_NAMESIZE + 1]; // 军队名称
  char  cityname[MAX_NAMESIZE + 1]; // 所属城市
  char  genname[MAX_NAMESIZE + 1]; // 将军姓名
  DWORD dwCapNum; // 队长人数
};

// 返回军队列表
#define RTN_ARMY_LIST_PARA 6
struct stRtnArmyListUserCmd : public stArmyUserCmd
{
  stRtnArmyListUserCmd()
  {
    byParam = RTN_ARMY_LIST_PARA;
    dwSize = 0;
  }

  DWORD dwSize;
  BYTE  byType;
  stArmyBaseInfo data[0];
};

// 请求军队详细信息
#define REQ_ARMY_SPEC_PARA 7
struct stReqArmySpecUserCmd : public stArmyUserCmd
{
  stReqArmySpecUserCmd()
  {
    byParam = REQ_ARMY_SPEC_PARA;
    dwArmyID = 0;
  }
  
  DWORD dwArmyID;
};

struct stCaptainBase
{
  char name[MAX_NAMESIZE + 1];
  DWORD dwCharID;
};
// 返回军队详细信息
#define RTN_ARMY_SPEC_PARA 8
struct stRtnArmySpecUserCmd : public stArmyUserCmd
{
  stRtnArmySpecUserCmd()
  {
    byParam = RTN_ARMY_SPEC_PARA;
    dwSize = 0;
    bzero(name,MAX_NAMESIZE);
    bzero(cityname,MAX_NAMESIZE);
    bzero(genname,MAX_NAMESIZE);
  }

  char name[MAX_NAMESIZE + 1]; // 军队名
  char cityname[MAX_NAMESIZE + 1]; // 城市名
  char genname[MAX_NAMESIZE + 1]; // 将军名
  DWORD dwSize;
  stCaptainBase data[0];
};

// 离开军队
#define EXIT_ARMY_PARA 9
struct stExitArmyUserCmd : public stArmyUserCmd
{
  stExitArmyUserCmd()
  {
    byParam = EXIT_ARMY_PARA;
  }
};  

// 解散军队
#define REMOVE_ARMY_PARA 10
struct stRemoveArmyUserCmd : public stArmyUserCmd
{
  stRemoveArmyUserCmd()
  {
    byParam = REMOVE_ARMY_PARA;
    dwArmyID = 0;
  }

  DWORD dwArmyID;
};

// 更改军队名称
#define CHANGE_ARMY_NAME_PARA 11
struct stChangeArmyNameUserCmd : public stArmyUserCmd
{
  stChangeArmyNameUserCmd()
  {
    byParam = CHANGE_ARMY_NAME_PARA;
    dwArmyID = 0;
    bzero(newArmyName,MAX_NAMESIZE);
  }

  DWORD dwArmyID;
  char  newArmyName[MAX_NAMESIZE + 1];
};

enum ADD_ARMY_CAPTAIN{
  QUESTION_CAPTAIN,// 发出询问
  ANSWER_CAPTAIN_YES,// 确认邀请
  ANSWER_CAPTAIN_NO,// 拒绝邀请
};
// 招收队长
#define ADD_ARMY_CAPTAIN_PARA 12
struct stAddArmyCaptainUserCmd : public stArmyUserCmd
{
  stAddArmyCaptainUserCmd()
  {
    byParam = ADD_ARMY_CAPTAIN_PARA;
    bzero(capName,MAX_NAMESIZE);
    bzero(armyName,MAX_NAMESIZE);
    capID = 0;
    armyID = 0;
    byState = QUESTION_CAPTAIN;
  }

  char capName[MAX_NAMESIZE + 1]; // 被邀请的人
  char armyName[MAX_NAMESIZE + 1]; // 邀请的军队名称
  DWORD armyID; // 军队ID
  DWORD capID; // 被邀请人ID
  BYTE byState; // 参见 enum ADD_ARMY_CAPTAIN
};

// 开除队长
#define FIRE_ARMY_CAPTAIN_PARA 13
struct stFireArmyCaptainUserCmd : public stArmyUserCmd
{
  stFireArmyCaptainUserCmd()
  {
    byParam = FIRE_ARMY_CAPTAIN_PARA;
    dwUserID = 0;
  }

  DWORD dwUserID; // 待开除的队长ID,通过军队详细信息获得
};

/*// 更改军队将军
#define CHANGE_ARMY_GEN_PARA 12
struct stChangeArmyGenUserCmd : public stArmyUserCmd
{
  stChangeArmyGenUserCmd()
  {
    byParam = CHANGE_ARMY_GEN_PARA;
    dwArmyID = 0;
    bzero(newArmyGen,MAX_NAMESIZE);
  }

  DWORD dwArmyID;
  char  newArmyGen[MAX_NAMESIZE + 1];
};
*/
//////////////////////////////////////////////////////////////
// 军队指令定义结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// 护宝指令定义开始
//////////////////////////////////////////////////////////////
struct stGemUserCmd : public stNullUserCmd
{
    stGemUserCmd()
    {
        byCmd = GEM_USERCMD;
    }
};

// 领取龙精
#define REQUEST_DRAGON_PARA 1
struct stReqDragonUserCmd : public stGemUserCmd
{
  stReqDragonUserCmd()
  {
    byParam = REQUEST_DRAGON_PARA;
  }
};

// 领取虎魄
#define REQUEST_TIGER_PARA 2
struct stReqTigerUserCmd : public stGemUserCmd
{
  stReqTigerUserCmd()
  {
    byParam = REQUEST_TIGER_PARA;
  }
};

//////////////////////////////////////////////////////////////
// 护宝指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 战斗指令定义开始
//////////////////////////////////////////////////////////////

// 对战类型定义
enum
{
  UNION_DARE  = 0,// 帮会对战 
  SCHOOL_DARE  = 1,// 师门对战
  SEPT_DARE  = 2,// 家族对战
  SEPT_NPC_DARE   = 3,// 家族NPC争夺战
  UNION_CITY_DARE  = 4,// 帮会夺城战
  COUNTRY_FORMAL_DARE = 5,// 正式国战
  COUNTRY_FORMAL_ANTI_DARE = 6,// 正式国战反攻
  EMPEROR_DARE  = 7,// 皇城争夺战
};

struct stDareUserCmd : public stNullUserCmd
{
    stDareUserCmd()
    {
        byCmd = DARE_USERCMD;
    }
};

enum 
{
  DARE_QUESTION,// 发起或询问挑战
  DARE_YES,// 接受挑战
  DARE_NO         // 拒绝挑战
};

enum
{
  DARE_REPUTE_ONE = 1,
  DARE_REPUTE_TWO = 2,
  DARE_REPUTE_THREE = 3,
  DARE_REPUTE_FOUR = 4,
};

// 发起挑战
const BYTE ACTIVE_DARE_PARA = 1;
struct stActiveDareCmd : public stDareUserCmd
{
    stActiveDareCmd()
    {
      byParam = ACTIVE_DARE_PARA;
      dwWarID = 0;
      dwMsgType = DARE_QUESTION;
      byDareRepute = 0;
    }
    
    char name[MAX_NAMESIZE + 1]; // 挑战者姓名
    char fromRelationName[MAX_NAMESIZE + 1]; // 挑战者帮会或师门或家族名称
    char toRelationName[MAX_NAMESIZE + 1];  //被挑战者帮会或师门或家族名称
    DWORD dwWarID;    // 交战ID
    DWORD dwDareType; // 挑战类型: 帮会、师门、家族
    DWORD dwMsgType;  // 挑战者发起挑战者无意义。服务器收到该命令后，置为DARE_QUESTION，转发给有权限的相应玩家。
                      // 客户端对玩家提问后，返回DARE_YES或DARE_NO.结构其它信息保留。
    BYTE byDareRepute; // 家族随意战时，下多少声望做为赌资类型，类型有四种:1,2,3,4 分别对应1、5、10、20声望
};


enum
{
    NOTIFY_NO_EXIST,// 帮会或师门或家族名不存在
};

// 通知消息
const BYTE NOTIFY_DARE_PARA = 2;
struct stNotifyDare : public stDareUserCmd
{
    stNotifyDare()
    {
      byParam = NOTIFY_DARE_PARA;
    }

    DWORD dwType;       // 战斗类型
    DWORD dwNotify;     // 通知类型
};

// 通知国战胜利次数的改变
const BYTE CHANGE_COUNTRY_STAR_PARA = 3;
struct stChangeCountryStar : public stDareUserCmd
{
  stChangeCountryStar()
  {
    byParam = CHANGE_COUNTRY_STAR_PARA;
  }
  
  DWORD dwStar; // 当前胜利次数
};

// 请求挑战列表
const BYTE QUERY_DARE_LIST_PARA = 4;
struct stQueryDareList : public stDareUserCmd
{
  stQueryDareList()
  {
    byParam = QUERY_DARE_LIST_PARA;
  }
  
  BYTE byType; // UNION_DARE,SEPT_DARE
};

struct stDareList
{
  char name[MAX_NAMESIZE + 1];
};

// 通知可以挑战的社会关系列表
const BYTE SEND_DARE_LIST_PARA = 5;
struct stSendDareList : public stDareUserCmd
{
  stSendDareList()
  {
    byParam = SEND_DARE_LIST_PARA;
  }

  DWORD dwSize;
  BYTE  byType;
  struct stDareList dare_list[0];
};

// 发起帮会夺城挑战
const BYTE ACTIVE_UNION_CITY_DARE_PARA = 6;
struct stActiveUnionCityDare : public stDareUserCmd
{
  stActiveUnionCityDare()
  {
    byParam = ACTIVE_UNION_CITY_DARE_PARA;
    toCountryID = 0;
  }

  DWORD toCountryID;
};

// 领取当天税收
const BYTE GET_UNION_CITY_TAX_PARA = 7;
struct stGetUnionCityTax : public stDareUserCmd
{
  stGetUnionCityTax()
  {
    byParam = GET_UNION_CITY_TAX_PARA;
  }
};

// 通知客户端进入皇城争夺战区域
const BYTE ENTER_EMPEROR_DARE_ZONE = 8;
struct stEnterEmperorDareZone : public stDareUserCmd
{
  stEnterEmperorDareZone()
  {
    byParam = ENTER_EMPEROR_DARE_ZONE;
    dwDefCountryID = 0;
    state = 0;
  }

  DWORD dwDefCountryID; // 守方国家ID
  BYTE state; // 0,为退出,1,为进入
};

// 用户上线,通知客户端,正在进行皇城争夺战
const BYTE ENTER_EMPEROR_DARE_ACTIVE = 9;
struct stEnterEmperorDareActive : public stDareUserCmd
{
  stEnterEmperorDareActive()
  {
    byParam = ENTER_EMPEROR_DARE_ACTIVE;
  }
};

enum enmCallDutyType
{
  CALL_DUTY_KING,//国王
  CALL_DUTY_UNION,//帮主
  CALL_DUTY_SEPT,//族长
  CALL_DUTY_NUM
};
enum enmCallDutyPipeline
{
  PIPELINE_CALL = 0,//召唤
  PIPELINE_REFUSE,//拒绝
  PIPELINE_AGREE,//同意
  PIPELINE_NUM
};

//国王、帮主、族长拉人
const BYTE DARE_CALL_DUTY = 10;
struct stDareCallDuty : public stDareUserCmd
{
  stDareCallDuty()
  {
    leaderTempID=0;
    byParam = DARE_CALL_DUTY;
    byCallerType = CALL_DUTY_NUM;
    byPipeline = PIPELINE_NUM;
  }
  DWORD  leaderTempID;      //领导tempid
  BYTE  byCallerType;      //enmCallDutyType
  BYTE  byPipeline;        //enmCallDutyPipeline
  char  mapName[MAX_NAMESIZE + 1];  //目标地图名称
  WORD  x;            //坐标x
  WORD  y;            //坐标y
};

///////////////////////////////////////////////////////////////
// 战斗指令定义结束
///////////////////////////////////////////////////////////////


//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 社会关系指令定义开始
//////////////////////////////////////////////////////////////
struct stRelationUserCmd : public stNullUserCmd
{
  stRelationUserCmd()
  {
    byCmd = RELATION_USERCMD;
  }
};

enum {
  RELATION_TYPE_LOVE,// 夫妻关系
  RELATION_TYPE_TEACHER,// 师徒关系
  RELATION_TYPE_FRIEND,// 好友关系
  RELATION_TYPE_BAD,// 黑名单
  RELATION_TYPE_OVER,// 关系已经断绝，主要是用在数据库中传达离线通知，当人物上线后会根据状态向客户端发消息。
  RELATION_TYPE_ENEMY      // 仇人关系
};
struct stRelation
{
  char  name[MAX_NAMESIZE + 1];  //  关系人名字
  BYTE  type;          //  关系类型 
  WORD  level;        //  关系级别
  WORD  user_level;              // 关系人等级
  BYTE  online;             //  在线状态 0为不在线，1为在线
  WORD  occupation;      // 职业类型
  DWORD exploit;    // 功勋值
  DWORD country;    // 国籍
  char  unionName[MAX_NAMESIZE + 1];  // 所属帮会
};

// 发送社会关系列表
const BYTE RELATION_SEND_RELATIONLIST_PARA = 1;
struct stSendRelationListCmd : public stRelationUserCmd
{
  WORD size;
  stRelation member[0];
  stSendRelationListCmd()
  {
    byParam = RELATION_SEND_RELATIONLIST_PARA;
  }
};

enum RELATION{
  RELATION_ADD, // 添加状态
  RELATION_QUESTION, // 发出邀请某人的询问
  RELATION_ANSWER_YES,// 确认邀请
  RELATION_ANSWER_NO,// 否定邀请
  RELATION_ONLINE,// 在线状态
  RELATION_OFFLINE,// 离线状态
  RELATION_TYPECHANGE,// 类型改变
  RELATION_REMOVE        // 删除状态
};

// 关系状态变更，以及邀请交互
const BYTE RELATION_STATUS_PARA =3;
struct stRelationStatusCmd : public stRelationUserCmd
{
  char  name[MAX_NAMESIZE + 1];
  BYTE  type;
  WORD  occupation;
  WORD    user_level;

  union {
    WORD level;
    DWORD userid;
  };

  BYTE  byState;      //  参见 enum RELATION
  DWORD   exploit;      // 功勋值
  DWORD   country;
    
  char  unionName[MAX_NAMESIZE + 1];  // 所属帮会
  
  stRelationStatusCmd()
  {
    byParam = RELATION_STATUS_PARA;
    user_level = 0;
    exploit = 0;
    country = 0;
    bzero(unionName,MAX_NAMESIZE);
  }
};


enum{
  MARRY_AHEAD_CHECK,
  MARRY_AHEAD_CHECK_FAIL,
  MARRY_ITEM_CHECK,
  MARRY_NO_ITEM,
  MARRY_ANSWER,
  MARRY_REFUSE,
  MARRY_AGREE,
  MARRY_PAY_MONEY,
  MARRY_PAY_MONEY1,
  MARRY_PAY_MONEY2,
  MARRY_NO_MONEY
};

/// 结婚前的用户状态检查消息
const BYTE MARRY_STATUS_CHECK_PARA = 4;
struct stMarryStatusCheckCmd  : public stRelationUserCmd
{
  stMarryStatusCheckCmd()
  {
    byParam = MARRY_STATUS_CHECK_PARA;

  }
  BYTE byStep;
};

/// 离婚消息
#define UNMARRY_PARA 5
struct stUnmarryCmd  : public stRelationUserCmd
{
  stUnmarryCmd()
  {
    byParam = UNMARRY_PARA;

  }
};

//////////////////////////////////////////////////////////////
// 社会关系指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 师徒门派关系指令定义开始
//////////////////////////////////////////////////////////////
struct stSchoolUserCmd : public stNullUserCmd
{
  stSchoolUserCmd()
  {
    byCmd = SCHOOL_USERCMD;
  }
};

enum SCHOOL_ADD_MEMBER{
      TEACHER_QUESTION, // 发出邀请某人加入师门的询问
      TEACHER_ANSWER_YES,// 确认邀请加入师门
      TEACHER_ANSWER_NO         // 否定邀请加入师门
};

// 邀请他人加入门派，兼任新人加入通知消息
const BYTE ADD_MEMBER_TO_SCHOOL_PARA = 1;  // 这个消息由客户端发到服务端是邀请某人，由服务端发到客户端是询问某人是否接受邀请
struct stAddMemberToSchoolCmd : public stSchoolUserCmd
{
  stAddMemberToSchoolCmd()
  {
    byParam = ADD_MEMBER_TO_SCHOOL_PARA;
    level = 0;
  }
  char   memberName[MAX_NAMESIZE + 1];      // 被邀请的人
  union {
      DWORD  memberID;          // 被邀请人ID
      DWORD  degree;            // 向客户端发送的时候告诉客户端新成员处于那一个层级之中
  };
  union {
      char   schoolName[MAX_NAMESIZE + 1];  // 门派名称，如果没有门派为空
      char    prename[MAX_NAMESIZE + 1];    // 他的师兄
  };
  BYTE   byState;              // 参见 enum SCHOOL_ADD_MEMBER
  WORD  wdOccupation;            // 新成员职业
  WORD    level;          // 加入成员的等级
};

// 将指定的人开除出师门或者门派
const BYTE FIRE_MEMBER_FROM_SCHOOL_PARA = 2;
struct stFireMemberFromSchoolCmd : public stSchoolUserCmd
{
  stFireMemberFromSchoolCmd()
  {
    byParam = FIRE_MEMBER_FROM_SCHOOL_PARA ;
  }
  char memberName[MAX_NAMESIZE + 1];
};

/// 门派创建前的用户状态检查消息
const BYTE SCHOOL_STATUS_CHECK_PARA = 3;
struct stSchoolStatusCheckCmd  : public stSchoolUserCmd
{
  stSchoolStatusCheckCmd()
  {
    byParam = SCHOOL_STATUS_CHECK_PARA;
  }
};

// 门派创建命令
const BYTE CREATE_SCHOOL_PARA = 4;
struct stCreateSchoolCmd: public stSchoolUserCmd
{
  stCreateSchoolCmd()
  {
    byParam = CREATE_SCHOOL_PARA;
  }
  char SchoolName[MAX_NAMESIZE + 1];
};

// 门派或师门成员申请脱离关系
const BYTE SCHOOLMEMBER_LEAVE_SCHOOL_PARA = 5;
struct stSchoolMemberLeaveSchoolCmd : public stSchoolUserCmd
{
  stSchoolMemberLeaveSchoolCmd()
  {
    byParam = SCHOOLMEMBER_LEAVE_SCHOOL_PARA;
  }
};

enum SCHOOL_PACKAGE_TAG{
  SCHOOL_PACKAGE_BODY=0,// 消息包体
  SCHOOL_PACKAGE_HEAD=1,// 消息包头
  SCHOOL_PACKAGE_TAIL=2  // 消息包尾
};

enum SCHOOL_LAYER {
  SCHOOL_NEWLAYER,// 换一新层
  SCHOOL_NEWLINE,// 换一新行
  SCHOOL_NONE        // 无动作
};

struct stSchoolMember{
  char name[MAX_NAMESIZE + 1];
  BYTE tag;    // enum SCHOOL_LAYER
  WORD level;             // 成员等级
  BYTE online;  // 0 为再不在线
  WORD occupation;// 职业类型
};

struct stTeacherMember{
  stTeacherMember()
  {
    level = 0;
  }
  char name[MAX_NAMESIZE + 1];
  WORD degree;   // 友好度
  BYTE tag;  // enum SCHOOL_MEMBER_TAG
  WORD level;     // 成员等级
  BYTE online;  // 0 为再不在线
  WORD occupation;// 职业类型
  DWORD country;          // 国籍
  char  unionName[MAX_NAMESIZE + 1];  // 所属帮会
  char  septName[MAX_NAMESIZE + 1];  // 所属家族
};

// 门派信息列表
const BYTE SENDLIST_SCHOOL_PARA = 6;
struct stSendListSchoolCmd : public stSchoolUserCmd
{
  stSendListSchoolCmd()
  {
    byParam = SENDLIST_SCHOOL_PARA;
  }
  DWORD dwMasterTempID;
  BYTE byPackageTag; //enum SCHOOL_PACKAGE_TAG
  WORD size;
  stSchoolMember list[0];
};

enum SCHOOL_MEMBER_TAG{
  TEACHER, // 师傅
  BIGBROTHER, // 师兄
  LITTLEBROTHER,// 师弟
  PRENTICE        // 徒弟
  
};

// 师门信息列表
const BYTE SENDMEMBERINFO_SCHOOL_PARA = 7;
struct stSendMemberInfoCmd : public stSchoolUserCmd
{
  stSendMemberInfoCmd()
  {
    byParam = SENDMEMBERINFO_SCHOOL_PARA;
  }
  WORD size; //大小
  stTeacherMember list[0]; // list里成员的tag使用 enum SCHOOL_MEMBER_TAG
};

enum {
  SCHOOL_STATUS_NONE,
  SCHOOL_STATUS_TEACHER,
  SCHOOL_STATUS_SCHOOL
};

// 初始化通知
const BYTE MEMBER_STATUS_SCHOOL_PARA = 8;
struct stMemberStatusSchool : public stSchoolUserCmd
{
  stMemberStatusSchool()
  {
    byParam = MEMBER_STATUS_SCHOOL_PARA;
  }
  char schoolName[MAX_NAMESIZE + 1]; // 门派名字
  BYTE byStatus; //  SCHOOL_STATUS_NONE,SCHOOL_STATUS_TEACHER,SCHOOL_STATUS_SCHOOL
};

enum {
  SCHOOL_MEMBER_OFFLINE=0,// 离线状态
  SCHOOL_MEMBER_ONLINE=1      // 在线状态
};

const BYTE SCHOOL_MEMBER_STATUS_PARA =9;
struct stSchoolMemberStatusCmd : public stSchoolUserCmd
{
  char  name[MAX_NAMESIZE + 1];
  BYTE  byState;            //  参见 SCHOOL_MEMBER_ONLINE SCHOOL_MEMBER_OFFLINE
  WORD    level;              //  成员等级
  DWORD  country;            //  国籍
  char  unionName[MAX_NAMESIZE + 1];    //  所属帮会
  char  septName[MAX_NAMESIZE + 1];      //  所属家族
  stSchoolMemberStatusCmd()
  {
    byParam = SCHOOL_MEMBER_STATUS_PARA;
  }
};

#define BULLETIN_MAX_SIZE 1000

enum {
  SCHOOL_BULLETIN_SET,// 设置公告
  SCHOOL_BULLETIN_GET,// 请求公告内容
  SCHOOL_BULLETIN_EDIT    // 编辑请求
};

const BYTE SCHOOL_BULLETIN__PARA =10;
struct stSchoolBulletinCmd : public stSchoolUserCmd
{
  BYTE byState; // SCHOOL_BULLETIN_SET SCHOOL_BULLETIN_GET
  WORD wdSize;  // 无内容设0
  char data[0];
  stSchoolBulletinCmd()
  {
    byParam = SCHOOL_BULLETIN__PARA;
  }
};

// 门派解散指令
const BYTE DESTROY_SCHOOL_PARA = 11;
struct stDestroySchoolCmd: public stSchoolUserCmd
{
  stDestroySchoolCmd()
  {
    byParam = DESTROY_SCHOOL_PARA;
  }
};

const BYTE SCHOOL_BULLETIN_NOTIFY_PARA = 12;
struct stSchoolBulletinNotifyCmd : public stSchoolUserCmd
{
  stSchoolBulletinNotifyCmd()
  {
    byParam = SCHOOL_BULLETIN_NOTIFY_PARA;
  }
};

enum
{
  QUERY_SCHOOL_BOUNTY,// 查询
  GET_SCHOOL_BOUNTY,// 提取
  PUT_SCHOOL_BOUNTY,// 进贡
};

// 做为师傅查询或领取进贡
#define REQ_MASTER_BOUNTY_PARA 13
struct stReqMasterBountyUserCmd : public stSchoolUserCmd
{
  stReqMasterBountyUserCmd()
  {
    byParam = REQ_MASTER_BOUNTY_PARA;
  }

  BYTE byState;
};

// 做为徒弟查询和进行进贡
#define REQ_PRENTICE_BOUNTY_PARA 14
struct stReqPrenticeBountyUserCmd : public stSchoolUserCmd
{
  stReqPrenticeBountyUserCmd()
  {
    byParam = REQ_PRENTICE_BOUNTY_PARA;
  }

  BYTE byState;
};

// 返回师傅查询
#define RTN_MASTER_BOUNTY_PARA 15
struct stRtnMasterBountyUserCmd : public stSchoolUserCmd
{
  stRtnMasterBountyUserCmd()
  {
    byParam = RTN_MASTER_BOUNTY_PARA;
    dwBalance = 0;
    dwTotal = 0;
  }

  DWORD dwBalance; // 可领取的金额
  DWORD dwTotal;  // 累计已领取的金额
};

// 返回徒弟查询
#define RTN_PRENTICE_BOUNTY_PARA 16
struct stRtnPrenticeBountyUserCmd : public stSchoolUserCmd
{
  stRtnPrenticeBountyUserCmd()
  {
    byParam = RTN_PRENTICE_BOUNTY_PARA;
    dwBalance = 0;
    dwTotal = 0;
    dwLastLevel = 0;
    bzero(name,sizeof(name));
  }
  
  DWORD dwBalance; // 可进贡的金额
  DWORD dwTotal;   // 累计已领取的金额
  DWORD dwLastLevel; // 上次领取时的等级
  char name[MAX_NAMESIZE + 1]; // 师傅的姓名
};

//////////////////////////////////////////////////////////////
// 师徒门派关系指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
/************************************************************
************************任务指令定义开始*********************
*************************************************************/
struct stQuestUserCmd : public stNullUserCmd
{
  stQuestUserCmd()
  {
    byCmd = TASK_USERCMD;  
  }
  DWORD id; //任务id
};

static const BYTE QUEST_INFO_PARA = 1;
struct stQuestInfoUserCmd : public stQuestUserCmd
{
  stQuestInfoUserCmd()
  {
    byParam = QUEST_INFO_PARA;
  }

  BYTE name[64];
  DWORD start;
  BYTE info[0];
};

static const BYTE QUEST_VARS_PARA = 2;
struct stQuestVarsUserCmd : public stQuestUserCmd
{
  enum {
    MAX_NSIZE = 32,
    MAX_VSIZE = 128,
  };

  stQuestVarsUserCmd()
  {
    byParam = QUEST_VARS_PARA;  
  }
  BYTE count; //变量数量
  struct Var {
    BYTE name[MAX_NSIZE];
    BYTE value[MAX_VSIZE];  
  } vars_list[0]; //变量列表
};

static const BYTE REQUEST_QUEST_PARA = 3;
struct stRequestQuestUserCmd : public stQuestUserCmd
{
  stRequestQuestUserCmd()
  {
    byParam = REQUEST_QUEST_PARA;
  }
  char target[16];
  BYTE offset; //任务分支
};

static const BYTE ABANDON_QUEST_PARA = 4;
struct stAbandonQuestUserCmd : public stQuestUserCmd
{
  stAbandonQuestUserCmd()
  {
    byParam = ABANDON_QUEST_PARA;
  }
};

static const BYTE CART_CONTROL_QUEST_PARA = 5;//控制镖车走和停
struct stCartControlQuestUserCmd : public stQuestUserCmd
{
  stCartControlQuestUserCmd()
  {
    byParam = CART_CONTROL_QUEST_PARA;
  }
};

static const BYTE CHECK_VALID_QUEST_PARA = 6;//检查可以接的任务列表
struct stCheckValidQuestUserCmd : public stQuestUserCmd
{
  stCheckValidQuestUserCmd()
  {
    byParam = CHECK_VALID_QUEST_PARA;
  }
};

static const BYTE REQ_VALID_QUEST_PARA = 7;//检查可以接的任务列表
struct stReqValidQuestUserCmd : public stQuestUserCmd
{
  stReqValidQuestUserCmd()
  {
    byParam = REQ_VALID_QUEST_PARA;
  }
};

static const BYTE RET_VALID_QUEST_PARA = 8;//返回可以接的任务列表
struct stRetValidQuestUserCmd : public stQuestUserCmd
{
  stRetValidQuestUserCmd()
  {
    byParam = RET_VALID_QUEST_PARA;
    size = 0;
  }
  DWORD size;
  char content[0];
};

/************************************************************
************************任务指令定义结束*********************
*************************************************************/

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 家族指令定义开始
//////////////////////////////////////////////////////////////
struct stSeptUserCmd : public stNullUserCmd
{
  stSeptUserCmd()
  {
    byCmd = SEPT_USERCMD;
  }
};

/// 家族创建前的用户状态检查消息
const BYTE SEPT_STATUS_CHECK_PARA = 1;
struct stSeptStatusCheckCmd  : public stSeptUserCmd
{
  stSeptStatusCheckCmd()
  {
    byParam = SEPT_STATUS_CHECK_PARA;

  }
};

// 家族创建命令
const BYTE CREATE_SEPT_PARA = 2;
struct stCreateSeptCmd: public stSeptUserCmd
{
  stCreateSeptCmd()
  {
    byParam = CREATE_SEPT_PARA;
  }
  char SeptName[MAX_NAMESIZE + 1];  // 家族名称
};

// 家族创建成功通知指令
const BYTE SERVER_RETURN_SEPT_CREATE_FAILED = 3;
struct stServerReturnSeptCheckCmd : public stSeptUserCmd
{
  stServerReturnSeptCheckCmd()
  {
    byParam = SERVER_RETURN_SEPT_CREATE_FAILED;
  }
};

struct stSeptRember{
  char  memberName[MAX_NAMESIZE + 1];        // 家族成员名称
  WORD  level;            // 成员等级
  BYTE  byOnline;            // 成员在线标志 0 为不在线 非0为在线
  WORD  occupation;          // 职业类型
  DWORD exploit;            // 功勋值
  DWORD useJob;				// sky 职业
  char memberAliasName[MAX_NAMESIZE + 1];      // 族员别名
  WORD nRight;
};

// 服务器返回家族成员列表，及请求者的个人家族信息
const BYTE ALL_SEPT_MEMBER_PARA = 5;
struct stAllSeptMemberCmd : public stSeptUserCmd
{
  stAllSeptMemberCmd()
  {
    byParam = ALL_SEPT_MEMBER_PARA;
  }
  WORD size;                     // 数量
  stSeptRember memberList[0];   // 成员列表
};


enum SEPT_ADD_MEMBER{
      SEPT_QUESTION,  // 发出邀请某人的询问
      SEPT_ANSWER_YES,// 确认邀请
      SEPT_ANSWER_NO          // 否定邀请
};

// 邀请他人加入家族
const BYTE ADD_MEMBER_TO_SEPT_PARA = 7;  // 这个消息由客户端发到服务端是邀请某人，由服务端发到客户端是询问某人是否接受邀请
struct stAddMemberToSeptCmd : public stSeptUserCmd
{
  stAddMemberToSeptCmd()
  {
    byParam = ADD_MEMBER_TO_SEPT_PARA;
  }
  char   memberName[MAX_NAMESIZE + 1];   // 被邀请的人
  DWORD memberID;                   // 被邀请人ID
  char   septName[MAX_NAMESIZE + 1];    // 家族名称
  BYTE   byState;                    // 参见 enum SEPT_ADD_MEMBER
};

// 开除家族成员
const BYTE FIRE_MEMBER_FROM_SEPT_PARA = 8;
struct stFireMemberFromSeptCmd : public stSeptUserCmd
{
  stFireMemberFromSeptCmd()
  {
    byParam = FIRE_MEMBER_FROM_SEPT_PARA ;
  }
  char memberName[MAX_NAMESIZE + 1];
};

enum{
     SEPT_MEMBER_STATUS_ONLINE,  // 家族成员上线
     SEPT_MEMBER_STATUS_OFFLINE, // 家族成员下线
     SEPT_MEMBER_STATUS_FIRE,    // 家族成员被开除
     SEPT_MEMBER_STATUS_NEWMEMBER,// 新增加家族成员
     SEPT_MEMBER_STATUS_ALIASCHANGE,// 更改别名
};

// 服务端更新家族成员状态及信息通知消息 状态见上表
const BYTE BROADCAST_SEPT_MEMBER_INFO_PARA = 10;
struct stBroadcastSeptMemberInfo : public stSeptUserCmd
{
  stBroadcastSeptMemberInfo()
  {
    byParam = BROADCAST_SEPT_MEMBER_INFO_PARA;
    level = 0;
    bzero(name,sizeof(name));
    bzero(aliasName,sizeof(name));
    exploit = 0;
    useJob = 0;
  }
  BYTE byStatus;                       // 成员状态
  WORD wdOccupation;          // 成员职业
  WORD level;           // 成员等级
  char name[MAX_NAMESIZE + 1];             // 成员名称
  char aliasName[MAX_NAMESIZE + 1];       // 成员别名
  DWORD exploit;           // 功勋值
  DWORD useJob;           // sky 职业
  //[Shx Add 职位ID]
  WORD  nRight;
};

// 服务器端发送家族信息
const BYTE SEPT_BASE_INFO_PARA = 11;
struct stSeptBaseInfoCmd : public stSeptUserCmd
{
  stSeptBaseInfoCmd()
  {
    byParam = SEPT_BASE_INFO_PARA;
    dwLevel = 0;
  }
  DWORD dwMasterTempID;
  char  septName[MAX_NAMESIZE + 1];         // 家族名称
  char  master[MAX_NAMESIZE + 1];            // 家族族长
  char  note[255];
  DWORD dwRepute;      // 家族声望
  DWORD dwLevel;      // 家族等级
  struct stStepRight
  {
	  char	RightName[MAX_NAMESIZE + 1];
	  DWORD	dwRight;
  } RightList[10];
};

// 家族成员申请退族
const BYTE SEPTMEMBER_LEAVE_SEPT_PARA = 12;
struct stSeptMemberLeaveSeptCmd : public stSeptUserCmd
{
  stSeptMemberLeaveSeptCmd()
  {
    byParam = SEPTMEMBER_LEAVE_SEPT_PARA;
  }
};

struct stSeptVoteRecord{
  char septName [MAX_NAMESIZE + 1];
  char master[MAX_NAMESIZE + 1];
  WORD wdVoteNumber;
  char note[255];
};

// 家族投票列表
const BYTE VOTELIST_SEPT_PARA = 13;
struct stVoteListSeptCmd : public stSeptUserCmd
{
  stVoteListSeptCmd()
  {
    byParam = VOTELIST_SEPT_PARA;
  }
  char septName[MAX_NAMESIZE + 1];
  DWORD dwSize;
  BYTE flag; // 0为消息头 1为后续消息
  stSeptVoteRecord data[0];
};

// 家族投票消息
const BYTE VOTE_SEPT_PARA = 14;
struct stVoteSeptCmd : public stSeptUserCmd
{
  stVoteSeptCmd()
  {
    byParam = VOTE_SEPT_PARA;
  }
  char septName[MAX_NAMESIZE + 1];
  BYTE bySuccess;   // 为1为成功 为0为失败
};

// 家族设置帮会说明
const BYTE NOTE_SEPT_PARA = 15;
struct stNoteSeptCmd : public stSeptUserCmd
{
  stNoteSeptCmd()
  {
    byParam = NOTE_SEPT_PARA;
  }
  char noteBuf[255];
};

// 家族成员别名设置
const BYTE CHANGE_SEPT_MEMBER_ALIASNAME_PARA = 16;
struct stChangeSeptMemberAliasName : public stSeptUserCmd
{
  stChangeSeptMemberAliasName()
  {
    byParam = CHANGE_SEPT_MEMBER_ALIASNAME_PARA;
  }

  char name[MAX_NAMESIZE + 1];             // 族员姓名
  char aliasname[MAX_NAMESIZE + 1];        // 族员别名
};

// 家族成员捐献荣誉点
const BYTE DONATE_HONOR_PARA = 17;
struct stDonateHonor : public stSeptUserCmd
{
  stDonateHonor()
  {
    byParam = DONATE_HONOR_PARA;
    dwHonor = 0;
  }
  
  DWORD dwHonor;
};

enum
{
  COUNTRY_SEPT_SORT,// 本国家族排行榜
  WORLD_SEPT_SORT,// 世界家族排行榜
};

// 查询家族排行榜（根据声望）
const BYTE REQ_SEPT_SORT_PARA = 18;
struct stReqSeptSort : public stSeptUserCmd
{
  stReqSeptSort()
  {
    byParam = REQ_SEPT_SORT_PARA;
    byType = COUNTRY_SEPT_SORT;
  }
  
  BYTE byType;
};

struct stSeptSortInfo
{
  char  septName[MAX_NAMESIZE + 1];           // 家族名称
  DWORD dwRepute;        // 家族声望
  DWORD dwOrder;        // 家族排名
  DWORD dwCountryID;      // 国家ID
};

// 返回家族排行榜（根据声望）
const BYTE RTN_SEPT_SORT_PARA = 19;
struct stRtnSeptSort : public stSeptUserCmd
{
  stRtnSeptSort()
  {
    byParam = RTN_SEPT_SORT_PARA;
    dwSize = 0;
  }
  
  BYTE byType;
  DWORD dwSize;
  stSeptSortInfo data[0];
};

struct stSeptRecord{
  char septName [MAX_NAMESIZE + 1];
  char master[MAX_NAMESIZE + 1];
  char note[255];
};

// 家族投票列表
const BYTE LIST_SEPT_PARA = 20;
struct stListSeptCmd : public stSeptUserCmd
{
  stListSeptCmd()
  {
    byParam = LIST_SEPT_PARA;
  }
  DWORD dwSize;
  BYTE flag; // 0为消息头 1为后续消息
  stSeptRecord data[0];
};

enum {
  REQUEST_JOIN_OK,
  REQUEST_JOIN_CANCEL,
  REQUEST_JOIN_TIMEOUT
};

// 请求加入家族消息
const BYTE REQUEST_JOIN_SEPT_PARA = 21;
struct stRequestJoinSeptCmd : public stSeptUserCmd
{
  stRequestJoinSeptCmd()
  {
    byParam = REQUEST_JOIN_SEPT_PARA;
  }
  char name[MAX_NAMESIZE + 1]; //发给服务器的时候填对方族长的名字，服务器发出来的时候填的是请求人的名字
  BYTE status;
};

// 请求家族占领NPC信息
const BYTE REQUEST_NPCINFO_SEPT_PARA = 22;
struct stRequestNpcInfoSeptCmd : public stSeptUserCmd
{
  stRequestNpcInfoSeptCmd()
  {
    byParam = REQUEST_NPCINFO_SEPT_PARA;
  }
};

// 请求领取家族经验
const BYTE REQUEST_SEPT_EXP_PARA = 23;
struct stRequestSeptExpCmd : public stSeptUserCmd
{
  stRequestSeptExpCmd()
  {
    byParam = REQUEST_SEPT_EXP_PARA;
  }
};

// 请求放弃占领该NPC
const BYTE REQUEST_ABJURATION_SEPTNPC_PARA = 24;
struct stRequestAbjurationSeptNpcSeptCmd : public stSeptUserCmd
{
  stRequestAbjurationSeptNpcSeptCmd()
  {
    byParam = REQUEST_ABJURATION_SEPTNPC_PARA;
  }
};

// 请求家族名称
const BYTE REQ_SEPT_NAME_PARA = 25;
struct stReqSeptNameCmd : public stSeptUserCmd
{
  stReqSeptNameCmd()
  {
    byParam = REQ_SEPT_NAME_PARA;
    dwSeptID = 0;
  }

  DWORD dwSeptID;
};

// 请求家族名称
const BYTE RTN_SEPT_NAME_PARA = 26;
struct stRtnSeptNameCmd : public stSeptUserCmd
{
  stRtnSeptNameCmd()
  {
    byParam = RTN_SEPT_NAME_PARA;
    dwSeptID = 0;
    bzero(name,MAX_NAMESIZE);
  }

  DWORD dwSeptID;
  char name[MAX_NAMESIZE + 1];
};
// 请求家族名称列表
const BYTE REQ_SEPT_NAME_LIST_PARA = 27;
struct stReqSeptNameListCmd : public stSeptUserCmd
{
  stReqSeptNameListCmd()
  {
    byParam = REQ_SEPT_NAME_LIST_PARA;
    num=0;
  }
  BYTE num;
  DWORD dwSeptID[0];
};

// 请求家族名称列表
const BYTE RTN_SEPT_NAME_LIST_PARA = 28;
struct stRtnSeptNameListCmd : public stSeptUserCmd
{
  stRtnSeptNameListCmd()
  {
    byParam = RTN_SEPT_NAME_LIST_PARA;
    num=0;
  }
  BYTE num;
  struct
  {
    DWORD dwSeptID;
    char name[MAX_NAMESIZE + 1];
  } list[0];
};

// 请求领取家族经验
const BYTE REQUEST_SEPT_NORMAL_EXP_PARA = 29;
struct stRequestSeptNormalExpCmd : public stSeptUserCmd
{
  stRequestSeptNormalExpCmd()
  {
    byParam = REQUEST_SEPT_NORMAL_EXP_PARA;
  }
};

//////////////////////////////////////////////////////////////
// 家族指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 宠物指令定义开始
//////////////////////////////////////////////////////////////
struct stPetUserCmd : public stNullUserCmd
{
  stPetUserCmd()
  {
    byCmd = PET_USERCMD;
  }
};

//宠物AI模式
enum petAIMode
{
  PETAI_MOVE_FOLLOW  = 0x0001,//跟随
  PETAI_MOVE_STAND  = 0x0002,//站立不动
  PETAI_ATK_ACTIVE  = 0x0100,//攻击所有敌人
  PETAI_ATK_PASSIVE  = 0x0200,//攻击正在攻击主人的敌人
  PETAI_ATK_NOATK    = 0x0400  //不战斗
};
// 设置宠物的AI模式
const BYTE SETAI_PET_PARA = 1;
struct stSetAIPetCmd : public stPetUserCmd
{
  stSetAIPetCmd()
  {
    byParam = SETAI_PET_PARA;
  }
  petType type;
  petAIMode mode;
};

//宠物状态
enum petState
{
  PET_STATE_NOPET    = 0,//没有宠物
  PET_STATE_NORMAL  = 1,//普通
  PET_STATE_PUTUP    = 2,//收起
  PET_STATE_DEAD    = 3,//死亡
  PET_STATE_CONSIGN  = 4    //寄存
};

//宠物的数据
//struct t_PetData
//{
//  DWORD id;    //npcid
//  char name[MAX_NAMESIZE + 1];//名字
//  BYTE lv;    //等级
//  DWORD hp;    //生命
//  DWORD maxhp;    //最大生命
//  WORD str;    //力量
//  WORD intel;    //智力
//  WORD agi;    //敏捷
//  WORD men;    //精神
//  WORD vit;    //体质
//  DWORD exp;    //经验
//  DWORD maxexp;    //最大经验
//  DWORD atk;    //攻击力
//  DWORD maxatk;    //最大攻击力
//  DWORD matk;    //魔攻
//  DWORD maxmatk;    //最大魔攻
//  DWORD def;    //物防
//  DWORD mdef;    //魔防
//  WORD cri;    //爆击
//  DWORD skills[4];  //技能
//  WORD ai;    //AI
//  DWORD maxhp_plus;  //附加最大生命
//  WORD atk_plus;    //附加物理攻击力
//  WORD maxatk_plus;  //附加最大物理攻击力
//  WORD matk_plus;    //附加魔法攻击力
//  WORD maxmatk_plus;  //附加最大魔法攻击力
//  WORD pdef_plus;    //附加物防
//  WORD mdef_plus;    //附加魔防
//  petType type;    //类型
//  petState state;    //状态
//};

struct t_PetData
{
	DWORD id;               //npcid
	char name[MAX_NAMESIZE + 1];//名字
	BYTE lv;                //等级
	DWORD hp;               //生命
	DWORD maxhp;            //最大生命
	DWORD str;               //力量
	DWORD intel;             //智力
	DWORD agi;               //敏捷
	DWORD men;               //精神
	DWORD vit;               //体质
	DWORD exp;              //经验
	DWORD maxexp;           //最大经验
	DWORD atk;              //攻击力
	DWORD maxatk;           //最大攻击力
	DWORD matk;             //魔攻
	DWORD maxmatk;          //最大魔攻
	DWORD def;              //物防
	DWORD mdef;             //魔防
	WORD cri;               //爆击
	DWORD skills[4];        //技能
	WORD ai;                //AI
	DWORD maxhp_plus;       //附加最大生命
	WORD atk_plus;          //附加物理攻击力
	WORD maxatk_plus;       //附加最大物理攻击力
	WORD matk_plus;         //附加魔法攻击力
	WORD maxmatk_plus;      //附加最大魔法攻击力
	WORD pdef_plus;         //附加物防
	WORD mdef_plus;         //附加魔防
	petType type;           //类型
	petState state;         //状态
};

// 请求宠物的数据
const BYTE REQUESTDATA_PET_PARA = 2;
struct stRequestDataPetCmd : public stPetUserCmd
{
  stRequestDataPetCmd()
  {
    byParam = REQUESTDATA_PET_PARA;
  }
  petType type;
};

//返回宠物的数据
const BYTE REFRESHDATA_PET_PARA = 3;
struct stRefreshDataPetCmd : public stPetUserCmd
{
  stRefreshDataPetCmd()
  {
    byParam = REFRESHDATA_PET_PARA;
    bzero(&data,sizeof(data));
  }
  petType type;
  DWORD id;

  t_PetData data;
};

//改宠物名字
const BYTE CHANGENAME_PET_PARA = 4;
struct stChangeNamePetCmd : public stPetUserCmd
{
  stChangeNamePetCmd()
  {
    byParam = CHANGENAME_PET_PARA;
  }
  petType type;
  char name[MAX_NAMESIZE + 1];
};

//增加宠物
const BYTE ADDPET_PET_PARA = 5;
struct stAddPetPetCmd : public stPetUserCmd
{
  stAddPetPetCmd()
  {
    byParam = ADDPET_PET_PARA;
  }
  petType type;
  DWORD id;
};

//删除宠物
const BYTE DELPET_PET_PARA = 6;
struct stDelPetPetCmd : public stPetUserCmd
{
  stDelPetPetCmd()
  {
    byParam = DELPET_PET_PARA;
  }
  petType type;
  DWORD id;
};

//删除技能
const BYTE DELSKILL_PET_PARA = 7;
struct stDelSkillPetCmd : public stPetUserCmd
{
  stDelSkillPetCmd()
  {
    byParam = DELSKILL_PET_PARA;
  }
  petType type;///宠物类型
  DWORD id;///技能id
};

//召唤马出来跟随
const BYTE CALLHORSE_PET_PARA = 8;
struct stCallHorsePetCmd : public stPetUserCmd
{
  stCallHorsePetCmd()
  {
    byParam = CALLHORSE_PET_PARA;
  }
};

//收起马匹
const BYTE PUTHORSE_PET_PARA = 9;
struct stPutHorsePetCmd : public stPetUserCmd
{
  stPutHorsePetCmd()
  {
    byParam = PUTHORSE_PET_PARA;
  }
};

//刷新马的数据
const BYTE HORSEDATA_PET_PARA = 10;
struct stHorseDataPetCmd : public stPetUserCmd
{
  stHorseDataPetCmd()
  {
    byParam = HORSEDATA_PET_PARA;
    type = PET_TYPE_RIDE;
  }
  petType type;
  DWORD id;
  t_HorseData data;
};

//强制宠物攻击目标
const BYTE SETTARGET_PET_PARA = 11;
struct stSetTargetPetCmd : public stPetUserCmd
{
  stSetTargetPetCmd()
  {
    byParam = SETTARGET_PET_PARA;
  }
  petType type;///宠物类型
  DWORD targetType;///目标类型 0:玩家 1:NPC
  DWORD id;///目标的临时ID
};

//同步宠物的血和经验
const BYTE HP_EXP_PET_PARA = 12;
struct stHpExpPetCmd : public stPetUserCmd
{
  stHpExpPetCmd()
  {
    byParam = HP_EXP_PET_PARA;
  }
  petType type;
  DWORD id;//tempid
  DWORD hp;
  DWORD exp;
};

/*
//换马
const BYTE CHANGEHORSE_PET_PARA = 11;
struct stChangeHorsePetCmd : public stPetUserCmd
{
  stChangeHorsePetCmd()
  {
    byParam = CHANGEHORSE_PET_PARA;
  }
  DWORD id;
};
*/

//////////////////////////////////////////////////////////////
// 宠物指令定义结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
/// 定义与客户端PING工具的命令
//////////////////////////////////////////////////////////////
struct stPingUserCmd : public stNullUserCmd
{
  stPingUserCmd()
  {
    byCmd = PING_USERCMD;
  }
};

struct ping_element
{
  BYTE gateway_ip[15+1];
  /**
    * EMPTY = 0,人数0-399,
    * VERYIDLE = 1,人数400-799,
    * IDLE = 2,人数800-1199,
    * BUSY = 3,人数1200-1599
    * VERYBUSY= 4     人数1600-1999
    */
  BYTE state;
  ping_element()
  {
    bzero(gateway_ip,sizeof(gateway_ip));
  }
};

const BYTE PING_LIST_PARA = 1;
struct stPingList : public stPingUserCmd
{
  DWORD zone_id;
  struct ping_element ping_list;

  stPingList()
  {
    byParam = PING_LIST_PARA;
  };
};

const BYTE REQUEST_PING_LIST_PARA = 2;
struct stRequestPingList : public stPingUserCmd
{
  DWORD id;  //游戏区号

  stRequestPingList() 
  {
    byParam = REQUEST_PING_LIST_PARA;
  }
};

const BYTE LOGIN_PING_PARA = 3;
struct stLoginPing : public stPingUserCmd
{
  stLoginPing() 
  {
    byParam = LOGIN_PING_PARA;
  }
};


//////////////////////////////////////////////////////////////
/// 定义与客户端PING工具的命令
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义金币命令开始
//////////////////////////////////////////////////////////////

enum enumBuyType{
  eBuySilver = 1,
  eBuyGold = 2,
  eBuyTicket = 4,
};

struct stGoldUserCmd : public stNullUserCmd
{
  stGoldUserCmd()
  {
    byCmd = GOLD_USERCMD;
  }
};

const BYTE QUERY_GOLD_PARA = 1;
struct stQueryGold : public stGoldUserCmd
{
  stQueryGold() 
  {
    byParam = QUERY_GOLD_PARA;
  }
};

enum
{
  REDEEM_SUCCESS,// 兑换成功 
  REDEEM_BUSY,// 服务器忙
  REDEEM_STOP,// 兑换系统停止服务
  REDEEM_FAIL,// 失败
};
#define REDEEM_RATE_GOLD 1 //兑换金币比率1:1
#define  REDEEM_RATE_MONTH_CARD 18//兑换月卡比率1:18
//请求兑换金币
const BYTE REQUEST_REDEEM_GOLD_PARA = 2;
struct stRequestRedeemGold : public stGoldUserCmd
{
  stRequestRedeemGold()
  {
    byParam = REQUEST_REDEEM_GOLD_PARA;
  }
  DWORD dwNum;  //需要兑换的点数
};
//兑换金币返回
const BYTE REDEEM_GOLD_PARA = 3;
struct stRedeemGold : public stGoldUserCmd
{
  stRedeemGold()
  {
    byParam = REDEEM_GOLD_PARA;
  }
  DWORD dwNum;  //返回当前金币数
  DWORD dwBalance;      /// 点卡余额
  BYTE byReturn;  //返回类型
};
 
//请求兑换月卡
const BYTE REQUEST_REDEEM_MONTH_CARD_PARA = 4;
struct stRequestRedeemMonthCard : public stGoldUserCmd
{
  stRequestRedeemMonthCard()
  {
    byParam = REQUEST_REDEEM_MONTH_CARD_PARA;
  }
};

//兑换月卡返回
const BYTE REDEEM_MONTH_CARD_PARA = 5;
struct stRedeemMonthCard : public stGoldUserCmd
{
  stRedeemMonthCard()
  {
    byParam = REDEEM_MONTH_CARD_PARA;
  }
  DWORD dwNum;  //到期时间(time_t,4字节结构)
  DWORD dwBalance;      /// 点卡余额
  BYTE byReturn;  //返回类型
};

//查询月卡和金币
const BYTE REQUEST_CARD_AND_GOLD_PARA = 6;
struct stRequestCardAndGold :  public stGoldUserCmd
{
  stRequestCardAndGold()
  {
    byParam = REQUEST_CARD_AND_GOLD_PARA;
  }
};

//查询返回
const BYTE RETURN_CARD_AND_GOLD_PARA = 7;
struct stReturnCardAndGold :  public stGoldUserCmd
{
  stReturnCardAndGold()
  {
    byParam = RETURN_CARD_AND_GOLD_PARA;
  }
  DWORD dwMonthCard;//月卡
  DWORD dwGold;//金币
  BYTE byReturn;//返回类型
};
//查询点卡
const BYTE REQUEST_POINT_PARA = 8;
struct stRequestPoint :  public stGoldUserCmd
{
  stRequestPoint()
  {
    byParam = REQUEST_POINT_PARA;
  }
};
//查询点卡返回
const BYTE RETURN_REQUEST_POINT_PARA = 9;
struct stReturnRequestPoint :  public stGoldUserCmd
{
  stReturnRequestPoint()
  {
    byParam = RETURN_REQUEST_POINT_PARA;
  }
  DWORD dwPoint;//剩余点数
  BYTE byReturn;//查询返回类型
};
//金币系停止服务
const BYTE STOP_SERVICE_GOLD_PARA = 10;
struct stStopServiceGold :  public stGoldUserCmd
{
  stStopServiceGold()
  {
    byParam = STOP_SERVICE_GOLD_PARA;
  }
};
#define CARDID_LENGTH_PARA 32
///消费卡的区类型
enum
{
  ZONE_CARD_OBJECT=1,///道具卡 
  ZONE_CARD_PROFRESSION=2,///专区卡
};
//消费卡消费
const BYTE CONSUME_CARD_PARA = 11;
struct stConSumeCardCard : public stGoldUserCmd
{
  stConSumeCardCard()
  {
    byParam = CONSUME_CARD_PARA;
    bzero(cardid,sizeof(cardid));
  }
  DWORD type;
  char cardid[CARDID_LENGTH_PARA];
};
/// 消费子类型
enum
{
  OBJ_GOLD_STONE = 1,//送精致升级宝石
  OBJ_GOLD_OBJECT = 2,//送金色装备
  OBJ_GREEN_OBJECT = 3,//送神圣装备
  SUBAT_GOLD = 4,//专区卡充值返回子类型//道具卡的子类型不能于该值重复
};
//消费卡消费返回
const BYTE RETURN_CONSUME_CARD_PARA = 12;
struct stReturnConSumeCardCard : public stGoldUserCmd
{
  stReturnConSumeCardCard()
  {
    byParam = RETURN_CONSUME_CARD_PARA;
  }
  BYTE byType;  //消费类型
  BYTE byReturn;  //返回类型
  DWORD balance;  //专区卡所带点数
};
/*
enum
{
  QUERY_SUCCESS,// 查询成功
  QUERY_BUSY,// 服务器忙
  QUERY_FAIL,// 查询失败
  QUERY_EMPTY,// 该帐号，没有记录
};

enum
{
  TYPE_QUERY,// 查询的返回
  TYPE_CHANGE    // 点数换金币的返回
};

const BYTE RETURN_QUERY_GOLD_PARA = 2;
struct stReturnQueryGold : public stGoldUserCmd
{
  double gold;        /// 帐户余额
  BYTE   state;                           /// 查询状态
  BYTE   type;                            /// 返回类型

  stReturnQueryGold()
  {
    gold = 0;
    type = TYPE_QUERY;
    byParam = RETURN_QUERY_GOLD_PARA;
  };
};

const BYTE CHANGE_POINTTOGOLD_PARA = 3;
struct stChangePointGold : public stGoldUserCmd
{
  DWORD point;        /// 要兑换的点数

  stChangePointGold()
  {
    point = 0;
    byParam = CHANGE_POINTTOGOLD_PARA;
  };
};
// */

//////////////////////////////////////////////////////////////
/// 定义金币命令结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
/// 定义股票命令开始
//////////////////////////////////////////////////////////////
//STOCK_USERCMD
struct stStockSceneUserCmd : public stNullUserCmd
{
  stStockSceneUserCmd()
  {
    byCmd = STOCK_SCENE_USERCMD;
  }
};
struct stStockBillUserCmd : public stNullUserCmd
{
  stStockBillUserCmd()
  {
    byCmd = STOCK_BILL_USERCMD;
  }
};
/// 股票密码
#define PASSWORD_STOCKPARA 1
struct stPassowrdStockUserCmd : public stStockBillUserCmd
{
  stPassowrdStockUserCmd()
  {
    byParam = PASSWORD_STOCKPARA;
    bzero(byPawword,sizeof(byPawword));
    bzero(byNew1,sizeof(byNew1));
    bzero(byNew2,sizeof(byNew2));
  }
  char byPawword[MAX_PASSWORD];  /// 当前密码
  char byNew1[MAX_PASSWORD];    /// 新密码
  char byNew2[MAX_PASSWORD];    /// 确认密码
};

/// 设置股票密码返回
enum
{
  STOCK_LOGIN_OK,/// 登陆ok
  STOCK_LOGIN_NOTLOGIN,/// 未登陆(提示请先登陆)
  STOCK_OPEN_OK,/// 启用帐号ok
  STOCK_CHANGE_OK,/// 修改密码
  STOCK_ERROR,/// 密码不对
  STOCK_DIFF,/// 两次输入密码不一致
  STOCK_NONE,/// 密码不能为空
  STOCK_SHORT,/// 密码太短
  STOCK_EXIST,/// 帐号已经存在
  STOCK_SERVER_WRONG,/// 服务器错误
  STOCK_GOLDLIST_MAX,/// 股票卖单满
  STOCK_MONEYLIST_MAX,/// 股票卖单满
};
#define RETUEN_PASSWORD_STOCKPARA 2
struct stReturnPasswordStockIserCmd : public stStockBillUserCmd
{
  stReturnPasswordStockIserCmd()
  {
    byParam = RETUEN_PASSWORD_STOCKPARA;
  }
  BYTE byReturn;  ///密码设置返回类型
};
/// 请求股票帐号余额
#define QUERY_FUND_STOCKPARA 3
struct stQueryFundStockUserCmd : public stStockBillUserCmd
{
  stQueryFundStockUserCmd() 
  {
    byParam = QUERY_FUND_STOCKPARA;
  }
  
};

/// 返回当前股票帐号余额
#define RETURN_FUND_STOCKPARA 4 
struct stReturnFundStockUserCmd : public stStockBillUserCmd
{
  stReturnFundStockUserCmd() 
  {
    byParam = RETURN_FUND_STOCKPARA;
  }
  DWORD dwGold;/// 当前帐号金币
  DWORD dwMoney;/// 当前帐号银币
};
 
/// 向股票帐号注入资金
#define TRANSFER_FUND_SAVE_STOCKPARA 5
struct stTransferFundStockSaveUserCmd : public stStockSceneUserCmd
{
  stTransferFundStockSaveUserCmd() 
  {
    byParam = TRANSFER_FUND_SAVE_STOCKPARA;
  }
  DWORD dwGold;/// 操作金币数量
  DWORD dwMoney;/// 操作银币数量
};

/// 从股票帐号提取资金
#define TRANSFER_FUND_FETCH_STOCKPARA 6 
struct stTransferFundStockFetchUserCmd : public stStockBillUserCmd
{
  stTransferFundStockFetchUserCmd() 
  {
    byParam = TRANSFER_FUND_FETCH_STOCKPARA;
  }
  DWORD dwGold;/// 操作金币数量
  DWORD dwMoney;/// 操作银币数量
};
 
/// 委托卖单
#define CONSIGN_GOLD_STOCKPARA 7 
struct stConsignGoldStockUserCmd : public stStockBillUserCmd
{
  stConsignGoldStockUserCmd() 
  {
    byParam = CONSIGN_GOLD_STOCKPARA;
  }
  DWORD dwNum;/// 金币数量
};
 
/// 委托买单
#define CONSIGN_MONEY_STOCKPARA 8
struct stConsignMoneyStockUserCmd : public stStockBillUserCmd
{
  stConsignMoneyStockUserCmd() 
  {
    byParam = CONSIGN_MONEY_STOCKPARA;
  }
  DWORD dwNum;/// 银币数量
};
/// 撤销卖单
#define CONSIGN_CANCEL_GOLD_STOCKPARA 9
struct stConsignCancelGoldStockUserCmd : public stStockBillUserCmd
{
  stConsignCancelGoldStockUserCmd() 
  {
    byParam = CONSIGN_CANCEL_GOLD_STOCKPARA;
  }
  DWORD dwNum;/// 卖单流水号
};

/// 撤销买单
#define CONSIGN_CANCEL_MONEY_STOCKPARA 10
struct stConsignCancelMoneyStockUserCmd : public stStockBillUserCmd
{
  stConsignCancelMoneyStockUserCmd() 
  {
    byParam = CONSIGN_CANCEL_MONEY_STOCKPARA;
  }
  DWORD dwNum;/// 卖单流水号
};
enum StockType
{
  STOCK_GOLD,
  STOCK_MONEY,
};
struct StockList
{
  DWORD id;      /// 流水号
  DWORD dwNum;    /// 数量
  DWORD dwPrice;  /// 委托价格
  DWORD dwTime;/// 委托时间
};
/// 请求未成交委托单
#define REQUEST_CONSIGN_LIST_STOCKPARA 11
struct stRequestConsignListStockUserCmd : public stStockBillUserCmd
{
  stRequestConsignListStockUserCmd() 
  {
    byParam = REQUEST_CONSIGN_LIST_STOCKPARA;
  }
};

/// 未成交的金币委托单
#define CONSIGN_GOLD_LIST_STOCKPARA 12
struct stConsignGoldListStockUserCmd : public stStockBillUserCmd
{
  stConsignGoldListStockUserCmd() 
  {
    byParam = CONSIGN_GOLD_LIST_STOCKPARA;
  }
  DWORD size;
  StockList list[0];
};
/// 未成交的银币委托单
#define CONSIGN_MONEY_LIST_STOCKPARA 13
struct stConsignMoneyListStockUserCmd : public stStockBillUserCmd
{
  stConsignMoneyListStockUserCmd() 
  {
    byParam = CONSIGN_MONEY_LIST_STOCKPARA;
  }
  DWORD size;
  StockList list[0];
};
/// 请求撤单
#define REQUEST_CANCEL_LIST_STOCKPARA 14
struct stRequestCancelListStockUserCmd : public stStockBillUserCmd
{
  stRequestCancelListStockUserCmd() 
  {
    byParam = REQUEST_CANCEL_LIST_STOCKPARA;
  }
  DWORD id;
  BYTE byType;
};
enum
{
  STOCK_CANCEL_ERROR,
  STOCK_CANCEL_OK,
};
/// 应答撤单
#define RETURN_CANCEL_LIST_STOCKPARA 15
struct stReturnCancelListStockUserCmd : public stStockBillUserCmd
{
  stReturnCancelListStockUserCmd() 
  {
    byParam = RETURN_CANCEL_LIST_STOCKPARA;
  }
  DWORD id;
  BYTE byType;
  BYTE byReturn;/*0表示失败,1表示成功*/
};
/// 请求排行前10位的单子
#define REQUEST_FIRSTTEN_LIST_STOCKPARA 16
struct stRequestFirstTenListStockUserCmd : public stStockBillUserCmd
{
  stRequestFirstTenListStockUserCmd() 
  {
    byParam = REQUEST_FIRSTTEN_LIST_STOCKPARA;
  }
};

struct FirstTen
{
  DWORD dwNum;
  DWORD dwPrice;
};
/// 排行前5位的价格和数量
#define FIRSTFIVE_LIST_STOCKPARA 17
struct stFirstFiveListStockUserCmd : public stStockBillUserCmd
{
  stFirstFiveListStockUserCmd() 
  {
    byParam = FIRSTFIVE_LIST_STOCKPARA;
  }
  BYTE byType;//买或卖
  DWORD size;
  FirstTen list[0];
};

/// 提交委托单
#define PUT_LIST_STOCKPARA 18
struct stPutListStockUserCmd : public stStockBillUserCmd
{
  stPutListStockUserCmd() 
  {
    byParam = PUT_LIST_STOCKPARA;
  }
  DWORD dwNum;  //金币或者银币数量
  DWORD dwPrice;  //单价(银币/金币)
  BYTE  byType;  //单子类型,金币或银币
};
/// 返回提交的委托单
#define RETURN_PUT_LIST_STOCKPARA 19
struct stReturnPutListStockUserCmd : public stStockBillUserCmd
{
  stReturnPutListStockUserCmd() 
  {
    byParam = RETURN_PUT_LIST_STOCKPARA;
  }
  StockList list;
};
//股票历史数据结构
struct ConsignHistoryType
{
  ConsignHistoryType()
  {
    dwTime=0;
    dwPrice=0;
    dwTotal=0;
  }
  DWORD dwTime;
  WORD dwPrice;
  WORD dwTotal;
};
/// 玩家请求大盘历史交易数据
#define REQUEST_HISTORY_STOCKPARA 20
struct stRequstHistoryStockUserCmd : public stStockBillUserCmd
{
  stRequstHistoryStockUserCmd() 
  {
    byParam = REQUEST_HISTORY_STOCKPARA;
    begintime=0;
    num=0;
  }
  DWORD begintime;
  DWORD num;
};
/// 返回最新大盘历史数据(当前一分钟的统计数据)
#define NEW_HISTORY_STOCKPARA 21
struct stNewHistoryStockUserCmd : public stStockBillUserCmd
{
  stNewHistoryStockUserCmd() 
  {
    byParam = NEW_HISTORY_STOCKPARA;
  }
  ConsignHistoryType gold;
  ConsignHistoryType money;
};
/// 返回大盘历史金币数据(不定长)
#define HISTORY_GOLD_STOCKPARA 22
struct stHistoryGoldStockUserCmd : public stStockBillUserCmd
{
  stHistoryGoldStockUserCmd() 
  {
    byParam = HISTORY_GOLD_STOCKPARA;
  }
  DWORD size;
  ConsignHistoryType list[0];
};
/// 返回大盘历史银币数据(不定长)
#define HISTORY_MONEY_STOCKPARA 23
struct stHistoryMoneyStockUserCmd : public stStockBillUserCmd
{
  stHistoryMoneyStockUserCmd() 
  {
    byParam = HISTORY_MONEY_STOCKPARA;
  }
  DWORD size;
  ConsignHistoryType list[0];
};
/// 玩家请求自己历史交易数据
#define REQUEST_SELF_HISTORY_STOCKPARA 24
struct stRequstSelfHistoryStockUserCmd : public stStockBillUserCmd
{
  stRequstSelfHistoryStockUserCmd() 
  {
    byParam = REQUEST_SELF_HISTORY_STOCKPARA;
    begintime=0;
    num=0;
  }
  DWORD begintime;
  DWORD num;
};
//个人委托单历史数据
struct ConsignSelfHistoryType
{
  ConsignSelfHistoryType()
  {
  }
  DWORD dwID;
  DWORD wdNum;
  DWORD wdCommitPrice;
  DWORD wdPrice;
  DWORD dwCommitTime;
  DWORD dwOkTime;
};
/// 返回自己历史金币数据(不定长)
#define SELF_HISTORY_GOLD_STOCKPARA 25
struct stSelfHistoryGoldStockUserCmd : public stStockBillUserCmd
{
  stSelfHistoryGoldStockUserCmd() 
  {
    byParam = SELF_HISTORY_GOLD_STOCKPARA;
  }
  DWORD size;
  ConsignSelfHistoryType list[0];
};
/// 返回自己历史银币数据(不定长)
#define SELF_HISTORY_MONEY_STOCKPARA 26
struct stSelfHistoryMoneyStockUserCmd : public stStockBillUserCmd
{
  stSelfHistoryMoneyStockUserCmd() 
  {
    byParam = SELF_HISTORY_MONEY_STOCKPARA;
  }
  DWORD size;
  ConsignSelfHistoryType list[0];
};
/// 股票系统停止服务
#define STOP_SERVICE_STOCKPARA 27
struct stStopServiceStockUserCmd : public stStockBillUserCmd
{
  stStopServiceStockUserCmd() 
  {
    byParam = STOP_SERVICE_STOCKPARA;
  }
};
 
/// 清除未成交委托单
#define CONSIGN_CLEAN_LIST_STOCKPARA 28
struct stConsignCleanListStockUserCmd : public stStockBillUserCmd
{
  stConsignCleanListStockUserCmd() 
  {
    byParam = CONSIGN_CLEAN_LIST_STOCKPARA;
  }
};

/// 请求得到当前用户的激活和登陆状态
#define REQUEST_STATE_STOCKPARA 29
struct stRequestStateStockUserCmd : public stStockBillUserCmd
{
  stRequestStateStockUserCmd() 
  {
    byParam = REQUEST_STATE_STOCKPARA;
  }
  bool  active;
  bool  login;
};
//股票系统控制指令
#define PARA_CANCELLISTALL_STOCKPARA  30
struct t_CancelListAllStock_GateScene : public stStockBillUserCmd
{
  t_CancelListAllStock_GateScene()
    {
      byParam = PARA_CANCELLISTALL_STOCKPARA;
    }
};
//////////////////////////////////////////////////////////////
/// 定义股票命令结束
//////////////////////////////////////////////////////////////


//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义答题命令开始
//////////////////////////////////////////////////////////////
struct stQuizUserCmd : public stNullUserCmd
{
  stQuizUserCmd()
  {
    byCmd = QUIZ_USERCMD;
  }
};

enum
{
  QUIZ_WORLD,
  QUIZ_PERSONAL
};

enum 
{
  QUIZ_QUESTION,// 询问是否接受问答竞赛
  QUIZ_YES,// 参与竞赛
  QUIZ_NO         // 拒绝竞赛
};

const BYTE QUERY_QUIZ_PARA = 1;
struct stQueryQuiz : public stQuizUserCmd
{
  stQueryQuiz() 
  {
    byParam = QUERY_QUIZ_PARA;
    byMsgType = QUIZ_QUESTION;
    byQuizType = 0;
  }
  
  BYTE byMsgType;
  BYTE byQuizType; // 1是普通全国，2是活动
};

enum
{
  CREATE_QUESTION,// 请求进行智力问答
  CREATE_YES,// 请求成功
  CREATE_FAIL   // 金钱不足，失败
};

const BYTE CREATE_QUIZ_PARA = 2;
struct stCreateQuiz : public stQuizUserCmd
{
  stCreateQuiz() 
  {
    byParam = CREATE_QUIZ_PARA;
    byType  = CREATE_QUESTION;
    dwMoney = 100;
  }

  DWORD dwMoney;  // 个人问答时，所需银两
  BYTE byType;
};

const BYTE QUESTION_QUIZ_PARA = 3;
struct stQuestionQuiz : public stQuizUserCmd
{
  stQuestionQuiz()
  {
    byParam = QUESTION_QUIZ_PARA;
    dwSize = 7;
    dwTotal = 0;
  }

  DWORD dwID;  // 题目序号
  BYTE  bySpareTime; // 剩余时间
  BYTE  byNextStartTime;
  BYTE  dwSize; // 题目条数
  DWORD dwTotal;  // 总人数
  
  char subject[0]; // 题目 答案一 答案二 答案三....，中间以0做为分隔
};

const BYTE ANSWER_QUIZ_PARA = 4;
struct stAnswerQuiz : public stQuizUserCmd
{
  stAnswerQuiz()
  {
    byParam = ANSWER_QUIZ_PARA;
    byLuck = 0;
  }

  DWORD dwID;   // 题目序号
  BYTE byType;   // 竞赛类型
  BYTE  byLuck;  // 是否使用幸运星,1使用，其它值是不使用
  DWORD dwScore;  // 得分

  DWORD answerID; // 答案
};

const BYTE ANSWER_RETURN_QUIZ_PARA = 5;
struct stAnswerReturnQuiz : public stQuizUserCmd
{
  stAnswerReturnQuiz()
  {
    byParam = ANSWER_RETURN_QUIZ_PARA;
    byAnswerStatus = -1;
  }

  int byAnswerStatus; // -1:放弃，0:回答正确,1:回答错误
};

struct rank_elem
{
  char name[MAX_NAMESIZE + 1];   // 玩家姓名
  char countryName[MAX_NAMESIZE + 1]; // 国家名称
  int  score;  // 得分
  int  useJob; //sky 职业
  int  rank; // 玩家排名
};

const BYTE QUIZ_POS_LIST_PARA = 6;
struct stQuizPosList : public stQuizUserCmd
{
  stQuizPosList()
  {
    byParam = QUIZ_POS_LIST_PARA;
    bzero(rank_list,sizeof(rank_list));
    dwSize = 1;
  }
  
  DWORD dwSize;
  rank_elem rank_list[21];
};

const BYTE QUIZ_CUR_SCORE_PARA = 7;
struct stQuizCurScore : public stQuizUserCmd
{
  stQuizCurScore()
  {
    byParam = QUIZ_CUR_SCORE_PARA;
    dwScore = 0;
    dwGrace = 0;
  }

  DWORD dwScore; // 本次答题累积分数
  DWORD dwGrace; // 本次答题累积文采
};

const BYTE QUIZ_EXIT_PARA = 8;
struct stQuizExit : public stQuizUserCmd
{
  stQuizExit()
  {
    byParam = QUIZ_EXIT_PARA;
  }
};

const BYTE QUIZ_PARAM_PARA = 9;
struct stQuizParam : public stQuizUserCmd
{
  stQuizParam() 
  {
    byParam = QUIZ_PARAM_PARA;
    byReadQuestionTime = 10;
    byAnswerQuestionTime = 10;
    byCalcTime = 5;
    bySubjectNumber = 90;
  }

  BYTE byReadQuestionTime;  // 读题时间
  BYTE byAnswerQuestionTime;  // 答题时间
  BYTE byCalcTime;    // 计算答案时间
  BYTE bySubjectNumber;    // 总题数
  BYTE byType;      // 竞赛类型
  BYTE byStartTime;    // 竞赛开始剩余时间
};

//////////////////////////////////////////////////////////////
/// 定义答题命令结束
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/// 定义NPC争夺命令开始
//////////////////////////////////////////////////////////////
struct stNpcDareUserCmd : public stNullUserCmd
{
  stNpcDareUserCmd()
  {
    byCmd = NPCDARE_USERCMD;
  }
};

const BYTE NPCDARE_DARE_PARA = 1;
struct stDareNpcDare : public stNpcDareUserCmd
{
  stDareNpcDare() 
  {
    byParam = NPCDARE_DARE_PARA;
  }
  DWORD dwNpcID;
};

const BYTE NPCDARE_GETGOLD_PARA = 2;
struct stDareNpcGetGold : public stNpcDareUserCmd
{
  stDareNpcGetGold() 
  {
    byParam = NPCDARE_GETGOLD_PARA;
  }
  DWORD dwNpcID;
};

enum
{
  QUESTION_NPCDARE_HOLD,// 查询城市所属
  QUESTION_NPCDARE_DARE,// 当天城市争夺战
};

// 查询问NPC争夺战信息
const BYTE QUESTION_NPCDARE_INFO_PARA = 3;
struct stQuestionNpcDareInfo : public stNpcDareUserCmd
{
  stQuestionNpcDareInfo()
  {
    byParam = QUESTION_NPCDARE_INFO_PARA;
  }
  BYTE byType;  
  DWORD dwNpcID;
};
//////////////////////////////////////////////////////////////
/// 定义NPC争夺命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义与GM工具交互的命令开始
//////////////////////////////////////////////////////////////
struct stGmToolUserCmd : public stNullUserCmd
{
  stGmToolUserCmd()
  {
    byCmd = GMTOOL_USERCMD;
  }
};

const BYTE CHAT_GMTOOL_PARA = 1;
struct stChatGmTool : public stGmToolUserCmd
{
  char userName[MAX_NAMESIZE + 1];
  DWORD countryID;
  DWORD sceneID;
  stChannelChatUserCmd chat_cmd;
  stChatGmTool() 
  {
    byParam = CHAT_GMTOOL_PARA;
    countryID = 0;
    sceneID = 0;
  }
};

const BYTE MSG_GMTOOL_PARA = 2;
struct stMsgGmTool : public stGmToolUserCmd
{
  BYTE type;//定单类型
  char content[512];//主要内容
  BYTE contact;//联系方式
  char tele[64];//地址、电话
  char hisName[MAX_NAMESIZE + 1];//被举报者
  char bugCountry[8];//bug发生国家
  char bugMap[16];//bug发生地图
  char bugPos[8];//bug发生位置
  char bugTime[64];//发生时间
  char progName[64];//疑似外挂名称
  BYTE behavior;//不良游戏现象
  stMsgGmTool()
  {

    type = 0;
    bzero(content,sizeof(content));
    contact = 0;
    bzero(tele,sizeof(tele));
    bzero(hisName,sizeof(hisName));
    bzero(bugCountry,sizeof(bugCountry));
    bzero(bugMap,sizeof(bugMap));
    bzero(bugPos,sizeof(bugPos));
    bzero(bugTime,sizeof(bugTime));
    bzero(progName,sizeof(progName));
    behavior = 0;
  }
};

//////////////////////////////////////////////////////////////
/// 定义与GM工具交互的命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 卡通宠物指令定义开始
//////////////////////////////////////////////////////////////

//宝宝的状态
enum cartoonState
{
  CARTOON_STATE_PUTAWAY,//收起
  CARTOON_STATE_FOLLOW,//跟随主人
  CARTOON_STATE_WAITING,//等待领养
  CARTOON_STATE_ADOPTED  //被领养
};

//宝宝的数据
struct t_CartoonData
{
  //DWORD cartoonID;    //宝宝id
  char name[MAX_NAMESIZE + 1];  //名字
  DWORD npcID;      //npcid
  DWORD masterID;      //主人id
  char masterName[MAX_NAMESIZE + 1];  //主人名字
  BYTE lv;      //等级
  DWORD exp;      //经验
  DWORD maxExp;      //升级经验
  DWORD addExp;      //给主人增加的经验
  BYTE state;    //状态
  char adopter[MAX_NAMESIZE + 1];  //领养人
  DWORD time;      //挂机剩余时间(秒)
  DWORD sp;      //精气值
  DWORD maxSp;      //最大精气值
  DWORD masterLevel;    //主人等级
  BYTE repair;      //自动修理主人装备

  t_CartoonData & operator = (const t_CartoonData& reg)
  {
    bcopy(&reg,this,sizeof(t_CartoonData),sizeof(t_CartoonData));

    return *this;
  }

  t_CartoonData & operator << (const t_CartoonData& reg)
  {
    addExp += reg.addExp;
    state = reg.state;
    bcopy(reg.adopter,adopter,MAX_NAMESIZE,sizeof(adopter));
    time = reg.time;
    /*
    DWORD e = addExp;
    bcopy(&reg,this,sizeof(t_CartoonData));
    addExp += e;
    */

    return *this;
  }
};

struct stCartoonUserCmd : public stNullUserCmd
{
  stCartoonUserCmd()
  {
    byCmd = CARTOON_USERCMD;
  }
};

#define BUY_CARTOON_PARA 1  //购买
struct stBuyCartoonCmd : public stCartoonUserCmd
{
  stBuyCartoonCmd()
  {
    byParam = BUY_CARTOON_PARA;
  }
  DWORD npcID;
};

#define ADD_CARTOON_PARA 2  //添加列表
struct stAddCartoonCmd : public stCartoonUserCmd
{
  stAddCartoonCmd()
  {
    byParam = ADD_CARTOON_PARA;
  }
  bool isMine;
  DWORD cartoonID;
  t_CartoonData data;
};

#define REMOVE_CARTOON_PARA 3  //移除列表
struct stRemoveCartoonCmd : public stCartoonUserCmd
{
  stRemoveCartoonCmd()
  {
    byParam = REMOVE_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define FOLLOW_CARTOON_PARA 4  //跟随/取消跟随
struct stFollowCartoonCmd : public stCartoonUserCmd
{
  stFollowCartoonCmd()
  {
    byParam = FOLLOW_CARTOON_PARA;
  }
  DWORD cartoonID;//取消跟随填0
};

#define LETOUT_CARTOON_PARA 5  //放出，使别人可以领养
struct stLetOutCartoonCmd : public stCartoonUserCmd
{
  stLetOutCartoonCmd()
  {
    byParam = LETOUT_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define ADOPT_CARTOON_PARA 6  //领养宠物
struct stAdoptCartoonCmd : public stCartoonUserCmd
{
  stAdoptCartoonCmd()
  {
    byParam = ADOPT_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define RETURN_CARTOON_PARA 7  //归还宠物
struct stReturnCartoonCmd : public stCartoonUserCmd
{
  stReturnCartoonCmd()
  {
    byParam = RETURN_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define GETBACK_CARTOON_PARA 8  //收回宠物
struct stGetBackCartoonCmd : public stCartoonUserCmd
{
  stGetBackCartoonCmd()
  {
    byParam = GETBACK_CARTOON_PARA;
  }
};

#define DRAWEXP_CARTOON_PARA 9  //提取经验
struct stDrawExpCartoonCmd : public stCartoonUserCmd
{
  stDrawExpCartoonCmd()
  {
    byParam = DRAWEXP_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define CHANGENAME_CARTOON_PARA 10  //改名字
struct stChangeNameCartoonCmd : public stCartoonUserCmd
{
  stChangeNameCartoonCmd()
  {
    byParam = CHANGENAME_CARTOON_PARA;
  }
  DWORD cartoonID;
  char name[MAX_NAMESIZE + 1];
};

#define ADD_WAITING_CARTOON_PARA 11  //添加等待列表
struct stAddWaitingCartoonCmd : public stCartoonUserCmd
{
  stAddWaitingCartoonCmd()
  {
    byParam = ADD_WAITING_CARTOON_PARA;
  }
  DWORD cartoonID;    //宝宝id
  DWORD npcID;    //NPC ID
  char name[MAX_NAMESIZE + 1];  //名字
  char masterName[MAX_NAMESIZE + 1];  //主人名字
  BYTE state;    //状态
  DWORD time;      //挂机剩余时间(秒)

  void operator = (const t_CartoonData& reg)
  {
    npcID = reg.npcID;
    strncpy(name,reg.name, MAX_NAMESIZE);
    strncpy(masterName,reg.masterName, MAX_NAMESIZE);
    state = reg.state;
    time = reg.time;
  }
};

#define REMOVE_WAITING_CARTOON_PARA 12  //移除等待列表
struct stRemoveWaitingCartoonCmd : public stCartoonUserCmd
{
  stRemoveWaitingCartoonCmd()
  {
    byParam = REMOVE_WAITING_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define REQUEST_LIST_CARTOON_PARA 13  //请求等待列表
struct stRequestListCartoonCmd : public stCartoonUserCmd
{
  stRequestListCartoonCmd()
  {
    byParam = REQUEST_LIST_CARTOON_PARA;
  }
};

#define SALE_CARTOON_PARA 14  //卖出宠物
struct stSaleCartoonCmd : public stCartoonUserCmd
{
  DWORD cartoonID;
  stSaleCartoonCmd()
  {
    byParam = SALE_CARTOON_PARA;

    cartoonID = 0;
  }
};

#define CHARGE_CARTOON_PARA 15  //充值
struct stChargeCartoonCmd : public stCartoonUserCmd
{
  stChargeCartoonCmd()
  {
    byParam = CHARGE_CARTOON_PARA;
  }
  DWORD cartoonID;
  DWORD time;//充多长时间(秒)
};

#define HP_EXP_CARTOON_PARA 16  //同步sp和经验
struct stHpExpCartoonCmd : public stCartoonUserCmd
{
  stHpExpCartoonCmd()
  {
    byParam = HP_EXP_CARTOON_PARA;
  }
  DWORD cartoonID;
  DWORD sp;
  DWORD exp;
};

#define SELL_ALL_CARTOON_PARA 17  //卖包裹里所有物品
struct stSellAllCartoonCmd : public stCartoonUserCmd
{
  stSellAllCartoonCmd()
  {
    byParam = SELL_ALL_CARTOON_PARA;
  }
};

#define CONSIGN_CARTOON_PARA 18  //委托领养
struct stConsignCartoonCmd : public stCartoonUserCmd
{
  stConsignCartoonCmd()
  {
    byParam = CONSIGN_CARTOON_PARA;
  }
  DWORD cartoonID;
  char name[MAX_NAMESIZE + 1];//请求时是被委托人，被请求时是委托人
};

#define CONSIGN_RET_CARTOON_PARA 19  //确认委托领养
struct stConsignRetCartoonCmd : public stCartoonUserCmd
{
  stConsignRetCartoonCmd()
  {
    byParam = CONSIGN_RET_CARTOON_PARA;
  }
  DWORD cartoonID;
  BYTE ret;//0：拒绝 1：同意
};

#define REPAIR_CARTOON_PARA 20  //设置自动修理
struct stRepairCartoonCmd : public stCartoonUserCmd
{
  stRepairCartoonCmd()
  {
    byParam = REPAIR_CARTOON_PARA;
  }
  DWORD cartoonID;
  BYTE repair;//0：关闭 1：打开
};

//////////////////////////////////////////////////////////////
// 卡通宠物指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义邮件命令开始
//////////////////////////////////////////////////////////////
const DWORD mail_postage = 50;  ///邮资50文

struct stMailUserCmd : public stNullUserCmd
{
  stMailUserCmd()
  {
    byCmd = MAIL_USERCMD;
  }
};

/*
const BYTE CHECK_ITEM_MAIL_PARA = 1;
struct stCheckItemMail : public stMailUserCmd
{
  DWORD itemID;
  stCheckItemMail()
  {
    byParam = CHECK_ITEM_MAIL_PARA;
  }
};

enum CheckReturn
{
  CHECK_RETURN_SUCCESS = 1,
  CHECK_RETURN_FAIL = 2
};
const BYTE CHECK_RETURN_MAIL_PARA = 2;
struct stCheckReturnMail : public stMailUserCmd
{
  CheckReturn retCode;
  stCheckReturnMail()
  {
    byParam = CHECK_RETURN_MAIL_PARA;
  }
};
*/

//发送邮件
const BYTE SEND_MAIL_PARA = 3;
struct stSendMail : public stMailUserCmd
{
  char toName[MAX_NAMESIZE + 1];
  char title[MAX_NAMESIZE + 1];
  char text[256];
  DWORD sendMoney;
  DWORD recvMoney;
  DWORD sendGold;
  DWORD recvGold;
  DWORD itemID;
  stSendMail() 
  {
    byParam = SEND_MAIL_PARA;
    sendMoney = 0;
    recvMoney = 0;
    sendGold = 0;
    recvGold = 0;
    itemID = 0;
  }
};

/*
enum sendReturn
{
  SEND_RETURN_SUCCESS = 1,
  SEND_RETURN_FAIL = 2
};
const BYTE SEND_RETURN_MAIL_PARA = 4;
struct stSendReturnMail : public stMailUserCmd
{
  sendReturn retCode;
  stSendReturnMail()
  {
    byParam = SEND_RETURN_MAIL_PARA;
  }
};
*/

//请求邮件列表
const BYTE GET_LIST_MAIL_PARA = 5;
struct stGetListMail : public stMailUserCmd
{
  stGetListMail()
  {
    byParam = GET_LIST_MAIL_PARA;
  }
};

//添加邮件列表
const BYTE ADD_LIST_MAIL_PARA = 6;
struct stAddListMail : public stMailUserCmd
{
  DWORD id;
  BYTE state;
  char fromName[MAX_NAMESIZE + 1];
  bool accessory;
  DWORD endTime;
  BYTE type;  //0:普通 1：系统
  stAddListMail()
  {
    byParam = ADD_LIST_MAIL_PARA;
    id = 0;
    state = 0;
    accessory = 0;
    endTime = 0;
    bzero(fromName,sizeof(fromName));
    type = 0;
  }
};

//请求邮件内容
const BYTE OPEN_MAIL_PARA = 7;
struct stOpenMail : public stMailUserCmd
{
  DWORD mailID;
  stOpenMail()
  {
    byParam = OPEN_MAIL_PARA;
  }
};

//邮件内容
const BYTE CONTENT_MAIL_PARA = 8;
struct stContentMail : public stMailUserCmd
{
  DWORD mailID;
  char title[MAX_NAMESIZE + 1];
  bool accessory;
  char text[256];
  DWORD sendMoney;
  DWORD recvMoney;
  DWORD sendGold;
  DWORD recvGold;
  t_Object item;
  stContentMail()
  {
    byParam = CONTENT_MAIL_PARA;
    mailID = 0;
    bzero(title,sizeof(title));
    accessory = false;
    bzero(text,sizeof(text));
    sendMoney = recvMoney = 0;
    sendGold = 0;
    recvGold = 0;
    bzero(&item,sizeof(item));
  }
};

//取得邮件附件
const BYTE GET_ITEM_MAIL_PARA = 9;
struct stGetItemMail : public stMailUserCmd
{
  DWORD mailID;
  stGetItemMail()
  {
    byParam = GET_ITEM_MAIL_PARA;
  }
};

//删除邮件附件
const BYTE REMOVE_ITEM_MAIL_PARA = 10;
struct stRemoveItemMail : public stMailUserCmd
{
  DWORD mailID;
  stRemoveItemMail()
  {
    byParam = REMOVE_ITEM_MAIL_PARA;
  }
};

//删除邮件
const BYTE DEL_MAIL_PARA = 11;
struct stDelMail : public stMailUserCmd
{
  DWORD mailID;
  stDelMail()
  {
    byParam = DEL_MAIL_PARA;
  }
};

//新邮件提示
const BYTE NOTIFY_NEW_MAIL_PARA = 12;
struct stNotifyNewMail : public stMailUserCmd
{
  stNotifyNewMail()
  {
    byParam = NOTIFY_NEW_MAIL_PARA;
  }
};

//退回邮件
const BYTE TURN_BACK_MAIL_PARA = 13;
struct stTurnBackMail : public stMailUserCmd
{
  DWORD mailID;
  stTurnBackMail()
  {
    byParam = TURN_BACK_MAIL_PARA;
  }
};

/*
*/
//////////////////////////////////////////////////////////////
/// 定义邮件命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义拍卖命令开始
//////////////////////////////////////////////////////////////
//const DWORD mail_postage = 50;  ///邮资50文

struct stAuctionUserCmd : public stNullUserCmd
{
  stAuctionUserCmd()
  {
    byCmd = AUCTION_USERCMD;
  }
};

enum
{
  AUCTION_WEAPOM_SWORD = 1,
  AUCTION_WEAPOM_AXE = 2,
  AUCTION_WEAPOM_BOW = 3,
  AUCTION_WEAPOM_STICK = 4,
  AUCTION_WEAPOM_WAND = 5,
  AUCTION_WEAPOM_FAN = 6,
  AUCTION_EQUIP_HEAD = 11,
  AUCTION_EQUIP_BODY = 12,
  AUCTION_EQUIP_WRIST = 13,
  AUCTION_EQUIP_SHIELD = 14,
  AUCTION_EQUIP_WAIST = 15,
  AUCTION_EQUIP_FOOT = 16,
  AUCTION_ACCESSORY_NECKLACE = 21,
  AUCTION_ACCESSORY_RING = 22,
  AUCTION_ACCESSORY_ADORNMENT = 23,
  AUCTION_BOOK_FIGHTER = 31,
  AUCTION_BOOK_ARCHER = 32,
  AUCTION_BOOK_WIZARD = 33,
  AUCTION_BOOK_SUMMONER = 34,
  AUCTION_BOOK_PRIEST = 35,
  AUCTION_BOOK_SPECIAL = 36,
  AUCTION_OTHER_GEM = 41,
  AUCTION_OTHER_ITEM = 42,
  AUCTION_OTHER_MATERIAL = 43,
  AUCTION_OTHER_LEECHDOM = 44
};

const BYTE AUCTION_BID_TYPE_MONEY = 0;
const BYTE AUCTION_BID_TYPE_GOLD = 1;

//拍卖一件物品
const BYTE SALE_AUCTION_PARA = 1;
struct stSaleAuction : public stAuctionUserCmd
{
  DWORD itemID;
  DWORD minMoney;
  DWORD maxMoney;
  DWORD minGold;
  DWORD maxGold;
  BYTE bidType;
  stSaleAuction()
  {
    byParam = SALE_AUCTION_PARA;
    itemID = 0xffffffff;
    minMoney = 0;
    maxMoney = 0;
    minGold = 0;
    maxGold = 0;
    bidType = 0;
  }
};

//竞价
const BYTE BID_AUCTION_PARA = 2;
struct stBidAuction : public stAuctionUserCmd
{
  DWORD auctionID;
  DWORD money;
  DWORD gold;
  stBidAuction()
  {
    byParam = BID_AUCTION_PARA;
    auctionID = 0;
    money = 0;
    gold = 0;
  }
};

//添加列表
const BYTE ADD_LIST_AUCTION_PARA = 3;
struct stAddListAuction : public stAuctionUserCmd
{
  BYTE list;//1:查看列表 2:竞标列表 3:拍卖列表 4:所有列表
  DWORD auctionID;
  DWORD minMoney;
  DWORD maxMoney;
  DWORD minGold;
  DWORD maxGold;
  DWORD endTime;
  t_Object item;
  bool mine;//是否我的价格最高
  char owner[MAX_NAMESIZE + 1];//拍卖者
  DWORD max;//总共多少个
  BYTE bidType;
  stAddListAuction()
  {
    byParam = ADD_LIST_AUCTION_PARA;

    list = 0;
    auctionID = 0;
    minMoney = 0;
    maxMoney = 0;
    minGold = 0;
    maxGold = 0;
    bzero(&item,sizeof(item));
    mine = false;
    bzero(owner,sizeof(owner));
    max = 0;
    bidType = 0;
  }
};

//移除列表
const BYTE REMOVE_LIST_AUCTION_PARA = 4;
struct stRemoveListAuction : public stAuctionUserCmd
{
  BYTE list;//1:查看列表 2:竞标列表 3:拍卖列表 4:所有列表
  DWORD auctionID;
  stRemoveListAuction()
  {
    byParam = REMOVE_LIST_AUCTION_PARA;

    list = 0;
    auctionID = 0;
  }
};

//搜索
const BYTE QUERY_AUCTION_PARA = 5;
struct stQueryAuction : public stAuctionUserCmd
{
  BYTE type;
  char name[MAX_NAMESIZE + 1];
  BYTE quality;//1普通,2蓝色,3金色,5神圣
  WORD level;
  WORD page;
  stQueryAuction()
  {
    byParam = QUERY_AUCTION_PARA;

    type = 0;
    bzero(name,sizeof(name));
    quality = 0;
    level = (WORD)-1;
    page = 0;
  }
};

//取消拍卖
const BYTE CANCEL_SALE_AUCTION_PARA = 6;
struct stCancelSaleAuction : public stAuctionUserCmd
{
  DWORD auctionID;
  stCancelSaleAuction()
  {
    byParam = CANCEL_SALE_AUCTION_PARA;

    auctionID = 0;
  }
};

//请求列表
const BYTE GET_LIST_AUCTION_PARA = 7;
struct stGetListAuction : public stAuctionUserCmd
{
  BYTE list;//2:竞标列表 3:拍卖列表 
  stGetListAuction()
  {
    byParam = GET_LIST_AUCTION_PARA;

    list = 0;
  }
};

//////////////////////////////////////////////////////////////
/// 定义拍卖命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义监狱命令开始
//////////////////////////////////////////////////////////////

struct stPrisonUserCmd : public stNullUserCmd
{
  stPrisonUserCmd()
  {
    byCmd = PRISON_USERCMD;
  }
};

//请求出狱
const BYTE OUT_PRISON_PARA = 1;
struct stOutPrison : public stPrisonUserCmd
{
  stOutPrison()
  {
    byParam = OUT_PRISON_PARA;
  }
};

//贿赂
const BYTE BRIBE_PRISON_PARA = 2;
struct stBribePrison : public stPrisonUserCmd
{
  DWORD money;
  stBribePrison()
  {
    byParam = BRIBE_PRISON_PARA;

    money = 0;
  }
};

//取保就医(帮别人洗PK值)
const BYTE BAIL_PRISON_PARA = 3;
struct stBailPrison : public stPrisonUserCmd
{
  char name[MAX_NAMESIZE + 1];
  DWORD money;
  stBailPrison()
  {
    byParam = BAIL_PRISON_PARA;

    bzero(name,sizeof(name));
    money = 0;
  }
};

//请求出牢狱
const BYTE LEAVE_PRISON_PARA = 4;
struct stLeavePrison : public stPrisonUserCmd
{
  stLeavePrison()
  {
    byParam = LEAVE_PRISON_PARA;
  }
};

//////////////////////////////////////////////////////////////
/// 定义监狱命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义礼官命令开始
//////////////////////////////////////////////////////////////

struct stGiftUserCmd : public stNullUserCmd
{
  stGiftUserCmd()
  {
    byCmd = GIFT_USERCMD;
  }
};

//请求活动列表
const BYTE GET_LIST_GIFT_PARA = 1;
struct stGetListGift : public stGiftUserCmd
{
  stGetListGift()
  {
    byParam = GET_LIST_GIFT_PARA;
  }
};

struct actTitle
{
  DWORD id;
  char name[MAX_NAMESIZE + 1];
  BYTE state;
};

//发送活动列表
const BYTE LIST_GIFT_PARA = 2;
struct stListGift : public stGiftUserCmd
{
  DWORD num;
  actTitle titles[0];
  stListGift()
  {
    byParam = LIST_GIFT_PARA;
    num = 0;
  }
};

//请求活动内容
const BYTE GET_DETAIL_GIFT_PARA = 3;
struct stGetDetailGift : public stGiftUserCmd
{
  DWORD id;
  stGetDetailGift()
  {
    byParam = GET_DETAIL_GIFT_PARA;
    id = 0;
  }
};

//发送活动内容
const BYTE DETAIL_GIFT_PARA = 4;
struct stDetailGift : public stGiftUserCmd
{
  DWORD id;//活动ID
  char text[MAX_CHATINFO];
  stDetailGift()
  {
    byParam = DETAIL_GIFT_PARA;
    id = 0;
    bzero(text,sizeof(text));
  }
};

//领取奖品
const BYTE GET_ITEM_GIFT_PARA = 5;
struct stGetItemGift : public stGiftUserCmd
{
  DWORD id;
  stGetItemGift()
  {
    byParam = GET_ITEM_GIFT_PARA;
    id = 0;
  }
};

//请求获奖名单
const BYTE GET_WINNER_GIFT_PARA = 6;
struct stGetWinnerGift : public stGiftUserCmd
{
  DWORD id;//活动ID
  stGetWinnerGift()
  {
    byParam = GET_WINNER_GIFT_PARA;
    id = 0;
  }
};

//发送获奖名单
const BYTE WINNER_GIFT_PARA = 7;
struct stWinnerGift : public stGiftUserCmd
{
  DWORD num;
  char winners[0];
  stWinnerGift()
  {
    byParam = WINNER_GIFT_PARA;
    num = 0;
  }
};

//////////////////////////////////////////////////////////////
/// 定义礼官命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义国家联盟命令开始
//////////////////////////////////////////////////////////////

struct stAllyUserCmd : public stNullUserCmd
{
  stAllyUserCmd()
  {
    byCmd = ALLY_USERCMD;
  }
};

enum
{
  QUESTION_COUNTRY_ALLY,// 发起请求
  YES_COUNTRY_ALLY,// 同意请求
  NO_COUNTRY_ALLY,// 拒绝请求
};

//请求结盟
#define REQ_COUNTRY_ALLY_PARA  1
struct stReqCountryAlly : public stAllyUserCmd
{
  stReqCountryAlly()
  {
    byParam = REQ_COUNTRY_ALLY_PARA;
    dwCountryID = 0;
    dwAllyCountryID = 0;
    byStatus = QUESTION_COUNTRY_ALLY;
  }
  
  DWORD dwCountryID; // 发起请求的国家,发起时不用填写
  DWORD dwAllyCountryID; // 被邀请的国家
  BYTE  byStatus;
};

// 设置盟国信息
#define UPDATE_COUNTRY_ALLY_PARA 2
struct stUpdateCountryAlly : public stAllyUserCmd
{
  stUpdateCountryAlly()
  {
    byParam = UPDATE_COUNTRY_ALLY_PARA;
    dwAllyCountryID = 0;
  }

  DWORD dwAllyCountryID;
};

// 取缔盟约
#define CANCEL_COUNTRY_ALLY_PARA 3
struct stCancelCountryAlly : public stAllyUserCmd
{
  stCancelCountryAlly()
  {
    byParam = CANCEL_COUNTRY_ALLY_PARA;
    dwAllyCountryID = 0;
  }

  DWORD dwAllyCountryID;
};

// 请求国家联盟信息
#define REQ_COUNTRY_ALLY_INFO_PARA 4
struct stReqCountryAllyInfo : public stAllyUserCmd
{
  stReqCountryAllyInfo()
  {
    byParam = REQ_COUNTRY_ALLY_INFO_PARA;
  }
};

// 返回国家联盟信息
#define RTN_COUNTRY_ALLY_INFO_PARA 5
struct stRtnCountryAllyInfo : public stAllyUserCmd
{
  stRtnCountryAllyInfo()
  {
    byParam = RTN_COUNTRY_ALLY_INFO_PARA;
    dwAllyCountryID = 0;
    dwFriendDegree = 0;
  }
  
  DWORD dwAllyCountryID;
  DWORD dwFriendDegree;
};

//////////////////////////////////////////////////////////////
/// 定义国家联盟命令结束
//////////////////////////////////////////////////////////////

/*
//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义小游戏命令开始
//////////////////////////////////////////////////////////////

struct stMiniGameUserCmd : public stNullUserCmd
{
  stMiniGameUserCmd()
  {
    byCmd = MINIGAME_USERCMD;
  }
};

// 邀请
#define INVITE_MINI_PARA 1
struct stInviteMiniGame : public stMiniGameUserCmd
{
  stInviteMiniGame()
  {
    byParam = INVITE_MINI_PARA;
  }
  DWORD tempid;//邀请者/被邀请者的临时ID
  DWORD money;//赌注
};

// 邀请回复
#define INVITE_RET_MINI_PARA 2
struct stInviteRetMiniGame : public stMiniGameUserCmd
{
  stInviteRetMiniGame()
  {
    byParam = INVITE_RET_MINI_PARA;
  }
  DWORD tempid;//邀请者的临时ID
  DWORD money;//赌注
  DWORD ret;//1:同意 0:不同意
};

// 开始游戏
#define START_MINI_PARA 3
struct stStartMiniGame : public stMiniGameUserCmd
{
  stStartMiniGame()
  {
    byParam = START_MINI_PARA;
  }
  DWORD tempid;//对方的临时ID
  DWORD money;//赌注
};

// 停止色子
#define STOP_DICE_MINI_PARA 4
struct stStopDiceMiniGame : public stMiniGameUserCmd
{
  stStopDiceMiniGame()
  {
    byParam = STOP_DICE_MINI_PARA;
  }
};

// 色子数字
#define DICE_NUM_MINI_PARA 5
struct stDiceNumMiniGame : public stMiniGameUserCmd
{
  stDiceNumMiniGame()
  {
    byParam = DICE_NUM_MINI_PARA;
  }
  DWORD tempid;//掷色子人的临时ID
  DWORD num;
};

// 结果
#define RESULT_MINI_PARA 6
struct stResultMiniGame : public stMiniGameUserCmd
{
  stResultMiniGame()
  {
    byParam = RESULT_MINI_PARA;
  }
  DWORD res;//0:输 1:赢 2:平
};

// 游戏结束 //主动离开游戏
#define END_MINI_PARA 7
struct stEndMiniGame : public stMiniGameUserCmd
{
  stEndMiniGame()
  {
    byParam = END_MINI_PARA;

    reason = 0;
  }
  DWORD reason;//结束原因 0:正常结束 1:对方离开
};

// 继续游戏
#define CONTINUE_MINI_PARA 8
struct stContinueMiniGame : public stMiniGameUserCmd
{
  stContinueMiniGame()
  {
    byParam = CONTINUE_MINI_PARA;
  }
  DWORD ret;//0:不继续 1:继续
};

// 通知客户端进入游戏
#define ENTER_MINI_PARA 9
struct stEnterMiniGame : public stMiniGameUserCmd
{
  stEnterMiniGame()
  {
    byParam = ENTER_MINI_PARA;
  }
};

//////////////////////////////////////////////////////////////
/// 定义小游戏命令结束
//////////////////////////////////////////////////////////////
*/

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义推荐人系统命令开始
//////////////////////////////////////////////////////////////

struct stRecommendUserCmd : public stNullUserCmd
{
  stRecommendUserCmd()
  {
    byCmd = RECOMMEND_USERCMD;
  }
};

// 填写自己的推荐人,<=15级的玩家才能填写
#define SET_RECOMMEND_PARA 1
struct stSetRecommendUserCmd : public stRecommendUserCmd
{
  stSetRecommendUserCmd()
  {
    byParam = SET_RECOMMEND_PARA;
    bzero(name,MAX_NAMESIZE);
  }

  char name[MAX_NAMESIZE + 1];
};

enum
{
  QUERY_BOUNTY,// 查询当前奖励金
  GET_BOUNTY,// 提取当前奖励金
};

// 推荐人查询或领取奖励
#define REQ_RECOMMEND_BOUNTY_PARA 2
struct stReqRecommendBountyUserCmd : public stRecommendUserCmd
{
  stReqRecommendBountyUserCmd()
  {
    byParam = REQ_RECOMMEND_BOUNTY_PARA;
  }

  BYTE byState;
};

// 被推荐人查询或领取奖励
#define REQ_RECOMMENDED_BOUNTY_PARA 3
struct stReqRecommendedBountyUserCmd : public stRecommendUserCmd
{
  stReqRecommendedBountyUserCmd()
  {
    byParam = REQ_RECOMMENDED_BOUNTY_PARA;
  }

  BYTE byState;
};

struct stRecommendItem
{
  char name[MAX_NAMESIZE + 1]; // 被推荐人姓名
  DWORD dwLevel;  // 最后一次提取时的等级
  DWORD dwTotal;  // 累计贡献多少金额
};

// 返回推荐人奖励
#define RTN_RECOMMEND_BOUNTY_PARA 4
struct stRtnRecommendBountyUserCmd : public stRecommendUserCmd
{
  stRtnRecommendBountyUserCmd()
  {
    byParam = RTN_RECOMMEND_BOUNTY_PARA;
    dwBalance = 0;
    dwTotal = 0;
    dwSize = 0;
  }

  DWORD dwBalance; // 可领取的金额
  DWORD dwTotal;  // 累计已领取的金额
  DWORD dwSize;  // 被推荐人数目,有可能有很多,如果超过窗口大小,能不能做成可以拉动
  stRecommendItem data[0];
};

// 返回被推荐人奖励
#define RTN_RECOMMENDED_BOUNTY_PARA 5
struct stRtnRecommendedBountyUserCmd : public stRecommendUserCmd
{
  stRtnRecommendedBountyUserCmd()
  {
    byParam = RTN_RECOMMENDED_BOUNTY_PARA;
    dwBalance = 0;
    dwTotal = 0;
    dwLastLevel = 0;
    bzero(name,sizeof(name));
  }
  
  DWORD dwBalance; // 可领取的余额
  DWORD dwTotal;   // 累计已领取的金额
  DWORD dwLastLevel; // 上次领取时的等级
  char name[MAX_NAMESIZE + 1]; // 推荐人姓名
};

//////////////////////////////////////////////////////////////
/// 定义推荐人系统命令结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
/// 定义财产保护系统指令开始
//////////////////////////////////////////////////////////////
struct stSafetyUserCmd : public stNullUserCmd
{
  stSafetyUserCmd()
  {
    byCmd = SAFETY_USERCMD;
  }
};

// 玩家设置保护状态
#define SET_SAFETY_PARA 1
struct stSetSafetyUserCmd : public stSafetyUserCmd
{
  stSetSafetyUserCmd()
  {
    byParam = SET_SAFETY_PARA;
    pwd = 0;
    state = 0;
  }

  DWORD pwd; // 数字密码
  BYTE  state; // 保护状态,0为关闭,1为开启,两个操作都需要输入数字密码
};

enum
{
  SAFETY_OPEN,// 保护状态,该状态下,不能进行拆装备操作
  SAFETY_TEMP_CLOSE,// 本次登录,暂时关闭状态,可以进行任何操作
};

// 玩家上线时,服务器通知客户端,玩家是否在保护状态
#define NOTIFY_SAFETY_PARA 2
struct stNotifySafetyUserCmd : public stSafetyUserCmd
{
  stNotifySafetyUserCmd()
  {
    byParam = NOTIFY_SAFETY_PARA;
    safe_setup = 0;
    byState = 0;
  }

  BYTE byState;
  BYTE safe_setup; 
};

// 玩家进入临时未保护状态,只在一次登录中有效,小退和关客户端后,无效
#define SET_TEMP_UNSAFETY_PARA 3
struct stSetTempUnSafetyUserCmd : public stSafetyUserCmd
{
  stSetTempUnSafetyUserCmd()
  {
    byParam = SET_TEMP_UNSAFETY_PARA;
    pwd = 0;
  }
  
  DWORD pwd;
};

enum
{
  SAFE_SPLIT_OBJECT,// 拆装备时,需要验证
  SAFE_THIRD_PACK,// 从第二,三个包裹中拿出物品,需要验证
  SAFE_GOLD_STOCK,// 金币购买股票
};
// 设置需要保护的功能
// 用,set_state,clear_state,来操作
#define SET_SAFETY_DETAIL_PARA 4
struct stSetSafetyDetailUserCmd : public stSafetyUserCmd
{
  stSetSafetyDetailUserCmd()
  {
    byParam = SET_SAFETY_DETAIL_PARA;
    safe_setup=0;
    pwd = 0;
  }
  
  DWORD pwd;
  BYTE safe_setup;
};

//////////////////////////////////////////////////////////////
/// 定义财产保护系统指令结束
//////////////////////////////////////////////////////////////

};

/**
 * \brief 定义游戏区
 * 对游戏进行分类，然后在同种游戏中再分区
 */

//struct GameZone_t
//{
//
//  operator int() const
//	  {
//		return id;
//	  }
//
//  union
//  {
//    /**
//     * \brief 唯一编号
//     */
//    DWORD id;
//    struct
//    {
//      /**
//       * \brief 游戏分区编号
//       */
//      WORD zone;
//      /**
//       * \brief 游戏种类编号
//       */
//      WORD game;
//    };
//  };
//
//  GameZone_t()
//  {
//    this->game = 0;
//    this->zone = 0;
//  }
//  GameZone_t(const GameZone_t &gameZone)
//  {
//    this->id = gameZone.id;
//  }
//  GameZone_t & operator= (const GameZone_t &gameZone)
//  {
//    this->id = gameZone.id;
//    return *this;
//  }
//  bool operator== (const GameZone_t &gameZone) const
//  {
//    return this->id == gameZone.id;
//  }
//};


namespace Cmd
{
  const BYTE CMD_NULL = 0;    /**< 空的指令 */
  const BYTE PARA_NULL = 0;  /**< 空的指令参数 */

  /**
   * \brief 空操作指令，测试信号和对时间指令
   *
   */
  struct t_NullCmd
  {
    BYTE cmd;          /**< 指令代码 */
    BYTE para;          /**< 指令代码子编号 */
    /**
     * \brief 构造函数
     *
     */
    t_NullCmd(const BYTE cmd = CMD_NULL,const BYTE para = PARA_NULL) : cmd(cmd),para(para) {};
  };
};

/**
 * \brief 定义服务器信息采集指令
 */


/**
 * \brief 定义统一用户平台登陆服务器指令
 */

struct BinaryHeader
{
	int32_t version;
	int32_t size;
	char data[0];
};

struct BinaryMember
{
	int32_t type;
	int32_t size;
	char data[0];
};

enum
{
	BINARY_ACCOUNT_NULL = 0,
	BINARY_ACCOUNT_SETTING,	// 设置属性
	BINARY_ACCOUNT_MAX,
};


enum
{
	BINARY_USER_NULL = 0,
	BINARY_USER_COUNTER = 1,
	BINARY_USER_RELATION = 2,
	BINARY_USER_MAX,
};

enum 
{
	BINARY_MESSAGE_NULL = 0,
	BINARY_MESSAGE_CONENT,
	BINARY_MESSAGE_MARK, //标记信息
	BINARY_MESSAGE_MAX,
};


// 实体类型 
enum EntityType
{
	ENTITY_TYPE_NPC = 1,
	ENTITY_TYPE_PLAYER = 2,
	ENTITY_TYPE_MASTER = 3,
	ENTITY_TYPE_TRANSFER = 4,
};

#define MAX_SPELL_CONTROL_NUM 4

/*-------------------------------------------------------------------
* @Brief : PK对象属性定义
*
* @Author:hzd 2015:11:12
*------------------------------------------------------------------*/
////////////////////////////////////战斗对象共用属性 start//////////////////////////////////////
struct EntryPkValBase
{
	int32_t nStatus;							// 状态(二进制位运算值) 
	int32_t nLevel;							// 等级 
	int32_t nRed;								// 红(血) 
	int32_t nRedMax;							// 红上限 
	int32_t nBlue;							// 蓝(法术) 
	int32_t nBlueMax;							// 蓝上限 
	int32_t nRedRecover;						// 红恢复 
	int32_t nBlueRecover;						// 蓝恢复 
	int32_t nPhysicAttack;					// 物理攻击 
	int32_t nPhysicDefend;					// 物理防御 
	int32_t nSpellAttack;						// 法术攻击 
	int32_t nSpellDefend;						// 法术防御 
	int32_t nBaojilv;							// 暴击率 
	int32_t nBaoji;							// 暴击 
	int32_t nGedanglv;						// 隔挡率 
	int32_t nGedang;							// 隔挡 
	int32_t nShanbilv;						// 闪避率 
	int32_t nMingzhonglv;						// 命中率 
	int32_t nAttackSpeed;						// 速度 
	int32_t nMoveSpeed;						// 移速 

	EntryPkValBase()
	{
		memset(this, 0, sizeof(*this));
	}

	EntryPkValBase(const EntryPkValBase& pkVal)
	{
		operator=(pkVal);
	}

	EntryPkValBase& operator=(const EntryPkValBase& pkVal)
	{
		memcpy(this, &pkVal, sizeof(*this));
		return *this;
	}

};




// 生物体类型 
/*-------------------------------------------------------------------
* @Brief : 本类属性，是指在地图上使用的，共用的，也就是地图上的PK相关
*			的数据，而功能属性不注册在这里
* @Author:hzd 2015:11:28
*------------------------------------------------------------------*/
enum EntiryBaseAttrType
{
	////////////////////////////////////Entry共用属性//////////////////////////////////////
	ENTITY_ATTRIBUTE_MAPID,
	ENTITY_ATTRIBUTE_POS_X,
	ENTITY_ATTRIBUTE_POS_Y,
	ENTITY_ATTRIBUTE_INVIEWRANGE,
	ENTITY_ATTRIBUTE_OUTVIEWRANGE,
	ENTITY_ATTRIBUTE_MAX,
};

struct BaseAttribute
{
	int32_t nMapID;					// 地图ID 
	zPos sPos;						// 坐标 
	int32_t nInViewRange;				// 进入视野距离 
	int32_t nOutViewRangle;			// 离开视野距离 
	BaseAttribute()
	{
		sPos.x = sPos.y = 0;
		nInViewRange = nOutViewRangle = 0;
	}
};

//////////////////////////////////////////////////////////////////////////

struct SpellData
{
	uint32_t nSpellID;	// 技能ID 
	int32_t nPosition;    // 携带位置 (-1未携带,0 - 4 携带在对应的位置上) 
};

enum CharacterType
{
	CHARACTER_TYPE_NULL = 0,    // 非法 
	CHARACTER_TYPE_SHAOLIN = 1,	// 少林 
	CHARACTER_TYPE_MOJIAO = 2,	// 魔教 
	CHARACTER_TYPE_GUMU = 3,	// 古墓 
	CHARACTER_TYPE_XIAOYAO = 4,	// 逍遥 
};

//////////////////////////////////////////////////////////////////////////

/*------------------------------------------------------------------
*
* @Brief : 频道消息类型
*
* @Author: hzd
* @File  : def_channel.h
* @Date  : 2015/09/18 23:54
* @Copyright (c) 2015,hzd, All rights reserved.
*-----------------------------------------------------------------*/
enum EChannelRegistType
{
	E_CH_REG_TYPE_NULL = 0x0000000,	// 无 
	E_CH_REG_TYPE_POS_B = 0x00000001,	// 位置信息广播 
	E_CH_REG_TYPE_POS_R = 0x00000002,	// 位置信息收集 
	E_CH_REG_TYPE_NPC_B = 0x00000004,	// 生物体信息广播 
	E_CH_REG_TYPE_NPC_R = 0x00000008,	// 生物体信息收集 
	E_CH_REG_TYPE_EQUIP_B = 0x00000010,   // 装备广播 
	E_CH_REG_TYPE_EQUIP_R = 0x00000020,   // 装备收集 
	E_CH_REG_TYPE_SPELL_B = 0x00000040,	// 技能广播 
	E_CH_REG_TYPE_SPELL_R = 0x00000080,   // 技能收集 
	E_CH_REG_TYPE_BUFF_B = 0x00000100,	// Buff信息广播	 
	E_CH_REG_TYPE_BUFF_R = 0x00000200,	// Buff信息收集 
	E_CH_REG_TYPE_MAX
};

enum
{
	MAX_CHANNEL_BUFF = 15,	// 最大Buff数量	 
	MAX_CHARACTER_NAME_LENGTH_C = 32,
};

enum
{
	MAX_POSITION_COUNT = 100, // 最多可存放周边玩家位置数据 
	MAX_CREATURE_COUNT = 100, // 最多可存放周边玩家生物数据 
};


// 位置信息
struct ChannelPosition
{
	uint64_t			nID;			// 实体ID 
	int32_t			nPositionX;		// 位置x 
	int32_t			nPositionZ;		// 位置z 
	int32_t			nHeadingX;		// 朝向X已经扩大了100 
	int32_t			nHeadingZ;		// 朝向X已经扩大了100 
};

// 生物体信息 
struct ChannelCreature
{
	uint64_t		nID;									// 实体ID 
	int8_t		arrName[MAX_CHARACTER_NAME_LENGTH_C];	// 昵称 
	int32_t		nRed;									// 红(血) 
	int32_t		nRedMax;								// 红上限 
	int32_t		nBlue;									// 蓝(法术) 
	int32_t		nBlueMax;								// 蓝上限 
};

// 装备信息 
struct ChannelWear
{
	uint64_t		nID;				// 实体ID 
	uint32_t		nClothesID;			// 衣服ID 
	uint32_t		nWeaponID;			// 武器装备ID 
};

// 技能信息 
struct ChannelSpell
{
	uint64_t		nID;			// 实体ID 
	uint32_t      nSpellID;		// 技能ID 
};

// Buff信息 
struct ChannelBuff
{
	uint32_t		nNum;							// Buff数量 
	uint64_t		nID;							// 实体ID 
	uint32_t		arrBuffID[MAX_CHANNEL_BUFF];    // BuffID  
};


#define FUNCTION_CHANNEL_BROADCAST(InfoType)\
virtual void ChannelBroadcast(const std::set<const InfoType*>& rsetValues) {}
#define DEFINE_FUNCTION_CHANNEL_BROADCAST(InfoType)\
virtual void ChannelBroadcast(const std::set<const InfoType*>& rsetValues);
#define IMPLEMENT_FUNCTION_CHANNEL_BROADCAST(ClassName, InfoType)\
void ClassName::ChannelBroadcast(const std::set<const InfoType*>& rsetValues)

#define FUNCTION_CHANNEL_COLLECT(InfoType)\
typedef const InfoType* P##InfoType;\
virtual void ChannelCollect(P##InfoType& o_rpInfo) { \
o_rpInfo = &m_s##InfoType; }
#define DEFINE_FUNCTION_CHANNEL_COLLECT(InfoType)\
virtual void ChannelCollect(P##InfoType& o_rpInfo);
#define IMPLEMENT_FUNCTION_CHANNEL_COLLECT(ClassName, InfoType)\
void ClassName::ChannelCollect(P##InfoType& o_rpInfo)

#pragma pack()

#endif //_INC_CSCOMMON_H_
