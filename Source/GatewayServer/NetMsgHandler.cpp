#include "NetMsgHandler.h"
#include "PlayerMsgHandler.h"
#include "ProcLsHandler.h"
#include "ProcSsHandler.h"
#include "GameService.h"
#include "WebMsgHandler.h"

NetMsgHandler::NetMsgHandler() :zMsgHandler(GameService::Instance())
{
		// ls
#define REGISTER_LS_MESSAGE(msg_idx,cls,handler)\
	{\
	RegisterMessage(msg_idx, sizeof(cls), boost::bind(&ProcLsHandler::handler, ProcLsHandler::Instance(), _1, _2, _3)); \
	}

//	REGISTER_LS_MESSAGE(PRO_L2W_LOADLIST, L2WLoadList, RqLoadList);

#undef REGISTER_LS_MESSAGE

	// ss
#define REGISTER_SS_MESSAGE(cmd,cmdType,cls,handler)\
	{\
	RegisterMessage(cmd,cmdType, sizeof(cls), boost::bind(&ProcSsHandler::handler, ProcSsHandler::Instance(), _1, _2, _3)); \
	}

	REGISTER_SS_MESSAGE(::comdef::msg_ss, ::msg_maj::UpdateFepUserID, PbMsgWebSS, UpdateUserToGate);

	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::start_robot_req, PbMsgWebSS, onStartRobotReq);
	REGISTER_SS_MESSAGE(::comdef::msg_room, ::msg_maj::stop_robot_req, PbMsgWebSS, onStopRobotReq);

	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::robot_reconnect_resp, PbMsgWebSS, RobotReconnResp);
	REGISTER_SS_MESSAGE(::comdef::msg_maj, ::msg_maj::robot_start_round_resp, PbMsgWebSS, RobotStartRoundResp);
	
	
#undef REGISTER_SS_MESSAGE

	// send to player
#define REGISTER_SEND_TO_PLAYER_MESSAGE(cmd,cmdType,cls)\
	{\
	RegisterMessage(cmd,cmdType, sizeof(cls), boost::bind(&WebMsgHandler::SendToPlayer, WebMsgHandler::Instance(), _1, _2, _3)); \
	}

	// login
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_login, ::msg_maj::login_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_login, ::msg_maj::prelogin_account_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_login, ::msg_maj::kictout_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_login, ::msg_maj::login_player_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_login, ::msg_maj::sdk_token_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_login, ::msg_maj::notify_another_login, PbMsgWebSS);

	// role
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_role, ::msg_maj::setting_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_role, ::msg_maj::set_logo_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_role, ::msg_maj::get_title_list_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_role, ::msg_maj::set_title_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_role, ::msg_maj::player_info_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_role, ::msg_maj::update_role_data, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_role, ::msg_maj::cardinfo_req, PbMsgWebSS);

	// room
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::room_list_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::open_room_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::enter_room_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::role_enter_room, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::role_leave_room, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::dismiss_room_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::dismiss_room_vote_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::room_ready_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::room_reconnect_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::role_online_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::kick_role_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::dismiss_room_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::roomcard_price_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::sync_room_role_info, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::sync_romm_inn_info, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::notify_room_dismiss, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_room, ::msg_maj::leave_room_resp, PbMsgWebSS);

	//-----maj---------
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::start_round_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::discard_tile_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::deal_tile_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::response_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::game_result_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::total_result_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::reconnect_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::ask_start_game, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::accept_start_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::prepare_round_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::reconnect_sync_card, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::sync_player_status, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::quickmessage_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::notify_player_event, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::notify_ghostpai_result, PbMsgWebSS);
	
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::ask_start_sanzhang, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::huan_sanzhang_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::ask_start_dingque, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::dingque_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::hu_pailist_notify, PbMsgWebSS);

	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::ting_pai_discard_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::ting_pai_waite_notify, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::my_scorelist_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_maj, ::msg_maj::my_ting_pai_resp, PbMsgWebSS);

	// rank
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_rank, ::msg_maj::rank_resp, PbMsgWebSS);

	// gm
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_gm, ::msg_maj::remaining_card_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_gm, ::msg_maj::assign_all_cards_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_gm, ::msg_maj::assign_next_card_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_gm, ::msg_maj::gm_common_oper_resp, PbMsgWebSS);

	// event
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_event, ::msg_event::resp_invite_game, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_event, ::msg_event::notice_list_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_event, ::msg_event::mail_list_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_event, ::msg_event::mail_opt_resp, PbMsgWebSS);

	// hist
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_hist, ::msg_maj::history_list_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_hist, ::msg_maj::history_room_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_hist, ::msg_maj::history_inn_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_hist, ::msg_maj::replay_resp, PbMsgWebSS);

	// activity
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::get_share_info_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::share_Report_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::Recv_share_reward_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::get_invitation_info_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::Recv_invitation_reward_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::get_binding_agent_info_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::binding_agent_resp, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::Sync_activity_info, PbMsgWebSS);
	REGISTER_SEND_TO_PLAYER_MESSAGE(::comdef::msg_activity, ::msg_maj::input_invitation_code_resp, PbMsgWebSS);

#undef REGISTER_SEND_TO_PLAYER_MESSAGE

}


NetMsgHandler::~NetMsgHandler()
{ 
}

void NetMsgHandler::OnNetMsgEnter(NetSocket& rSocket)
{
	CommonOnNetMsgEnter(rSocket);
}

void NetMsgHandler::OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32_t nSize)
{
	CommonOnNetMsg(rSocket, pMsg, nSize);
}

void NetMsgHandler::OnNetMsgExit(NetSocket& rSocket)
{
	CommonOnNetMsgExit(rSocket);
}

void NetMsgHandler::sendSToPlayer(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	zSession* player = GameService::getMe().SessionMgr()->get(pMsg->clientSessID);
	if (!player)
	{
		ASSERT(player);
		H::logger->error("sessid不正确，找不到玩家session");
		return;
	}

	static char arrUnBuffer[65536];
	static char arrEnBuffer[65536];
	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	int nCSize = nSize - (nSHeadSize - nCHeadSize);
	memcpy(&arrUnBuffer[0], pMsg, nSize);
	memcpy(&arrEnBuffer[0], &arrUnBuffer[0], nCHeadSize);
	memcpy(&arrEnBuffer[nCHeadSize], &arrUnBuffer[nSHeadSize], nSize - nSHeadSize);
	zEncrypt::xorCode(nCSize, player->encrypt, arrEnBuffer, nCSize);
	player->socket->ParkMsg((uint8_t*)&arrEnBuffer[0], nCSize);
}



