#include "LoginAccountMgr.h"




ObjPool<StAccountInfo> LoginAccountMgr::s_cAccountInfoFactory;

LoginAccountMgr::LoginAccountMgr(void)
{
}


LoginAccountMgr::~LoginAccountMgr(void)
{
}

void LoginAccountMgr::Update(int32 nServerTimes)
{

}

StAccountInfo* LoginAccountMgr::GetAccountInfo(int32 nFepSessionId)
{
	AccountInfoMapType::iterator it = m_mapAccountInfo.find(nFepSessionId);
	if(it != m_mapAccountInfo.end())
		return it->second;
	return NULL;
}

StAccountInfo* LoginAccountMgr::AddAccountInfo(int32 nFepSessionId)
{
	if(StAccountInfo* pAccountInfo = s_cAccountInfoFactory.CreateObj(nFepSessionId))
	{
		m_mapAccountInfo.insert(std::make_pair(nFepSessionId,pAccountInfo));
		return pAccountInfo;
	}
	return NULL;
}

void LoginAccountMgr::RemoveAccountInfo(int32 nFepSessionId)
{
	AccountInfoMapType::iterator it = m_mapAccountInfo.find(nFepSessionId);
	if(it != m_mapAccountInfo.end())
	{
		m_mapAccountInfo.erase(it);
	}
}

