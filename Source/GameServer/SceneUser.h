#ifndef __CHARACTER_H_
#define __CHARACTER_H_

#include "SrvEngine.h"
#include "SceneEntryPk.h"
#include "base/hmx_data.pb.h"

/*
 *	Detail: 角色类  
 *  Created by hzd 2014-12-17
 */
class SceneUser : public SceneEntryPk
{
public:
	SceneUser(const ::data::UserInfo& proto);
	~SceneUser();

	inline uint64_t GetUID() const { return dataProto.id(); }
	inline uint64_t GetSessionID() const { return nSessionID; }
	inline uint64_t GetFepSessID() const { return nFepSessionID; }

private:

	int64_t nSessionID;			/* payersessid*/
	int32_t nFepSessionID;		/* Fep会话 */
	bool initDataFinish;		/* 是否装载完数据 */
	bool clientReady;			/* 前端状态 0 ok,1 加载资源中 */ 
	bool userModity;			/* 是否数据变动(0无,1有) */

	//S::t_UserSceneBase userbase;		/* 角色属性数据 */

	::data::UserInfo dataProto;

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

	void sendCmdToMe(NetMsgSS* pMsg, int32_t nSize);
	void sendToFep(NetMsgSS* pMsg, int32_t nSize);
	void sendToDp(NetMsgSS* pMsg, int32_t nSize);
	void sendToWs(NetMsgSS* pMsg, int32_t nSize);

public:

	bool CheckMoneyEnough(int32_t type,int32_t num);
	bool TrySubMoney(int32_t type, int32_t num);
	bool SubMoney(int32_t type, int32_t num, bool notify = true, bool isTry = false);
	
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

	int32_t getVip() const
	{
		return 0;
	}

	int32_t getCountry() const
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

	virtual void showCurrentEffect(const WORD &state, bool isShow, bool notify = true);

	virtual bool preAttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics = true, const bool good = false);

	/**
	* \brief 让角色死亡
	* \param dwTempID 攻击者的临时ID
	*/
	virtual void toDie(const DWORD &dwTempID);

	virtual SWORD directDamage(SceneEntryPk *pAtt, const SDWORD &dam, bool notify = false);



};

#endif



