#include "DBServer_PCH.h"
#include "RsyncTools.h"

RsyncTools::RsyncTools(void)
{
}

RsyncTools::~RsyncTools(void)
{
}

void RsyncTools::LoadDb()
{




}

void RsyncTools::Update(int32 nSrvTime)
{
	if(__INTERAVAL_ONE_SECOND__)
	{

	}

	if(__INTERAVAL_TWO_SECOND__)  // 3 √Î 
	{


	}

	if(__INTERAVAL_THREE_SECOND__)
	{

	}

}

void RsyncTools::SaveMixItemNumber(int32 eType,int64 nValue)
{
	//IDbBase* pDB = DbConnectsMgr::getMe().GetMainConn();
	//ASSERT(pDB);

	//static char SQL_BUFFER[ MAX_SQL_BUFFER ];

	//ostringstream ss;
	//ss << "REPLACE INTO `mixitem_number_info` (`type`,`value`,`time`) VALUES(";
	//ss << eType << ",";
	//ss << nValue << ",";
	//ss << "now()" << ");";

	//memset(SQL_BUFFER,0,MAX_SQL_BUFFER);
	//SPRINTF(SQL_BUFFER,"%s" ,ss.str().c_str());
	//SQL_BUFFER[ MAX_SQL_BUFFER - 1 ] = '\0';

	//pDB->ExecSQL(SQL_BUFFER);

}


void RsyncTools::SaveMixItemBinary(int32 eType,char* data,int32 nLen)
{

}