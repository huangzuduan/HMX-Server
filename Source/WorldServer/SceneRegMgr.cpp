#include "SceneRegMgr.h"

struct MyScene : public execEntry<SceneReg>
{
	MyScene(int32_t _mapid):mapid(_mapid)
	{
		scene = NULL;
	}
	virtual bool exec(SceneReg *entry)
	{
		if (!scene && entry->mapid == mapid)
		{
			scene = entry;
		}
		return true;
	}

	int32_t mapid;
	SceneReg* scene;
};

SceneRegMgr::SceneRegMgr()
{

}

SceneRegMgr::~SceneRegMgr()
{

}


SceneReg* SceneRegMgr::CreateObj()
{
	return objpool.CreateObj();
}

void SceneRegMgr::DestroyObj(SceneReg* obj)
{
	objpool.DestroyObj(obj);
}

bool SceneRegMgr::add(SceneReg* scene)
{
	return zEntryMgr< zEntryID<0> >::addEntry(scene);
}

void SceneRegMgr::remove(SceneReg* scene)
{
	zEntryMgr< zEntryID<0> >::removeEntry(scene);
}

SceneReg* SceneRegMgr::get(int64_t id)
{
	return (SceneReg*)zEntryMgr< zEntryID<0> >::getEntryByID(id);
}

SceneReg* SceneRegMgr::getBymapid(int32_t mapid)
{
	MyScene exec(mapid);
	zEntryMgr< zEntryID<0> >::execEveryEntry(exec);
	return exec.scene;
}

SceneReg* SceneRegMgr::getFreeBymapid(int32_t mapid)
{
	MyScene exec(mapid); // todo 
	zEntryMgr< zEntryID<0> >::execEveryEntry(exec);
	return exec.scene;
}