#ifndef __CHARACTER_H_
#define __CHARACTER_H_

#include "Includes.h"

#include "SceneNpc.h"

#include "MyCounters.h"
#include "SrvEngine.h"
#include "character.pb.h"
#include "itemslots.pb.h"
#include "chatmsg.pb.h"

#include "ConfigBase.h" 
#include "Object.h"
#include "ObjectManager.h"
#include "Relation.h"


/*
 *	Detail: 角色类  
 *  Created by hzd 2014-12-17
 */
class SceneUser : public SceneEntryPk
{
public:
	SceneUser();
	~SceneUser();

	bool loadDB(const S::SSRtLoadUser* packet, int32 nSize);
	bool saveDB();
	void readBinary(const char* data,int32 len);
	int32 writeBinary(char* data);

	bool serialize(::protobuf::CounterProto& proto);
	void unserialize(const ::protobuf::CounterProto& proto);
	//bool serialize(::protobuf::RelationProto& proto);
	//void unserialize(const ::protobuf::RelationProto& proto);

public:

	int64 sessid;				/* payersessid*/
	int32 fepsid;				/* Fep会话 */
	bool initDataFinish;		/* 是否装载完数据 */
	bool clientReady;			/* 前端状态 0 ok,1 加载资源中 */ 
	bool userModity;			/* 是否数据变动(0无,1有) */

	S::t_UserSceneBase userbase;		/* 角色属性数据 */

public:

	bool move(Cmd::stUserMoveMoveUserCmd *rev);
	void online(); 
	
	// 由场景调用,可以根据不同的场景,改善调用的频率
	// 通宵要是200ms以内调用一次
	void Timer(const zTaskTimer* t);

public:

	/* 进入场景需要发送数据 */ 
	void sendMainToMe();

	// 重新计算PK属性
	void setupCharBase(); 

	int64 getUid()
	{ 
		return id;
	}

	int32 getType()
	{
		return 0;
	}

	int32 getLandMapID() const
	{
		return 0;
	}

	int32 getInstanceMapID() const
	{
		return 0;
	}

	int32 getCurrMapID() const
	{
		if (getInstanceMapID())
		{
			return getInstanceMapID();
		}
		else
		{
			return getLandMapID();
		}
	}

	int32 getSceneID() const
	{
		return 0;
	}

	int32 getZoneID() const
	{
		return 0;
	}

	int32 getTeamID() const 
	{
		return 0;
	}

	void sendCmdToMe(NetMsgSS* pMsg, int32 nSize);
	void sendToFep(NetMsgSS* pMsg, int32 nSize);
	void sendToDp(NetMsgSS* pMsg, int32 nSize);
	void sendToWs(NetMsgSS* pMsg, int32 nSize);
	
//-------------------------------属性更改回调函数------------------------------------------
private:

	void OnExpChange(const ValueType& vOldValue, const ValueType& vNewValue);
	void OnMapIDChange(const ValueType& vOldValue, const ValueType& vNewValue);
	void OnClothesChange(const ValueType& vOldValue, const ValueType& vNewValue);
	void OnWeaponChange(const ValueType& vOldValue, const ValueType& vNewValue);
	void OnMoneyChange(const ValueType& vOldValue, const ValueType& vNewValue);

public:

	bool CheckMoneyEnough(int32 type,int32 num);
	bool TrySubMoney(int32 type, int32 num);
	bool SubMoney(int32 type, int32 num, bool notify = true, bool isTry = false);

//----------------------------------控制器管理------------------------------------------
public:

	/* 计数器(支持每时每日每周每月等清零处理) id=>值 <开始时间,结束时间> */ 
	MyCounters ucm; 

	/* 技能管理器 */
	UserSkillM usm;

	/* 物品管理器 */
	ObjectManager objM;

	/* 背包模块功能 */  
public:

	void getAllItemSlots(std::vector<qObject*>& slots);

	bool TryAddObject(int32 itemID, int32 itemNum);
	bool AddObject(int32 itemID, int32 itemNum,bool notify = true,bool isTry = false);

	bool TryUseObject(int32 uniqueID,int32 num);
	bool UseObject(int32 uniqueID, int32 num, bool notify = true, bool isTry = false);


private:

	bool UseObject(qObject* obj, int32 num, bool notify = true, bool isTry = false);
	bool UseItemObj(qObject* obj, int32 num, bool notify = true, bool isTry = false);
	bool UseEquip(qObject* obj, int32 num, bool notify = true, bool isTry = false);
	bool UseQuest(qObject* obj, int32 num, bool notify = true, bool isTry = false);
	bool UsePking(qObject* obj, int32 num, bool notify = true, bool isTry = false);
	bool ExecEffectMoney(const zItemB::Effect& effect, int32 num);
	
public:

	/**
	* \brief 改变角色的hp
	* \param hp 变更的HP
	*/
	virtual void changeHP(const SDWORD &hp);

	/**
	* \brief 改变角色的sp
	* \param sp 变更的SP
	*/
	virtual void changeSP(const SDWORD &sp);

	/**
	* \brief 改变角色的mp
	* \param mp 变更的MP
	*/
	virtual void changeMP(const SDWORD &mp);

	/**
	* \brief 判断是否是敌人
	* \return true 是 false 不是
	*/
	virtual int isEnemy(SceneEntryPk *entry, bool notify = false, bool good = false);

	/**
	* \brief 获取自己的主人,一般针对NPC而言,Player的主人是自己
	* \return NULL或者主人的对象指针
	*/
	virtual SceneEntryPk *getMaster();

	/**
	* \brief 得到最上层的主人
	*
	* \return 主人
	*/
	virtual SceneEntryPk *getTopMaster();

	/**
	* \brief 判断角色是否死亡
	*/
	virtual bool isDie();

	/**
	* \brief 获取角色的级别
	*/
	virtual DWORD getLevel() const;

	int32 getVip() const
	{
		return 0;
	}

	int32 getCountry() const
	{
		return 0;
	}

	/**
	* \brief 获取五行点数
	* \return 返回该类型的五行点数
	*/
	virtual DWORD getFiveType() { return 0; }

	/**
	* \brief 需要的职业类型,决定可以使用的技能类型
	*/
	virtual bool needType(const DWORD &needtype);

	/**
	* \brief 需要的职业类型,决定可以使用的技能类型
	*/
	virtual bool addSkillToMe(zSkill *skill);

	/**
	* \brief 是否有该技能需要的武器
	* \return true 有 false 没有
	*/
	virtual bool needWeapon(DWORD skillid);

	/**
	* \brief 是否Pk区域
	* \param other PK相关人
	* \return true 是 false 否
	*/
	virtual bool isPkZone(SceneEntryPk *other = NULL);

	/**
	* \brief 依赖物品消耗型法术
	* \param object 消耗物品的类型
	* \param num 消耗物品的数量
	* \return true 消耗成功 false 失败
	*/
	virtual bool reduce(const DWORD &object, const BYTE num);

	/**
	* \brief 检查可消耗物品是否足够
	* \param object 消耗物品的类型
	* \param num 消耗物品的数量
	* \return true 足够 false 不够
	*/
	virtual bool checkReduce(const DWORD &object, const BYTE num);
	/**
	* \brief 获取装备伤害加成
	* \return 伤害加成
	*/
	virtual WORD getDamageBonus() { return 0; }

	/**
	* \brief 施放技能所导致的消耗MP,HP,SP
	* \param base 技能基本属性对象
	* \return true 消耗成功 false 失败
	*/
	virtual bool doSkillCost(const zSkillB *base);

	virtual void showCurrentEffect(const WORD &state, bool isShow, bool notify = true);

	virtual bool preAttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics = true, const bool good = false);

	/**
	* \brief 让角色死亡
	* \param dwTempID 攻击者的临时ID
	*/
	virtual void toDie(const DWORD &dwTempID);

	virtual SWORD directDamage(SceneEntryPk *pAtt, const SDWORD &dam, bool notify = false);


public:
	
	RelationM relM;


};

#endif



