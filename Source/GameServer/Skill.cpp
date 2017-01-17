#include "ScenesServer.h"
#include "SceneEntryPk.h"

///声明
extern int getCharType(DWORD type);

/// 声明技能唯一ID,定义取值范围
///DWORD zSkill::uniqueID(1);

/**
 * \brief 检查技能是否可用
 * \return true 表示可用 false 表示技能不可用
 */
bool zSkill::canUse()
{

  return true;
}

/**
 * \brief 重设冷却时间
 */
void zSkill::resetUseTime()
{
  zRTime ctv;
  lastUseTime = ctv.msecs();
}

/**
 * \brief 清除冷却时间
 */
void zSkill::clearUseTime()
{
  zRTime ctv;
  lastUseTime = 0;
}

/**
 * \brief 构造函数,初始化基本属性
 */
zSkill::zSkill() : zEntry()
{
  zRTime ctv;
  bzero(&data,sizeof(data));
  base = NULL;
  actionbase = NULL;
  inserted = false;
  needSave = false;
  ctv.setmsecs(0);
  lastUseTime = ctv.msecs();
  _entry = NULL;
  dirty = false;
}

/**
 * \brief 检查是否可升级
 * \param pEntry
 * \return true 表示可以升级该技能 false表示升级条件不满足
 */
bool zSkill::canUpgrade(SceneEntryPk *pEntry)
{
  if (pEntry->getLevel() < MAX_SKILLLEVEL)
  {
    return false;
  }

  /*
  if (pUser->charbase.fivevalue[data.five] < data.nextfive)
  {
    return false;
  }
  // */
  return true;
}

/**
 * \brief 检查相应的技能书是否存在,如果存在则删除
 * \param nextbase 是否取下一及的base
 * \return true 可以学习该技能 false 不能学习,没有书
 */
bool zSkill::checkSkillBook(bool nextbase)
{


  return true;
}

/**
 * \brief 检查本技能的学习条件
 * \return false 不可以学习 true 可以学习
 */
bool zSkill::checkSkillStudy(bool nextbase)
{


  return true;
}

/**
 * \brief 根据技能字典初始化本技能对象
 * \param pEntry 等待加载技能的角色
 * \return false 初始化失败 true 初始化成功
 */
bool zSkill::setupSkillBase(SceneEntryPk *pEntry)
{

  return true;
}

/**
 * \brief 第一次学习一个技能的时候使用此方法创建一个技能对象并投送到角色身上
 * \param pEntry 等待加载技能的角色
 * \param id 技能id
 * \param level 技能的级别
 * \return 如果成功加载则返回这个技能对象,否则返回NULL
 */
zSkill *zSkill::create(SceneEntryPk *pEntry,DWORD id,DWORD level)
{
	//zSkillB *basebm = skillbm.get(skill_hash(id,level));
	//if (basebm == NULL) 
	//{
	//	return NULL;
	//}

	//zSkill *ret = new zSkill();
	//if (ret == NULL)
	//{
	//	return NULL;
	//}
	//ret->_entry = pEntry;
	//ret->base = basebm;
	//ret->id = basebm->id;
	//ret->tempid = basebm->skillid;

	////TODO 填充数据
	//ret->data.skillid = basebm->skillid;
	//strncpy(ret->name,basebm->name,MAX_NAMESIZE);
	//ret->data.level = basebm->level;

	//if (pEntry->getType() == zSceneEntry::SceneEntry_Player && pEntry->getPriv()<=Gm::normal_mode)
	//{
	//	if (!ret->checkSkillStudy())
	//	{
	//		SAFE_DELETE(ret);
	//		return NULL;
	//	}

	//	if (!ret->checkSkillBook())
	//	{
	//		SAFE_DELETE(ret);
	//		return NULL;
	//	}

	//	if (pEntry->usm.getPointInTree(ret->base->subkind) < ret->base->needpoint)
	//	{
	//		SAFE_DELETE(ret);
	//		return NULL;
	//	}
	//}

	//ret->setupSkillBase(pEntry);

	//if (!pEntry->addSkillToMe(ret))
	//{
	//	Zebra::logger->debug("zSkill::create():无法将新技能加到角色身上");
	//	SAFE_DELETE(ret);
	//	return NULL;
	//}

	//zRTime ctv;
	//ret->lastUseTime = ctv.msecs() - ret->base->dtime;
	//ret->inserted = true;
	//ret->istemp = false;
	//pEntry->skillStatusM.processPassiveness();
	//return ret;
	return NULL;
}

/**
 * \brief 创建临时技能对象并返回
 * \param pEntry 等待获取技能的角色
 * \param id 技能id
 * \param level 技能的级别
 * \return 如果成功加载则返回这个技能对象,否则返回NULL
 */
zSkill *zSkill::createTempSkill(SceneEntryPk *pEntry,DWORD id,DWORD level)
{
  //zSkillB *basebm = skillbm.get(skill_hash(id,level));
  //if (basebm == NULL) 
  //{
  //  return NULL;
  //}

  //zSkill *ret = new zSkill();
  //if (ret == NULL)
  //{
  //  return NULL;
  //}
  //ret->_entry = pEntry;
  //ret->base = basebm;
  //ret->id = basebm->id;
  //ret->tempid = basebm->skillid;///++uniqueID;
  ////if (!ret->tempid)
  ////{
  ////  ret->tempid = ++uniqueID;
  ////}

  ////TODO 填充数据
  //ret->data.skillid = basebm->skillid;
  //strncpy(ret->name,basebm->name,MAX_NAMESIZE);
  //ret->data.level = basebm->level;

  //ret->inserted = true;
  //ret->istemp = true;
  //return ret;
	return NULL;
}

/**
 * \brief 加载一个技能到角色身上
 * \param pEntry 等待加载技能的角色
 * \param s 需要加载的存档
 * \return 如果成功加载则返回这个技能对象,否则返回NULL
 */
zSkill *zSkill::load(SceneEntryPk *pEntry,const SaveSkill *s)
{
  //DWORD mylevel = 0;
  //DWORD colddown = 0;

  //if (s == NULL)
  //{
  //  return NULL;
  //}
  //
  //mylevel = s->level%100;
  //colddown = (s->level - mylevel)/100;
  //zSkillB *basebm = skillbm.get(skill_hash(s->type,mylevel));
  //

  //if (basebm == NULL)
  //{
  //  return NULL;
  //}

  //zSkill *ret = new zSkill();
  //if (ret == NULL)
  //{
  //  return NULL;
  //}
  //ret->_entry = pEntry;
  //ret->id = basebm->id;
  //ret->tempid = basebm->skillid;///++uniqueID;
  ////if (!ret->tempid)
  ////{
  ////  ret->tempid = ++uniqueID;
  ////}
  ///*
  //if (ret->tempid == uniqueID.invalid())
  //{
  //  SAFE_DELETE(ret);
  //  return NULL;
  //}
  //// */
  //ret->data.skillid = basebm->skillid;
  //strncpy(ret->name,basebm->name,MAX_NAMESIZE);
  //ret->data.level = basebm->level;
  //ret->setupSkillBase(pEntry);
  //ret->_entry=pEntry;

  //zRTime ctv;
  //if (colddown>ret->base->dtime) colddown = ret->base->dtime;
  //ret->lastUseTime = ctv.msecs() - (ret->base->dtime - colddown);
  //
  //if (!pEntry->addSkillToMe(ret))
  //{
  //  SAFE_DELETE(ret);
  //  return NULL;
  //}
  //ret->inserted = true;
  //ret->istemp = false;
  ////if (ret->base->usetype == SKILL_TYPE_PASSIVENESS) ret->doPassivenessSkill();
  //return ret;
  return NULL;
}

/**
 * \brief 刷新技能,主要用于武器更换对技能登基造成的影响
 */
void zSkill::refresh(bool ignoredirty)
{
  /*actionbase = this->getNewBase();
  if (dirty||ignoredirty)
  {
    dirty = false;
    zRTime ctv;
    DWORD colddown = ctv.msecs() - this->lastUseTime;
    if (colddown >= this->base->dtime)
      colddown = 0;
    else
      colddown = this->base->dtime - colddown;

    Cmd::stAddUserSkillPropertyUserCmd ret;
    ret.dwSkillID = this->base->skillid;
    ret.wdLevel = this->base->level;
    ret.wdUpNum = _entry->skillUpLevel(base->skillid,base->kind);
    if (ret.wdUpNum+ret.wdLevel>10) ret.wdUpNum = 10 - ret.wdLevel;
    ret.dwExperience = colddown;
    if (this->base->usetype == SKILL_TYPE_PASSIVENESS) this->doPassivenessSkill();
    if (_entry->getType()==zSceneEntry::SceneEntry_Player) ((SceneUser *)_entry)->sendCmdToMe(&ret,sizeof(ret));
  }*/
}


/**
 * \brief 获取技能存档数据
  * \return ture （无聊要这个返回值做什么）
 */
bool zSkill::getSaveData(SaveSkill *save)
{
 /* zRTime ctv;
  DWORD colddown = ctv.msecs() - this->lastUseTime;
  if (colddown >= this->base->dtime)
    colddown = 0;
  else
    colddown = this->base->dtime - colddown;
  save->type = data.skillid;
  save->level = (colddown) *100 + data.level;*/
  return true;
}


/**
 * \brief 析构处理
  */

zSkill::~zSkill()
{
  if (inserted)
  {
    inserted = false;
    bzero(&data,sizeof(data));
  }
}

const zSkillB *zSkill::getNewBase()
{
  //const zSkillB *temp = NULL;
  //DWORD curLevel = base->level + _entry->skillUpLevel(base->skillid,base->kind);
  //if (curLevel >10) curLevel = 10;

  //temp = skillbm.get(skill_hash(base->skillid,curLevel));

  //if (!temp)
  //  temp = base;
  //if (!dirty &&(temp != actionbase)) dirty = true;
  return /*temp*/ NULL;
}

/**
 * \brief 执行一个永久被动操作
 */
void zSkill::doPassivenessSkill()
{
  std::vector<SkillStatus>::const_iterator iter;

  actionbase = getNewBase();

  //for(iter  = actionbase->skillStatus.begin(); iter != actionbase->skillStatus.end(); iter ++)
  //{
  //  SkillStatus *pSkillStatus = (SkillStatus *)&*iter;
  //  DWORD skillid = actionbase->skillid;
  //  _entry->skillStatusM.putPassivenessOperationToMe(skillid,pSkillStatus);
  //}
}

/**
 * \brief  触发一个技能[SKY技能触发]
 * \param  rev 本次收到的客户端消息
 * \param cmdLen 消息长度
 * \return true 技能使用成功 false 技能使用失败
 */
bool zSkill::action(const Cmd::stAttackMagicUserCmd *rev,const DWORD cmdLen)
{
  if (_entry)
  {
 //   actionbase = getNewBase();
 //   curRevCmd = rev;
 //   curRevCmdLen = cmdLen;

	////sky SKILLID_IMMOLATE 献祭技能的ID
	//if(rev->wdMagicType == SKILLID_IMMOLATE && _entry->Immolate)
	//{
	//	_entry->skillStatusM.clearSkill(rev->wdMagicType);
	//	return true;
	//}

 //   // 消耗
 //   if (this->istemp||_entry->needWeapon(curRevCmd->wdMagicType)) // 检查施放技能是否需要武器
 //   {
 //     if (actionbase->ride==0) 
 //     {
 //       if (_entry->checkMountHorse()) return false;
 //     }
 //     if (_entry->checkSkillCost(actionbase))  // 计算自身各种消耗
 //     {
 //       if (_entry->checkPercent())  // 判断技能施放成功的几率
 //       {
 //         std::vector<SkillStatus>::const_iterator iter;
 //         if (_entry->checkReduce(actionbase->objcost,actionbase->objnum))
 //         {
 //           showMagicToAll();
 //           switch(rev->wdMagicType)
 //           {
 //             case 226: // 食尸术
 //             case 319: // 尸暴术
 //               {
 //                 SceneNpc *pNpc = SceneNpcManager::getMe().getNpcByTempID(rev->dwDefenceTempID);
 //                 if (pNpc)
 //                 {
 //                   if (pNpc->getState() == zSceneEntry::SceneEntry_Death && !pNpc->isUse) 
 //                   {
 //                     pNpc->isUse = true;
 //                     Cmd::stRemoveMapNpcMapScreenUserCmd removeNpc;
 //                     removeNpc.dwMapNpcDataPosition = rev->dwDefenceTempID;
 //                     pNpc->scene->sendCmdToNine(pNpc->getPosI(),&removeNpc,sizeof(removeNpc),pNpc->dupIndex);
 //                   }
 //                   else
 //                   {
 //                     return false;
 //                   }
 //                 }
 //                 else
 //                 {
 //                   return false;
 //                 }
 //               }
 //               break;
 //             default:
 //               break;
 //           }
 //           _entry->doSkillCost(actionbase);
 //           for(iter  = actionbase->skillStatus.begin(); iter != actionbase->skillStatus.end(); iter ++)
 //           {
 //             // 处理依赖消耗物品型技能对物品的消耗,目前此接口未启用,两个参数分别是物品ID和消耗数量
 //             {
 //               SkillStatus *pSkillStatus = (SkillStatus *)&*iter;
 //               doOperation(pSkillStatus);
 //             }
 //           }
 //           _entry->reduce(actionbase->objcost,actionbase->objnum);
 //           return true;
 //         }
 //       }
 //     }
 //   }
  }
  else
  {
    Zebra::logger->error("学习的技能中_entry指针为空");
  }
  return false;
}

/**
 * \brief 展示魔法效果
 * \return 如果是返回true表示可以继续处理攻击攻击过程否则false表示返回
 */
bool zSkill::showMagicToAll()
{
  if (!ScenePk::attackUserCmdToNine(curRevCmd,_entry))
  {
    return false;
  }
  return true;
}

/**
 * \brief 遍历,查找在有效范围内的点
 *
struct GetMagicPosExec : public MagicPosExec
{
  GetMagicPosExec(SceneMagic::zPos_vector &pos_vec,Scene *s) : _pos_vec(pos_vec),scene(s){}
  //~GetMaigcPosExec(){}
  bool exec(zPos &pos)
  {
    //检查范围有效
    if (!scene->zPosValidate(pos))
    {
      return false;
    }
    _pos_vec.push_back(pos);
    return true;
  }
  private:
  SceneMagic::zPos_vector &_pos_vec;
  Scene *scene;
};
*/

/**
 * \brief  遍历结构,用来给组队中所有队员广播消息
 */


/**
 * \brief 执行一个技能操作（一个操作包含若干个技能状态,操作有不同的目标对象和范围等）[sky]技能操作
 */
void zSkill::doOperation(const SkillStatus *pSkillStatus)
{
  _entry->carrier.status  = pSkillStatus;      // 一个技能操作
  //_entry->carrier.skilltype = base->usetype;  // 技能使用类型
  //_entry->carrier.skillID  = id;        // 技能ID
  _entry->carrier.skillbase = actionbase;        // 技能字典
  _entry->carrier.revCmd  = *curRevCmd;      // 保存本次收到的攻击消息
  _entry->carrier.attacker  = _entry;      // 攻击者的指针


//  WORD wdTarget = pSkillStatus->target;
//  if (wdTarget& TARGET_SELF)
//  {
//    if (_entry->skillStatusM.putOperationToMe(_entry->carrier,true))
//    {
//      //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//    }
//    wdTarget&=(0xff & (~(1))); // 清除表示自己的位,如果只对自己施法那么wdTarget将为0
//  }
//
//  _entry->pkValue.damagebonus = actionbase->damnum;
//  Scene *pScene = NULL;
//  pScene = _entry->scene;
//  if (wdTarget)
//  {
//    if (1 == pSkillStatus->range) // 1据说表示单格,所以做为单攻的判断标志
//    {
//      switch(curRevCmd->byAttackType)
//      {
//        case Cmd::ATTACKTYPE_N2U:  /// Npc攻击用户
//          {
//            //if (!_entry->isPkZone()) return;
//            /*if (_entry->tempid == curRevCmd->dwDefenceTempID)
//            {
//              ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//              return;
//            }*/
//            SceneUser *pDef = pScene->getUserByTempID(curRevCmd->dwDefenceTempID);
//            if (pDef)
//            {
//              if (wdTarget&TARGET_FRIEND)
//              {
//                if (!_entry->isEnemy(pDef,false,true)&&_entry->checkMagicFlyRoute(pDef,pSkillStatus->mode))
//                {
//                  if (pDef->skillStatusM.putOperationToMe(_entry->carrier,true))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//              }
//              if (wdTarget&TARGET_ENEMY)
//              {
//                if (pDef->getTopMaster()&&pDef->getTopMaster()->getType() == zSceneEntry::SceneEntry_Player)
//                {
//                  if (!(pDef->isPkZone(_entry) && _entry->isPkZone(pDef))) // 新加&&this->isPkZone(pDef)
//                  {
//                    ScenePk::attackFailToMe(curRevCmd,_entry);
//                    return;
//                  }
//                }
//
//                if (_entry->isEnemy(pDef,_entry->getType() == zSceneEntry::SceneEntry_Player)&& // 判断敌人友和检查PK模式是一个方法,所以只要判断一次就OK了
//                  _entry->checkMagicFlyRoute(pDef,pSkillStatus->mode))
//                {
//                  if (pDef->skillStatusM.putOperationToMe(_entry->carrier))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//              }
//            }
//          }
//          break;
//        case Cmd::ATTACKTYPE_U2U:  /// 用户攻击用户
//          {
//            //if (!_entry->isPkZone()) return;
//            /*if (_entry->tempid == curRevCmd->dwDefenceTempID)
//            {
//              ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//              return;
//            }*/
//            SceneUser *pDef = pScene->getUserByTempID(curRevCmd->dwDefenceTempID);
//            if (pDef)
//            {
//              if (wdTarget&TARGET_FRIEND)
//              {
//                if (!_entry->isEnemy(pDef,false,true)&&_entry->checkMagicFlyRoute(pDef,pSkillStatus->mode))
//                {
//                  if (pDef->skillStatusM.putOperationToMe(_entry->carrier,true))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//              }
//              if (wdTarget&TARGET_ENEMY)
//              {
//                if (_entry->isEnemy(pDef,_entry->getType() == zSceneEntry::SceneEntry_Player)&& // 判断敌人友和检查PK模式是一个方法,所以只要判断一次就OK了
//                  pDef->isPkZone(_entry)&&_entry->isPkZone(pDef)&&//新加 _entry->isPkZone(pDef)
//                  _entry->checkMagicFlyRoute(pDef,pSkillStatus->mode))
//                {
//                  if (pDef->skillStatusM.putOperationToMe(_entry->carrier))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//                else
//                {
//                  ScenePk::attackFailToMe(curRevCmd,_entry);
//                }
//              }
//            }
//          }
//          break;
//        case Cmd::ATTACKTYPE_U2N:  /// 用户攻击Npc
//          {
//            SceneNpc *pNpc = SceneNpcManager::getMe().getNpcByTempID(curRevCmd->dwDefenceTempID);
//            if (pNpc)
//            {
//              if (wdTarget&TARGET_PET)
//              {
//                if (!_entry->isEnemy(pNpc,false,true)&&_entry->checkMagicFlyRoute(pNpc,pSkillStatus->mode)&&pNpc->getPetType()==Cmd::PET_TYPE_PET)
//                {
//                  if (pNpc->skillStatusM.putOperationToMe(_entry->carrier,true))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//              }
//              else if (wdTarget&TARGET_SUMMON)
//              {
//                if (!_entry->isEnemy(pNpc,false,true)&&_entry->checkMagicFlyRoute(pNpc,pSkillStatus->mode)&&pNpc->getPetType()==Cmd::PET_TYPE_SUMMON)
//                {
//                  if (pNpc->skillStatusM.putOperationToMe(_entry->carrier,true))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//              }
//              else if (wdTarget&TARGET_NPC)
//              {
//                if (pNpc->getTopMaster()&&pNpc->getTopMaster()->getType() == zSceneEntry::SceneEntry_Player)
//                {
//                  if (!(pNpc->isPkZone(_entry) && _entry->isPkZone(pNpc))) // 新加&&this->isPkZone(pDef)
//                  {
//                    ScenePk::attackFailToMe(curRevCmd,_entry);
//                    return;
//                  }
//                }
//
//                if (_entry->isEnemy(pNpc)&& // 判断敌人友和检查PK模式是一个方法,所以只要判断一次就OK了
//                  _entry->checkMagicFlyRoute(pNpc,pSkillStatus->mode))
//                {
//                  if (pNpc->skillStatusM.putOperationToMe(_entry->carrier))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//                else
//                {
//                  ScenePk::attackFailToMe(curRevCmd,_entry);
//                }
//              }
//            }
//          }
//          break;
//        case Cmd::ATTACKTYPE_N2N:  /// Npc攻击Npc
//          {
//            SceneNpc *pNpc = SceneNpcManager::getMe().getNpcByTempID(curRevCmd->dwDefenceTempID);
//            if (pNpc)
//            {
//              if (wdTarget&TARGET_PET)
//              {
//                if (!_entry->isEnemy(pNpc,false,true)&&_entry->checkMagicFlyRoute(pNpc,pSkillStatus->mode)&&pNpc->getPetType()==Cmd::PET_TYPE_PET)
//                {
//                  if (pNpc->skillStatusM.putOperationToMe(_entry->carrier,true))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//              }
//              else if (wdTarget&TARGET_SUMMON)
//              {
//                if (!_entry->isEnemy(pNpc,false,true)&&_entry->checkMagicFlyRoute(pNpc,pSkillStatus->mode)&&pNpc->getPetType()==Cmd::PET_TYPE_SUMMON)
//                {
//                  if (pNpc->skillStatusM.putOperationToMe(_entry->carrier,true))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                    return;
//                  }
//                  else
//                  {
//                    return;
//                  }
//                }
//              }
//              else if (wdTarget&TARGET_NPC)
//              {
//                if (_entry->getTopMaster() &&
//                  _entry->getTopMaster()->getType() == zSceneEntry::SceneEntry_Player &&
//                  pNpc->getTopMaster() &&
//                  pNpc->getTopMaster()->getType() == zSceneEntry::SceneEntry_Player)
//                {
//                  if (!(pNpc->isPkZone(_entry) && _entry->isPkZone(pNpc))) // 新加&&this->isPkZone(pDef)
//                  {
//                    ScenePk::attackFailToMe(curRevCmd,_entry);
//                    return;
//                  }
//                }
//
//                if (_entry->isEnemy(pNpc)&& // 判断敌人友和检查PK模式是一个方法,所以只要判断一次就OK了
//                  _entry->checkMagicFlyRoute(pNpc,pSkillStatus->mode))
//                {
//                  if (pNpc->skillStatusM.putOperationToMe(_entry->carrier))
//                  {
//                    //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//                  }
//                  return;
//                }
//              }
//            }
//          }
//          break;
//        case Cmd::ATTACKTYPE_U2P:  /// 用户攻击点
//          {
//            zPos pd;
//            DWORD num =0;
//            pd.x = (DWORD)curRevCmd->xDes;
//            pd.y = (DWORD)curRevCmd->yDes;
//            if (findAttackTarget(pSkillStatus,pd,num))
//            {
//              //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
//            }
//            return;
//          }
//          break;
//        case Cmd::ATTACKTYPE_U2B:  /// 用户攻击建筑
//        default:
//          {
//            //if (!ScenePk::attackUserCmdToNine(curRevCmd,_entry))
//            //{
//            //  return;
//            //}
//            return;
//          }
//          break;
//      }
////      ScenePk::attackFailToMe(curRevCmd,_entry);
//    }
//    else
//    {
//      zPos center,pd;
//      BYTE byDir=0;
//      if (curRevCmd->dwDefenceTempID!=0)
//      {
//        switch(curRevCmd->byAttackType)
//        {
//          case Cmd::ATTACKTYPE_N2U:  /// Npc攻击用户
//          case Cmd::ATTACKTYPE_U2U:  /// Npc攻击用户
//            {
//              SceneUser *pDef = pScene->getUserByTempID(curRevCmd->dwDefenceTempID);
//              if (pDef)
//              {
//                center = pDef->getPos();
//              }
//              else
//              {
//                center.x = (DWORD)curRevCmd->xDes;
//                center.y = (DWORD)curRevCmd->yDes;
//              }
//            }
//            break;
//          case Cmd::ATTACKTYPE_N2N:  /// Npc攻击用户
//          case Cmd::ATTACKTYPE_U2N:  /// Npc攻击用户
//            {
//              SceneNpc *pNpc = SceneNpcManager::getMe().getNpcByTempID(curRevCmd->dwDefenceTempID);
//              if (pNpc)
//              {
//                center = pNpc->getPos();
//              }
//              else
//              {
//                center.x = (DWORD)curRevCmd->xDes;
//                center.y = (DWORD)curRevCmd->yDes;
//              }
//            }
//            break;
//          default:
//            {
//              center.x = (DWORD)curRevCmd->xDes;
//              center.y = (DWORD)curRevCmd->yDes;
//            }
//            break;
//        }
//      }
//      else
//      {
//        center.x = (DWORD)curRevCmd->xDes;
//        center.y = (DWORD)curRevCmd->yDes;
//      }
//
//      switch(pSkillStatus->center)
//      {
//        case SKILL_CENTER_TYPE_MOUSE:
//          {
////            center.x = (DWORD)curRevCmd->xDes;
////            center.y = (DWORD)curRevCmd->yDes;
//            byDir = curRevCmd->byDirect;
//            _entry->setDir(byDir);
//#ifdef _DEBUG 
//            Channel::sendSys(_entry->tempid,Cmd::INFO_TYPE_GAME,"中心点类型：鼠标（%u,%u) 方向:%u",center.x,center.y,byDir);
//#endif
//            // debug提示
//          }
//          break;
//        case SKILL_CENTER_TYPE_SELF:
//          {
//            center.x = _entry->getPos().x;
//            center.y = _entry->getPos().y;
//            byDir = curRevCmd->byDirect;//_entry->getDir();
//            _entry->setDir(byDir);
//#ifdef  _DEBUG 
//            Channel::sendSys(_entry->tempid,Cmd::INFO_TYPE_GAME,"中心点类型：自身（%u,%u) 方向:%u",center.x,center.y,byDir);
//#endif
//          }
//          break;
//        default:
//#ifdef _DEBUG 
//          Channel::sendSys(_entry->tempid,Cmd::INFO_TYPE_GAME,"中心点类型：填写错误请查证");
//#endif
//          break;
//      }
//
//      switch(pSkillStatus->range)
//      {
//        case 20:
//          {
//            DWORD tempLen = sizeof(struct Cmd::stAttackMagicUserCmd);
//            DWORD itemNum = 0;
//#ifdef _DEBUG
//            Zebra::logger->error("!!!---客户端发过来的攻击指令原始长度[%u] 当前长度[%u]",tempLen,curRevCmdLen);
//#endif
//            if (curRevCmdLen>tempLen)
//            {
//              itemNum = (curRevCmdLen-tempLen)/sizeof(DWORD);
//#ifdef _DEBUG
//              Zebra::logger->error("!!!---客户端发过来的攻击列表数目[%u]",itemNum);
//#endif
//              if (itemNum >5) itemNum=5;
//              for (DWORD i=0; i<itemNum; i++)
//              {
//                SceneNpc *pNpc=NULL;
//                SceneUser *pUser=NULL;
//#ifdef _DEBUG
//                Zebra::logger->error("!!!---客户端发过来的被攻击临时坐标[%u]",curRevCmd->dwTempIDList[i]);
//#endif
//                if ((pNpc=_entry->scene->getNpcByTempID(curRevCmd->dwTempIDList[i]))!=NULL)
//                {
//                  pd = pNpc->getPos();
//                }
//                else if ((pUser=_entry->scene->getUserByTempID(curRevCmd->dwTempIDList[i]))!=NULL)
//                {
//                  pd = pUser->getPos();
//                }
//                else continue;
///*
//                pd.x= (curRevCmd->dwTempIDList[i]>>16) &0xffff;
//                pd.y= (curRevCmd->dwTempIDList[i]&0xff);
//*/    
//#ifdef _DEBUG
//                Zebra::logger->error("!!!---客户端发过来的攻击坐标[%u][x=%u,y=%u]",curRevCmd->dwTempIDList[i],pd.x,pd.y);
//#endif
//
////-技能范围测试
//#ifdef _DEBUG
//                zObjectB *base = objectbm.get(501);
//                if (base)
//                {
//                  zObject *o=zObject::create(base,1);
//                  _entry->scene->addObject(o,pd);
//                }
//#endif
//                DWORD num=0;
//                if (!findAttackTarget(pSkillStatus,pd,num)) break;
//              }
//            }
//          }
//          break;
//        case 21:
//          {
//            zPosVector range;
//            pScene->findEntryPosInNine(_entry->getPos(),_entry->getPosI(),range);
//            for(zPosVector::iterator iter = range.begin(); iter != range.end() ; iter ++)
//            {
//              pd = *iter;
////-技能范围测试
//#ifdef _DEBUG
//              zObjectB *base = objectbm.get(585);
//              if (base)
//              {
//                zObject *o=zObject::create(base,randBetween(1,10));
//                _entry->scene->addObject(o,pd);
//              }
//#endif
//              DWORD num=0;
//              if (!findAttackTarget(pSkillStatus,pd,num)) break;
//            }
//          }
//          break;
//        case 22:
//          {
//            if (_entry->getType() == zSceneEntry::SceneEntry_Player)
//            {
//              SceneUser *pUser = (SceneUser *)_entry;
//
//			  TeamManager * team = SceneManager::getInstance().GetMapTeam(pUser->TeamThisID);
//
//              if (team)
//              {
//				  SendStatusToTeamExec exec(pUser,pSkillStatus);
//				  team->execEveryOne(exec);
//              }
//            }
//          }
//          break;
//        case 50:
//          {
//            zPosVector range;
//            int count=0;
//            pScene->findEntryPosInOne(_entry->getPos(),_entry->getPosI(),range);
//            for(zPosVector::iterator iter = range.begin(); iter != range.end() ; iter ++)
//            {
//              count++;
//              if (count>20) break;
//              pd = *iter;
////-技能范围测试
//#ifdef _DEBUG
//              zObjectB *base = objectbm.get(585);
//              if (base)
//              {
//                zObject *o=zObject::create(base,randBetween(1,10));
//                _entry->scene->addObject(o,pd);
//              }
//#endif
//              DWORD num=0;
//              if (!findAttackTarget(pSkillStatus,pd,num)) break;
//            }
//          }
//          break;
//        default:
//          {
//            SMagicRange range;
//            DWORD maxCount =0;
//            DWORD count=0;
//            MagicRangeInit::getInstance().get(pSkillStatus->range,byDir % 2,range);
//            maxCount = range.num;
//            if (0==maxCount) maxCount = 65535;
//            for(std::vector<RelativePos>::iterator iter = range.lib.begin(); iter != range.lib.end() ; iter ++)
//            {
//              SWORD rangDamageBonus=0;
//              pd = iter->getAbsolutePos(center,byDir);
//              rangDamageBonus = (*iter).w;
////-技能范围测试
//#ifdef _DEBUG
//              zObjectB *base = objectbm.get(585);
//              if (base)
//              {
//                zObject *o=zObject::create(base,randBetween(1,10));
//                _entry->scene->addObject(o,pd);
//              }
//#endif
//              DWORD num=0;
//              if (!findAttackTarget(pSkillStatus,pd,num,rangDamageBonus)) break;
//              if (num>0)
//              {
//                count++;
//                if (count>= maxCount) break;
//              }
//            }
//          }
//      }
//      return;
//    }
//  }
}

/**
 * \brief 投送操作到目标对象身上
 * \param pSkillStatus 操作
 * \param pd 坐标点
 * \return 如果是返回true表示可以继续处理攻击攻击过程否则false表示返回
 */
bool zSkill::findAttackTarget(const SkillStatus *pSkillStatus,zPos &pd,DWORD &count,SWORD rangDamageBonus)
{
  //WORD wdTarget = pSkillStatus->target;
  //Scene *pScene = _entry->scene;

  ////检查范围有效
  //if (!pScene->zPosValidate(pd))
  //{
  //  return true;
  //}
  //SceneUser *pFindUser = NULL;
  //SceneNpc  *pFindNpc = NULL;
  //if (wdTarget&TARGET_FRIEND)
  //{
  //  pFindUser = pScene->getSceneUserByPos(pd);
  //  if (pFindUser/* && pFindUser!=_entry*/)
  //  {
  //    if (!_entry->isEnemy(pFindUser,false,true)&&_entry->checkMagicFlyRoute(pFindUser,pSkillStatus->mode))
  //    {
  //      count=1;
  //      if (pFindUser->skillStatusM.putOperationToMe(_entry->carrier,true,rangDamageBonus))
  //      {
  //        //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
  //        return true;
  //      }
  //      else
  //      {
  //        return false;
  //      }
  //    }
  //  }
  //}
  //if (wdTarget&TARGET_ENEMY)
  //{
  //  if (!pFindUser) pFindUser = pScene->getSceneUserByPos(pd);
  //  if (pFindUser && pFindUser!=_entry)
  //  {
  //    if (_entry->getTopMaster()&&_entry->getTopMaster()->getType() == zSceneEntry::SceneEntry_Player)
  //    {
  //      if (!(pFindUser->isPkZone(_entry) && _entry->isPkZone(pFindUser))) // 新加&&this->isPkZone(pDef)
  //      {
  //        return true;
  //      }
  //    }

  //    if (_entry->isEnemy(pFindUser)&&
  //       _entry->checkMagicFlyRoute(pFindUser,pSkillStatus->mode))
  //    {
  //      count=1;
  //      if (pFindUser->skillStatusM.putOperationToMe(_entry->carrier,false,rangDamageBonus))
  //      {
  //        //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
  //        return true;
  //      }
  //      else
  //      {
  //        return false;
  //      }
  //    }
  //  }
  //}

  //if (!pFindUser)
  //{
  //  if (wdTarget&TARGET_PET)
  //  {
  //    pFindNpc = pScene->getSceneNpcByPos(pd);
  //    if (pFindNpc/* && pFindNpc!=_entry*/)
  //    {
  //      if (!_entry->isEnemy(pFindNpc,false,true)&&_entry->checkMagicFlyRoute(pFindNpc,pSkillStatus->mode)&&pFindNpc->getPetType()==Cmd::PET_TYPE_PET)
  //      {
  //        count=1;
  //        if (pFindNpc->skillStatusM.putOperationToMe(_entry->carrier,true,rangDamageBonus))
  //        {
  //          //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
  //          return true;
  //        }
  //        else
  //        {
  //          return false;
  //        }
  //      }
  //    }
  //  }

  //  if (wdTarget&TARGET_SUMMON)
  //  {
  //    pFindNpc = pScene->getSceneNpcByPos(pd);
  //    if (pFindNpc/* && pFindNpc!=_entry*/)
  //    {
  //      if (!_entry->isEnemy(pFindNpc,false,true)&&_entry->checkMagicFlyRoute(pFindNpc,pSkillStatus->mode)&&pFindNpc->getPetType()==Cmd::PET_TYPE_SUMMON)
  //      {
  //        count=1;
  //        if (pFindNpc->skillStatusM.putOperationToMe(_entry->carrier,true,rangDamageBonus))
  //        {
  //          //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
  //          return true;
  //        }
  //        else
  //        {
  //          return false;
  //        }
  //      }
  //    }
  //  }

  //  if (wdTarget&TARGET_NPC)
  //  {
  //    if (!pFindNpc) pFindNpc = pScene->getSceneNpcByPos(pd);
  //    if (pFindNpc && pFindNpc!=_entry)
  //    {
  //      if (_entry->getTopMaster() &&
  //        _entry->getTopMaster()->getType() == zSceneEntry::SceneEntry_Player &&
  //        pFindNpc->getTopMaster() &&
  //        pFindNpc->getTopMaster()->getType() == zSceneEntry::SceneEntry_Player)
  //      {
  //        if (!(pFindNpc->isPkZone(_entry) && _entry->isPkZone(pFindNpc))) // 新加&&this->isPkZone(pDef)
  //        {
  //          return true;
  //        }
  //      }
  //      if (_entry->isEnemy(pFindNpc)&&
  //         _entry->checkMagicFlyRoute(pFindNpc,pSkillStatus->mode))
  //      {
  //        count=1;
  //        if (pFindNpc->skillStatusM.putOperationToMe(_entry->carrier,false,rangDamageBonus))
  //        {
  //          //ScenePk::attackUserCmdToNine(curRevCmd,_entry);
  //          return true;
  //        }
  //        else
  //        {
  //          return false;
  //        }
  //      }
  //    }
  //  }
  //}
  return true;
}

/*
	sky 新增技能特殊属性检测函数 begin
*/


