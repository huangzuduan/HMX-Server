#include "WebMsgHandler.h"
#include "PlayerMsgHandler.h"
#include "GameService.h"
#include "GateScene.h"
#include "GateUser.h"
#include "CRobot.hpp"
#include "CRobotMgr.hpp"
#include "CMsgConn.hpp"

// 在 fep 中 ，client的sessionID为socketID

WebMsgHandler::WebMsgHandler() :zMsgHandler(GameService::Instance())
{
	// to local
#define REGISTER_LOCAL_MESSAGE(cmd,cmdType,cls)\
	{\
	RegisterMessage(cmd,cmdType,sizeof(cls),boost::bind(&WebMsgHandler::ReqSendLocalServer, this, _1, _2,_3));\
	}

	//-----base--------
	REGISTER_LOCAL_MESSAGE(::comdef::msg_base, ::msg_base::heartbeat_req, PbMsgWebSS);
	REGISTER_LOCAL_MESSAGE(::comdef::msg_base, ::msg_base::heartbeat_resp, PbMsgWebSS);
	REGISTER_LOCAL_MESSAGE(::comdef::msg_base, ::msg_base::time_req, PbMsgWebSS);

#undef REGISTER_LOCAL_MESSAGE

	// to ls
#define REGISTER_LS_MESSAGE(cmd,cmdType,cls)\
	{\
	RegisterMessage(cmd,cmdType,sizeof(cls),boost::bind(&WebMsgHandler::ReqSendToLoginServer, this, _1, _2,_3));\
	}

	//-----login-------
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::login_weixin_req, PbMsgWebSS);
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::login_account_req, PbMsgWebSS);
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::prelogin_account_req, PbMsgWebSS);
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::sdk_token_req, PbMsgWebSS);
	
#undef REGISTER_LS_MESSAGE

	// to ws
#define REGISTER_WS_MESSAGE(cmd,cmdType,cls)\
	{\
		RegisterMessage(cmd,cmdType,sizeof(cls), boost::bind(&WebMsgHandler::ReqSendToWorldServer,this, _1, _2,_3)); \
	}

	REGISTER_WS_MESSAGE(::comdef::msg_login, ::msg_maj::logout_req, PbMsgWebSS);
	REGISTER_WS_MESSAGE(::comdef::msg_login, ::msg_maj::login_player_req, PbMsgWebSS);

#undef REGISTER_WS_MESSAGE

	// to ss
#define REGISTER_SS_MESSAGE(cmd,cmdType,cls)\
	{\
		RegisterMessage(cmd,cmdType, sizeof(cls), boost::bind(&WebMsgHandler::ReqSendToSceneServer, this, _1, _2,_3)); \
	}

	//-----role--------
	REGISTER_SS_MESSAGE(::comdef::msg_role, ::msg_maj::player_info_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_role, ::msg_maj::gps_upload_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_role, ::msg_maj::update_role_req,PbMsgWebSS);

	//-----room--------
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::room_list_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::open_room_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::enter_room_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::leave_room_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::dismiss_room_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::room_reconnect_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::dismiss_room_vote_accept, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::kick_role_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::enter_room_ready, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::roomcard_price_req, PbMsgWebSS);

	//-----maj---------
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::start_game_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::accept_start_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::disover_card_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::discard_tile_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::prepare_round_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::response_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::reconnect_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::reconnect_ready_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::reconnect_other_ready_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::quickmessage_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::huan_sanzhang_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::dingque_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::my_scorelist_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::my_ting_pai_req, PbMsgWebSS);

	//-----rank-------
	REGISTER_SS_MESSAGE(::comdef::msg_rank, ::msg_maj::rank_req, PbMsgWebSS);

	//-------gm--------
	REGISTER_SS_MESSAGE(::comdef::msg_gm, ::msg_maj::remaining_card_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_gm, ::msg_maj::assign_all_cards_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_gm, ::msg_maj::assign_next_card_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_gm, ::msg_maj::gm_common_oper_req, PbMsgWebSS);

	//-------event--------
	REGISTER_SS_MESSAGE(::comdef::msg_event, ::msg_event::mail_list_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_event, ::msg_event::mail_opt_req, PbMsgWebSS);

	//-------hist--------
	REGISTER_SS_MESSAGE(::comdef::msg_hist, ::msg_maj::history_list_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_hist, ::msg_maj::replay_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_hist, ::msg_maj::history_room_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_hist, ::msg_maj::history_inn_req, PbMsgWebSS);

	//-------activity----
	REGISTER_SS_MESSAGE(::comdef::msg_activity, ::msg_maj::get_share_info_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_activity, ::msg_maj::share_Report_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_activity, ::msg_maj::Recv_share_reward_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_activity, ::msg_maj::get_invitation_info_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_activity, ::msg_maj::Recv_invitation_reward_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_activity, ::msg_maj::get_binding_agent_info_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_activity, ::msg_maj::binding_agent_req, PbMsgWebSS);
	REGISTER_SS_MESSAGE(::comdef::msg_activity, ::msg_maj::input_invitation_code_req, PbMsgWebSS);

#undef REGISTER_SS_MESSAGE

}


WebMsgHandler::~WebMsgHandler()
{
}

void WebMsgHandler::OnWebMsgEnter(CWebClient* client)
{
	H::logger->info("[网页玩家]连接成功！来自于:id=%d ip=%s", client->GetSessionID(), client->GetIP().c_str());
	zSession* pSession = GameService::getMe().PlayerSessMgr()->addWeb(client->GetSessionID(), client);
	if (pSession == NULL)
	{
		client->close();
		return;
	}
}


void WebMsgHandler::OnWebMsg(CWebClient* client, PbMsgWebSS* pMsg,int32_t nSize)
{
	zSession* pSession = GameService::getMe().PlayerSessMgr()->get(client->GetSessionID());
	if(pSession)
	{
		const MsgFunc* handler = GetMsgHandler(pMsg->protocol);
		if(handler == NULL)
		{
			H::logger->error("[网页玩家]找不该协议,cmd:%d,cmdType:%d,大小:%d", pMsg->cmd,pMsg->cmdType,nSize);
			ASSERT(0);
			GameService::getMe().PlayerSessMgr()->remove(pSession);
			client->close();
			return;
		}
		else
		{
			H::logger->info("[网页玩家]收到协议,cmd:%d,cmdType:%d", pMsg->cmd, pMsg->cmdType);
			(handler->handlerFun)(pSession, (PbMsgWebSS*)pMsg ,nSize);
		}
	}
	else
	{
		H::logger->error("[网页玩家]找不到该连接:%lld", client->GetSessionID());
		GameService::getMe().PlayerSessMgr()->remove(pSession);
		client->close();
	}
}

void WebMsgHandler::OnWebMsgExit(CWebClient* client)
{
	zSession* pSession = GameService::getMe().PlayerSessMgr()->get(client->GetSessionID());
	if (pSession)
	{
		GameService::getMe().PlayerSessMgr()->remove(pSession);

		// 发送到ss
		GateUser* gateUser = GateUserManager::getMe().getBySessID(pSession->GetID());
		if (gateUser)
		{
			zSession* pSs = GameService::getMe().SessionMgr()->getSs(gateUser->GetSceneServerID());
			if (pSs)
			{
				::msg_maj::NotifyPlayerExit sendExit;
				pSs->sendMsgProto(::comdef::msg_login, ::msg_maj::notify_dis_conntion, pSession->GetID(), GameService::getMe().GetServerID(), sendExit);
			}
			GateUserManager::getMe().remove(gateUser);
		}

		// 发送到ws
		zSession* pWs = GameService::getMe().SessionMgr()->getWs();
		if (pWs)
		{
			::msg_maj::NotifyPlayerExit sendExit;
			pWs->sendMsgProto(::comdef::msg_login, ::msg_maj::notify_dis_conntion, pSession->GetID(), GameService::getMe().GetServerID(), sendExit);
		}

		return;
	}	
	H::logger->error("[网页玩家]连接断开:%d,IP:%s", client->GetSessionID(), client->GetIP().c_str());
}

void WebMsgHandler::ReqSendLocalServer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	switch (pMsg->cmdType)
	{
	case ::msg_base::heartbeat_req:
	{
		break;
	}
	case ::msg_base::heartbeat_resp:
	{
		break;
	}
	case ::msg_base::time_req:
	{
		break;
	}
	default:
		break;

	}
}

// 发送到 ls 
void WebMsgHandler::ReqSendToLoginServer(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	zSession* pLs = GameService::getMe().SessionMgr()->getLs();
	if (pLs == NULL)
	{
		H::logger->warn("[网页玩家]无法转发到LS,找不到LS Session");
		return;
	}
	MSG_MAKE_PLAYER_SESSID(pSession->GetID(),GameService::getMe().GetServerID(),pMsg,nSize);
	pLs->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

// 发送到 ss
void WebMsgHandler::ReqSendToSceneServer(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	GateUser* gateUser = GateUserManager::getMe().getBySessID(pSession->GetID());
	if (gateUser)
	{
		zSession* pSs = GameService::getMe().SessionMgr()->getSs(gateUser->GetSceneServerID());
		if (pSs == NULL)
		{
			H::logger->warn("[网页玩家]无法转发到SS,找不到SS,serverid:%d", gateUser->GetSceneServerID());
			return;
		}
		MSG_MAKE_PLAYER_SESSID(pSession->GetID(), GameService::getMe().GetServerID(), pMsg, nSize);
		pSs->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
	}
	else
	{
		H::logger->warn("[网页玩家]无法转发到SS,找不到SS,session:%lld", pSession->GetID());
		//ASSERT(0);
	}
}

// 发送到 ws
void WebMsgHandler::ReqSendToWorldServer(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	zSession* pWs = GameService::getMe().SessionMgr()->getWs();
	if (!pWs)
	{
		H::logger->warn("[网页玩家]无法转发到WS,找不到WS Session");
		return;
	}
	MSG_MAKE_PLAYER_SESSID(pSession->GetID(), GameService::getMe().GetServerID(), pMsg, nSize);
	pWs->sendMsg((NetMsgSS*)(&vecMsgBuffer[0]), vecMsgBuffer.size());
}

void WebMsgHandler::SendToPlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	if (pMsg->clientSessID >= ROBOT_START_ID && pMsg->clientSessID <= ROBOT_END_ID)
	{
		CRobot* pRobot = CRobotMgr::Instance()->GetRobot((uint32_t)pMsg->clientSessID);
		if (pRobot)
		{
			CMsgConn::Instance()->HandleMsg(pMsg);
		}
		else
		{
			H::logger->error("[机器]无法找到机器人,clientSessID:%lld", pMsg->clientSessID);
			//ASSERT(0);
		}
	}
	else
	{
		zSession* pWebSession = GameService::getMe().PlayerSessMgr()->get(pMsg->clientSessID);
		if (pWebSession)
		{
			pWebSession->sendMsg(pMsg, nSize);
		}
		else
		{
			// 需要过滤一些协议，它可能是不存在这个zSession的
			//pMsg->cmd == ::msg_maj::notify_another_login;
			if (pMsg->cmd == ::comdef::msg_login && pMsg->cmdType == ::msg_maj::notify_another_login)
			{

			}
			else
			{
				H::logger->error("[玩家]无法找到玩家,clientSessID:%lld", pMsg->clientSessID);
				//ASSERT(0);
			}
		}
	}
}




