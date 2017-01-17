#ifndef __BASE_H_
#define __BASE_H_

#include "BaseDefine.h"
#include "ServerDefine.h"


class SceneUser;


/* 功能类基本定义 */ 

enum EPkSceneType
{
	E_PK_SCENE_TYPE_NULL = 0,	// 无  
	E_PK_SCENE_TYPE_GENERAL,	// 普通 
	E_PK_SCENE_TYPE_INSTANCE,	// 副本 
};


/* 场景基类 */
class BaseScene
{
public:
	BaseScene(){};

	/* 预前检查/轻度(玩家内存还未加载) */ 
	virtual bool CheckEnter(const stEnterSceneParam& param) = 0;

	/* 进入该场景并检查(深度检查，已经加载玩家内存) */ 
	virtual void OnUserEnter(SceneUser* pUser) = 0;

	/* 退出场景 */ 
	virtual void OnUserLeave(SceneUser* pUser) = 0;

protected:


};


#endif 



