#ifndef __OFFLINE_USER_MGR_H_
#define __OFFLINE_USER_MGR_H_

#include "Includes.h"
#include "OfflineUser.h"

class OfflineUserMgr : protected zEntryMgr< zEntryID, zEntryName >
{
public:
	OfflineUserMgr();
	~OfflineUserMgr();
	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	OfflineUser* CreateObj();
	void DestroyObj(OfflineUser* user);

	void loadDB();

	bool addUser(OfflineUser *user)
	{
		return zEntryMgr::addEntry(user);
	}

	OfflineUser* getUserByName(const char * name)
	{
		return (OfflineUser *)zEntryMgr::getEntryByName(name);
	}

	OfflineUser* getUserByID(QWORD id)
	{
		return (OfflineUser *)zEntryMgr::getEntryByID(id);
	}

	void removeUser(OfflineUser *user)
	{
		zEntryMgr::removeEntry(user);
	}

	template <class YourUserEntry>
	bool execEveryUser(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr::execEveryEntry<>(exec);
	}

private:

	zObjPool<OfflineUser> objpool;
	
};


#endif


