#include "Client_PCH.h"


NetService::NetService():zService(Zebra::logger->getName())
{
	dbCoon = NULL;
	netioTaskTimer = NULL;
	timeTickTaskTimer = NULL;
	Zebra::timeTick = new zTimeTick();
}

NetService::~NetService()
{

}

bool NetService::run()
{
	SSleep(10);
	return true;
}

void NetService::finaly()
{

}

void NetService::netioUpdate(const zTaskTimer* timer)
{
	/* 与ws,fep,dp之前socket定时处理IO消息，包括消息协议的处理  */
	sessionMgr.updateIO(timer);
	GameCommand::Instance()->LoopInput();

	/* 玩家定时处理有需要的时间事件(业务逻辑) */
	if (timer->is1Min())
	{
		pingToServer();

	}

	if (timer->is1Sec())
	{
		PlayerMgr::Instance()->Update(timer);
	}
}

void NetService::timerTickUpdate(const zTaskTimer* timer)
{
	if (Zebra::timeTick)
	{
		Zebra::timeTick->update();
	}
}

void NetService::pingToServer()
{
	struct MyPing : public execEntry<zSession>
	{
		virtual bool exec(zSession* entry)
		{
			if (entry->serverType == zSession::SERVER_TYPE_CLIENT)
			{
				static SSRqPingToS send;
				entry->sendMsg(&send, send.GetPackLength());
			}
			return true;
		}
	};
	MyPing ping;
	sessionMgr.execEveryConn(ping);
}

bool NetService::init()
{
	// 初始化NetService所有变量等数据 

	serverID = strtoul(Zebra::global["serverid"].c_str(), (char**)NULL, 10);
	serverType = serverID / 1000;

	bool bResult = serverCfgMgr.loadConfig("serivces.xml");
	if (!bResult)
	{
		Zebra::logger->error("Load serivces.xml fail");
		return false;
	}

	const zSerivceCfgMgr::Server* server = serverCfgMgr.getServer(serverID);
	std::map<int32, zSerivceCfgMgr::Serivce>::const_iterator it = server->serivces.begin();
	for (;it != server->serivces.end();++it)
	{
		const zSerivceCfgMgr::Serivce& info = it->second;
		if (stricmp(info.name.c_str(),"client") == 0)
		{
			zSession* session = sessionMgr.connect(info.id, info.ip.c_str(), info.port,
				boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
				boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
				boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
			);
			if (!session)
			{
				Zebra::logger->error("Connect Server Fail!");
				ASSERT(0);
				return false;
			}
			session->setSessionType(server->getSessType());
			Player* player = PlayerMgr::getMe().CreateObj();
			player->id = session->id;
			player->session = session;
			PlayerMgr::getMe().add(player);
		}
	}

	netioTaskTimer = new zTaskTimer(IO_UPDTATE_TIME, 0, boost::bind(&NetService::netioUpdate,this,_1));
	netioTaskTimer->start();

	timeTickTaskTimer = new zTaskTimer(TIMETICK_UPDATE_TIME, 0, boost::bind(&NetService::timerTickUpdate,this,_1));
	timeTickTaskTimer->start();

	GameCommand::getMe().Init();
	GameCommand::getMe().ShowCmd();

	Zebra::logger->error("Server Start Success !");

	return true;
}


/* 参数 -c cfg.xml -l 日志文件  */ 
int main(int argc, const char * argv[])
{
	Zebra::logger = new zLogger("Client");
	/* 设置缺省参数  */
	Zebra::global["datadir"] = "data/";
	Zebra::global["confdir"] = "conf/";
	Zebra::global["questdir"] = "quest/";
	Zebra::global["mail_service"] = "on";
	Zebra::global["log"] = "debug";

	Zebra::logger->setLevel(Zebra::global["log"]);


	std::string strServerID = "1";
	if (argc > 2)
	{
		for (int32 i = 1; i < argc;)
		{
			if (strncmp("-c", argv[i], 2) == 0)
			{
				strServerID = argv[i + 1];
			}
			i += 2;
		}
	}

	Zebra::global["serverid"] = strServerID;

	NetService::getMe().main();
	NetService::delMe();

	return 0;
}



