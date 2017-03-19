#ifndef __COMMON_S2S_H_
#define __COMMON_S2S_H_

#include "BaseDefine.h"
#include "DbConfig.h"
#include "NetConfig.h"
#include "csCommon.h"

namespace S
{



	/*

	服务器与客户端或客户端与服务器直接通信的协议

	*/

#pragma pack(push,1)


	enum
	{
		PRO_S2S_LOGIN = PRO_S2S + 100,
		PRO_S2S_SCENE = PRO_S2S + 200,	/* 场景协议 */
		PRO_S2S_LOAD = PRO_S2S + 300,	/* 加载协议 */
		PRO_S2S_CHAT = PRO_S2S + 400,
		PRO_S2W_RELATION = PRO_S2S + 500,
	};

	//------------------------req------------------------------
	// 登录处理，包括,所有服务器登录到ws 
	const int32 SS_RQ_LOGIN = PRO_S2S_LOGIN + 0;
	struct SSRqLogin : public NetMsgSS
	{
		SSRqLogin() :NetMsgSS(SS_RQ_LOGIN)
		{
			serverID = serverID = 0;
		}
		int32 serverID;
		int32 serivceID;

	};

	// 分配服务器信息  
	const int32 SS_RQ_CHECK_SERIVCES = PRO_S2S_LOGIN + 2;
	struct SSRqCheckSerivces : public NetMsgSS
	{
		SSRqCheckSerivces() :NetMsgSS(SS_RQ_CHECK_SERIVCES)
		{

		}
	};

	// PING协议客户端ping服务端，ping后，就socket->setTimeout,收到数据，则取消 
	const int32 SS_RQ_PING_S = PRO_S2S_LOGIN + 3;
	struct SSRqPingToS : public NetMsgSS
	{
		SSRqPingToS() :NetMsgSS(SS_RQ_PING_S)
		{

		}
	};


	//--------------------------rep------------------------------------

	// 登录结果  
	const int32 SS_RT_LOGINED = PRO_S2S_LOGIN + 4;
	struct SSRtLogined : public NetMsgSS
	{
		SSRtLogined() :NetMsgSS(SS_RT_LOGINED)
		{
		}
		enum
		{
			SUCCESS,
			FAIL,
		};
		int32 result;
	};

	// 服务器列表信息 
	const int32 SS_RT_SERVERINFO_LIST = PRO_S2S_LOGIN + 5;
	struct SSServerRegList : public NetMsgSS
	{
		SSServerRegList() :NetMsgSS(SS_RT_SERVERINFO_LIST)
		{
			count = 0;
		}
		int8 count;
		t_ServerReg reglist[0];
		int32 getSize()
		{
			return sizeof(*this) + count * sizeof(t_ServerReg);
		}
	};

	// 更新服务器信息 
	const int32 SS_NT_SERVERID = PRO_S2S_LOGIN + 6;
	struct SSNtInitUserClient : public NetMsgSS
	{
		SSNtInitUserClient() :NetMsgSS(SS_NT_SERVERID)
		{
			nSceneID = 0;
		}
		int32 nSceneID;
	};

	// 服务器返回PING的结果，将socket取消定时器 
	const int32 SS_RT_PING_S = PRO_S2S_LOGIN + 7;
	struct SSRtPingS : public NetMsgSS
	{
		SSRtPingS() :NetMsgSS(SS_RT_PING_S)
		{
		}
	};

	static dbCol user_columns[] =
	{
		{ "ID", DB_QWORD, sizeof(int64) },
		{ "ACCID", DB_QWORD, sizeof(int64) },
		{ "NAME",DB_STR,MAX_NAMESIZE + 1 },
		{ "STATUS",DB_BYTE, sizeof(int8) },
		{ "LEVEL",DB_WORD, sizeof(int16) },
		{ "VIP",DB_BYTE, sizeof(int8) },
		{ "SCENEID",DB_DWORD, sizeof(int64) },
		{ "MAPID",DB_DWORD, sizeof(int32) },
		{ "ROLETYPE",DB_DWORD, sizeof(int8) },
		{ "EXP",DB_DWORD, sizeof(int32) },
		{ "POSX",DB_DWORD, sizeof(int32) },
		{ "POSY",DB_DWORD, sizeof(int32) },
		{ "GOLD",DB_DWORD, sizeof(int32) },
		{ "SILVER",DB_DWORD, sizeof(int32) },
		{ "COPPER",DB_DWORD, sizeof(int32) },
		{ "LASTLOGIN",DB_DWORD, sizeof(int32) },
		{ "COUNTRY",DB_DWORD, sizeof(int8) },
		{ "TEAMID",DB_DWORD, sizeof(int32) },
		{ "INFO",DB_BIN2, 0 },
		{ NULL,0,0 }
	};

	struct t_UserSceneBase
	{
		t_UserSceneBase()
		{
			id = accid = status = level = sceneid = mapid = vip = roletype = exp = 0;
			posx = posy = gold = silver = copper = lastLogin = country = teamid = 0;
		}

		int64 id;
		int64 accid;
		char name[MAX_NAMESIZE + 1];
		int8 status;
		int16 level;
		int8 vip;
		int64 sceneid;
		int32 mapid;
		int8 roletype;				// 角色类型 
		int32 exp;					// 经验 
		int32 posx;					// X
		int32 posy;					// Y
		int32 gold;
		int32 silver;
		int32 copper;
		int32 lastLogin;
		int8 country;
		int32 teamid;
	};

	struct t_UserGateBase
	{
		t_UserGateBase()
		{
			uid = x = y = level = vip = sceneid = mapid = zoneid = countryID = teamid = 0;
			bzero(name, sizeof(name));
		}

		int32 uid;
		char name[MAX_NAMESIZE + 1];
		int32 x;
		int32 y;
		int16 level;
		int8 vip;
		int64 sceneid;
		int32 mapid;
		int32 zoneid;
		int8 countryID;
		int32 teamid;
	};

	struct t_UserWorldBase // World
	{

	};


	struct t_UserWorldBase2 // offline
	{

	};

	/////////////////////////////////s2dp/////////////////////////////////////////

	// 消息的结构体
	struct t_MsgObject
	{
		char conent[MAX_ACCNAMESIZE + 1];
	};

	// 消息详细结构
	struct t_RelChatMsg
	{
		int64 msgid; 		// 唯一消息编号
		int64 senduid;		// 发送者ID
		char sendname[MAX_NAMESIZE + 1];	// 发送者名字
		int64 recvuid;		// 接收者ID
		char recvname[MAX_NAMESIZE + 1];	// 接收者名字
		int32 sendtime;	// 发送时间
		t_MsgObject msgobj;	// 消息的结构体	
	};

	// 加载角色数据 
	const int32 SS_RQ_LOAD_USER = PRO_S2S_CHAT + 0;
	struct SSRqLoadUser : public NetMsgSS
	{
		SSRqLoadUser() :NetMsgSS(SS_RQ_LOAD_USER)
		{
			uid = sceneid = enterType = 0;
		}
		int64 uid;
		int64 sceneid;
		int32 enterType; /* 0首次进入,1更改场景,2离线加载 */
	};

	// 玩家从场景退出
	const int32 SS_RQ_CLIENT_EXIT_SCENE = PRO_S2S_CHAT + 1;
	struct SSRqClientExitScene : public NetMsgSS
	{
		SSRqClientExitScene() :NetMsgSS(SS_RQ_CLIENT_EXIT_SCENE)
		{
		}
		int32 nReason;
	};

	// 保存数据 
	const int32	SS_RQ_SAVE_USER = PRO_S2S_CHAT + 2;
	struct SSRqSaveUser : public NetMsgSS
	{
		SSRqSaveUser() :NetMsgSS(SS_RQ_SAVE_USER)
		{
		}
		t_UserSceneBase base;
		int32 size;
		BinaryHeader header;
		int32 getSize()
		{
			return sizeof(SSRqSaveUser) + header.size;
		}
	};

	////////////////////////////////d2s//////////////////////////////////////////

	/* 加载角色数据 */
	const int32 SS_RT_LOAD_USER = PRO_S2S_CHAT + 3;
	struct SSRtLoadUser : public NetMsgSS
	{
		SSRtLoadUser() :NetMsgSS(SS_RT_LOAD_USER)
		{
		}
		t_UserSceneBase base;
		int32 size;
		BinaryHeader header;
		int32 getSize()
		{
			return sizeof(SSRtLoadUser) + header.size;
		}
	};


	////////////////////////////////s2fep//////////////////////////////////////////

	const int32 SS_NT_SYNC_USER_SCENE = PRO_S2S_CHAT + 4;
	struct SSNtSyncUserScene : public NetMsgSS
	{
		SSNtSyncUserScene() :NetMsgSS(SS_NT_SYNC_USER_SCENE)
		{
			uid = 0;
		}
		int64 uid;
	};

	/* 加载角色数据到网关 */
	const int32 SS_NT_SYNC_USER_DATA = PRO_S2S_CHAT + 5;
	struct SSNtSyncUserData : public NetMsgSS
	{
		SSNtSyncUserData() :NetMsgSS(SS_NT_SYNC_USER_DATA)
		{
		}
		t_UserGateBase base;
	};

	/*
	 * 广播消息
	 */
	const int32 SS_NT_BORADCAST_MSG = PRO_S2S_CHAT + 6;
	struct SSNtBoradCastMsg : public NetMsgSS
	{
		SSNtBoradCastMsg() : NetMsgSS(SS_NT_BORADCAST_MSG)
		{
			msgtype = regid = regid = x = y = size = 0;
		}

		/* 广播消息类型 */
		enum
		{
			TYPE_ALL = 0,
			TYPE_COUNTRY,
			TYPE_MAPID,
			TYPE_SCENE,
			TYPE_ZONE,
			TYPE_NINE,
			TYPE_TEAM
		};

		int32 msgtype;	/* 0全体,1国家,2地图,3场景,4区域,5九屏,6队伍 */
		int32 regid;	/* 范围参考值,复用：国家ID,地图ID,场景ID,区域ID,队伍ID */
		int64 userid;	/* 用户ID参考值 */
		int32 x;		/* 坐标x */
		int32 y;		/* 坐标y */
		int32 size;
		char data[0];
	};

	// 客户端退出 
	const int32 SS_RQ_PLAYER_EXIT = PRO_S2S_CHAT + 7;
	struct SSRqPlayerExit : public NetMsgSS
	{
		SSRqPlayerExit() : NetMsgSS(SS_RQ_PLAYER_EXIT)
		{
			nReason = 0;
			nPostion = 0;
		}

		enum
		{
			REASON_UNKOWN = 0,			// 未知 
			REASON_SERVER_TICKED,			// 服务器踢出
			REASON_CLIENT_EXIT,			// 主动退出 
			REASON_TIMEOUT,				// 超时断开 
			REASON_PACKAGE_ERROR,			// 非法协议 
			REASON_SEND_ERROR,			// 向Client发送时出错 
			REASON_SWITCH_SCENE,			// 切换场景（这个仅对Scene，dp）
			REASON_REPEAT_CHARACTER = 99,	// 重复登录
		};

		enum
		{
			STATE_IN_UNKOWN = 0,	// 未知 
			STATE_IN_LOGIN,		// 在登录时退出 
			STATE_IN_SELECT,		// 在选择角色时退出 
			STATE_IN_WORLD,		// 在WORLD中 
			STATE_IN_SCENE,		// 在场景中退出 
		};

		int64 uid;
		int32 nReason;
		int32 nPostion;				// 玩家所在位置 
	};

	// 注册场景 
	const int32 SS_RQ_REGISTER_SCENE = PRO_S2S_CHAT + 8;
	struct SSRqRegisterScene : public NetMsgSS
	{
		SSRqRegisterScene() :NetMsgSS(SS_RQ_REGISTER_SCENE)
		{
		}

		QWORD sceneid;
		QWORD sceneTempID;
		char name[MAX_NAMESIZE + 1];
		char fileName[MAX_NAMESIZE + 1];
		DWORD dwCountryID;
		BYTE byLevel;
		DWORD mapid;
	};

	// 注销场景 
	const int32 SS_RQ_CANCEL_SCENE = PRO_S2S_CHAT + 9;
	struct SSRqCancelScene : public NetMsgSS
	{
		SSRqCancelScene() :NetMsgSS(SS_RQ_CANCEL_SCENE)
		{

		}
		int32 nSceneNum;
		int32 arrSceneID[MAX_MAP_NUM];
	};

	// 进入场景结果
	const int32 SS_RQ_ENTER_SCENE_RESULT = PRO_S2S_CHAT + 10;
	struct SSRqEnterSceneResult : public NetMsgSS
	{
		SSRqEnterSceneResult() :NetMsgSS(SS_RQ_ENTER_SCENE_RESULT)
		{
			nSceneID = nEnterType = nCross = nResult = 0;
		}
		enum
		{
			E_ENTER_SUCCESS = 0,
			E_ENTER_FAIL,
		};
		int32 nSceneID;
		int32 nEnterType;
		int32 nCross;// 是否为跨服，1是，则需要通知原场景，0否，则需要进入主场景 
		int32 nResult;
	};

	/*

	切换场景，由ss向ws请求
	参考td

	*/
	const int32 SS_RQ_CHANGE_SCENE = PRO_S2S_CHAT + 11; // 请求切换场景 
	struct SSRqChangeScene : public NetMsgSS
	{
		SSRqChangeScene() :NetMsgSS(SS_RQ_CHANGE_SCENE)
		{
			uid = sceneID = 0;
		}
		int64 uid;
		int32 sceneID;
		stEnterSceneParam stParam;
	};

	/* ChatMsg */
	/* 单聊转发消息 */
	const int32 SS_RQ_CHATTOONE = PRO_S2S_CHAT + 12;
	struct SSRqChatToOne : public NetMsgSS
	{
		SSRqChatToOne() :NetMsgSS(SS_RQ_CHATTOONE)
		{
		}
		int64 fromUID;
		int64 toUID;
	};

	const int32 SS_RQ_REL_SCENE_ADD = PRO_S2S_CHAT + 13;
	struct SSRqRelalionAdd : public NetMsgSS
	{
		SSRqRelalionAdd() :NetMsgSS(SS_RQ_REL_SCENE_ADD)
		{

		}
	};


	//////////////////////////////////////////////////////////////////////////

	/* 全局信息 */
	const int32 SS_RT_GLOBAL_INFO = PRO_S2S_LOAD + 0;
	struct SSRtGlobalInfo : public NetMsgSS
	{
		SSRtGlobalInfo() :NetMsgSS(SS_RT_GLOBAL_INFO)
		{

		}
		// 第几次启动 
		int32 nStartTimes;
	};

	/*-------------------------------------------------------------------
	* @Brief : 保存在WS上的数据，WS上保存的数据比较少，也减少S2W数据同步
	*
	* @Author:hzd 2015:11:6
	*------------------------------------------------------------------*/
	struct StUserDataForWs
	{
		StUserDataForWs()
		{
			memset(this, 0, sizeof(*this));
		}

		StUserDataForWs(const StUserDataForWs* _userData)
		{
			memcpy(this, _userData, sizeof(StUserDataForWs));
		}
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

	};

	/* 选择角色结果 */
	const int32 SS_RT_SELECT_ROLE_RESULT = PRO_S2S_LOAD + 1;
	struct SSRtSelectRoleResult : public NetMsgSS
	{
		SSRtSelectRoleResult() :NetMsgSS(SS_RT_SELECT_ROLE_RESULT)
		{
			nResult = fepSessionID = 0;
		}
		enum {

			E_SELECT_SUCCESS = 0,
			E_SELECT_LOADING,	// 加载中 
			E_SELECT_NOT_FOUND, // 找不到
		};
		int32 nResult;
		int64 fepSessionID;
		StUserDataForWs data;
	};

	/* 加载数据 */
	const int32 SS_RT_LOAD_SORTLIST = PRO_S2S_LOAD + 2;
	struct SSRtLoadSortLists : public NetMsgSS
	{
		SSRtLoadSortLists() :NetMsgSS(SS_RT_LOAD_SORTLIST)
		{
			nByteSize = 0;
			memset(arrByte, 0, sizeof(arrByte));
		}
		int32 nByteSize; /* 该长度为proto真实长度 */
		char arrByte[4096];
	};

	// 加载角色列表 
	const int32 SS_RQ_LOADLIST = PRO_S2S_LOAD + 3;
	struct SSRqLoadList : public NetMsgSS
	{
		SSRqLoadList() :NetMsgSS(SS_RQ_LOADLIST)
		{
			accid = 0;
		}
		int64 accid;
	};

	// 客户端退出 
	const int32 SS_NT_PLAYER_EXIT = PRO_S2S_LOAD + 4;
	struct SSNtRqPlayerExit : public NetMsgSS
	{
		SSNtRqPlayerExit() : NetMsgSS(SS_NT_PLAYER_EXIT)
		{
			nReason = 0;
			nPostion = 0;
		}

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


	};

	// 创建频道
	const int32 SS_NT_CREATE_CHANNEL = PRO_S2S_LOAD + 5;
	struct SSNtChannelCreate : public NetMsgSS
	{
		SSNtChannelCreate() : NetMsgSS(SS_NT_CREATE_CHANNEL)
		{

		}
		char name[MAX_NAMESIZE + 1];
		int8 count;
		int64 uids[0];
	};

	// 更新频道
	const int32 SS_NT_UPDATE_CHANNLE = PRO_S2S_LOAD + 6;
	struct SSNtChannelUpdate : public NetMsgSS
	{
		SSNtChannelUpdate() :NetMsgSS(SS_NT_UPDATE_CHANNLE)
		{

		}
		char name[MAX_NAMESIZE + 1];
		int8 opt;//0全部更新，1新增，2删除
		int8 count;
		int64 uids[0];
	};

	// 删除频道
	const int32 SS_NT_DELETE_CHANNEL = PRO_S2S_LOAD + 7;
	struct SSNtChannelDelete : public NetMsgSS
	{
		SSNtChannelDelete() :NetMsgSS(SS_NT_DELETE_CHANNEL)
		{

		}
		char name[MAX_NAMESIZE + 1];
	};

	//////////////////////////////////////////////////////////////////////////


	/* 请求进入场景 */
	const int32 SS_RQ_ReqTransfer = PRO_S2S_LOAD + 8;
	struct SSRqEnterScene : public NetMsgSS
	{
		SSRqEnterScene() :NetMsgSS(SS_RQ_ReqTransfer)
		{
			uid = mapid = sceneid = enterscenetime = 0;
		}
		int64 uid;
		int64 sceneid;
		int16 mapid;
		int32 enterscenetime;
	};

	/* 请求场景结果 */
	const int32 SS_RQ_ENTER_RESULT = PRO_S2S_LOAD + 9;
	struct SSRqEnterResult : public NetMsgSS
	{
		SSRqEnterResult() :NetMsgSS(SS_RQ_ENTER_RESULT)
		{
			nCharID = nResult = 0;
		}
		enum
		{
			E_ENTER_SUCCESS = 0,
			E_ENTER_FAIL,
		};

		int64 nCharID;
		int32 nResult;
	};

#pragma pack(pop)

}; //namespace

#endif



