#ifndef _SCENE_USER_MGR_H_
#define _SCENE_USER_MGR_H_

#include <ScenesServer.h>
#include "SceneUser.h"

class SceneUserMgr :protected zUserManager 
{
public:
	SceneUserMgr();
	virtual ~SceneUserMgr();
	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	SceneUser * CreateObj();
	void DestroyObj(SceneUser * user);
	SceneUser * getUserByName(const char * name);
	SceneUser * getUserByID(QWORD id);
	SceneUser * getUserBySessID(QWORD sessid);
	SceneUser * getUserByNameOut(const char * name);
	SceneUser * getUserByIDOut(DWORD id);
	SceneUser * getUserByTempIDOut(DWORD tempid);
	bool addUser(SceneUser *user);
	void removeUser(SceneUser *user);
	void removeUserInOneScene(Scene *scene);
	void removeUserToHuangcheng(Scene *scene);
	void clearEmperorDare(Scene* scene);
	void setEmperorDare(Scene* scene);
	void removeUserByTask(SceneTask *task);
	void removeAllUser();
	DWORD countUserInOneScene(Scene *scene);
	DWORD countUserByTask(SceneTask *task);
	void countryTrans(DWORD dwCountryID, DWORD dwLevel);
	void setAntiAtt(DWORD dwType, DWORD dwFromRelationID, DWORD dwToRelationID);
	void Update(const zTaskTimer* timer);

private:
	
	ObjPool<SceneUser> objpool;

};



#endif
