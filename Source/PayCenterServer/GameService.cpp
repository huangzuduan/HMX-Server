#include "GameService.h"
#include "NetIncludes.h"
#include "NetMsgHandler.h"
#include "DBConnection.h"
#include "ProcWorldHandler.h"

GameService::GameService()
	:zNetSerivce(H::logger->getName())
{
}

GameService::~GameService()
{

}

bool GameService::run()
{
#ifdef WIN32
	Sleep(MAIN_LOOP_TIME);
#else
	usleep(MAIN_LOOP_TIME);
#endif
	return true;
}

void GameService::finaly()
{

}


bool GameService::doBindServer(const ::config::SerivceInfo& info)
{
	bool bResult = SessionMgr()->bind(this,info,
		boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
		boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
		boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
		);
	if (!bResult)
	{
		H::logger->error("Bind Server Fail!");
		ASSERT(0);
		return false;
	}
	return true;
}

bool GameService::doConnectServer(const ::config::SerivceInfo& info)
{
	zSession* session = SessionMgr()->connect(this,info,
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
	return true;
}

void GameService::netioUpdate(const zTaskTimer* timer)
{
	/* 与ws,fep,dp之前socket定时处理IO消息，包括消息协议的处理  */
	SessionMgr()->updateIO(timer);

	/* 玩家定时处理有需要的时间事件(业务逻辑) */
	if (timer->is1Min())
	{
		pingToServer();
	}
}

boost::asio::io_service* GameService::GetIoService()
{
	return  SessionMgr()->GetNetServer(1);
}

bool GameService::init()
{
	bool bResult = SrvSerivceMgr()->LoadConfig("serivces.xml");
	if (!bResult)
	{
		H::logger->error("Load serivces.xml fail");
		return false;
	}

	zServerMgr* pSrvMgr = SrvSerivceMgr()->GetServerMgr(GetServerID());
	if (!pSrvMgr)
	{
		H::logger->error("Not found serverID=%u serivces.xml", GetServerID());
		return false;
	}

	if (!pSrvMgr->StartSerivces(this))
	{
		H::logger->error("Server Start Fail!");
		return false;
	}

	app = new MyHttpServer("WS_HTTP_SERVER",8009);
	app->start();

	H::logger->info("Server Start Success !");

	return true;
}

/* 参数 -c cfg.xml -l 日志文件  */ 
int main(int argc, const char * argv[])
{
	H::logger = new zLogger("PayCenterServer");
	H::logger->addLocalFileLog("./pay");

	/* 设置缺省参数  */
	H::global["datadir"] = "data/";
	H::global["confdir"] = "conf/";
	H::global["questdir"] = "quest/";
	H::global["mail_service"] = "on";
	H::global["log"] = "debug";

	H::logger->setLevel(H::global["log"]);

	std::string strServerID = "6001";
	if (argc > 2)
	{
		for (int32_t i = 1; i < argc;)
		{
			if (strncmp("-c", argv[i], 2) == 0)
			{
				strServerID = argv[i + 1];
			}
			i += 2;
		}
	}

	H::global["serverid"] = strServerID;

	ProcWorldHandler::Instance()->reqWxPayOrderInfo(NULL, NULL, 0);

	GameService::getMe().main();
	GameService::delMe();

	return 0;
}



