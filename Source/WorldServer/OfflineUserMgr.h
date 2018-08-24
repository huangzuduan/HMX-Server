#ifndef __OFFLINE_USER_MGR_H_
#define __OFFLINE_USER_MGR_H_

#include "SrvEngine.h"
#include "OfflineUser.h"
#include <boost/pool/object_pool.hpp>

class OfflineUserMgr : protected zEntryMgr< zEntryID<0>, zEntryName >
{
public:
	OfflineUserMgr();
	~OfflineUserMgr();

	void loadDB();

	OfflineUser* addUser(const ::msg_maj::RoleOff& proto);

	OfflineUser* getUserByName(const char * name)
	{
		return (OfflineUser *)zEntryMgr<  zEntryID<0>, zEntryName >::getEntryByName(name);
	}

	OfflineUser* getUserByID(QWORD id)
	{
		return (OfflineUser *)zEntryMgr<  zEntryID<0>, zEntryName >::getEntryByID(id);
	}

	void removeUser(OfflineUser *user)
	{
		zEntryMgr<  zEntryID<0>, zEntryName >::removeEntry(user);
	}

	template <class YourUserEntry>
	bool execEveryUser(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr<  zEntryID<0>, zEntryName >::execEveryEntry<>(exec);
	}

private:

	boost::object_pool<OfflineUser> objpool;
	
};


#endif


