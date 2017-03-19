#include "DBServer_PCH.h"

NetMsgHandler::NetMsgHandler()
{
	/* common 需要用到内部协议 */
	/* 内部协议，即不分不同servertype，都去做统一的事情，如登录，返回列表，ping等等操作 */ 
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler) \
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
}

	REGISTER_INTERNAL_MESSAGE(S::SS_RQ_LOGIN,S::SSRqLogin,recvLoginRequest);
	REGISTER_INTERNAL_MESSAGE(S::SS_RT_LOGINED,S::SSRtLogined,recvLoginReponse);
	REGISTER_INTERNAL_MESSAGE(S::SS_RQ_PING_S,S::SSRqPingToS, recvPingRequest);
	REGISTER_INTERNAL_MESSAGE(S::SS_RT_SERVERINFO_LIST, S::SSServerRegList, recvSrvListNotifty);

#undef REGISTER_INTERNAL_MESSAGE

	// ws 
#define REGISTER_WS_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcWorldHandler::handler, ProcWorldHandler::Instance(), _1, _2, _3)); \
	}



#undef REGISTER_WS_MESSAGE

		// ls
#define REGISTER_LS_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcLsHandler::handler, ProcLsHandler::Instance(), _1, _2, _3)); \
	}

#undef REGISTER_LS_MESSAGE

		// ss
#define REGISTER_SS_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcSsHandler::handler, ProcSsHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_SS_MESSAGE(S::SS_RQ_LOAD_USER, S::SSRqLoadUser, ReqLoadUser);
	REGISTER_SS_MESSAGE(S::SS_RQ_SAVE_USER, S::SSRtLoadUser, ReqSaveUser);
	

#undef REGISTER_SS_MESSAGE


}


NetMsgHandler::~NetMsgHandler()
{ 
}


void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	H::logger->info("连接成功！来自于:id=%d ip=%s,port=%d", rSocket.SID(),rSocket.GetIp().c_str(),(int32)rSocket.GetPort());
	zSession* pSession = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (pSession)
	{
		if (pSession->serverType == zSession::SERVER_TYPE_CLIENT)
		{
			S::SSRqLogin send;
			send.serverID = GameService::getMe().getServerID();
			send.serivceID = pSession->serivceid;
			pSession->sendMsg(&send, sizeof(send));
			H::logger->info("发送登录信息到:ip=%s port=%d", rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
		}
	}
	else
	{
		ASSERT(0);
	}
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg,int32 nSize)
{
	zSession* pSession = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	if(pSession == NULL)
	{
		H::logger->error("Can not find session");
		rSocket.OnEventColse();
		return ;
	}

	const MsgFunc* pMsgHandlerInfo = GetMsgHandler(pMsg->protocol);
	if(pMsgHandlerInfo == NULL)
	{
		H::logger->error("找不到该协议:%d,大小:%d", pMsg->protocol,nSize);
		rSocket.OnEventColse();
		return;
	}

	H::logger->info("收到协议=%d", pMsg->protocol);

	(pMsgHandlerInfo->handlerFun)((zSession*)(pSession),pMsg,nSize);

}

/* 有Server断开回调(此时socket已经回收) */ 
void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{     
	H::logger->info("连接断开！来自于:id=%d ip=%s,port=%d", rSocket.SID(), rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
}

void NetMsgHandler::recvLoginRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSRqLogin* packet = static_cast<const S::SSRqLogin*>(pMsg);
	const zSerivceCfgMgr::Server* serverCfg = GameService::getMe().getServerCfgMgr().getServer(packet->serverID);
	if (!serverCfg)
	{
		ASSERT(0);
		return;
	}

	pSession->setSessionType(serverCfg->getSessType());
	pSession->serivceid = packet->serivceID;
	pSession->serverid = packet->serverID;
	zServerRegMgr& regMgr = GameService::getMe().getServerRegMgr();
	zServerReg* addReg = regMgr.CreateObj();
	if (addReg)
	{
		S::SSRtLogined sendLg;
		addReg->id = packet->serverID;
		addReg->sessid = pSession->id;
		if (!regMgr.add(addReg))
		{
			H::logger->error("注册服务器ID重复");
			ASSERT(0);
			regMgr.DestroyObj(addReg);
			sendLg.result = S::SSRtLogined::SUCCESS;
			pSession->sendMsg(&sendLg, sizeof(sendLg));
			return;
		}
		else
		{
			sendLg.result = S::SSRtLogined::SUCCESS;
			pSession->sendMsg(&sendLg, sizeof(sendLg));
		}

		if (serverCfg->recvsrvlist)
		{
			struct MyStruct : public execEntry<zServerReg>
			{
				virtual bool exec(zServerReg* entry)
				{
					const zSerivceCfgMgr::Server* serverCfg = GameService::getMe().getServerCfgMgr().getServer(entry->id);
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

			BUFFER_CMD(S::SSServerRegList, send, MAX_USERDATASIZE);
			send->count = 0;
			std::vector<int32>::const_iterator it = exec.outServerID.begin();
			for (; it != exec.outServerID.end(); ++it)
			{
				send->reglist[send->count].id = *it;
				send->count++;
			}
			pSession->sendMsg(send, send->getSize());

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
					const zSerivceCfgMgr::Server* serverCfg = GameService::getMe().getServerCfgMgr().getServer(entry->id);
					if (!serverCfg)
					{
						ASSERT(0);
						return true;
					}

					if (serverCfg->recvsrvlist)
					{
						zSession* session = GameService::getMe().getSessionMgr().get(entry->sessid);
						if (session)
						{
							BUFFER_CMD(S::SSServerRegList, send, MAX_USERDATASIZE);
							send->count = 0;
							send->reglist[send->count].id = addServerID;
							send->count++;
							session->sendMsg(send, send->getSize());
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
	const S::SSRtLogined* packet = static_cast<const S::SSRtLogined*>(pMsg);
	if (packet->result == S::SSRtLogined::SUCCESS)
	{
		H::logger->error("登录成功");
	}
	else
	{
		H::logger->error("登录失败");
		ASSERT(0);
	}
}

void NetMsgHandler::recvPingRequest(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void NetMsgHandler::recvSrvListNotifty(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSServerRegList* packet = static_cast<const S::SSServerRegList*>(pMsg);

	// to connect
	for (int32 i = 0; i < packet->count; ++i)
	{
		int32 serverID = packet->reglist[i].id;
		const zSerivceCfgMgr::Server* serverCfg = GameService::getMe().getServerCfgMgr().getServer(serverID);
		if (serverCfg == NULL)
		{
			H::logger->error("本地找不到该服务器配置ID:%d",serverID);
			continue;
		}

		std::map<int32, zSerivceCfgMgr::Serivce>::const_iterator it = serverCfg->serivces.begin();
		for (; it != serverCfg->serivces.end();++it)
		{
			const zSerivceCfgMgr::Serivce& info = it->second;
			if (stricmp(info.name.c_str(), "server") == 0 && stricmp(info.fun.c_str(), "forss") == 0)
			{
				zSession* session = GameService::getMe().getSessionMgr().connect(info.id, info.ip.c_str(), info.port,
					boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
					boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
					boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
				);
				if (!session)
				{
					H::logger->error("Connect Server Fail!");
					ASSERT(0);
					continue;
				}
				session->setSessionType(serverCfg->getSessType());
				session->setServerID(serverID);
			}
		}
	}
}


