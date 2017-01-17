#include "../DyNetSocket/NetIncludes.h"
#include "../DyNetMysql/DbIncludes.h"

#include "LogManager.h"
#include "DeallineAsync.h"

#include "ServerStatistic.h"

#include "ClientSession.h"
#include "ServerSession.h"
#include "CommonServerOpt.h"
#include "ServerConnectMgr.h"
#include "ForSClientMsgHandler.h"
#include "ForServerMsgHandler.h"


/*
*
*	Detail: 程序主入口 
*
*  Created by hzd 2014-11-28
*
*/


char SQL_BUFFER[ MAX_SQL_BUFFER ];

NetServer*	gNetServerForServer = NULL; // connected to other sever
DeallineAsync* gDealCommon;		// 定时器 

DbConnManager* gDbServerMgr = DbConnManager::Instance(); // db 

bool gIsRun = true;

bool Init();
void ServerStart();
void RunServerExit();
void InteravalCommonUpdate(int32 nSrvTime);

int main(int argc, const char * argv[])
{
	Zebra::logger = new zLogger("LogServer");

	//设置缺省参数
	Zebra::global["datadir"] = "data/";
	Zebra::global["confdir"] = "conf/";
	Zebra::global["questdir"] = "quest/";
	Zebra::global["cmdswitch"] = "true";
	Zebra::global["writebacktimer"] = "600";
	Zebra::global["ExpRate"] = "1";
	Zebra::global["DropRate"] = "1";
	Zebra::global["DropRateLevel"] = "0";
	Zebra::global["mail_service"] = "on";
	Zebra::global["log"] = "debug";

	Zebra::logger->setLevel(Zebra::global["log"]);

	// 初始化服务器所都要准备好的数据 
	bool bResult = Init();

	if(!bResult)
	{
		//FLOG_INFO("Init Fail");
		ASSERT(0);
		return 0;
	}

	// 启动服务 
	ServerStart();

	// 执行退出的相关操作 
	RunServerExit();

	return 0;
}

void ServerStart()
{
	while(gIsRun)
	{
		SSleep(10);
	}
}

void RunServerExit()
{
	// TODO，处理停服相关的数据 
}

void InteravalCommonUpdate(int32 nSrvTime)
{

	if (gNetServerForServer)
	{
		gNetServerForServer->Update();
	}

	ServerConnectMgr::Instance()->Update(nSrvTime);

	if (gDbServerMgr)
	{
		gDbServerMgr->Update();
	}

	ClientSessionMgr::Instance()->Update(nSrvTime);
	ServerSessionMgr::Instance()->Update(nSrvTime);

	if(__INTERAVAL_FIVE_SECOND__)
	{
		int32 nServerNum = ServerSessionMgr::Instance()->CountConnected();
		int32 nClientNum = ClientSessionMgr::Instance()->ConnectedSessions();
		printf("Server Info:Server Connected Num:%d , Client Connected Num:%d\n", nServerNum,nClientNum);	// 标识主线程还在做事中
	}

	if (__INTERAVAL_ONE_MINUTE__)
	{
		ServerStatistic::Instance()->Update();
	}

}

bool Init()
{
	bool bResult = NetServerOpt::Instance()->LoadServerConfig("log_cfg.xml",ESERVER_TYPE_DP);
	if(!bResult)
	{
		printf("Load cfg fail\n");
		return false;
	}
	
	// 连接数据库  
	DatabaseInfoOpt& rDbInfo = NetServerOpt::Instance()->GetDatabaseInfo();
	IDbBase* pDb = gDbServerMgr->AddDatabase(rDbInfo.strHost.c_str(),rDbInfo.strUser.c_str(),rDbInfo.strPass.c_str(),rDbInfo.strDbname.c_str());
	if(pDb == NULL)
	{
		printf("Connnect to Database fail!\n");
		return false;
	}

	// 连接WS服务 
	ServerInfoOpt& rWsInfo = NetServerOpt::Instance()->GetRemoteServerInfo();
	bResult = ServerConnectMgr::Instance()->ConnectToServer(rWsInfo.nID, rWsInfo.nType, rWsInfo.strHost.c_str(), rWsInfo.nPort,
		boost::bind(&ForSClientMsgHandler::OnNetMsgEnter, ForSClientMsgHandler::Instance(), _1),
		boost::bind(&ForSClientMsgHandler::OnNetMsg, ForSClientMsgHandler::Instance(), _1, _2,_3),
		boost::bind(&ForSClientMsgHandler::OnNetMsgExit, ForSClientMsgHandler::Instance(), _1));
	if(!bResult)
	{
		printf("Connect Fail!\n" );
		return false;
	}

	// 初始化ForServer服务   
	ServerInfoOpt& rLocalInfo = NetServerOpt::Instance()->GetLocalServerInfo();
	gNetServerForServer = new NetServer(MAX_SERVER_CONNECTED);
	gNetServerForServer->SetTimeout(SERVER_TIMEOUT);
	gNetServerForServer->SetAddress(rLocalInfo.strHost.c_str(), rLocalInfo.nPort);
	gNetServerForServer->SetHandler(boost::bind(&ForServerMsgHandler::OnNetMsgEnter, ForServerMsgHandler::Instance(), _1),
		boost::bind(&ForServerMsgHandler::OnNetMsg, ForServerMsgHandler::Instance(), _1, _2, _3),
		boost::bind(&ForServerMsgHandler::OnNetMsgExit, ForServerMsgHandler::Instance(), _1));
	gNetServerForServer->Start();

	// 启动定时器    
	gDealCommon = new DeallineAsync(INTEVAL_COMMON_TIME, 0, InteravalCommonUpdate);
	gDealCommon->Start();

	printf("Server Start Success !\n");

	return true;

}
