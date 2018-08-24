#include "SrvEngine.h"

zNetSerivce::zNetSerivce(const std::string &_name) 
	:zService(_name)
	,mServerID(0)
	,mServerType(0)
	,netioTaskTimer(NULL)
	,timeTickTaskTimer(NULL)
	,flatID(0)
	,flatZone(0)
	,m_config(NULL)
	,m_data(NULL)
	,m_log(NULL)
{
	mSessionMgr = new zSessionMgr();
	mServerRegMgr = new zServerRegMgr();
	mSrvSerivceMgr = new zSrvSerivceMgr();
	mServerID = strtoul(H::global["serverid"].c_str(), NULL, 10);
	mServerType = mServerID / 1000;
}

// 将消息发到某区
void zNetSerivce::sendToServerZone(GeneralRoute_t route, const NetMsgSS* cmd, int32_t len)
{

}

void zNetSerivce::sendToServerZoneUser(GeneralRoute_t route, int64_t toUserID, const NetMsgSS* cmd, int32_t len)
{

}

																								
void zNetSerivce::gotoServerZone(GeneralRoute_t route) 
{

}

bool zNetSerivce::doConnectMysql(const ::config::SerivceInfo& info)
{
	if (!m_config && info.serivceid() == 1)
	{
		unsigned int readtimeout = 10;
		unsigned int writetimeout = 10;
		unsigned int conntimeout = 10;
		m_config = new db::DBConnection();
		m_config->setReadTimeout(readtimeout);
		m_config->setWriteTimeout(writetimeout);
		m_config->setConnectTimeout(conntimeout);
		bool ret = m_config->connect(info.serivceip(), info.serivceuser(), info.serivcepasswd(), info.serivcevalue(), info.serivceport());
		return ret;
	}
	else if (!m_data && info.serivceid() == 2)
	{
		unsigned int readtimeout = 10;
		unsigned int writetimeout = 10;
		unsigned int conntimeout = 10;
		m_data = new db::DBConnection();
		m_data->setReadTimeout(readtimeout);
		m_data->setWriteTimeout(writetimeout);
		m_data->setConnectTimeout(conntimeout);
		bool ret = m_data->connect(info.serivceip(), info.serivceuser(), info.serivcepasswd(), info.serivcevalue(), info.serivceport());
		return ret;
	}
	else if (!m_log  && info.serivceid() == 3)
	{
		unsigned int readtimeout = 10;
		unsigned int writetimeout = 10;
		unsigned int conntimeout = 10;
		m_log = new db::DBConnection();
		m_log->setReadTimeout(readtimeout);
		m_log->setWriteTimeout(writetimeout);
		m_log->setConnectTimeout(conntimeout);
		bool ret = m_log->connect(info.serivceip(), info.serivceuser(), info.serivcepasswd(), info.serivcevalue(), info.serivceport());
		return ret;
	}
	else
	{
		ASSERT(0);
	}
	return true;
}

void zNetSerivce::bindTimer()
{
	netioTaskTimer = new zTaskTimer(IO_UPDTATE_TIME, boost::bind(&zNetSerivce::mainioUpdate, this, _1));
	netioTaskTimer->start();

	timeTickTaskTimer = new zTaskTimer(TIMETICK_UPDATE_TIME, boost::bind(&zNetSerivce::timerTickUpdate, this, _1));
	timeTickTaskTimer->start();
}

void zNetSerivce::mainioUpdate(const zTaskTimer* timer)
{
	mLastIoTimer = time(NULL);
	netioUpdate(timer);
}

void zNetSerivce::timerTickUpdate(const zTaskTimer* timer)
{
	// 检查IO线程是否在运行中，如果不运行，则重启线程
	if (time(NULL) >= mLastIoTimer + 120)
	{
		ASSERT(0);
		netioTaskTimer->cancel();
		S_SAFE_DELETE(netioTaskTimer);
		netioTaskTimer = new zTaskTimer(IO_UPDTATE_TIME, boost::bind(&zNetSerivce::mainioUpdate, this, _1));
		netioTaskTimer->start();
	}
}

void zNetSerivce::sendToServerZone(GeneralRoute_t route, std::pair<int32_t, int64_t> toPair, const NetMsgSS* cmd, int32_t len)
{

}

void zNetSerivce::pingToServer()
{
	struct MyPing : public execEntry<zSession>
	{
		virtual bool exec(zSession* entry)
		{
			switch (entry->GetRemoteServerType())
			{
			case ::config::server_t_gateway:
			case ::config::server_t_login:
			case ::config::server_t_world:
			case ::config::server_t_scene:
			case ::config::server_t_database:
			{
				::hmx_msg_login::PingServerClientProto pingProto;
				pingProto.set_time(time(NULL));
				pingProto.set_from_server_id(this->localServerID);
				pingProto.set_to_server_id(entry->GetRemoteServerID());
				entry->sendMsgProto(::hmx_cmd::msg_login, ::hmx_msg_login::ping_req, pingProto);
				break;
			}
			default:
				break;
			}
			return true;
		}
		int32_t localServerID;
	};
	MyPing ping;
	ping.localServerID = GetServerID();
	SessionMgr()->execEverySession(ping);
}



