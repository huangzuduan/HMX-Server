#include "SrvEngine.h"

zServerRegMgr::zServerRegMgr()
{
}

zServerRegMgr::~zServerRegMgr()
{
}

zServerReg* zServerRegMgr::add(const ::config::ServerInfo& proto)
{
	zServerReg* obj = objpool.CreateObj(proto);
	if (!zEntryMgr< zEntryID<0> >::addEntry(obj))
	{
		objpool.DestroyObj(obj);
		return NULL;
	}
	return obj;
}

void zServerRegMgr::remove(zServerReg* obj)
{
	return  zEntryMgr< zEntryID<0> >::removeEntry(obj);
}

zServerReg* zServerRegMgr::get(int64_t id)
{
	return (zServerReg*)zEntryID<0>::getEntryByID(id);
}



