#ifndef __INSTANCE_SCENE_H_
#define __INSTANCE_SCENE_H_

#include "Base.h"

class Scene;
class SceneUser;

/*-------------------------------------------------------------------
 * @Brief : 副本场景共用类，所有副本都需要继承该类 
 * 
 * @Author:hzd 2015:11:9
 *------------------------------------------------------------------*/
class InstanceScene : public BaseScene
{
public:
	/*-------------------------------------------------------------------
	 * @Brief : 副本场景是根据条件创建的，一个server会出现N个副本，有不同
	 *			的玩家加入进来(动态副本)
	 * @Author:hzd 2015:11:9
	 *------------------------------------------------------------------*/
	InstanceScene(Scene* _scene);
	~InstanceScene(void);

	virtual bool CheckEnter(const stEnterSceneParam& param) { return true; };

	virtual void OnUserEnter(SceneUser* pUser) {};

	virtual void OnUserLeave(SceneUser* pUser) {};

public:

	/* 关连的场景地图 */ 
	Scene* scene;

	std::map<int64,SceneUser*> allUsers;

};


/*
	
	副本管理器 

*/
class InstanceSceneMgr : public zEntryMgr< zEntryID >
{
protected:

	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	InstanceSceneMgr();
	virtual ~InstanceSceneMgr();
	static InstanceSceneMgr *ins;

public:

	InstanceScene* CreateObj(Scene* scene);
	void DestroyObj(InstanceScene* obj);
	static InstanceSceneMgr &getMe();
	static void destroyMe();

	InstanceScene* getInsSceneByID(int32 id);
	InstanceScene* getInsSceneByTempID(int32 tempid);

	void Update(DWORD nSrvTimes);

private:

	ObjPool<InstanceScene> objpool;

};



#endif

