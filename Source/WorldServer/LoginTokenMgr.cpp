#include "LoginTokenMgr.h"

LoginTokenMgr::LoginTokenMgr()
{
}


LoginTokenMgr::~LoginTokenMgr()
{

}

void LoginTokenMgr::AddToken(const ::msg_maj::LoginToken& loginToken)
{
	std::map<std::string, ::msg_maj::LoginToken>::iterator it = m_mapLoginToken.find(loginToken.unionid());
	if (it != m_mapLoginToken.end())
	{
		m_mapLoginToken.erase(it);
	}
	m_mapLoginToken.insert(std::make_pair(loginToken.unionid(), loginToken));
}

const ::msg_maj::LoginToken* LoginTokenMgr::GetToken(const std::string& unionid)
{
	std::map<std::string, ::msg_maj::LoginToken>::iterator it = m_mapLoginToken.find(unionid);
	if (it != m_mapLoginToken.end())
	{
		return &it->second;
	}
	return NULL;
}
