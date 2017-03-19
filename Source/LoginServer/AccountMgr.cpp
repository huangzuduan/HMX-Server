#include "LoginServer_PCH.h"
#include "AccountMgr.h"


AccountMgr::AccountMgr()
{
	maxAccountID = 0;
}

AccountMgr::~AccountMgr()
{

}

void AccountMgr::loadDB()
{

	acc::dbID* dataList, *dataTmp;
	int ret = GameService::getMe().getDbMysql()->ExecSelect("ACCOUNT", acc::Id, NULL, NULL, (unsigned char**)&dataList);
	if (ret > 0)
	{
		int usercount = 0;
		int failcount = 0;
		for (int c = 0; c < ret; ++c)
		{
			dataTmp = &dataList[c];
			Account* account = new Account();
			account->id = dataTmp->id;
			if (account->loadDB() && add(account))
			{
				usercount++;
			}
			else
			{
				failcount++;
				H::logger->error("加载帐号失败[ID:%lld]", account->id);
				remove(account);
			}
		}

		SAFE_DELETE_VEC(dataList);
		H::logger->info("共%d条数据，成功加载%d条,失败%d条", ret, usercount, failcount);

	}
}

bool AccountMgr::getUniqeID(QWORD& tempid)
{
	return true;
}

void AccountMgr::putUniqeID(const QWORD& tempid)
{

}

void AccountMgr::timer()
{

}

bool AccountMgr::add(Account* obj)
{
	if (obj->id > maxAccountID)
	{
		maxAccountID = obj->id;
	}
	return zEntryMgr::addEntry(obj);
}

void AccountMgr::remove(Account* obj)
{
	zEntryMgr::removeEntry(obj);
}

Account* AccountMgr::get(int64 id)
{
	return (Account*)zEntryMgr::getEntryByID(id);
}

Account* AccountMgr::getByName(const char* name)
{
	return (Account*)zEntryMgr::getEntryByName(name);
}

void AccountMgr::doUserCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	switch (pMsg->protocol)
	{
		case C::RQ_ACCOUNT_LOGIN:
		{
			const C::RqAccountLogin* packet = static_cast<const C::RqAccountLogin*>(pMsg);
			switch (packet->loginType)
			{
				case C::RqAccountLogin::LOGINTYPE_NAMEPASS:
				{
					doLoginNamePass(pSession, packet);
				}
				break;
				case C::RqAccountLogin::LOGINTYPE_RSA:
				{
					doLoginRSA(pSession, packet);
				}
				break;
				case C::RqAccountLogin::LOGINTYPE_CREATENAME:
				{
					doCreateAccount(pSession, packet);
				}
				break;
				case C::RqAccountLogin::LOGINTYPE_CREATERSA:
				{
					doRandRsaAccount(pSession, packet);
				}
				break;
				default:
				break;
			}
		}
		break;
		default:
		break;
	}
}

void AccountMgr::doLoginNamePass(zSession* pSession, const NetMsgSS* pMsg)
{
	const C::RqAccountLogin* packet = static_cast<const C::RqAccountLogin*>(pMsg);
	//packet->username[MAX_NAMESIZE] = '\0';
	char username[MAX_NAMESIZE + 1];
	char password[MAX_NAMESIZE + 1];
	bzero(username, sizeof(username));
	bzero(password, sizeof(password));

	strncpy(username, packet->username, MAX_NAMESIZE);
	strncpy(password, packet->password, MAX_NAMESIZE);

	C::RtAccLogin sendRet;
	sendRet.sessid = packet->sessid;
	sendRet.fepsid = packet->fepsid;

	Account* account = GameService::getMe().getAccountMgr().getByName(username);
	if (!account)
	{
		sendRet.accid = 0;
		sendRet.result = 0;
		pSession->sendMsg(&sendRet, sizeof(sendRet));
		return;
	}

	unsigned char passMd5[MAX_NAMESIZE + 1];
	memset(passMd5, 0, sizeof(passMd5));
	EncryptMD5(passMd5, (unsigned char*)password);
	passMd5[MAX_NAMESIZE] = '\0';

	if (strnicmp((const char*)passMd5, account->name, MAX_NAMESIZE) != 0)
	{
		sendRet.accid = 0;
		sendRet.result = 0;
		pSession->sendMsg(&sendRet, sizeof(sendRet));
		return;
	}

	// 登录成功

	int32 nowTime = H::timeTick->now();
	std::ostringstream outstr;
	outstr << account->id;
	outstr << SERVERKEY;
	outstr << nowTime;
	unsigned char commonMd5[MAX_NAMESIZE + 1];
	memset(commonMd5, 0, sizeof(commonMd5));
	EncryptMD5(commonMd5, (unsigned char*)outstr.str().c_str());
	commonMd5[MAX_NAMESIZE] = '\0';
	strncpy(sendRet.keymd5, (const char*)commonMd5, MAX_NAMESIZE);

	sendRet.keytime = nowTime;

	H::logger->info("生成密钥:%s", commonMd5);
	H::logger->info("%s登录%s", packet->username, "成功");

	// 发送加载角色列表返回给用户 
	S::SSRqLoadList sendWs;
	sendWs.sessid = packet->sessid;
	sendWs.fepsid = packet->fepsid;
	sendWs.accid = account->id;
	GameService::getMe().getSessionMgr().sendToWs(&sendWs, sizeof(sendWs));
}

void AccountMgr::doLoginRSA(zSession* pSession, const NetMsgSS* pMsg)
{

}

void AccountMgr::doCreateAccount(zSession* pSession, const NetMsgSS* pMsg)
{

}

void AccountMgr::doRandRsaAccount(zSession* pSession, const NetMsgSS* pMsg)
{
	const C::RqAccountLogin* packet = static_cast<const C::RqAccountLogin*>(pMsg);

	C::RtAccLogin sendRet;
	sendRet.sessid = packet->sessid;
	sendRet.fepsid = packet->fepsid;

	AccountMgr& accMgr = GameService::getMe().getAccountMgr();
	int64 maxAccount = accMgr.getMaxID();

	Account* account = new Account();
	account->id = maxAccount + 1;
	zEncrypt::getRandKey(account->name, MAX_NAMESIZE);
	zEncrypt::getRandKey(account->password, MAX_NAMESIZE);

	zRSA* rsa = new zRSA(account->name, account->name, account->password);
	if (!rsa->generateKey()) // 
	{
		H::logger->error("生成帐号密码失败");
		sendRet.result = 1;
		pSession->sendMsg(&sendRet, sizeof(sendRet));
		SAFE_DELETE(rsa);
		SAFE_DELETE(account);
		return;
	}

	int32 nowTime = H::timeTick->now();
	std::ostringstream outstr;
	outstr << account->id;
	outstr << SERVERKEY;
	outstr << nowTime;
	unsigned char loginKey[MAX_NAMESIZE + 1];
	memset(loginKey, 0, sizeof(loginKey));
	EncryptMD5(loginKey, (unsigned char*)outstr.str().c_str());
	loginKey[MAX_NAMESIZE] = '\0';

	if (!accMgr.add(account))
	{
		sendRet.result = 2;
		pSession->sendMsg(&sendRet, sizeof(sendRet));
		SAFE_DELETE(rsa);
		SAFE_DELETE(account);
		return;
	}

	account->saveDB();

	sendRet.accid = account->id;
	sendRet.result = 0;
	sendRet.keytime = nowTime;
	strncpy(sendRet.keymd5, (const char*)loginKey, MAX_NAMESIZE);

	pSession->sendMsg(&sendRet, sizeof(sendRet));

	// 发送加载角色列表返回给用户 
	S::SSRqLoadList sendWs;
	sendWs.sessid = packet->sessid;
	sendWs.fepsid = packet->fepsid;
	sendWs.accid = account->id;
	GameService::getMe().getSessionMgr().sendToWs(&sendWs, sizeof(sendWs));

	SAFE_DELETE(rsa);
}
