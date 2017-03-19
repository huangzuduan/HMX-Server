#ifndef __ACCOUNT_MGR_H_
#define __ACCOUNT_MGR_H_
#include "Account.h"

class AccountMgr : protected zEntryMgr< zEntryID, zEntryName > 
{
public:
	AccountMgr();
	~AccountMgr();
	void loadDB();
	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	
	void timer();

	bool add(Account* obj);
	void remove(Account* obj);
	Account* get(int64 id);
	Account* getByName(const char* name);

	template <class YourSessionEntry>
	bool execEveryServer(execEntry<YourSessionEntry> &exec)
	{
		return execEveryEntry<>(exec);;
	}

public:

	void doUserCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
private:

	void doLoginNamePass(zSession* pSession, const NetMsgSS* pMsg);
	void doLoginRSA(zSession* pSession, const NetMsgSS* pMsg);
	void doCreateAccount(zSession* pSession, const NetMsgSS* pMsg);
	void doRandRsaAccount(zSession* pSession, const NetMsgSS* pMsg);

public:

	int64 getMaxID()
	{
		return maxAccountID;
	}

private:

	int64 maxAccountID; // 自增部分的ID，非帐号的唯一ID 

};

#endif

