#include "GameServer_PCH.h"
#include "DataRsyncTools.h"


DataRsyncTools::DataRsyncTools(zSession* pDbServer):m_pDbServer(pDbServer)
{

}

void DataRsyncTools::SavaMixItemNumber(EMixItemNumberType eType,int64 nValue)
{

}

void DataRsyncTools::SaveMixItemBinary(EMixItemBinaryType eType,const char* data,int32 nLen)
{

}

int64 DataRsyncTools::GetMixNumber(EMixItemNumberType eType)
{

	return 0;
}

void DataRsyncTools::GetMixNumber(EMixItemBinaryType eType,char* o_data)
{

}


