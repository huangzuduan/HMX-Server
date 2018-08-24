#include "CMaJiang.hpp"
#include "CRoom.hpp"
#include "SrvEngine.h"

::boost::object_pool<CMaJiang> g_objpoolMaJiang;

CMaJiang::CMaJiang(CRoom* pRoom):
	m_bGM(false),
	m_pRoom(pRoom),
	m_pRule(NULL),
	m_curMJPos(0),
	m_maxMjPos(__MAJING_NUM__ - 1),
	m_usMaPaiNum(0),
	m_usYiMaAllHit(0),
	m_unRoll(0),
	m_usSendCardPos(0),
	m_usSendCardNum(0),
	m_usDicardPos(0),
	m_eActionType(eActionType_NULL),
	m_usCurActionPos(0),
	m_usCurActionPai(0),
	m_bActionEvent(false),
	m_usGang(0),
	m_nLoopPoses(0),
	m_nLoopEvents(0),
	m_bHadCheckGZ(false),
	m_bGenZhuangSuccess(false),
	m_bHadFan(false),
	m_bHadSendGhost(false),
	m_nFanPai(0),
	m_nLastGangType(0),
	m_nLastGangPai(0),
	m_nLastGangPos(0),
	m_nLastGangFromPos(0),
	m_usFirstSeat(-1),
	m_bEnd(false)
{
}

CMaJiang::~CMaJiang()
{
}

void CMaJiang::Release()
{
	if (m_vecHuPai.size())
	{
		for (vecHuPai::const_iterator it = m_vecHuPai.begin(); it != m_vecHuPai.end(); ++it)
		{
			bool foundIt = false;
			for (vecLastHuInfo::iterator it2 = m_vecLastHuInfo.begin(); it2 != m_vecLastHuInfo.end(); ++it2)
			{
				if (it2->seat == it->m_usHupaiPos)
				{
					foundIt = true;
					it2->times += 1;
					break;
				}
			}
			if (!foundIt)
			{
				stLastHuInfo huInfo;
				huInfo.seat = it->m_usHupaiPos;
				huInfo.times = 1;
				m_vecLastHuInfo.push_back(huInfo);
			}
		}

		// 清除掉与胡牌无关的人
		for (vecLastHuInfo::iterator it3 = m_vecLastHuInfo.begin(); it3 != m_vecLastHuInfo.end();)
		{
			bool foundIt = false;
			for (vecHuPai::const_iterator it4 = m_vecHuPai.begin(); it4 != m_vecHuPai.end(); ++it4)
			{
				if (it3->seat == it4->m_usHupaiPos)
				{
					foundIt = true;
					break;
				}
			}
			if (!foundIt)
			{
				it3 = m_vecLastHuInfo.erase(it3);
			}
			else
			{
				++it3;
			}
		}
	}
	else
	{
		m_vecLastHuInfo.clear();
	}

	if (m_stLastBanker.seat == m_pRoom->GetBankerSeat())
	{
		m_stLastBanker.times += 1;
	}
	else
	{
		m_stLastBanker.seat = m_pRoom->GetBankerSeat();
		m_stLastBanker.times += 1;
	}

	m_vecPaiList.clear();
	m_maxMjPos = __MAJING_NUM__ - 1;
	m_unRoll = 0;
	//m_usSendCardPos = 0;
	m_usSendCardNum = 0;
	m_usDicardPos = 0;
	m_usCurActionPos = 0;
	m_usCurActionPai = 0;
	m_bActionEvent = false;
	m_usGang = 0;
	m_nLoopPoses = 0;
	m_nLoopEvents = 0;
	m_usYiMaAllHit = 0;
	m_bHadCheckGZ = false;
	m_bGenZhuangSuccess = false;
	m_vecDiscards.clear();
	m_bHadFan = false;
	m_bHadSendGhost = false;
	m_nFanPai = 0;
	m_vecHuPai.clear();
	m_usMaPaiNum = 0;
	m_vecMaPai.clear();
	m_vecSeatEvent.clear();
	m_nLastGangType = 0;
	m_nLastGangPai = 0;
	m_nLastGangPos = 0;
	m_nLastGangFromPos = 0;
	m_mapOutPai.clear();
	m_usFirstSeat = -1;
}

//打乱所有麻将
bool CMaJiang::InitMajing()
{
	// 根据游戏类型，房间参数初始化牌
	InitPai();

	// 随机筛子
	RandomRoll();

	// 是否有GM操作
	if (m_bGM)
	{
		m_bGM = false;

		if (!GMOper())
		{
			return false;
		}
	}

	return true;
}

void CMaJiang::InitMaPai()
{
	m_usMaPaiNum = m_pRoom->GetRule()->GetMaiMaNum();
}

void CMaJiang::OpenMaPai()
{
	for (uint16_t i = 0; i < m_usMaPaiNum; ++i)
	{
		uint16_t pai = GetPai();
		if (pai) m_vecMaPai.push_back(pai);
	}
}

void CMaJiang::OpenYiMaAllHit()
{
	uint16_t pai = GetPai();
	if (pai) m_vecMaPai.push_back(pai);
}

void CMaJiang::GMSetMajiang(const std::vector<uint16_t>& pailist)
{
	if (pailist.size() != 53)
	{
		//LOG(ERROR) << "CMajingRule::GMSetMajiang() size: " << pailist.size();
		return;
	}

	m_bGM = true;
	m_vecGMPailist = pailist;
}

void CMaJiang::GMSetPai(uint16_t usPai)
{
	uint16_t usSize = m_vecPaiList.size();
	if (usSize == 0)
	{
		return;
	}

	if (m_vecPaiList[usSize - 1] == usPai)
	{
		return;
	}

	bool bFind = false;
	uint16_t usPos = 0;
	uint16_t i = 0;
	for (std::vector<uint16_t>::iterator iter = m_vecPaiList.begin(); iter != m_vecPaiList.end(); ++iter)
	{
		if (*iter == usPai)
		{
			bFind = true;
			usPos = i;
		}
		++i;
	}

	if (!bFind)
	{
		return;
	}

	m_vecPaiList[usPos] = m_vecPaiList[usSize - 1];
	m_vecPaiList[usSize - 1] = usPai;
}

uint16_t CMaJiang::GetPai()
{
	uint16_t usSize = m_vecPaiList.size();
	if (usSize == 0)
	{
		return 0;
	}
	uint16_t usPai = m_vecPaiList[usSize - 1];
	m_vecPaiList.pop_back();
	return usPai;
}

void CMaJiang::InitPai()
{
	std::vector<uint16_t> vevFilter;
	GetFilterPai(vevFilter);
	for (uint16_t i = 0; i < __MAJING_NUM__; ++i)
	{
		bool foundIt = false;
		uint16_t tmpPai = g_majing_data[i];
		for (std::vector<uint16_t>::iterator it2 = vevFilter.begin(); it2 != vevFilter.end();)
		{
			if (tmpPai == *it2)
			{
				it2 = vevFilter.erase(it2);
				foundIt = true;
				break;
			}
			else
			{
				++it2;
			}
		}
		if (!foundIt)
		{
			m_vecPaiList.push_back(tmpPai);
		}
	}

	random_shuffle(m_vecPaiList.begin(), m_vecPaiList.end());

	if (randBetween(1, 100) > 80)
	{
		return;
	}

	// 换牌
	//LOG(WARNING) << "&&&&&&&&&&&&&&&&&&&&&change pai";
	std::vector<uint16_t> changelist;
	for (uint16_t i = 0; i < m_pRoom->GetTotalPersons(); ++i)
	{
		ChangePai(i, changelist);
	}
	random_shuffle(changelist.begin(), changelist.end());
	uint16_t index = 0;
	if (!m_vecPaiList.empty())
	{
		for (uint16_t i = m_vecPaiList.size() - 1; i >= 0; --i)
		{
			if (m_vecPaiList[i] == 0)
			{
				m_vecPaiList[i] = changelist[index++];
				if (index == changelist.size())
				{
					break;
				}
			}
		}
	}
}

void CMaJiang::GetFilterPai(std::vector<uint16_t>& vevFilter)
{
	if (m_pRule->IsWuZi())
	{
		for (uint16_t i = 1; i <= 7; ++i)
		{
			if (m_pRule->IsGhost() && m_pRule->IsGhostCard(i))
			{
				continue;
			}
			vevFilter.push_back(i);
			vevFilter.push_back(i);
			vevFilter.push_back(i);
			vevFilter.push_back(i);
		}
	}
	for (uint16_t i = 0; i < __HUA_NUM_8__; ++i)
	{
		if (m_pRule->IsGhost() && m_pRule->IsGhostCard(i))
		{
			continue;
		}
		vevFilter.push_back(g_majing_hua_8[i]);
	}

	if (m_pRule->GetPlayerNum() == 2)
	{
		for (uint16_t i = 12; i <= 18; ++i)
		{
			vevFilter.push_back(i);
			vevFilter.push_back(i);
			vevFilter.push_back(i);
			vevFilter.push_back(i);
		}
	}

	if (m_pRule->GetPlayerNum() == 2)
	{
		for (uint16_t i = 12; i <= 18; ++i)
		{
			vevFilter.push_back(i);
			vevFilter.push_back(i);
			vevFilter.push_back(i);
			vevFilter.push_back(i);
		}
		for (uint16_t i = 22; i <= 28; ++i)
		{
			vevFilter.push_back(i);
			vevFilter.push_back(i);
			vevFilter.push_back(i);
			vevFilter.push_back(i);
		}
	}
}

void CMaJiang::GetMaxCardTypeNum(uint16_t usSeat, eCardType& etype, uint16_t& usNum)
{
	uint16_t usTongNum = 0, usTiaoNum = 0, usWanNum = 0, usGhostNum = 0;
	uint16_t usStart = m_vecPaiList.size() - 1 - usSeat * 13;
	uint16_t usEnd = usStart - 13;
	for (uint16_t i = usStart; i > usEnd; --i)
	{
		if (m_vecPaiList[i] == m_pRoom->GetRule()->GetGhostCard())
		{
			++usGhostNum;
			continue;
		}

		switch (m_vecPaiList[i] / 10)
		{
		case eCardType_Tong:
		{
			++usTongNum;
			break;
		}
		case eCardType_Tiao:
		{
			++usTiaoNum;
			break;
		}
		case eCardType_Wan:
		{
			++usWanNum;
			break;
		}
		default:
			break;
		}
	}

	if (usTiaoNum > usTongNum)
	{
		etype = eCardType_Tiao;
		usNum = usTiaoNum;
	}
	else
	{
		etype = eCardType_Tong;
		usNum = usTongNum;
	}

	if (etype == eCardType_Tong)
	{
		if (usWanNum > usTongNum)
		{
			etype = eCardType_Wan;
			usNum = usWanNum;
		}
	}
	else
	{
		if (usWanNum > usTiaoNum)
		{
			etype = eCardType_Wan;
			usNum = usWanNum;
		}
	}

	usNum += usGhostNum;
}

void CMaJiang::ChangePai(uint16_t usSeat, std::vector<uint16_t>& changelist)
{
	uint16_t usStart = m_vecPaiList.size() - 1 - usSeat * 13;
	uint16_t usEnd = usStart - 13;
	eCardType emaxtype;
	uint16_t usMaxNum = 0;
	uint16_t usChangCount = 2;
	GetMaxCardTypeNum(usSeat, emaxtype, usMaxNum);	
	if (usMaxNum >= 11) //该玩家不参与换牌
	{
		////LOG(WARNING) << "11张";
	}
	else if (usMaxNum >= 9 && usMaxNum <= 10) //挑出的牌中随机再抽出3张牌
	{
		////LOG(WARNING) << "9-10张";
		std::vector<uint16_t> pailist;
		for (uint16_t i = usStart; i > usEnd; --i)
		{
			if (m_vecPaiList[i] == m_pRoom->GetRule()->GetGhostCard() ||
				m_vecPaiList[i] / 10 == emaxtype)
			{
				continue;
			}

			m_pRoom->GetRule()->AddPai(pailist, m_vecPaiList[i]);
			if (pailist.size() == usChangCount)
			{
				break;
			}
		}

		if (ChangePaiEx(usSeat, pailist))
		{
			for (std::vector<uint16_t>::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
			{
				changelist.push_back(*iter);
			}
		}
	}
	else if (usMaxNum >= 7 && usMaxNum <= 8) //挑出的牌中优先保留对子/顺子/刻子
	{
		////LOG(WARNING) << "7-8张";
		std::vector<uint16_t> pailist;
		for (uint16_t i = usStart; i > usEnd; --i)
		{
			if (m_vecPaiList[i] == m_pRoom->GetRule()->GetGhostCard() ||
				m_vecPaiList[i] / 10 == emaxtype)
			{
				continue;
			}

			m_pRoom->GetRule()->AddPai(pailist, m_vecPaiList[i]);
		}

		std::vector<uint16_t> gulist, jianlist, xianglist, samelist;
		m_pRoom->GetRule()->GetGuJianXiang(pailist, gulist, jianlist, xianglist, samelist);

		pailist.clear();
		if (gulist.size() > usChangCount)
		{
			random_shuffle(gulist.begin(), gulist.end());
		}
		for (std::vector<uint16_t>::iterator iter = gulist.begin(); iter != gulist.end(); ++iter)
		{
			if (pailist.size() == usChangCount)
			{
				break;
			}
			m_pRoom->GetRule()->AddPai(pailist, *iter);
		}

		if (pailist.size() < usChangCount)
		{
			if (jianlist.size() > 1)
			{
				random_shuffle(jianlist.begin(), jianlist.end());
			}
			for (std::vector<uint16_t>::iterator iter = jianlist.begin(); iter != jianlist.end(); ++iter)
			{
				if (pailist.size() == usChangCount)
				{
					break;
				}
				m_pRoom->GetRule()->AddPai(pailist, *iter);
			}
		}
		
		if (pailist.size() < usChangCount)
		{
			if (xianglist.size() > 1)
			{
				random_shuffle(xianglist.begin(), xianglist.end());
			}
			for (std::vector<uint16_t>::iterator iter = xianglist.begin(); iter != xianglist.end(); ++iter)
			{
				if (pailist.size() == usChangCount)
				{
					break;
				}
				m_pRoom->GetRule()->AddPai(pailist, *iter);
			}
		}
		
		if (pailist.size() < usChangCount)
		{
			if (samelist.size() > 1)
			{
				random_shuffle(samelist.begin(), samelist.end());
			}
			for (std::vector<uint16_t>::iterator iter = samelist.begin(); iter != samelist.end(); ++iter)
			{
				if (pailist.size() == usChangCount)
				{
					break;
				}
				m_pRoom->GetRule()->AddPai(pailist, *iter);
			}
		}	

		if (ChangePaiEx(usSeat, pailist))
		{
			for (std::vector<uint16_t>::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
			{
				changelist.push_back(*iter);
			}
		}
	}
	else //
	{
		////LOG(WARNING) << "6张及以下";
		std::vector<uint16_t> pailist;
		for (uint16_t i = usStart; i > usEnd; --i)
		{
			m_pRoom->GetRule()->AddPai(pailist, m_vecPaiList[i]);
		}

		std::vector<uint16_t> gulist, jianlist, xianglist, samelist;
		m_pRoom->GetRule()->GetGuJianXiang(pailist, gulist, jianlist, xianglist, samelist);
		pailist.clear();
		if (gulist.size() > usChangCount)
		{
			random_shuffle(gulist.begin(), gulist.end());
		}
		for (std::vector<uint16_t>::iterator iter = gulist.begin(); iter != gulist.end(); ++iter)
		{
			if (pailist.size() == usChangCount)
			{
				break;
			}
			m_pRoom->GetRule()->AddPai(pailist, *iter);
		}

		if (pailist.size() < usChangCount)
		{
			if (jianlist.size() > 1)
			{
				random_shuffle(jianlist.begin(), jianlist.end());
			}
			for (std::vector<uint16_t>::iterator iter = jianlist.begin(); iter != jianlist.end(); ++iter)
			{
				if (pailist.size() == usChangCount)
				{
					break;
				}
				m_pRoom->GetRule()->AddPai(pailist, *iter);
			}
		}

		if (pailist.size() < usChangCount)
		{
			if (xianglist.size() > 1)
			{
				random_shuffle(xianglist.begin(), xianglist.end());
			}
			for (std::vector<uint16_t>::iterator iter = xianglist.begin(); iter != xianglist.end(); ++iter)
			{
				if (pailist.size() == usChangCount)
				{
					break;
				}
				m_pRoom->GetRule()->AddPai(pailist, *iter);
			}
		}

		if (ChangePaiEx(usSeat, pailist))
		{
			for (std::vector<uint16_t>::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
			{
				changelist.push_back(*iter);
			}
		}
	}
}

bool CMaJiang::ChangePaiEx(uint16_t usSeat, std::vector<uint16_t>& pailist)
{
	uint16_t usChangCount = 2;
	if (pailist.size() != usChangCount)
	{
		return false;
	}

	uint16_t usStart = m_vecPaiList.size() - 1 - usSeat * 13;
	uint16_t usEnd = usStart - 13;

	for (std::vector<uint16_t>::iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		for (uint16_t i = usStart; i > usEnd; --i)
		{
			if (m_vecPaiList[i] == 0)
			{
				continue;
			}

			if (m_vecPaiList[i] == *iter)
			{
				m_vecPaiList[i] = 0;
				break;
			}
		}
		
	}

	return true;
}

void CMaJiang::RandomRoll()
{
	uint32_t nNum1 = randBetween(1, 6);
	uint32_t nNum2 = randBetween(1, 6);
	m_unRoll = nNum1 * 10 + nNum2;
}

uint32_t CMaJiang::GetRandRoll() const
{
	return m_unRoll;
}

bool CMaJiang::GMOper()
{
	std::vector<uint16_t> vevFilter;
	GetFilterPai(vevFilter);
	for (std::vector<uint16_t>::iterator iter = vevFilter.begin(); iter != vevFilter.end(); ++iter)
	{
		for (std::vector<uint16_t>::iterator it = m_vecGMPailist.begin(); it != m_vecGMPailist.end(); ++it)
		{
			if (*it == *iter)
			{
				m_vecGMPailist.erase(it);
				break;
			}
		}
	}

	for (std::vector<uint16_t>::iterator iter = m_vecGMPailist.begin(); iter != m_vecGMPailist.end(); ++iter)
	{
		for (std::vector<uint16_t>::iterator it = m_vecPaiList.begin(); it != m_vecPaiList.end(); ++it)
		{
			if (*it == *iter)
			{
				m_vecPaiList.erase(it);
				break;
			}
		}
	}

	uint16_t usNum = m_vecGMPailist.size() + m_vecPaiList.size();
	switch (usNum)
	{
	case 72: break;
	case 76: break;
	case 80: break;
	case 108: break;
	case 112: break;
	case 132: break;
	case 136: break;
	case 140: break;
	case 144: break;	
	default: return false; break;
	}

	uint16_t usGMNum = m_vecGMPailist.size();
	for (uint16_t i = usGMNum; i > 0; --i)
	{
		m_vecPaiList.push_back(m_vecGMPailist[i - 1]);
	}

	return true;
}

bool CMaJiang::InitFanGhostPai()
{
	return false;
}

void CMaJiang::AddSeatEvent(::msg_maj::event_type etype, uint16_t usSeat, bool bAction)
{
	stSeatEvent st;
	st.etype = etype;
	st.usSeat = usSeat;
	st.bAction = bAction;
	m_vecSeatEvent.push_back(st);
}

uint16_t CMaJiang::GetEventSeatNum()
{
	std::set<uint16_t> seatlist;
	for (vecSeatEvent::iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end(); ++iter)
	{
		uint16_t usSeat = (*iter).usSeat;
		if (seatlist.find(usSeat) == seatlist.end())
		{
			seatlist.insert(usSeat);
		}
	}

	return seatlist.size();
}

bool CMaJiang::DelSeatEvent(uint16_t usSeat)
{
	bool bRet = false;
	for (vecSeatEvent::iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end();)
	{
		stSeatEvent& st = *iter;
		if (st.usSeat == usSeat)
		{
			bRet = true;
			iter = m_vecSeatEvent.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	return true;
}

bool CMaJiang::CheckEvent(::msg_maj::event_type etype, uint16_t usSeat)
{
	for (vecSeatEvent::iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end(); ++iter)
	{
		if ((*iter).usSeat != usSeat)
		{
			continue;
		}

		if (etype == ::msg_maj::pass || (*iter).etype == etype)
		{
			return true;
		}
	}

	return false;
}

bool CMaJiang::DoSeatEvent(::msg_maj::event_type etype, uint16_t usSeat)
{
	bool bRet = false;
	std::set<uint16_t> huseatlist;
	for (vecSeatEvent::iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end();)
	{
		stSeatEvent& st = *iter;

		if (st.etype == ::msg_maj::zi_mo_hu && huseatlist.find(st.usSeat) == huseatlist.end())
		{
			huseatlist.insert(st.usSeat);
		}

		if (st.etype == ::msg_maj::dian_pao_hu && huseatlist.find(st.usSeat) == huseatlist.end())
		{
			huseatlist.insert(st.usSeat);
		}

		if (st.usSeat != usSeat)
		{
			++iter;
			continue;
		}

		if (st.etype != etype)
		{
			iter = m_vecSeatEvent.erase(iter);
			continue;
		}

		if (st.bAction == false)
		{
			bRet = true;
			st.bAction = true;
		}

		++iter;
	}

	if (bRet && (etype == ::msg_maj::zi_mo_hu || etype == ::msg_maj::dian_pao_hu))
	{
		for (vecSeatEvent::iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end();)
		{
			stSeatEvent& st = *iter;
			if (st.etype == ::msg_maj::zi_mo_hu || st.etype == ::msg_maj::dian_pao_hu)
			{
				++iter;
				continue;
			}

			if (huseatlist.find(st.usSeat) == huseatlist.end())
			{
				iter = m_vecSeatEvent.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}

	if (etype != ::msg_maj::zi_mo_hu && etype != ::msg_maj::dian_pao_hu)
	{
		DelHuPai(usSeat);
	}

	return bRet;
}

bool CMaJiang::IsDoAllSeatEvent() const
{
	for (vecSeatEvent::const_iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end(); ++iter)
	{
		if (!(*iter).bAction)
		{
			return false;
		}
	}

	return true;
}

void CMaJiang::AddHuPai(const stHuPai& st)
{
	if (st.m_eHupaiType != ::msg_maj::hu_none)
	{
		m_vecHuPai.push_back(st);
	}
}

void CMaJiang::GetHuPai(uint16_t usPos, stHuPai& hupai) const
{
	for (vecHuPai::const_iterator iter = m_vecHuPai.begin(); iter != m_vecHuPai.end(); ++iter)
	{
		const stHuPai& st = *iter;
		if (st.m_usHupaiPos == usPos)
		{
			hupai = *iter;
			return;
		}
	}
}

void CMaJiang::DelHuPai(uint16_t usSeat)
{
	for (vecHuPai::iterator iter = m_vecHuPai.begin(); iter != m_vecHuPai.end();)
	{
		if ((*iter).m_usHupaiPos == usSeat)
		{
			iter = m_vecHuPai.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

::msg_maj::hu_way CMaJiang::GetHuWay() const
{
	for (vecHuPai::const_iterator iter = m_vecHuPai.begin(); iter != m_vecHuPai.end(); ++iter)
	{
		return (*iter).m_eHupaiWay;
	}

	return ::msg_maj::hu_way_none;
}

void CMaJiang::GetActionEvent(stSeatEvent& st) const
{
	if (m_vecSeatEvent.size() != 1)
	{
		return;
	}

	const stSeatEvent& st_yuan = m_vecSeatEvent[0];
	if (st_yuan.bAction == true)
	{
		st = st_yuan;
	}
}

::msg_maj::event_type CMaJiang::GetEventTypeBySeat(uint16_t usSeat) const
{
	for (vecSeatEvent::const_iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end(); ++iter)
	{
		if ((*iter).usSeat == usSeat)
		{
			return (*iter).etype;
		}
	}

	return ::msg_maj::e_none;
}

bool CMaJiang::IsHasHuEvent() const
{
	for (vecSeatEvent::const_iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end(); ++iter)
	{
		const stSeatEvent& st = *iter;
		if (st.etype == ::msg_maj::zi_mo_hu && st.bAction == true)
		{
			return true;
		}
	}

	return false;
}

void CMaJiang::DeleteHuPaiExtOne(uint16_t nSeat)
{
	for (vecHuPai::iterator it = m_vecHuPai.begin(); it != m_vecHuPai.end();)
	{
		if (it->m_usHupaiPos != nSeat)
		{
			it = m_vecHuPai.erase(it);
		}
		else
		{
			++it;
		}
	}
}

uint16_t CMaJiang::GetLastHuPaiTimes(uint16_t seat)
{	
	if (false)
	{
		for (vecLastHuInfo::iterator it = m_vecLastHuInfo.begin(); it != m_vecLastHuInfo.end(); ++it)
		{
			if (it->seat == seat)
			{
				return it->times;
			}
		}
	}
	return 0;
}

uint16_t CMaJiang::GetLastBankerTimes(uint16_t seat)
{
	if (false)
	{
		if (m_stLastBanker.seat == seat)
		{
			return m_stLastBanker.times;
		}
	}
	return 0;
}

void CMaJiang::SetSendCardPos(uint16_t usPos)
{
	if (usPos > m_pRoom->GetTotalPersons())
	{
		m_usSendCardPos = 0;
		//LOG(ERROR) << "CMaJiang::SetSendCardPos(): " << usPos;
		return;
	}

	if (usPos == m_pRoom->GetTotalPersons())
	{
		m_usSendCardPos = 0;
		return;
	}

	m_usSendCardPos = usPos;
}

bool CMaJiang::HasThisEventTypeBySeat(uint16_t usSeat, ::msg_maj::event_type etype) const
{
	for (vecSeatEvent::const_iterator iter = m_vecSeatEvent.begin(); iter != m_vecSeatEvent.end(); ++iter)
	{
		if ((*iter).usSeat == usSeat)
		{
			if (iter->etype == etype)
			{
				return true;
			}
		}
	}
	return false;
}

