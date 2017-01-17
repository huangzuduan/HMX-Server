#include "GameServer_PCH.h"
/**
 * \brief SceneManager的实现
 *
 *  这个类暂时没有用到 
 */
#include "ScenesServer.h"

std::map<WORD, stRangMap*> RangMapData;
std::vector<DWORD> BmapBaseID;

//using namespace Cmd::Session;
using namespace Zebra;
///SceneManager的唯一实例
SceneManager *SceneManager::sm(new SceneManager());

/**
 * \brief 生成一个唯一ID
 *
 * \param tempid 输出：取得的ID
 * \return 是否成功
 */
bool SceneManager::getUniqeID(QWORD &tempid)
{
  tempid=sceneUniqeID->get();
  return (tempid!=sceneUniqeID->invalid());
}

/**
 * \brief 释放唯一ID
 *
 * \param tempid 要释放的ID
 */
void SceneManager::putUniqeID(const QWORD &tempid)
{
  sceneUniqeID->put(tempid);
}

/**
 * \brief 生成一个队伍唯一ID
 *
 * \param tempid 输出：取得的ID
 * \return 是否成功
 */
bool SceneManager::getTeamID(DWORD &tempid)
{
  tempid=sceneTeamID->get();
  return (tempid!=sceneTeamID->invalid());
}

/**
 * \brief 释放队伍唯一ID
 *
 * \param tempid 要释放的ID
 */
void SceneManager::putTeamID(const DWORD &tempid)
{
  sceneTeamID->put(tempid);
}

/**
 * \brief 构造函数
 *
 */
SceneManager::SceneManager()
{
  inited=false;
  newzone=false; 
  //ScenTeamMap.clear();
}

/**
 * \brief 析构函数
 *
 */
SceneManager::~SceneManager()
{
	//if(!ScenTeamMap.empty())
	//{
	//	std::map<DWORD, TeamManager*>::iterator iter;
	//	for(iter=ScenTeamMap.begin(); iter!=ScenTeamMap.end(); iter++)
	//	{
	//		delete iter->second;
	//	}

	//	ScenTeamMap.clear();
	//}

	final();
}

/**
 * \brief 得到SceneManager的指针
 * 如果指针为0则进行初始化
 *
 */
SceneManager & SceneManager::getInstance()
{
	if (sm==NULL)
		sm=new SceneManager();
	return *sm;
}

/**
 * \brief 删除SceneManager
 *
 */
void SceneManager::delInstance()
{
  if (sm!=NULL)
  {
    sm->final();
    SAFE_DELETE(sm);
  }
}

/**
 * \brief 释放所有已经加载的地图
 *
 */
void SceneManager::final()
{
  if (inited)
  {
    inited=false;
    unloadAllScene();
  }
}

/**
 * \brief 初始化
 * 加载所有地图
 *
 */
bool SceneManager::init()
{
	if (inited) return inited;

	//为每个场景服务器生成不相交叉的场景临时ID分配器,最小的从10000开始,每个有49998个ID可用
	DWORD firstTempID = 10000+(NetService::getMe().getServerID()%100)*50000;
	sceneUniqeID = new zUniqueDWORDID(firstTempID,firstTempID+49998);

	////sky 生成不相交的场景队伍临时ID分配器最小从10000开始,每个有4998个ID可用
	//firstTempID = 500000+(ScenesService::getInstance().getServerID()%100)*5000;
	//sceneTeamID=new zUniqueDWORDID(firstTempID,firstTempID+4998);

	//// 初始化所有地图
	zXMLParser parser;
	if (parser.initFile(Zebra::global["confdir"] + "scenesinfo.xml"))
	{
		xmlNodePtr root = parser.getRootNode("ScenesInfo");
		xmlNodePtr countryNode = parser.getChildNode(root, "countryinfo");
		if (countryNode)
		{
			xmlNodePtr subnode = parser.getChildNode(countryNode,"country");
			while(subnode)
			{
				if (strcmp((char*)subnode->name,"country") == 0)
				{
					CountryInfo info;
					bzero(&info,sizeof(info));
					parser.getNodePropNum(subnode,"id",&info.id,sizeof(info.id));
					parser.getNodePropStr(subnode,"name",info.name,sizeof(info.name));
					parser.getNodePropNum(subnode,"mapID",&info.mapid,sizeof(info.mapid));
					parser.getNodePropNum(subnode,"function",&info.function,sizeof(info.function));
					Zebra::logger->info("加载国家名称(%u,%s,%u,%u)",info.id,info.name,info.mapid,info.function);
					country_info.insert(CountryMap_value_type(info.id,info));
				}
				subnode = parser.getNextNode(subnode,NULL);
			}
		}
		xmlNodePtr mapNode=parser.getChildNode(root,"mapinfo");
		if (mapNode)
		{
			xmlNodePtr subnode = parser.getChildNode(mapNode,"map");
			while(subnode)
			{
				if (strcmp((char*)subnode->name,"map") == 0)
				{
					MapInfo info;
					bzero(&info,sizeof(info));
					parser.getNodePropNum(subnode,"mapID",&info.id,sizeof(info.id));
					parser.getNodePropStr(subnode,"name",info.name,sizeof(info.name));
					parser.getNodePropStr(subnode,"fileName",info.filename,sizeof(info.filename));
					parser.getNodePropNum(subnode,"backto",&info.backto,sizeof(info.backto));
					parser.getNodePropNum(subnode,"backtocity",&info.backtoCity,sizeof(info.backtoCity));
					parser.getNodePropNum(subnode,"foreignerbackto",&info.foreignbackto,sizeof(info.foreignbackto));
					parser.getNodePropNum(subnode,"countrydarebackto",&info.countrydarebackto,
						sizeof(info.countrydarebackto));

					parser.getNodePropNum(subnode,"countrydefbackto",&info.countrydefbackto,
						sizeof(info.countrydefbackto));
					parser.getNodePropNum(subnode,"pklevel",&info.pklevel,
						sizeof(info.pklevel));



					parser.getNodePropNum(subnode,"commoncountrybackto",&info.commoncountrybackto,sizeof(info.commoncountrybackto));
					parser.getNodePropNum(subnode,"commonuserbackto",&info.commonuserbackto,sizeof(info.commonuserbackto));
					parser.getNodePropNum(subnode,"backtodare",&info.backtodare,sizeof(info.backtodare));
					parser.getNodePropNum(subnode,"function",&info.function,sizeof(info.function));
					parser.getNodePropNum(subnode,"level",&info.level,sizeof(info.level));
					parser.getNodePropNum(subnode,"exprate",&info.exprate,sizeof(info.exprate));
					map_info.insert(MapMap_value_type(info.id,info));
				}
				subnode = parser.getNextNode(subnode,NULL);
			}
		}
		xmlNodePtr serverNode=parser.getChildNode(root,"server");
		while (serverNode) {
			int id = 0;
			parser.getNodePropNum(serverNode,"id",&id,sizeof(id));
			if (NetService::getMe().getServerID() == id) {
				int mapCount=0;
				xmlNodePtr countryNode=parser.getChildNode(serverNode,"country");
				while(countryNode)
				{
					DWORD countryid=0;
					parser.getNodePropNum(countryNode,"id",&countryid,sizeof(countryid));
					xmlNodePtr mapNode=parser.getChildNode(countryNode,"map");
					while(mapNode)
					{
						//加载地图
						DWORD mapid = 0;
						if (!parser.getNodePropNum(mapNode,"mapID", &mapid,sizeof(mapid)))
						{
							Zebra::logger->error("得到地图编号失败");
							return inited;
						}

						Scene *newScene = loadScene(Scene::STATIC, countryid, mapid);

						// 注册地图
						if (newScene)
						{
							printf("向session发送注册消息(%s-%d-%d)\n",newScene->name,newScene->id,newScene->tempid);
							Zebra::logger->info("加载%s(%d,%d)成功",newScene->name,newScene->id,newScene->tempid);
							S2WRegisterScene regscene;
							regscene.sceneid = newScene->id;
							//Zebra::logger->info("[地图真实ID]:%d",loaded->id&0x0FFF);
							regscene.sceneTempID=newScene->tempid;
							regscene.mapid = mapid;
							strncpy(regscene.name,newScene->name,MAX_NAMESIZE);
							strncpy(regscene.fileName,newScene->getFileName(),MAX_NAMESIZE);
							regscene.dwCountryID = countryid;
							regscene.byLevel = newScene->getLevel();
							NetService::getMe().getSessionMgr().sendToWs(&regscene, regscene.GetPackLength());
							mapCount++;
						}
						else
						{
							return inited;
						}
						mapNode=parser.getNextNode(mapNode,"map");
					}
					countryNode=parser.getNextNode(countryNode,"country");
				}
				Zebra::logger->info("ScenesServer id=%d加载%d张地图.",id,mapCount);
			}
			else{
				Zebra::logger->info("skip id=%d != %d.",id, NetService::getMe().getServerID());
			}
			serverNode=parser.getNextNode(serverNode,"server");
		}
		inited=true;
	}
	else
		Zebra::logger->warn("SceneManager 解析配置文件失败.");
	//刷新玉如意需要的地图信息
	freshEverySceneField(); 
	return inited;
}

/**
 * \brief 根据名字的到场景指针的回调
 * 方法是遍历所有scene并比较名字
 * 
 */
class GetSceneByFileName:public SceneCallBack
{
  public:
    ///找到的scene指针
    Scene *ret;
    ///要找的场景名字
    const char *name;

    /**
     * \brief 构造函数
     *
     * 
     * \param name 要查找的场景名字
     * \return 
     */
    GetSceneByFileName(const char *name) : ret(NULL),name(name) {};

    /**
     * \brief  执行查找的方法
     *
     *
     * \param scene 场景指针
     * \return 是否继续查找
     */
    bool exec(Scene *scene)
    {
      if (strncmp(scene->getFileName(),name,MAX_NAMESIZE)==0)
      {
        ret=scene;
        return false;
      }
      else
        return true;
    }
};

/**
 * \brief 根据文件名字找到场景指针
 *
 * \param name 要找的场景名字
 * \return 要找的场景指针,失败返回0
 */
Scene * SceneManager::getSceneByFileName( const char * name)
{
  GetSceneByFileName gsfn(name);
  execEveryScene(gsfn);
  return gsfn.ret;
}

/**
 * \brief 根据名字找到场景指针
 *
 * \param name 要找的场景名字
 * \return 要找的场景指针,失败返回0
 */
Scene * SceneManager::getSceneByName( const char * name)
{
  rwlock.rdlock();
  Scene *ret =(Scene *)getEntryByName(name);
  rwlock.unlock();
  return ret;
}

/**
 * \brief 根据领事ID找到场景指针
 *
 * \param tempid 要找的场景的临时id
 * \return 要找的场景指针,失败返回0
 */
Scene * SceneManager::getSceneByTempID( DWORD tempid)
{
  rwlock.rdlock();
  Scene * ret = (Scene *)getEntryByTempID(tempid);
  rwlock.unlock();
  return ret;
}

/**
 * \brief 根据id找到场景指针
 *
 * \param id 要找的场景id
 * \return 要找的场景指针,失败返回0
 */
Scene * SceneManager::getSceneByID( DWORD id)
{
  rwlock.rdlock();
  Scene * ret = (Scene *)getEntryByID(id);
  rwlock.unlock();
  return ret;
}

DWORD SceneManager::getMapId(DWORD countryid,DWORD mapid)
{
  MapMap_iter map_iter = map_info.find(mapid);
  if (map_iter == map_info.end())
  {
    return 0;
  }
  
  CountryMap_iter country_iter = country_info.find(countryid);
  
  if (country_iter == country_info.end())
  {
    return 0;
  }
  
  return (country_iter->second.id << 16) + map_iter->second.id;


}

/**
 * \brief 加载一个地图
 *
 * \param type 地图类型,静态/动态
 * \param countryid 国家id
 * \param mapid 地图id
 * \return 新加载的场景指针
 */
Scene * SceneManager::loadScene(int type/*Scene::SceneType type*/,DWORD countryid,DWORD mapid)
{
  Zebra::logger->info("SceneManager::loadScene type=%d,countryid=%d,mapid=%d",type,countryid,mapid);
  zEntry *s=NULL;
  switch(type)
  {
	  case 0://Scene::STATIC:
        s=new StaticScene();
      break;
	  //case 1://Scene::GANG:
		 // s=new GangScene();
      break;
    default:
        Zebra::logger->error("未知场景类型");
        return false;
  }
  rwlock.wrlock();
  bool ret=((Scene *)s)->init(countryid,mapid);
  if (ret)
  {
    ret=addEntry(s);
    if (!ret)
      Zebra::logger->error("SceneManager::loadScene addEntry[%s]失败.",s->name);
    else Zebra::logger->info("SceneManager::loadScene[%s]成功",s->name);
  }
  else
    Zebra::logger->error("SceneManager::loadScene init[%s]失败.",s->name);
  rwlock.unlock();
  if (!ret)
  {
    SAFE_DELETE(s);
  }

  return (Scene *)s;
}

/**
* \brief 动态加载一个地图
*
* \param type 地图类型,静态/动态
* \param countryid 国家id
* \param baseid 地图源id
* \return 新加载的场景指针
*/
Scene * SceneManager::loadBattleScene(DWORD baseid)
{
	if(baseid == 0)
		return NULL;

	zEntry *s=NULL;
	//s=new GangScene();

	//std::map<WORD, stRangMap*>::iterator iter;
	//iter = RangMapData.find(baseid);

	//if(iter == RangMapData.end())
	//	return NULL;

	//DWORD countryid = iter->second->GetCountryid();
	//DWORD mapid = 0;
	//if(!iter->second->getUniqeID(mapid))
	//{
	//	printf("%d 类型战场分配已到最大限制!无法再分配", baseid);
	//	return NULL;
	//}

	//rwlock.wrlock();
	//bool ret = ((GangScene*)s)->GangSceneInit(countryid, baseid, mapid);

	////sky 配置战场基本数据
	////((GangScene*)s)->InitData();

	//if (ret)
	//{
	//	ret=addEntry(s);
	//	if (!ret)
	//		Zebra::logger->error("SceneManager::loadScene addEntry[%s]失败.",s->name);
	//	else 
	//		Zebra::logger->info("SceneManager::loadScene[%s]成功",s->name);
	//}
	//else
	//	Zebra::logger->error("SceneManager::loadScene init[%s]失败.",s->name);
	//rwlock.unlock();
	//if (!ret)
	//{
	//	SAFE_DELETE(s);
	//}

	return (Scene *)s;
}

/**
 * \brief 根据名字卸载一张地图
 *
 * \param name 要卸载的地图名字
 */
void SceneManager::unloadScene(std::string &name)
{
  zEntry * ret=NULL;
  rwlock.wrlock();
  if (zEntryName::find(name.c_str(),ret))
    removeEntry(ret);
  SAFE_DELETE(ret);
  rwlock.unlock();
  Zebra::logger->debug("SceneManager::unloadScene");
}

/**
 * \brief 根据场景指针卸载一张地图
 *
 * \param scene 要卸载的地图指针
 */
void SceneManager::unloadScene(Scene * &scene)
{
  if (scene==NULL) return;
  rwlock.wrlock();
  removeEntry((zEntry *)scene);
  SAFE_DELETE(scene);
  rwlock.unlock();
  Zebra::logger->debug("SceneManager::unloadScene");
}

/**
 * \brief 卸载全部地图
 *
 */
void SceneManager::unloadAllScene()
{
  zEntry * ret=NULL;
  rwlock.wrlock();
  while(zEntryName::findOne(ret))
  {
    removeEntry(ret);
    SAFE_DELETE(ret);
  }
  rwlock.unlock();
  Zebra::logger->debug("SceneManager::unloadAllScene");
}

/**
 * \brief 检查并删除设置为remove的场景
 * 方法是遍历所有场景,如果设置了remove标志,则清除所有npc和物件,然后删除场景
 * 该方法在场景主循环中执行
 *
 */
void SceneManager::checkUnloadOneScene()
{
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    Scene *scene = (Scene *)it->second;
    if (scene->getRunningState() == SCENE_RUNNINGSTATE_REMOVE)
    {
      Zebra::logger->debug("卸载场景%s",scene->name);
      SceneNpcManager::getMe().removeNpcInOneScene(scene);
      scene->removeSceneObjectInOneScene();
      unloadScene(scene);
      return ;
    }
  }
}

struct EveryMapExec : public execEntry<SceneManager::MapInfo>
{
  Scene *_scene;
  EveryMapExec(Scene *s):_scene(s)
  {
  }
  bool exec(SceneManager::MapInfo *info)
  {
    if (info->function & 0x2)
    {
      char buf[MAX_NAMESIZE + 1];
      bzero(buf,sizeof(buf));
      if (SceneManager::getInstance().buildMapName(_scene->getCountryID(),info->name,buf))
      {
        _scene->addMainMapName(buf);
      }
    }
    if (info->function & 0x20)
    {
      char buf[MAX_NAMESIZE + 1];
      bzero(buf,sizeof(buf));
      if (SceneManager::getInstance().buildMapName(_scene->getCountryID(),info->name,buf))
      {
        _scene->addIncMapName(buf);
      }
    }
    return true;
  }
};
void SceneManager::freshEverySceneField()
{
  struct getAllMapExec :public SceneCallBack
  {
    Scene *_old_scene;
    getAllMapExec(Scene *s):_old_scene(s)
    {
    }
    bool exec(Scene *scene)
    {
      //Zebra::logger->debug("%d,%d,%d,%s",scene->getCountryID(),_old_scene->getCountryID(),scene->isMainCity(),scene->getFileName());
      //if (/*scene != _old_scene && */_old_scene->isMainCity() && scene->getCountryID() == _old_scene->getCountryID() && scene->isField() && _old_scene->getWayPoint(scene->getFileName()))
      //{
      //  _old_scene->addFieldMapName(scene->name);
      //}
      return true;
    }
  };
  struct EverySceneExec :public SceneCallBack
  {
    bool exec(Scene *scene)
    {
      scene->clearMainMapName();
      EveryMapExec exec1(scene); 
      SceneManager::getInstance().execEveryMap(exec1);
      scene->clearFieldMapName();
      getAllMapExec exec(scene);
      SceneManager::getInstance().execEveryScene(exec);
      return true;
    }
  };
  EverySceneExec exec; 
  SceneManager::getInstance().execEveryScene(exec);
}
/**
 * \brief 对每个场景执行回调函数
 *
 * \param callback 要执行的回调函数
 */
void SceneManager::execEveryScene(SceneCallBack &callback)
{
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    if (!callback.exec((Scene *)it->second))
    {
      //mlock.unlock();
      return;
    }
  }
}


/**
 * \brief 根据国家名字得到国家id
 *
 * \param name 要得到id的国家名字
 * \return 找到的id,失败返回0
 */
DWORD SceneManager::getCountryIDByCountryName(const char *name)
{
  SceneManager::CountryMap_iter country_iter = SceneManager::getInstance().country_info.begin();
  for(; country_iter != SceneManager::getInstance().country_info.end() ; country_iter ++)
  {
    if (strcmp(name,country_iter->second.name) == 0)
    {
      return country_iter->first;
    }
  }
  return 0;
}

/**
 * \brief 对每个国家配置执行回调函数
 *
 * \param callback 要执行的回调函数
 */
/*
void SceneManager::execEveryMap(MapCallBack &callback)
{
  SceneManager::MapMap_iter map_iter = SceneManager::getInstance().map_info.begin();
  for(; map_iter != SceneManager::getInstance().map_info.end() ; map_iter ++)
  {
    callback.exec(map_iter->second);
  }
}
// */
/**
 * \brief 根据国家id得到国家名字
 *
 * \param id 要找的国家id
 * \return 找到的国家名字,失败返回0
 */
const char * SceneManager::getCountryNameByCountryID(DWORD id)
{
  SceneManager::CountryMap_iter country_iter = SceneManager::getInstance().country_info.begin();
  for(; country_iter != SceneManager::getInstance().country_info.end() ; country_iter ++)
  {
    if (country_iter->first == id)
    {
      return country_iter->second.name;
    }
  }
  return 0;
}

/**
 * \brief 根据地图名字得到地图id
 *
 * \param name 要找的地图名字
 * \return 找到的id,失败返回0
 */
DWORD SceneManager::getMapIDByMapName(const char *name)
{
  const char *p = strstr(name,"·");
  if (p)
    p += strlen("·");
  else
    p = name;

  SceneManager::MapMap_iter map_iter = SceneManager::getInstance().map_info.begin();
  for(; map_iter != SceneManager::getInstance().map_info.end() ; map_iter ++)
  {
    if (strcmp(p,map_iter->second.name) == 0)
    {
      return map_iter->first;
    }
  }
  return 0;
}

/**
 * \brief 根据国家id和地图id组成场景name
 *
 */
bool SceneManager::buildMapName(DWORD countryid,DWORD mapid,char *out)
{
  const char *c = getCountryNameByCountryID(countryid);
  const char *m = map_info[mapid].name;
  if (c && m)
  {
    sprintf(out,"%s·%s",c,m);
    return true;
  }
  return false;
}
 

/**
 * \brief 根据国家id和地图name组成场景name
 *
 */
bool SceneManager::buildMapName(DWORD countryid,const char *in,char *out)
{
  const char *c = getCountryNameByCountryID(countryid);
  if (c && in)
  {
    sprintf(out,"%s·%s",c,in);
    return true;
  }
  return false;
}
/**
 * \brief 根据国家id和地图id组成场景id
 *
 */
DWORD SceneManager::buildMapID(DWORD countryid,DWORD mapid)
{
  return (countryid << 16) + mapid;
}
bool SceneManager::isNewZoneConfig()
{
  return newzone && (!newzon_vec.empty());
}
void SceneManager::setNewZoneConfig(bool type)
{
  newzone=type;
  if (newzone==false)
  {
    newzon_vec.clear();
  }
}
void SceneManager::addNewZonePos(DWORD x,DWORD y)
{
  newzon_vec.push_back(std::make_pair(x,y));
}
SceneManager::NewZoneVec &SceneManager::queryNewZonePos()
{
  return newzon_vec;
}
bool SceneManager::randzPosNewZone(Scene *intoScene,zPos &findedPos)
{
  bool founded=false;
  int i=0;
  while(!founded && i < (int)newzon_vec.size())
  {
    int which = randBetween(0,newzon_vec.size() - 1);
    zPos initPos;
    int x = randBetween(0,10);
    int y = randBetween(0,10);
    initPos.x =newzon_vec[which].first + 5 - x;
    initPos.y =newzon_vec[which].second + 5 - y;
    founded = intoScene->findPosForUser(initPos,findedPos);
  }
  return founded;
}


//TeamManager* SceneManager::GetMapTeam(DWORD TeamID)
//{
//	if(ScenTeamMap.empty() || ScenTeamMap[TeamID] == 0)
//		return NULL;
//	else
//		return ScenTeamMap[TeamID];
//}

//bool SceneManager::SceneNewTeam(SceneUser *pUser)
//{
//	if (pUser->TeamThisID == 0)
//	{
//		//sky 计算出队伍唯一ID
//		DWORD teamid;
//		if(!getTeamID(teamid))
//		{
//			Channel::sendSys(pUser,Cmd::INFO_TYPE_GAME,"分配队伍唯一ID失败！队伍建立失败！");
//			return false;
//		}
//
//		TeamManager * team = new TeamManager();
//		if(team == NULL)
//		{
//			Zebra::logger->debug("内存不足!组队失败");
//			putTeamID(teamid);
//			return false;
//		}
//
// 		if (team->addMemberByTempID(pUser,pUser->tempid))
//		{
//			team->setTeamtempId(teamid);
//			team->setLeader(pUser->tempid);
//
//			ScenTeamMap[teamid] = team;
//
//			pUser->TeamThisID = teamid;
//
//			Cmd::stAddTeamMemberUserCmd ret;
//			ret.dwTeamID = teamid;
//			ret.dwHeadID = pUser->tempid;
//			ret.data.dwTempID = pUser->tempid;
//			ret.data.dwMaxHealth = pUser->charstate.maxhp;
//			ret.data.dwHealth = pUser->charbase.hp;
//			ret.data.dwMaxMp = pUser->charstate.maxmp;
//			ret.data.dwMp = pUser->charbase.mp;
//			ret.data.wdFace = pUser->charbase.face;
//			strncpy(ret.data.pstrName,pUser->name,MAX_NAMESIZE);
//			ret.data.byHead = true;
//			pUser->sendCmdToMe(&ret,sizeof(ret));
//
//			pUser->team_mode = Cmd::TEAM_HONOR;
//			pUser->reSendMyMapData();
//			//session队伍
//			ScenTeamMap[teamid]->addMemberToSession(pUser->name);
//
//			return true;
//		}
//	}
//
//	return false;
//}
//
//bool SceneManager::SceneNewTeam(Cmd::Session::t_Team_Data* send)
//{
//	std::map<DWORD, TeamManager*>::iterator iter;
//	iter = ScenTeamMap.find(send->dwTeamThisID);
//	
//	if(iter != ScenTeamMap.end())
//		return true;
//
//	TeamManager * team = new TeamManager();
//	if(team == NULL)
//	{
//		Zebra::logger->debug("内存不足!跨场景建立新队伍失败");
//		return false;
//	}
//
//	team->setTeamtempId(send->dwTeamThisID);
//
//	SceneUser * leader = SceneUserManager::getMe().getUserByID(send->LeaderID);
//
//	if(leader)
//		team->setLeader(leader->tempid);
//	else
//		team->setLeader( 0 );
//
//	for(int i=0; i<send->dwSize; i++)
//	{
//		bool bleaber;
//		if(send->Member->dwID == send->LeaderID)
//			bleaber = true;
//		else
//			bleaber = false;
//
//		team->addWAwayMember(&(send->Member[i]));
//	}
//
//	ScenTeamMap[send->dwTeamThisID] = team;
//
//	return true;
//}

//sky 通知Session也删除队伍管理器的队伍
//bool SceneManager::SceneDelTeam(DWORD TeamID)
//{
//	std::map<DWORD, TeamManager*>::iterator iter;
//	iter = ScenTeamMap.find(TeamID);
//
//	if(iter != ScenTeamMap.end())
//	{
//		/*if(iter->second)
//		{
//			iter->second->deleteTeam();
//			delete iter->second;
//		}
//		
//		ScenTeamMap.erase(iter);
//
//		putTeamID(TeamID);*/
//
//		//sky 告诉Session删除队伍
//		Cmd::Session::t_Team_DelTeam rev;
//		rev.TeamThisID = TeamID;
//		sessionClient->sendCmd(&rev, sizeof(Cmd::Session::t_Team_DelTeam));
//	}
//
//	return true;
//}
//
////sky 删除当前场景的队伍管理器里的队伍
//bool SceneManager::DelMapTeam(DWORD TeamID)
//{
//	std::map<DWORD, TeamManager*>::iterator iter;
//	iter = ScenTeamMap.find(TeamID);
//
//	if(iter != ScenTeamMap.end())
//	{
//		if(iter->second)
//		{
//			iter->second->deleteTeam();
//			delete iter->second;
//		}
//
//		ScenTeamMap.erase(iter);
//
//		putTeamID(TeamID);
//	}
//
//	return true;
//}
//
//void SceneManager::TeamRollItme()
//{
//	std::map<DWORD, TeamManager*>::iterator iter;
//	for(iter=ScenTeamMap.begin(); iter!=ScenTeamMap.end(); iter++)
//	{
//		TeamManager * team = iter->second;
//
//		if(team)
//		{
//			if(team->bRoll)
//				team->RollItem_A();
//		}
//	}
//}