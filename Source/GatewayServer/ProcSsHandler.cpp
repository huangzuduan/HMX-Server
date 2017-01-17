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
	const S2FSyncUserScene* packet = static_cast<const S2FSyncUserScene*>(pMsg);
	GateUser* gateUser = GateUserManager::getMe().get(packet->uid);
	if (gateUser)
	{
		gateUser->sceneServerid = pSession->serverid;
	}

	zSession* playerSession = NetService::getMe().getSessionMgr().get(packet->sessid);
	if (playerSession)
	{
		playerSession->status = E_CLIENT_STATUS_IN_SCENE;
	}
}

void ProcSsHandler::NtSyncUserData(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S2FSyncUserData* packet = static_cast<const S2FSyncUserData*>(pMsg);
	GateUser* gateUser = GateUserManager::getMe().get(packet->uid);
	if (!gateUser)
	{
		gateUser = GateUserManager::getMe().CreateObj();
		gateUser->id = packet->uid;
		gateUser->tempid = packet->sessid;
		strncpy(gateUser->name, packet->name, MAX_NAMESIZE);
		if (!GateUserManager::getMe().add(gateUser))
		{
			Zebra::logger->info("创建网关用户[%s]失败!", Utf8ToGBK(packet->name));
			GateUserManager::getMe().DestoryObj(gateUser);
			return;
		}
		memcpy(&gateUser->base, &packet->base, sizeof(gateUser->base));
		Zebra::logger->info("创建网关用户[%s]成功!", Utf8ToGBK(gateUser->name));
	}
	else
	{
		memcpy(&gateUser->base, &packet->base, sizeof(gateUser->base));
		Zebra::logger->info("更新网关用户[%s]成功!", Utf8ToGBK(gateUser->name));
	}

}


void ProcSsHandler::TurnChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S2WChatToOne* cmd = static_cast<const S2WChatToOne*>(pMsg);

}

void ProcSsHandler::NtBroadcastMsg(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S2FBoradCastMsg* packet = static_cast<const S2FBoradCastMsg*>(pMsg);

	// 广播某条协议 
	struct SendToAllPlayer : public execEntry<zSession>
	{
		SendToAllPlayer(const S2FBoradCastMsg* _packet):packet(_packet)
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
		const S2FBoradCastMsg* packet;
	};

	SendToAllPlayer castExec(packet);

	NetService::getMe().getSessionMgr().execEveryConn(castExec);

}



