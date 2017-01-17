#include "LoginServer_PCH.h"
#include "NamesManager.h"
#include "Utility.h"

NamesManager::NamesManager(void)
{
}

NamesManager::~NamesManager(void)
{
}

void NamesManager::LoadItems(const char* arrName)
{
	StNameInfo sInfo;
	memcpy(sInfo.arrName,arrName,32);
	sInfo.nMark = 0;
	m_setNameInfo.push_back(sInfo);
}

bool NamesManager::GetRandTtems(char* o_arrName)
{
	int32 nRandMax = m_setNameInfo.size();
	if(nRandMax == 0)
		return false;

	int32 nRandIndx = RangedRand(0,nRandMax);
	memcpy(o_arrName,&m_setNameInfo[nRandIndx].arrName,32);
	return true;
}
