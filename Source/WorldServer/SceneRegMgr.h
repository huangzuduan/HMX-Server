#ifndef __SCENE_INFO_MANAGER_H_
#define __SCENE_INFO_MANAGER_H_

#include "Includes.h"
#include "Config.h"


/*-------------------------------------------------------------------
 * @Brief : 本类记录场景服的信息，记录场景服在WS上注册了哪些场景ID
 *			同时
 * @Author:hzd 2015:11:18
 *------------------------------------------------------------------*/

/*
	场景动态信息 id=场景ID 
*/
class SceneReg : public zEntry
{
public:
	SceneReg()
	{
		sessid = mapid = 0;
	}

public:
	int64 sessid;
	int32 mapid;

};


/*--
	场景管理器 
*/
class SceneRegMgr : protected zEntryMgr<zEntryID>,public Single<SceneRegMgr>
{
protected:
	friend class Single<SceneRegMgr>;
	SceneRegMgr();
	~SceneRegMgr();

public:

	SceneReg* CreateObj();
	void DestroyObj(SceneReg* obj);

	bool add(SceneReg* scene);
	void remove(SceneReg* scene);
	SceneReg* get(int64 id);
	SceneReg* getBymapid(int32 mapid);// 获得第一个scene(通常也只有一个scene)
	SceneReg* getFreeBymapid(int32 mapid); // 获得比较空闲的场景 

private:

	ObjPool<SceneReg> objpool;

};


#endif

