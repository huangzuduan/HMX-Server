#include "GatewayServer_PCH.h"


GameService::GameService():zNetSerivce(H::logger->getName())
{
	dbCoon = NULL;
	netioTaskTimer = NULL;
	timeTickTaskTimer = NULL;
	H::timeTick = new zTimeTick();
}

GameService::~GameService()
{

}

bool GameService::run()
{
	SSleep(10);
	return true;
}

void GameService::finaly()
{

}

void GameService::netioUpdate(const zTaskTimer* timer)
{
	/* 与ws,fep,dp之前socket定时处理IO消息，包括消息协议的处理  */
	sessionMgr.updateIO(timer);

	/* 玩家定时处理有需要的时间事件(业务逻辑) */
	if (timer->is1Min())
	{
		pingToServer();

	}
}

void GameService::timerTickUpdate(const zTaskTimer* timer)
{
	if (H::timeTick)
	{
		H::timeTick->update();
	}
}

void GameService::pingToServer()
{
	struct MyPing : public execEntry<zSession>
	{
		virtual bool exec(zSession* entry)
		{
			if (entry->serverType == zSession::SERVER_TYPE_CLIENT)
			{
				static S::SSRqPingToS send;
				entry->sendMsg(&send, sizeof(send));
			}
			return true;
		}
	};
	MyPing ping;
	sessionMgr.execEveryConn(ping);
}

bool GameService::init()
{
	// 初始化NetService所有变量等数据 

	serverID = strtoul(H::global["serverid"].c_str(), (char**)NULL, 10);
	serverType = serverID / 1000;

	bool bResult = serverCfgMgr.loadConfig("serivces.xml");
	if (!bResult)
	{
		H::logger->error("Load serivces.xml fail");
		return false;
	}

	const zSerivceCfgMgr::Server* server = serverCfgMgr.getServer(serverID);
	std::map<int32, zSerivceCfgMgr::Serivce>::const_iterator it = server->serivces.begin();
	for (;it != server->serivces.end();++it)
	{
		const zSerivceCfgMgr::Serivce& info = it->second;
		if (stricmp(info.name.c_str(),"server") == 0)
		{
			if (stricmp(info.fun.c_str(), "forss") == 0)
			{
				bResult = sessionMgr.bind(info.id, info.ip.c_str(), info.port, info.maxConnects,
					boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
					boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
					boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
				);
			}
			else if (stricmp(info.fun.c_str(), "foruser") == 0)
			{
				bResult = sessionMgr.bind(info.id, info.ip.c_str(), info.port, info.maxConnects,
					boost::bind(&PlayerMsgHandler::OnNetMsgEnter, PlayerMsgHandler::Instance(), _1),
					boost::bind(&PlayerMsgHandler::OnNetMsg, PlayerMsgHandler::Instance(), _1, _2, _3),
					boost::bind(&PlayerMsgHandler::OnNetMsgExit, PlayerMsgHandler::Instance(), _1)
				);
			}

			if (!bResult)
			{
				H::logger->error("Bind Server Fail!");
				ASSERT(0);
				return false;
			}
		}
		else if (stricmp(info.name.c_str(),"client") == 0)
		{
			zSession* session = sessionMgr.connect(info.id, info.ip.c_str(), info.port,
				boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
				boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
				boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
			);
			if (!session)
			{
				H::logger->error("Connect Server Fail!");
				ASSERT(0);
				return false;
			}
			session->setSessionType(zSession::FOR_WORLD);
			session->setServerID(info.remoteid);
		}
		else if (stricmp(info.name.c_str(), "mysqld") == 0)
		{
			if(!dbCoon)
			{
				dbCoon = new DbMysql();
				bResult = dbCoon->Open(info.ip.c_str(),info.port,info.user.c_str(),info.passwd.c_str(),info.value.c_str());
				if (!bResult)
				{
					H::logger->error("Connect DB Fail!");
					ASSERT(0);
					return false;
				}
			}
		}
	}

	netioTaskTimer = new zTaskTimer(IO_UPDTATE_TIME, 0, boost::bind(&GameService::netioUpdate,this,_1));
	netioTaskTimer->start();

	timeTickTaskTimer = new zTaskTimer(TIMETICK_UPDATE_TIME, 0, boost::bind(&GameService::timerTickUpdate,this,_1));
	timeTickTaskTimer->start();

	H::logger->error("Server Start Success !");

	return true;
}


/* 参数 -c cfg.xml -l 日志文件  */ 
int main(int argc, const char * argv[])
{
	H::logger = new zLogger("GatewayServer");
	/* 设置缺省参数  */
	H::global["datadir"] = "data/";
	H::global["confdir"] = "conf/";
	H::global["questdir"] = "quest/";
	H::global["mail_service"] = "on";
	H::global["log"] = "debug";

	H::logger->setLevel(H::global["log"]);


	std::string strServerID = "1001";
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

	H::global["serverid"] = strServerID;

	GameService::getMe().main();
	GameService::delMe();

	return 0;
}



