#include "GatewayServer_PCH.h"
#include "ProcSsHandler.h"

ProcSsHandler::ProcSsHandler()
{
}

ProcSsHandler::~ProcSsHandler()
{
}

void ProcSsHandler::NtSyncUserScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSNtSyncUserScene* packet = static_cast<const S::SSNtSyncUserScene*>(pMsg);
	GateUser* gateUser = GateUserManager::getMe().get(packet->uid);
	if (gateUser)
	{
		gateUser->sceneServerid = pSession->serverid;
	}

	zSession* playerSession = GameService::getMe().getSessionMgr().get(packet->sessid);
	if (playerSession)
	{
		playerSession->status = E_CLIENT_STATUS_IN_SCENE;
	}
}

void ProcSsHandler::NtSyncUserData(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSNtSyncUserData* packet = static_cast<const S::SSNtSyncUserData*>(pMsg);
	GateUser* gateUser = GateUserManager::getMe().get(packet->base.uid);
	if (!gateUser)
	{
		gateUser = GateUserManager::getMe().CreateObj();
		strncpy(gateUser->name, packet->base.name, MAX_NAMESIZE);
		if (!GateUserManager::getMe().add(gateUser))
		{
			H::logger->info("创建网关用户[%s]失败!", zUtility::Utf8ToGBK(packet->base.name));
			GateUserManager::getMe().DestoryObj(gateUser);
			return;
		}
		memcpy(&gateUser->base, &packet->base, sizeof(gateUser->base));
		H::logger->info("创建网关用户[%s]成功!", zUtility::Utf8ToGBK(gateUser->name));
	}
	else
	{
		memcpy(&gateUser->base, &packet->base, sizeof(gateUser->base));
		H::logger->info("更新网关用户[%s]成功!", zUtility::Utf8ToGBK(gateUser->name));
	}

}


void ProcSsHandler::TurnChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSRqChatToOne* cmd = static_cast<const S::SSRqChatToOne*>(pMsg);

}

void ProcSsHandler::NtBroadcastMsg(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S::SSNtBoradCastMsg* packet = static_cast<const S::SSNtBoradCastMsg*>(pMsg);

	// 广播某条协议 
	struct SendToAllPlayer : public execEntry<zSession>
	{
		SendToAllPlayer(const S::SSNtBoradCastMsg* _packet):packet(_packet)
		{

		}
		virtual bool exec(zSession* entry)
		{
			if (entry->sessionType == zSession::FOR_PLAYER)
			{
				PlayerMsgHandler::Instance()->SendToPlayer(entry,(const NetMsgSS*)packet->data,packet->size);
			}
			return true;
		}
		const S::SSNtBoradCastMsg* packet;
	};

	SendToAllPlayer castExec(packet);

	GameService::getMe().getSessionMgr().execEveryConn(castExec);

}



