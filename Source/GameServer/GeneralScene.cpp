#include "GameServer_PCH.h"
#include "GeneralScene.h"
#include "SceneUser.h"
#include "ResourceMgr.h"

GeneralScene::GeneralScene(Scene* _scene):scene(_scene)
{
}

GeneralScene::~GeneralScene(void)
{
}


GeneralSceneMgr* GeneralSceneMgr::ins = NULL;

bool GeneralSceneMgr::getUniqeID(QWORD& tempid)
{
	return true;
}

void GeneralSceneMgr::putUniqeID(const QWORD& tempid)
{

}

GeneralSceneMgr::GeneralSceneMgr()
{

}

GeneralSceneMgr::~GeneralSceneMgr()
{

}

void GeneralSceneMgr::CreateAllScene()
{
	/*MapInfoOpt& mapInfo = zSerivceCfgMgr::getMe().GetSceneInfo();
	for (int32 i = 0; i < mapInfo.nMapNum; ++i)
	{
		int32 nMapID = mapInfo.arrMapID[i];
		CreateScene(nMapID);
	}*/
}

GeneralScene* GeneralSceneMgr::CreateScene(int32 mapID)
{

	const StMapInfoResCfg* mapInfo = ResourceMgr::getMe().GetMapInfoCfg(mapID);
	if (mapInfo)
	{
		const StMapZoneResCfg* zoneRes = ResourceMgr::getMe().GetMapZoneRes(mapID);
		if (zoneRes == NULL)
		{
			printf("[ERROR]Load mapzone fail mapid:%d\n", mapID);
			ASSERT(zoneRes);
			return NULL;
		}

		int32 nSceneType = mapInfo->nSceneType;
		int32 nXAmount = zoneRes->nXAmount;
		int32 nZAmount = zoneRes->nYAmount;
		int32 nXCellLength = zoneRes->nXCellLength;
		int32 nZCellLength = zoneRes->nYCellLength;

		/*
		Y
		|
		|
		--------->X
		*/
		/*zPos sTopLeftCoordinate(0, nZAmount * nZCellLength);
		Scene* sceneMap = SceneMapManager::getMe().AddSceneMap(mapID, nSceneType, sTopLeftCoordinate, nXAmount, nZAmount, nXCellLength, nZCellLength, zoneRes->regionValue);
		if (sceneMap == NULL)
		{
			Zebra::logger->error("Scene Add Map Fail!");
			ASSERT(0);
			return NULL;
		}

		GeneralScene* pScene = CreateObj(sceneMap);
		if (pScene == NULL)
		{
			Zebra::logger->error("Scene CreateObj Map Fail!");
			ASSERT(0);
			return NULL;
		}

		pScene->id = mapID;
		
		if (!AddGeneralScene(pScene))
		{
			Zebra::logger->error("AddGeneralScene Fail!");
			DestroyObj(pScene);
			ASSERT(0);
			return NULL;
		}*/

		//return pScene;
	}

	return NULL;

}

GeneralScene* GeneralSceneMgr::CreateObj(Scene* scene)
{
	return objpool.CreateObj(scene);
}

void GeneralSceneMgr::DestroyObj(GeneralScene* obj)
{
	objpool.DestroyObj(obj);
}

GeneralSceneMgr &GeneralSceneMgr::getMe()
{
	if (ins == NULL)
	{
		ins = new GeneralSceneMgr();
	}
	return *ins;
}

void GeneralSceneMgr::destroyMe()
{

}

bool GeneralSceneMgr::AddGeneralScene(GeneralScene* generalScene)
{
	bool ret;
	mlock.lock();
	ret = addEntry(generalScene);
	mlock.unlock();
	return ret;

}

GeneralScene* GeneralSceneMgr::getInsSceneByID(int32 id)
{
	return NULL;
}

GeneralScene* GeneralSceneMgr::getInsSceneByTempID(int32 tempid)
{
	return NULL;
}

void GeneralSceneMgr::Update(DWORD nSrvTimes)
{

}
