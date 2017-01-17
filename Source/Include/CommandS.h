#ifndef __COMMON_D2L_H_
#define __COMMON_D2L_H_


#include "ServerDefine.h"
#include "NetConfig.h"
#include "CommonInternal.h"

#pragma pack(push,1)

enum EProD2L
{

	PRO_D2L_ACCOUNT_LOGIN			= PRO_D2L_BASE + 0, // 返回帐号登录结果 
	PRO_D2L_CHARACTER_LIST			= PRO_D2L_BASE + 1, // 返回角色列表信息 
	PRO_D2L_ROLE_CREATE_RESULT		= PRO_D2L_BASE + 2,	// 角色创建结果 
	PRO_D2L_NAMES_LIST				= PRO_D2L_BASE + 3, 


};


/*------------------------------------------------------------------
 *
 * @Brief : 校验帐户密码返回结果
 *
 * @Author: hzd 
 * @File  : CommonD2L.h
 * @Date  : 2015/10/18 20:52
 * @Copyright (c) 2015,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
struct D2LAccountLogin : public NetMsgSS
{

	enum 
	{
		E_RESULT_SUCCESS = 0,
		E_RESULT_FAIL,
	};

	int32 result;
	int64 accountID;

	D2LAccountLogin():NetMsgSS(PRO_D2L_ACCOUNT_LOGIN)
	{
		result = 0;
		accountID = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/*-------------------------------------------------------------------
 * @Brief : 角色列表信息，当帐号密码正确时，会自动返回该信息到LS
 * 
 * @Author:hzd 2015:10:24
 *------------------------------------------------------------------*/
struct D2LCharacterList : public NetMsgSS
{
	int32 nCount;
	struct StCharacterInfo
	{
		int64 nCharID;
		int32 nServerID;
		int64 nAccountID;
		char arrName[MAX_NAME_LENGTH];
		int32 nType;
		int32 nLevel;
		int32 nLastLogin;
		StCharacterInfo()
		{
			nCharID = nAccountID = nServerID = nType = nLevel = nLastLogin = 0;
			memset(arrName,0,sizeof(arrName));
		}
	};

	StCharacterInfo arrInfo[MAX_ROLE_TYPE_COUNT];

	D2LCharacterList():NetMsgSS(PRO_D2L_CHARACTER_LIST)
	{
		nCount = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct D2LRoleCreateResult : public NetMsgSS
{

	enum
	{
		E_SUCCESS = 0,
		E_FAIL_SYNC,
		E_FAIL_ROLE_MAX,
		E_FAIL_NAME_EXIST,
		E_FAIL_INSERT_FAIL,
	};

	int32 nResult;
	int64 nNewCharID;

	D2LRoleCreateResult():NetMsgSS(PRO_D2L_ROLE_CREATE_RESULT)
	{
		nResult = 0;
		nNewCharID = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct D2LNamesList : public NetMsgSS
{
	int32 nCount;
	struct StNameInfo
	{
		char arrName[32];
	};

	StNameInfo arrNameList[1000];

	D2LNamesList():NetMsgSS(PRO_D2L_NAMES_LIST)
	{
		nCount = 0;
		memset(arrNameList,0,sizeof(arrNameList));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////////////////////////////////////////////////


//-------------------dp2ws--------------------- 600-699

enum EProDP2WS
{

};

/////////////////////////////////////l2d/////////////////////////////////////

enum EProL2D
{
	PRO_L2D_ACCOUNT_LOGIN		= PRO_L2D_BASE + 1,	// 查询用户名与密码是否正确 
	PRO_L2D_ROLE_CREATE			= PRO_L2D_BASE + 2, // 创建角色
};

struct L2DAccountLogin : public NetMsgSS
{
	L2DAccountLogin():NetMsgSS(PRO_L2D_ACCOUNT_LOGIN)
	{

	}
	char name[32];
	char password[32];

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct L2DRoleCreate : public NetMsgSS
{
	int32 nType;
	int64 nAccountID;
	char arrName[MAX_NAME_LENGTH];
	L2DRoleCreate():NetMsgSS(PRO_L2D_ROLE_CREATE)
	{
		nType = 0;
		nAccountID = 0;
		memset(arrName,0,sizeof(arrName));
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/////////////////////////////////s2dp/////////////////////////////////////////

enum EProS2D
{

	PRO_S2D_LOAD_USER			= PRO_S2D_BASE + 0,	// 加载角色数据 
	PRO_S2D_CLIENT_EXIT_SCENE	= PRO_S2D_BASE + 1,	// 玩家从场景退出
	PRO_S2D_SAVE_USER			= PRO_S2D_BASE + 2, // 保存数据 

	PRO_S2D_SAVE_MIXITEMNUMBER	= PRO_S2D_BASE + 3, // 
	PRO_S2D_SAVE_MXIITEMBINARY	= PRO_S2D_BASE + 4,

};


struct S2DLoadUser : public NetMsgSS
{
	int64 uid;
	int64 sceneid;
	int32 enterType; /* 0首次进入,1更改场景,2离线加载 */
	S2DLoadUser():NetMsgSS(PRO_S2D_LOAD_USER)
	{
		uid = sceneid = enterType = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct S2DClientExitScene : public NetMsgSS
{

	S2DClientExitScene():NetMsgSS(PRO_S2D_CLIENT_EXIT_SCENE)
	{

	}

	int32 nReason;

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}

};

struct S2DSaveUser : public NetMsgSS
{
	S2DSaveUser():NetMsgSS(PRO_S2D_SAVE_USER)
	{
		uid = size = 0;
	}
	int64 uid;
	UserSceneBase base;
	int32 size;
	char data[0];
};

struct S2DSaveMixItemNumber : public NetMsgSS
{
	int32 nType;
	int64 nValue;
	S2DSaveMixItemNumber():NetMsgSS(PRO_S2D_SAVE_MIXITEMNUMBER)
	{
		nType = 0;
		nValue = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

////////////////////////////////d2s//////////////////////////////////////////

enum EProD2S
{
	PRO_D2S_LOAD_USER	= PRO_D2S_BASE + 0, /* 加载角色数据 */ 
	PRO_D2S_SAVE_CALLBACK	= PRO_D2S_BASE + 1, /* 保存成功回调 */ 
};




struct D2SLoadUser : public NetMsgSS
{
	D2SLoadUser():NetMsgSS(PRO_D2S_LOAD_USER)
	{
		size = 0;
	}
	int64 uid;
	UserSceneBase base;
	int32 size;
	char data[0];
};

struct D2SSaveCallBack : public NetMsgSS
{

	int64 nCharID;
	int32 nReceiptID;

	D2SSaveCallBack() :NetMsgSS(PRO_D2S_SAVE_CALLBACK)
	{
		nCharID = nReceiptID = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}

};



////////////////////////////////s2fep//////////////////////////////////////////

enum EProS2F
{
	PRO_S2F_SYNC_USER_SCENE = PRO_S2F_BASE + 0,
	PRO_S2F_SYNC_USER_DATA = PRO_S2F_BASE + 1,	/* 加载角色数据到网关 */ 
	PRO_S2F_BORADCAST_MSG = PRO_S2F_BASE + 2,	/* 广播消息到用户（网关处理） */
};

struct S2FSyncUserScene : public NetMsgSS
{
	S2FSyncUserScene():NetMsgSS(PRO_S2F_SYNC_USER_SCENE)
	{
		uid = 0;
	}

	int64 uid; 

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct S2FSyncUserData : public NetMsgSS
{
	int64 uid;
	char name[MAX_NAME_LENGTH + 1];
	UserGateBase base;
	
	S2FSyncUserData() :NetMsgSS(PRO_S2F_SYNC_USER_DATA)
	{
		uid = 0;
		memset(name, 0, sizeof(name));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/* 广播消息类型 */
enum 
{
	BORADCAST_TYPE_ALL = 0,
	BORADCAST_TYPE_COUNTRY,
	BORADCAST_TYPE_MAPID,
	BORADCAST_TYPE_SCENE,
	BORADCAST_TYPE_ZONE,
	BORADCAST_TYPE_NINE,
	BORADCAST_TYPE_TEAM
};

/*
 * 广播消息 
 * 
 */
struct S2FBoradCastMsg : public NetMsgSS
{
	S2FBoradCastMsg() : NetMsgSS(PRO_S2F_BORADCAST_MSG)
	{
		msgtype = regid = regid = x = y = size = 0;
	}

	int32 msgtype;	/* 0全体,1国家,2地图,3场景,4区域,5九屏,6队伍 */
	int32 regid;	/* 范围参考值,复用：国家ID,地图ID,场景ID,区域ID,队伍ID */
	int64 userid;	/* 用户ID参考值 */
	int32 x;		/* 坐标x */
	int32 y;		/* 坐标y */

	int32 size;
	char data[0];
};

enum EProF2S
{
	PRO_F2S_PLAYER_EXIT = PRO_F2S_BASE + 0, // 客户端退出 
};

struct F2SRqPlayerExit : public NetMsgSS
{
	enum
	{
		E_REASON_UNKOWN = 0,			// 未知 
		E_REASON_SERVER_TICKED,			// 服务器踢出
		E_REASON_CLIENT_EXIT,			// 主动退出 
		E_REASON_TIMEOUT,				// 超时断开 
		E_REASON_PACKAGE_ERROR,			// 非法协议 
		E_REASON_SEND_ERROR,			// 向Client发送时出错 
		E_REASON_SWITCH_SCENE,			// 切换场景（这个仅对Scene，dp）
		E_REASON_REPEAT_CHARACTER = 99,	// 重复登录
	};

	int64 uid;
	int32 nReason;

	enum
	{
		E_STATE_IN_UNKOWN = 0,	// 未知 
		E_STATE_IN_LOGIN,		// 在登录时退出 
		E_STATE_IN_SELECT,		// 在选择角色时退出 
		E_STATE_IN_WORLD,		// 在WORLD中 
		E_STATE_IN_SCENE,		// 在场景中退出 
	};

	int32 nPostion;				// 玩家所在位置 

	F2SRqPlayerExit() : NetMsgSS(PRO_F2S_PLAYER_EXIT)
	{
		nReason = 0;
		nPostion = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)














#endif

#ifndef __COMMON_S2W_H_
#define __COMMON_S2W_H_


#include "ServerDefine.h"
#include "NetConfig.h"
#include "CommanC.h"


#pragma pack(push,1)

enum
{
	PRO_S2W_SCENE_BASE = PRO_S2W_BASE + 0,
	PRO_S2W_CHAT_BASE = PRO_S2W_BASE + 400,
	PRO_S2W_REL_BASE = PRO_S2W_BASE + 500,
	PRO_L2W_LOGIN_BASE = PRO_L2W_BASE + 100,
	PRO_F2W_LOGIN_BASE = PRO_F2W_BASE + 200,
};


enum EProS2W
{
	/* 场景相关协议 */
	PRO_S2W_REGISTER_SCENE = PRO_S2W_SCENE_BASE + 0, // 注册场景 
	PRO_S2W_CANCEL_SCENE = PRO_S2W_SCENE_BASE + 1, // 注销场景 
	PRO_S2W_ENTER_SCENE_RESULT = PRO_S2W_SCENE_BASE + 2,	// 进入场景结果
	PRO_S2W_CHANGE_SCENE = PRO_S2W_SCENE_BASE + 3, // 请求切换场景 


												   // scene
												   /* 聊天协议 */
												   PRO_S2W_CHATTOONE = PRO_S2W_CHAT_BASE + 0,
												   //PRO_S2W_REL_SCENE_RM = PRO_S2W_REL_BASE + 1,

};

struct S2WRegisterScene : public NetMsgSS
{

	S2WRegisterScene() :NetMsgSS(PRO_S2W_REGISTER_SCENE)
	{

	}

	QWORD sceneid;
	QWORD sceneTempID;
	char name[MAX_NAMESIZE + 1];
	char fileName[MAX_NAMESIZE + 1];
	DWORD dwCountryID;
	BYTE byLevel;
	DWORD mapid;

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct S2WReqCancelScene : public NetMsgSS
{
	S2WReqCancelScene() :NetMsgSS(PRO_S2W_CANCEL_SCENE)
	{

	}
	int32 nSceneNum;
	int32 arrSceneID[MAX_MAP_NUM];
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


struct S2WEnterSceneResult : public NetMsgSS
{

	int32 nSceneID;
	int32 nEnterType;
	// 是否为跨服，1是，则需要通知原场景，0否，则需要进入主场景 
	int32 nCross;
	enum
	{
		E_ENTER_SUCCESS = 0,
		E_ENTER_FAIL,
	};

	int32 nResult;

	S2WEnterSceneResult() :NetMsgSS(PRO_S2W_ENTER_SCENE_RESULT)
	{
		nSceneID = nEnterType = nCross = nResult = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/*

切换场景，由ss向ws请求
参考td

*/
struct S2WChangeScene : public NetMsgSS
{
	int64 uid;
	int32 sceneID;
	stEnterSceneParam stParam;
	S2WChangeScene() :NetMsgSS(PRO_S2W_CHANGE_SCENE)
	{
		uid = sceneID = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/* ChatMsg */
/* 单聊转发消息 */
struct S2WChatToOne : public NetMsgSS
{
	S2WChatToOne() :NetMsgSS(PRO_S2W_CHATTOONE)
	{
	}
	int64 fromUID;
	int64 toUID;
	t_ChatBase msg;
};

const int32 PRO_S2W_REL_SCENE_ADD = PRO_S2W_REL_BASE + 0;
struct S2WRelalionAdd : public NetMsgSS
{
	S2WRelalionAdd() :NetMsgSS(PRO_S2W_REL_SCENE_ADD)
	{

	}
};


//////////////////////////////////////////////////////////////////////////

enum EProD2W
{

	PRO_D2W_GLOBAL_INFO = PRO_D2W_BASE + 0,	/* 全局信息 */
	PRO_D2W_SELECT_ROLE_RESULT = PRO_D2W_BASE + 1,	/* 选择角色结果 */
	PRO_D2W_LOAD_SORTLIST = PRO_D2W_BASE + 2, /* 加载数据 */

};

struct D2WGlobalInfo : public NetMsgSS
{

	// 第几次启动 
	int32 nStartTimes;
	// 

	D2WGlobalInfo() :NetMsgSS(PRO_D2W_GLOBAL_INFO)
	{

	}
	inline int32 GetLength()
	{
		return sizeof(*this);
	}
};

/*-------------------------------------------------------------------
* @Brief : 保存在WS上的数据，WS上保存的数据比较少，也减少S2W数据同步
*
* @Author:hzd 2015:11:6
*------------------------------------------------------------------*/
struct StUserDataForWs
{
	int64 uid;
	int32 nServerID;
	int64 nAccountID;
	char name[MAX_NAMESIZE + 1];
	int32 nType;
	int32 nLevel;
	int32 nLandMapid;
	int32 nLandX;
	int32 nLandY;
	int32 nInstanceMapId;
	int32 nInstanceX;
	int32 nInstanceY;
	StUserDataForWs()
	{
		memset(this, 0, sizeof(*this));
	}

	StUserDataForWs(const StUserDataForWs* _userData)
	{
		memcpy(this, _userData, sizeof(StUserDataForWs));
	}

	inline int32 GetLength()
	{
		return sizeof(*this);
	}
};

/*-------------------------------------------------------------------
* @Brief : 选择角色信息，本信息如果成功会有数据通知到Client，失败
*			则会停在WS，由WS处理，等Client再次发起选择角色
* @Author:hzd 2015:11:6
*------------------------------------------------------------------*/
struct D2WSelectRoleResult : public NetMsgSS
{
	enum {

		E_SELECT_SUCCESS = 0,
		E_SELECT_LOADING,	// 加载中 
		E_SELECT_NOT_FOUND, // 找不到
	};
	int32 nResult;
	int64 fepSessionID;
	StUserDataForWs data;
	D2WSelectRoleResult() :NetMsgSS(PRO_D2W_SELECT_ROLE_RESULT)
	{
		nResult = fepSessionID = 0;
	}
	inline int32 GetLength()
	{
		return sizeof(*this);
	}
};

struct D2WLoadSortLists : public NetMsgSS
{
	int32 nByteSize; /* 该长度为proto真实长度 */
	char arrByte[4096];
	D2WLoadSortLists() :NetMsgSS(PRO_D2W_LOAD_SORTLIST)
	{
		nByteSize = 0;
		memset(arrByte, 0, sizeof(arrByte));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

enum EProL2W
{
	PRO_L2W_LOADLIST = PRO_L2W_LOGIN_BASE + 0, // 加载角色列表 
};

// login
struct L2WLoadList : public NetMsgSS
{
	L2WLoadList() :NetMsgSS(PRO_L2W_LOADLIST)
	{
		accid = 0;
	}

	int64 accid;

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

enum EProF2W
{
	PRO_F2W_PLAYER_EXIT = PRO_F2W_LOGIN_BASE + 0, // 客户端退出 
};

struct F2WRqPlayerExit : public NetMsgSS
{
	enum
	{
		E_REASON_UNKOWN = 0,			// 未知 
		E_REASON_SERVER_TICKED,			// 服务器踢出
		E_REASON_CLIENT_EXIT,			// 主动退出 
		E_REASON_TIMEOUT,				// 超时断开 
		E_REASON_PACKAGE_ERROR,			// 非法协议 
		E_REASON_SEND_ERROR,			// 向Client发送时出错 
		E_REASON_SWITCH_SCENE,			// 切换场景（这个仅对Scene，dp）
		E_REASON_REPEAT_CHARACTER = 99,	// 重复登录
	};

	int64 uid;
	int32 nReason;

	enum
	{
		E_STATE_IN_UNKOWN = 0,	// 未知 
		E_STATE_IN_LOGIN,		// 在登录时退出 
		E_STATE_IN_SELECT,		// 在选择角色时退出 
		E_STATE_IN_WORLD,		// 在WORLD中 
		E_STATE_IN_SCENE,		// 在场景中退出 
	};

	int32 nPostion;				// 玩家所在位置 

	F2WRqPlayerExit() : NetMsgSS(PRO_F2W_PLAYER_EXIT)
	{
		nReason = 0;
		nPostion = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)




#endif

#ifndef __COMMON_W2D_H_
#define __COMMON_W2D_H_


#include "ServerDefine.h"
#include "NetConfig.h"


//-----------------------600~699-----------------

enum EProWS2DP
{
	PRO_W2D_LOGINED = PRO_W2D_BASE + 0, // 登录结果 
	PRO_W2D_SERVER_INFO = PRO_W2D_BASE + 1,
	PRO_W2D_SCENE_INFO = PRO_W2D_BASE + 2,
	PRO_W2D_EVENT_INFO = PRO_W2D_BASE + 3, // 查询event_info是否有后台事件要执行   
	PRO_W2D_SELECT_ROLE = PRO_W2D_BASE + 4, // 选择角色 

	PRO_W2D_LOAD_SORTLISTS = PRO_W2D_BASE + 100, /* 加载排行榜数据 */
	PRO_W2D_SAVE_SORTLIST = PRO_W2D_BASE + 101, /* 保存排行榜数据 */
};

#pragma pack(push,1)

struct WS2DPLogined : public NetMsgSS
{

	WS2DPLogined() :NetMsgSS(PRO_W2D_LOGINED)
	{

	}
	enum
	{
		SUCCESS,
		FAIL,
	};
	int32 nResult; // 0 成功,其他失败 
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct NotifyServerInfo
{
	NotifyServerInfo()
	{
		int32 nServerLoad = 0;
		int32 nClientLoad = 0;
	}
	char arrHost[32];
	int32 nPort;
	int32 nServerType;
	int32 nServerID;
	int32 nServerLoad; // 该服务器下负载人数 
	int32 nClientLoad; // 客户端选择的人数 
};

struct W2DNotifyServerInfo : public NetMsgSS
{
	W2DNotifyServerInfo() :NetMsgSS(PRO_W2D_SERVER_INFO)
	{
		nGroupID = 0;
	}
	int32 nGroupID;
	int32 nServerNum;
	NotifyServerInfo arrServerInfo[MAX_SERVER_NUM];

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct NotifySceneInfo
{
	int32 nServerID;
	int32 nSceneID;
	int32 nLoadNum; // 当前负载量 
};

struct W2DNotifySceneInfo : public NetMsgSS
{
	W2DNotifySceneInfo() :NetMsgSS(PRO_W2D_SCENE_INFO)
	{

	}
	int32 nSceneNum;
	NotifySceneInfo arrSceneInfo[MAX_MAP_NUM];
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct W2DReqEventInfo : public NetMsgSS
{
	W2DReqEventInfo() :NetMsgSS(PRO_W2D_EVENT_INFO)
	{

	}
	int32 nTimestamp; // 时间戳  
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct W2DSelectRole : public NetMsgSS
{
	int64 uid;
	int64 fepSessionID;
	W2DSelectRole() :NetMsgSS(PRO_W2D_SELECT_ROLE)
	{
		uid = fepSessionID = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct W2DLoadSortLists : public NetMsgSS
{
	W2DLoadSortLists() :NetMsgSS(PRO_W2D_LOAD_SORTLISTS)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct W2DSaveSortLists : public NetMsgSS
{
	int32 nByteSize;
	char arrByte[4096];
	W2DSaveSortLists() :NetMsgSS(PRO_W2D_SAVE_SORTLIST)
	{
		nByteSize = 0;
		memset(arrByte, 0, sizeof(arrByte));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////////////////////////////////////////////////


enum EProW2Fep
{
	PRO_W2FEP_LOGINED = 200, // 登录结果 

};

// fep登录结果 
struct W2FepLogined : public NetMsgSS
{
	W2FepLogined() :NetMsgSS(PRO_W2FEP_LOGINED)
	{

	}
	enum
	{
		SUCCESS,
		FAIL,
	};
	int32 nResult; // 0 成功,其他失败 
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// 创建频道
const BYTE PRO_W2F_CREATE_CHANNEL = PRO_W2F_BASE + 1;
struct W2FChannelCreate : public NetMsgSS
{
	W2FChannelCreate() : NetMsgSS(PRO_W2F_CREATE_CHANNEL)
	{

	}
	char name[MAX_NAMESIZE + 1];
	int8 count;
	int64 uids[0];
};

// 更新频道
const BYTE PRO_W2F_UPDATE_CHANNLE = PRO_W2F_BASE + 2;
struct W2FChannelUpdate : public NetMsgSS
{
	W2FChannelUpdate() :NetMsgSS(PRO_W2F_UPDATE_CHANNLE)
	{

	}
	char name[MAX_NAMESIZE + 1];
	int8 opt;//0全部更新，1新增，2删除
	int8 count;
	int64 uids[0];
};

// 删除频道
const BYTE PRO_W2F_DELETE_CHANNEL = PRO_W2S_BASE + 3;
struct W2FChannelDelete : public NetMsgSS
{
	W2FChannelDelete() :NetMsgSS(PRO_W2F_DELETE_CHANNEL)
	{

	}
	char name[MAX_NAMESIZE + 1];
};

//////////////////////////////////////////////////////////////////////////

enum EProW2Ls
{

	PRO_W2LS_LOGINED = 300, // 登录结果 
	PRO_W2LS_SERVERINFO_LIST = 301,

};



//////////////////////////////////////////////////////////////////////////

enum MyEnum
{
	PRO_W2S_SCENE = PRO_W2S_BASE + 0,	/* 场景协议 */
	PRO_W2S_LOAD = PRO_W2S_BASE + 100, /* 加载协议 */
};

enum EProW2Ss
{
	PRO_W2S_ReqTransfer = PRO_W2S_SCENE + 0,	/* 请求进入场景 */
	PRO_W2S_RepEnterResult = PRO_W2S_SCENE + 1, /* 请求场景结果 */

	PRO_W2S_LOAD_UIDS = PRO_W2S_LOAD + 0, /* 加载离线玩家数据到临时场景中 */

};

struct W2SRqEnterScene : public NetMsgSS
{
	int64 uid;
	int64 sceneid;
	int16 mapid;
	int32 enterscenetime;
	W2SRqEnterScene() :NetMsgSS(PRO_W2S_ReqTransfer)
	{
		uid = mapid = sceneid = enterscenetime = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct W2SNtEnterResult : public NetMsgSS
{
	int64 nCharID;
	enum
	{
		E_ENTER_SUCCESS = 0,
		E_ENTER_FAIL,
	};

	int32 nResult;

	W2SNtEnterResult() :NetMsgSS(PRO_W2S_RepEnterResult)
	{
		nCharID = nResult = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}

};


struct W2SLoadUids : public NetMsgSS
{
	int32 count;
	int64 uids[MAX_LOAD_ALL_UID];
	W2SLoadUids() :NetMsgSS(PRO_W2S_LOAD_UIDS)
	{
		count = 0;
		memset(uids, 0, sizeof(uids));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(uids) + count * sizeof(uids[0]);
	}
};

#pragma pack(pop)


#endif



