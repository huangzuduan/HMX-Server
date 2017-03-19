#ifndef __ENTITY_H_
#define __ENTITY_H_

#include <bitset>
#include <assert.h>

#include "UnorderedSet.h"
#include "SceneChannel.h"
#include "SrvEngine.h"
#include "ScenesServer.h"

class SceneRegion;
class Scene;

/*------------------------------------------------------------------
 *
 * @Brief : 实体父类，指在地图上可存在的实体，如NPC，Buff,玩家，怪物等
 *			它们都会有实际的位置，同时也会在场景中出现，所以需要继承场景
 *			频道注册接口，需要实现位置频道接口
 * @Author: hzd 
 * @File  : Entity.h
 * @Date  : 2015/09/19 00:16
 * @Copyright (c) 2015,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
class SceneEntryPk : public zSceneEntry 
{
public:
	SceneEntryPk(const SceneEntryType entrytype);
	virtual ~SceneEntryPk() {}

	virtual int32 getLevel() { return 0;}
	virtual int32 getHp(){ return 0;}
	virtual int32 getHpMax(){ return 0;}
	virtual int32 getMp(){return 0;}
	virtual int32 getMpMax(){return 0;}

	inline const zPos &getPos() const { return pos; }
	void setPos(const zPos& zPos) { pos = zPos; }

public:

	Scene*	scene; 
	PkValue pkVal;/* pk属性 */

	///脱离战斗状态的时间 
//	zRTime endBattleTime;
	///施法者 
	DWORD curMagicManID;
	///对施法者类型  
	DWORD curMagicManType;
	///对手 
	DWORD curTargetID;
	///对手类型 
	DWORD curTargetType;

	bool attackAction;  /// 攻击许可
	bool moveAction;  /// 移动许可
	bool skillAction;   /// 技能攻击许可
	bool ignoreDam;    /// 忽略伤害
	bool ignorePhysicDam; /// 忽略物理伤害
	bool ignoreMagicDam; /// 忽略魔法伤害
	bool notifyHMS;    /// 通知HP,MP,SP改变
	bool maxattack;    /// 攻击取上限
	bool mdeftozero;   /// 魔法防御变成0
	bool pdeftozero;   /// 魔法防御变成0
	bool useRes;    /// 可否使用物品
	bool isAutoRestitute; // 是否自动恢复
	bool frenzy;       /// 狂暴状态
	bool huntermark;  /// 猎手标记
	bool isPhysics;    /// 计算公式走物理   
	bool dropweapon;   /// 缴械
	bool tosh;        /// 胡言乱语
	bool stone;      /// 石化
	bool watchTrap;    /// 观察陷阱
	bool mhpd;  /// 魔法伤害减半,物理伤害加倍标志。
	bool blazeflag; ///火焰系法术加成标志
	bool levinflag;  ///雷电系法术加成标志
	bool trapflag;  ///陷阱系法术加成标志
	bool iceflag;  ///冰系法术加成标志
	DWORD swapdamcharid; ///献身施法者的临时ID
	DWORD swapdamcharid2; ///关爱施法者的临时ID
	bool changeface;  ///易容术,可以访问国外NPC
	bool hideme;     /// 隐藏自己
	bool icebox;   /// 冰灵柜状态
	bool liquidState; ///液态（无阻挡）
	BYTE resist;     ///格档,有一次抵御伤害的机会
	BYTE dmpbyhp;  ///吸魔剑法
	BYTE mdmtomp;  ///将法术伤害转成魔法值百分比
	BYTE mdmtompper; ///将法术伤害转成魔法值百分比几率
	SDWORD icedam;  ///冰冻结界吸收的伤害数值
	QWORD unitaryBattleKeepTime; //一元阵法持续时间
	SDWORD dietodam; ///死亡攻击数值
	bool attacklow; ///攻击力取下限
	BYTE killnow; //一击必杀
	BYTE diewithme; //血债血偿
	BYTE switchdie; //同屏转移死亡状态的几率
	BYTE summonsplit; //焰魔君主死亡后分裂标志


	bool reSendData;  /// 重新发送NPC或角色数据给自己
	bool reSendOther;  /// 重新发送NPC或角色数据给其它人

	bool mplock;  ///对mp进行锁定
	bool hplock;  ///对hp进行锁定
	bool splock;  ///对sp进行锁定

	bool afreetMode; /// 恶魔杀无赦（砍人必死）
	bool angelMode;  /// 天使无敌（优于恶魔,砍不死）

	bool isPhysicBang; /// 是否物理暴击
	bool isMagicBang; /// 是否魔法暴击
	bool isHPhysicBang; /// 是否物理暴击
	bool isHMagicBang; /// 是否魔法暴击

	bool assault; ///冲锋

				  //sky 新增角色战斗状态 begin
	bool Daggerflag;	//sky 匕首增加伤害标志
	bool Throflag;		//sky 投掷武器增加伤害标志
	bool Handsflag;		//sky 双手武器增加伤害标志
	bool Handflag;		//sky 单手武器增加伤害标志
	bool Flameflag;		//sky 火焰魔法增加伤害标志
	bool Iceflag;		//sky 冰霜魔法增加伤害标志
	bool Sacredflag;	//sky 神圣魔法增加伤害标志
	bool Darkflag;		//sky 黑暗魔法增加伤害标志
	bool Immolate;		//sky 献祭标志

	bool dread;			/// sky 恐惧
	bool blind;			/// sky 失明状态
	bool frozen;		/// sky 冰冻
	bool repentange;	/// sky 忏悔
	bool Silence;		/// sky 沉默
	bool Coma;			///	sky 昏迷
	bool Exile;			/// sky 放逐

	bool ImmuneDread;	/// sky 免疫恐惧状态
	bool ImmuneFrozen;	/// sky 免疫冰冻状态
	bool ImmuneSilence;	/// sky 免疫沉默状态
	bool ImmuneComa;	/// sky 免疫昏迷状态
	bool ImmuneExile;	/// sky 免疫放逐状态
						
	bool Soulflag;

	DWORD BattCampID;
	//sky end

	zPos keepPos;  /// 保存技能的攻击目标点,传递给需要使用的功能
	BYTE keepDir;  /// 保存技能的攻击方向,传递给需要使用的功能
	BYTE  lastPkTime; //最后PK标志
	DWORD bombskillId; /// 人物死亡后投送技能ID

	BYTE damtohpper;  /// 角色的伤害转化成生命值的几率;
	BYTE damtohpvalper; /// 角色的伤害转化成生命值的百分比

	SkillStatusManager skillStatusM;  /// 技能状态管理器
	SkillStatusCarrier carrier;      /// 技能操作投送器
	std::map<BYTE, BYTE>  _effectState;  /// 技能状态特效计数器
	SceneEntryPk *attackTarget;      /// 武器附带攻击状态攻击目标


	/**
	* \brief 造成直接伤害
	* \param pAtt 攻击者
	* \param dam 伤害
	* \param notify 是否通知客户端
	* \return 伤害值
	*/
	virtual SWORD directDamage(SceneEntryPk *pAtt, const SDWORD &dam, bool notify = false);

	/**
	* \brief 改变角色的hp
	* \param hp 变更的HP
	*/
	virtual void changeHP(const SDWORD &hp) = 0;

	/**
	* \brief 改变角色的sp
	* \param sp 变更的SP
	*/
	virtual void changeSP(const SDWORD &sp) = 0;

	/**
	* \brief 改变角色的mp
	* \param mp 变更的MP
	*/
	virtual void changeMP(const SDWORD &mp) = 0;

	/**
	* \brief 获得最大的hp
	* \return 返回最大值
	*/
	virtual DWORD getMaxHP() { return 0; }

	/**
	* \brief 获得最大的hp
	* \return 返回最大值
	*/
	virtual DWORD getBaseMaxHP() { return 0; }

	/**
	* \brief 获得最大的mp
	* \return 返回最大值
	*/
	virtual DWORD getMaxMP() { return 0; }

	/**
	* \brief 获得最大的mp
	* \return 返回最大值
	*/
	virtual DWORD getBaseMaxMP() { return 0; }

	/**
	* \brief 获得最大的sp
	* \return 返回最大值
	*/
	virtual DWORD getMaxSP() { return 0; }

	/**
	* \brief 获得当前魔法攻击力
	* \return 魔法攻击力
	*/
	virtual DWORD getMaxMDamage() { return 0; }

	/**
	* \brief 获得当前物理攻击力
	* \return 物理攻击力
	*/
	virtual DWORD getMaxPDamage() { return 0; }

	/**
	* \brief 获得当前物理防御力
	* \return 物理防御力
	*/
	virtual DWORD getPDefence() { return 0; }

	/**
	* \brief 获得当前魔法防御力
	* \return 魔法防御力
	*/
	virtual DWORD getMDefence() { return 0; }

	/**
	* \brief 重置最大的hp
	*/
	virtual void changeAndRefreshHMS(bool lock = true, bool sendData = true) {}

	/**
	* \brief 在被自己攻击之前的处理,包括,装备损耗处理,攻击有效几率判断等
	* \param pUser 攻击者
	* \param rev 本次攻击的触发指令
	* \param physics 是否物理攻击
	* \param good 为true则必中,false要判断回避率
	* \return true为这次攻击是有效的,false为一次无效的攻击
	*/
	virtual bool preAttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics = true, const bool good = false) = 0;

	/**
	* \brief 角色被攻击
	* \param pUser 攻击者
	* \param rev 本次攻击的触发消息
	* \param physics 是否物理攻击
	* \return true为这次攻击是有效的,false为一次无效的攻击
	*/
	virtual bool AttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics = true, SWORD rangDamageBonus = 0);
	/**
	* \brief 判断是否是敌人
	* \return true 是 false 不是
	*/
	virtual int isEnemy(SceneEntryPk *entry, bool notify = false, bool good = false) = 0;

	/**
	* \brief 判断是否可攻击
	* \return true 是 false 不是
	*/
	virtual bool isBugbear() { return true; }

	/**
	* \brief 获取自己的主人,一般针对NPC而言,Player的主人是自己
	* \return NULL或者主人的对象指针
	*/
	virtual SceneEntryPk *getMaster() = 0;

	/**
	* \brief 得到最上层的主人
	*
	* \return 主人
	*/
	virtual SceneEntryPk *getTopMaster() = 0;

	/**
	* \brief 让角色死亡
	* \param dwTempID 攻击者的临时ID
	*/
	virtual void toDie(const DWORD &dwTempID) = 0;

	/**
	* \brief 在屏幕内随机移动
	*/
	virtual void goToRandomScreen() {};

	/**
	* \brief 在屏幕内定点移动
	*/
	virtual void jumpTo(zPos &newPos) {};

	/**
	* \brief 通知客户端生命值的变化
	*/
	virtual void attackRTHpAndMp() {};

	/**
	* \brief 判断角色是否死亡
	*/
	virtual bool isDie() = 0;

	/**
	* \brief 获取角色的级别
	*/
	virtual DWORD getLevel() const = 0;

	/**
	* \brief 获取五行点数
	* \return 返回该类型的五行点数
	*/
	virtual DWORD getFiveType() { return 0; }

	/**
	* \brief 需要的职业类型,决定可以使用的技能类型
	*/
	virtual bool needType(const DWORD &needtype) = 0;

	/**
	* \brief 需要的职业类型,决定可以使用的技能类型
	*/
	virtual bool addSkillToMe(zSkill *skill) = 0;

	/**
	* \brief 是否有该技能需要的武器
	* \return true 有 false 没有
	*/
	virtual bool needWeapon(DWORD skillid) = 0;

	/**
	* \brief 是否Pk区域
	* \param other PK相关人
	* \return true 是 false 否
	*/
	virtual bool isPkZone(SceneEntryPk *other = NULL) = 0;

	/**
	* \brief 依赖物品消耗型法术
	* \param object 消耗物品的类型
	* \param num 消耗物品的数量
	* \return true 消耗成功 false 失败
	*/
	virtual bool reduce(const DWORD &object, const BYTE num) = 0;

	/**
	* \brief 检查可消耗物品是否足够
	* \param object 消耗物品的类型
	* \param num 消耗物品的数量
	* \return true 足够 false 不够
	*/
	virtual bool checkReduce(const DWORD &object, const BYTE num) = 0;
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
	virtual bool doSkillCost(const zSkillB *base) = 0;

	virtual void showCurrentEffect(const WORD &state, bool isShow, bool notify = true) = 0;

};

#endif


