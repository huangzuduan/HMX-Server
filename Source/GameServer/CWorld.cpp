#include "CWorld.hpp"
#include "CPlayer.hpp"
#include "CRoomMgr.hpp"
#include "CNoticeMgr.hpp"
#include "CMailMgr.hpp"
#include "GameService.h"
#include "CMaJiang.hpp"

CWorld::CWorld() :
	m_pSaveDataTimer(NULL)
{
}

CWorld::~CWorld()
{
	Release();
}

bool CWorld::Init()
{
	
	m_pSaveDataTimer = new fogs::FogsTimer(*GameService::Instance()->GetIoService());
	m_pSaveDataTimer->start(g_unSaveDataTime * 1000, boost::bind(&CWorld::SavePlayerData, this), fogs::FogsTimer::PERIODICAL_TIMER);

	return true;
}

void CWorld::Release()
{

	if (m_pSaveDataTimer)
	{
		m_pSaveDataTimer->cancel();
		S_SAFE_DELETE(m_pSaveDataTimer);
	}

	for (mapPlayerBySessionID::iterator iter = m_mapPlayerBySessionID.begin(); iter != m_mapPlayerBySessionID.end(); ++iter)
	{
		S_SAFE_DELETE(iter->second);
		g_objpoolPlayer.destroy(iter->second);
	}

	m_mapPlayerBySessionID.clear();
	m_mapPlayerByUUID.clear();
}

void CWorld::AddPlayer(CPlayer* pPlayer)
{
	if (NULL == pPlayer)
	{
		return;
	}

	mapPlayerByUUID::iterator iter = m_mapPlayerByUUID.find(pPlayer->GetCharID());
	if (iter != m_mapPlayerByUUID.end())
	{
		return;
	}

	m_mapPlayerByUUID.insert(std::make_pair(pPlayer->GetCharID(), pPlayer));
	m_mapPlayerBySessionID.insert(std::make_pair(pPlayer->GetSessionID(), pPlayer));
	m_umapPlayerByAccount.insert(std::make_pair(pPlayer->GetAccount(), pPlayer));

	H::logger->info("==== player num: %d ", m_mapPlayerBySessionID.size());

	GetOnlinePlayerNum();
}

CPlayer* CWorld::CreatePlayer(uint64_t unSessionID, uint32_t unFepServerID, const ::msg_maj::Role& proData)
{	
	CPlayer* ply = g_objpoolPlayer.construct(unSessionID, unFepServerID, proData);
	AddPlayer(ply);
	return ply;
}

CPlayer* CWorld::LoadPlayer(uint64_t unSessionID,uint32_t unFepServerID, const ::msg_maj::Role& proData)
{
	CPlayer* ply = g_objpoolPlayer.construct(unSessionID, unFepServerID, proData);
	if (!ply->Init()) {
		g_objpoolPlayer.destroy(ply);
		return NULL;
	}
	
	AddPlayer(ply);
	return ply;
}


CPlayer* CWorld::GetPlayerBySessionID(uint64_t unSessionID) const
{
	mapPlayerBySessionID::const_iterator iter = m_mapPlayerBySessionID.find(unSessionID);
	if (iter == m_mapPlayerBySessionID.end())
	{
		std::map<uint64_t, CPlayer*>::const_iterator itRobot = m_mapRobotID.find(unSessionID);
		if (itRobot != m_mapRobotID.end())
		{
			return itRobot->second;
		}
		return NULL;
	}
	return iter->second;
}

CPlayer* CWorld::GetPlayerByUUID(uint64_t ulUUID) const
{
	mapPlayerByUUID::const_iterator iter = m_mapPlayerByUUID.find(ulUUID);
	if (iter == m_mapPlayerByUUID.end())
	{
		return NULL;
	}

	return iter->second;
}

CPlayer* CWorld::GetPlayerByAccount(const std::string& strAccount) const
{
	umapPlayerByAccount::const_iterator iter = m_umapPlayerByAccount.find(strAccount);
	if (iter == m_umapPlayerByAccount.end())
	{
		return NULL;
	}

	return iter->second;
}

void CWorld::ResetSessionID(CPlayer* pPlayer, uint64_t unSessionID)
{
	if (NULL == pPlayer || unSessionID <= 0)
	{
		//LOG(ERROR) << "CWorld::ResetSessionID()";
		return;
	}

	mapPlayerBySessionID::iterator iter = m_mapPlayerBySessionID.find(pPlayer->GetSessionID());
	if (iter != m_mapPlayerBySessionID.end())
	{
		m_mapPlayerBySessionID.erase(iter);
	}

	pPlayer->SetSessionID(unSessionID);
	m_mapPlayerBySessionID.insert(std::make_pair(unSessionID, pPlayer));
}

void CWorld::LeaveGame(uint32_t unSessionID)
{
	DelSessionIP(unSessionID);

	mapPlayerBySessionID::iterator iter = m_mapPlayerBySessionID.find(unSessionID);
	if (iter == m_mapPlayerBySessionID.end())
	{
		return;
	}

	CPlayer* pPlayer = iter->second;
	if (NULL == pPlayer)
	{
		m_mapPlayerBySessionID.erase(iter);
		return;
	}

	if (pPlayer->Disconnect())
	{
		return;
	}

	pPlayer->LeaveGame();

	std::string strAccount = pPlayer->GetAccount();
	uint64_t ulCharID = pPlayer->GetCharID();

	mapPlayerByUUID::iterator it = m_mapPlayerByUUID.find(pPlayer->GetCharID());
	if (it != m_mapPlayerByUUID.end())
	{
		m_mapPlayerByUUID.erase(it);
	}

	umapPlayerByAccount::iterator it_ = m_umapPlayerByAccount.find(strAccount);
	if (it_ != m_umapPlayerByAccount.end())
	{
		m_umapPlayerByAccount.erase(it_);
	}

	g_objpoolPlayer.destroy(pPlayer);
	m_mapPlayerBySessionID.erase(iter);

	CMailMgr::Instance()->OfflinePlayer(pPlayer->GetCharID());
}

void CWorld::SavePlayerData()
{
	for (std::set<uint64_t>::iterator iter = m_setSavePlayer.begin(); iter != m_setSavePlayer.end(); ++iter)
	{
		mapPlayerByUUID::iterator it = m_mapPlayerByUUID.find(*iter);
		if (it == m_mapPlayerByUUID.end())
		{
			continue;
		}

		CPlayer* pPlayer = it->second;
		if (pPlayer)
		{
			pPlayer->SaveDataToDB(0);
		}
	}

	m_setSavePlayer.clear();
}

void CWorld::GatewayDisconnect()
{
}

void CWorld::SendWorldMsg(uint16_t usCmd, uint16_t usMsg, const google::protobuf::Message& msg)
{
	for (mapPlayerBySessionID::iterator iter = m_mapPlayerBySessionID.begin(); iter != m_mapPlayerBySessionID.end(); ++iter)
	{
		CPlayer* pPlayer = iter->second;
		if (pPlayer)
		{
			pPlayer->SendMsgToClient(usCmd, usMsg, msg);
		}
	}
}

void CWorld::AddSessionIP(uint64_t unSessionID, const std::string& strIP)
{
	//LOG(WARNING) << "CWorld::AddSessionIP(): " << unSessionID << " " << strIP;
	std::map<uint64_t, std::string>::iterator iter = m_mapSessionIP.find(unSessionID);
	if (iter == m_mapSessionIP.end())
	{
		m_mapSessionIP.insert(std::make_pair(unSessionID, strIP));
		return;
	}

	iter->second = strIP;
}

void CWorld::DelSessionIP(uint64_t unSessionID)
{
	std::map<uint64_t, std::string>::iterator iter = m_mapSessionIP.find(unSessionID);
	if (iter == m_mapSessionIP.end())
	{
		return;
	}

	m_mapSessionIP.erase(iter);
}

void CWorld::AddSessionAccountName(uint32_t unUserID, const std::string& strAccount, const std::string& strName, const std::string& strIconAddr)
{
	//LOG(INFO) << "CWorld::AddSessionAccountName(): " << strAccount;
	stSessionAccount st;
	st.unUserID = unUserID;
	st.strAccount = strAccount;
	st.strName = strName;
	st.strIconAddr = strIconAddr;
	m_umapSessionAccountName[strAccount] = st;
}

void CWorld::DelSessionAccountName(const std::string& strAccount)
{
	umapSessionAccountName::iterator iter = m_umapSessionAccountName.find(strAccount);
	if (iter == m_umapSessionAccountName.end())
	{
		return;
	}

	m_umapSessionAccountName.erase(iter);
}

void CWorld::GetSessionAccount(const std::string& strAccount, stSessionAccount& st)
{
	umapSessionAccountName::iterator iter = m_umapSessionAccountName.find(strAccount);
	if (iter == m_umapSessionAccountName.end())
	{
		return;
	}

	st = iter->second;
	m_umapSessionAccountName.erase(iter);
}

bool CWorld::SessionAccount(const std::string& strAccount) const
{
	umapSessionAccountName::const_iterator iter = m_umapSessionAccountName.find(strAccount);
	if (iter == m_umapSessionAccountName.end())
	{
		return false;
	}

	return true;
}

std::string CWorld::GetSessionIP(uint64_t unSessionID)
{
	std::map<uint64_t, std::string>::iterator iter = m_mapSessionIP.find(unSessionID);
	if (iter == m_mapSessionIP.end())
	{
		return "";
	}
	return iter->second;
}

void CWorld::AddRoomInfo(uint32_t unRoomID, uint32_t unServerID)
{
	std::map<uint32_t, uint32_t>::iterator iter = m_mapRoomInfo.find(unRoomID);
	if (iter == m_mapRoomInfo.end())
	{
		m_mapRoomInfo.insert(std::make_pair(unRoomID, unServerID));
	}
}

void CWorld::DelRoomInfo(uint32_t unRoomID)
{
	std::map<uint32_t, uint32_t>::iterator iter = m_mapRoomInfo.find(unRoomID);
	if (iter == m_mapRoomInfo.end())
	{
		return;
	}

	m_mapRoomInfo.erase(iter);
}

uint32_t CWorld::GetServerIDByRoomID(uint32_t unRoomID) const
{
	std::map<uint32_t, uint32_t>::const_iterator iter = m_mapRoomInfo.find(unRoomID);
	if (iter == m_mapRoomInfo.end())
	{
		return 0;
	}
	return iter->second;
}

uint32_t CWorld::GetOnlinePlayerNum() const
{
	uint32_t unNum = 0;
	for (mapPlayerByUUID::const_iterator iter = m_mapPlayerByUUID.begin(); iter != m_mapPlayerByUUID.end(); ++iter)
	{
		CPlayer* pPlayer = iter->second;
		if (pPlayer && !pPlayer->IsDisconnect())
		{
			++unNum;
		}
	}
	H::logger->info("CWorld::GetOnlinePlayerNum():%d " , unNum);
	return unNum;
}

void CWorld::AddSavePlayer(uint64_t ulCharID)
{
	if (m_setSavePlayer.find(ulCharID) == m_setSavePlayer.end())
	{
		m_setSavePlayer.insert(ulCharID);
	}
}

void CWorld::DelSavePlayer(uint64_t ulCharID)
{
	std::set<uint64_t>::iterator iter = m_setSavePlayer.find(ulCharID);
	if (iter == m_setSavePlayer.end())
	{
		return;
	}

	m_setSavePlayer.erase(iter);
}

CPlayer* CWorld::GetFreeRobot()
{	
	for (mapPlayerByUUID::iterator it = m_mapPlayerByUUID.begin(); it != m_mapPlayerByUUID.end(); ++it)
	{
		if (it->second->IsRobot())
		{
			if (it->second->GetRoomID() < 1)
			{
				return it->second;
			}
		}
	}
	return NULL;
}

void CWorld::DelRobotByUid(uint64_t uid)
{
	std::map<uint64_t, CPlayer*>::iterator it = m_mapRobotID.begin();
	for (; it != m_mapRobotID.end(); ++it)
	{
		if (it->second->GetCharID() == uid)
		{
			m_mapRobotID.erase(it);
			break;
		}
	}
}

void CWorld::AddRobot(CPlayer* pPlayer)
{
	m_mapRobotID.insert(make_pair(pPlayer->GetSessionID(), pPlayer));
}

void CWorld::SendMoneyLog(uint16_t charID, const std::string& nickname, int32_t num, int32_t totalNum, ::fogs::proto::msg::log_type type)
{
	fogs::proto::msg::SaveMoneyLogRequest proto;
	::fogs::proto::msg::MoneyLog* moneyLog = proto.mutable_moneylog();

	zUUID zuuid;
	moneyLog->set_log_id(zuuid.generate32());
	moneyLog->set_room_card(num);
	moneyLog->set_log_type(type);
	moneyLog->set_user_id(charID);
	moneyLog->set_time(time(NULL));
	moneyLog->set_room_total(totalNum);

	GameService::Instance()->SendToDp(::comdef::msg_ss, ::msg_maj::SaveMoneyLogRequestID, proto);
}

void CWorld::LoadConfigFromDB()
{
	fogs::proto::msg::GetRewardConfigReq proReq1;
	GameService::Instance()->SendToDp(::comdef::msg_ss, ::msg_maj::GetRewardConfigReqID, proReq1);

	fogs::proto::msg::GetFreeConfigReq proReq2;
	GameService::Instance()->SendToDp(::comdef::msg_ss, ::msg_maj::GetFreeConfigReqID, proReq2);

	fogs::proto::msg::GetFreeConfigReq proReq3;
	GameService::Instance()->SendToDp(::comdef::msg_ss, ::msg_maj::GetNotifyConfigReqID, proReq3);

	fogs::proto::msg::GetRoomSetConfigReq proReq4;
	GameService::Instance()->SendToDp(::comdef::msg_ss, ::msg_maj::GetRoomSetConfigReqID, proReq4);
}

bool CWorld::IsFreeCard() const
{
	if (m_proFreeConfig.start_time() <= time(NULL) && m_proFreeConfig.end_time() >= time(NULL))
	{
		return true;
	}
	return false;
}