#ifndef __GENERAL_SCENE_H_
#define __GENERAL_SCENE_H_

#include "Base.h"
#include "ScenesServer.h"

class Scene;

/*-------------------------------------------------------------------
 * @Brief : 普通的地图场景，如常用的游戏中的跑图地图，该类实现跑图
 *          地图的所有常用功能
 * @Author:hzd 2015:11:9
 *------------------------------------------------------------------*/

class GeneralScene : public BaseScene, public zEntry
{
public:
	
	/*-------------------------------------------------------------------
	 * @Brief : 普通场景，这个是所有玩家共有的，一个服务只有一个这样的场景
	 *			Scene在游戏启动时就已经创建好
	 * @Author:hzd 2015:11:9
	 *------------------------------------------------------------------*/
	GeneralScene(Scene* _scene);
	~GeneralScene(void);

	virtual bool CheckEnter(const stEnterSceneParam& param) { return true; };
	virtual void OnUserEnter(SceneUser* pUser) {};
	virtual void OnUserLeave(SceneUser* pUser) {};


public:

	Scene* scene;
	
};


/*
 *	主要普通场景（静态场景，每个mapid，在游戏中仅有一个地图）
 */
class GeneralSceneMgr : public zEntryMgr< zEntryID, zMultiEntryName >
{
protected:

	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	GeneralSceneMgr();
	virtual ~GeneralSceneMgr();
	static GeneralSceneMgr *ins;

public:

	void CreateAllScene();
	GeneralScene* CreateScene(int32 mapID);
	GeneralScene* CreateObj(Scene* scene);
	void DestroyObj(GeneralScene* obj);
	static GeneralSceneMgr &getMe();
	static void destroyMe();

	bool AddGeneralScene(GeneralScene* generalScene);

	GeneralScene* getInsSceneByID(int32 id);
	GeneralScene* getInsSceneByTempID(int32 tempid);

	void Update(DWORD nSrvTimes);

private:

	zMutex mlock;
	ObjPool<GeneralScene> objpool;
};

#endif


