#include "ProcDpHandler.h"
#include "SceneUser.h"
#include "SceneUserMgr.h"
#include "GameService.h"
#include "CWorld.hpp"
#include "CMail.hpp"
#include "CMailMgr.hpp"
#include "CPlayer.hpp"
#include "CNotice.hpp"
#include "CNoticeMgr.hpp"
#include "CRoom.hpp"
#include "CRoomMgr.hpp"

ProcDpHandler::ProcDpHandler()
{

}

ProcDpHandler::~ProcDpHandler()
{

}

void ProcDpHandler::HandleQueryPlayerResponse(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::QueryPlayerResponse proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);

	if (proto.result() == 1)
	{
		::msg_maj::LoginPlayerResp proLogin;
		proLogin.set_code(::msg_maj::FAIL);
		proLogin.set_srv_time(time(NULL));
		zSession* pFep = GameService::Instance()->SessionMgr()->getFep(pMsg->fepServerID);
		if (pFep)
		{
			pFep->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_resp, proLogin);
		}
		return;
	}

	CPlayer* pPlayer = CWorld::Instance()->LoadPlayer(pMsg->clientSessID, pMsg->fepServerID, proto.role_info());
	if (pPlayer)
	{
		if (pPlayer->IsRobot())
		{
			pPlayer->StartRobot();
		}

		// Í¨ÖªÍø¹Ø
		pPlayer->UpdateToGate();
		pPlayer->EnterGame();
		pPlayer->SaveDataToDB(0);
		if (proto.room_id() > 0 )
		{
			pPlayer->JoinRoom(proto.room_id());
		}
	}
}

void ProcDpHandler::HandleQueryMailResponse(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::QueryMailResponse proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CMailMgr::Instance()->UnSerialize(proto);
}

void ProcDpHandler::HandleQueryMailSysLogResponse(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::QueryMailSystemLogResponse proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CMailSysLogMgr::Instance()->UnSerialize(proto);
}

void ProcDpHandler::HandleGetMaxUUIDResponse(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::GetMaxUUIDResponse proRep;
	proRep.ParseFromArray(pMsg->data, pMsg->size);
}

void ProcDpHandler::HandleSessionAccountName(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::SessionAccountName proData;
	proData.ParseFromArray(pMsg->data, pMsg->size);
	CWorld::Instance()->AddSessionAccountName(proData.user_id(), proData.account(), proData.name(), proData.icon_addr());
}

void ProcDpHandler::HandleUpdateRoomInfo(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::UpdateRoomInfo proData;
	proData.ParseFromArray(pMsg->data, pMsg->size);
	//DUMP_PROTO_MSG(proData);

	switch (proData.room_starus())
	{
	case fogs::proto::msg::RoomStatus_Open:
	{
		CWorld::Instance()->AddRoomInfo(proData.room_id(), proData.server_id());
		break;
	}
	case fogs::proto::msg::RoomStatus_Close:
	{
		CWorld::Instance()->DelRoomInfo(proData.room_id());
		break;
	}
	default:
		break;
	}
}

void ProcDpHandler::HandlerZhanjiQueryResp(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::ZhanjiQueryResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CPlayer* pPlayer = CWorld::Instance()->GetPlayerByUUID(proto.char_id());
	if (pPlayer == NULL)
	{
		return;
	}
	pPlayer->SendMsgToClient(::comdef::msg_hist, ::msg_maj::history_list_resp, proto.resp());
}

void ProcDpHandler::HandlerZhanjiRoomResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::ZhanjiQueryRoomResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CPlayer* pPlayer = CWorld::Instance()->GetPlayerByUUID(proto.char_id());
	if (pPlayer == NULL)
	{
		return;
	}
	pPlayer->SendMsgToClient(::comdef::msg_hist, ::msg_maj::history_room_resp, proto.resp());
}

void ProcDpHandler::HandlerZhanjiReplyResp(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	fogs::proto::msg::ZhanjiRespReply proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CPlayer* pPlayer = CWorld::Instance()->GetPlayerByUUID(proto.char_id());
	if (pPlayer == NULL)
	{
		return;
	}
	pPlayer->SendMsgToClient(::comdef::msg_hist, ::msg_maj::replay_resp, proto.resp());
}

void ProcDpHandler::HandleFreeConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::GetFreeConfigResp proResp;
	proResp.ParseFromArray(pMsg->data, pMsg->size);
	CWorld::Instance()->SetFreeConfig(proResp);
}

void ProcDpHandler::HandleRewardConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::GetRewardConfigResp proResp;
	proResp.ParseFromArray(pMsg->data, pMsg->size);
	CWorld::Instance()->SetInvitationRewardConfig(proResp.invitation_reward());
	CWorld::Instance()->SetShareRewardConfig(proResp.share_reward());
}

void ProcDpHandler::HandleNotifyConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::GetNotifyConfigResp proResp;
	proResp.ParseFromArray(pMsg->data, pMsg->size);
	CWorld::Instance()->SetNotifyConfig(proResp);
}

void ProcDpHandler::HandleRoomSetConfigResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	fogs::proto::msg::GetRoomSetConfigResp proResp;
	proResp.ParseFromArray(pMsg->data, pMsg->size);
	CWorld::Instance()->SetRoomSetConfig(proResp);
}


