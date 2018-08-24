#ifndef __ACCOUNT_MGR_H_
#define __ACCOUNT_MGR_H_

#include "SrvEngine.h"
#include "AccountWx.h"

#include <boost/pool/object_pool.hpp>

/*
	微信Token管理，自动检查与刷新access_token的有效值
 */

class AccountWx;

class AccountWxMgr : protected zEntryMgr< zEntryID<0>, zEntryName > 
{
public:
	AccountWxMgr();
	~AccountWxMgr();

	void LoginAccountWx(const ::data::AccountWxInfo& data);

	void Timer();

private:

	std::map<std::string, AccountWx>	m_mapAccountWx;
	::boost::object_pool<AccountWx>		objpool;

};

#endif

