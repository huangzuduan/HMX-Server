#ifndef __SCENE_INFO_MANAGER_H_
#define __SCENE_INFO_MANAGER_H_

#include "SrvEngine.h"
#include "Single.h"

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
		id = tempid = sessid = mapid = 0;
	}

	inline uint64_t GetID(){ return id; }
	inline uint64_t GetTempID(){ return tempid; }
	inline const std::string& GetName(){ return _entry_name; }

public:
	uint64_t id;
	uint64_t tempid;
	uint64_t sessid;
	uint32_t mapid;
};


/*--
	场景管理器 
*/
class SceneRegMgr : protected zEntryMgr< zEntryID<0> >,public Single<SceneRegMgr>
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
	SceneReg* get(int64_t id);
	SceneReg* getBymapid(int32_t mapid);// 获得第一个scene(通常也只有一个scene)
	SceneReg* getFreeBymapid(int32_t mapid); // 获得比较空闲的场景 

private:

	zObjPool<SceneReg> objpool;

};


#endif

