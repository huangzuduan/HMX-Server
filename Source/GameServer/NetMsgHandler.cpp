#include "GameServer_PCH.h"


NetMsgHandler::NetMsgHandler()
{
	/* common 需要用到内部协议 */
	/* 内部协议，即不分不同servertype，都去做统一的事情，如登录，返回列表，ping等等操作 */ 
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler) \
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(PRO_SS_RQ_LOGIN,SSRqLogin,recvLoginRequest);
	REGISTER_INTERNAL_MESSAGE(PRO_SS_RT_LOGINED,SSRtLogined,recvLoginReponse);
	REGISTER_INTERNAL_MESSAGE(PRO_SS_RQ_PING_S,SSRqPingToS, recvPingRequest);
	REGISTER_INTERNAL_MESSAGE(PRO_SS_RT_SERVERINFO_LIST, SSServerRegList, recvSrvListNotifty);
	//REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_CONNECT_INFO,	SSNotifyConnectInfo,NotifyConnectInfo);
	//REGISTER_INTERNAL_MESSAGE(PRO_SS_REQ_INIT_CLIENT,	SSReqInitClient,	QqInitClient);

#undef REGISTER_INTERNAL_MESSAGE

	/*  从WS过来的业务协议 */
#define REGISTER_W2S_MESSAGE(msg_idx,cls,handler) \
	{\
		RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcWorldHandler::handler, ProcWorldHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_W2S_MESSAGE(PRO_W2S_ReqTransfer, W2SRqEnterScene, RqEnterScene);		/* 请求进入场景 */
	REGISTER_W2S_MESSAGE(PRO_W2S_RepEnterResult, W2SNtEnterResult, NtEnterResult);/* 请求进入场景 */
	REGISTER_W2S_MESSAGE(PRO_W2S_LOAD_UIDS, W2SLoadUids, NtLoadUids);


#undef REGISTER_W2S_MESSAGE

	// dp 
#define REGISTER_DP_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcDpHandler::handler, ProcDpHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_DP_MESSAGE(PRO_D2S_LOAD_USER, D2SLoadUser, RtLoadUserData);

#undef REGISTER_DP_MESSAGE

		// ls
#define REGISTER_LS_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcLsHandler::handler, ProcLsHandler::Instance(), _1, _2, _3)); \
	}

//	REGISTER_LS_MESSAGE(PRO_L2W_LOADLIST, L2WLoadList, RqLoadList);

#undef REGISTER_LS_MESSAGE

	// fep
#define REGISTER_FEP_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcFepHandler::handler, ProcFepHandler::Instance(), _1, _2, _3)); \
	}
	//REGISTER_FEP_MESSAGE(PRO_C2W_SELECT_ROLE, C2WSelectRole, RqSelectRole);
	//REGISTER_FEP_MESSAGE(PRO_C2W_CREATE_ROLE, C2WCreateRole, RqCreateRole);
	REGISTER_FEP_MESSAGE(PRO_F2S_PLAYER_EXIT, F2SRqPlayerExit, RqPlayerExit);

#undef REGISTER_FEP_MESSAGE

	/* 从玩家过来的协议 */
#define REGISTER_C2S_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcFepHandler::handler, ProcFepHandler::Instance(), _1, _2, _3)); \
	}

	//	REGISTER_C2S_MESSAGE(PRO_C2S_CHAT_WORLD,C2SCharWorld,ReqChatWorld);				/* 世界聊天 */
	REGISTER_C2S_MESSAGE(PRO_C2S_SCENE_INIT_DATA, C2SClientIsReady, RqClientIsReady);	/* 请求场景数据 */
	REGISTER_C2S_MESSAGE(PRO_C2S_CHANGE_SCENE, C2SClientIsReady, ReqChangeScene);		/* 切换场景 */
	REGISTER_C2S_MESSAGE(PRO_C2S_POSITION_MOVE, C2SPositionMove, ReqPositionMove);	/* 请求移动 */
	REGISTER_C2S_MESSAGE(PRO_C2S_SHOPPING_BUY_ITME, C2SShoppingBuyItem, ReqShoppingBuyItem); /* 商城 */
	REGISTER_C2S_MESSAGE(PRO_C2S_SHOPPING_SELL_ITME, C2SShoppingSellItem, ReqShoppingSellItem); /* 商城 */

	REGISTER_C2S_MESSAGE(PRO_C2S_ITEM_USE_OBJECT, C2SItemUseObject, ReqUseItem);
	REGISTER_C2S_MESSAGE(PRO_C2S_CHAT_TO_WORLD, C2SChatToWorld, RqChatToWorld);

	REGISTER_C2S_MESSAGE(PRO_C2S_RELATION_LIST, C2SRelationList, rqRelationList);
	REGISTER_C2S_MESSAGE(PRO_C2S_RELATION_ADD, C2SRelationAdd, rqRelationAdd);
	REGISTER_C2S_MESSAGE(PRO_C2S_RELATION_REMOVE, C2SRelationRemove, rqRelationRemove);

#undef REGISTER_C2S_MESSAGE

}


NetMsgHandler::~NetMsgHandler()
{ 
}


void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	Zebra::logger->info("连接成功！来自于:id=%d ip=%s,port=%d", rSocket.SID(),rSocket.GetIp().c_str(),(int32)rSocket.GetPort());
	zSession* pSession = NetService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (pSession)
	{
		if (pSession->serverType == zSession::SERVER_TYPE_CLIENT)
		{
			SSRqLogin send;
			send.serverID = NetService::getMe().getServerID();
			send.serivceID = pSession->serivceid;
			pSession->sendMsg(&send, send.GetPackLength());
			Zebra::logger->info("发送登录信息到:ip=%s port=%d", rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
		}
	}
	else
	{
		ASSERT(0);
	}
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize)
{
	zSession* pSession = NetService::getMe().getSessionMgr().get(rSocket.SLongID());
	if(pSession == NULL)
	{
		Zebra::logger->error("Can not find session");
		rSocket.OnEventColse();
		return ;
	}

	const MsgFunc* pMsgHandlerInfo = GetMsgHandler(pMsg->protocol);
	if(pMsgHandlerInfo == NULL)
	{
		Zebra::logger->error("找不到该协议:%d,大小:%d", pMsg->protocol,nSize);
		rSocket.OnEventColse();
		return;
	}

	Zebra::logger->info("收到协议=%d", pMsg->protocol);

	(pMsgHandlerInfo->handlerFun)((zSession*)(pSession),pMsg,nSize);

}

/* 有Server断开回调(此时socket已经回收) */ 
void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{     
	Zebra::logger->info("连接断开！来自于:id=%d ip=%s,port=%d", rSocket.SID(), rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
}

void NetMsgHandler::recvLoginRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const SSRqLogin* packet = static_cast<const SSRqLogin*>(pMsg);
	const zSerivceCfgMgr::Server* serverCfg = NetService::getMe().getServerCfgMgr().getServer(packet->serverID);
	if (!serverCfg)
	{
		ASSERT(0);
		return;
	}

	pSession->setSessionType(serverCfg->getSessType());
	pSession->serivceid = packet->serivceID;
	pSession->serverid = packet->serverID;
	zServerRegMgr& regMgr = NetService::getMe().getServerRegMgr();
	zServerReg* addReg = regMgr.CreateObj();
	if (addReg)
	{
		SSRtLogined sendLg;
		addReg->id = packet->serverID;
		addReg->sessid = pSession->id;
		if (!regMgr.add(addReg))
		{
			Zebra::logger->error("注册服务器ID重复");
			ASSERT(0);
			regMgr.DestroyObj(addReg);
			sendLg.result = SSRtLogined::SUCCESS;
			pSession->sendMsg(&sendLg, sendLg.GetPackLength());
			return;
		}
		else
		{
			sendLg.result = SSRtLogined::SUCCESS;
			pSession->sendMsg(&sendLg, sendLg.GetPackLength());
		}

		if (serverCfg->recvsrvlist)
		{
			struct MyStruct : public execEntry<zServerReg>
			{
				virtual bool exec(zServerReg* entry)
				{
					const zSerivceCfgMgr::Server* serverCfg = NetService::getMe().getServerCfgMgr().getServer(entry->id);
					if (!serverCfg)
					{
						ASSERT(0);
						return true;
					}

					if (serverCfg->broadcastlist)
					{
						outServerID.push_back(entry->id);
					}
					return true;
				}
				std::vector<int32> outServerID;
			};

			MyStruct exec;
			regMgr.execEveryServer(exec);

			SSServerRegList sendList;
			std::vector<int32>::const_iterator it = exec.outServerID.begin();
			for (; it != exec.outServerID.end(); ++it)
			{
				sendList.reglist[sendList.count].id = *it;
				sendList.count++;
			}
			pSession->sendMsg(&sendList, sendList.GetPackLength());

		}

		if (serverCfg->broadcastlist)
		{
			struct MyStruct : public execEntry<zServerReg>
			{
				MyStruct(int32 serverID):addServerID(serverID)
				{

				}

				virtual bool exec(zServerReg* entry)
				{
					const zSerivceCfgMgr::Server* serverCfg = NetService::getMe().getServerCfgMgr().getServer(entry->id);
					if (!serverCfg)
					{
						ASSERT(0);
						return true;
					}

					if (serverCfg->recvsrvlist)
					{
						zSession* session = NetService::getMe().getSessionMgr().get(entry->sessid);
						if (session)
						{
							SSServerRegList sendList;
							sendList.reglist[sendList.count].id = addServerID;
							sendList.count++;
							session->sendMsg(&sendList,sendList.GetPackLength());
						}
					}
					return true;
				}

				int32 addServerID;
			};
			MyStruct exec(addReg->id);
			regMgr.execEveryServer(exec);
		}
	}
	else
	{
		ASSERT(0);
	}

}

void NetMsgHandler::recvLoginReponse(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const SSRtLogined* packet = static_cast<const SSRtLogined*>(pMsg);
	if (packet->result == SSRtLogined::SUCCESS)
	{
		Zebra::logger->error("登录成功");
		if (pSession->sessionType == zSession::FOR_WORLD)
		{
			SceneManager::getInstance().init();
		}

	}
	else
	{
		Zebra::logger->error("登录失败");
		ASSERT(0);
	}
}

void NetMsgHandler::recvPingRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void NetMsgHandler::recvSrvListNotifty(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	SSServerRegList recevice;
	memcpy(&recevice,pMsg,nSize);
	const SSServerRegList* packet = &recevice;

	// to connect
	for (int32 i = 0; i < packet->count; ++i)
	{
		int32 serverID = packet->reglist[i].id;
		const zSerivceCfgMgr::Server* serverCfg = NetService::getMe().getServerCfgMgr().getServer(serverID);
		if (serverCfg == NULL)
		{
			Zebra::logger->error("本地找不到该服务器配置ID:%d",serverID);
			continue;
		}

		std::map<int32, zSerivceCfgMgr::Serivce>::const_iterator it = serverCfg->serivces.begin();
		for (; it != serverCfg->serivces.end();++it)
		{
			const zSerivceCfgMgr::Serivce& info = it->second;
			if (stricmp(info.name.c_str(), "server") == 0 && stricmp(info.fun.c_str(), "forss") == 0)
			{
				zSession* session = NetService::getMe().getSessionMgr().connect(info.id, info.ip.c_str(), info.port,
					boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
					boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
					boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
				);
				if (!session)
				{
					Zebra::logger->error("Connect Server Fail!");
					ASSERT(0);
					continue;
				}
				session->setSessionType(serverCfg->getSessType());
				session->setServerID(serverID);
			}
		}
	}
}


