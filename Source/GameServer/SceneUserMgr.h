#ifndef _SCENE_USER_MGR_H_
#define _SCENE_USER_MGR_H_

#include "SceneUser.h"

class SceneUserMgr :protected zUserManager 
{
public:
	SceneUserMgr();
	virtual ~SceneUserMgr();
	SceneUser * getUserByName(const char * name);
	SceneUser * getUserByID(QWORD id);
	SceneUser * getUserBySessID(QWORD sessid);
	bool addUser(SceneUser *user);
	void removeUser(SceneUser *user);
	void removeAllUser();
	void Update(const zTaskTimer* timer);
private:
	
	zObjPool<SceneUser> objpool;

};



#endif
