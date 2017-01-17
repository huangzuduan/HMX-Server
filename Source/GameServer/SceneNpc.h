#ifndef __CREATURE_H_
#define __CREATURE_H_

#include "SceneEntryPk.h"
#include "UnorderedSet.h"
#include "Single.h"
#include "srvEngine.h"
#include "ScenesServer.h"

class SceneNpcAIController;
struct Buff;

class SceneNpc : public SceneEntryPk, public zAStar<1>
{
public:
	SceneNpc(zNpcB* npc, const t_NpcDefine* define, const SceneEntryType entrytype);

private:

	//////////////////////////////AI//////////////////////////////////////
public:

	/**
	* \brief 寻路过程中判断中间点是否可达目的地
	* \param tempPos 寻路过程的中间点
	* \param destPos 目的点坐标
	* \param radius 寻路范围，超出范围的视为目的地不可达
	* \return 返回是否可到达目的地
	*/
	virtual bool moveable(const zPos &tempPos, const zPos &destPos, const int radius = 12);

	/**
	* \brief 物件向某一个方向移动
	* \param direct 方向
	* \param step 表示步长
	* \return 移动是否成功
	*/
	virtual bool move(const int direct, const int step = 1);

	void setAI(const t_NpcAIDefine &ad);
	// 动作 
	void action(int32 now);
	virtual bool normalAction();
	//---
	virtual bool doNormalAI();
	virtual bool doSayAI();
	virtual bool doRandomChatAI();
	virtual bool doMovetoAI();
	virtual bool doAttackAI();
	virtual bool doGoOnPathAI();
	virtual bool doPatrolAI();
	virtual bool doFleeAI();
	virtual bool doChangeMapAI();
	virtual bool doWarpAI();
	virtual bool doReturnToRegionAI();
	virtual bool doClearAI();
	virtual bool doDropItemAI();

	virtual bool canMove();

	bool checkMoveTime(const int32 ct);
	void setMoveTime(const int32 ct);
	void setMoveTime(const int32 ct, const int delay);
	void delayMoveTime(const int delay);
	bool checkAttackTime(const int32 ct) const;
	void setAttackTime(const int32 ct);
	void setAttackTime(const int32 ct, const int delay);

	void randomChat(NpcChatType type);

	bool warp(const zPos &pos, bool ignore = false);//跳转
	void jumpTo(zPos &newPos) {};
	bool gotoFindPath(const zPos &srcPos, const zPos &destPos);
	bool goTo(const zPos &pos);
	bool shiftMove(const int direct);
	
	virtual void on_reached() { }//回调点 

public:

	// npcai控制器 
	SceneNpcAIController* AIC;

	// Npc定义数据
	const t_NpcDefine* define;

	// npc当前的AI
	t_NpcAIDefine aiDefine;

	// npcAI标志
	int32 aif;

	// Npc基本数据
	zNpcB *npc;

	// 下一次移动时间
	int32 nextMoveTime;

	// 下一次攻击时间
	int32 nextAttackTime;

	bool	m_bFighting;		//NPC是否处于战斗中的标志
	int32	m_dwNowTime;		
	int32	m_dwGtime;			//记录战斗持续的时间(秒级)
	bool	m_mobType;			//召唤怪物标志

};



#endif
