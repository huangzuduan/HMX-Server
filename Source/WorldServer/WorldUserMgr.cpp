#include "WorldUserMgr.h"
#include "SceneRegMgr.h"
#include "GameService.h"

#include "BaseDefine.h"

WorldUserMgr::WorldUserMgr()
{

}

WorldUserMgr::~WorldUserMgr()
{

}

WorldUser* WorldUserMgr::AddUser(const ::msg_maj::RoleWs& proto, uint64_t _clientSessID)
{
	WorldUser* obj = objpool.construct(proto);
	obj->SetClientSessID(_clientSessID);
	bool ret = zEntryMgr< zEntryID<0>, zEntryName >::addEntry(obj);
	if (!ret)
	{
		objpool.destroy(obj);
		return NULL;
	}
	return obj;
}

WorldUser* WorldUserMgr::getByUID(uint64_t id)
{
	return (WorldUser*)zEntryMgr< zEntryID<0>, zEntryName >::getEntryByID(id);
}

WorldUser* WorldUserMgr::getBySessID(uint64_t sessid)
{
	return (WorldUser*)zEntryMgr< zEntryID<0>, zEntryName >::getEntryByID(sessid);
}

WorldUser* WorldUserMgr::getByName(const char* name)
{
	return (WorldUser*)zEntryMgr< zEntryID<0>, zEntryName >::getEntryByName(name);
}

void WorldUserMgr::OfflineUser(WorldUser* user)
{
	// 处理其它下线的事
	zEntryMgr< zEntryID<0>, zEntryName >::removeEntry(user);
}

//////////////////////////////////////////////////////////////////////////


void WorldUserMgr::sendRoleList(int64_t accid, int64_t fepsid, int64_t sessid)
{

}