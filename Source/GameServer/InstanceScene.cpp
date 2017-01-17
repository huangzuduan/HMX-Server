#include "GameServer_PCH.h"
#include "InstanceScene.h"

InstanceScene::InstanceScene(Scene* _scene):scene(_scene)
{
}

InstanceScene::~InstanceScene(void)
{
}


bool InstanceSceneMgr::getUniqeID(QWORD& tempid)
{

	return true;
}

void InstanceSceneMgr::putUniqeID(const QWORD& tempid)
{

}

InstanceSceneMgr::InstanceSceneMgr()
{

}

InstanceSceneMgr::~InstanceSceneMgr()
{

}

InstanceSceneMgr *InstanceSceneMgr::ins = NULL;

InstanceScene* InstanceSceneMgr::CreateObj(Scene* scene)
{
	return objpool.CreateObj(scene);
}

void InstanceSceneMgr::DestroyObj(InstanceScene* obj)
{
	objpool.DestroyObj(obj);
}

InstanceSceneMgr &InstanceSceneMgr::getMe()
{
	if (ins == NULL)
	{
		ins = new InstanceSceneMgr();
	}
	return *ins;
}

void InstanceSceneMgr::destroyMe()
{

}

InstanceScene* InstanceSceneMgr::getInsSceneByID(int32 id)
{
	return NULL;
}

InstanceScene* InstanceSceneMgr::getInsSceneByTempID(int32 tempid)
{
	return NULL;
}

void InstanceSceneMgr::Update(DWORD nSrvTimes)
{

}
