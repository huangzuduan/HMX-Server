#include "CMsgConn.hpp"
#include "CRobotMgr.hpp"
#include "SrvEngine.h"

CMsgConn::CMsgConn()
{
}

CMsgConn::~CMsgConn()
{
}

void CMsgConn::HandleHandshakeResponse(const PbMsgWebSS* pMsg)
{
	fogs::proto::msg::HandshakeResponse proRep;
	proRep.ParseFromArray(pMsg->data, pMsg->size);
}

void CMsgConn::HandleMsg(const PbMsgWebSS* pMsg)
{
	uint16_t usCmd = pMsg->cmd;
	switch (usCmd)
	{
	case 0: break;
	case ::comdef::msg_login: HandleLoginMsg(pMsg); break;
	case ::comdef::msg_room: HandleRoomMsg(pMsg); break;
	case ::comdef::msg_maj: HandleMajiangMsg(pMsg); break;
	default: break;
	}
}

void CMsgConn::HandleLoginMsg(const PbMsgWebSS* pMsg)
{
	uint16_t usCCmd = pMsg->cmd;
	switch (usCCmd)
	{
	case ::msg_maj::login_player_resp: HandleLoginPlayerResp(pMsg); break;
	default: break;
	}
}

void CMsgConn::HandleLoginPlayerResp(const PbMsgWebSS* pMsg)
{
	::msg_maj::LoginPlayerResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	pRobot->bIsLogin_2 = true;
	pRobot->role.CopyFrom(proto.role());

	CRobotMgr::Instance()->CheckLoginAll();
}

void CMsgConn::HandleCreateRoomResp(const PbMsgWebSS* pMsg)
{
	::msg_maj::OpenRoomResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
		return;

	switch (proto.code())
	{
	case ::msg_maj::OpenRoomResp_error_code_SUCCESS:
	{
		H::logger->info("CMsgConn::HandleLoginPlayerResp() 创建房间成功: %ld",pMsg->clientSessID);

		pRobot->m_nRoomID = proto.info().room_id();
		pRobot->m_usSeat = proto.role().seat_id();
		pRobot->bIsSendCreate_2 = true;

		pRobot->SetActionType(eActionType_EnterReady);
		break;
	}
	case ::msg_maj::OpenRoomResp_error_code_FAIL:
	{
		H::logger->info("CMsgConn::HandleLoginPlayerResp() 创建房间失败1:%ld ",pMsg->clientSessID);
		break;
	}
	case ::msg_maj::OpenRoomResp_error_code_ALREADY_IN:
	{
		pRobot->m_nRoomID = proto.info().room_id();
		break;
	}
	case ::msg_maj::OpenRoomResp_error_code_NO_DIAMOND:
	{
		H::logger->info("CMsgConn::HandleLoginPlayerResp() 创建房间失败2: %ld",pMsg->clientSessID);
		break;
	}
	case ::msg_maj::OpenRoomResp_error_code_ROOMCARD_NOTENOUTH:
	{
		H::logger->info("CMsgConn::HandleLoginPlayerResp() 创建房间失败,房卡不足:%ld ", pMsg->clientSessID);
		break;
	}
	default:
		break;
	}
}

void CMsgConn::HandleEnterRoomResp(const PbMsgWebSS* pMsg)
{
	::msg_maj::EnterRoomResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
		return;

	switch (proto.code())
	{
	case ::msg_maj::EnterRoomResp_msg_room_code_SUCCESS:
	{
		H::logger->info("CMsgConn::HandleLoginPlayerResp() 进入房间成功: %ld", pMsg->clientSessID);

		pRobot->m_nRoomID = proto.info().room_id();
		pRobot->m_usSeat = proto.self_seat();
		pRobot->bIsSendJoin_2 = true;
		int32_t game_type = proto.info().option().game_type();
		int32_t jushutype = proto.info().option().jushutype();
		pRobot->m_uTotalInnCount = jushutype * 8;
		pRobot->SetActionType(eActionType_EnterReady);		
		break;
	}
	case ::msg_maj::EnterRoomResp_msg_room_code_FAIL:
	{
		
		break;
	}
	case ::msg_maj::EnterRoomResp_msg_room_code_ALREADY_IN:
	{
		pRobot->SendLeaveRoom();
		pRobot->bIsSendJoin_1 = false;
		pRobot->bIsSendJoin_2 = false;
		break;
	}
	case ::msg_maj::EnterRoomResp_msg_room_code_PERSONS_FULL:
	{
		H::logger->info("CMsgConn::HandleLoginPlayerResp() 进入房间失败: %ld", pMsg->clientSessID);
		break;
	}
	default:
		break;
	}
}

void CMsgConn::HandleRoomReadyNotify(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	::msg_maj::RoomReadyNotify proResp;
	proResp.ParseFromArray(pMsg->data, pMsg->size);

	switch (proResp.roomer_aciton())
	{
	case ::msg_maj::can_start:
	{
		H::logger->info("收到开始按钮消息...");
		pRobot->SetActionType(eActionType_StartGame);
		break;
	}
	case ::msg_maj::cancel_start:
	{
		H::logger->info("收到取消开始按钮消息...");
		break;
	}
	default:
		break;
	}
}

void CMsgConn::HandleInnRoomInfoNotify(const PbMsgWebSS* pMsg)
{
	::msg_maj::SyncRommInnInfo proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	pRobot->m_uCurrInnID = proto.inn_id();
}

void CMsgConn::HandleSyncRoleInfResp(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	pRobot->bIsSendJoinReady_2 = true;
}

void CMsgConn::HandleAskStartGameResp(const PbMsgWebSS* pMsg)
{
	::msg_maj::AskStartGame proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	H::logger->info("CMsgConn::HandleAskStartGameResp() 准备去接受开始: %ld", pMsg->clientSessID);
	pRobot->bIsStartGame_2 = true;

	pRobot->SetActionType(eActionType_AcceptStart);
}

void CMsgConn::HandleStartRoundResp(const PbMsgWebSS* pMsg)
{
	::msg_maj::StartRoundResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	H::logger->info("%s, 现在是第[%d]局，收到初始发牌信息:%lld",pRobot->GetAccount().c_str(),pRobot->m_uCurrInnID,pMsg->clientSessID);
	pRobot->bIsSendAcceptStart_2 = true;
	pRobot->myPaiData.CopyFrom(proto);
	pRobot->Display();
	pRobot->SendDisoverCard();
}

void CMsgConn::HandleDealTileNotify(const PbMsgWebSS* pMsg)
{
	::msg_maj::DealNotify proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	if (pRobot->m_usSeat == proto.seat())
	{
		////LOG(ERROR) << pRobot->GetAccount() << ", 摸到牌: " << CRobotMgr::Instance()->GetPaiZhong(proto.tile()) << ",剩:" << proto.desk_tile_count() << "张牌";
		pRobot->dealNotify.CopyFrom(proto);
		pRobot->myPaiData.add_tile_list(proto.tile());
		bool doEvent = false;
		//判断事件
		for (int i = 0; i < pRobot->dealNotify.eventlist_size(); ++i)
		{
			::msg_maj::event_type type_t = pRobot->dealNotify.eventlist(i).event_t();
			switch (type_t)
			{
			case msg_maj::zi_mo_hu:
				H::logger->info("%s ,ID:%d, 可以自摸: %s", pRobot->GetAccount().c_str() ,pRobot->GetID32(),CRobotMgr::Instance()->GetPaiZhong(proto.tile()).c_str());
				pRobot->m_usPai = proto.tile();
				pRobot->SetActionType(eActionType_ZiMo);
				pRobot->bIsBanker = true;
				doEvent = true;
				break;
			case msg_maj::dian_pao_hu:
				pRobot->m_usPai = proto.tile();
				pRobot->SetActionType(eActionType_DianPao);
				pRobot->bIsBanker = true;
				doEvent = true;
				break;
			case msg_maj::ming_gang:
				pRobot->m_usPai = proto.tile();
				pRobot->SetActionType(eActionType_MingGang);
				doEvent = true;
				break;
			case msg_maj::an_gang:
				if (proto.eventlist_size() > 0)
				{
					pRobot->m_usPai = proto.eventlist(0).event_pai(0);
				}
				pRobot->SetActionType(eActionType_AnGang);
				doEvent = true;
				break;
			case msg_maj::guo_shou_gang:
				pRobot->m_usPai = proto.tile();
				pRobot->SetActionType(eActionType_GuoShouGang);
				doEvent = true;
				break;
			default:
				break;
			}
			break;
		}

		if (pRobot->dealNotify.eventlist_size() < 1)
		{
			pRobot->m_usPai = 0;
			pRobot->SetActionType(eActionType_Discard);
		}
		else
		{
			if (!doEvent)
			{
				pRobot->m_usPai = 0;
				pRobot->SetActionType(eActionType_Discard);
			}
		}
	}
}

void CMsgConn::HandleDiscardTileResp(const PbMsgWebSS* pMsg)
{
	::msg_maj::DiscardResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	bool bDoEvent = false;
	for (int i = 0; i < proto.eventlist_size(); ++i)
	{
		::msg_maj::event_type type_t = proto.eventlist(i).event_t();
		switch (type_t)
		{
		case msg_maj::dian_pao_hu:
		{
			pRobot->m_usPai = proto.tile();
			pRobot->SetActionType(eActionType_DianPao);
			bDoEvent = true;
			break;
		}	
		case msg_maj::pong:
		{
			if (pRobot->tingPaiDiscardNotify.ting_list_size() > 0)
				pRobot->SetActionType(eActionType_Pass);
			else
			{
				pRobot->m_usPai = proto.tile();
				pRobot->SetActionType(eActionType_Peng);
			}
			bDoEvent = true;
			break;
		}		
		case msg_maj::ming_gang:
		{
			pRobot->m_usPai = proto.tile();
			pRobot->SetActionType(eActionType_MingGang);
			bDoEvent = true;
			break;
		}
		default:
			break;
		}
		break;
	}
	if (proto.eventlist_size() > 0)
	{
		if (!bDoEvent)
		{
			pRobot->RespPassPai(proto.tile());	// 过牌
		}
	}
}

void CMsgConn::HandleGameResultNotify(const PbMsgWebSS* pMsg)
{
	::msg_maj::GameResultNotify proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	pRobot->NextReset();

	if (pRobot->bIsRoomer)
	{
		H::logger->error("%s,ID:, 本局结束: %d", pRobot->GetAccount().c_str(),pRobot->GetID32());
		for (int i = 0; i < proto.seats_size(); ++i)
		{
			const ::msg_maj::GameResultSeat& seatResult =  proto.seats(i);
			H::logger->error("结算,座位:%d 得分: %d" , seatResult.seat(),seatResult.total_score());
		}
	}

	// 判断是否还有下一场
	if (pRobot->m_uCurrInnID < pRobot->m_uTotalInnCount)
	{
		pRobot->SetActionType(eActionType_RoundPrepare);
	}
	else 
	{
		if (pRobot->m_uCurrInnID == pRobot->m_uTotalInnCount) // 正常局数
		{
			pRobot->SendLeaveRoom();// 离开房间
		}
		else // 提前解散，先准备，后解散
		{
			if (!pRobot->bIsDismiss && pRobot->bIsRoomer)
			{
				pRobot->bIsDismiss = true;
				pRobot->SendDismissRoomReq();
			}
		}
	}
}

void CMsgConn::HandleTotalResultNotify(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	::msg_maj::TotalResultNotify proResp;
	proResp.ParseFromArray(pMsg->data, pMsg->size);

	H::logger->info("游戏结束...");

	pRobot->Release();
	CRobotMgr::Instance()->OpenRoom();
}

void CMsgConn::HandleResponseResp(const PbMsgWebSS* pMsg)
{
	::msg_maj::ResponseEventResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	if (pRobot->m_usSeat == proto.seat())
	{
		switch (proto.event())
		{
		case ::msg_maj::pong:
		{
			int16_t usPai = proto.eventtilelist(0);
			pRobot->FitlerFai(usPai, proto.eventtilelist_size());
			//pRobot->DiscardReq(0);
			pRobot->m_usPai = 0;
			pRobot->SetActionType(eActionType_Discard);

			break;
		}
		case ::msg_maj::ming_gang:
		{
			int16_t usPai = proto.eventtilelist(0);
			pRobot->FitlerFai(usPai, proto.eventtilelist_size());
			break;
		}
		case ::msg_maj::an_gang:
		{
			int16_t usPai = proto.eventtilelist(0);
			pRobot->FitlerFai(usPai, proto.eventtilelist_size());
			break;
		}
		case ::msg_maj::guo_shou_gang:
		{
			int16_t usPai = proto.eventtilelist(0);
			pRobot->FitlerFai(usPai, proto.eventtilelist_size());
			break;
		}
		default:
			break;
		}
	}
}

void CMsgConn::HandleNotifyPlayerEvent(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	::msg_maj::NotifyPlayerEvent proData;
	proData.ParseFromArray(pMsg->data, pMsg->size);
	
	for (uint16_t i = 0; i < proData.event_list_size(); ++i)
	{
		if (proData.event_list(i).event_t() == ::msg_maj::zi_mo_hu)
		{
			if (proData.event_list_size() > 0)
			{
				pRobot->m_usPai = proData.event_list(0).event_pai(0);
			}		
			pRobot->SetActionType(eActionType_ZiMo);
			break;
		}
	}
}

void CMsgConn::HandlePrepareRoundNotify(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	pRobot->SendAcceptStart();
}

void CMsgConn::HandleDismissRoomNotify(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	pRobot->m_bClickDismiss = true;
	pRobot->SetActionType(eActionType_AgreeDismiss);
}

void CMsgConn::HandleDismissRoomResp(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	pRobot->StopDismissRoom();
}

void CMsgConn::HandleRobotReconnected(const PbMsgWebSS* pMsg)
{
	::msg_maj::ReconnectLoadResp proMaj;
	proMaj.ParseFromArray(pMsg->data, pMsg->size);

	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (pRobot == NULL)
	{
		H::logger->error("找不到Robot");
		ASSERT(0);
		return;
	}

	pRobot->SeatMySeat(proMaj.self_seat().seat());

	if (proMaj.self_discard()) // 该自己打牌了
	{
		uint16_t usPai = 0;
		if (proMaj.self_events_size() > 0)
		{
			for (int i = 0; i < proMaj.self_events_size(); ++i)
			{
				const ::msg_maj::EventInfo& eventInfo = proMaj.self_events(i);
				::msg_maj::event_type event_t = eventInfo.event_t();
				if (eventInfo.event_pai_size() >= i)
				{
					usPai = eventInfo.event_pai(i);
				}
				else
				{
					usPai = proMaj.curr_tile();
				}

				switch (event_t)
				{
				case msg_maj::e_none:
					break;
				case msg_maj::zi_mo_hu:
					pRobot->SetActionType(eActionType_ZiMo);
					break;
				case msg_maj::dian_pao_hu:
					pRobot->SetActionType(eActionType_DianPao);
					break;
				case msg_maj::ming_gang:
					pRobot->SetActionType(eActionType_MingGang);
					break;
				case msg_maj::an_gang:
					pRobot->SetActionType(eActionType_AnGang);
					break;
				case msg_maj::guo_shou_gang:
					pRobot->SetActionType(eActionType_GuoShouGang);
					break;
				case msg_maj::pong:
					pRobot->SetActionType(eActionType_Peng);
					break;
				case msg_maj::pass:
					pRobot->SetActionType(eActionType_DianPao);
					break;
				case msg_maj::discard:
					pRobot->SetActionType(eActionType_Discard);
					break;
				case msg_maj::e_max:
					break;
				default:
					break;
				}
			}
		}
		else
		{
			pRobot->SetActionType(eActionType_Discard);
		}
	}
}

void CMsgConn::HandleRobotStartRoundResp(const PbMsgWebSS* pMsg)
{
	::msg_maj::StartRoundResp proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	pRobot->myPaiData.CopyFrom(proto);
}

void CMsgConn::HandleRobotDiscardTingNotify(const PbMsgWebSS* pMsg)
{
	::msg_maj::TingPaiDiscardNotify proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	pRobot->tingPaiDiscardNotify.CopyFrom(proto);
}

void CMsgConn::HandleAskSanZhuang(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	pRobot->SetActionType(eActionType_HuanSanZhang);
}

void CMsgConn::HandleHuanSanNotify(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}

	::msg_maj::HuanSanZhangNotify proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	for (int i = 0 ; i < proto.pais_size(); ++i)
	{
		pRobot->myPaiData.add_tile_list(proto.pais(i));
	}
}

void CMsgConn::HandleAskDingQue(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	pRobot->SetActionType(eActionType_DingQue);
}

void CMsgConn::HandleReconnectSyncCard(const PbMsgWebSS* pMsg)
{
	CRobot* pRobot = CRobotMgr::Instance()->GetRobot(pMsg->clientSessID);
	if (NULL == pRobot)
	{
		return;
	}
	pRobot->SendReconnectOtherReady();
}

void CMsgConn::HandleRoomMsg(const PbMsgWebSS* pMsg)
{
	uint16_t usCCmd = pMsg->cmdType;
	switch (usCCmd)
	{
	case ::msg_maj::open_room_resp:
	{
		HandleCreateRoomResp(pMsg);
		break;
	}	
	case ::msg_maj::enter_room_resp:
	{
		HandleEnterRoomResp(pMsg);
		break;
	}
	case ::msg_maj::room_ready_notify:
	{
		HandleRoomReadyNotify(pMsg);
		break;
	}
	case ::msg_maj::sync_room_role_info:
	{
		HandleSyncRoleInfResp(pMsg);
		break;
	}
	case ::msg_maj::sync_romm_inn_info:
	{
		HandleInnRoomInfoNotify(pMsg);
		break;
	}
	case ::msg_maj::dismiss_room_notify:
	{
		HandleDismissRoomNotify(pMsg);
		break;
	}
	case ::msg_maj::dismiss_room_resp:
	{
		HandleDismissRoomResp(pMsg);
		break;
	}
	default:
		break;
	}
}

void CMsgConn::HandleMajiangMsg(const PbMsgWebSS* pMsg)
{
	uint16_t usCCmd = pMsg->cmdType;
	switch (usCCmd)
	{
	case ::msg_maj::ask_start_game:
	{
		HandleAskStartGameResp(pMsg);
		break;
	}
	case ::msg_maj::start_round_resp:
	{
		HandleStartRoundResp(pMsg);
		break;
	}
	case ::msg_maj::robot_start_round_resp:
	{
		HandleRobotStartRoundResp(pMsg);
		break;
	}
	case ::msg_maj::deal_tile_notify:
	{
		HandleDealTileNotify(pMsg);
		break;
	}
	case ::msg_maj::discard_tile_resp:
	{
		HandleDiscardTileResp(pMsg);
		break;
	}
	case ::msg_maj::game_result_notify:
	{
		HandleGameResultNotify(pMsg);
		break;
	}
	case ::msg_maj::total_result_notify:
	{
		HandleTotalResultNotify(pMsg);
		break;
	}
	case ::msg_maj::response_resp: // 事件广播
	{
		HandleResponseResp(pMsg);
		break;
	}
	case ::msg_maj::notify_player_event: // 通知玩家时间
	{
		HandleNotifyPlayerEvent(pMsg);
		break;
	}
	case ::msg_maj::robot_reconnect_resp:
	{
		HandleRobotReconnected(pMsg);
		break;
	}
	case ::msg_maj::ting_pai_discard_notify:
	{
		HandleRobotDiscardTingNotify(pMsg);
		break;
	}
	case ::msg_maj::ask_start_sanzhang:
	{
		HandleAskSanZhuang(pMsg);
		break;
	}
	case ::msg_maj::huan_sanzhang_notify:
	{
		HandleHuanSanNotify(pMsg);
		break;
	}
	case ::msg_maj::ask_start_dingque:
	{
		HandleAskDingQue(pMsg);
		break;
	}
	case ::msg_maj::reconnect_sync_card:
	{
		break;
	}
	default:
		break;
	}
}