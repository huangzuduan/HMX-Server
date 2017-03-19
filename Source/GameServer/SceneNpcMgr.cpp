/**
 * \brief Npc管理容器
 *
 * 
 */

#include <ScenesServer.h>

/// SceneNpcManager的唯一实例
SceneNpcManager *SceneNpcManager::snm(NULL);

/**
 * \brief 初始化
 *
 */
bool SceneNpcManager::init()
{
  return true;
}

/**
 * \brief 构造函数
 *
 */
SceneNpcManager::SceneNpcManager()
{
  if (!loadNpcCommonChatTable())
    H::logger->error("读取npc说话内容失败");
#ifdef _DEBUG  
  H::logger->debug("SceneNpcManager::SceneNpcManager");
#endif    
}

SceneNpcManager::~SceneNpcManager()
{
#ifdef _DEBUG  
  H::logger->debug("SceneNpcManager::~SceneNpcManager()");
#endif    

}

/**
 * \brief 向管理器添加一个npc
 *
 *
 * \param sceneNpc 要添加的npc指针
 * \return 是否添加成功
 */
bool SceneNpcManager::addSceneNpc(SceneNpc *sceneNpc)
{
  //rwlock.wrlock();
  //bool ret=addEntry(sceneNpc);
  ////addSpecialNpc(sceneNpc);
  //rwlock.unlock();
  //return ret;
	return false;
}

/**
 * \brief 添加特殊npc
 * 特殊npc包括宠物、boss、有固定脚本的npc
 *
 * \param sceneNpc 要添加的npc
 * \return 是否添加成功
 */
bool SceneNpcManager::addSpecialNpc(SceneNpc *sceneNpc,bool force)
{
//  rwlock.wrlock();
//  if (sceneNpc && (sceneNpc->isSpecialNpc()||force))
//  {
//    specialNpc.insert(sceneNpc);
//#ifdef _DEBUG
//    //H::logger->debug("addSceneNpc(): 增加特殊npc %s",sceneNpc->name);
//#endif
//    rwlock.unlock();
//    return true;
//  }
//  rwlock.unlock();
  return false;
}

/**
 * \brief 删除一个npc
 *
 *
 * \param sceneNpc 要删除的npc
 * \return 
 */
void SceneNpcManager::removeSceneNpc(SceneNpc *sceneNpc)
{
  //rwlock.wrlock();
  //removeEntry(sceneNpc);
  //rwlock.unlock();
}

/**
 * \brief 删除一个特殊npc
 *
 *
 * \param sceneNpc 要删除的npc
 * \return 
 */
void SceneNpcManager::removeSpecialNpc(SceneNpc *sceneNpc)
{
  if (!sceneNpc) return;

  rwlock.wrlock();
  specialNpc.erase(sceneNpc);
#ifdef _DEBUG
  //H::logger->debug("removeSpecialNpc(): 删除特殊npc %s(%u)",sceneNpc->name,sceneNpc->tempid);
#endif
  rwlock.unlock();
}

/**
 * \brief 关闭所有的功能NPC为停机做准备
 */
void SceneNpcManager::closeFunctionNpc()
{
  struct SearchSceneExec :public execEntry<SceneNpc>
  {
    std::vector<DWORD> del_vec;
    SearchSceneExec()
    {
    }
    bool exec(SceneNpc *n)
    {
     /* switch(n->npc->id)
      {
        case 522:
        case 56025:
          {
            del_vec.push_back(n->tempid);
          }
          break;
        default:
          break;
      }*/
      return true;
    }
  };
  SearchSceneExec exec;
  SceneNpcManager::getMe().execEveryNpc(exec);
  for(std::vector<DWORD>::iterator iter = exec.del_vec.begin() ; iter != exec.del_vec.end() ; iter ++)
  {
    SceneNpc *pNpc=SceneNpcManager::getMe().getNpcByTempID(*iter);
    if (pNpc)
    {
      //DWORD tempid=0;
      //pNpc->toDie(tempid);
    }
  }
}


/**
 * \brief 根据临时id得到npc的指针
 *
 *
 * \param tempid npc的临时id
 * \return 找到的指针,失败返回0
 */
SceneNpc *SceneNpcManager::getNpcByTempID(DWORD tempid)
{
  rwlock.rdlock();
  SceneNpc *ret = (SceneNpc *)getEntryByTempID(tempid);
  rwlock.unlock();
  return ret;
}

/**
 * \brief 得到SceneNpcManager的实例
 *
 * \return SceneNpcManager的实例引用
 */
SceneNpcManager &SceneNpcManager::getMe()
{
  if (snm==NULL)
  {
    snm=new SceneNpcManager();
  }
  return *snm;
}

/**
 * \brief 删除SceneNpcManager的唯一实例
 */
void SceneNpcManager::destroyMe()
{
  SAFE_DELETE(snm);
}

/**
 * \brief 删除一个场景内的所有npc 
 *
 *
 * \param scene 要删除npc的场景
 * \return 
 */
void SceneNpcManager::removeNpcInOneScene(Scene *scene)
{
#ifdef _DEBUG  
  H::logger->debug("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!SceneNpcManger::removeNpcInOneScene");
#endif    

  struct UnloadSceneExec :public execEntry<SceneNpc>
  {
    Scene *scene;
    std::vector<DWORD> del_vec;
    UnloadSceneExec(Scene *s):scene(s)
    {
    }
    bool exec(SceneNpc *n)
    {
      //if (n->scene->tempid == scene->tempid)
      //{
      //  del_vec.push_back(n->tempid);
      //}
      return true;
    }
  };
  UnloadSceneExec exec(scene);
  SceneNpcManager::getMe().execEveryNpc(exec);
  for(std::vector<DWORD>::iterator iter = exec.del_vec.begin() ; iter != exec.del_vec.end() ; iter ++)
  {
    SceneNpc *pNpc=SceneNpcManager::getMe().getNpcByTempID(*iter);
    if (pNpc)
    {
      SceneNpcManager::getMe().removeSceneNpc(pNpc);
      SAFE_DELETE(pNpc);
    }
  }
}

void SceneNpcManager::SpecialAI()
{
}

/**
 * \brief 读取npc说话内容
 *
 * \return 是否读取成功
 */
bool SceneNpcManager::loadNpcCommonChatTable()
{
  zXMLParser xml;
  if (!xml.initFile(H::global["confdir"] + "NpcCommonChat.xml"))
  {
    H::logger->error("不能读取NpcCommonChat.xml");
    return false;
  }

  xmlNodePtr root = xml.getRootNode("root");
  if (!root) return false;

  xmlNodePtr chatNode = xml.getChildNode(root,"chat");
  int itemCount = 0;
  while (chatNode)
  {
    int type,rate;
    xml.getNodePropNum(chatNode,"type",&type,sizeof(type));
    if (0!=type)
    {
      xml.getNodePropNum(chatNode,"rate",&rate,sizeof(rate));
      NpcCommonChatRate[type] = rate;
      char str[MAX_CHATINFO];
      std::vector<std::string> strTable;
      xmlNodePtr contentNode = xml.getChildNode(chatNode,"content");
      while (contentNode)
      {
        bzero(str,sizeof(str));
        xml.getNodePropStr(contentNode,"str",str,sizeof(str));
        strTable.push_back(std::string(str));
        //H::logger->debug("loadNpcCommonChatTable:%s",std::string(str).c_str());
        itemCount++;
        contentNode = xml.getNextNode(contentNode,"content");
      }
      NpcCommonChatTable[type] = strTable;
    }
    chatNode = xml.getNextNode(chatNode,"chat");
  }

  H::logger->info("加载npc随机聊天文件成功,共%d类%d条",NpcCommonChatTable.size(),itemCount);
  return true;
}

/**
 * \brief 随机得到一句npc说的话
 *
 * \param type 要取得的说话类型
 * \param content 输出,取得的内容
 * \return 得到的说话内容
 */
bool SceneNpcManager::getNpcCommonChat(DWORD type,char * content)
{
  if (NpcCommonChatTable[type].empty() || !selectByPercent(NpcCommonChatRate[type])) return false;

  int index = randBetween(0,NpcCommonChatTable[type].size()-1);
  strncpy(content,NpcCommonChatTable[type][index].c_str(),MAX_CHATINFO-1);
  return true;
}
