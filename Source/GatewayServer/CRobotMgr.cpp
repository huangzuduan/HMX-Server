#include "CRobotMgr.hpp"
#include "CRobot.hpp"


::boost::object_pool<CRobot> objpool;

CRobotMgr::CRobotMgr() :
	m_pGameConn(NULL)
{
	m_nGoTimes = 0;
	m_usID = 0;
	m_usGhostNum = 0;

	m_pTimer_verify = NULL;

	m_unProductID = 0;
	m_usPort = 0;
	m_usConnPort = 0;
	m_usRobotNum = 0;

	InitSound();
}

CRobotMgr::~CRobotMgr()
{
}

void CRobotMgr::InitSound()
{
	std::vector<stSound> tmpVecSound;

	{
		stSound st("tiao_1", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("tiao_2", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("tiao_3", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("tiao_4", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("tiao_5", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("tiao_6", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("tiao_7", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("tiao_8", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("tiao_9", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}

	//

	{
		stSound st("bing_1", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("bing_2", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("bing_3", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("bing_4", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("bing_5", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("bing_6", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("bing_7", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("bing_8", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("bing_9", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	//

	{
		stSound st("wan_1", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("wan_2", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("wan_3", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("wan_4", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("wan_5", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("wan_6", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("wan_7", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("wan_8", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("wan_9", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}

	// 字
	{
		stSound st("zi_1", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("zi_2", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("zi_3", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("zi_4", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("zi_5", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("zi_6", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("zi_7", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("buhua", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("x_hu", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("x_peng", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("an_gang", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("x_gang", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("x_zimo", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}
	{
		stSound st("zi_7", 1, 1, 1, 1);
		tmpVecSound.push_back(st);
	}

	int index = 0;
	for (size_t i = 0; i < tmpVecSound.size(); ++i)
	{
		stSound st = tmpVecSound[i];
		for (int i = 0; i < st.normal_man; ++i)
		{
			st.msg_index = index++;
			m_mapSoundData.insert(std::make_pair(st.path, st));
		}

		for (int i = 0; i < st.normal_women; ++i)
		{
			st.msg_index = index++;
			m_mapSoundData.insert(std::make_pair(st.path, st));
		}

		for (int i = 0; i < st.fy_man; ++i)
		{
			st.msg_index = index++;
			m_mapSoundData.insert(std::make_pair(st.path, st));
		}

		for (int i = 0; i < st.fy_women; ++i)
		{
			st.msg_index = index++;
			m_mapSoundData.insert(std::make_pair(st.path, st));
		}
	}
}

int32_t CRobotMgr::GetOutCardSound(CRobot* robot, int16_t type, int16_t point)
{
	int16_t changeType = type;
	std::stringstream key;
	switch (changeType) {
	case 0:
		key << "zi_" << point;
		break;
	case 1:
		key << "bing_" << point;
		break;
	case 2:
		key << "tiao_" << point;
		break;
	case 3:
		key << "wan_" << point;
		break;
	default:
		return -1;
	}
	std::map<std::string, stSound>::const_iterator it = m_mapSoundData.find(key.str());
	if (it != m_mapSoundData.end()) {
		return GetOutCardSoundIndex(robot, it->second);
	}
	return -1;
}

int32_t CRobotMgr::GetStateSound(CRobot* robot, ::msg_maj::event_type state)
{
	std::stringstream key;
	switch (state)
	{
	case msg_maj::e_none:
		break;
	case msg_maj::zi_mo_hu:
	case msg_maj::dian_pao_hu:
		key << "x_hu";
		break;
	case msg_maj::an_gang:
	case msg_maj::ming_gang:
	case msg_maj::guo_shou_gang:
		key << "x_gang";
		break;
	case msg_maj::pong:
		key << "x_peng";
		break;
	default:
		return -1;
		break;
	}

	std::map<std::string, stSound>::const_iterator it = m_mapSoundData.find(key.str());
	if (it != m_mapSoundData.end()) {
		return GetOutCardSoundIndex(robot, it->second);
	}
	return -1;
}

int32_t CRobotMgr::GetOutCardSoundIndex(CRobot* robot, const stSound& cardSound)
{
	int16_t manvoice = robot->role.sexual(); // 0男1女声
	int16_t normalVoice = 0; // 0本地1方言
	int16_t currLanType = manvoice + normalVoice * 2;//用0-3表示当前语言

	if (currLanType >= 4 || currLanType < 0) {
		return -1;
	}

	//当前语音的数量
	int16_t subCount = 0;
	int16_t countArray[] = { cardSound.normal_man, cardSound.normal_women, cardSound.fy_man, cardSound.fy_women };

	//当前起始序列
	int16_t subStartIndex = 0;

	for (int16_t i = 0; i < (sizeof(countArray) / sizeof(countArray[0])); i++) {
		if (i == currLanType) {
			subCount = countArray[i];
			break;
		}
		subStartIndex += countArray[i];
	}

	if (subCount <= 0) {
		return -1;
	}

	int16_t subIndex = randBetween(0, subCount - 1);
	if (subIndex >= subCount) {
		return -1;
	}

	int32_t finalIndex = cardSound.msg_index + subStartIndex + subIndex;
	return finalIndex;
}

bool CRobotMgr::StartNewRobot(zSession* pSession,uint32_t sessionID, uint64_t uid)
{
	std::stringstream smData;
	smData << m_strRobotName << sessionID;
	CRobot* pRobot = new CRobot(pSession,smData.str(),sessionID,uid);
	if (!zEntryMgr< zEntryID<0> >::addEntry(pRobot))
	{
		delete pRobot;
		pRobot = NULL;
		return false;
	}
	else
	{
		pRobot->Init();
		return true;
	}
}

void CRobotMgr::StopRebot(uint64_t uid)
{
	struct MyStruct : public execEntry<CRobot>
	{
		MyStruct(uint64_t _uid):m_uid(_uid), m_robot(NULL)
		{
		
		}
		virtual bool exec(CRobot *entry)
		{
			if (entry->m_usUid == m_uid)
			{
				m_robot = entry;
			}
			return true;
		}
		uint64_t m_uid;
		CRobot* m_robot;
	};

	MyStruct myexec(uid);
	execEveryRobot(myexec);
}

CRobot* CRobotMgr::GetRobot(uint32_t unSessionID) const
{
	return (CRobot*)zEntryMgr< zEntryID<0> >::getEntryByID((uint64_t)unSessionID);
}

CRobot* CRobotMgr::GetMaster(CRobot* entry)
{
	uint32_t offset = (entry->GetID32() - 1) % 4;
	uint32_t roomerID = entry->GetID32() - offset;
	CRobot* master = CRobotMgr::Instance()->GetRobot(roomerID);
	return master;
}

void CRobotMgr::GetFriends(CRobot* entry, std::vector<CRobot*>& vecFriend)
{
	if (entry->bIsRoomer)
	{
		for (int i = 1; i <= 3; ++i)
		{
			CRobot* robot = GetRobot(entry->GetID32() + i);
			if (robot)
			{
				vecFriend.push_back(robot);
			}
		}
	}
}

std::string CRobotMgr::GetPaiZhong(uint16_t usPai)
{
	std::stringstream sql_data;
	switch (usPai)
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
	return sql_data.str();
}

void CRobotMgr::OpenRoom()
{
	return; //关闭机器人开房功能

	struct MyStruct : public execEntry<CRobot>
	{
		virtual bool exec(CRobot *entry)
		{
			if (entry->bIsRoomer)
			{
				entry->SetActionType(eActionType_OpenRoom);
			}	
			return true;
		}
	};

	MyStruct myexec;
	execEveryRobot(myexec);
}

void CRobotMgr::CheckLoginAll()
{
	struct MyStruct : public execEntry<CRobot>
	{
		MyStruct()
		{
			unNum = 0;
		}

		virtual bool exec(CRobot *entry)
		{
			if (entry->bIsLogin_2)
			{
				++unNum;
			}

			return true;
		}

		uint32_t unNum;
	};

	MyStruct myexec;
	execEveryRobot(myexec);

	if (myexec.unNum == CRobotMgr::size())
	{
		OpenRoom();
	}
}

void CRobotMgr::CheckHasVerifyPai(const std::vector<uint16_t>& pailist)
{
	std::stringstream smData;
	for (std::vector<uint16_t>::const_iterator iter = pailist.begin(); iter != pailist.end(); ++iter)
	{
		smData << *iter;
	}

	uint64_t ulIndex = 0;
	smData >> ulIndex;

	std::map<uint64_t, std::vector<uint16_t> >::const_iterator it = group_list.find(ulIndex);
	if (it == group_list.end())
	{
		group_list.insert(std::make_pair(ulIndex, pailist));

		H::logger->info("CheckHasVerifyPai() size: %d",group_list.size());
	}
}

void CRobotMgr::AddVerifyPai(uint16_t num1, uint16_t num2, uint16_t num3, uint16_t num4, uint16_t num5, uint16_t num6, uint16_t num7, uint16_t num8, uint16_t num9)
{
	std::vector<uint16_t> list1;
	if (num1 > 0)
	{
		for (uint16_t i = 0; i < num1; ++i)
		{
			list1.push_back(1);
		}
	}
	if (num2 > 0)
	{
		for (uint16_t i = 0; i < num2; ++i)
		{
			list1.push_back(2);
		}
	}
	if (num3 > 0)
	{
		for (uint16_t i = 0; i < num3; ++i)
		{
			list1.push_back(3);
		}
	}
	if (num4 > 0)
	{
		for (uint16_t i = 0; i < num4; ++i)
		{
			list1.push_back(4);
		}
	}
	if (num5 > 0)
	{
		for (uint16_t i = 0; i < num5; ++i)
		{
			list1.push_back(5);
		}
	}
	if (num6 > 0)
	{
		for (uint16_t i = 0; i < num6; ++i)
		{
			list1.push_back(6);
		}
	}
	if (num7 > 0)
	{
		for (uint16_t i = 0; i < num7; ++i)
		{
			list1.push_back(7);
		}
	}
	if (num8 > 0)
	{
		for (uint16_t i = 0; i < num8; ++i)
		{
			list1.push_back(8);
		}
	}
	if (num9 > 0)
	{
		for (uint16_t i = 0; i < num9; ++i)
		{
			list1.push_back(9);
		}
	}

	std::sort(list1.begin(), list1.end());
	CheckHasVerifyPai(list1);
}

void CRobotMgr::GetGroupPai(uint16_t usNum)
{
	for (uint16_t i = 0; i < 5; ++i)
	{
		for (uint16_t j = 0; j < 5; ++j)
		{
			for (uint16_t k = 0; k < 5; ++k)
			{
				for (uint16_t l = 0; l < 5; ++l)
				{
					if (i + j + k + l == usNum)
					{
						AddVerifyPai(i, j, k, l, 0, 0, 0, 0, 0);
						break;
					}
					for (uint16_t m = 0; m < 5; ++m)
					{
						if (i + j + k + l + m == usNum)
						{
							AddVerifyPai(i, j, k, l, m, 0, 0, 0, 0);
							break;
						}
						for (uint16_t n = 0; n < 5; ++n)
						{
							if (i + j + k + l + m + n == usNum)
							{
								AddVerifyPai(i, j, k, l, m, n, 0, 0, 0);
								break;
							}
							for (uint16_t o = 0; o < 5; ++o)
							{
								if (i + j + k + l + m + n + o == usNum)
								{
									AddVerifyPai(i, j, k, l, m, n, o, 0, 0);
									break;
								}
								for (uint16_t p = 0; p < 5; ++p)
								{
									if (i + j + k + l + m + n + o + p == usNum)
									{
										AddVerifyPai(i, j, k, l, m, n, o, p, 0);
										break;
									}
									for (uint16_t q = 0; q < 5; ++q)
									{
										if (i + j + k + l + m + n + o + p + q == usNum)
										{
											AddVerifyPai(i, j, k, l, m, n, o, p, q);
											break;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
}

void CRobotMgr::GetGroupPaiZi(uint16_t usNum)
{
	for (uint16_t i = 0; i < 5; ++i)
	{
		for (uint16_t j = 0; j < 5; ++j)
		{
			for (uint16_t k = 0; k < 5; ++k)
			{
				for (uint16_t l = 0; l < 5; ++l)
				{
					if (i + j + k + l == usNum)
					{
						AddVerifyPai(i, j, k, l, 0, 0, 0, 0, 0);
						break;
					}
					for (uint16_t m = 0; m < 5; ++m)
					{
						if (i + j + k + l + m == usNum)
						{
							AddVerifyPai(i, j, k, l, m, 0, 0, 0, 0);
							break;
						}
						for (uint16_t n = 0; n < 5; ++n)
						{
							if (i + j + k + l + m + n == usNum)
							{
								AddVerifyPai(i, j, k, l, m, n, 0, 0, 0);
								break;
							}
						}
					}
				}
			}
		}
	}
}

void CRobotMgr::GeneratePai(uint32_t usGhostNum)
{
	m_usGhostNum = usGhostNum;

	H::logger->info("CMajingRule::GeneratePai() usGhostNum:%d", usGhostNum);

	uint16_t usNum = 14 - usGhostNum;
	GetGroupPai(usNum);

	H::logger->info("CMajingRule::GeneratePai() size: %d",group_list.size());
}

void CRobotMgr::GeneratePai_Jiang(uint32_t usGhostNum)
{
	m_usGhostNum = usGhostNum;

	H::logger->info("CMajingRule::GeneratePai_Jiang() usGhostNum:%d ", usGhostNum);

	uint16_t usNum = 14 - usGhostNum - 2;
	GetGroupPai(usNum);

	H::logger->info("CMajingRule::GeneratePai_Jiang() size: %d", group_list.size());
}

void CRobotMgr::GeneratePaiZi(uint32_t usGhostNum)
{
	m_usGhostNum = usGhostNum;

	H::logger->info("CMajingRule::GeneratePaiZi() usGhostNum: %d" , usGhostNum);

	uint16_t usNum = 14 - usGhostNum;

	GetGroupPaiZi(usNum);

	H::logger->info("CMajingRule::GeneratePaiZi() size: %d" ,group_list.size());
}

void CRobotMgr::GeneratePaiZi_Jiang(uint32_t usGhostNum)
{
	m_usGhostNum = usGhostNum;

	H::logger->info("CMajingRule::GeneratePaiZi_Jiang() usGhostNum: %d" , usGhostNum);

	uint16_t usNum = 14 - usGhostNum - 2;

	GetGroupPaiZi(usNum);

	H::logger->info("CMajingRule::GeneratePaiZi_Jiang() size: %d" , group_list.size());
}

void CRobotMgr::GeneratePai_ting(uint32_t usGhostNum)
{
	m_usGhostNum = usGhostNum;

	H::logger->info("CMajingRule::GeneratePai_ting() usGhostNum:%d " ,usGhostNum);

	uint16_t usNum = 14 - usGhostNum;
	GetGroupPai(usNum);

	H::logger->info("CMajingRule::GeneratePai_ting() size: %d" , group_list.size());
}

void CRobotMgr::GeneratePai_ting_Jiang(uint32_t usGhostNum)
{
	m_usGhostNum = usGhostNum;

	H::logger->info("CMajingRule::GeneratePai_ting_Jiang() usGhostNum:%d ", usGhostNum);

	uint16_t usNum = 14 - usGhostNum - 2;
	GetGroupPai(usNum);

	H::logger->info("CMajingRule::GeneratePai_ting_Jiang() size: %d" , group_list.size());
}
