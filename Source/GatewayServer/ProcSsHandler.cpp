#include "ProcSsHandler.h"
#include "PlayerMsgHandler.h"
#include "GameService.h"
#include "GateUser.h"
#include "CRobotMgr.hpp"
#include "CMsgConn.hpp"

ProcSsHandler::ProcSsHandler()
{
}

ProcSsHandler::~ProcSsHandler()
{
}

void ProcSsHandler::onStartRobotReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	H::logger->error("[网页玩家]启动机器人替打:%lld", pMsg->clientSessID);
	::msg_maj::StartRobotReq proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobotMgr::Instance()->StartNewRobot(pSession,proto.session_id(),proto.uid());
}

void ProcSsHandler::onStopRobotReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	H::logger->error("[网页玩家]结束机器人替打,clientSessID:%lld", pMsg->clientSessID);
	::msg_maj::StopRobotReq proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobotMgr::Instance()->StopRebot(proto.uid());
}

void ProcSsHandler::RobotReconnResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	H::logger->error("[网页玩家]机器人获得分析当前的牌,clientSessID:%lld", pMsg->clientSessID);
	CMsgConn::getMe().HandleMsg(pMsg);
}

void ProcSsHandler::RobotStartRoundResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	H::logger->error("[网页玩家]机器人获得当前的牌数据,clientSessID:%lld", pMsg->clientSessID);
	CMsgConn::getMe().HandleMsg(pMsg);
}

void ProcSsHandler::TurnChatToOne(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	//const S::SSRqChatToOne* cmd = static_cast<const S::SSRqChatToOne*>(pMsg);

}

void ProcSsHandler::NtBroadcastMsg(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	//const S::SSNtBoradCastMsg* packet = static_cast<const S::SSNtBoradCastMsg*>(pMsg);

	// 广播某条协议 
	//struct SendToAllPlayer : public execEntry<zSession>
	//{
	//	SendToAllPlayer(const S::SSNtBoradCastMsg* _packet):packet(_packet)
	//	{

	//	}
	//	virtual bool exec(zSession* entry)
	//	{
	//		if (entry->GetServerType() == 0)
	//		{
	//			PlayerMsgHandler::Instance()->SendToPlayer(entry,(const NetMsgSS*)packet->data,packet->size);
	//		}
	//		return true;
	//	}
	//	const S::SSNtBoradCastMsg* packet;
	//};

	//SendToAllPlayer castExec(packet);

	//GameService::getMe().SessionMgr()->execEveryConn(castExec);

}

void ProcSsHandler::UpdateUserToGate(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::msg_maj::RoleFep proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	GateUser* gateUser = GateUserManager::getMe().get(proto.id());
	if (gateUser == NULL)
	{
		
	}
	else
	{
		GateUserManager::getMe().remove(gateUser);
		//todo对老的session进行下线删除
	}

	GateUserManager::getMe().add(proto);

}



