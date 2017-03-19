#include "ScenesServer.h"



bool UserSkillM::getUniqeID(QWORD &tempid)
{
	return true;
}

void UserSkillM::putUniqeID(const QWORD &tempid)
{
}

UserSkillM::UserSkillM(SceneUser* u):pOwner(u)
{

}


UserSkillM::~UserSkillM()
{
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    zSkill *skill = (zSkill *)it->second;
    SAFE_DELETE(skill);
  }
}


zSkill *UserSkillM::getSkillByTempID(DWORD id)
{
  return (zSkill *)getEntryByTempID(id);
}


void UserSkillM::removeSkillByTempID(DWORD id)
{
  zEntry *e=getEntryByTempID(id);
  if (e)
    removeEntry(e);
}


void UserSkillM::removeSkill(zSkill *s)
{
  removeEntry(s);
}


bool UserSkillM::addSkill(zSkill *s)
{
  bool bret = false;
  if (s)
  {
    zSkill *ret = (zSkill *)getEntryByTempID(s->id);
    if (ret)
    {
      H::logger->debug("技能ID重复(%ld)",s->id);
    }

    bret = addEntry((zSkill *)s);
    if (!bret)
    {
      H::logger->fatal("添加技能表失败");
    }
  }

  return bret;
}


zSkill *UserSkillM::findSkill(DWORD skillid)
{
  //zSkill *s;
  //for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  //{
  //  s = (zSkill *)it->second;
  //  if (s->data.skillid == skillid)
  //  {
  //    return (zSkill *)it->second;
  //  }
  //}
  //return NULL;
  return (zSkill *)getEntryByTempID(skillid);
}


DWORD UserSkillM::getPointInTree(DWORD mySubkind)
{
  zSkill *s;
  DWORD num=0;
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    s = (zSkill *)it->second;

	////sky 判断技能的树系是否和要学的技能的树系一致
 //   if ((s->base->subkind == mySubkind)) 
	//	num+=s->base->level;  //sky 是的就把该系的点数加1
  }

  return num;
}


void UserSkillM::execEvery(UserSkillExec &exec)
{
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    if (!exec.exec((zSkill *)it->second))
      return;
  }
}

/**
 * \brief  重设该用户所有的技能冷却时间
 */
void UserSkillM::resetAllUseTime()
{
  zSkill *s;
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    s = (zSkill *)it->second;
    s->resetUseTime();
	s->refresh(true);
  }
}

/**
 * \brief  清除该用户所有的技能冷却时间
 * \skillID 不在清除之列的技能ID
 */
void UserSkillM::clearAllUseTime(DWORD skillID)
{
  zSkill *s;
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {

	  s = (zSkill *)it->second;
	  if(s && s->base->id != skillID)
	  {
		  s->clearUseTime();
		  s->refresh(true);
	  }
  }
}

/**
 * \brief  刷新技能(武器提升技能等级。。。。。)
 */
void UserSkillM::refresh()
{
  zSkill *s;
  for(zEntryTempID::hashmap::iterator it=zEntryTempID::ets.begin();it!=zEntryTempID::ets.end();it++)
  {
    s = (zSkill *)it->second;
    s->refresh();
  }
}

void UserSkillM::clear()
{
	zEntryMgr::clear();
}

int UserSkillM::size() const
{
  return zEntryMgr::size();
}

/**
 * \brief  根据技能id查找对应的技能对象并删除
  * \return 技能对象
 */
void UserSkillM::clearskill(DWORD skillid)
{
	zEntryMgr::removeEntry(getEntryByTempID(skillid));
}
