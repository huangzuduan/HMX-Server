#ifndef __WORLD_USER_MGR_H_
#define __WORLD_USER_MGR_H_


#include "SrvEngine.h"
#include "WorldUser.h"

#include <boost/pool/object_pool.hpp>

class WorldUserMgr : protected zEntryMgr< zEntryID<0>, zEntryName >
{
public:
	WorldUserMgr();
	~WorldUserMgr();
	
	WorldUser* AddUser(const ::msg_maj::RoleWs& proto, uint64_t _clientSessID);

	WorldUser* getByUID(uint64_t id);
	WorldUser* getBySessID(uint64_t sessid);
	WorldUser* getByName(const char* name);
	void OfflineUser(WorldUser* user);
	template <class YourUserEntry>
	bool execEveryUser(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr< zEntryID<0>,zEntryName >::execEveryEntry<>(exec);
	}

public:

	void sendRoleList(int64_t accid, int64_t fepsid, int64_t sessid);
	inline uint32_t GetOnlineNum() const { return zEntryMgr< zEntryID<0>, zEntryName >::size(); }

private:

	boost::object_pool<WorldUser> objpool;
	
};


#endif


