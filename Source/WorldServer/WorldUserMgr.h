#ifndef __WORLD_USER_MGR_H_
#define __WORLD_USER_MGR_H_

#include "BaseDefine.h"
#include "Single.h"
#include "WorldUser.h"

class WorldUserMgr : protected zEntryMgrsessid< zEntryIDsessid, zEntryTempIDsessid, zEntryNamesessid >
{
public:
	WorldUserMgr();
	~WorldUserMgr();
	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	WorldUser* CreateObj();
	void DestroyObj(WorldUser* user);
	bool add(WorldUser *user);
	WorldUser* get(QWORD id);
	WorldUser* getBySessID(QWORD sessid);
	WorldUser* getByName(const char* name);
	void remove(WorldUser* user);

	template <class YourUserEntry>
	bool execEveryUser(execEntry<YourUserEntry> &exec)
	{
		return zEntryMgr::execEveryEntry<>(exec);
	}

public:

	bool checkmd5(int64 accid,int32 keytime,const char* keymd5);
	void sendRoleList(int64 accid, int64 fepsid, int64 sessid);

private:

	ObjPool<WorldUser> objpool;
	
};


#endif


