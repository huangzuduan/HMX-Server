#include "CRobot.hpp"
#include "CRobotMgr.hpp"
#include "GameService.h"
#include "SrvEngine.h"

CRobot::CRobot(zSession* pSession,const std::string& strAccount, uint32_t unSessionID, uint64_t uid) :
	m_pTimer(NULL),
	m_pSession(pSession),
	m_bGhost(false),
	m_bClickDismiss(false),
	m_eActionType(eActionType_NULL),
	m_strAccount(strAccount),
	m_unSessionID(_entry_id),
	m_usUid(uid),
	m_nRoomID(0),
	m_uCurrInnID(0),
	m_usSeat(-1),
	m_usPai(0),
	m_uQueType(0),
	bIsRoomer(false),
	bIsBanker(false),
	bIsLogin_1(false),
	bIsLogin_2(false),
	bIsSendCreate_1(false),
	bIsSendCreate_2(false),
	bIsSendJoin_1(false),
	bIsSendJoin_2(false),
	bIsSendJoinReady_1(false),
	bIsSendJoinReady_2(false),
	bIsStartGame_1(false),
	bIsStartGame_2(false),
	bIsSendAcceptStart_1(false),
	bIsSendAcceptStart_2(false),
	bIsDisoverCard(false),
	bIsPlaying(false),
	bIsCanHu(false),
	bIsCanGang(false),
	bIsCanPeng(false),
	bIsCanDiscard(false),
	bIsDismiss(false),
	bIsTingpai(false)
{
	m_unSessionID = unSessionID;
	bIsRoomer = (m_unSessionID % 4 == 1);
	bIsBanker = (m_unSessionID % 4 == 1);
}

CRobot::~CRobot()
{
}

bool CRobot::Init()
{
	m_pTimer = new fogs::FogsTimer(*GameService::getMe().GetIoService());
	return true;
}

void CRobot::NextReset()
{
	this->bIsSendAcceptStart_2 = false;
	this->bIsDisoverCard = false;
	this->bIsPlaying = false;
	this->bIsTingpai = false;
}

void CRobot::Release()
{
	m_bGhost = false;
	m_bClickDismiss = false;
	m_eActionType = eActionType_NULL;
	m_nRoomID = 0;
	m_uCurrInnID = 0;
	m_uTotalInnCount = 0;
	m_usSeat = -1;
	m_usPai = 0;
	m_uQueType = 0;
	bIsSendCreate_1 = false;
	bIsSendCreate_2 = false;
	bIsSendJoin_2 = false;
	bIsSendJoinReady_1 = false;
	bIsSendJoinReady_2 = false;
	bIsStartGame_1 = false;
	bIsStartGame_2 = false;
	bIsSendAcceptStart_1 = false;
	bIsSendAcceptStart_2 = false;
	bIsDisoverCard = false;
	bIsPlaying = false;
	bIsCanHu = false;
	bIsCanGang = false;
	bIsCanPeng = false;
	bIsCanDiscard = false;
	bIsDismiss = false;
	bIsTingpai = false;
}

void CRobot::SetActionType(eActionType etype)
{
	if (m_eActionType != eActionType_NULL)
	{
		Timer();
	}
	m_eActionType = etype;
	m_pTimer->start(1500, boost::bind(&CRobot::Timer, this), fogs::FogsTimer::SINGLE_SHOOT_TIMER);
}

void CRobot::Timer()
{
	switch (m_eActionType)
	{
	case eActionType_NULL: break;
	case eActionType_Login: SendLoginReq(); break;
	case eActionType_OpenRoom: SendCreateRoomReq(); break;
	case eActionType_EnterReady: SendJoinReadyReq(); break;
	case eActionType_StartGame: SendStartGame(); break;
	case eActionType_AcceptStart: SendAcceptStart(); break;
	case eActionType_AgreeDismiss: SendAgreeDismiss(); break;
	case eActionType_ZiMo: RespZiMoPai(m_usPai); break;
	case eActionType_DianPao: RespDiaoPaoHu(m_usPai); break;
	case eActionType_MingGang: RespMingGang(m_usPai); break;
	case eActionType_AnGang: RespAnGang(m_usPai); break;
	case eActionType_GuoShouGang: RespGuoShouGang(m_usPai); break;
	case eActionType_Peng: RespPong(m_usPai); break;
	case eActionType_RoundPrepare: SendRoundPrepare(); break;
	case eActionType_Discard: DiscardReq(m_usPai); break;
	case eActionType_HuanSanZhang:HuanSanZhangReq(); break;
	case eActionType_DingQue:DingQueReq();break;
	case eActionType_Num: break;
	default: break;
	}

	m_eActionType = eActionType_NULL;

	SendAgreeDismiss();
}

void CRobot::StopDismissRoom()
{
	m_bClickDismiss = false;
	if (m_eActionType == eActionType_AgreeDismiss)
	{
		m_pTimer->cancel();
		m_eActionType = eActionType_NULL;
	}
}

void CRobot::SendLoginReq()
{
	::msg_maj::LoginPlayerReq proto;
	proto.set_account(m_strAccount);
	m_pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::login_player_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 请求登录",GetAccount().c_str(),GetID32());
}

void CRobot::SendCreateRoomReq()
{
	if (m_nRoomID > 0)
	{
		return;
	}

	uint16_t g_usGameType = 1;
	uint16_t g_usMaNumType = 0;
	uint16_t g_usPlayNumType = 1;
	::msg_maj::OpenRoomReq proto;
	bool g_bIsGhost = false;
	proto.set_game_type(::msg_maj::maj_t_yulin);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::open_room_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 请求创建房间" ,GetAccount().c_str(),GetID32());
}

void CRobot::SendJoinRoomReq(uint32_t roomID)
{
	::msg_maj::EnterRoomReq proto;
	proto.set_type(::msg_maj::ROOM_ROOM_NO);
	proto.set_room_no(roomID);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::enter_room_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 请求进入房间:", GetAccount().c_str(),GetID32());
}

void CRobot::SendJoinReadyReq()
{
	::msg_maj::EnterRoomReady proto;
	m_pSession->sendMsgProto(::comdef::msg_room, ::msg_maj::enter_room_ready, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,请求进入准备完成:",GetAccount().c_str(), GetID32());
}

void CRobot::SendStartGame()
{
	::msg_maj::StartGameReq proto;
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::start_game_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,请求开始游戏",GetAccount().c_str(),GetID32());
}

void CRobot::SendAcceptStart()
{
	::msg_maj::AcceptStartReq  proto;
	proto.set_accept(true);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::accept_start_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,请求接受开始:", GetAccount().c_str(), GetID32());
}

void CRobot::SendDisoverCard()
{
	::msg_maj::DisCardOver proto;
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::disover_card_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,请求发牌完毕:", GetAccount().c_str(), GetID32());
}

void CRobot::SendRoundPrepare()
{
	::msg_maj::PrepareRoundReq  proto;
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::prepare_round_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,请求准备下一场:", GetAccount().c_str(), GetID32());
}

void CRobot::SendLeaveRoom()
{
	::msg_maj::LeaveRoomReq proto;
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::leave_room_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,请求离开房间,打完了第:[%d]局",GetAccount().c_str() , GetID32(),this->m_uCurrInnID);
}

void CRobot::SendDismissRoomReq()
{
	::msg_maj::DismissRoomReq proto;
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::dismiss_room_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,发起解散房间",GetAccount().c_str(), GetID32());
}

void CRobot::SendAgreeDismiss()
{
	if (!m_bClickDismiss)
	{
		return;
	}

	::msg_maj::AgreeDismissReq proto;
	proto.set_isagree(true);
	proto.set_seat(m_usSeat);
	m_pSession->sendMsgProto(::comdef::msg_room, ::msg_maj::dismiss_room_vote_accept, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,同意解散房间", GetAccount().c_str(), GetID32());

	m_bClickDismiss = false;
}

void CRobot::SendReconnectOtherReady()
{
	::msg_maj::ReconnectOtherReadyReq proto;
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::reconnect_other_ready_req, m_unSessionID, proto);
}

bool CRobot::IsGhostPai(uint16_t usPai)
{
	switch (CRobotMgr::Instance()->m_unProductID)
	{
	case 10001: //贵港
	{
		if (usPai == 7)
		{
			return true;
		}
		break;
	}
	case 10002:
	{
		if (usPai == 5)
		{
			return true;
		}
		break;
	}
	case 10003:
	{
		if (usPai == 7)
		{
			return true;
		}
		break;
	}
	default:
		break;
	}

	return false;
}

void CRobot::Display()
{
	std::stringstream sql_data;
	for (int i = 0; i < myPaiData.tile_list_size(); ++i)
	{
		switch (myPaiData.tile_list(i))
		{
		case 1: sql_data << "东" << ","; break;
		case 2: sql_data << "南" << ","; break;
		case 3: sql_data << "西" << ","; break;
		case 4: sql_data << "北" << ","; break;
		case 5: sql_data << "中" << ","; break;
		case 6: sql_data << "发" << ","; break;
		case 7: sql_data << "白" << ","; break;
		case 11: sql_data << "1筒" << ","; break;
		case 12: sql_data << "2筒" << ","; break;
		case 13: sql_data << "3筒" << ","; break;
		case 14: sql_data << "4筒" << ","; break;
		case 15: sql_data << "5筒" << ","; break;
		case 16: sql_data << "6筒" << ","; break;
		case 17: sql_data << "7筒" << ","; break;
		case 18: sql_data << "8筒" << ","; break;
		case 19: sql_data << "9筒" << ","; break;
		case 21: sql_data << "1条" << ","; break;
		case 22: sql_data << "2条" << ","; break;
		case 23: sql_data << "3条" << ","; break;
		case 24: sql_data << "4条" << ","; break;
		case 25: sql_data << "5条" << ","; break;
		case 26: sql_data << "6条" << ","; break;
		case 27: sql_data << "7条" << ","; break;
		case 28: sql_data << "8条" << ","; break;
		case 29: sql_data << "9条" << ","; break;
		case 31: sql_data << "1万" << ","; break;
		case 32: sql_data << "2万" << ","; break;
		case 33: sql_data << "3万" << ","; break;
		case 34: sql_data << "4万" << ","; break;
		case 35: sql_data << "5万" << ","; break;
		case 36: sql_data << "6万" << ","; break;
		case 37: sql_data << "7万" << ","; break;
		case 38: sql_data << "8万" << ","; break;
		case 39: sql_data << "9万" << ","; break;
		default:
			break;
		}
	}
	H::logger->info("%s",sql_data.str().c_str());
}

void CRobot::DiscardReq(uint16_t usPai)
{
	if (usPai == 0) //则取单个发牌
	{
		bool bRandPai = false;
		if (bRandPai)
		{
			int index = randBetween(0, myPaiData.tile_list_size() - 1);
			usPai = myPaiData.tile_list(index);
			DiscardReq(usPai);
			return;
		}
		if (tingPaiDiscardNotify.ting_list_size() > 0)// 检查是否可以听牌
		{
			int32_t ting_size = tingPaiDiscardNotify.ting_list_size();
			int32_t ting_max_count_discard = 0;
			int32_t ting_max_count_weigthVal = 0;
			H::logger->info("%s,ID:%d,有听牌 %d 张", GetAccount().c_str(), GetID32(), ting_size);
			for (int i = 0; i < tingPaiDiscardNotify.ting_list_size(); ++i)
			{
				const ::msg_maj::TingPai& tingPai = tingPaiDiscardNotify.ting_list(i);
				if (ting_max_count_discard == 0)
				{
					ting_max_count_discard = tingPai.dicard();
					for (int j = 0; j < tingPai.prompt_list_size(); j++)
					{
						const ::msg_maj::PromptPai& promPai = tingPai.prompt_list(j);
						ting_max_count_weigthVal += promPai.paidest() * promPai.mulit();
					}
				}
				else
				{
					int32_t thisTing_max_count_weigthVal = 0;
					for (int j = 0; j < tingPai.prompt_list_size(); j++)
					{
						const ::msg_maj::PromptPai& promPai = tingPai.prompt_list(j);
						thisTing_max_count_weigthVal += promPai.paidest() * promPai.mulit();
					}
					if (thisTing_max_count_weigthVal > ting_max_count_weigthVal)
					{
						ting_max_count_discard = tingPai.dicard();
					}
				}
			}
			usPai = ting_max_count_discard;
		}
		else
		{
			bool bHadDingQuePai = false;
			std::map<uint16_t, uint32_t> paiNumMap;
			for (int i = 0; i < myPaiData.tile_list_size(); ++i)
			{
				paiNumMap[myPaiData.tile_list(i)] += 1;
				if (m_uQueType > 0 && myPaiData.tile_list(i) / 10 == m_uQueType)
				{
					usPai = myPaiData.tile_list(i);
					bHadDingQuePai = true;
					break;
				}
			}

			if (bHadDingQuePai == false)
			{
				std::vector<uint16_t> vecOneCount;
				std::vector<uint16_t> vecTwoCount;
				std::vector<uint16_t> vecThreeCount;
				std::vector<uint16_t> vecFourCount;
				for (std::map<uint16_t, uint32_t>::const_iterator it = paiNumMap.begin(); it != paiNumMap.end(); ++it)
				{
					if (m_bGhost && IsGhostPai(it->first))
					{
						continue;
					}
					if (it->second == 1)
					{
						vecOneCount.push_back(it->first);
					}
					else if (it->second == 2)
					{
						vecTwoCount.push_back(it->first);
					}
					else if (it->second == 3)
					{
						vecThreeCount.push_back(it->first);
					}
					else if (it->second == 4)
					{
						vecFourCount.push_back(it->first);
					}
				}

				if (vecOneCount.size() > 0)
				{
					if (vecOneCount.size() >= 3)
					{
						std::vector<uint16_t> unLianPai; // 不能连在一起的牌
						for (size_t i = 0; i < vecOneCount.size() - 2; ++i)
						{
							if (CheckABCPai(vecOneCount[i], vecOneCount[i + 1], vecOneCount[i + 2]))
							{
								i += 2;
							}
							else
							{
								unLianPai.push_back(vecOneCount[i]);
							}
						}
						if (unLianPai.size() > 0)
						{
							// 有字牌先出字牌
							for (size_t i = 0; i < vecOneCount.size(); ++i)
							{
								if (vecOneCount[i] / 10 == 0)
								{
									usPai = vecOneCount[i];
									return DiscardReq(usPai);
								}
							}
							int index = randBetween(0, unLianPai.size() - 1);
							usPai = unLianPai[index];
							return DiscardReq(usPai);
						}
					}
					else
					{
						// 有字牌先出字牌
						for (size_t i = 0; i < vecOneCount.size(); ++i)
						{
							if (vecOneCount[i] / 10 == 0)
							{
								usPai = vecOneCount[i];
								return DiscardReq(usPai);
							}
						}
						int index = randBetween(0, vecOneCount.size() - 1);
						usPai = vecOneCount[index];
						return DiscardReq(usPai);
					}
				}

				if (vecTwoCount.size() > 0)
				{
					int index = randBetween(0, vecTwoCount.size() - 1);
					usPai = vecTwoCount[index];
				}
				else if (vecThreeCount.size() > 0)
				{
					int index = randBetween(0, vecThreeCount.size() - 1);
					usPai = vecThreeCount[index];
				}
				else if (vecFourCount.size() > 0)
				{
					int index = randBetween(0, vecFourCount.size() - 1);
					usPai = vecFourCount[index];
				}
			}
		}
		DiscardReq(usPai);
		return;
	}
	else // 要去掉该张牌
	{
		FitlerFai(usPai,1);
	}

	::msg_maj::DiscardReq proto;
	proto.set_tile(dealNotify.tile());
	proto.set_tile(usPai);

	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::discard_tile_req, m_unSessionID, proto);

	int32_t msg_index = CRobotMgr::Instance()->GetOutCardSound(this, usPai / 10, usPai % 10);
	if (msg_index > -1)
	{
		::msg_maj::QuickMessageReq msgProto;
		msgProto.set_seat(this->m_usSeat);
		msgProto.set_msg_index(msg_index);
		m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::quickmessage_req, m_unSessionID, msgProto);
	}

}

void CRobot::HuanSanZhangReq()
{
	std::map<int16_t, int16_t> mapTypeCount;
	mapTypeCount[1] = 0;
	mapTypeCount[2] = 0;
	mapTypeCount[3] = 0;
	for (int i = 0; i < myPaiData.tile_list_size(); ++i)
	{
		mapTypeCount[myPaiData.tile_list(i) / 10] += 1;
	}

	std::vector<int16_t> vecHuan;
	if (mapTypeCount[1] >= 3)
	{
		vecHuan.push_back(1);
	}
	if (mapTypeCount[2] >= 3)
	{
		vecHuan.push_back(2);
	}
	if (mapTypeCount[3] >= 3)
	{
		vecHuan.push_back(3);
	}

	int randIndex = randBetween(0, vecHuan.size() - 1);
	int usType = vecHuan[randIndex];

	::msg_maj::HuanSanZhangReq proReq;
	proReq.set_type(usType);
	proReq.set_seat(m_usSeat);
	for (int i = 0; i < myPaiData.tile_list_size(); ++i)
	{
		int tile = myPaiData.tile_list(i);
		if (tile / 10 == usType)
		{
			proReq.add_pais(tile);
			if (proReq.pais_size() == 3)
			{
				break;
			}
		}
	}

	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::huan_sanzhang_req, m_unSessionID, proReq);

	for (int i = 0; i < proReq.pais_size(); ++i)
	{
		FitlerFai(proReq.pais(i), 1);
	}
}

void CRobot::DingQueReq()
{
	std::map<uint16_t, uint32_t> paiNumMap;
	paiNumMap[1] = 0;
	paiNumMap[2] = 0;
	paiNumMap[3] = 0;
	for (int i = 0; i < myPaiData.tile_list_size(); ++i)
	{
		paiNumMap[myPaiData.tile_list(i) / 10] += 1;
	}

	::msg_maj::DingQueReq proReq;
	proReq.set_seat(m_usSeat);
	if (paiNumMap[1] <= paiNumMap[2] && paiNumMap[1] <= paiNumMap[3])
	{
		proReq.set_type(1);
	}
	else if (paiNumMap[2] <= paiNumMap[1] && paiNumMap[2] <= paiNumMap[3])
	{
		proReq.set_type(2);
	}
	else if (paiNumMap[3] <= paiNumMap[1] && paiNumMap[3] <= paiNumMap[2])
	{
		proReq.set_type(3);
	}
	else
	{
		proReq.set_type(randBetween(1,3));
	}
	this->m_uQueType = proReq.type();
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::dingque_req, m_unSessionID, proReq);
}

void CRobot::FitlerFai(uint16_t usPai, int16_t num)
{
	::msg_maj::StartRoundResp paiDataTmp;
	paiDataTmp.CopyFrom(myPaiData);
	myPaiData.clear_tile_list();
	int16_t count = 0;
	for (int i = 0; i < paiDataTmp.tile_list_size(); ++i)
	{
		if (paiDataTmp.tile_list(i) == usPai && count < num)
		{
			count++;
		}
		else
		{
			myPaiData.add_tile_list(paiDataTmp.tile_list(i));
		}
	}
}

void CRobot::RespZiMoPai(uint16_t usPai)
{
	::msg_maj::ResponseEventReq proto;
	proto.set_event(::msg_maj::zi_mo_hu);
	proto.set_tile(usPai);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::response_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d,自摸:%s",GetAccount().c_str(),GetID32(), CRobotMgr::Instance()->GetPaiZhong(usPai).c_str());
	int32_t msg_index = CRobotMgr::Instance()->GetStateSound(this, ::msg_maj::zi_mo_hu);
	if (msg_index > -1)
	{
		::msg_maj::QuickMessageReq msgProto;
		msgProto.set_seat(this->m_usSeat);
		msgProto.set_msg_index(msg_index);
		m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::quickmessage_req, m_unSessionID, msgProto);
	}
}

void CRobot::RespPassPai(uint16_t usPai)
{
	::msg_maj::ResponseEventReq proto;
	proto.set_event(::msg_maj::pass);
	proto.set_tile(usPai);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::response_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 过牌:%s ",GetAccount().c_str(), GetID32(), CRobotMgr::Instance()->GetPaiZhong(usPai).c_str());
}

void CRobot::RespDiaoPaoHu(uint16_t usPai)
{
	::msg_maj::ResponseEventReq proto;
	proto.set_event(::msg_maj::dian_pao_hu);
	proto.set_tile(usPai);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::response_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 放炮: %s",GetAccount().c_str(), GetID32(), CRobotMgr::Instance()->GetPaiZhong(usPai).c_str());
	int32_t msg_index = CRobotMgr::Instance()->GetStateSound(this, ::msg_maj::dian_pao_hu);
	if (msg_index > -1)
	{
		::msg_maj::QuickMessageReq msgProto;
		msgProto.set_seat(this->m_usSeat);
		msgProto.set_msg_index(msg_index);
		m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::quickmessage_req, m_unSessionID, msgProto);
	}
}

void CRobot::RespMingGang(uint16_t usPai)
{
	::msg_maj::ResponseEventReq proto;
	proto.set_event(::msg_maj::ming_gang);
	proto.set_tile(usPai);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::response_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 明杠: %s",GetAccount().c_str(),GetID32(), CRobotMgr::Instance()->GetPaiZhong(usPai).c_str());
	int32_t msg_index = CRobotMgr::Instance()->GetStateSound(this, ::msg_maj::ming_gang);
	if (msg_index > -1)
	{
		::msg_maj::QuickMessageReq msgProto;
		msgProto.set_seat(this->m_usSeat);
		msgProto.set_msg_index(msg_index);
		m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::quickmessage_req, m_unSessionID, msgProto);
	}
}

void CRobot::RespAnGang(uint16_t usPai)
{
	::msg_maj::ResponseEventReq proto;
	proto.set_event(::msg_maj::an_gang);
	proto.set_tile(usPai);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::response_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 暗杠: %s",GetAccount().c_str() ,GetID32() , CRobotMgr::Instance()->GetPaiZhong(usPai).c_str());
	int32_t msg_index = CRobotMgr::Instance()->GetStateSound(this, ::msg_maj::an_gang);
	if (msg_index > -1)
	{
		::msg_maj::QuickMessageReq msgProto;
		msgProto.set_seat(this->m_usSeat);
		msgProto.set_msg_index(msg_index);
		m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::quickmessage_req, m_unSessionID, msgProto);
	}
}

void CRobot::RespGuoShouGang(uint16_t usPai)
{
	::msg_maj::ResponseEventReq proto;
	proto.set_event(::msg_maj::guo_shou_gang);
	proto.set_tile(usPai);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::response_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 过手杠: %s",GetAccount().c_str(), GetID32(), CRobotMgr::Instance()->GetPaiZhong(usPai).c_str());
	int32_t msg_index = CRobotMgr::Instance()->GetStateSound(this, ::msg_maj::guo_shou_gang);
	if (msg_index > -1)
	{
		::msg_maj::QuickMessageReq msgProto;
		msgProto.set_seat(this->m_usSeat);
		msgProto.set_msg_index(msg_index);
		m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::quickmessage_req, m_unSessionID, msgProto);
	}
}

void CRobot::RespPong(uint16_t usPai)
{
	::msg_maj::ResponseEventReq proto;
	proto.set_event(::msg_maj::pong);
	proto.set_tile(usPai);
	m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::response_req, m_unSessionID, proto);
	H::logger->info("%s,ID:%d, 碰: %s",GetAccount().c_str(),GetID32() , CRobotMgr::Instance()->GetPaiZhong(usPai).c_str());

	int32_t msg_index = CRobotMgr::Instance()->GetStateSound(this, ::msg_maj::pong);
	if (msg_index > -1)
	{
		::msg_maj::QuickMessageReq msgProto;
		msgProto.set_seat(this->m_usSeat);
		msgProto.set_msg_index(msg_index);
		m_pSession->sendMsgProto(::comdef::msg_maj, ::msg_maj::quickmessage_req, m_unSessionID, msgProto);
	}
}