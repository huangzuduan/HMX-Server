#include "COnlineRecord.h"
#include "CWorld.hpp"
#include "GameService.h"


COnlineRecord::COnlineRecord():m_pSaveDataTimer(NULL),m_online_num(0), m_roomcard_num(0), m_inn_num(0)
{
}


COnlineRecord::~COnlineRecord()
{
}

void COnlineRecord::Init()
{
	m_pSaveDataTimer = new fogs::FogsTimer(*GameService::Instance()->GetIoService());
	m_pSaveDataTimer->start(60 * 1000, boost::bind(&COnlineRecord::doRecord, this), fogs::FogsTimer::PERIODICAL_TIMER);
}

void COnlineRecord::AddRoomcard(int32_t num)
{
	m_roomcard_num += num;
}

void COnlineRecord::doRecord()
{
	m_online_num = CWorld::Instance()->GetOnlinePlayerNum();

	::fogs::proto::msg::SaveOnlinePlayer sendProto;
	sendProto.set_time(time(NULL));
	sendProto.set_online_num(m_online_num);
	sendProto.set_roomcard_num(m_roomcard_num);
	sendProto.set_inn_num(m_inn_num);

	m_online_num = 0;
	m_roomcard_num = 0;
	m_inn_num = 0;
	GameService::Instance()->SendToDp(::comdef::msg_ss, ::msg_maj::SaveOnlinePlayerID,sendProto);
}
