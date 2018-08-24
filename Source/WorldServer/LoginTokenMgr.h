#ifndef _LOGIN_TOKEN_H_
#define _LOGIN_TOKEN_H_

#include "SrvEngine.h"
#include "Single.h"

// 登录的临时缓存，主要用于更新微信用户一些变动的信息

class LoginTokenMgr : public Single<LoginTokenMgr>
{
public:
	LoginTokenMgr();
	~LoginTokenMgr();
	void AddToken(const ::msg_maj::LoginToken& loginToken);
	const ::msg_maj::LoginToken* GetToken(const std::string& unionid);
private:

	std::map<std::string, ::msg_maj::LoginToken> m_mapLoginToken;
};

#endif

