#include "CMajingRule.hpp"
#include "CRoom.hpp"
#include "CPlayer.hpp"

#include "CMaJiang.hpp"

CMajingRule::CMajingRule(CRoom* pRoom,const ::msg_maj::RoomOption& roomOption)
	:m_pRoom(pRoom)
	,m_pMaj(NULL)
	,m_roomOption(roomOption)
{
	m_usPayType = roomOption.paytype();		// 支付类型
	m_usBaseScoreType = roomOption.basescoretype();	// 底分类型
	m_usJuShuType = roomOption.jushutype();
	m_usRenShuType = roomOption.renshutype();
	m_usFengDingType = roomOption.fengdingtype();

	m_usMaiMaType = 0;	
	m_bYiMaAllHit = false;
	m_bGhost = false;				
	m_bWuZi = false;				
	m_bCanPaoHu = false;			
	m_bDaHuJiaBei = false;			
	m_bGangShangPaoBao3Jia = false;		
	m_bQiangGangBao3Jia = false;	
	m_bGangKaiHuaIsBao3Jia = false;	

	m_bJieHu = false;
	m_bGengZhuang = false;

	m_bIsGuoPeng = true;
	m_bIsGuoHu = true;
	m_bIsGuoGang = true;
}

CMajingRule::~CMajingRule()
{
}

uint16_t CMajingRule::GetTotalPaiNum() const
{
	uint16_t usTotalNum = m_bWuZi ? (m_bGhost ? 112 : 108) : 136;
	if (GetPlayerNum() == 2)
	{
		usTotalNum -= 7 * 2 * 4;
	}
	return usTotalNum;
}

bool CMajingRule::IsGhostCard(uint16_t usPai)
{
	return  m_setGhostPai.find(usPai) != m_setGhostPai.end();
}

void CMajingRule::CountEventGang(uint16_t usSeat, uint16_t usEventType)
{
	switch (usEventType)
	{
	case ::msg_maj::ming_gang:
	{
		CountEventMingGang(usSeat);
		break;
	}
	case ::msg_maj::an_gang:
	{
		CountEventAnGang(usSeat);
		break;
	}
	case ::msg_maj::guo_shou_gang:
	{
		CountEventGouShouGang(usSeat);
		break;
	}
	default:
		break;
	}
}

void CMajingRule::CountEventMingGang(uint16_t usSeat)
{
	int32_t nScore = 1;
	m_pRoom->GetPlayer(usSeat)->AddTotalFan(nScore*(m_pRoom->GetTotalPersons() - 1));
	m_pRoom->GetPlayer(usSeat)->AddMingGangTimes(1);

	m_pRoom->GetPlayer(m_pMaj->GetUsCurActionPos())->AddTotalFan(-nScore*(m_pRoom->GetTotalPersons()-1));
	m_pRoom->GetPlayer(m_pMaj->GetUsCurActionPos())->AddFangGangTimes(1);
}

void CMajingRule::CountEventAnGang(uint16_t usSeat)
{
	int32_t nScore = 2;
	for (uint16_t i = 0; i < m_pRoom->GetTotalPersons(); ++i)
	{
		if (NULL == m_pRoom->GetPlayer(i))
		{
			continue;
		}
		int32_t nGetScore = 0;
		if (i == usSeat)
		{
			m_pRoom->GetPlayer(i)->AddTotalFan(nScore*(m_pRoom->GetTotalPersons() - 1));
			m_pRoom->GetPlayer(i)->AddAnGangTimes(1);
		}
		else
		{
			m_pRoom->GetPlayer(i)->AddTotalFan(-nScore);
		}
	}
}

void CMajingRule::CountEventGouShouGang(uint16_t usSeat)
{
	int32_t nScore = 1;
	for (uint16_t i = 0; i < m_pRoom->GetTotalPersons(); ++i)
	{
		if (NULL == m_pRoom->GetPlayer(i))
		{
			continue;
		}
		int32_t nGetScore = 0;
		if (i == usSeat)
		{
			m_pRoom->GetPlayer(i)->AddTotalFan(nScore*(m_pRoom->GetTotalPersons() - 1));
			m_pRoom->GetPlayer(i)->AddNextGangTimes(1);
		}
		else
		{
			m_pRoom->GetPlayer(i)->AddTotalFan(-nScore);
		}
	}
}

void CMajingRule::CheckHitMa(uint16_t usSeat, std::vector<uint16_t>& hitmalist) const
{
	hitmalist.clear();
	std::vector<uint16_t> allmalist;
	const vecHuPai& vecHuPai = m_pMaj->GetVecHuPai();
	for (vecHuPai::const_iterator iter = vecHuPai.begin(); iter != vecHuPai.end(); ++iter)
	{
		const stHuPai& st = *iter;
		if (st.m_usHupaiPos == usSeat)
		{
			int16_t sSeatType = ( 4 + usSeat - m_pRoom->GetBankerSeat()) % 4;
			switch (sSeatType)
			{
			case 0:
			{
				allmalist.push_back(11);
				allmalist.push_back(15);
				allmalist.push_back(19);
				allmalist.push_back(21);
				allmalist.push_back(25);
				allmalist.push_back(29);
				allmalist.push_back(31);
				allmalist.push_back(35);
				allmalist.push_back(1);
				break;
			}
			case 1:
			{
				//12~16~22~26~32~36~2~6
				allmalist.push_back(12);
				allmalist.push_back(16);
				allmalist.push_back(22);
				allmalist.push_back(26);
				allmalist.push_back(32);
				allmalist.push_back(36);
				allmalist.push_back(2);
				allmalist.push_back(5);
				break;
			}
			case 2:
			{
				//13~17~23~27~33~37~3~7
				allmalist.push_back(13);
				allmalist.push_back(17);
				allmalist.push_back(23);
				allmalist.push_back(27);
				allmalist.push_back(33);
				allmalist.push_back(37);
				allmalist.push_back(3);
				allmalist.push_back(6);
				break;
			}
			case 3:
			{
				//14~18~24~28~34~38~4
				allmalist.push_back(14);
				allmalist.push_back(18);
				allmalist.push_back(24);
				allmalist.push_back(28);
				allmalist.push_back(34);
				allmalist.push_back(38);
				allmalist.push_back(4);
				allmalist.push_back(7);
				break;
			}
			default: break;
			}

			const ::vector<uint16_t>& malist = m_pMaj->GetMaPaiList();
			for (std::vector<uint16_t>::const_iterator iter = malist.begin(); iter != malist.end(); ++iter)
			{
				for (std::vector<uint16_t>::iterator it = allmalist.begin(); it != allmalist.end(); ++it)
				{
					if (*iter == *it)
					{
						hitmalist.push_back(*iter);
						break;
					}
				}
			}

			break;
		}
	}
}

void CMajingRule::CountGengZhuang(uint16_t usPai)
{
	if (m_bGengZhuang)
	{
		m_pMaj->AddDiscards(usPai);
		// 检查跟庄中分
		if (m_pMaj->m_bHadCheckGZ == false && m_pMaj->m_bGenZhuangSuccess == false && m_pMaj->GetLoopPoses() == 4)
		{
			m_pMaj->m_bHadCheckGZ = true;
			// 计算是否有四张相同的出牌
			const std::vector<uint16_t>& discards = m_pMaj->GetDiscards();
			if (discards.size() == 4)
			{
				if (discards[0] == discards[1] && discards[1] == discards[2] && discards[2] == discards[3])
				{
					m_pMaj->m_bGenZhuangSuccess = true;

					// 广播跟庄事件
					::msg_maj::NotifyGenzhuang notifyGZ;
					m_pRoom->BrocastMsg(::comdef::msg_maj, ::msg_maj::notify_genzhuang_success, notifyGZ);

					uint32_t total = 0;
					for (uint16_t i = 0; i < m_pRoom->GetTotalPersons(); ++i)
					{
						if (i == m_pRoom->GetBankerSeat()) continue;

						if (m_pRoom->GetPlayer(i) == NULL) continue;

						total += 1;
						m_pRoom->GetPlayer(i)->AddTotalFan(1);
					}
					m_pRoom->GetPlayer(m_pRoom->GetBankerSeat())->AddTotalFan(-total);
				}
			}
		}
	}
}

uint16_t CMajingRule::GetFanAnGang(CPlayer* pPlayer) const
{ 
	return (m_pRoom->GetTotalPersons() - 1) * pPlayer->GetAnGangTimes() * 2; 
}

uint16_t CMajingRule::GetFanMingGang(CPlayer* pPlayer) const
{ 
	return (m_pRoom->GetTotalPersons() - 1) * pPlayer->GetMingGangTimes() * 1; 
}

uint16_t CMajingRule::GetFanNextGang(CPlayer* pPlayer) const
{ 
	return (m_pRoom->GetTotalPersons() - 1) * pPlayer->GetNextGangTimes() * 1; 
}

bool CMajingRule::IsQiangGangHuBao3Jia(const stHuPai& sthupai) const
{
	if (m_bQiangGangBao3Jia)
	{
		if (m_pMaj->m_nLastGangType == ::msg_maj::guo_shou_gang)
		{
			return true;
		}
	}
	return false;
}

bool CMajingRule::IsGangKaiHuaBao3Jia(const stHuPai& sthupai) const
{
	if (m_bGangKaiHuaIsBao3Jia) // 杠上花包三家
	{
		if (m_pMaj->m_nLastGangType == ::msg_maj::ming_gang)
		{
			const vecEventPai& eventPai = m_pRoom->GetPlayer(sthupai.m_usHupaiPos)->GetEventPaiList();
			for (vecEventPai::const_iterator it2 = eventPai.begin(); it2 != eventPai.end(); ++it2)
			{
				if (it2->usEventType == ::msg_maj::ming_gang && it2->usPai == m_pMaj->m_nLastGangPai)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool CMajingRule::IsFliterPaiEvent(CPlayer* pPlayer, uint16_t usPai) const { return false; }
bool CMajingRule::HuedCanSendCard(CPlayer* pPlayer) const { return pPlayer->IsHued() ? false : true; }
bool CMajingRule::HuedCanDiscard(CPlayer* pPlayer)const { return pPlayer->IsHued() ? false : true; }
bool CMajingRule::HuedCanEvent(CPlayer* pPlayer) const { return pPlayer->IsHued() ? false : true; }
bool CMajingRule::HuedCanGang(CPlayer* pPlayer) const { return pPlayer->IsHued() ? false : true; }
bool CMajingRule::HuedCanPeng(CPlayer* pPlayer) const { return pPlayer->IsHued() ? false : true; }
bool CMajingRule::HuedCanDiaoPao(CPlayer* pPlayer) const { return pPlayer->IsHued() ? false : true; }
bool CMajingRule::HuedCanGangShanPao(CPlayer* pPlayer) const { return pPlayer->IsHued() ? false : true; }

//检测是否胡牌（张）  
bool CMajingRule::CheckAAPai(int iValue1, int iValue2)
{
	if (iValue1 == iValue2)return true;
	return false;
}

//检测是否三连张  
bool CMajingRule::CheckABCPai(int iValue1, int iValue2, int iValue3)
{
	if (iValue1 == (iValue2 - 1) && iValue2 == (iValue3 - 1))return true;
	return false;
}

bool CMajingRule::CheckABCDPai(int iValue1, int iValue2, int iValue3, int iValue4)
{
	if (iValue1 == (iValue2 - 1) && iValue2 == (iValue3 - 1) && iValue3 == (iValue4 - 1))return true;
	return false;
}

bool CMajingRule::CheckABCDEFGPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6, int iValue7)
{
	if (iValue1 == (iValue2 - 1) &&
		iValue2 == (iValue3 - 1) &&
		iValue3 == (iValue4 - 1) &&
		iValue4 == (iValue5 - 1) &&
		iValue5 == (iValue6 - 1) &&
		iValue6 == (iValue7 - 1))
	{
		return true;
	}

	return false;
}

//检测是否三重张  
bool CMajingRule::CheckAAAPai(int iValue1, int iValue2, int iValue3)
{
	if (iValue1 == iValue2&&iValue2 == iValue3)return true;
	return false;
}

//检测是否四重张  
bool CMajingRule::CheckAAAAPai(int iValue1, int iValue2, int iValue3, int iValue4)
{
	if (iValue1 == iValue2&&iValue2 == iValue3&&iValue3 == iValue4)return true;
	return false;
}

//检测是否三连对  
bool CMajingRule::CheckAABBCCPai(int iValue1, int iValue2, int iValue3, int iValue4, int iValue5, int iValue6)
{
	if (iValue1 / 10 == eCardType_Zi)
	{
		return false;
	}

	if (iValue1 == iValue2&&iValue3 == iValue4&&iValue5 == iValue6)
	{
		if ((iValue1 == iValue3 - 1) && (iValue3 == iValue5 - 1))
		{
			return true;
		}
	}
	return false;
}

bool CMajingRule::DelAAPai_NULL(vecCheckPai& stlist)
{
	for (vecCheckPai::iterator iter = stlist.begin(); iter != stlist.end(); ++iter)
	{
		stCheckPai& st = *iter;
		if (st.usNum == 2)
		{
			stlist.erase(iter);
			return true;
		}
	}

	return false;
}

bool CMajingRule::DelAAPai_Pai(vecCheckPai& stlist, uint16_t usPai)
{
	if (usPai <= 0)
	{
		return false;
	}

	for (vecCheckPai::iterator iter = stlist.begin(); iter != stlist.end(); ++iter)
	{
		stCheckPai& st = *iter;
		if (st.usPai == usPai)
		{
			st.usNum -= 2;
			if (st.usNum == 0)
			{
				stlist.erase(iter);
			}
			return true;
		}
	}

	return false;
}

bool CMajingRule::DelAAPai_Num(vecCheckPai& stlist, uint16_t& usNum)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 2)
		{
			DelStructPai(stlist, 0, 4);
			++usNum;
		}

		return true;

		break;
	}
	default:
		break;
	}

	for (uint16_t i = 0; i < usSize - 1; ++i)
	{
		if (stlist[i].usNum >= 2)
		{
			DelStructPai(stlist, i, 4);
			++usNum;
			return DelAAABACPai(stlist, usNum);
		}
	}

	if (stlist[usSize - 1].usNum >= 2)
	{
		DelStructPai(stlist, usSize - 1, 4);
		++usNum;
	}

	return true;
}

bool CMajingRule::DelAAAPai(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	for (uint16_t i = 0; i < usSize; ++i)
	{
		if (stlist[i].usNum >= 3)
		{
			DelStructPai(stlist, i, 3);
			return DelAAAPai(stlist);
		}
	}

	return true;
}

bool CMajingRule::DelAAAABCPai(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
		}

		return true;

		break;
	}
	case 2:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
			return DelAAAABCPai(stlist);
		}

		if (stlist[1].usNum >= 3)
		{
			DelStructPai(stlist, 1, 3);
		}

		return true;

		break;
	}
	default:
		break;
	}

	for (uint16_t i = 0; i < usSize - 2; ++i)
	{
		if (stlist[i].usNum >= 3)
		{
			DelStructPai(stlist, i, 3);
			return DelAAAABCPai(stlist);
		}

		if (CheckABCPai(stlist[i].usPai, stlist[i + 1].usPai, stlist[i + 2].usPai))
		{
			DelStructPai(stlist, i, 1);
			return DelAAAABCPai(stlist);
		}
	}

	if (stlist[usSize - 2].usNum >= 3)
	{
		DelStructPai(stlist, usSize - 2, 3);
	}

	usSize = stlist.size();
	if (stlist[usSize - 1].usNum >= 3)
	{
		DelStructPai(stlist, usSize - 1, 3);
	}

	return true;
}

bool CMajingRule::DelAAAABCPai_ting(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
		}

		return true;

		break;
	}
	case 2:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
			return DelAAAABCPai_ting(stlist);
		}

		if (stlist[1].usNum >= 3)
		{
			DelStructPai(stlist, 1, 3);
		}

		return true;

		break;
	}
	case 4:
	{
		if (stlist[0].usNum == stlist[1].usNum &&
			stlist[1].usNum == stlist[2].usNum &&
			stlist[2].usNum == stlist[3].usNum &&
			CheckABCDPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai, stlist[3].usPai))
		{
			return true;
		}

		break;
	}
	default:
		break;
	}

	if (stlist[0].usNum >= 3)
	{
		DelStructPai(stlist, 0, 3);
		return DelAAAABCPai_ting(stlist);
	}

	if (CheckABCPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai))
	{
		DelStructPai(stlist, 0, 1);
		return DelAAAABCPai_ting(stlist);
	}

	return true;
}

bool CMajingRule::DelAAAABCPaiEx(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
		}

		return true;

		break;
	}
	case 2:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
			return DelAAAABCPaiEx(stlist);
		}

		if (stlist[1].usNum >= 3)
		{
			DelStructPai(stlist, 1, 3);
		}

		return true;

		break;
	}
	default:
		break;
	}

	for (uint16_t i = usSize - 1; i >= 2; --i)
	{
		if (stlist[i].usNum >= 3)
		{
			DelStructPai(stlist, i, 3);
			return DelAAAABCPaiEx(stlist);
		}

		if (CheckABCPai(stlist[i - 2].usPai, stlist[i - 1].usPai, stlist[i].usPai))
		{
			DelStructPai(stlist, i - 2, 1);
			return DelAAAABCPaiEx(stlist);
		}
	}

	if (stlist[1].usNum >= 3)
	{
		DelStructPai(stlist, 1, 3);
	}

	if (stlist[0].usNum >= 3)
	{
		DelStructPai(stlist, 0, 3);
	}

	return true;
}

bool CMajingRule::DelAAAABCPaiEx_ting(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
		}

		return true;

		break;
	}
	case 2:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
			return DelAAAABCPaiEx_ting(stlist);
		}

		if (stlist[1].usNum >= 3)
		{
			DelStructPai(stlist, 1, 3);
		}

		return true;

		break;
	}
	case 4:
	{
		if (stlist[0].usNum == stlist[1].usNum &&
			stlist[1].usNum == stlist[2].usNum &&
			stlist[2].usNum == stlist[3].usNum &&
			CheckABCDPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai, stlist[3].usPai))
		{
			return true;
		}

		break;
	}
	default:
		break;
	}

	if (stlist[usSize - 1].usNum >= 3)
	{
		DelStructPai(stlist, usSize - 1, 3);
		return DelAAAABCPaiEx_ting(stlist);
	}

	if (CheckABCPai(stlist[usSize - 3].usPai, stlist[usSize - 2].usPai, stlist[usSize - 1].usPai))
	{
		DelStructPai(stlist, usSize - 3, 1);
		return DelAAAABCPaiEx_ting(stlist);
	}

	return true;
}

bool CMajingRule::DelAAAABCJC_ting(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
		}

		return true;

		break;
	}
	case 2:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
			return DelAAAABCJC_ting(stlist);
		}

		if (stlist[1].usNum >= 3)
		{
			DelStructPai(stlist, 1, 3);
		}

		return true;

		break;
	}
	default:
		break;
	}

	if (stlist[0].usNum >= 3)
	{
		DelStructPai(stlist, 0, 3);
		return DelAAAABCJC_ting(stlist);
	}

	if (stlist[0].usNum > stlist[1].usNum || stlist[0].usNum > stlist[2].usNum)
	{
		return true;
	}

	if (CheckABCPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai))
	{
		DelStructPai(stlist, 0, 1);
		return DelAAAABCJC_ting(stlist);
	}

	return true;
}

bool CMajingRule::DelAAAABCHead_ting(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
		}

		return true;

		break;
	}
	case 2:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
			return DelAAAABCHead_ting(stlist);
		}

		if (stlist[1].usNum >= 3)
		{
			DelStructPai(stlist, 1, 3);
		}

		return true;

		break;
	}
	case 4:
	{
		if (stlist[0].usNum == stlist[1].usNum &&
			stlist[1].usNum == stlist[2].usNum &&
			stlist[2].usNum == stlist[3].usNum &&
			CheckABCDPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai, stlist[3].usPai))
		{
			return true;
		}

		break;
	}
	default:
		break;
	}

	if (stlist[0].usNum >= 3)
	{
		DelStructPai(stlist, 0, 3);
		return DelAAAABCHead_ting(stlist);
	}

	if (stlist[0].usPai % 10 != 1)
	{
		return true;
	}

	if (stlist[0].usNum >= 3)
	{
		DelStructPai(stlist, 0, 3);
		return DelAAAABCHead_ting(stlist);
	}

	if (CheckABCPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai))
	{
		DelStructPai(stlist, 0, 1);
		return DelAAAABCHead_ting(stlist);
	}

	return true;
}

bool CMajingRule::DelAAAABCJCEx_ting(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
		}

		return true;

		break;
	}
	case 2:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
			return DelAAAABCPaiEx(stlist);
		}

		if (stlist[1].usNum >= 3)
		{
			DelStructPai(stlist, 1, 3);
		}

		return true;

		break;
	}
	default:
		break;
	}

	if (stlist[usSize - 1].usNum >= 3)
	{
		DelStructPai(stlist, usSize - 1, 3);
		return DelAAAABCPaiEx(stlist);
	}

	if (stlist[usSize - 1].usNum > stlist[usSize - 2].usNum || stlist[usSize - 1].usNum > stlist[usSize - 3].usNum)
	{
		return true;
	}

	if (CheckABCPai(stlist[usSize - 3].usPai, stlist[usSize - 2].usPai, stlist[usSize - 1].usPai))
	{
		DelStructPai(stlist, usSize - 3, 1);
		return DelAAAABCPaiEx(stlist);
	}

	return true;
}

bool CMajingRule::DelAAAABCHeadEx_ting(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
		}

		return true;

		break;
	}
	case 2:
	{
		if (stlist[0].usNum >= 3)
		{
			DelStructPai(stlist, 0, 3);
			return DelAAAABCHeadEx_ting(stlist);
		}

		if (stlist[1].usNum >= 3)
		{
			DelStructPai(stlist, 1, 3);
		}

		return true;

		break;
	}
	case 4:
	{
		if (stlist[0].usNum == stlist[1].usNum &&
			stlist[1].usNum == stlist[2].usNum &&
			stlist[2].usNum == stlist[3].usNum &&
			CheckABCDPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai, stlist[3].usPai))
		{
			return true;
		}

		break;
	}
	default:
		break;
	}

	if (stlist[usSize - 1].usNum >= 3)
	{
		DelStructPai(stlist, usSize - 1, 3);
		return DelAAAABCHeadEx_ting(stlist);
	}

	if (stlist[usSize - 1].usPai % 10 != 9)
	{
		return true;
	}

	if (stlist[usSize - 1].usNum >= 3)
	{
		DelStructPai(stlist, usSize - 1, 3);
		return DelAAAABCHeadEx_ting(stlist);
	}

	if (CheckABCPai(stlist[usSize - 3].usPai, stlist[usSize - 2].usPai, stlist[usSize - 1].usPai))
	{
		DelStructPai(stlist, usSize - 3, 1);
		return DelAAAABCHeadEx_ting(stlist);
	}

	return true;
}

bool CMajingRule::DelABCPai(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	if (usSize < 3)
	{
		return true;
	}

	for (uint16_t i = 0; i < usSize - 2; ++i)
	{
		if (CheckABCPai(stlist[i].usPai, stlist[i + 1].usPai, stlist[i + 2].usPai))
		{
			DelStructPai(stlist, i, 1);
			return DelABCPai(stlist);
		}
	}

	return true;
}

bool CMajingRule::DelABCPaiEx(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	if (usSize < 3)
	{
		return true;
	}

	for (uint16_t i = usSize - 1; i >= 2; --i)
	{
		if (CheckABCPai(stlist[i - 2].usPai, stlist[i - 1].usPai, stlist[i].usPai))
		{
			DelStructPai(stlist, i - 2, 1);
			return DelABCPaiEx(stlist);
		}
	}

	return true;
}

bool CMajingRule::DelAAABACPai(vecCheckPai& stlist, uint16_t& usNum)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 2)
		{
			DelStructPai(stlist, 0, 4);
			++usNum;
		}

		return true;

		break;
	}
	default:
		break;
	}

	for (uint16_t i = 0; i < usSize - 1; ++i)
	{
		if (stlist[i].usNum >= 2)
		{
			DelStructPai(stlist, i, 4);
			++usNum;
			return DelAAABACPai(stlist, usNum);
		}

		if (stlist[i + 1].usPai - stlist[i].usPai <= 2)
		{
			DelStructPai(stlist, i, 2);
			++usNum;
			return DelAAABACPai(stlist, usNum);
		}
	}

	if (stlist[usSize - 1].usNum >= 2)
	{
		DelStructPai(stlist, usSize - 1, 4);
		++usNum;
	}

	return true;
}

bool CMajingRule::DelAAABACPaiEx(vecCheckPai& stlist, uint16_t& usNum)
{
	uint16_t usSize = stlist.size();
	switch (usSize)
	{
	case 0: return true;

	case 1:
	{
		if (stlist[0].usNum >= 2)
		{
			DelStructPai(stlist, 0, 4);
			++usNum;
		}

		return true;

		break;
	}
	default:
		break;
	}

	for (uint16_t i = usSize - 1; i >= 1; --i)
	{
		if (stlist[i].usNum >= 2)
		{
			DelStructPai(stlist, i, 4);
			++usNum;
			return DelAAABACPaiEx(stlist, usNum);
		}

		if (stlist[i].usPai - stlist[i - 1].usPai <= 2)
		{
			DelStructPai(stlist, i - 1, 2);
			++usNum;
			return DelAAABACPaiEx(stlist, usNum);
		}
	}

	if (stlist[0].usNum >= 2)
	{
		DelStructPai(stlist, 0, 4);
		++usNum;
	}

	return true;
}

bool CMajingRule::DelAABBCC(vecCheckPai& stlist, uint16_t& usNum)
{
	uint16_t usSize = stlist.size();
	if (usSize < 3)
	{
		return false;
	}

	for (uint16_t i = 0; i <= usSize - 3; ++i)
	{
		if (CheckABCPai(stlist[i].usPai, stlist[i + 1].usPai, stlist[i + 2].usPai) &&
			stlist[i].usNum == 2 &&
			stlist[i + 1].usNum == 2 &&
			stlist[i + 2].usNum == 2)
		{
			uint16_t j = 0;
			for (vecCheckPai::iterator iter = stlist.begin(); iter != stlist.end(); ++iter)
			{
				if (j++ == i)
				{
					iter = stlist.erase(iter);
					iter = stlist.erase(iter);
					iter = stlist.erase(iter);
					return DelAABBCC(stlist, ++usNum);
				}
			}
		}
	}

	return false;
}

bool CMajingRule::DelAAAABC_Head(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();
	if (usSize >= 1 &&
		stlist[0].usNum == 3)
	{
		DelStructPai(stlist, 0, 3);
		return DelAAAABC_Head(stlist);
	}

	if (usSize >= 3 &&
		stlist[0].usNum == 2 &&
		stlist[1].usNum == 1 &&
		stlist[2].usNum == 1)
	{
		return true;
	}

	if (usSize >= 3 &&
		CheckABCPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai))
	{
		DelStructPai(stlist, 0, 1);
		return DelAAAABC_Head(stlist);
	}

	return true;
}

bool CMajingRule::DelAAAC_Head(vecCheckPai& stlist)
{
	uint16_t usSize = stlist.size();

	if (usSize >= 1 &&
		stlist[0].usNum == 2)
	{
		DelStructPai(stlist, 0, 4);
		return true;
	}

	if (usSize >= 2 &&
		stlist[0].usNum == 1 &&
		stlist[1].usPai - stlist[0].usPai == 2)
	{
		DelStructPai(stlist, 0, 2);
		return true;
	}

	return false;
}

void CMajingRule::CheckAnGang(const std::vector<uint16_t>& pailist, std::vector<uint16_t>& agpailist)
{
	//LOG(WARNING) << "CheckAnGang() size: " << pailist.size();

	if (pailist.size() < 5)
	{
		return;
	}

	for (uint16_t i = 0; i < pailist.size() - 3;)
	{
		if (CheckAAAAPai(pailist[i], pailist[i+1], pailist[i+2], pailist[i+3]))
		{
			agpailist.push_back(pailist[i]);
			i += 4;	
		}
		else
		{
			++i;
		}
	}
}

bool CMajingRule::CheckGangPai(const std::vector<uint16_t>& pailist, uint16_t usPai)
{
	//LOG(WARNING) << "CheckGangPai() size: " << pailist.size();

	if (pailist.size() < 4)
	{
		return false;
	}

	for (uint16_t i = 0; i < pailist.size() - 2; ++i)
	{
		if (CheckAAAAPai(pailist[i], pailist[i+1], pailist[i+2], usPai))
		{
			return true;
		}
	}

	return false;
}

bool CMajingRule::CheckPengPai(const std::vector<uint16_t>& pailist, uint16_t usPai)
{
	//LOG(WARNING) << "CheckPengPai() size: " << pailist.size();

	if (pailist.size() < 4)
	{
		return false;
	}

	for (uint16_t i = 0; i < pailist.size() - 1; ++i)
	{
		if (CheckAAAPai(pailist[i], pailist[i+1], usPai))
		{
			return true;
		}
	}

	return false;
}

bool CMajingRule::CheckEatPai(const std::vector<uint16_t>& pailist, uint16_t usPai, std::set<uint16_t>& out_eatlist)
{
	if (pailist.size() < 2)
	{
		return false;
	}

	if (usPai < 10)
	{
		return false;
	}

	std::vector<uint16_t> copy_pailist(pailist);

	bool bFind = false;
	for (std::vector<uint16_t>::iterator iter = copy_pailist.begin(); iter != copy_pailist.end(); ++iter)
	{
		if ((*iter) > usPai)
		{
			copy_pailist.insert(iter, usPai);
			bFind = true;
			break;
		}
	}
	if (!bFind)
	{
		copy_pailist.push_back(usPai);
	}

	for (int i = 0; i < copy_pailist.size() + 1 - 3; ++i )
	{
		if (copy_pailist[i] == usPai || copy_pailist[i + 1] == usPai || copy_pailist[i + 2] == usPai)
		{
			if (CheckABCPai(copy_pailist[i], copy_pailist[i + 1], copy_pailist[i + 2]))
			{
				out_eatlist.insert(copy_pailist[i]);
			}
		}
	}

	return !out_eatlist.empty();
}

void CMajingRule::DelHasCheckPai(std::vector<uint16_t>& pailist, uint16_t usStartIndex, uint16_t usNum)
{
	if (pailist.size() == 0 ||
		usStartIndex >= pailist.size() ||
		usNum > (pailist.size() - usStartIndex))
	{
		return;
	}

	uint16_t usIndex = 0;
	for (std::vector<uint16_t>::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (usIndex++ == usStartIndex)
		{
			for (uint16_t i = 0; i < usNum; ++i)
			{
				iter = pailist.erase(iter);
			}
			break;
		}
	}
}

bool CMajingRule::CheckHupai_PingHu(const std::vector<uint16_t>& pailist)
{
	for (uint16_t i = 0; i < pailist.size() - 1; ++i)
	{
		if (pailist[i] != pailist[i+1])
		{
			continue;
		}

		std::vector<uint16_t> pailist_copy = pailist;
		DelHasCheckPai(pailist_copy, i, 2);

		vecCheckPai stpailist;
		ChangeStructPai(pailist_copy, stpailist);
		if (CheckStructPai(stpailist))
		{
			return true;
		}	
	}

	return false;
}

bool CMajingRule::CheckHupai_PingHu_AbcJJ19(const std::vector<uint16_t>& pailist)
{
	for (uint16_t i = 0; i < pailist.size() - 1; ++i)
	{
		if (pailist[i] != pailist[i + 1])
		{
			continue;
		}
		else
		{
			if (!Is1Or9(pailist[i]))
			{
				continue;
			}
		}

		std::vector<uint16_t> pailist_copy = pailist;
		DelHasCheckPai(pailist_copy, i, 2);

		vecCheckPai stpailist;
		ChangeStructPai(pailist_copy, stpailist);

		if (CheckStructPai1Or9(stpailist))
		{
			return true;
		}
	}
	return false;
}

bool CMajingRule::CheckHupai_PingHu_Jiang258(const std::vector<uint16_t>& pailist)
{
	for (uint16_t i = 0; i < pailist.size() - 1; ++i)
	{
		if (pailist[i] != pailist[i + 1])
		{
			continue;
		}

		if (!Is258(pailist[i]))
		{
			continue;
		}

		std::vector<uint16_t> pailist_copy = pailist;
		DelHasCheckPai(pailist_copy, i, 2);

		vecCheckPai stpailist;
		ChangeStructPai(pailist_copy, stpailist);
		if (CheckStructPai(stpailist))
		{
			return true;
		}
	}
	return false;
}

uint16_t CMajingRule::CheckNeedGhostNum(const vecCheckPai& stlist_yuan)
{
	uint16_t usNeedNum = 0;
	uint16_t usNum = 0;
	uint16_t usHeadNum = 0;

	// 顺向检测
	vecCheckPai stlist = stlist_yuan;
	DelAAAABCPai(stlist);
	usNum = 0;
	DelAAABACPai(stlist, usNum);
	usNeedNum = usNum + stlist.size() * 2;


	// 先删除ABC AC
	stlist = stlist_yuan;
	DelAAAABC_Head(stlist);
	usHeadNum = 0;
	if (DelAAAC_Head(stlist))
	{
		usHeadNum = 1;
	}
	DelAAAABCPai(stlist);
	usNum = 0;
	DelAAABACPai(stlist, usNum);
	uint16_t usNeedNum1 = usNum + stlist.size() * 2 + usHeadNum;
	if (usNeedNum1 < usNeedNum)
	{
		usNeedNum = usNeedNum1;
	}

	// 逆向检测 先删除 ABC AC
	stlist = stlist_yuan;
	uint16_t usSize = stlist.size();
	if (usSize >= 3 &&
		stlist[usSize - 1].usNum == 1 &&
		stlist[usSize - 2].usNum == 1 &&
		stlist[usSize - 3].usNum == 1 &&
		CheckABCPai(stlist[usSize - 3].usPai, stlist[usSize - 2].usPai, stlist[usSize - 1].usPai))
	{
		DelStructPai(stlist, usSize - 3, 1);
	}
	usHeadNum = 0;
	usSize = stlist.size();
	if (usSize >= 2 &&
		stlist[usSize - 1].usNum == 1 &&
		stlist[usSize - 1].usPai - stlist[usSize - 2].usPai == 2)
	{
		DelStructPai(stlist, usSize - 2, 2);
		usHeadNum = 1;
	}
	DelAAAABCPaiEx(stlist);
	usNum = 0;
	DelAAABACPaiEx(stlist, usNum);
	uint16_t usNeedNum_Ni = usNum + stlist.size() * 2 + usHeadNum;
	if (usNeedNum_Ni < usNeedNum)
	{
		usNeedNum = usNeedNum_Ni;
	}

	return usNeedNum;
}


uint16_t CMajingRule::CheckNeedGhostNum_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang)
{
	uint16_t usMinNum = 0;
	vecCheckPai stlist_copy = stlist_yuan;

	uint16_t usNum = 0;
	DelAABBCC(stlist_copy, usNum);
	if (stlist_copy.size() == 0)
	{
		return 2;
	}

	for (vecCheckPai::iterator iter = stlist_copy.begin(); iter != stlist_copy.end(); ++iter)
	{
		stCheckPai& st = *iter;
		if (st.usNum < 2)
		{
			continue;
		}

		vecCheckPai stlist_check = stlist_yuan;
		DelAAPai_Pai(stlist_check, st.usPai);
		usNum = CheckNeedGhostNum2_Jiang(stlist_check);
		if (usNum <= 0)
		{
			return 0;
		}

		if (usMinNum == 0)
		{
			usMinNum = usNum;
		}
		else
		{
			if (usNum < usMinNum)
			{
				usMinNum = usNum;
			}
		}
	}

	// 单个判断
	{
		bool bJiangEx = false;
		bool bJiang1 = false;
		usNum = CheckNeedGhostNum1_Jiang(stlist_yuan, bJiang1);
		bool bJiang2 = false;
		uint16_t usNum_Ni = CheckNeedGhostNum1_JiangEx(stlist_yuan, bJiang2);
		if (usNum_Ni < usNum)
		{
			usNum = usNum_Ni;
			bJiangEx = bJiang2;
		}
		else
		{
			bJiangEx = bJiang1;
		}

		if (usMinNum == 0 || usNum <= usMinNum)
		{
			bJiang = bJiangEx;
			usMinNum = usNum;
		}
	}

	return usMinNum;
}

uint16_t CMajingRule::CheckNeedGhostNum_Jiang_258(const vecCheckPai& stlist_yuan, bool& bJiang)
{
	uint16_t usMinNum = 0;
	vecCheckPai stlist_copy = stlist_yuan;

	uint16_t usNum = 0;
	DelAABBCC(stlist_copy, usNum);
	if (stlist_copy.size() == 0)
	{
		return 2;
	}

	for (vecCheckPai::iterator iter = stlist_copy.begin(); iter != stlist_copy.end(); ++iter)
	{
		stCheckPai& st = *iter;
		if (st.usNum < 2 || !Is258(st.usPai))
		{
			continue;
		}

		vecCheckPai stlist_check = stlist_yuan;
		DelAAPai_Pai(stlist_check, st.usPai);
		usNum = CheckNeedGhostNum2_Jiang(stlist_check);
		if (usNum <= 0)
		{
			return 0;
		}

		if (usMinNum == 0)
		{
			usMinNum = usNum;
		}
		else
		{
			if (usNum < usMinNum)
			{
				usMinNum = usNum;
			}
		}
	}

	// 单个判断
	{
		bool bJiangEx = false;
		bool bJiang1 = false;
		usNum = CheckNeedGhostNum1_Jiang(stlist_yuan, bJiang1);
		bool bJiang2 = false;
		uint16_t usNum_Ni = CheckNeedGhostNum1_JiangEx(stlist_yuan, bJiang2);
		if (usNum_Ni < usNum)
		{
			usNum = usNum_Ni;
			bJiangEx = bJiang2;
		}
		else
		{
			bJiangEx = bJiang1;
		}

		if (usMinNum == 0 || usNum <= usMinNum)
		{
			bJiang = bJiangEx;
			usMinNum = usNum;
		}
	}

	return usMinNum;
}

uint16_t CMajingRule::CheckNeedGhostNum1_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang)
{
	vecCheckPai stlist = stlist_yuan;
	DelAAAABCPai(stlist);

	uint16_t usNum = 0;
	DelAAABACPai(stlist, usNum);

	bJiang = true;

	if (stlist.size() > 0)
	{
		return usNum + (stlist.size() - 1) * 2 + 1;
	}

	if (usNum > 0)
	{
		return usNum - 1 + 2 + 1;
	}

	return 1 + 1;
}

uint16_t CMajingRule::CheckNeedGhostNum1_JiangEx(const vecCheckPai& stlist_yuan, bool& bJiang)
{
	vecCheckPai stlist = stlist_yuan;
	DelAAAABCPaiEx(stlist);

	uint16_t usNum = 0;
	DelAAABACPaiEx(stlist, usNum);

	bJiang = true;

	if (stlist.size() > 0)
	{
		return usNum + (stlist.size() - 1) * 2 + 1;
	}

	if (usNum > 0)
	{
		return usNum - 1 + 2 + 1;
	}

	return 1 + 1;
}

uint16_t CMajingRule::CheckNeedGhostNum2_Jiang(const vecCheckPai& stlist_yuan)
{
	uint16_t usNeedNum = 0;
	uint16_t usNum = 0;

	// 顺向删除
	vecCheckPai stlist = stlist_yuan;
	DelAAAABCPai(stlist);
	usNum = 0;
	DelAAABACPai(stlist, usNum);
	usNeedNum = usNum + stlist.size() * 2;

	// 先删除ABC AC
	stlist = stlist_yuan;
	DelAAAABC_Head(stlist);
	uint16_t usHeadNum = 0;
	if (DelAAAC_Head(stlist))
	{
		usHeadNum = 1;
	}
	DelAAAABCPai(stlist);
	usNum = 0;
	DelAAABACPai(stlist, usNum);
	uint16_t usNeedNum4 = usNum + stlist.size() * 2 + usHeadNum;
	if (usNeedNum4 < usNeedNum)
	{
		usNeedNum = usNeedNum4;
	}

	// 逆向 先删除 ABC AC
	stlist = stlist_yuan;
	uint16_t usSize = stlist.size();
	if (usSize >= 3 &&
		stlist[usSize - 1].usNum == 1 &&
		stlist[usSize - 2].usNum == 1 &&
		stlist[usSize - 3].usNum == 1 &&
		CheckABCPai(stlist[usSize - 3].usPai, stlist[usSize - 2].usPai, stlist[usSize - 1].usPai))
	{
		DelStructPai(stlist, usSize - 3, 1);
	}
	usHeadNum = 0;
	usSize = stlist.size();
	if (usSize >= 2 &&
		stlist[usSize - 1].usNum == 1 &&
		stlist[usSize - 1].usPai - stlist[usSize - 2].usPai == 2)
	{
		DelStructPai(stlist, usSize - 2, 2);
		usHeadNum = 1;
	}
	DelAAAABCPaiEx(stlist);
	usNum = 0;
	DelAAABACPaiEx(stlist, usNum);
	uint16_t usNeedNum_Ni = usNum + stlist.size() * 2 + usHeadNum;
	if (usNeedNum_Ni < usNeedNum)
	{
		usNeedNum = usNeedNum_Ni;
	}

	return usNeedNum;
}

uint16_t CMajingRule::CheckNeedGhostNumZi(const vecCheckPai& zilist_yuan)
{
	/*vecCheckPai zilist = zilist_yuan;
	DelAAAPai(zilist);
	uint16_t usNum = 0;
	DelAAPai_Num(zilist, usNum);
	return usNum + zilist.size() * 2;*/

	uint16_t usNum1 = 0, usNum2 = 0;
	for (vecCheckPai::const_iterator iter = zilist_yuan.begin(); iter != zilist_yuan.end(); ++iter)
	{
		switch ((*iter).usNum)
		{
		case 1: ++usNum1; break;
		case 2: ++usNum2; break;
		case 3: break;
		case 4: ++usNum1; break;
		default: break;
		}
	}

	return usNum1 * 2 + usNum2;
}

uint16_t CMajingRule::CheckNeedGhostNumZi_Jiang(const vecCheckPai& stlist_yuan, bool& bJiang)
{
	/*vecCheckPai stlist = stlist_yuan;
	uint16_t usNeedJiangGhost = 1;
	if (DelAAPai_NULL(stlist))
	{
	usNeedJiangGhost = 0;
	}
	DelAAAPai(stlist);
	uint16_t usNum = 0;
	DelAAPai_Num(stlist, usNum);
	if (stlist.size() > 0)
	{
	return usNum + (stlist.size() - 1) * 2 + usNeedJiangGhost;
	}
	if (usNum > 0)
	{
	if (usNeedJiangGhost == 0)
	{
	return usNum;
	}
	else
	{
	return usNum - 1 + 2 + usNeedJiangGhost;
	}
	}
	uint16_t usDecABC = 0;
	if (usNeedJiangGhost == 1)
	{
	usDecABC = 1;
	}
	return usDecABC + usNeedJiangGhost;*/

	uint16_t usNum1 = 0, usNum2 = 0, usNum3 = 0, usNum4 = 0;
	for (vecCheckPai::const_iterator iter = stlist_yuan.begin(); iter != stlist_yuan.end(); ++iter)
	{
		switch ((*iter).usNum)
		{
		case 1: ++usNum1; break;
		case 2: ++usNum2; break;
		case 3: ++usNum3; break;
		case 4: ++usNum4; break;
		default: break;
		}
	}

	if (usNum2 > 0)
	{
		--usNum2;
		return usNum1 * 2 + usNum2 * 1 + usNum4 * 2;
	}

	if (usNum1 > 0)
	{
		--usNum1;
		bJiang = true;
		return 1 + usNum1 * 2 + usNum4 * 2;
	}

	if (usNum4 > 0)
	{
		--usNum4;
		bJiang = true;
		return 1 + usNum4 * 2;
	}

	return 2;
}

bool CMajingRule::CheckHupai_PingHu_Ghost(const std::vector<uint16_t>& pailist)
{
	uint16_t usGhostNum = 0;
	vecCheckPai zilist, tonglist, tiaolist, wanlist;
	ChangeStructPai_Ex(pailist, usGhostNum, zilist, tonglist, tiaolist, wanlist);
	
	if (usGhostNum > 0 && 
		zilist.size() == 0 &&
		tonglist.size() == 0 &&
		tiaolist.size() == 0 &&
		wanlist.size() == 0)
	{
		return true;
	}

	uint16_t usNeedGhostNum = 0;

	uint16_t usNumZi = CheckNeedGhostNumZi(zilist);
	bool bJiang_zi = false;
	uint16_t usNumZi_Jiang = CheckNeedGhostNumZi_Jiang(zilist, bJiang_zi);

	uint16_t usNumTong = CheckNeedGhostNum(tonglist);
	bool bJiang_tong = false;
	uint16_t usNumTong_Jiang = CheckNeedGhostNum_Jiang(tonglist, bJiang_tong);

	uint16_t usNumTiao = CheckNeedGhostNum(tiaolist);
	bool bJiang_tiao = false;
	uint16_t usNumTiao_Jiang = CheckNeedGhostNum_Jiang(tiaolist, bJiang_tiao);

	uint16_t usNumWan = CheckNeedGhostNum(wanlist);
	bool bJiang_wan = false;
	uint16_t usNumWan_Jiang = CheckNeedGhostNum_Jiang(wanlist, bJiang_wan);

	//LOG(WARNING) << "=====: " << zilist.size() << " " << tonglist.size() << " " << tiaolist.size() << " " << wanlist.size();

	//将牌在风中
	if (zilist.size() > 0)
	{
		usNeedGhostNum = usNumZi_Jiang + usNumTong + usNumTiao + usNumWan;
		if (usNeedGhostNum <= usGhostNum)
		{
			return true;
		}
	}

	//将在筒中
	if (tonglist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong_Jiang + usNumTiao + usNumWan;
		if (usNeedGhostNum <= usGhostNum)
		{
			return true;
		}
	}

	//将在条中
	if (tiaolist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong + usNumTiao_Jiang + usNumWan;
		if (usNeedGhostNum <= usGhostNum)
		{
			return true;
		}
	}

	//将在万中
	if (wanlist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong + usNumTiao + usNumWan_Jiang;
		if (usNeedGhostNum <= usGhostNum)
		{
			return true;
		}
	}

	return false;
}

bool CMajingRule::CheckHupai_PingHu_Ghost_Jiang258(const std::vector<uint16_t>& pailist)
{
	uint16_t usGhostNum = 0;
	vecCheckPai zilist, tonglist, tiaolist, wanlist;
	ChangeStructPai_Ex(pailist, usGhostNum, zilist, tonglist, tiaolist, wanlist);

	if (usGhostNum > 0 &&
		zilist.size() == 0 &&
		tonglist.size() == 0 &&
		tiaolist.size() == 0 &&
		wanlist.size() == 0)
	{
		return true;
	}

	uint16_t usNeedGhostNum = 0;

	uint16_t usNumZi = CheckNeedGhostNumZi(zilist);
	bool bJiang_zi = false;
	uint16_t usNumZi_Jiang = CheckNeedGhostNumZi_Jiang(zilist, bJiang_zi);

	uint16_t usNumTong = CheckNeedGhostNum(tonglist);
	bool bJiang_tong = false;
	uint16_t usNumTong_Jiang = CheckNeedGhostNum_Jiang_258(tonglist, bJiang_tong);

	uint16_t usNumTiao = CheckNeedGhostNum(tiaolist);
	bool bJiang_tiao = false;
	uint16_t usNumTiao_Jiang = CheckNeedGhostNum_Jiang_258(tiaolist, bJiang_tiao);

	uint16_t usNumWan = CheckNeedGhostNum(wanlist);
	bool bJiang_wan = false;
	uint16_t usNumWan_Jiang = CheckNeedGhostNum_Jiang_258(wanlist, bJiang_wan);

	//LOG(WARNING) << "=====: " << zilist.size() << " " << tonglist.size() << " " << tiaolist.size() << " " << wanlist.size();

	//将牌在风中
	//if (zilist.size() > 0)
	//{
	//	usNeedGhostNum = usNumZi_Jiang + usNumTong + usNumTiao + usNumWan;
	//	if (usNeedGhostNum <= usGhostNum)
	//	{
	//		return true;
	//	}
	//}

	//将在筒中
	if (tonglist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong_Jiang + usNumTiao + usNumWan;
		if (usNeedGhostNum <= usGhostNum)
		{
			return true;
		}
	}

	//将在条中
	if (tiaolist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong + usNumTiao_Jiang + usNumWan;
		if (usNeedGhostNum <= usGhostNum)
		{
			return true;
		}
	}

	//将在万中
	if (wanlist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong + usNumTiao + usNumWan_Jiang;
		if (usNeedGhostNum <= usGhostNum)
		{
			return true;
		}
	}

	return false;
}

bool CMajingRule::CheckHupai_QiDui(const std::vector<uint16_t>& pailist)
{
	if (pailist.size() != 14)
	{
		return false;
	}

	for (uint16_t i = 0; i < 7; ++i)
	{
		if (pailist[i*2] != pailist[i*2+1])
		{
			return false;
		}
	}

	return true;
}

uint16_t CMajingRule::GetQiDuiType(const std::vector<uint16_t>& pailist, uint16_t usPai)
{
	if (pailist.size() != 14)
	{
		return false;
	}

	std::vector<uint16_t> pailist_copy = pailist;
	if (!IsGhostCard( usPai))
	{
		for (std::vector<uint16_t>::iterator iter = pailist_copy.begin(); iter != pailist_copy.end(); ++iter)
		{
			if (*iter == usPai)
			{
				pailist_copy.erase(iter);
				break;
			}
		}
	}

	uint16_t usGhostNum = 0;
	vecCheckPai zilist, tonglist, tiaolist, wanlist;
	ChangeStructPai_Ex(pailist_copy, usGhostNum, zilist, tonglist, tiaolist, wanlist);

	uint16_t usNeedGhostNum = 0;
	for (vecCheckPai::const_iterator it = zilist.begin(); it != zilist.end(); ++it)
	{
		if (it->usNum == 1 || it->usNum == 3) usNeedGhostNum++;
	}
	for (vecCheckPai::const_iterator it = tonglist.begin(); it != tonglist.end(); ++it)
	{
		if (it->usNum == 1 || it->usNum == 3) usNeedGhostNum++;
	}
	for (vecCheckPai::const_iterator it = tiaolist.begin(); it != tiaolist.end(); ++it)
	{
		if (it->usNum == 1 || it->usNum == 3) usNeedGhostNum++;
	}
	for (vecCheckPai::const_iterator it = wanlist.begin(); it != wanlist.end(); ++it)
	{
		if (it->usNum == 1 || it->usNum == 3) usNeedGhostNum++;
	}

	if (IsGhostCard( usPai))
	{
		if (usGhostNum >= 2 && usNeedGhostNum <= usGhostNum - 2)
		{
			return 2;
		}

		if (usGhostNum >= 1)
		{
			if (usNeedGhostNum <= usGhostNum) // 
			{
				return 1;
			}
		}
	}
	else
	{
		if (usGhostNum >= 1 && usNeedGhostNum <= usGhostNum - 1)
		{
			return 1;
		}
	}
	return 0;
}

uint16_t CMajingRule::GetPingHuType(const std::vector<uint16_t>& pailist, uint16_t usPai)
{
	std::vector<uint16_t> pailist_copy = pailist;
	if (!IsGhostCard( usPai))
	{
		for (std::vector<uint16_t>::iterator iter = pailist_copy.begin(); iter != pailist_copy.end(); ++iter)
		{
			if (*iter == usPai)
			{
				pailist_copy.erase(iter);
				break;
			}
		}
	}

	uint16_t usGhostNum = 0;
	vecCheckPai zilist, tonglist, tiaolist, wanlist;
	ChangeStructPai_Ex(pailist_copy, usGhostNum, zilist, tonglist, tiaolist, wanlist);

	uint16_t usNumZi = CheckNeedGhostNumZi(zilist);
	uint16_t usNumTong = CheckNeedGhostNum(tonglist);
	uint16_t usNumTiao = CheckNeedGhostNum(tiaolist);
	uint16_t usNumWan = CheckNeedGhostNum(wanlist);

	uint16_t usNeedGhostNum = usNumZi + usNumTong + usNumTiao + usNumWan;

	if (IsGhostCard( usPai))
	{
		if (usGhostNum >= 2 && usNeedGhostNum <= usGhostNum - 2)
		{
			return 2;
		}

		if (usGhostNum >= 1)
		{
			bool bJiang = false;
			bool bJiang_zi = false;
			uint16_t usNumZi_Jiang = CheckNeedGhostNumZi_Jiang(zilist, bJiang_zi);
			bool bJiang_tong = false;
			uint16_t usNumTong_Jiang = CheckNeedGhostNum_Jiang(tonglist, bJiang_tong);
			bool bJiang_tiao = false;
			uint16_t usNumTiao_Jiang = CheckNeedGhostNum_Jiang(tiaolist, bJiang_tiao);
			bool bJiang_wan = false;
			uint16_t usNumWan_Jiang = CheckNeedGhostNum_Jiang(wanlist, bJiang_wan);

			usNeedGhostNum = usNumZi_Jiang + usNumTong + usNumTiao + usNumWan;
			bJiang = bJiang_zi;
			uint16_t usNeedGhostNum1 = usNumZi + usNumTong_Jiang + usNumTiao + usNumWan;
			if (usNeedGhostNum1 < usNeedGhostNum)
			{
				bJiang = bJiang_tong;
			}
			usNeedGhostNum1 = usNumZi + usNumTong + usNumTiao_Jiang + usNumWan;
			if (usNeedGhostNum1 < usNeedGhostNum)
			{
				bJiang = bJiang_tiao;
			}
			usNeedGhostNum1 = usNumZi + usNumTong + usNumTiao + usNumWan_Jiang;
			if (usNeedGhostNum1 < usNeedGhostNum)
			{
				bJiang = bJiang_wan;
			}

			if (bJiang)
			{
				return 1;
			}
		}	
	}
	else
	{
		if (usGhostNum >= 1 && usNeedGhostNum <= usGhostNum - 1)
		{
			return 1;
		}
	}

	return 0;
}

bool CMajingRule::CheckHupai_QuangFeng(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	int16_t nGhostNum = 0;
	int16_t nFengTouNum = 0;
	for (std::vector<uint16_t>::const_iterator it = pailist.begin(); it != pailist.end(); ++it)
	{
		if (bGhost && IsGhostCard((*it)))
		{
			nGhostNum++;
		}
		else
		{
			if ((*it) / 10 == eCardType_Zi)
			{
				nFengTouNum++;
			}
		}
	}

	for (vecEventPai::const_iterator it = eventpailist.begin(); it != eventpailist.end(); ++it)
	{
		if (it->usPai / 10 == eCardType_Zi)
		{
			nFengTouNum++;
		}
	}

	if (bGhost)
	{
		return  nGhostNum >= (pailist.size() + eventpailist.size() - nFengTouNum);
	}
	else
	{
		return pailist.size() + eventpailist.size() == nFengTouNum;
	}
}

bool CMajingRule::CheckHupai_QiDui_Ghost(const std::vector<uint16_t>& pailist)
{
	if (pailist.size() != 14)
	{
		return ::msg_maj::hu_none;
	}

	vecCheckPai stpailist;
	ChangeStructPai(pailist, stpailist);
	uint16_t usSameNum = 0;
	uint16_t usGhostNum = 0;
	for (vecCheckPai::iterator iter = stpailist.begin(); iter != stpailist.end(); ++iter)
	{
		stCheckPai& st = *iter;
		if (IsGhostCard( st.usPai))
		{
			usGhostNum += st.usNum;
		}
		else
		{
			usSameNum += st.usNum / 2;
		}
	}

	if (usGhostNum < 7 - usSameNum)
	{
		return false;
	}

	return true;
}

bool CMajingRule::CheckHupai_13yao(const std::vector<uint16_t>& pailist)
{
	if (pailist.size() != 14)
	{
		return false;
	}

	for (uint16_t i = 0; i < pailist.size() - 1; ++i)
	{
		if (pailist[i] != pailist[i + 1])
		{
			continue;
		}

		if (pailist[i] < 10 || pailist[i] % 10 == 1 || pailist[i] % 10 == 9)
		{
		}
		else
		{
			return false;
		}

		std::vector<uint16_t> pailist_copy = pailist;
		DelHasCheckPai(pailist_copy, i, 1);

		for (uint16_t i = 0; i < __13_YAO_NUM__; ++i)
		{
			if (pailist_copy[i] != g_majing_13yao[i])
			{
				return false;
			}
		}

		return true;
	}

	return false;
}

bool CMajingRule::Is258(uint16_t usPai)
{
	if (usPai > 10)
	{
		uint16_t remainPai = usPai % 10;
		if (remainPai == 2 || remainPai == 5 || remainPai == 8)
		{
			return true;
		}
	}
	return false;
}

bool CMajingRule::Is1Or9(uint16_t usPai)
{
	if (usPai > 10)
	{
		uint16_t remainPai = usPai % 10;
		if (remainPai == 1 || remainPai == 9)
		{
			return true;
		}
	}
	return false;
}

bool CMajingRule::CheckHupai_13yao_Ghost(const std::vector<uint16_t>& pailist)
{
	if (pailist.size() != 14)
	{
		return false;
	}

	std::set<uint16_t> setlist;
	uint16_t usSameNum = 0;
	uint16_t usGhostNum = 0;
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (IsGhostCard( *iter))
		{
			++usGhostNum;
		}
		else
		{
			if (*iter < 10 || *iter % 10 == 1 || *iter % 10 == 9)
			{
			}
			else
			{
				return false;
			}
			if (setlist.find(*iter) == setlist.end())
			{
				setlist.insert(*iter);
			}
			else
			{
				++usSameNum;
				if (usSameNum > 1)
				{
					return false;
				}
			}
		}
	}

	if (usGhostNum < 14 - usSameNum - setlist.size())
	{
		return false;
	}

	return true;
}

void CMajingRule::DelStructPai(vecCheckPai& pailist, uint16_t usPos, uint16_t usNum)
{
	switch (usNum)
	{
	case 1: //删除ABC
	{
		uint16_t i = 0;
		for (vecCheckPai::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
		{
			if (i == usPos)
			{
				(*iter).usNum -= 1;
				if ((*iter).usNum == 0)
				{
					iter = pailist.erase(iter);
				}
				else
				{
					++iter;
				}
				(*iter).usNum -= 1;
				if ((*iter).usNum == 0)
				{
					iter = pailist.erase(iter);
				}
				else
				{
					++iter;
				}
				(*iter).usNum -= 1;
				if ((*iter).usNum == 0)
				{
					iter = pailist.erase(iter);
				}
				else
				{
					++iter;
				}

				break;
			}
			++i;
		}
		break;
	}
	case 2: //删除ABAC
	{
		uint16_t i = 0;
		for (vecCheckPai::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
		{
			if (i == usPos)
			{
				(*iter).usNum -= 1;
				if ((*iter).usNum == 0)
				{
					iter = pailist.erase(iter);
				}
				else
				{
					++iter;
				}
				(*iter).usNum -= 1;
				if ((*iter).usNum == 0)
				{
					iter = pailist.erase(iter);
				}
				else
				{
					++iter;
				}

				break;
			}
			++i;
		}
		break;
	}
	case 3: //删除AAA
	{
		uint16_t i = 0;
		for (vecCheckPai::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
		{
			if (i == usPos)
			{
				(*iter).usNum -= 3;
				if ((*iter).usNum == 0)
				{
					iter = pailist.erase(iter);
				}
				break;
			}

			++i;
		}
		break;
	}
	case 4: //删除AA
	{
		uint16_t i = 0;
		for (vecCheckPai::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
		{
			if (i == usPos)
			{
				(*iter).usNum -= 2;
				if ((*iter).usNum == 0)
				{
					iter = pailist.erase(iter);
				}
				break;
			}

			++i;
		}
		break;
	}

	default:
		break;
	}
}

bool CMajingRule::CheckStructPai(vecCheckPai& pailist)
{
	if (pailist.size() <= 0)
	{
		return true;
	}

	switch (pailist[0].usNum)
	{
	case 1:
	case 2:
	{
		if (pailist[0].usPai / 10 == eCardType_Zi)
		{
			return false;
		}
		if (pailist.size() < 3)
		{
			return false;
		}
		if (!CheckABCPai(pailist[0].usPai, pailist[1].usPai, pailist[2].usPai))
		{
			return false;
		}

		DelStructPai(pailist, 0, 1);
		return CheckStructPai(pailist);

		break;
	}
	default:
	{
		DelStructPai(pailist, 0, 3);
		return CheckStructPai(pailist);

		break;
	}
	}

	return false;
}

bool CMajingRule::CheckStructPai1Or9(vecCheckPai& pailist)
{
	if (pailist.size() <= 0)
	{
		return true;
	}

	switch (pailist[0].usNum)
	{
	case 1:
	case 2:
	{
		if (pailist[0].usPai / 10 == eCardType_Zi)
		{
			return false;
		}
		if (pailist.size() < 3)
		{
			return false;
		}

		if (!Is1Or9(pailist[0].usPai) && !Is1Or9(pailist[1].usPai) && !Is1Or9(pailist[2].usPai))
		{
			return false;
		}

		if (!CheckABCPai(pailist[0].usPai, pailist[1].usPai, pailist[2].usPai))
		{
			return false;
		}

		DelStructPai(pailist, 0, 1);
		return CheckStructPai1Or9(pailist);

		break;
	}
	default:
	{
		DelStructPai(pailist, 0, 3);
		return CheckStructPai1Or9(pailist);

		break;
	}
	}

	return false;
}

bool CMajingRule::CheckHasStructPai(const vecCheckPai& pailist, uint16_t usPai)
{
	if (usPai == 0)
	{
		return false;
	}

	for (vecCheckPai::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if ((*iter).usPai == usPai)
		{
			return true;
		}
	}

	return false;
}

void CMajingRule::ChangeStructPai(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist)
{
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		bool bMark = false;
		for (vecCheckPai::iterator it = stpailist.begin(); it != stpailist.end(); ++it)
		{
			if ((*it).usPai == *iter)
			{
				(*it).usNum += 1;
				bMark = true;
				break;
			}
		}
		if (!bMark)
		{
			stCheckPai st;
			st.usPai = *iter;
			st.usNum = 1;
			stpailist.push_back(st);
		}
	}
}

void CMajingRule::ChangeStructPai_Ghost(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist, uint16_t& usGhostNum)
{
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (IsGhostCard( *iter))
		{
			++usGhostNum;
			continue;
		}

		bool bMark = false;
		for (vecCheckPai::iterator it = stpailist.begin(); it != stpailist.end(); ++it)
		{
			if ((*it).usPai == *iter)
			{
				(*it).usNum += 1;
				bMark = true;
				break;
			}
		}
		if (!bMark)
		{
			stCheckPai st;
			st.usPai = *iter;
			st.usNum = 1;
			stpailist.push_back(st);
		}
	}
}

void CMajingRule::ChangeStructPai_Ghost_Custom(const std::vector<uint16_t>& pailist, vecCheckPai& stpailist, uint16_t& usGhostNum, uint16_t usCusGhostPai)
{
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (usCusGhostPai == *iter)
		{
			++usGhostNum;
			continue;
		}

		bool bMark = false;
		for (vecCheckPai::iterator it = stpailist.begin(); it != stpailist.end(); ++it)
		{
			if ((*it).usPai == *iter)
			{
				(*it).usNum += 1;
				bMark = true;
				break;
			}
		}
		if (!bMark)
		{
			stCheckPai st;
			st.usPai = *iter;
			st.usNum = 1;
			stpailist.push_back(st);
		}
	}
}

void CMajingRule::ChangeStructPai_Ex(const std::vector<uint16_t>& pailist, uint16_t& usGhostNum, vecCheckPai& zilist, vecCheckPai& tonglist, vecCheckPai& tiaolist, vecCheckPai& wanlist)
{
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (IsGhostCard( *iter))
		{
			++usGhostNum;
			continue;
		}

		switch (*iter / 10)
		{
		case eCardType_Zi:
		{
			bool bMark = false;
			for (vecCheckPai::iterator it = zilist.begin(); it != zilist.end(); ++it)
			{
				if ((*it).usPai == *iter)
				{
					(*it).usNum += 1;
					bMark = true;
					break;
				}
			}
			if (!bMark)
			{
				stCheckPai st;
				st.usPai = *iter;
				st.usNum = 1;
				zilist.push_back(st);
			}
			break;
		}
		case eCardType_Tong:
		{
			bool bMark = false;
			for (vecCheckPai::iterator it = tonglist.begin(); it != tonglist.end(); ++it)
			{
				if ((*it).usPai == *iter)
				{
					(*it).usNum += 1;
					bMark = true;
					break;
				}
			}
			if (!bMark)
			{
				stCheckPai st;
				st.usPai = *iter;
				st.usNum = 1;
				tonglist.push_back(st);
			}
			break;
		}
		case eCardType_Tiao:
		{
			bool bMark = false;
			for (vecCheckPai::iterator it = tiaolist.begin(); it != tiaolist.end(); ++it)
			{
				if ((*it).usPai == *iter)
				{
					(*it).usNum += 1;
					bMark = true;
					break;
				}
			}
			if (!bMark)
			{
				stCheckPai st;
				st.usPai = *iter;
				st.usNum = 1;
				tiaolist.push_back(st);
			}
			break;
		}
		case eCardType_Wan:
		{
			bool bMark = false;
			for (vecCheckPai::iterator it = wanlist.begin(); it != wanlist.end(); ++it)
			{
				if ((*it).usPai == *iter)
				{
					(*it).usNum += 1;
					bMark = true;
					break;
				}
			}
			if (!bMark)
			{
				stCheckPai st;
				st.usPai = *iter;
				st.usNum = 1;
				wanlist.push_back(st);
			}
			break;
		}
		default:
			break;
		}
	}
}

void CMajingRule::GetSamePaiNumNum(const vecCheckPai& pailist, uint16_t& usNum1, uint16_t& usNum2, uint16_t& usNum3, uint16_t& usNum4)
{
	for (vecCheckPai::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		const stCheckPai& st = *iter;
		switch (st.usNum)
		{
		case 1: ++usNum1; break;
		case 2: ++usNum2; break;
		case 3: ++usNum3; break;
		case 4: ++usNum4; break;
		default:
			break;
		}
	}
}

// 混一色
bool CMajingRule::IsHys(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	uint16_t usCardType = 100;
	bool usCardTypeZi = false;
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (IsGhostCard( *iter) && bGhost)
			continue;

		uint16_t tmpType = (*iter) / 10;
		if (tmpType == eCardType_Zi)
			usCardTypeZi = true;
		else
		{
			if (usCardType == 100)
				usCardType = tmpType;
			else
			{
				if (tmpType != usCardType)
					return false;
			}
		}
	}

	for (vecEventPai::const_iterator iter = eventpailist.begin(); iter != eventpailist.end(); ++iter)
	{
		uint16_t tmpType = (*iter).usPai / 10;
		if (tmpType == eCardType_Zi)
			usCardTypeZi = true;
		else
		{
			if (usCardType == 100)
				usCardType = tmpType;
			else
			{
				if (tmpType != usCardType)
					return false;
			}
		}
	}
	return usCardTypeZi && usCardType != 100;
}

bool CMajingRule::IsQys(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	uint16_t usCardType = 100;
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (IsGhostCard( *iter) && bGhost)
		{
			continue;
		}

		if (!bGhost && (*iter) / 10 == eCardType_Zi)
		{
			return false;
		}

		if (usCardType == 100)
		{
			usCardType = (*iter) / 10;
		}
		else
		{
			if ((*iter) / 10 != usCardType)
			{
				return false;
			}
		}
	}

	for (vecEventPai::const_iterator iter = eventpailist.begin(); iter != eventpailist.end(); ++iter)
	{
		if ((*iter).usPai / 10 != usCardType)
		{
			return false;
		}
	}

	return true;
}

bool CMajingRule::IsDuanYj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	for (vecEventPai::const_iterator iter = eventpailist.begin(); iter != eventpailist.end(); ++iter)
	{
		const stEventPai& st = *iter;
		if (st.usPai % 10 == 1 || st.usPai % 10 == 9)
		{
			return false;
		}
	}

	uint16_t count1Or9 = 0;
	for (std::vector<uint16_t>::const_iterator it = pailist.begin(); it != pailist.end(); ++it)
	{
		uint16_t usPai = *it;
		if (usPai % 10 == 1 || usPai % 10 == 9)
		{
			return false;
		}
	}

	return true;
}

bool CMajingRule::IsDaiYj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	for (vecEventPai::const_iterator iter = eventpailist.begin(); iter != eventpailist.end(); ++iter)
	{
		const stEventPai& st = *iter;
		if (st.usPai % 10 != 1 || st.usPai % 10 != 9)
		{
			return false;
		}
	}

	if (pailist.size() == 2)
	{
		if (pailist[0] != pailist[1] || pailist[0] == 1 || pailist[0] == 9)
		{
			return false;
		}
	}
	else
	{
		uint16_t count1Or9 = 0;
		for (std::vector<uint16_t>::const_iterator it = pailist.begin(); it != pailist.end(); ++it)
		{
			uint16_t usPai = *it;
			if (usPai % 10 == 1 || usPai % 10 == 9)
			{
				count1Or9++;
			}
		}

		if (count1Or9 * 3 < pailist.size())
		{
			return false;
		}
	}

	return true;
}

bool CMajingRule::IsJingGG(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	return eventpailist.size() == 4;
}

// 杂幺九
bool CMajingRule::IsZyj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	bool usCardTypeZi = false;
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (IsGhostCard( *iter) && bGhost)
		{
			continue;
		}
		uint16_t tmpType = (*iter) / 10;
		if (tmpType == eCardType_Zi)
			usCardTypeZi = true;
		else
		{
			if ((*iter) % 10 != 1 && (*iter) % 10 != 9)
				return false;
		}
	}

	for (vecEventPai::const_iterator iter = eventpailist.begin(); iter != eventpailist.end(); ++iter)
	{
		uint16_t tmpType = (*iter).usPai / 10;
		if (tmpType == eCardType_Zi)
			usCardTypeZi = true;
		else
		{
			if ((*iter).usPai % 10 != 1 && (*iter).usPai % 10 != 9)
				return false;
		}
	}
	return usCardTypeZi;
}

// 全幺九
bool CMajingRule::IsQyj(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if (IsGhostCard( *iter) && bGhost)
		{
			continue;
		}
		if ((*iter) / 10 == eCardType_Zi)
		{
			return false;
		}
		if ((*iter) % 10 != 1 && (*iter) % 10 != 9)
		{
			return false;
		}
	}

	for (vecEventPai::const_iterator iter = eventpailist.begin(); iter != eventpailist.end(); ++iter)
	{
		if ((*iter).usPai / 10 == eCardType_Zi)
		{
			return false;
		}
		if ((*iter).usPai % 10 != 1 && (*iter).usPai % 10 != 9)
		{
			return false;
		}
	}

	return true;
}

//18罗汉
bool CMajingRule::Is18Lh(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	if (eventpailist.size() != 4)
	{
		return false;
	}
	for (vecEventPai::const_iterator iter = eventpailist.begin(); iter != eventpailist.end(); ++iter)
	{
		int16_t event_t = (*iter).usEventType;
		if (event_t != ::msg_maj::ming_gang && event_t != ::msg_maj::an_gang  && event_t != ::msg_maj::guo_shou_gang)
		{
			return false;
		}
	}
	return true;
}

uint16_t CMajingRule::CheckHhNum(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	uint16_t usGhostNum = 0;
	vecCheckPai stpailist;
	if (bGhost)
		ChangeStructPai_Ghost(pailist, stpailist, usGhostNum);
	else
		ChangeStructPai(pailist, stpailist);

	uint16_t usNum1 = 0, usNum2 = 0, usNum3 = 0, usNum4 = 0;
	GetSamePaiNumNum(stpailist, usNum1, usNum2, usNum3, usNum4);
	int32_t hasNumCount = 0;
	hasNumCount += usNum4;

	/*if (usGhostNum)
	{
		if (usNum1)
		{
			usGhostNum -= usNum1;
		}

		if (usNum3)
		{
			if (usNum3 < usGhostNum)
			{
				hasNumCount += usNum3; usGhostNum -= usNum3;
			}
			else
			{
				hasNumCount += usGhostNum; usGhostNum = 0;
			}
		}

		if (usNum2 && usGhostNum >= 2)
		{
			if (usGhostNum * 2 >= usNum2)
			{
				hasNumCount += 2; usGhostNum = 0;
			}
			else
			{
				hasNumCount += 1; usGhostNum -= 2;
			}
		}

		if (usNum1)
		{
			if (usGhostNum > 1)
			{
				hasNumCount += usGhostNum / 2;
				usGhostNum -= (usGhostNum / 2) * 2;
			}
		}

	}*/

	while (usGhostNum > 0)
	{
		if (usNum1 > 0)
		{
			usGhostNum -= usNum1;
			if (usGhostNum == 0)
			{
				break;
			}
		}

		if (usNum3 > 0)
		{
			hasNumCount += usNum3; 
			usGhostNum -= usNum3;
			if (usGhostNum == 0)
			{
				break;
			}
		}

		while (usNum2 > 0)
		{
			if (usGhostNum < 2)
			{
				break;
			}

			--usNum2;
			usGhostNum -= 2;
			++hasNumCount;
		}
		
		while (usNum1 > 0)
		{
			if (usGhostNum < 3)
			{
				break;
			}

			--usNum1;
			usGhostNum -= 3;
			++hasNumCount;
		}
	}

	return hasNumCount;
}

bool CMajingRule::IsHh(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	return CheckHhNum(pailist, eventpailist, bGhost) >= 1;
}

bool CMajingRule::IsHh2(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	return CheckHhNum(pailist, eventpailist, bGhost) >= 2;
}

bool CMajingRule::IsHh3(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	return CheckHhNum(pailist, eventpailist, bGhost) >= 3;
}

bool CMajingRule::IsQuanQiuRen(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	if (pailist.size() != 2 || pailist[0] != pailist[1])
	{
		return false;
	}

	for (vecEventPai::const_iterator iter = eventpailist.begin(); iter != eventpailist.end(); ++iter)
	{
		const stEventPai& st = *iter;
		if (st.usEventType == ::msg_maj::an_gang)
		{
			return false;
		}
	}

	return true;
}

bool CMajingRule::IsPPHu(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	uint16_t usGhostNum = 0;
	vecCheckPai stpailist;
	if (bGhost)
	{
		ChangeStructPai_Ghost(pailist, stpailist, usGhostNum);
	}
	else
	{
		ChangeStructPai(pailist, stpailist);
	}
	uint16_t usNum1 = 0, usNum2 = 0, usNum3 = 0, usNum4 = 0;
	GetSamePaiNumNum(stpailist, usNum1, usNum2, usNum3, usNum4);
	uint16_t usNeedGhostNum = 0;
	if (usNum2 == 0)
	{
		if (usNum1 > 0)
		{
			usNeedGhostNum += 1;
			usNum1 -= 1;
			if (usNum1 > 0)
			{
				usNeedGhostNum += usNum1 * 2;
			}
			if (usNum4 > 0)
			{
				usNeedGhostNum += usNum4 * 2;
			}
		}
		else
		{
			switch (usNum4)
			{
			case 1: usNeedGhostNum = 1; break;
			case 2: usNeedGhostNum = 3; break;
			case 3: usNeedGhostNum = 5; break;
			default:
				break;
			}
		}
	}
	else
	{
		if (usNum1 > 0)
		{
			usNeedGhostNum += usNum1 * 2;
		}
		if (--usNum2 > 0)
		{
			usNeedGhostNum += usNum2 * 1;
		}
		if (usNum4 > 0)
		{
			usNeedGhostNum += usNum4 * 2;
		}
	}

	if (usNeedGhostNum <= usGhostNum)
	{
		return true;
	}

	return false;
}

bool CMajingRule::IsMq(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	if (eventpailist.empty())
	{
		return true;
	}
	else
	{
		for (vecEventPai::const_iterator it = eventpailist.begin(); it != eventpailist.end(); ++it)
		{
			if (it->usEventType != ::msg_maj::an_gang)
			{
				return false;
			}
		}
		return true;
	}
}

bool CMajingRule::IsJJHu(const std::vector<uint16_t>& pailist, const vecEventPai& eventpailist, bool bGhost)
{
	for (std::vector<uint16_t>::const_iterator it = pailist.begin(); it != pailist.end(); ++it)
	{
		uint16_t usPai = *it;
		if (IsGhostCard( usPai))
			continue;
		uint16_t usPaiRema = usPai % 10;
		if (usPai > 10 && usPaiRema != 2 && usPaiRema != 5 && usPaiRema != 8)
			return false;
	}

	for (vecEventPai::const_iterator it2 = eventpailist.begin(); it2 != eventpailist.end(); ++it2)
	{
		uint16_t usPai = it2->usPai;
		if (IsGhostCard( usPai))
			continue;

		uint16_t usPaiRema = usPai % 10;
		if (usPai > 10 && usPaiRema != 2 && usPaiRema != 5 && usPaiRema != 8)
			return false;
	}

	return true;
}

void CMajingRule::Display(const std::vector<uint16_t>& pailist)
{
	std::stringstream sql_data;
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		switch (*iter)
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

	//////////LOG(INFO) << sql_data.str();
}

void CMajingRule::DisplayEx(const std::vector<uint16_t>& pailist, uint16_t usNum)
{
	uint16_t usSize = pailist.size();
	if (usSize < usNum)
	{
		//LOG(ERROR) << "CMajingRule::DisplayEx() usNum: " << usNum;
		return;
	}

	std::stringstream sql_data;
	for (uint16_t i = usSize - 1; i >= usSize - usNum; --i)
	{
		switch (pailist[i])
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

	//////////LOG(INFO) << sql_data.str();
}

void CMajingRule::AddPai(std::vector<uint16_t> & pailist, uint16_t usPai)
{
	bool bFind = false;
	for (std::vector<uint16_t>::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		if ((*iter) > usPai)
		{
			pailist.insert(iter, usPai);
			bFind = true;
			break;
		}
	}
	if (!bFind)
	{
		pailist.push_back(usPai);
	}
}

void CMajingRule::GetGuJianXiang(const std::vector<uint16_t>& pailist, std::vector<uint16_t>& gulist, std::vector<uint16_t>& jianlist, std::vector<uint16_t>& xianglist, std::vector<uint16_t>& samelist)
{
	uint16_t usSize = pailist.size();
	if (usSize <= 3)
	{
		//LOG(ERROR) << "CMajingRule::GetGuJianXiang() usSize: " << usSize;
		return;
	}

	// 头
	if (!IsGhostCard( pailist[0]))
	{
		if (pailist[0] / 10 == eCardType_Zi)
		{
			if (pailist[0] != pailist[1])
			{
				gulist.push_back(pailist[0]);
			}
			else
			{
				samelist.push_back(pailist[0]);
			}
		}
		else
		{
			if (pailist[1]/10 == pailist[0]/10)
			{
				switch (pailist[1] - pailist[0])
				{
				case 0: samelist.push_back(pailist[0]); break;
				case 1: xianglist.push_back(pailist[0]); break;
				case 2: jianlist.push_back(pailist[0]); break;
				default: gulist.push_back(pailist[0]); break;
				}
			}
			else
			{
				gulist.push_back(pailist[0]);
			}
		}
	}
	
	// 中
	for (uint16_t i = 1; i < usSize - 1; ++i)
	{
		// 鬼牌
		if (IsGhostCard( pailist[i]))
		{
			continue;
		}

		// 字牌
		if (pailist[i]/10 == eCardType_Zi)
		{
			if (pailist[i] == pailist[i+1] || 
				pailist[i] == pailist[i-1])
			{
				samelist.push_back(pailist[i]);
			}
			else
			{
				gulist.push_back(pailist[i]);
			}

			continue;
		}

		// 相同
		if (pailist[i+1] - pailist[i] == 0 ||
			pailist[i] - pailist[i-1] == 0)
		{
			samelist.push_back(pailist[i]);
			continue;
		}

		// 相邻
		if ((pailist[i+1]/10 == pailist[i]/10 && pailist[i+1] - pailist[i] == 1) ||
			(pailist[i]/10 == pailist[i-1]/10 && pailist[i] - pailist[i-1] == 1))
		{
			xianglist.push_back(pailist[i]);
			continue;
		}

		// 间邻
		if ((pailist[i+1]/10 == pailist[i]/10 && pailist[i+1] - pailist[i] == 2) ||
			(pailist[i]/10 == pailist[i-1]/10 && pailist[i] - pailist[i-1] == 2))
		{
			jianlist.push_back(pailist[i]);
			continue;
		}

		// 孤牌
		gulist.push_back(pailist[i]);
	}

	// 尾
	if (!IsGhostCard( pailist[usSize - 1]))
	{
		if (pailist[usSize-1] / 10 == eCardType_Zi)
		{
			if (pailist[usSize-1] != pailist[usSize-2])
			{
				gulist.push_back(pailist[usSize - 1]);
			}
			else
			{
				samelist.push_back(pailist[usSize - 1]);
			}
		}
		else
		{
			if (pailist[usSize-1]/10 == pailist[usSize-2]/10)
			{
				switch (pailist[usSize - 1] - pailist[usSize - 2])
				{
				case 0: samelist.push_back(pailist[usSize - 1]); break;
				case 1: xianglist.push_back(pailist[usSize - 1]); break;
				case 2: jianlist.push_back(pailist[usSize - 1]); break;
				default: gulist.push_back(pailist[usSize - 1]); break;
				}
			}
			else
			{
				gulist.push_back(pailist[usSize - 1]);
			}
		}
	}
}

bool CMajingRule::VerifyPai(uint16_t usGhostNum, const std::vector<uint16_t> & pailist)
{
	std::vector<uint16_t> pailist1 = pailist;
	for (std::vector<uint16_t>::iterator iter = pailist1.begin(); iter != pailist1.end();)
	{
		if (*iter == 7)
		{
			iter = pailist1.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	uint16_t usStart = 11, usEnd = 19;

	switch (usGhostNum)
	{
	case 0:
	{
		return true;

		break;
	}
	case 1:
	{
		for (uint16_t i = usStart; i <= usEnd; ++i)
		{
			std::vector<uint16_t> pailist_copy = pailist1;
			AddPai(pailist_copy, i);
			bool bRet = CheckHupai_PingHu(pailist_copy);
			if (bRet)
			{
				return true;
			}
		}

		break;
	}
	case 2:
	{
		for (uint16_t i = usStart; i <= usEnd; ++i)
		{
			for (uint16_t j = usStart; j <= usEnd; ++j)
			{
				std::vector<uint16_t> pailist_copy = pailist1;
				AddPai(pailist_copy, i);
				AddPai(pailist_copy, j);
				bool bRet = CheckHupai_PingHu(pailist_copy);
				if (bRet)
				{
					return true;
				}
			}
		}

		break;
	}
	case 3:
	{
		for (uint16_t i = usStart; i <= usEnd; ++i)
		{
			for (uint16_t j = usStart; j <= usEnd; ++j)
			{
				for (uint16_t k = usStart; k <= usEnd; ++k)
				{
					std::vector<uint16_t> pailist_copy = pailist1;
					AddPai(pailist_copy, i);
					AddPai(pailist_copy, j);
					AddPai(pailist_copy, k);
					bool bRet = CheckHupai_PingHu(pailist_copy);
					if (bRet)
					{
						return true;
					}
				}
			}
		}

		break;
	}
	case 4:
	{
		for (uint16_t i = usStart; i <= usEnd; ++i)
		{
			for (uint16_t j = usStart; j <= usEnd; ++j)
			{
				for (uint16_t k = usStart; k <= usEnd; ++k)
				{
					for (uint16_t l = usStart; l <= usEnd; ++l)
					{
						std::vector<uint16_t> pailist_copy = pailist1;
						AddPai(pailist_copy, i);
						AddPai(pailist_copy, j);
						AddPai(pailist_copy, k);
						AddPai(pailist_copy, l);
						bool bRet = CheckHupai_PingHu(pailist_copy);
						if (bRet)
						{
							return true;
						}
					}
				}
			}
		}

		break;
	}

	default:
		break;
	}

	return false;
}

//***********************************************听牌********************************************************

void CMajingRule::AddTingPai(std::set<uint16_t>& tinglist, uint16_t usPai)
{
	if (usPai == 0)
	{
		return;
	}

	if (tinglist.find(usPai) == tinglist.end())
	{
		tinglist.insert(usPai);
	}
}

void CMajingRule::AddTingPaiEx(const vecCheckPai& stlist, std::set<uint16_t>& tinglist)
{
	switch (stlist.size())
	{
	case 1:
	{
		AddTingPai(tinglist, stlist[0].usPai);
		break;
	}
	case 2:
	{
		//AABB
		if (stlist[0].usNum == 2 && stlist[1].usNum == 2)
		{
			AddTingPai(tinglist, stlist[0].usPai);
			AddTingPai(tinglist, stlist[1].usPai);
			break;
		}

		//AB AC
		if (stlist[0].usNum != 1 || stlist[1].usNum != 1)
		{
			break;
		}

		if (stlist[1].usPai - stlist[0].usPai == 1)
		{
			uint16_t usMin = stlist[0].usPai - 1;
			if (usMin % 10 != 0)
			{
				AddTingPai(tinglist, usMin);
			}
			uint16_t usMax = stlist[1].usPai + 1;
			if (usMax % 10 != 0)
			{
				AddTingPai(tinglist, usMax);
			}
		}
		else if (stlist[1].usPai - stlist[0].usPai == 2)
		{
			AddTingPai(tinglist, stlist[0].usPai + 1);
		}
		break;
	}
	case 4:
	{
		if (stlist[0].usNum == stlist[1].usNum &&
			stlist[1].usNum == stlist[2].usNum &&
			stlist[2].usNum == stlist[3].usNum &&
			CheckABCDPai(stlist[0].usPai, stlist[1].usPai, stlist[2].usPai, stlist[3].usPai))
		{
			AddTingPai(tinglist, stlist[0].usPai);
			AddTingPai(tinglist, stlist[3].usPai);
		}

		break;
	}
	default:
		break;
	}
}

void CMajingRule::GetTingPaiList(const vecCheckPai& stlist, std::set<uint16_t>& tinglist)
{
	//顺向检测
	vecCheckPai stlist_copy = stlist;
	DelAAAABCPai_ting(stlist_copy);
	DelAAAABCPaiEx_ting(stlist_copy);
	AddTingPaiEx(stlist_copy, tinglist);

	//逆向检测
	stlist_copy = stlist;
	DelAAAABCPaiEx_ting(stlist_copy);
	DelAAAABCPai_ting(stlist_copy);
	AddTingPaiEx(stlist_copy, tinglist);

	//先删除头尾
	stlist_copy = stlist;
	DelAAAABCHead_ting(stlist_copy);
	DelAAAABCHeadEx_ting(stlist_copy);

	vecCheckPai stlist_copy_ni = stlist_copy; //逆向

	vecCheckPai stlist_copy_jc = stlist_copy; //交叉

	DelAAAABCPai_ting(stlist_copy);
	AddTingPaiEx(stlist_copy, tinglist);

	DelAAAABCPaiEx_ting(stlist_copy_ni);
	AddTingPaiEx(stlist_copy_ni, tinglist);

	DelAAAABCJC_ting(stlist_copy_jc);
	DelAAAABCJCEx_ting(stlist_copy_jc);
	AddTingPaiEx(stlist_copy_jc, tinglist);
}

void CMajingRule::GetTingPaiList_Jiang(const vecCheckPai& stlist, uint16_t usJiangPai, std::set<uint16_t>& tinglist)
{
	//有将牌判断
	for (vecCheckPai::const_iterator iter = stlist.begin(); iter != stlist.end(); ++iter)
	{
		const stCheckPai& st = *iter;
		if (st.usNum < 2)
		{
			continue;
		}

		vecCheckPai stlist_del = stlist;
		DelAAPai_Pai(stlist_del, st.usPai);

		//顺向检测
		vecCheckPai stlist_copy = stlist_del;
		DelAAAABCPai_ting(stlist_copy);
		DelAAAABCPaiEx_ting(stlist_copy);
		AddTingPaiEx(stlist_copy, tinglist);

		//逆向检测
		stlist_copy = stlist_del;
		DelAAAABCPaiEx_ting(stlist_copy);
		DelAAAABCPai_ting(stlist_copy);
		AddTingPaiEx(stlist_copy, tinglist);

		//先删除头尾
		stlist_copy = stlist_del;
		DelAAAABCHead_ting(stlist_copy);
		DelAAAABCHeadEx_ting(stlist_copy);

		vecCheckPai stlist_copy_ni = stlist_copy; //逆向

		vecCheckPai stlist_copy_jc = stlist_copy; //交叉

		vecCheckPai stlist_copy_aaa = stlist_copy; //先删除AAA

		DelAAAABCPai_ting(stlist_copy);
		AddTingPaiEx(stlist_copy, tinglist);

		DelAAAABCPaiEx_ting(stlist_copy_ni);
		AddTingPaiEx(stlist_copy_ni, tinglist);

		DelAAAABCJC_ting(stlist_copy_jc);
		DelAAAABCJCEx_ting(stlist_copy_jc);
		AddTingPaiEx(stlist_copy_jc, tinglist);

		DelAAAPai(stlist_copy_aaa);
		DelAAAABCPai_ting(stlist_copy_aaa);
		AddTingPaiEx(stlist_copy_aaa, tinglist);
	}

	//无将牌判断
	{
		//顺向检测
		vecCheckPai stlist_copy = stlist;
		DelAAAABCPai_ting(stlist_copy);
		AddTingPaiEx(stlist_copy, tinglist);

		//逆向检测
		stlist_copy = stlist;
		DelAAAABCPaiEx_ting(stlist_copy);
		AddTingPaiEx(stlist_copy, tinglist);

		//先删除头尾
		stlist_copy = stlist;
		DelAAAABCHead_ting(stlist_copy);
		DelAAAABCHeadEx_ting(stlist_copy);

		vecCheckPai stlist_copy_ni = stlist_copy; //逆向

		vecCheckPai stlist_copy_aaa = stlist_copy; //先删除AAA

		DelAAAABCPai_ting(stlist_copy);
		AddTingPaiEx(stlist_copy, tinglist);

		DelAAAABCPaiEx_ting(stlist_copy_ni);
		AddTingPaiEx(stlist_copy_ni, tinglist);

		DelAAAPai(stlist_copy_aaa);
		DelAAAABCPai_ting(stlist_copy_aaa);
		AddTingPaiEx(stlist_copy_aaa, tinglist);
	}
}

void CMajingRule::GetTingPaiListZi(const vecCheckPai& stlist, std::set<uint16_t>& tinglist)
{
	for (vecCheckPai::const_iterator iter = stlist.begin(); iter != stlist.end(); ++iter)
	{
		if ((*iter).usNum == 2)
		{
			AddTingPai(tinglist, (*iter).usPai);
		}
	}
}

void CMajingRule::GetTingPaiListZi_Jiang(const vecCheckPai& stlist, std::set<uint16_t>& tinglist)
{
	for (vecCheckPai::const_iterator iter = stlist.begin(); iter != stlist.end(); ++iter)
	{
		switch ((*iter).usNum)
		{
		case 1:
		{
			AddTingPai(tinglist, (*iter).usPai);
			return;

			break;
		}
		default:
			break;
		}
	}

	for (vecCheckPai::const_iterator iter = stlist.begin(); iter != stlist.end(); ++iter)
	{
		switch ((*iter).usNum)
		{
		case 2:
		{
			AddTingPai(tinglist, (*iter).usPai);
			break;
		}
		default:
			break;
		}
	}
}

bool CMajingRule::CheckTing_PingHu(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist)
{
	uint16_t usGhostNum = 0;
	vecCheckPai zilist, tonglist, tiaolist, wanlist;
	ChangeStructPai_Ex(pailist, usGhostNum, zilist, tonglist, tiaolist, wanlist);

	if (usGhostNum > 0)
	{
		stCheckPai st;
		st.usPai = GetGhostCard();
		st.usNum = usGhostNum;
		zilist.push_back(st);
	}

	//uint16_t usJiangPai = 0;
	uint16_t usNeedGhostNum = 0;

	uint16_t usNumZi = CheckNeedGhostNumZi(zilist);

	bool bJiang_zi = false;
	uint16_t usNumZi_Jiang = CheckNeedGhostNumZi_Jiang(zilist, bJiang_zi);

	uint16_t usNumTong = CheckNeedGhostNum(tonglist);
	bool bJiang_tong = false;
	uint16_t usNumTong_Jiang = CheckNeedGhostNum_Jiang(tonglist, bJiang_tong);

	uint16_t usNumTiao = CheckNeedGhostNum(tiaolist);
	bool bJiang_tiao = false;
	uint16_t usNumTiao_Jiang = CheckNeedGhostNum_Jiang(tiaolist, bJiang_tiao);

	uint16_t usNumWan = CheckNeedGhostNum(wanlist);
	bool bJiang_wan = false;
	uint16_t usNumWan_Jiang = CheckNeedGhostNum_Jiang(wanlist, bJiang_wan);

	//LOG(WARNING) << "=====: " << zilist.size() << " " << tonglist.size() << " " << tiaolist.size() << " " << wanlist.size();
	uint16_t usJiangPai_tiao = 0;
	uint16_t usJiangPai_tong = 0;
	uint16_t usJiangPai_wan = 0;

	//将牌在风中
	if (zilist.size() > 0)
	{
		usNeedGhostNum = usNumZi_Jiang + usNumTong + usNumTiao + usNumWan;
		if (usNeedGhostNum == 1)
		{
			if (usNumZi_Jiang == 1)
			{
				GetTingPaiListZi_Jiang(zilist, tinglist);
			}
			else if (usNumTong == 1)
			{
				GetTingPaiList(tonglist, tinglist);
			}
			else if (usNumTiao == 1)
			{
				GetTingPaiList(tiaolist, tinglist);
			}
			else if (usNumWan == 1)
			{
				GetTingPaiList(wanlist, tinglist);
			}
		}
	}

	//将在筒中
	if (tonglist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong_Jiang + usNumTiao + usNumWan;
		if (usNeedGhostNum == 1)
		{
			if (usNumZi == 1)
			{
				GetTingPaiListZi(zilist, tinglist);
			}
			else if (usNumTong_Jiang == 1)
			{
				GetTingPaiList_Jiang(tonglist, usJiangPai_tong, tinglist);
			}
			else if (usNumTiao == 1)
			{
				GetTingPaiList(tiaolist, tinglist);
			}
			else if (usNumWan == 1)
			{
				GetTingPaiList(wanlist, tinglist);
			}
		}
	}

	//将在条中
	if (tiaolist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong + usNumTiao_Jiang + usNumWan;
		if (usNeedGhostNum == 1)
		{
			if (usNumZi == 1)
			{
				GetTingPaiListZi(zilist, tinglist);
			}
			else if (usNumTong == 1)
			{
				GetTingPaiList(tonglist, tinglist);
			}
			else if (usNumTiao_Jiang == 1)
			{
				GetTingPaiList_Jiang(tiaolist, usJiangPai_tiao, tinglist);
			}
			else if (usNumWan == 1)
			{
				GetTingPaiList(wanlist, tinglist);
			}
		}
	}

	//将在万中
	if (wanlist.size() > 0)
	{
		usNeedGhostNum = usNumZi + usNumTong + usNumTiao + usNumWan_Jiang;
		if (usNeedGhostNum == 1)
		{
			if (usNumZi == 1)
			{
				GetTingPaiListZi(zilist, tinglist);
			}
			else if (usNumTong == 1)
			{
				GetTingPaiList(tonglist, tinglist);
			}
			else if (usNumTiao == 1)
			{
				GetTingPaiList(tiaolist, tinglist);
			}
			else if (usNumWan_Jiang == 1)
			{
				GetTingPaiList_Jiang(wanlist, usJiangPai_wan, tinglist);
			}
		}
	}

	return !tinglist.empty();
}

bool CMajingRule::CheckTing_QiDui(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist)
{
	if (pailist.size() != 13)
	{
		return false;
	}

	uint16_t usSingleNum = 0;
	uint16_t usTingPai = 0;
	vecCheckPai stpailist;
	ChangeStructPai(pailist, stpailist);
	for (vecCheckPai::const_iterator iter = stpailist.begin(); iter != stpailist.end(); ++iter)
	{
		switch ((*iter).usNum)
		{
		case 1:
		case 3:
		{
			if (++usTingPai > 1)
			{
				return false;
			}
			usTingPai = (*iter).usPai;
			break;
		}
		default: break;
		}
	}

	AddTingPai(tinglist, usTingPai);
	return true;
}

bool CMajingRule::CheckTing_13yao(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist)
{
	vecCheckPai stpailist;
	ChangeStructPai(pailist, stpailist);

	switch (stpailist.size())
	{
	case 12:
	{
		uint16_t usNotHas = 0;
		uint16_t usTingPai = 0;
		for (uint16_t i = 0; i < __13_YAO_NUM__; ++i)
		{
			if (!CheckHasStructPai(stpailist, g_majing_13yao[i]))
			{
				if (++usNotHas > 1)
				{
					return false;
				}
				usTingPai = g_majing_13yao[i];
			}
		}

		AddTingPai(tinglist, usTingPai);

		break;
	}
	case 13:
	{
		uint16_t i = 0;
		for (vecCheckPai::const_iterator iter = stpailist.begin(); iter != stpailist.end(); ++iter)
		{
			if ((*iter).usPai != g_majing_13yao[i++])
			{
				return false;
			}
		}

		for (i = 0; i < __13_YAO_NUM__; ++i)
		{
			AddTingPai(tinglist, g_majing_13yao[i]);
		}

		break;
	}
	default: return false;
		break;
	}

	return true;
}

bool CMajingRule::IsTianHu(CPlayer* pPlayer)
{
	if (pPlayer->GetSeat() == m_pRoom->GetBankerSeat())
	{
		if (m_pMaj->GetLoopPoses() == 1)
		{
			return true;
		}
	}
	return false;
}

bool CMajingRule::IsDiHu(CPlayer* pPlayer)
{
	for (uint16_t i = 0; i < m_pRoom->GetTotalPersons(); ++i)
	{
		if (!m_pRoom->GetPlayer(i)->GetEventPaiList().empty())
		{
			return false;
		}
	}
	if (m_pMaj->GetLoopPoses() <= 4 && m_pMaj->GetLoopPoses() >= 2)
	{
		uint16_t offset = pPlayer->GetSeat() > m_pRoom->GetBankerSeat() ? pPlayer->GetSeat() - m_pRoom->GetBankerSeat() : pPlayer->GetSeat() + 4 - m_pRoom->GetBankerSeat();
		offset = offset % 4;
		if (m_pMaj->GetLoopPoses() > 1 && m_pMaj->GetLoopPoses() == offset + 1)
		{
			return true;
		}
	}
	return false;
}

uint16_t CMajingRule::GetCostCard()
{
	if (m_usPayType == 1)
	{
		return  m_usJuShuType;
	}
	else
	{
		return m_usJuShuType * GetPlayerNum();
	}
}

int16_t CMajingRule::CheckTingPai(const std::vector<uint16_t>& pailist, std::set<uint16_t>& tinglist)
{
	//检测七对
	if (CheckTing_QiDui(pailist, tinglist))
	{
		return 1;
	}

	//检测平胡
	if (CheckTing_PingHu(pailist, tinglist))
	{
		return 2;
	}
	return 0;
}

bool CMajingRule::IsHasGhostPai(const std::vector<uint16_t>& pailist)
{
	for (std::vector<uint16_t>::const_iterator it = pailist.begin(); it != pailist.end(); ++it)
	{
		if (IsGhostCard(*it))
		{
			return true;
		}
	}
	return false;
}




