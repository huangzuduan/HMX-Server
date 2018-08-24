#include "GameService.h"
#include "ClientCommand.h"
#include "PlayerMgr.h"
#include "NetMsgHandler.h"
#include "DbIncludes.h"
#include "NetIncludes.h"
#include "SrvIncludes.h"

GameService::GameService() :zNetSerivce(H::logger->getName())
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

	GameCommand::getMe().Init();
	GameCommand::getMe().ShowCmd();

	H::logger->info("Server Start Success !");

	return true;
}

bool GameService::doBindServer(const ::config::SerivceInfo& info)
{
	bool bResult = SessionMgr()->bind(this, info,
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
	zSession* session = SessionMgr()->connect(this, info,
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

/* 参数 -c cfg.xml -l 日志文件  */
int main(int argc, const char * argv[])
{
	H::logger = new zLogger("Client");
	/* 设置缺省参数  */
	H::global["datadir"] = "data/";
	H::global["confdir"] = "conf/";
	H::global["questdir"] = "quest/";
	H::global["mail_service"] = "on";
	H::global["log"] = "debug";

	H::logger->setLevel(H::global["log"]);
	std::string strServerID = "1";
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

	GameService::getMe().main();
	GameService::delMe();

	return 0;
}












