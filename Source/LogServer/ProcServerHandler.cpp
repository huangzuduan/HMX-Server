#include "ProcServerHandler.h"

#include "Config.h"
#include "../DyNetMysql/DbIncludes.h"
#include "../Shared/CommonDef/SharedIncludes.h"

ProcServerHandler::ProcServerHandler(void)
{

}

ProcServerHandler::~ProcServerHandler(void)
{

}

void ProcServerHandler::ReqSaveToDb(BaseSession* pBaseSession, const NetMsgSS* pMsg,int32 nSize)
{

	const S2LogMsg* log = static_cast<const S2LogMsg*>(pMsg);
	IDbBase* pDB = DbConnManager::Instance()->GetMainDB();
	if(pDB)
	{
		ASSERT(pDB);	
		return ;
	}
	
	memset(SQL_BUFFER,0,MAX_SQL_BUFFER);
	char arrFunctionName[100];
	char arrDetail[200];
	memset(arrFunctionName,0,100);
	memset(arrDetail,0,200);
	pDB->Escape(arrFunctionName,log->arrFunctionName);
	pDB->Escape(arrDetail,log->arrDetail);
	SPRINTF(SQL_BUFFER,"INSERT INTO `log_info` (`servertype`,`starttimes`,`level`,`functionname`,`rownum`,`detail`,`time`) VALUES (%d,%d,%d,'%s',%d,'%s',%d);",log->nServerType,log->nStartTimes,log->nLevel,arrFunctionName,log->nRowNum,arrDetail,log->nTime);
	SQL_BUFFER[ MAX_SQL_BUFFER - 1 ] = '\0';
	pDB->ExecSQLAsync(SQL_BUFFER,NULL);
	
}
