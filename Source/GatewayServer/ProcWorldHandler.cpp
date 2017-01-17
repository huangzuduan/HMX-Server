#include "GatewayServer_PCH.h"
#include "ProcWorldHandler.h"


ProcWorldHandler::ProcWorldHandler()
{
}


ProcWorldHandler::~ProcWorldHandler()
{
}


void ProcWorldHandler::ReqLogin(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{

	if(pSession->status != E_SERVER_STATUS_CONNETED)
	{
//		FLOG_INFO("pBaseSession->getStatus() != E_SERVER_STATUS_CONNETED");
		return;
	}

	// 判断 
	pSession->status = E_SERVER_STATUS_LOGINED;

	// ok finish!
	// 等待其它 ls,ss的连接  

}

