#include "AccountWxMgr.h"
#include "GameService.h"

AccountWxMgr::AccountWxMgr()
{
}

AccountWxMgr::~AccountWxMgr()
{
}

void AccountWxMgr::Timer()
{
}

void AccountWxMgr::LoginAccountWx(const ::data::AccountWxInfo& data)
{
	std::map<std::string, AccountWx>::iterator it = m_mapAccountWx.find(data.openid());
	if (it == m_mapAccountWx.end())
	{
		AccountWx accountWx(data);
		m_mapAccountWx.insert(std::make_pair(data.openid(), accountWx));
	}
	else
	{
		AccountWx accountWx = it->second;
		accountWx.Update(data);
	}

	// Í¨Öªµ½ws-
	::msg_maj::LoginToken loginToken;
	loginToken.set_openid(data.openid());
	loginToken.set_nickname(data.nickname());
	loginToken.set_sex(data.sex());
	loginToken.set_province(data.province());
	loginToken.set_city(data.city());
	loginToken.set_country(data.country());
	loginToken.set_headimgurl(data.headimgurl());
	loginToken.set_unionid(data.unionid());
	loginToken.set_ip(data.ip());

	GameService::Instance()->SendToWs(::comdef::msg_ss,::msg_maj::LoginTokenNotifyID, loginToken);
}
