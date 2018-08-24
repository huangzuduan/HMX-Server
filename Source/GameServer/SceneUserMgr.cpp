#include "SceneUserMgr.h"
#include "GameService.h"

SceneUserMgr::SceneUserMgr()
{
	
}

SceneUserMgr::~SceneUserMgr()
{
	clear();
}

SceneUser * SceneUserMgr::getUserByName( const char * name)
{
	return (SceneUser *)zUserManager::getUserByName(name);
}

SceneUser * SceneUserMgr::getUserByID( QWORD id)
{
  return (SceneUser *)zUserManager::getUserByID(id);
}

SceneUser * SceneUserMgr::getUserBySessID(QWORD sessid)
{
	return (SceneUser *)zUserManager::getUserBySessID(sessid);
}

void SceneUserMgr::removeAllUser()
{
  struct UnloadAllExec :public execEntry<SceneUser>
  {
    std::vector<DWORD> del_vec;
    UnloadAllExec()
    {
    }
    bool exec(SceneUser *u)
    {
     /* if (u->scene)
        del_vec.push_back(u->id);*/
      return true;
    }
  };
  UnloadAllExec exec;
  GameService::getMe().getSceneUserMgr()->execEveryUser(exec);
  for(std::vector<DWORD>::iterator iter = exec.del_vec.begin() ; iter != exec.del_vec.end() ; iter ++)
  {
    SceneUser *pUser=GameService::getMe().getSceneUserMgr()->getUserByID(*iter);
    if (pUser)
    {
      //pUser->save(Cmd::Record::LOGOUT_WRITEBACK);
      //NetService::getMe().getSceneUserMgr()->removeUser(pUser);
      //Zebra::logger->info("用户%s(%ld)因服务器关闭卸载",pUser->name,pUser->id);
      //OnQuit event(1);
      //EventTable::Instance().execute(*pUser,event);
      //execute_script_event(pUser,"quit");

      //pUser->save(Cmd::Record::LOGOUT_WRITEBACK);
      ////pUser->killAllPets();
      //pUser->unreg();
      ////通知网关服务器
      //Cmd::Scene::t_Unreg_LoginScene retgate;
      //retgate.dwUserID = pUser->id;
      //retgate.dwSceneTempID = pUser->scene->tempid;
      //retgate.retcode = Cmd::Scene::UNREGUSER_RET_UNLOAD_SCENE;
      //pUser->gatetask->sendCmd(&retgate,sizeof(retgate));

      //S_SAFE_DELETE(pUser);
    }
  }
}

void SceneUserMgr::removeUser(SceneUser *user)
{
  zUserManager::removeUser(user);
}

bool SceneUserMgr::addUser(SceneUser *user)
{
  return zUserManager::addUser(user);
}


//void SceneUserMgr::enterWar(Cmd::Session::t_enterWar_SceneSession* cmd)
//{
//  struct EverySceneUserAction : public execEntry<SceneUser>
//  {
//    Cmd::Session::t_enterWar_SceneSession* ptCmd;
//    EverySceneUserAction(Cmd::Session::t_enterWar_SceneSession* cmd)
//    {
//      ptCmd = cmd;
//    }
//
//    bool exec(SceneUser *su)
//    {
//      if (su->scene && su->charbase.country == ptCmd->dwFromRelationID)
//      {
//        if (ptCmd->dwStatus == 1)
//        {
//          Zebra::logger->debug("当前对战记录数: %u",su->warSize());
//          Zebra::logger->debug("加入国战: toRelation:%u,isAtt:%u",ptCmd->dwToRelationID,ptCmd->isAtt);
//          su->addWarRecord(ptCmd->dwWarType,ptCmd->dwToRelationID,ptCmd->isAtt);
//
//          Zebra::logger->debug("当前对战记录数: %u",su->warSize());
//
//          if (ptCmd->isAntiAtt)
//          {
//            su->setAntiAttState(ptCmd->dwWarType,ptCmd->dwToRelationID);
//          }
//            
//          if (su->scene->getRealMapID() == 139 
//              && ptCmd->dwToRelationID==su->scene->getCountryID()
//              && su->scene->getCountryDareBackToMapID())
//          {
//            su->deathBackToMapID =  (ptCmd->dwToRelationID << 16) + 
//              su->scene->getCountryDareBackToMapID();
//          }
//        }
//        else
//        {
//          Zebra::logger->debug("当前对战记录数: %u",su->warSize());
//          Zebra::logger->debug("删除国战: toRelation:%u,isAtt:%u",ptCmd->dwToRelationID,ptCmd->isAtt);
//
//          su->removeWarRecord(ptCmd->dwWarType,ptCmd->dwToRelationID);
//          
//          Zebra::logger->debug("当前对战记录数: %u",su->warSize());
//
//          //if (!su->isSpecWar(Cmd::COUNTRY_FORMAL_DARE))
//          //{// 不在国战状态了
//            su->setDeathBackToMapID(su->scene);
//          //}
//        }
//
//        //su->sendNineToMe(); // 及时更新对战状态
//        su->setStateToNine(Cmd::USTATE_WAR);
//      }
//
//      return true;
//    }
//  };      
//
//  EverySceneUserAction esua(cmd);
//  NetService::getMe().getSceneUserMgr()->execEveryUser(esua);
//}

//SceneRecycleUserManager &SceneRecycleUserManager::getInstance()
//{
//  if (instance==NULL)
//  {
//    instance=new SceneRecycleUserManager();
//  }
//  return *instance;
//}
//void SceneRecycleUserManager::destroyInstance()
//{
//  SAFE_DELETE(instance);
//}
//bool SceneRecycleUserManager::addUser(zSceneEntry *user)
//{
//  rwlock.wrlock();
//  bool ret =addEntry((zEntry *)user);
//  rwlock.unlock();
//  return ret;
//}
//bool SceneRecycleUserManager::canReg(DWORD id)
//{
//  rwlock.rdlock();
//  SceneUser *ret =(SceneUser *)getEntryByID(id);
//  rwlock.unlock();
//  if (!ret)
//  {
//    return true;
//  }
//  else
//  {
//    Zebra::logger->debug("等待回收时再次登陆:%s",ret->name);
//    rwlock.wrlock();
//    SceneRecycleUserManager::getInstance().removeUser(ret);
//    ret->gatetask=NULL;
//    SAFE_DELETE(ret);
//    rwlock.unlock();
//    return true;
//  }
//}
//SceneUser* SceneRecycleUserManager::getUserByID(DWORD id)
//{
//  SceneUser *user =(SceneUser *)SceneRecycleUserManager::getInstance().getEntryByID(id);
//  return user;
//}
//
//void SceneRecycleUserManager::removeUser(SceneUser *user)
//{
//  SceneRecycleUserManager::getInstance().removeEntry((zEntry *)user);
//}
struct Del 
{
  template<typename T>
    void operator()(T id)
    {
     /* SceneUser *user =(SceneUser *)SceneRecycleUserManager::getInstance().getUserByID(id);
      if (user)
      {
        SceneRecycleUserManager::getInstance().removeUser(user);
        user->gatetask=NULL;
		S_SAFE_DELETE(user);
      }*/
    }
};
//void SceneRecycleUserManager::refresh()
//{
//  struct RecycleUserExec:public execEntry<SceneUser>
//  {
//    std::list<DWORD> wait_del;
//    bool exec(SceneUser *su)
//    {
//      if (su->canRecycle(SceneTimeTick::currentTime))
//      {
//        wait_del.push_back(su->id);
//      }
//      return true;
//    }
//  };
//  RecycleUserExec exec;
//  rwlock.rdlock();
//  execEveryUser(exec);
//  rwlock.unlock();
//  if (!exec.wait_del.empty())
//  {
//    rwlock.wrlock();
//    std::for_each(exec.wait_del.begin(),exec.wait_del.end(),Del());
//    rwlock.unlock();
//  }
//}

void SceneUserMgr::Update(const zTaskTimer* timer)
{

	struct SetEmperorDareSceneExec : public execEntry<SceneUser>
	{
		SetEmperorDareSceneExec(const zTaskTimer* _timer):timer(_timer)
		{
		}
		bool exec(SceneUser *u)
		{
			u->Timer(timer);
			return true;
		}
		const zTaskTimer* timer;
	};

	SetEmperorDareSceneExec exec(timer);
	GameService::getMe().getSceneUserMgr()->execEveryUser(exec);
}

