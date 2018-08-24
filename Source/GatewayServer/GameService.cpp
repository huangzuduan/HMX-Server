#include "GameService.h"
#include "NetIncludes.h"
#include "NetMsgHandler.h"
#include "WebMsgHandler.h"
#include "ProcLsHandler.h"
#include "ProcSsHandler.h"

GameService::GameService()
	:zNetSerivce(H::logger->getName())
{
	mPlayerSessionMgr = new zSessionMgr();
	m_pWebServer = NULL;
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
	bool bResult = false;
	if (info.serivcefun() == "forss")
	{
		bResult = SessionMgr()->bind(this,info,
			boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
			boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
			boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
			);
	}
	else if (info.serivcefun() == "foruser")
	{
		bResult = SessionMgr()->bind(this, info,
			boost::bind(&NetMsgHandler::OnNetMsgEnter, NetMsgHandler::Instance(), _1),
			boost::bind(&NetMsgHandler::OnNetMsg, NetMsgHandler::Instance(), _1, _2, _3),
			boost::bind(&NetMsgHandler::OnNetMsgExit, NetMsgHandler::Instance(), _1)
			);
	}

	if (!bResult)
	{
		H::logger->error("Bind Server Fail!");
		ASSERT(0);
		return false;
	}
	return true;
}

bool GameService::doWebServer(const ::config::SerivceInfo& info)
{
	NetServer* pServer = SessionMgr()->GetNetServer(1);
	if (pServer)
	{
		m_pWebServer = new CWebServer(*pServer, info.serivceip(), info.serivceport());
		m_pWebServer->init(boost::bind(&WebMsgHandler::OnWebMsgEnter, WebMsgHandler::Instance(), _1),
			boost::bind(&WebMsgHandler::OnWebMsg, WebMsgHandler::Instance(), _1, _2, _3),
			boost::bind(&WebMsgHandler::OnWebMsgExit, WebMsgHandler::Instance(), _1));
		H::logger->info("启动一个WebSocket服务器,ip=%s port=%d", info.serivceip().c_str(), info.serivceport());
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

void GameService::netioUpdate(const zTaskTimer* timer)
{
	/* 与ws,fep,dp之前socket定时处理IO消息，包括消息协议的处理  */
	SessionMgr()->updateIO(timer);

	/* Web断开处理 */
	if (timer->is5Sec())
	{
		m_pWebServer->clear_close();
	}

	/* 玩家定时处理有需要的时间事件(业务逻辑) */
	if (timer->is1Min())
	{
		pingToServer();
	}
}

boost::asio::io_service* GameService::GetIoService()
{
	return  SessionMgr()->GetNetClient(1);
}

bool GameService::init()
{
	bool bResult = SrvSerivceMgr()->LoadConfig(H::global["confdir"] + "/serivces.xml");
	if (!bResult)
	{
		H::logger->error("Load serivces.xml fail,path=%s", "serivces.xml");
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

	H::logger->info("Server Start Success !");

	return true;
}

/* 参数 -c cfg.xml -l 日志文件  */ 
int main(int argc, const char * argv[])
{
	H::logger = new zLogger("GatewayServer");
	H::logger->addLocalFileLog("./fep");
	/* 设置缺省参数  */
	H::global["datadir"] = "data/";
	H::global["confdir"] = "conf/";
	H::global["questdir"] = "quest/";
	H::global["mail_service"] = "on";
	H::global["log"] = "debug";

	H::logger->setLevel(H::global["log"]);

	H::global["confdir"] = (argc >= 2 ? argv[1] : ".");
	H::global["serverid"] = "1001";

	GameService::getMe().main();
	GameService::delMe();

	return 0;
}



