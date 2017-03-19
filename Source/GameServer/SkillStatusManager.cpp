/**
 * \brief 定义技能状态管理器头文件
 *
 */

#include "ScenesServer.h"
#include "SceneEntryPk.h"
#include "SceneUser.h"
#include "SceneUserMgr.h"

/**
 * \brief  状态0 空状态,不做任何操作
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_0(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 0;
  return SKILL_RETURN;
}

/**
 * \brief  状态1 对状态接受者伤害增加固定数值
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_1(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 1;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
//          pEntry->skillValue.dvalue += sse.value;
          //pEntry->pkValue.dvalue += sse.value;
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
//        pEntry->skillValue.dvalue += sse.value;
       // pEntry->pkValue.dvalue += sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态2 对状态接受者伤害增加百分比,基准数值为角色的裸身与装备攻击力的总和
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_2(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 1;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
         /* pEntry->skillValue.dvaluep = sse.value;
          pEntry->pkValue.dvaluep = sse.value;*/
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
        /*pEntry->skillValue.dvaluep = sse.value;
        pEntry->pkValue.dvaluep = sse.value;*/
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态3 技能的物理攻击力[此状态可能已经被废弃]
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_3(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 2;
 // pEntry->reSendData = true;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
//          pEntry->skillValue.pdam = sse.value;
         // pEntry->pkValue.pdamage = sse.value;
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
//        pEntry->skillValue.pdam += sse.value;
       // pEntry->pkValue.pdamage = sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态4 指定状态接受者的物理防御基础值[基本上不存在这种技能所以此状态可能也已经被废弃]
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_4(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 3;
 // pEntry->reSendData = true;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
//          pEntry->skillValue.pdef = sse.value;
       //   pEntry->pkValue.pdefence = sse.value;
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
       // pEntry->pkValue.pdefence = sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态5 表示状态接受者裸身法术攻击力,装备法术攻击的力总和
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_5(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 10;
//  pEntry->reSendData = true;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
//          pEntry->skillValue.mdam = sse.value;
       //   pEntry->pkValue.mdamage = sse.value;
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
       // pEntry->pkValue.mdamage = sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态6 表示状态接受者裸身法术防御力,装备法术防御力的总和
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_6(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_GOOD;
  sse.byMutexType = 11;
  //pEntry->reSendData = true;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
          //pEntry->skillValue.mdef = sse.value;
       //   pEntry->pkValue.mdefence = sse.value;
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
      //  pEntry->pkValue.mdefence = sse.value;
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态7 消耗状态接受者的固定值法术值
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_7(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 4;

  WORD value=0;
  if (sse.attacktype == zSceneEntry::SceneEntry_Player)
  {
    SceneUser *pUser = NULL;
    pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(sse.dwTempID);
    if (pUser)
    {
     // value= (WORD)(0.5f*pUser->charstate.wdMen);
    }
  }

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
         // pEntry->changeMP(0-sse.value-value);
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
      //  pEntry->changeMP(0-sse.value-value);
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态8 消耗状态接受者的百分比法术值
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_8(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 4;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
         /* SDWORD value = (SDWORD)(pEntry->getMaxMP()*(sse.value/100.0f));
          pEntry->changeMP(value);*/
          return SKILL_RECOVERY;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
        /*SDWORD value = (SDWORD)(pEntry->getMaxMP()*(sse.value/100.0f));
        pEntry->changeMP(value);*/
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态9 消耗状态接受者的固定值生命值
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_9(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 5;

  WORD value=0;
  if (sse.attacktype == zSceneEntry::SceneEntry_Player)
  {
    SceneUser *pUser = NULL;
    pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(sse.dwTempID);
    if (pUser)
    {
      //value= (WORD)(1*pUser->charstate.wdMen);
    }
  }

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
          //pEntry->changeHP(0-sse.value);
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
        SceneEntryPk *pAtt = NULL;
        switch(sse.attacktype)
        {
          case zSceneEntry::SceneEntry_Player:  // 玩家角色
            {
             // pAtt = NetService::getMe().getSceneUserMgr().getUserBySessID(sse.dwTempID);
            }
            break;
          case zSceneEntry::SceneEntry_NPC:    // NPC
            {
              //pAtt = SceneNpcManager::getMe().getNpcByTempID(sse.dwTempID);
            }
            break;
          default:
            break;
        }

        if (pAtt)
        {
          //pEntry->directDamage(pAtt,sse.value+value,true);
          //pEntry->processDeath(pAtt);
        }
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

/**
 * \brief  状态10 消耗状态接受者的百分比生命值,基准为最大生命值
 * \param pEntry 状态所有者
 * \param sse 技能状态
 * \return 技能状态返回值,参见头文件中的技能状态处理返回值枚举
 */
BYTE SkillStatus_10(SceneEntryPk *pEntry,SkillStatusElement &sse)
{
  sse.byGoodnessType = SKILL_BAD;
  sse.byMutexType = 5;

  switch(sse.byStep)
  {
    case ACTION_STEP_DOPASS:
    case ACTION_STEP_START:
    case ACTION_STEP_RELOAD:
      {
        if (selectByPercent((int)(sse.percent)))
        {
          //SDWORD value = (SDWORD)(pEntry->getMaxHP()*(sse.value/100.0f));
          //pEntry->changeHP(0-value);
          return SKILL_ACTIVE;
        }
        else
          return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_TIMER:
      {
        SceneEntryPk *pAtt = NULL;
        switch(sse.attacktype)
        {
          case zSceneEntry::SceneEntry_Player:  // 玩家角色
            {
           //   pAtt = NetService::getMe().getSceneUserMgr().getUserBySessID(sse.dwTempID);
            }
            break;
          case zSceneEntry::SceneEntry_NPC:    // NPC
            {
           //   pAtt = SceneNpcManager::getMe().getNpcByTempID(sse.dwTempID);
            }
            break;
          default:
            break;
        }

        if (pAtt)
        {
   /*       SDWORD value = (SDWORD)(pEntry->getMaxHP()*(sse.value/100.0f));
          pEntry->directDamage(pAtt,value,true);
          pEntry->processDeath(pAtt);*/
        }
        return SKILL_RETURN;
      }
      break;
    case ACTION_STEP_STOP:
    case ACTION_STEP_CLEAR:
      {
      }
      break;
    default:
      break;
  }

  return SKILL_RETURN;
}

//--------------------------------------------------

/**
 * \brief 技能状态管理器构造函数
 */
SkillStatusManager::SkillStatusManager()
{
  entry = NULL;
  bclearActiveSkillStatus = false;
}


/**
 * \brief 技能状态管理器析构函数
 */
SkillStatusManager::~SkillStatusManager()
{
  //if (entry->getType() == zSceneEntry::SceneEntry_Player)  saveSkillStatus();
}

/**
 * \brief 技能状态管理器析构函数
 * \param pEntry 传入技能管理器的使用对象
 */
void SkillStatusManager::initMe(SceneEntryPk *pEntry)
{
  entry = pEntry;
  funlist[0].func = SkillStatus_0;
  funlist[1].func = SkillStatus_1;
  funlist[2].func = SkillStatus_2;
  funlist[3].func = SkillStatus_3;
  funlist[4].func = SkillStatus_4;
  funlist[5].func = SkillStatus_5;
  funlist[6].func = SkillStatus_6;
  funlist[7].func = SkillStatus_7;
  funlist[8].func = SkillStatus_8;
  funlist[9].func = SkillStatus_9;
  funlist[10].func = SkillStatus_10;

  //if (entry->getType() == zSceneEntry::SceneEntry_Player) loadSkillStatus();
}

/**
 * \brief 通知某个状态数值
 */
void SkillStatusManager::sendSelectStates(SceneEntryPk *pThis,DWORD state,WORD value,WORD time)
{
  //pThis->sendtoSelectedState(state,value,time);
  //pThis->sendSevenStateToMe(state,value,time);
}

/**
 * \brief 得到当前7大状态的数值
 */
void SkillStatusManager::getSelectStates(Cmd::stSelectReturnStatesPropertyUserCmd *buf,unsigned long maxSize)
{

  using namespace Cmd;
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  zRTime ctv;
  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end(); tIterator++)
  {
    if (tIterator->second.state >0 && 
        (sizeof(stSelectReturnStatesPropertyUserCmd) + sizeof(buf->states[0]) * buf->size)<= maxSize)
    {
      buf->states[buf->size].state = tIterator->second.state;
      buf->states[buf->size].result = tIterator->second.value;
      buf->states[buf->size].time = tIterator->second.dwTime;
      buf->size ++;
    }
/*        break;
      default:
        break;
    }*/
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end(); tIterator++)
  {

    if (tIterator->second.state >0 &&
        (sizeof(stSelectReturnStatesPropertyUserCmd) + sizeof(buf->states[0]) * buf->size)<= maxSize)
    {
      buf->states[buf->size].state = tIterator->second.state;
      buf->states[buf->size].result = tIterator->second.value;
      buf->states[buf->size].time = (tIterator->second.qwTime- ctv.msecs())/1000;
      buf->size ++;
    }
  }

}

/**
 * \brief 加载历史的技能状态,上次下线的时候技能还存留在身上的技能状态继续有效
 */
void SkillStatusManager::loadSkillStatus(char *buf,DWORD length)
{
  SkillStatusElement *value;
//  char buf[zSocket::MAX_DATASIZE];
  DWORD count;
  DWORD statelen;
  bool notify;
  /*DWORD length;

  count = 0; 
  length=0;
  bzero(buf,zSocket::MAX_DATASIZE);*/

  SkillState *pState = (SkillState *)buf;
  statelen = sizeof(SkillState);
 // memcpy(&(entry->skillValue),pState,statelen,sizeof(entry->skillValue));
  length-=statelen;

#ifdef _DEBUG
  H::logger->debug("[为角色(%s)(%d)加载保存的技能状态]",entry->name,entry->id);
#endif
  //COfflineSkillStatus::getOfflineSkillStatus(entry->id,buf,length);
  count = length/sizeof(SkillStatusElement);
  notify = false;
#ifdef _DEBUG
  H::logger->debug("[有%d个技能状态需要加载]",count);
#endif
  value = (SkillStatusElement *)(buf+statelen);

  SceneEntryPk *pAtt = NULL;
  if (value->attacktype == zSceneEntry::SceneEntry_Player)
  {
   // pAtt = NetService::getMe().getSceneUserMgr().getUserByID(value->dwAttackerID);
    if (pAtt) value->dwTempID = pAtt->tempid;
  }

  for(DWORD i=0; i<count; i++)
  {
    value->byStep = ACTION_STEP_RELOAD;
    switch(runStatusElement(*value))
    {
      case SKILL_RECOVERY:
        {
#ifdef _DEBUG
          H::logger->debug("[%d号技能状态被加载到临时被动表内]",value->id);
#endif
          //value->refresh = 1;
          //value->qwTime = H::timeTick->getMilliTime()+value->dwTime *1000;
          _recoveryElement[value->id/*value->byMutexType*/]=*value;
         // _recoveryElement[value->id].qwTime = H::timeTick->getMilliTime()+_recoveryElement[value->id].dwTime *1000;
          if (value->state >0)
          {
            sendSelectStates(entry,value->state,value->value,value->dwTime);
            //entry->setEffectStatus(value->state);
           // entry->showCurrentEffect(value->state,true);
          }
          notify = true;
        }
        break;
      case SKILL_ACTIVE:
        {
#ifdef _DEBUG
          H::logger->debug("[%d号技能状态被加载到主动表内]",value->id);
#endif
          _activeElement[value->id/*value->byMutexType*/]=*value;
         // _recoveryElement[value->id].qwTime = H::timeTick->getMilliTime()+_recoveryElement[value->id].dwTime *1000;
          if (value->state >0)
          {
            sendSelectStates(entry,value->state,value->value,value->dwTime);
            //entry->setEffectStatus(value->state);
          //  entry->showCurrentEffect(value->state,true);
          }
          notify = true;
        }
        break;
      default:
#ifdef _DEBUG
          H::logger->debug("[%d号技能状态无法被加到对应的表中]",value->id);
#endif
        break;
    }
    value++;
  }

  if (notify&&entry)
  {
    //entry->changeAndRefreshHMS(true,true);
  }
}

/**
 * \brief 存储历史的技能状态,上次下线的时候技能还存留在身上的技能状态继续有效
 */
void SkillStatusManager::saveSkillStatus(char *buf,DWORD &size)
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  SkillStatusElement *value;
  DWORD count;
  DWORD statelen;
  DWORD length;

  length = 0;
  count = 0;
  statelen = 0;

  SkillState *pState = (SkillState *)buf;
  statelen = sizeof(SkillState);
  //memcpy(pState,&(entry->skillValue),statelen,statelen);

  value = (SkillStatusElement *)(buf+statelen);
  length = sizeof(SkillStatusElement);
  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end();tIterator ++)
  {
    //memcpy(value,&tIterator->second,length,length);
#ifdef _DEBUG
    H::logger->debug("[技能状态%d被存储]",tIterator->second.id);
#endif
    count++;
    value++;
    if (count>3000) break;
  }

  if (count<3000)
  {
    for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();tIterator ++)
    {
      //memcpy(value,&tIterator->second,length,length);
#ifdef _DEBUG
    H::logger->debug("[技能状态%d被存储]",tIterator->second.id);
#endif
      count++;
      value++;
      if (count>3000) break;
    }
  }
  //if (count >0) COfflineSkillStatus::writeOfflineSkillStatus(entry->id,buf,count*length);
  size = statelen + count*length;
#ifdef _DEBUG
  H::logger->debug("[有%d个技能状态需要存储]",count);
#endif
}

/**
 * \brief 将一个技能操作施加在我的身上[SKY技能链第3步]
 * \param carrier 技能操作投送器,里面包含了技能状态
 * \param good 标志这个技能是不是一个增益的技能
 * \return true 为继续下一个操作,false为停止并返回。
 */
bool SkillStatusManager::putOperationToMe(const SkillStatusCarrier &carrier,const bool good,SWORD rangDamageBonus)
{
  std::vector<SkillElement>::const_iterator tIterator;
  bool sendData = false;

  entry->isPhysics = false;
  if (!entry->preAttackMe(carrier.attacker,&carrier.revCmd,false,good)) return true;

  for (tIterator = carrier.status->_StatusElementList.begin();
    tIterator != carrier.status->_StatusElementList.end();
    tIterator++)
  {
    SkillStatusElement element;
    element.byStep  =  ACTION_STEP_START;
    element.id    =  tIterator->id;
    element.percent =  tIterator->percent;
    element.value  =  tIterator->value;
    element.state  =  tIterator->state;

    element.dwSkillID = carrier.skillbase->id;//carrier.skillID; 
    element.dwTime = tIterator->time;
    element.qwTime = H::timeTick->getMilliTime()+element.dwTime *1000;

    SceneEntryPk *pAtt = carrier.attacker->getTopMaster();
    element.dwTempID = pAtt->tempid;
    element.dwAttackerID = pAtt->id;
    element.attacktype = pAtt->getType();
    if (element.dwTime <=2)
    {
      element.refresh = 0;
    }
    else
    {
      element.refresh = 1;
      sendData = true;
    }

    entry->curMagicManType = element.attacktype;
    entry->curMagicManID = element.dwTempID;
    entry->keepPos.x = (DWORD)carrier.revCmd.xDes;
    entry->keepPos.y = (DWORD)carrier.revCmd.yDes;
    entry->keepDir = carrier.revCmd.byDirect;

    switch(runStatusElement(element))
    {
      case SKILL_RECOVERY:
        {
#ifdef _DEBUG
          H::logger->debug("[临时被动]第[%u]号状态被施加在身上持续时间为[%u]",element.id,element.dwTime);
          Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[临时被动]第[%u]号状态被施加在身上持续时间为[%u]",element.id,element.dwTime);
#endif
          element.qwTime = H::timeTick->getMilliTime()+element.dwTime *1000;
          if (element.state >0)
          {
            clearMapElement(element.id/*element.byMutexType*/,_recoveryElement,element.id,false);
            _recoveryElement[element.id/*element.byMutexType*/]=element;
            sendSelectStates(entry,element.state,element.value,element.dwTime);
            //entry->setEffectStatus(element.state);
            entry->showCurrentEffect(element.state,true);
          }
          else
          {
            clearMapElement(element.id/*element.byMutexType*/,_recoveryElement,element.id);
            _recoveryElement[element.id/*element.byMutexType*/]=element;
          }
        }
        break;
      case SKILL_BREAK:
        {
          return false;
        }
        break;
      case SKILL_ACTIVE:
        {
#ifdef _DEBUG
          H::logger->debug("[伤害状态]第[%u]号状态被施加在身上持续时间为[%u]",element.id,element.dwTime);
          Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[攻击状态]第[%u]号状态被施加在身上持续时间为[%u]",element.id,element.dwTime);
#endif
          if (element.dwTime==0) break;
          clearMapElement(element.id/*element.byMutexType*/,_activeElement,element.id);
          _activeElement[element.id/*element.byMutexType*/]=element;
          if (element.state >0)
          {
            sendSelectStates(entry,element.state,element.value,element.dwTime);
            //entry->setEffectStatus(element.state);
            entry->showCurrentEffect(element.state,true);
          }
        }
        break;
      case SKILL_RETURN:
      default:
        break;
    }
  }

  if (carrier.status->isInjure == 1)
  {
    entry->AttackMe(carrier.attacker,&carrier.revCmd,entry->isPhysics,rangDamageBonus);
   // carrier.attacker->setPetsChaseTarget(entry);
#ifdef _DEBUG
    H::logger->debug("[走攻防计算公式]");
    Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[伤害法术]");
#endif
  }
  else
  {
    if (entry->notifyHMS)
    {
      entry->attackRTHpAndMp();
    }
    SceneEntryPk *pAtt = carrier.attacker->getTopMaster();
    if (pAtt&&pAtt->isEnemy(entry)&&carrier.status->range!=22)
    {
      SceneEntryPk * aMaster = pAtt->getTopMaster();
      SceneEntryPk * pMaster = entry->getTopMaster();
      if (aMaster->getType()==zSceneEntry::SceneEntry_Player)
      {
        SceneUser * a = (SceneUser *)aMaster;
        if (pMaster->getType()==zSceneEntry::SceneEntry_Player)
        {
          SceneUser * p = (SceneUser *)pMaster;
         // ScenePk::checkProtect(a,p);
        }
      }
    }
    //entry->processDeath(carrier.attacker);
#ifdef _DEBUG
    H::logger->debug("[不走攻防计算公式]");
    Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[非伤血性法术]");
#endif
  }
  entry->isPhysics = false;
  if (entry->reSendData) entry->changeAndRefreshHMS(true,sendData);
  return true;
}

/**
 * \brief 定时器刷新
 */
void SkillStatusManager::timer()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;
  bool dirty=false;
  bool sendData =false;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
  {
#ifdef _DEBUG
    H::logger->debug("[计时.伤]施加在身上的第[%u]号状态剩下时间[%u]",tIterator->second.id,tIterator->second.dwTime);
    Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[计时.伤]施加在身上的第[%u]号状态剩下时间[%u]",tIterator->second.id,tIterator->second.dwTime);
#endif
	if (tIterator->second.dwTime>0)
	{
		//sky 献祭和灵魂状态没有时间概念
		if(tIterator->second.dwSkillID != SKILLID_IMMOLATE && tIterator->second.dwSkillID != SKILLID_SOUL)
			tIterator->second.dwTime --;
	}
	else 
	{
		tIterator->second.dwTime = 0;
	}

    tIterator->second.byStep = ACTION_STEP_TIMER;
    runStatusElement(tIterator->second);

    if (0 == tIterator->second.dwTime)
    {
      tIterator->second.byStep = ACTION_STEP_STOP;
      runStatusElement(tIterator->second);
      if (tIterator->second.refresh) sendData = true;
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        //entry->showCurrentEffect(tIterator->second.state,false);
      }
#ifdef _DEBUG
    H::logger->debug("[伤害状态]施加在身上的第[%u]号状态被删除",tIterator->second.id);
    Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[伤害状态]施加在身上的第[%u]号状态被删除",tIterator->second.id);
#endif
      delIterator = tIterator;
      tIterator ++;
      _activeElement.erase(delIterator->first);
      dirty = true;
    }
    else
    {
      tIterator ++;
    }
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
  {
    QWORD curQtime = H::timeTick->getMilliTime();
    if (curQtime >= tIterator->second.qwTime)
    {
      tIterator->second.byStep = ACTION_STEP_STOP;
      runStatusElement(tIterator->second);
      if (tIterator->second.refresh) sendData = true;
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
#ifdef _DEBUG
      H::logger->debug("[临时被动]施加在身上的第[%u]号状态被删除",tIterator->second.id);
      Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[临时被动]施加在身上的第[%u]号状态被删除",tIterator->second.id);
#endif
      delIterator = tIterator;
      tIterator ++;
      _recoveryElement.erase(delIterator->first);
      dirty = true;
    }
    else
    {
      tIterator->second.dwTime = (tIterator->second.qwTime - curQtime)/1000;
      tIterator ++;
    }
  }
  if (entry->notifyHMS)
  {
    entry->attackRTHpAndMp();
  }
  if (dirty||entry->reSendData)
  {
    entry->changeAndRefreshHMS(false,sendData);
  }
  //std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;
  if (bclearActiveSkillStatus)
  {
    for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _activeElement.erase(delIterator->first);
  
    }

    for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _recoveryElement.erase(delIterator->first);
    }
    bclearActiveSkillStatus = false;
  }
}

/**
 * \brief 重新运行被动状态,包括永久被动和临时被动
 */
void SkillStatusManager::processPassiveness()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end() ; tIterator ++)
  {
    tIterator->second.byStep = ACTION_STEP_DOPASS;
    if (tIterator->second.percent<100) tIterator->second.percent=100;
    runStatusElement(tIterator->second);
  }

  for(tIterator = _passivenessElement.begin() ; tIterator !=_passivenessElement.end() ; tIterator ++)
  {
    tIterator->second.byStep = ACTION_STEP_DOPASS;
    if (tIterator->second.percent<100&&tIterator->second.id!=180) tIterator->second.percent=100;
    runStatusElement(tIterator->second);
  }
}

/**
 * \brief 执行一个具体的状态  [进入技能状态的实际处理]
 * \return 状态返回值
      SKILL_ACTIVE    //  加到活动MAP中
      SKILL_RECOVERY    //  加到临时被动MAP中
      SKILL_PASSIVENESS  //  加到永久被动MAP中
      SKILL_RETURN    //  返回不做任何操作
      SKILL_DONOW      //  立即执行属性值扣除动作
 */
BYTE SkillStatusManager::runStatusElement(SkillStatusElement &element)
{
  return  funlist[element.id>SKILLSTATENUMBER?0:element.id].func(entry,element);
}

/**
 * \brief  清除人物身上的不良的非永久状态
 */
void SkillStatusManager::clearBadActiveSkillStatus()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _activeElement.erase(delIterator->first);
    }
    else
    {
      tIterator ++;
    }
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _recoveryElement.erase(delIterator->first);
    }
    else
    {
      tIterator ++;
    }
  }
}

/**
 * \brief  清除人物身上的非永久性状态
 */
void SkillStatusManager::clearActiveSkillStatus()
{
  bclearActiveSkillStatus = true;
}

/**
 * \brief  清除人物身上的非永久性状态
 */
void SkillStatusManager::clearActiveSkillStatusOnlyUseToStatus48()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
  {
    tIterator->second.byStep = ACTION_STEP_CLEAR;
    runStatusElement(tIterator->second);
    if (tIterator->second.state >0)
    {
      //entry->clearEffectStatus(tIterator->second.state);
      entry->showCurrentEffect(tIterator->second.state,false);
    }
    delIterator = tIterator;
    tIterator ++;
    _activeElement.erase(delIterator->first);

  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
  {
    if (tIterator->second.id == 173)
    { 
      tIterator++;
      continue; //不好意思特殊处理一下
    }
    tIterator->second.byStep = ACTION_STEP_CLEAR;
    runStatusElement(tIterator->second);
    if (tIterator->second.state >0)
    {
      //entry->clearEffectStatus(tIterator->second.state);
      entry->showCurrentEffect(tIterator->second.state,false);
    }
    delIterator = tIterator;
    tIterator ++;
    _recoveryElement.erase(delIterator->first);
  }
  this->entry->changeAndRefreshHMS();
}


/**
 * \brief  清除指定技能ID的技能状态
 */
void SkillStatusManager::clearSkill(DWORD dwSkillID)
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; )
  {
    if (tIterator->second.dwSkillID == dwSkillID)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
	  tIterator->second.dwTime = 0;
	  tIterator ++;
      /*delIterator = tIterator;
      _activeElement.erase(delIterator->first);*/
    }
    else
    {
      tIterator++;
    }

  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end();)
  {
    if (tIterator->second.dwSkillID == dwSkillID)
    {
      tIterator->second.byStep = ACTION_STEP_CLEAR;
      runStatusElement(tIterator->second);
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      _recoveryElement.erase(delIterator->first);
    }
    else
    {
      tIterator++;
    }
  }
  this->entry->changeAndRefreshHMS();
}


/**
 * \brief 按被动技能来处理这个操作
 * \param skillid 技能id
 * \param pSkillStatus 技能中的操作
 */
void SkillStatusManager::putPassivenessOperationToMe(const DWORD skillid,const SkillStatus *pSkillStatus)
{
  std::vector<SkillElement>::const_iterator tIterator;

  for (tIterator = pSkillStatus->_StatusElementList.begin();
    tIterator != pSkillStatus->_StatusElementList.end();
    tIterator++)
  {
    SkillStatusElement element;
    element.id    =  tIterator->id;
    element.percent =  tIterator->percent;
    element.value  =  tIterator->value;
    element.state  =  tIterator->state;
    element.dwSkillID = skillid;
    element.dwTime = tIterator->time;
    _passivenessElement[element.id]=element;

#ifdef _DEBUG
      H::logger->debug("[永久被动]之[%u]号状态被施加在身上",element.id);
      Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[永久被动]之[%u]号状态被施加在身上",element.id);
#endif
  }
}

/**
 * \brief  增加不良状态的持续时间数值
 */
void SkillStatusManager::addBadSkillStatusPersistTime(const DWORD &value)
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; tIterator ++)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.dwTime += value;
    }
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end(); tIterator++)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.dwTime += value;
      tIterator->second.qwTime += value;
    }
  }
}

/**
 * \brief  增加不良状态的持续时间百分比
 */
void SkillStatusManager::addBadSkillStatusPersistTimePercent(const DWORD &value)
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;

  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end() ; tIterator ++)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.dwTime = (DWORD)(tIterator->second.dwTime*(value/100.0f));
    }
  }

  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end(); tIterator++)
  {
    if (tIterator->second.byGoodnessType == SKILL_BAD)
    {
      tIterator->second.dwTime = (DWORD)(tIterator->second.dwTime*(value/100.0f));
      tIterator->second.qwTime = (DWORD)(tIterator->second.qwTime*(value/100.0f));
    }
  }
}

/**
 * \brief  清除持续状态中的指定类别
 * \param byMutexType 技能大类
 * \param myMap 操作的状态map
 * \param dwID 过滤状态id
 */
void SkillStatusManager::clearMapElement(const BYTE &byMutexType,std::map<DWORD,SkillStatusElement> &myMap,DWORD dwID,bool notify)
{
/*  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = myMap.begin() ; tIterator !=myMap.end();)
  {
    if (tIterator->second.byMutexType == byMutexType)
    {
      if (tIterator->second.id != dwID)
      {
        tIterator->second.byStep = ACTION_STEP_CLEAR;
        runStatusElement(tIterator->second);
      }
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false);
      }
      delIterator = tIterator;
      tIterator ++;
      myMap.erase(delIterator->first);
    }
    else
    {
      tIterator ++;
    }
  }*/
  std::map<DWORD,SkillStatusElement>::iterator tIterator,delIterator;

  for(tIterator = myMap.begin() ; tIterator !=myMap.end();)
  {
    if (tIterator->second.id == byMutexType)
    {
      if (tIterator->second.id != dwID)
      {
        tIterator->second.byStep = ACTION_STEP_CLEAR;
        runStatusElement(tIterator->second);
      }
      if (tIterator->second.state >0)
      {
        //entry->clearEffectStatus(tIterator->second.state);
        entry->showCurrentEffect(tIterator->second.state,false,notify);
      }
      delIterator = tIterator;
      tIterator ++;
      myMap.erase(delIterator->first);
    }
    else
    {
      tIterator ++;
    }
  }

}

void SkillStatusManager::clearRecoveryElement(DWORD value)
{
  clearMapElement(value,_recoveryElement,0);
}

void SkillStatusManager::clearActiveElement(DWORD value)
{
  clearMapElement(value,_activeElement,0);
}

void SkillStatusManager::processDeath()
{
  if (entry->bombskillId >0)
  {
    Cmd::stAttackMagicUserCmd cmd;

    cmd.byAttackType = Cmd::ATTACKTYPE_U2P;
    cmd.dwDefenceTempID = 0;
    cmd.dwUserTempID = entry->tempid;
    cmd.wdMagicType = entry->bombskillId;
    cmd.byAction = Cmd::Ani_Num;
    cmd.byDirect = entry->getDir();
    cmd.xDes = (WORD)entry->getPos().x;
    cmd.yDes = (WORD)entry->getPos().y;

    zSkill *s = NULL;

    s = zSkill::createTempSkill(entry,entry->bombskillId,1);
    if (s)
    {
      s->action(&cmd,sizeof(cmd));
      SAFE_DELETE(s);
    }
  }

  clearActiveSkillStatus();
}


/**
 * \brief  测试函数用来显示技能状态当前值
 */
void SkillStatusManager::showValue()
{
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"角色身上的[SkillValue]属性列表:---------------------------");
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"伤害值增加固定数值1=%ld",entry->skillValue.dvalue);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"伤害值增加x%2=%ld",entry->skillValue.dvaluep);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"物理防御数值变更 57,86=%ld",entry->skillValue.pdefence);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"物理防御变更百分比=%ld",entry->skillValue.pdefencep);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"变为随机小动物79=%ld",entry->skillValue.topet);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"产生额外伤害83=%ld",entry->skillValue.appenddam);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"移动速度变更百分比 16,56=%ld",entry->skillValue.movespeed);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"减少技能施放间隔17=%ld",entry->skillValue.mgspeed);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"减少陷入冰冻状态几率18=%ld",entry->skillValue.coldp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"减少陷入中毒状态几率19=%ld",entry->skillValue.poisonp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"减少陷入石化状态几率20=%ld",entry->skillValue.petrifyp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"减少陷入失明状态几率21=%ld",entry->skillValue.blindp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"减少陷入混乱状态几率22=%ld",entry->skillValue.chaosp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"命中率增加33,64=%ld",entry->skillValue.atrating);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"命中率增加33,64=%ld",entry->skillValue.reduce_atrating);

  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"生命值恢复速度增加34=%ld",entry->skillValue.hpspeedup);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"法术值恢复速度增加35=%ld",entry->skillValue.mpspeedup);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"体力值恢复速度增加36=%ld",entry->skillValue.spspeedup);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"闪避率上升37=%ld",entry->skillValue.akdodge);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"反弹45=%ld",entry->skillValue.reflect);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"反弹x%46=%ld",entry->skillValue.reflectp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"为反弹百分之几的敌人伤害50=%ld",entry->skillValue.reflect2);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"法术防御变更59,=%ld",entry->skillValue.mdefence);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"法术防御变更百分比x%=%ld",entry->skillValue.mdefencep);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"攻击速度变更80,81=%ld",entry->skillValue.uattackspeed);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"降低陷入七大状态几率82=%ld",entry->skillValue.sevendownp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"伤害转移百分比=%ld",entry->skillValue.tsfdamp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"被动:额外伤害=%ld",entry->skillValue.passdam);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"角色身上的[PkValue]属性列表:---------------------------");
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"物理攻击力=%ld",entry->pkValue.pdamage);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"物理防御力=%ld",entry->pkValue.pdefence);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"法术攻击力=%ld",entry->pkValue.mdamage);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"法术防御力=%ld",entry->pkValue.mdefence);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"消耗法术值=%ld",entry->pkValue.mcost);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"消耗生命值=%ld",entry->pkValue.hpcost);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"消耗体力值=%ld",entry->pkValue.spcost);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"经验消耗=%ld",entry->pkValue.exp);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"伤害值=%ld",entry->pkValue.dvalue);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"伤害值增加百分比=%ld",entry->pkValue.dvaluep);
  //Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"列表结束:----------------------------------------------");
}

/**
 * \brief  打印技能状态当前值到log文件中
 */
void SkillStatusManager::showValueToLog()
{
  //Zebra::logger->debug("角色身上的[SkillValue]属性列表:---------------------------");
  //Zebra::logger->debug("伤害值增加固定数值1=%ld",entry->skillValue.dvalue);
  //Zebra::logger->debug("伤害值增加x%2=%ld",entry->skillValue.dvaluep);
  //Zebra::logger->debug("物理防御数值变更 57,86=%ld",entry->skillValue.pdefence);
  //Zebra::logger->debug("物理防御变更百分比=%ld",entry->skillValue.pdefencep);
  //Zebra::logger->debug("变为随机小动物79=%ld",entry->skillValue.topet);
  //Zebra::logger->debug("产生额外伤害83=%ld",entry->skillValue.appenddam);
  //Zebra::logger->debug("移动速度变更百分比 16,56=%ld",entry->skillValue.movespeed);
  //Zebra::logger->debug("减少技能施放间隔17=%ld",entry->skillValue.mgspeed);
  //Zebra::logger->debug("减少陷入冰冻状态几率18=%ld",entry->skillValue.coldp);
  //Zebra::logger->debug("减少陷入中毒状态几率19=%ld",entry->skillValue.poisonp);
  //Zebra::logger->debug("减少陷入石化状态几率20=%ld",entry->skillValue.petrifyp);
  //Zebra::logger->debug("减少陷入失明状态几率21=%ld",entry->skillValue.blindp);
  //Zebra::logger->debug("减少陷入混乱状态几率22=%ld",entry->skillValue.chaosp);
  //Zebra::logger->debug("命中率增加33,64=%ld",entry->skillValue.atrating);
  //Zebra::logger->debug("生命值恢复速度增加34=%ld",entry->skillValue.hpspeedup);
  //Zebra::logger->debug("法术值恢复速度增加35=%ld",entry->skillValue.mpspeedup);
  //Zebra::logger->debug("体力值恢复速度增加36=%ld",entry->skillValue.spspeedup);
  //Zebra::logger->debug("闪避率上升37=%ld",entry->skillValue.akdodge);
  //Zebra::logger->debug("反弹45=%ld",entry->skillValue.reflect);
  //Zebra::logger->debug("反弹x%46=%ld",entry->skillValue.reflectp);
  //Zebra::logger->debug("为反弹百分之几的敌人伤害50=%ld",entry->skillValue.reflect2);
  //Zebra::logger->debug("法术防御变更59,=%ld",entry->skillValue.mdefence);
  //Zebra::logger->debug("法术防御变更百分比x%=%ld",entry->skillValue.mdefencep);
  //Zebra::logger->debug("攻击速度变更80,81=%ld",entry->skillValue.uattackspeed);
  //Zebra::logger->debug("降低陷入七大状态几率82=%ld",entry->skillValue.sevendownp);
  //Zebra::logger->debug("伤害转移百分比=%ld",entry->skillValue.tsfdamp);
  //Zebra::logger->debug("被动:额外伤害=%ld",entry->skillValue.passdam);
  //Zebra::logger->debug("角色身上的[PkValue]属性列表:---------------------------");
  //Zebra::logger->debug("物理攻击力=%ld",entry->pkValue.pdamage);
  //Zebra::logger->debug("物理防御力=%ld",entry->pkValue.pdefence);
  //Zebra::logger->debug("法术攻击力=%ld",entry->pkValue.mdamage);
  //Zebra::logger->debug("法术防御力=%ld",entry->pkValue.mdefence);
  //Zebra::logger->debug("消耗法术值=%ld",entry->pkValue.mcost);
  //Zebra::logger->debug("消耗生命值=%ld",entry->pkValue.hpcost);
  //Zebra::logger->debug("消耗体力值=%ld",entry->pkValue.spcost);
  //Zebra::logger->debug("经验消耗=%ld",entry->pkValue.exp);
  //Zebra::logger->debug("伤害值=%ld",entry->pkValue.dvalue);
  //Zebra::logger->debug("伤害值增加百分比=%ld",entry->pkValue.dvaluep);
  //Zebra::logger->debug("列表结束:----------------------------------------------");
}

/**
 * \brief  显示角色身上的主动技能状态
 */
void SkillStatusManager::showActive()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  SkillStatusElement *element;

  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"角色身上的主动状态列表:");
  for(tIterator = _activeElement.begin() ; tIterator !=_activeElement.end(); tIterator++)
  {
    std::string myname;
    char buf [45];
    element = &tIterator->second;
    SceneUser *pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(element->dwTempID);
    if (pUser)
      myname = pUser->name;
    else
    {
      sprintf(buf,"临时ID:%u",element->dwTempID);
      myname = buf;
    }
    Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"技能:%u 大类:%u 状态类别:%u %s 剩余时间:%u 攻击者:%s 几率:%u 总时间:%u 状态值%u 特效值:%u",element->dwSkillID,element->byMutexType,element->id,element->byGoodnessType==1?"伤害":"和平",element->dwTime,myname.c_str(),element->percent,element->dwTime,element->value,element->state);
  }
  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"----------------------------------------------");
}

/**
 * \brief  显示角色身上的临时被动技能状态
 */
void SkillStatusManager::showRecovery()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  SkillStatusElement *element;

  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"角色身上的临时被动状态列表:");
  for(tIterator = _recoveryElement.begin() ; tIterator !=_recoveryElement.end(); tIterator++)
  {
    std::string myname;
    char buf [45];
    element = &tIterator->second;
    SceneUser *pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(element->dwTempID);
    if (pUser)
      myname = pUser->name;
    else
    {
      sprintf(buf,"临时ID:%u",element->dwTempID);
      myname = buf;
    }
    Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"技能:%u 大类:%u 状态类别:%u %s 剩余时间:%u 攻击者:%s 几率:%u 总时间:%u 状态值%u 特效值:%u",element->dwSkillID,element->byMutexType,element->id,element->byGoodnessType==1?"伤害":"和平",element->dwTime,myname.c_str(),element->percent,element->dwTime,element->value,element->state);
  }
  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"----------------------------------------------");
}

/**
 * \brief  显示角色身上的永久被动技能状态
 */
void SkillStatusManager::showPassiveness()
{
  std::map<DWORD,SkillStatusElement>::iterator tIterator;
  SkillStatusElement *element;

  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"角色身上的永久被动状态列表:");
  for(tIterator = _passivenessElement.begin() ; tIterator !=_passivenessElement.end(); tIterator++)
  {
    std::string myname;
    char buf [45];
    element = &tIterator->second;
    SceneUser *pUser = GameService::getMe().getSceneUserMgr().getUserBySessID(element->dwTempID);
    if (pUser)
      myname = pUser->name;
    else
    {
      sprintf(buf,"临时ID:%u",element->dwTempID);
      myname = buf;
    }
    Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"技能:%u 大类:%u 状态类别:%u %s 剩余时间:%u 攻击者:%s 几率:%u 总时间:%u 状态值%u 特效值:%u",element->dwSkillID,element->byMutexType,element->id,element->byGoodnessType==1?"伤害":"和平",element->dwTime,myname.c_str(),element->percent,element->dwTime,element->value,element->state);
  }
  Channel::sendSys((SceneUser *)entry,Cmd::INFO_TYPE_SYS,"----------------------------------------------");
}

/**
 * \brief  获得当前角色所携带的技能状态数目
 */
WORD SkillStatusManager::getSaveStatusSize()
{
  WORD ret =0;

  ret = _recoveryElement.size()+_activeElement.size();
  return ret; 
}

/**
* \brief sky 系统为用户设置一个状态到临时被动状态管理器里
*/
void SkillStatusManager::SetStatuToRecovery(DWORD id, DWORD time, DWORD percent, DWORD value, DWORD state)
{
	SkillStatusElement element;
	element.byStep  =  ACTION_STEP_START;
	element.id    =  id;
	element.percent =  percent;
	element.value  =  value;
	element.state  =  state;

	element.dwSkillID = 0;
	element.dwTime = time;
	element.qwTime = H::timeTick->getMilliTime()+element.dwTime *1000;
	

	switch(runStatusElement(element))
	{
	case SKILL_RECOVERY:
		{
#ifdef _DEBUG
			H::logger->debug("[临时被动]第[%u]号状态被施加在身上持续时间为[%u]",element.id,element.dwTime);
			Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[临时被动]第[%u]号状态被施加在身上持续时间为[%u]",element.id,element.dwTime);
#endif
			element.qwTime = H::timeTick->getMilliTime()+element.dwTime *1000;
			if (element.state >0)
			{
				clearMapElement(element.id/*element.byMutexType*/,_recoveryElement,element.id,false);
				_recoveryElement[element.id/*element.byMutexType*/]=element;
				sendSelectStates(entry,element.state,element.value,element.dwTime);
				//entry->setEffectStatus(element.state);
				entry->showCurrentEffect(element.state,true);
			}
			else
			{
				clearMapElement(element.id/*element.byMutexType*/,_recoveryElement,element.id);
				_recoveryElement[element.id/*element.byMutexType*/]=element;
			}
		}
		break;
	case SKILL_BREAK:
		{
			return;
		}
		break;
	case SKILL_ACTIVE:
		{
#ifdef _DEBUG
			H::logger->debug("[伤害状态]第[%u]号状态被施加在身上持续时间为[%u]",element.id,element.dwTime);
			Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[攻击状态]第[%u]号状态被施加在身上持续时间为[%u]",element.id,element.dwTime);
#endif
			if (element.dwTime==0) break;
			clearMapElement(element.id/*element.byMutexType*/,_activeElement,element.id);
			_activeElement[element.id/*element.byMutexType*/]=element;
			if (element.state >0)
			{
				sendSelectStates(entry,element.state,element.value,element.dwTime);
				//entry->setEffectStatus(element.state);
				//entry->showCurrentEffect(element.state,true);
			}
		}
		break;
	case SKILL_RETURN:
	default:
		break;
	}

	Channel::sendSys(entry->tempid,Cmd::INFO_TYPE_SYS,"[免疫类状态]之[%u]号状态被施加在身上",element.id);
}
