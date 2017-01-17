#ifndef __COMMON_C2F_H_
#define __COMMON_C2F_H_

#include "ServerDefine.h"
#include "NetConfig.h"
#include "SrvEngine.h"

#pragma pack(push,1)

//////////////////////////////////////////////////////////////////////////

enum EProC2F
{

	PRO_C2F_ENCRYPT		= PRO_C2F_BASE + 0, // 获得密钥 
	PRO_C2F_CLOSE		= PRO_C2F_BASE + 1, // 主动退出 
	
};



// 发送加密请求 
struct C2FepEncryptInfo : public NetMsgSS
{
	C2FepEncryptInfo():NetMsgSS(PRO_C2F_ENCRYPT)
	{
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2FepClose : public NetMsgSS
{
	C2FepClose():NetMsgSS(PRO_C2F_CLOSE)
	{
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


//////////////////////////////////////////////////////////////////////////


enum EProC2L
{

	PRO_C2L_ACCOUNT_LOGIN	= PRO_C2L_BASE + 0, // 帐号登录 
	PRO_C2L_RAND_NAMES		= PRO_C2L_BASE + 2, // 获得随机名 


};

struct C2LAccountLogin : public NetMsgSS
{
	char username[32];
	char password[32];
	C2LAccountLogin():NetMsgSS(PRO_C2L_ACCOUNT_LOGIN)
	{
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2LRandNames : public NetMsgSS
{
	C2LRandNames():NetMsgSS(PRO_C2L_RAND_NAMES)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


//////////////////////////////////////////////////////////////////////////

enum EProC2SFunc
{
	PRO_C2S_SCENE_BASE = PRO_C2S_BASE + 0,		// 场景模块  
	PRO_C2S_CHAR_BASE = PRO_C2S_BASE + 100,		// 主角模块
	PRO_C2S_EQUIP_BASE = PRO_C2S_BASE + 200,	// 装备模块
	PRO_C2S_ITEM_BASE = PRO_C2S_BASE + 300,		// 背包模块 
	PRO_C2S_QUEST_BASE = PRO_C2F_BASE + 400,	// 任务模块 
	PRO_C2S_CHAT_BASE	= PRO_C2S_BASE + 500,	/* 聊天模块 */
	PRO_C2S_RELATION_BASE = PRO_C2S_BASE + 600, 
};

enum EProC2S
{

	//////////////////////////////场景模块////////////////////////////////////////////
	PRO_C2S_SCENE_INIT_DATA = PRO_C2S_SCENE_BASE + 1,	// 进入场景获得数据 
	PRO_C2S_CHANGE_SCENE = PRO_C2S_SCENE_BASE + 2,	// 切换场景

	//////////////////////////////主角模块////////////////////////////////////////////
	PRO_C2S_POSITION_MOVE = PRO_C2S_CHAR_BASE + 100,   // 


	//////////////////////////////装备模块////////////////////////////////////////////	

	//////////////////////////////背包模块////////////////////////////////////////////
	PRO_C2S_ITEM_MOVE_POSITION = PRO_C2S_ITEM_BASE + 0, // 移动位置 
	PRO_C2S_ITEM_UPDATE = PRO_C2S_ITEM_BASE + 1, // 更新物品数据 
	PRO_C2S_ITEM_USE_OBJECT = PRO_C2S_ITEM_BASE + 2, // 使用物品 


	//////////////////////////////商城模块////////////////////////////////////////////
	PRO_C2S_SHOPPING_BUY_ITME = PRO_C2S_BASE + 500,	// 商城购买物品 
	PRO_C2S_SHOPPING_SELL_ITME = PRO_C2S_BASE + 501,	// 商城卖出物品 

	///////////////////////////////聊天模块///////////////////////////////////////////
	PRO_C2S_CHAT_TO_CHANNEL = PRO_C2S_CHAT_BASE + 0,
	PRO_C2S_CHAT_TO_TEAM = PRO_C2S_CHAT_BASE + 1,
	PRO_C2S_CHAT_TO_DISCUSS = PRO_C2S_CHAT_BASE + 2,
	PRO_C2S_CHAT_TO_WORLD = PRO_C2S_CHAT_BASE + 3,

	/* 社会关系 */
	PRO_C2S_RELATION_LIST = PRO_C2S_RELATION_BASE + 0,
	PRO_C2S_RELATION_ADD = PRO_C2S_RELATION_BASE + 1,
	PRO_C2S_RELATION_REMOVE = PRO_C2S_RELATION_BASE + 2,


};

/*
 *	世界聊天 
 */
//struct C2SCharWorld : public NetMsgSS
//{
//	C2SCharWorld():NetMsgSS(0)
//	{
//		nLength = 0;
//	}
//	int32 nLength;
//	char arrMsg[MAX_CHAR_WORLD_MSG_LENGTH];
//	inline int32 GetPackLength()const
//	{
//		return sizeof(*this) - sizeof(arrMsg) + nLength;
//	}
//};

/*
 *	请求加载场景的数据 
 */
struct C2SClientIsReady : public NetMsgSS
{
	enum
	{
		E_DATA_TYPE_NULL		= 0x00000000,
		E_DATA_TYPE_CHARMAIN	= 0x00000001,
		E_DATA_TYPE_PACKAGE		= 0x00000002,
		E_DATA_TYPE_RELATION	= 0x00000004,
		E_DATA_TYPE_PET			= 0x00000008,
		E_DATA_TYPE_ALL			= 0x0fffffff,
	};
	
	int32 nLoadDataFlags; // 需要加载的数据 
		
	C2SClientIsReady():NetMsgSS(PRO_C2S_SCENE_INIT_DATA)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/*
 *	切换场景 
 */
struct C2SChanageScene : public NetMsgSS
{
	int32 nSceneID;
	C2SChanageScene() :NetMsgSS(PRO_C2S_CHANGE_SCENE)
	{
		nSceneID = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2SPositionMove : public NetMsgSS
{
	int32 nNewX; // 已经放大一百倍，服务器直接使用即可 
	int32 nNewY; // 已经放大一百倍，服务器直接使用即可 
	C2SPositionMove() :NetMsgSS(PRO_C2S_POSITION_MOVE)
	{
		nNewX = nNewY = 0;
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/* 物品模块开始 */

struct C2SItemMovePosition : public NetMsgSS
{
	int32 nSrcPos;
	int32 nDstPos;
	C2SItemMovePosition() : NetMsgSS(PRO_C2S_ITEM_MOVE_POSITION)
	{
		nSrcPos = nDstPos = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2SItemUseObject : public NetMsgSS
{
	int32 nUniqueID;
	int32 nItemNum;
	C2SItemUseObject() :NetMsgSS(PRO_C2S_ITEM_USE_OBJECT)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/* 商城模块开始 */

struct C2SShoppingBuyItem : public NetMsgSS
{
	int32 nShopID;
	int32 nShopNum;
	C2SShoppingBuyItem() : NetMsgSS(PRO_C2S_SHOPPING_BUY_ITME)
	{
		nShopID = nShopNum = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2SShoppingSellItem : public NetMsgSS
{
	int32 nUniqueID;
	int32 nItemNum;
	C2SShoppingSellItem() : NetMsgSS(PRO_C2S_SHOPPING_SELL_ITME)
	{
		nUniqueID = nItemNum = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// 发起聊天者信息 
struct t_ChatBase
{
	int64 uid;
	char name[MAX_NAMESIZE + 1];
	int16 level;
	int8 vip;
};

// 聊天
struct C2SChatToChannel : public NetMsgSS
{
	C2SChatToChannel() :NetMsgSS(PRO_C2S_CHAT_TO_CHANNEL)
	{
		
	}

	int64 fromUID;
	int64 toChannelID;
	t_ChatBase fromBase;
	uint16 msgleg;
	char msgdata[0];

};

struct C2SChatToTeam : public NetMsgSS
{
	C2SChatToTeam() :NetMsgSS(PRO_C2S_CHAT_TO_TEAM)
	{

	}
	t_ChatBase msg;
};

struct C2SChatToDiscuss : public NetMsgSS
{
	C2SChatToDiscuss() :NetMsgSS(PRO_C2S_CHAT_TO_DISCUSS)
	{

	}
	t_ChatBase msg;
};

struct C2SChatToWorld : public NetMsgSS
{
	C2SChatToWorld() :NetMsgSS(PRO_C2S_CHAT_TO_WORLD)
	{

	}
	t_ChatBase msg;
};

struct C2SRelationList : public NetMsgSS
{
	C2SRelationList() :NetMsgSS(PRO_C2S_RELATION_LIST)
	{

	}
};

struct C2SRelationAdd : public NetMsgSS
{
	C2SRelationAdd() :NetMsgSS(PRO_C2S_RELATION_ADD)
	{
		memset(name, 0, sizeof(name));
		rel = 0;
	}
	char name[MAX_NAME_LENGTH + 1];
	int32 rel;
};

struct C2SRelationRemove : public NetMsgSS 
{
	C2SRelationRemove() :NetMsgSS(PRO_C2S_RELATION_REMOVE)
	{
		uid = 0;
	}
	int64 uid;
};

//创建一个会话(把自己添加进入)
const BYTE PRO_C2S_REL_CREATE_SESS = PRO_C2S_RELATION_BASE + 3;
struct C2SRelCreateSess : public NetMsgSS
{
	C2SRelCreateSess() : NetMsgSS(PRO_C2S_REL_CREATE_SESS)
	{

	}
};

//发送会话到频道中
const BYTE PRO_C2S_ReL_SEND_MSG = PRO_C2S_RELATION_BASE + 4;
struct C2SRelSendMsg : public NetMsgSS
{
	C2SRelSendMsg() :NetMsgSS(PRO_C2S_ReL_SEND_MSG)
	{

	}
};

//////////////////////////////////////////////////////////////////////////

enum EProC2W
{

	PRO_C2W_SWITCH_SCENE = PRO_C2W_BASE + 0, // 更换场景  选择角色后就直接根据场景ID进入游戏 
	PRO_C2W_SELECT_ROLE	 = PRO_C2W_BASE + 1, // 选择角色 
	PRO_C2W_CREATE_ROLE	 = PRO_C2W_BASE + 2, // 创建角色 
	PRO_C2W_DELETE_ROLE  = PRO_C2W_BASE + 3, // 删除角色

};




// fep->ws->ss,由ss确认 
struct C2WSwitchScene : public NetMsgSS
{
	C2WSwitchScene():NetMsgSS(PRO_C2W_SWITCH_SCENE)
	{
		nSceneID = 0;
	}
	int32 nSceneID;
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2WSelectRole : public NetMsgSS
{
	int64 uid;
	C2WSelectRole():NetMsgSS(PRO_C2W_SELECT_ROLE)
	{
		uid = 0; 
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


struct C2WCreateRole : public NetMsgSS
{
	int64 accid;
	int8 roleType;
	char name[MAX_NAMESIZE + 1];
	char keymd5[MAX_NAMESIZE + 1];
	int32 keytime;

	C2WCreateRole():NetMsgSS(PRO_C2W_CREATE_ROLE)
	{
		accid = roleType = keytime = 0;
		memset(name, 0, sizeof(name));
		memset(keymd5, 0, sizeof(keymd5));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct C2WDeleteRole : public NetMsgSS
{
	int64 uid;
	int64 accid;
	char keymd5[MAX_NAMESIZE + 1];
	int32 keytime;
	C2WDeleteRole() :NetMsgSS(PRO_C2W_DELETE_ROLE)
	{
		uid =  accid = keytime = 0;
		memset(keymd5, 0, sizeof(keymd5));
	}

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)





#endif

#ifndef __COMMONS2C_H_
#define __COMMONS2C_H_

#include "ServerDefine.h"
#include "NetConfig.h"
#include "def_entity.h"

enum EProcS2CFunc
{
	PRO_S2C_SCENE_BASE = PRO_S2C_BASE + 0,		// 场景相关 
	PRO_S2C_CHAR_BASE = PRO_S2C_BASE + 100,	// 主角相关  
	PRO_S2C_EQUIP_BASE = PRO_S2C_BASE + 200,	// 装备相关
	PRO_S2C_ITEM_BASE = PRO_S2C_BASE + 300,	// 背包相关
	PRO_S2C_QUEST_BASE = PRO_S2C_BASE + 400,	// 任务相关 
	PRO_S2C_CHANNEL_BASE = PRO_S2C_BASE + 500,	// 频道相关 
	PRO_S2C_RELATION_BASE = PRO_S2C_BASE + 600,	// 社会关系

	PRO_S2C_MAX_BASE = PRO_S2C_BASE + 9999,	// 最大模块数量99
};


// s2c协议 
enum EProS2C
{

	//////////////////////////////场景模块////////////////////////////////////////////
	PRO_S2C_SCENE_INIT_RESULT = PRO_S2C_SCENE_BASE + 0, // 场景初始化 
	PRO_S2C_CHAR_WORLD = PRO_S2C_SCENE_BASE + 1, // ss上的世界聊天 
	PRO_S2C_SCENE_LOADING = PRO_S2C_SCENE_BASE + 2, // 场景加载中 
	PRO_S2C_SEND_DATA_FINISH = PRO_S2C_SCENE_BASE + 3, // 发送数据完毕 
	PRO_S2C_SCENE_LOAD_INFO = PRO_S2C_SCENE_BASE + 4, // 进入的场景信息 

													  //////////////////////////////角色模块////////////////////////////////////////////
													  PRO_S2C_CHAR_MAIN_DATA = PRO_S2C_CHAR_BASE + 0,	// 角色主数据 
													  PRO_S2C_CHAR_MONEY_DATA = PRO_S2C_CHAR_BASE + 1,	// 钱包数据 

																										//////////////////////////////装备模块////////////////////////////////////////////
																										PRO_S2C_EQUIP_MAIN_DATA = PRO_S2C_EQUIP_BASE + 0, // 装备主数据(身上穿)


																																						  //////////////////////////////任务模块///////////////////////////////////////////////
																																						  PRO_S2C_QUEST_MAIN_DATA = PRO_S2C_QUEST_BASE + 0, // 任务主数据 


																																																			//////////////////////////////背包模块///////////////////////////////////////////////
																																																			PRO_S2C_ITEM_MAIN_DATA = PRO_S2C_ITEM_BASE + 0, // 背包主数据 
																																																			PRO_S2C_ITEM_UPDATE_DATA = PRO_S2C_ITEM_BASE + 1, // 增加或更新 
																																																			PRO_S2C_ITEM_DELTE_DATA = PRO_S2C_ITEM_BASE + 2, // 删除道具装备

																																																															 //////////////////////////////频道模块///////////////////////////////////////////////
																																																															 PRO_S2C_CHANNEL_JION = PRO_S2C_CHANNEL_BASE + 0,	/* 加入频道 */
																																																															 PRO_S2C_CHANNEL_LEAVE = PRO_S2C_CHANNEL_BASE + 1,	/* 离开频道 */

																																																																												//////////////////////////////社会关系模块///////////////////////////////////////////////
																																																																												PRO_S2C_RELATION_LIST = PRO_S2C_RELATION_BASE + 0,  /* 好友列表 */
																																																																												PRO_S2C_RELATION_UPDATE = PRO_S2C_RELATION_BASE + 1,
																																																																												PRO_S2C_RELATION_DELETE = PRO_S2C_RELATION_BASE + 2,
};


#pragma pack(push, 1)


//////////////////////////////场景模块////////////////////////////////////////////
struct S2CRepCharWorld : public NetMsgSS
{
	int64 fromUID;
	char fromName[MAX_NAME_LENGTH];

	int32 sayLen;
	char sayMsg[MAX_CHAR_WORLD_MSG_LENGTH];

	S2CRepCharWorld() :NetMsgSS(PRO_S2C_CHAR_WORLD)
	{
		fromUID = sayLen = 0;
		memset(fromName, 0, sizeof(fromName));
		memset(sayMsg, 0, sizeof(sayMsg));
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(sayMsg) + sayLen;
	}
};

// 进入场景的初始化结果 
struct S2CSceneInitResult : public NetMsgSS
{

	enum
	{
		SUCCESS = 0,
		FAIL
	};
	int32 nResult;

	S2CSceneInitResult() :NetMsgSS(PRO_S2C_SCENE_INIT_RESULT)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct S2CSceneLoadInfo : public NetMsgSS
{
	int32 mapid;
	S2CSceneLoadInfo() :NetMsgSS(PRO_S2C_SCENE_LOAD_INFO)
	{
		mapid = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

/*-------------------------------------------------------------------
* @Brief : 主数据发送完成
*
* @Author:hzd 2015:11:24
*------------------------------------------------------------------*/
struct S2CSendDataFinish : public NetMsgSS
{

	// 这里做发一些检查值 服务器时间等  
	int32 nServerTime; // 服务器时间
	int32 nMsgOrderID; // 消息顺序值，用于外挂检查 	
	S2CSendDataFinish() :NetMsgSS(PRO_S2C_SEND_DATA_FINISH)
	{
		nServerTime = nMsgOrderID = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////角色模块////////////////////////////////////////////

// 主角主数据 
struct S2CCharMainData : public NetMsgSS
{
	SceneUserAttr userVal;
	EntryPkValBase pkVal;
	S2CCharMainData() :NetMsgSS(PRO_S2C_CHAR_MAIN_DATA)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// 钱包数据 
struct S2CCharMoneyData : public NetMsgSS
{
	int32 nGold;
	int32 nSilver;
	int32 nCopper;
	S2CCharMoneyData() :NetMsgSS(PRO_S2C_CHAR_MONEY_DATA)
	{
		nGold = nSilver = nCopper = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////频道模块////////////////////////////////////////////
struct S2CChannelJion : public NetMsgSS
{
	int32 channelID;
	char name[MAX_NAME_LENGTH];
	S2CChannelJion() :NetMsgSS(PRO_S2C_CHANNEL_JION)
	{
		channelID = 0;
		memset(name, 0, sizeof(name));
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct S2CChannelLeave : public NetMsgSS
{
	int32 channelID;
	char name[MAX_NAME_LENGTH];
	S2CChannelLeave() :NetMsgSS(PRO_S2C_CHANNEL_LEAVE)
	{
		channelID = 0;
		memset(name, 0, sizeof(name));
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////装备模块////////////////////////////////////////////

// 穿着的装备数据 
struct S2CEquipMainData : public NetMsgSS
{
	S2CEquipMainData() :NetMsgSS(PRO_S2C_EQUIP_MAIN_DATA)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////背包模块///////////////////////////////////////////////

// 单个物品数据
struct stItemSlot
{
	int32 nUniqueID; // 唯一ID 
	int32 nItemID;

	// 其他动态参数
	uint8 nItemNum;		// 数量 
	uint8 nIndex;		// 格子位置 0-99 
	uint8 nLock;		// 是否有锁 
};

// inventory
// 对于服务器来说，只有一个背包（包括穿在身上）
// 背包主数据 inventory
struct S2CUserPackages : public NetMsgSS
{
	int32 nCount;
	stItemSlot items[100]; // 12 + 背包上的数量 最次最多只能发送100个 
	S2CUserPackages() :NetMsgSS(PRO_S2C_ITEM_MAIN_DATA)
	{
		nCount = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(items) + nCount * sizeof(items[0]);
	}
};

struct S2CItemSlotUpdate : public NetMsgSS
{
	int32 nCount;
	stItemSlot items[100]; // 最次最多只能发送100个 
	S2CItemSlotUpdate() :NetMsgSS(PRO_S2C_ITEM_UPDATE_DATA)
	{
		nCount = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this) - sizeof(items) + nCount * sizeof(items[0]);
	}
};

struct S2CItemSlotDelete : public NetMsgSS
{
	int32 nCount;
	int32 nUniqueIDs[100];
	S2CItemSlotDelete() :NetMsgSS(PRO_S2C_ITEM_DELTE_DATA)
	{
		nCount = 0;
		memset(nUniqueIDs, 0, sizeof(nUniqueIDs));
	}
	inline int32 GetPackLength() const
	{
		return sizeof(*this) - sizeof(nUniqueIDs) + nCount * sizeof(nUniqueIDs[0]);
	}
};

//////////////////////////////任务模块///////////////////////////////////////////////

// 任务主数据  
struct S2CQuestMainData : public NetMsgSS
{

	struct QuestInfo
	{
		int32 nQuestID;
		int32 nResult0;
		int32 nResult1;
	};

	QuestInfo arrHadAccept[MAX_QUEST_LIST_COUNT];
	QuestInfo arrCanAccept[MAX_QUEST_LIST_COUNT];

	S2CQuestMainData() :NetMsgSS(PRO_S2C_QUEST_MAIN_DATA)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};



//////////////////////////////////////////////////////////////////////////


enum EProF2C
{

	PRO_F2C_ENCRYPT_INFO = PRO_F2C_BASE + 0,	// 返回密钥信息 
	PRO_F2C_LOGIN_READY_FINISH = PRO_F2C_BASE + 1, // 服务器对即将登录请求准备完成 
	PRO_F2C_ENTER_SCENE_LOADED = PRO_F2C_BASE + 2, // 场景进入完成  

};


// 返回密钥 
struct F2CEncryptInfo : public NetMsgSS
{

	char encryptKey[MAX_ENCRYPTSIZE];

	F2CEncryptInfo() :NetMsgSS(PRO_F2C_ENCRYPT_INFO)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct F2CLoginReadyFinish : public NetMsgSS
{
	F2CLoginReadyFinish() :NetMsgSS(PRO_F2C_LOGIN_READY_FINISH)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// 加载完成 
struct F2CEnterSceneLoaded : public NetMsgSS
{
	enum EEnterSceneResult
	{
		SUCCESS = 0,
		FAIL
	};

	int32 nResult;

	F2CEnterSceneLoaded() :NetMsgSS(PRO_F2C_ENTER_SCENE_LOADED)
	{

	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

//////////////////////////////////////////////////////////////////////////

enum EProL2C
{
	PRO_L2C_ACC_LOGIN = PRO_L2C_BASE + 0,	// 返回登录信息 
	PRO_L2C_CREATE_RES = PRO_L2C_BASE + 2, // 角色创建结果 
	PRO_L2C_NAMES_LIST = PRO_L2C_BASE + 3, // 名字列表 
};


struct L2CAccLogin : public NetMsgSS
{
	int64 accid;
	int32 result; //1成功,0失败
	char keymd5[MAX_NAMESIZE + 1];
	int32 keytime;
	L2CAccLogin() :NetMsgSS(PRO_L2C_ACC_LOGIN)
	{
		accid = result = keytime = 0;
		memset(keymd5, 0, MAX_NAMESIZE);
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct L2CRoleCreateRes : public NetMsgSS
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

	L2CRoleCreateRes() :NetMsgSS(PRO_L2C_CREATE_RES)
	{
		nResult = 0;
		nNewCharID = 0;
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct L2CNamesList : public NetMsgSS
{
	int32 nCount;
	char arrNames[10][32];
	L2CNamesList() :NetMsgSS(PRO_L2C_NAMES_LIST)
	{
		nCount = 0;
		memset(arrNames, 0, 10 * 32);
	}
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

// 单个关系信息 
struct t_RelData
{
	int64 uid;
	char name[MAX_NAMESIZE + 1];
	int32 rel; // 0邀请未同意,1好友,2陌生人,3黑名单
	int32 createtime;
	int32 dealreltime; // 上次操作时间
};

// 好友列表
struct S2CRelationList : public NetMsgSS
{
	S2CRelationList() :NetMsgSS(PRO_S2C_RELATION_LIST)
	{
		count = 0;
	}
	int32 count;
	t_RelData list[0];
};

// 好友信息更新 
struct S2CRelationUpdate : public NetMsgSS
{
	S2CRelationUpdate() :NetMsgSS(PRO_S2C_RELATION_UPDATE)
	{

	}
	t_RelData rel;
};

// 好友删除
struct S2CRelationDelete : public NetMsgSS
{
	S2CRelationDelete() :NetMsgSS(PRO_S2C_RELATION_DELETE)
	{
		uid = 0;
	}
	int64 uid;
};

#pragma pack(pop)

#endif

#ifndef __COMMON_W2C_H_
#define __COMMON_W2C_H_


#include "ServerDefine.h"
#include "NetConfig.h"
#include "SrvEngine.h"
#include "csCommon.h"


//---------------------------------------

enum EProWS2C
{
	PRO_W2C_CHATTOWORLD = PRO_W2C_BASE + 0, // 世界聊天 
	PRO_W2C_USERLIST = PRO_W2C_BASE + 1,	// 角色列表
	PRO_W2C_CREATE_RET = PRO_W2C_BASE + 2,	// 创建结果
};

#pragma pack(push,1)




struct W2CUserList : public NetMsgSS
{
	W2CUserList() :NetMsgSS(PRO_W2C_USERLIST)
	{

	}

	struct UserInfo
	{
		int64 id;
		char name[MAX_NAMESIZE + 1];
		int16 level;
		UserInfo()
		{
			id = level = 0;
			memset(name, 0, sizeof(name));
		}
	};

	UserInfo datas[4];

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};


struct ChatMsgInfo2
{
	uint16 len;
	char data[MAX_SOCKET_BUFFER];
	ChatMsgInfo2()
	{
		len = 0;
		memset(data, 0, sizeof(data));
	}
	inline int32 GetLength() const
	{
		return sizeof(*this) - sizeof(data) + len;
	}
};

struct WS2CChatToWorld : public NetMsgSS
{

	WS2CChatToWorld() :NetMsgSS(PRO_W2C_CHATTOWORLD)
	{

	}

	ChatMsgInfo2 msg;

	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

struct W2CCreateRet : public NetMsgSS
{
	W2CCreateRet() :NetMsgSS(PRO_W2C_CREATE_RET)
	{
		reasoin = newid = 0;
	}
	int8 reasoin;
	int64 newid;
	inline int32 GetPackLength()const
	{
		return sizeof(*this);
	}
};

#pragma pack(pop)


#endif
