#include "COnlineRecord.h"
#include "GameService.h"
#include "MysqlProtobufHelper.h"
#include "WorldUserMgr.h"

COnlineRecord::COnlineRecord():m_pSaveDataTimer(NULL),m_online_num(0), m_inroom_num(0)
{
}

COnlineRecord::~COnlineRecord()
{
}

void COnlineRecord::Init()
{
	m_pSaveDataTimer = new fogs::FogsTimer(*GameService::getMe().GetIoService());
	m_pSaveDataTimer->start(300 * 1000, boost::bind(&COnlineRecord::doRecord, this), fogs::FogsTimer::PERIODICAL_TIMER);
}

void COnlineRecord::doRecord()
{
	m_online_num = GameService::getMe().GetWorldUserMgr()->GetOnlineNum();
	if (m_last_online_num == m_online_num && m_last_inroom_num  == m_inroom_num)
	{
		return;
	}
	std::stringstream dataSql;
	dataSql << "insert into tb_online_record(time,online_num,inroom_num) values("
		<< time(NULL) << ", "
		<< m_online_num << ", "
		<< m_inroom_num << ")";
	doQuery(*GameService::getMe().GetLogRef(), dataSql.str());

	m_last_online_num = m_online_num;
	m_last_inroom_num = m_inroom_num;

	m_online_num = 0;
	m_inroom_num = 0;

}
