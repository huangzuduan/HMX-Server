#ifndef __COMMON_Rq_H_
#define __COMMON_Rq_H_

#include "BaseDefine.h"
#include "DbConfig.h"
#include "NetConfig.h"
#include "csCommon.h"

namespace C
{
	/*
		服务器与客户端或客户端与服务器直接通信的协议
	 */

#pragma pack(push,1)


	enum ProRqFunc
	{
		PRO_LOGIN = PRO_C2S + 100,		// 登录相关 
		PRO_SCENE = PRO_C2S + 200,		// 场景相关 
		PRO_USER = PRO_C2S + 300,		// 主角相关  
		PRO_EQUIP = PRO_C2S + 400,		// 装备相关
		PRO_ITEM = PRO_C2S + 500,		// 背包相关
		PRO_QUEST = PRO_C2S + 600,		// 任务相关 
		PRO_CHANNEL = PRO_C2S + 700,	// 频道相关 
		PRO_RELATION = PRO_C2S + 800,	// 社会关系
		PRO_CHAT = PRO_C2S + 900,		// 聊天模块
		PRO_SHOP = PRO_C2S + 1000,		// 商城模块
		PRO_PACK = PRO_C2S + 1100,		// 背包模块
		PRO_MESSAGE = PRO_C2S + 1200,	// 信箱模块
	};

	// 主动断开连接 
	const int32 RQ_CLOSE = PRO_LOGIN + 1;
	struct RqClose : public NetMsgSS
	{
		RqClose() :NetMsgSS(RQ_CLOSE)
		{
		}
	};

	// 发送加密请求 
	const int32 RQ_ENCRYPT = PRO_LOGIN + 2;
	struct RqEncryptInfo : public NetMsgSS
	{
		RqEncryptInfo() :NetMsgSS(RQ_ENCRYPT)
		{
		}
	};

	// 返回密钥 
	const int32 RT_ENCRYPT_INFO = PRO_LOGIN + 3;
	struct RtEncryptInfo : public NetMsgSS
	{
		RtEncryptInfo() :NetMsgSS(RT_ENCRYPT_INFO)
		{

		}
		char encryptKey[MAX_ENCRYPTSIZE + 1];
	};


	// 服务器对即将登录请求准备完成 
	const int32 RT_LOGIN_READY_FINISH = PRO_LOGIN + 4;
	struct RtLoginReadyFinish : public NetMsgSS
	{
		RtLoginReadyFinish() :NetMsgSS(RT_LOGIN_READY_FINISH)
		{

		}
	};

	// 帐号登录 
	const int32 RQ_ACCOUNT_LOGIN = PRO_LOGIN + 5;
	struct RqAccountLogin : public NetMsgSS
	{
		RqAccountLogin() :NetMsgSS(RQ_ACCOUNT_LOGIN)
		{
			loginType = LOGINTYPE_NAMEPASS;
			bzero(username, sizeof(username));
			bzero(password, sizeof(password));
		}
		enum
		{
			LOGINTYPE_NAMEPASS = 0,	//普通帐号密码登录
			LOGINTYPE_RSA,			//RSA检验登录
			LOGINTYPE_CREATENAME,	//创建普通帐号
			LOGINTYPE_CREATERSA,	//创建RSA帐号
		};
		int8 loginType;
		char username[MAX_NAMESIZE + 1];
		char password[MAX_NAMESIZE + 1];
	};

	// 注册帐号
	const int32 RQ_ACCOUNT_REGIEST = PRO_LOGIN + 6;
	struct RqAccountRegiest : public NetMsgSS
	{
		RqAccountRegiest() :NetMsgSS(RQ_ACCOUNT_REGIEST)
		{
			bzero(username, sizeof(username));
			bzero(password, sizeof(password));
		}
		char username[MAX_NAMESIZE + 1];
		char password[MAX_NAMESIZE + 1];
	};

	// 获得随机名 
	const int32 RQ_ACCOUNT_RAND = PRO_LOGIN + 7;
	struct RqRandAccount : public NetMsgSS
	{
		RqRandAccount() :NetMsgSS(RQ_ACCOUNT_RAND)
		{
			bzero(username, sizeof(username));
			bzero(password, sizeof(password));
		}
		char username[MAX_NAMESIZE + 1];
		char password[MAX_NAMESIZE + 1];
	};

	struct t_NameInfo
	{
		char name[MAX_NAMESIZE + 1];
	};

	// 名字列表 
	const int32 RT_NAMES_LIST = PRO_LOGIN + 8;
	struct RtNamesList : public NetMsgSS
	{
		RtNamesList() :NetMsgSS(RT_NAMES_LIST)
		{
			count = 0;
		}
		int8 count;
		t_NameInfo list[0];
	};

	// 选择角色 
	const int32 RQ_Rq_SELECT_ROLE = PRO_LOGIN + 9;
	struct RqSelectRole : public NetMsgSS
	{
		int64 uid;
		RqSelectRole() :NetMsgSS(RQ_Rq_SELECT_ROLE)
		{
			uid = 0;
		}
	};

	// 返回登录信息 
	const int32 RT_ACC_LOGIN = PRO_LOGIN + 10;
	struct RtAccLogin : public NetMsgSS
	{
		RtAccLogin() :NetMsgSS(RT_ACC_LOGIN)
		{
			accid = result = keytime = 0;
			memset(keymd5, 0, MAX_NAMESIZE);
		}
		int64 accid;
		int32 result; //0成功,1失败,2...
		char keymd5[MAX_NAMESIZE + 1];
		int32 keytime;
	};

	// 创建角色 
	const int32 RQ_CREATE_ROLE = PRO_LOGIN + 11;
	struct RqCreateRole : public NetMsgSS
	{
		int64 accid;
		int8 roleType;
		char name[MAX_NAMESIZE + 1];
		char keymd5[MAX_NAMESIZE + 1];
		int32 keytime;

		RqCreateRole() :NetMsgSS(RQ_CREATE_ROLE)
		{
			accid = roleType = keytime = 0;
			memset(name, 0, sizeof(name));
			memset(keymd5, 0, sizeof(keymd5));
		}
	};

	// 创建结果
	const int32	RT_CREATE_RET = PRO_LOGIN + 12;
	struct RtCreateRet : public NetMsgSS
	{
		RtCreateRet() :NetMsgSS(RT_CREATE_RET)
		{
			reasoin = newid = 0;
		}
		int8 reasoin;
		int64 newid;
	};

	// 删除角色
	const int32 RQ_DELETE_ROLE = PRO_LOGIN + 13;
	struct RqDeleteRole : public NetMsgSS
	{
		RqDeleteRole() :NetMsgSS(RQ_DELETE_ROLE)
		{
			uid = accid = keytime = 0;
			memset(keymd5, 0, sizeof(keymd5));
		}
		int64 uid;
		int64 accid;
		char keymd5[MAX_NAMESIZE + 1];
		int32 keytime;
	};

	// 角色列表
	const int32 RT_USERLIST_LOGIN = PRO_LOGIN + 14;
	struct RtUserListLogon : public NetMsgSS
	{
		RtUserListLogon() :NetMsgSS(RT_USERLIST_LOGIN)
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
	};

	// 请求生成帐号
	const int32 RQ_GENENER_ACCOUNT = PRO_LOGIN + 15;
	struct rqGenenerAccount : public NetMsgSS
	{
		rqGenenerAccount() :NetMsgSS(RQ_GENENER_ACCOUNT)
		{
			bzero(inpassword, sizeof(inpassword));
		}
		char inpassword[MAX_NAMESIZE + 1];
	};

	//返还生成的帐号
	const int32 RT_GENERATE_ACCOUNT = PRO_LOGIN + 16;
	struct rtGenerateAccount : public NetMsgSS
	{
		rtGenerateAccount() :NetMsgSS(RT_GENERATE_ACCOUNT)
		{
			AccounID = 0;
			bzero(publickey, sizeof(publickey));
			bzero(privatekey, sizeof(privatekey));
		}
		int64 AccounID;
		char publickey[MAX_ACCNAMESIZE + 1];
		char privatekey[MAX_ACCNAMESIZE + 1];
	};

	//////////////////////////////场景模块////////////////////////////////////////////

	// 加载完成
	const int32 RT_ENTER_SCENE_LOADED = PRO_SCENE + 1;
	struct RtEnterSceneLoaded : public NetMsgSS
	{

		RtEnterSceneLoaded() :NetMsgSS(RT_ENTER_SCENE_LOADED)
		{

		}
		enum EEnterSceneResult
		{
			SUCCESS = 0,
			FAIL
		};
		int32 nResult;
	};

	//请求加载场景的数据
	const int32 RQ_SCENE_INIT_DATA = PRO_SCENE + 2;
	struct RqClientIsReady : public NetMsgSS
	{
		RqClientIsReady() :NetMsgSS(RQ_SCENE_INIT_DATA)
		{

		}

		enum
		{
			E_DATA_TYPE_NULL = 0x00000000,
			E_DATA_TYPE_CHARMAIN = 0x00000001,
			E_DATA_TYPE_PACKAGE = 0x00000002,
			E_DATA_TYPE_RELATION = 0x00000004,
			E_DATA_TYPE_PET = 0x00000008,
			E_DATA_TYPE_ALL = 0x0fffffff,
		};

		int32 nLoadDataFlags; // 需要加载的数据 
	};

	const int32 RT_CHAR_WORLD = PRO_SCENE + 3; // ss上的世界聊天 
	struct RtCharWorld : public NetMsgSS
	{
		RtCharWorld() :NetMsgSS(RT_CHAR_WORLD)
		{
			fromUID = sayLen = 0;
			memset(fromName, 0, sizeof(fromName));
			memset(sayMsg, 0, sizeof(sayMsg));
		}
		int64 fromUID;
		char fromName[MAX_NAME_LENGTH];
		int32 sayLen;
		char sayMsg[MAX_CHAR_WORLD_MSG_LENGTH];
	};

	// 进入场景的初始化结果 
	const int32 RT_SCENE_INIT_RESULT = PRO_SCENE + 4; // 场景初始化 
	struct RtSceneInitResult : public NetMsgSS
	{
		RtSceneInitResult() :NetMsgSS(RT_SCENE_INIT_RESULT)
		{

		}
		enum
		{
			SUCCESS = 0,
			FAIL
		};
		int32 nResult;
	};

	const int32 RT_SCENE_LOAD_INFO = PRO_SCENE + 5; // 进入的场景信息 
	struct RtSceneLoadInfo : public NetMsgSS
	{
		RtSceneLoadInfo() :NetMsgSS(RT_SCENE_LOAD_INFO)
		{
			mapid = 0;
		}
		int32 mapid;
	};

	// 发送数据完毕 
	const int32 RT_SEND_DATA_FINISH = PRO_SCENE + 6;
	struct RtSendDataFinish : public NetMsgSS
	{
		RtSendDataFinish() :NetMsgSS(RT_SEND_DATA_FINISH)
		{
			nServerTime = nMsgOrderID = 0;
		}
		// 这里做发一些检查值 服务器时间等  
		int32 nServerTime; // 服务器时间
		int32 nMsgOrderID; // 消息顺序值，用于外挂检查 	
	};

	/*
	 *	切换场景
	 */
	const int32 RQ_CHANGE_SCENE = PRO_SCENE + 7;	// 切换场景
	struct RqChanageScene : public NetMsgSS
	{
		RqChanageScene() :NetMsgSS(RQ_CHANGE_SCENE)
		{
			nSceneID = 0;
		}

		int32 nSceneID;
	};


	// fep->ws->ss,由ss确认 
	const int32 RQ_SWITCH_SCENE = PRO_SCENE + 8; // 更换场景  选择角色后就直接根据场景ID进入游戏 
	struct RqSwitchScene : public NetMsgSS
	{
		RqSwitchScene() :NetMsgSS(RQ_SWITCH_SCENE)
		{
			nSceneID = 0;
		}
		int32 nSceneID;

	};

	const int32 RQ_POSITION_MOVE = PRO_USER + 1;   // 
	struct RqPositionMove : public NetMsgSS
	{
		RqPositionMove() :NetMsgSS(RQ_POSITION_MOVE)
		{
			nNewX = nNewY = 0;
		}

		int32 nNewX; // 已经放大一百倍，服务器直接使用即可 
		int32 nNewY; // 已经放大一百倍，服务器直接使用即可 
	};

	/* 物品模块开始 */
	const int32 RQ_ITEM_MOVE_POSITION = PRO_ITEM + 1;// 移动位置 
	struct RqItemMovePosition : public NetMsgSS
	{
		RqItemMovePosition() : NetMsgSS(RQ_ITEM_MOVE_POSITION)
		{
			nSrcPos = nDstPos = 0;
		}
		int32 nSrcPos;
		int32 nDstPos;
	};

	const int32 RQ_ITEM_USE_OBJECT = PRO_ITEM + 2; // 使用物品 
	struct RqItemUseObject : public NetMsgSS
	{

		RqItemUseObject() :NetMsgSS(RQ_ITEM_USE_OBJECT)
		{

		}

		int32 nUniqueID;
		int32 nItemNum;
	};

	/* 商城模块开始 */
	const int32 RQ_SHOPPING_BUY_ITME = PRO_SHOP + 1;	// 商城购买物品 
	struct RqShoppingBuyItem : public NetMsgSS
	{
		RqShoppingBuyItem() : NetMsgSS(RQ_SHOPPING_BUY_ITME)
		{
			nShopID = nShopNum = 0;
		}
		int32 nShopID;
		int32 nShopNum;
	};

	const int32 RQ_SHOPPING_SELL_ITME = PRO_SHOP + 2;	// 商城卖出物品 
	struct RqShoppingSellItem : public NetMsgSS
	{

		RqShoppingSellItem() : NetMsgSS(RQ_SHOPPING_SELL_ITME)
		{
			nUniqueID = nItemNum = 0;
		}
		int32 nUniqueID;
		int32 nItemNum;
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
	const int32 RQ_CHAT_TO_CHANNEL = PRO_CHAT + 0;
	struct RqChatToChannel : public NetMsgSS
	{
		RqChatToChannel() :NetMsgSS(RQ_CHAT_TO_CHANNEL)
		{

		}

		int64 fromUID;
		int64 toChannelID;
		C::t_ChatBase fromBase;
		uint16 msgleg;
		char msgdata[0];

	};
	const int32 RQ_CHAT_TO_TEAM = PRO_CHAT + 1;
	struct RqChatToTeam : public NetMsgSS
	{
		RqChatToTeam() :NetMsgSS(RQ_CHAT_TO_TEAM)
		{

		}
		C::t_ChatBase msg;
	};

	const int32 RQ_CHAT_TO_DISCUSS = PRO_CHAT + 2;
	struct RqChatToDiscuss : public NetMsgSS
	{
		RqChatToDiscuss() :NetMsgSS(RQ_CHAT_TO_DISCUSS)
		{

		}
		C::t_ChatBase msg;
	};

	const int32 RQ_CHAT_TO_WORLD = PRO_CHAT + 3;
	struct RqChatToWorld : public NetMsgSS
	{
		RqChatToWorld() :NetMsgSS(RQ_CHAT_TO_WORLD)
		{

		}
		C::t_ChatBase msg;
	};

	struct ChatMsgInfo2
	{
		ChatMsgInfo2()
		{
			len = 0;
			memset(data, 0, sizeof(data));
		}
		uint16 len;
		char data[MAX_SOCKET_BUFFER];
	};

	// 世界聊天 
	const int32	RT_CHATTOWORLD = PRO_CHAT + 4;
	struct RtChatToWorld : public NetMsgSS
	{

		RtChatToWorld() :NetMsgSS(RT_CHATTOWORLD)
		{

		}
		ChatMsgInfo2 msg;
	};



	const int32 RQ_RELATION_LIST = PRO_RELATION + 0;
	struct RqRelationList : public NetMsgSS
	{
		RqRelationList() :NetMsgSS(RQ_RELATION_LIST)
		{

		}
	};

	const int32 RQ_RELATION_ADD = PRO_RELATION + 1;
	struct RqRelationAdd : public NetMsgSS
	{
		RqRelationAdd() :NetMsgSS(RQ_RELATION_ADD)
		{
			memset(name, 0, sizeof(name));
			rel = 0;
		}
		char name[MAX_NAMESIZE + 1];
		int32 rel;
	};

	const int32 RQ_RELATION_REMOVE = PRO_RELATION + 2;
	struct RqRelationRemove : public NetMsgSS
	{
		RqRelationRemove() :NetMsgSS(RQ_RELATION_REMOVE)
		{
			uid = 0;
		}
		int64 uid;
	};

	//创建一个会话(把自己添加进入)
	const int32  RQ_REL_CREATE_SESS = PRO_RELATION + 3;
	struct RqRelCreateSess : public NetMsgSS
	{
		RqRelCreateSess() : NetMsgSS(RQ_REL_CREATE_SESS)
		{

		}
	};

	//发送会话到频道中
	const int32 RQ_ReL_SEND_MSG = PRO_RELATION + 4;
	struct RqRelSendMsg : public NetMsgSS
	{
		RqRelSendMsg() :NetMsgSS(RQ_ReL_SEND_MSG)
		{

		}
	};

	// 单个关系信息 
	struct t_RelationData
	{
		int64 uid;
		char name[MAX_NAMESIZE + 1];
		int32 rel; // 0邀请未同意,1好友,2陌生人,3黑名单
		int32 createtime;
		int32 dealreltime; // 上次操作时间
	};

	// 好友列表
	const int32 RT_RELATION_LIST = PRO_RELATION + 5;
	struct RtRelationList : public NetMsgSS
	{
		RtRelationList() :NetMsgSS(RT_RELATION_LIST)
		{
			count = 0;
		}
		int32 count;
		C::t_RelationData list[0];
	};

	// 好友信息更新 
	const int32 RT_RELATION_UPDATE = PRO_RELATION + 6;
	struct RtRelationUpdate : public NetMsgSS
	{
		RtRelationUpdate() :NetMsgSS(RT_RELATION_UPDATE)
		{

		}
		C::t_RelationData rel;
	};

	// 好友删除
	const int32 RT_RELATION_DELETE = PRO_RELATION + 7;
	struct RtRelationDelete : public NetMsgSS
	{
		RtRelationDelete() :NetMsgSS(RT_RELATION_DELETE)
		{
			uid = 0;
		}
		int64 uid;
	};

	//////////////////////////////角色模块////////////////////////////////////////////

	// 主角主数据 
	const int32  RT_CHAR_MAIN_DATA = PRO_USER + 0;	// 角色主数据 
	struct RtCharMainData : public NetMsgSS
	{
		RtCharMainData() :NetMsgSS(RT_CHAR_MAIN_DATA)
		{

		}
		SceneUserAttr userVal;
		EntryPkValBase pkVal;
	};

	// 钱包数据 
	const int32 RT_CHAR_MONEY_DATA = PRO_USER + 1;	// 钱包数据 
	struct RtCharMoneyData : public NetMsgSS
	{
		RtCharMoneyData() :NetMsgSS(RT_CHAR_MONEY_DATA)
		{
			nGold = nSilver = nCopper = 0;
		}
		int32 nGold;
		int32 nSilver;
		int32 nCopper;
	};

	//////////////////////////////频道模块////////////////////////////////////////////
	const int32 RT_CHANNEL_JION = PRO_CHANNEL + 0;	/* 加入频道 */
	struct RtChannelJion : public NetMsgSS
	{
		RtChannelJion() :NetMsgSS(RT_CHANNEL_JION)
		{
			channelID = 0;
			memset(name, 0, sizeof(name));
		}
		int32 channelID;
		char name[MAX_NAME_LENGTH];
	};

	const int32 RT_CHANNEL_LEAVE = PRO_CHANNEL + 1;	/* 离开频道 */
	struct RtChannelLeave : public NetMsgSS
	{
		RtChannelLeave() :NetMsgSS(RT_CHANNEL_LEAVE)
		{
			channelID = 0;
			memset(name, 0, sizeof(name));
		}
		int32 channelID;
		char name[MAX_NAME_LENGTH];
	};

	//////////////////////////////装备模块////////////////////////////////////////////

	// 穿着的装备数据 
	const int32 RT_EQUIP_MAIN_DATA = PRO_EQUIP + 0; // 装备主数据(身上穿)
	struct RtEquipMainData : public NetMsgSS
	{
		RtEquipMainData() :NetMsgSS(RT_EQUIP_MAIN_DATA)
		{

		}
	};

	//////////////////////////////背包模块///////////////////////////////////////////////

	// 单个物品数据
	struct t_ItemSlot
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
	const int32 RT_ITEM_MAIN_DATA = PRO_PACK + 0; // 背包主数据 
	struct RtUserPackages : public NetMsgSS
	{
		RtUserPackages() :NetMsgSS(RT_ITEM_MAIN_DATA)
		{
			nCount = 0;
		}
		int32 nCount;
		t_ItemSlot items[100]; // 12 + 背包上的数量 最次最多只能发送100个 
	};

	const int32 RT_ITEM_UPDATE_DATA = PRO_PACK + 1; // 增加或更新 
	struct RtItemSlotUpdate : public NetMsgSS
	{
		RtItemSlotUpdate() :NetMsgSS(RT_ITEM_UPDATE_DATA)
		{
			nCount = 0;
		}
		int32 nCount;
		t_ItemSlot items[100]; // 最次最多只能发送100个 
	};

	const int32 RT_ITEM_DELTE_DATA = PRO_PACK + 2; // 删除道具装备
	struct RtItemSlotDelete : public NetMsgSS
	{
		RtItemSlotDelete() :NetMsgSS(RT_ITEM_DELTE_DATA)
		{
			nCount = 0;
			memset(nUniqueIDs, 0, sizeof(nUniqueIDs));
		}
		int32 nCount;
		int32 nUniqueIDs[100];
	};

	//////////////////////////////任务模块///////////////////////////////////////////////

	// 任务主数据  
	const int32 RT_QUEST_MAIN_DATA = PRO_QUEST + 0; // 任务主数据 
	struct RtQuestMainData : public NetMsgSS
	{
		RtQuestMainData() :NetMsgSS(RT_QUEST_MAIN_DATA)
		{

		}

		struct QuestInfo
		{
			int32 nQuestID;
			int32 nResult0;
			int32 nResult1;
		};

		QuestInfo arrHadAccept[MAX_QUEST_LIST_COUNT];
		QuestInfo arrCanAccept[MAX_QUEST_LIST_COUNT];

	};

	///////////////////////////信箱模块///////////////////////////////////////////////

	// 查看某个信件
	const int32 RQ_LOOK_MESSAGE = PRO_MESSAGE + 0;
	struct rqLookMessage : public NetMsgSS
	{
		rqLookMessage():NetMsgSS(RQ_LOOK_MESSAGE)
		{
			msgID = askPass = 0;
		}
		int64 msgID;	// 信件ID
		int32 askPass;	// 信件密码0时，则是查看是否有该信件，>0是获得内容
	};

	// 返回信件访问密码
	const int32 RT_NEED_PASS_MESSAGE = PRO_MESSAGE + 1;
	struct rtNeedPassMessage : public NetMsgSS
	{
		rtNeedPassMessage(): NetMsgSS(RT_NEED_PASS_MESSAGE)
		{
			msgID = needPass = 0;
		}
		int64 msgID;
		int32 needPass;	 // 需要指定密码才能查看
	};

	// 返回内容信息
	const int32 RT_CONNET_MESSAGE = PRO_MESSAGE + 2;
	struct rtConentMessage : public NetMsgSS
	{
		rtConentMessage():NetMsgSS(RT_CONNET_MESSAGE)
		{
			msgID = msgLen = 0;
		}
		int64 msgID;
		int16 msgLen;
		char msgData[0];
	};

	// 信件操作
	const int32 RQ_OPT_MESSAGE = PRO_MESSAGE + 3;
	struct rqOptMessage : public NetMsgSS
	{
		rqOptMessage() :NetMsgSS(RQ_OPT_MESSAGE)
		{
			msgID = pass = optType = 0;
		}
		int64 msgID;
		int32 pass;
		int8 optType; //0无,1删除
	};

#pragma pack(pop)

};	//namespace

#endif
