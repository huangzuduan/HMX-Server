#include "CRoomMgr.hpp"
#include "GameService.h"
#include "FogsTimerService.hpp"
#include "CRoom.hpp"

CRoomMgr::CRoomMgr() :
	m_pTimer(NULL)
{
}

CRoomMgr::~CRoomMgr()
{
	Release();
}

bool CRoomMgr::Init()
{
	m_unRoomIDMin = 100000;
	m_unRoomIDMax = m_unRoomIDMin + g_unRoomIDNum;
	for (uint32_t i = 0; i < g_unRoomIDNum; ++i)
	{
		m_arrRoomID[i] = i + m_unRoomIDMin;
	}
	m_unRemainRoomIDNum = g_unRoomIDNum;

	m_pTimer = new fogs::FogsTimer(*GameService::Instance()->GetIoService());
	m_pTimer->start(10 * 1000, boost::bind(&CRoomMgr::ClearRoom, this), fogs::FogsTimer::PERIODICAL_TIMER);

	return true;
}

void CRoomMgr::Release()
{
	if (m_pTimer)
	{
		m_pTimer->cancel();
		SAFE_DELETE(m_pTimer);
	}
	for (mapRoom::iterator iter = m_mapRoom.begin(); iter != m_mapRoom.end(); ++iter)
	{
		g_objpoolRoom.destroy(iter->second);

		//SAFE_DELETE(iter->second);
	}
}

uint32_t CRoomMgr::GenerateRoomID()
{
	/*uint16_t usNum1 = rand() % 10;
	if (usNum1 == 0) { ++usNum1; }
	uint16_t usNum2 = rand() % 10;
	uint16_t usNum3 = rand() % 10;
	uint16_t usNum4 = rand() % 10;
	uint16_t usNum5 = rand() % 10;
	uint16_t usNum6 = rand() % 10;
	uint32_t unNum = usNum1 * 100000 + usNum2 * 10000 + usNum3 * 1000 + usNum4 * 100 + usNum5 * 10 + usNum6;
	while (m_mapRoom.find(unNum) != m_mapRoom.end())
	{
		++unNum;
	}*/

	uint32_t unIndex = rand() % m_unRemainRoomIDNum;
	uint32_t unRoomID = m_arrRoomID[unIndex];
	m_arrRoomID[unIndex] = m_arrRoomID[m_unRemainRoomIDNum-- - 1];

	return unRoomID;
}

void CRoomMgr::RecoveryRoomID(uint32_t unRoomID)
{
	if (unRoomID < m_unRoomIDMin || unRoomID > m_unRoomIDMax)
	{
		//LOG(ERROR) << "CRoomMgr::RecoveryRoomID() room id: " << unRoomID;
		return;
	}

	if (m_unRemainRoomIDNum >= m_unRoomIDMax)
	{
		//LOG(ERROR) << "CRoomMgr::RecoveryRoomID() m_unRemainRoomIDNum: " << m_unRemainRoomIDNum;
		return;
	}

	m_arrRoomID[m_unRemainRoomIDNum++] = unRoomID;
}

CRoom* CRoomMgr::CreateRoom(::msg_maj::RoomType roomType, msg_maj::maj_type majType, uint64_t roomerID, uint64_t matchID, const ::msg_maj::RoomOption& option)
{
	CRoom* pRoom = g_objpoolRoom.construct(roomType,majType,option);
	if (NULL == pRoom)
	{
		return NULL;
	}
	pRoom->SetRoomer(roomerID);
	m_mapRoom.insert(std::make_pair(pRoom->GetRoomID(), pRoom));
	return pRoom;
}

void CRoomMgr::DelRoomByID(uint32_t unRoomID)
{
	mapRoom::iterator iter = m_mapRoom.find(unRoomID);
	if (iter == m_mapRoom.end())
	{
		return;
	}

	RecoveryRoomID(unRoomID);
	g_objpoolRoom.destroy(iter->second);

	//SAFE_DELETE(pRoom);
	m_mapRoom.erase(iter);
}

CRoom* CRoomMgr::GetRoomByID(uint32_t unRoomID) const
{
	mapRoom::const_iterator iter = m_mapRoom.find(unRoomID);
	if (iter == m_mapRoom.end())
	{
		return NULL;
	}

	return iter->second;
}

void CRoomMgr::AddCloseRoom(uint32_t unRoomID)
{
	if (unRoomID <= 0)
	{
		//LOG(ERROR) << "CRoomMgr::AddCloseRoom(): " << unRoomID;
		return;
	}

	std::set<uint32_t>::iterator iter = m_setCloseRoom.find(unRoomID);
	if (iter == m_setCloseRoom.end())
	{
		m_setCloseRoom.insert(unRoomID);
	}
}

void CRoomMgr::ClearRoom()
{
	for (std::set<uint32_t>::iterator iter = m_setCloseRoom.begin(); iter != m_setCloseRoom.end(); ++iter)
	{
		mapRoom::iterator it = m_mapRoom.find(*iter);
		if (it == m_mapRoom.end())
		{
			continue;
		}

		CRoom* pRoom = it->second;
		if (pRoom && pRoom->IsClose())
		{
			//LOG(WARNING) << "CRoomMgr::ClearRoom() room id: " << pRoom->GetRoomID();

			RecoveryRoomID(pRoom->GetRoomID());
			g_objpoolRoom.destroy(pRoom);
			m_mapRoom.erase(it);
		}
	}

	m_setCloseRoom.clear();
}