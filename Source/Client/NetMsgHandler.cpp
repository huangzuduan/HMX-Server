#include "Client_PCH.h"

NetMsgHandler::NetMsgHandler()
{
	/* common 需要用到内部协议 */
	/* 内部协议，即不分不同servertype，都去做统一的事情，如登录，返回列表，ping等等操作 */
#define REGISTER_INTERNAL_MESSAGE(msg_idx,cls,handler) \
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&NetMsgHandler::handler, this, _1, _2, _3)); \
	}

	REGISTER_INTERNAL_MESSAGE(S::SS_RQ_LOGIN, S::SSRqLogin, recvLoginRequest);
	REGISTER_INTERNAL_MESSAGE(S::SS_RT_LOGINED, S::SSRtLogined, recvLoginReponse);

#undef REGISTER_INTERNAL_MESSAGE

	// from server
#define REGISTER_FEP_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&PlayerProcHandler::handler, PlayerProcHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_FEP_MESSAGE(C::RT_ENCRYPT_INFO, C::RtEncryptInfo, RecvEncryptInfo);
	REGISTER_FEP_MESSAGE(C::RT_LOGIN_READY_FINISH, C::RtLoginReadyFinish, RecvLoginReadyFinish);
	REGISTER_FEP_MESSAGE(C::RT_ENTER_SCENE_LOADED, C::RtEnterSceneLoaded, RecvEnterScene);
	REGISTER_FEP_MESSAGE(C::RT_ACC_LOGIN, C::RtAccLogin, RecvLoginAccountResult);
	REGISTER_FEP_MESSAGE(C::RT_CHAR_WORLD, C::RtCharWorld, RecvChatWorld);
	//REGISTER_FEP_MESSAGE(C::RT_SCENE_INIT_RESULT, C::S::SSRtLogined, RecvSceneInitResult);
	REGISTER_FEP_MESSAGE(C::RT_USERLIST_LOGIN, C::RtUserListLogon, RecvCharacterList);
	REGISTER_FEP_MESSAGE(C::RT_CREATE_RET, C::RtCreateRet, RecvRoleCreateResult);
	REGISTER_FEP_MESSAGE(C::RT_CHAR_MAIN_DATA, C::RtCharMainData, RecvCharacterMainData);
	REGISTER_FEP_MESSAGE(C::RT_QUEST_MAIN_DATA, C::RtQuestMainData, RecvQuestMainData);
	REGISTER_FEP_MESSAGE(C::RT_SEND_DATA_FINISH, C::RtSendDataFinish, RecvSendDataFinish);
	REGISTER_FEP_MESSAGE(C::RT_SCENE_LOAD_INFO, C::RtSceneLoadInfo, RecvEnterSceneInfo);
	REGISTER_FEP_MESSAGE(C::RT_NAMES_LIST, C::RtNamesList, RecvRandNames);
	REGISTER_FEP_MESSAGE(C::RT_CHANNEL_JION, C::RtChannelJion, RecvChannelJion);
	REGISTER_FEP_MESSAGE(C::RT_CHANNEL_LEAVE, C::RtChannelLeave, RecvChannelLeave);
	REGISTER_FEP_MESSAGE(C::RT_RELATION_LIST, C::RtRelationList, RecvRelationList);
	REGISTER_FEP_MESSAGE(C::RT_RELATION_UPDATE, C::RtRelationUpdate, RecvRelationUpdate);
	REGISTER_FEP_MESSAGE(C::RT_RELATION_DELETE, C::RtRelationDelete, RecvRelationDelete);
	REGISTER_FEP_MESSAGE(C::RT_ITEM_MAIN_DATA, C::RtUserPackages, RecvUserPackages);

#undef REGISTER_FEP_MESSAGE

}


NetMsgHandler::~NetMsgHandler()
{
}


void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	H::logger->info("连接成功！来自于:id=%d ip=%s,port=%d", rSocket.SID(), rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
	zSession* pSession = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (pSession)
	{
		if (pSession->serverType == zSession::SERVER_TYPE_CLIENT && pSession->sessionType == zSession::FOR_NULL)
		{
			Player* player = PlayerMgr::getMe().get(pSession->id);
			if (player)
			{
				PlayerProcHandler::SendEncrypt(player);
				H::logger->info("发送请求密钥信息到:ip=%s port=%d", rSocket.GetIp().c_str(), (int32)rSocket.GetPort());
			}
		}
	}
	else
	{
		ASSERT(0);
	}
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32 nSize)
{
	zSession* pSession = GameService::getMe().getSessionMgr().get(rSocket.SLongID());
	if (pSession == NULL)
	{
		H::logger->error("Can not find session");
		rSocket.OnEventColse();
		return;
	}

	// 解密处理 
	static char msgEnBuffer[65536];
	static char msgUnBuffer[65536];

	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	memcpy(&msgEnBuffer[0], pMsg, nSize);

	zEncrypt::xorCode(nSize, pSession->encrypt, msgEnBuffer, nSize);

	// 组装为NetMsgSS头协议，中间补两种头协议的字节差 
	memcpy(&msgUnBuffer[0], msgEnBuffer, nCHeadSize);
	memset(&msgUnBuffer[nCHeadSize], 0, nSHeadSize - nCHeadSize);
	memcpy(&msgUnBuffer[nSHeadSize], &msgEnBuffer[nCHeadSize], nSize - nCHeadSize);

	pMsg = (NetMsgSS*)&msgUnBuffer[0];

	const MsgFunc* pMsgHandlerInfo = GetMsgHandler(pMsg->protocol);
	if (pMsgHandlerInfo == NULL)
	{
		H::logger->error("找不到该协议:%d,大小:%d", pMsg->protocol, nSize);
		rSocket.OnEventColse();
		return;
	}

	H::logger->info("收到协议=%d", pMsg->protocol);

	(pMsgHandlerInfo->handlerFun)((zSession*)(pSession), pMsg, nSize);

	

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
				MyStruct(int32 serverID) :addServerID(serverID)
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










