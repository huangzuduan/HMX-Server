#ifndef __CREATURE_CONTROLLER_H_
#define __CREATURE_CONTROLLER_H_

#include "SceneNpc.h"
#include "srvEngine.h"
#include "ScenesServer.h"

/**
* \brief AI控制器
* 控制器可以读取NPC脚本,使NPC按照脚本来动作
*
* 控制器处理各种事件,时间、被攻击、死亡等
* 根据不同的条件为NPC设置不同的AI
*
*/
class SceneNpcAIController
{
public:
	static const int npc_call_fellow_rate;///NPC召唤同伴的几率
	static const int npc_one_checkpoint_time;///NPC按照路线移动时,走一个路点的最长时间
	static const int npc_checkpoint_region;///NPC移动,到达一个路点的判定范围
	static const int npc_onhit_stop_time;///任务NPC移动中被攻击时,停止的时间
	static const int npc_flee_distance;///NPC逃离攻击者的距离
	static const int npc_min_act_region;///NPC最小活动范围

	///本控制器控制的npc
	SceneNpc * npc;
										///AI容器,AI按照在容器中的顺序依次执行
	std::vector<t_NpcAIDefine> phaseVector;
	///当前的AI索引
	DWORD curPhase;
	///当前AI的结束时间
	int64 phaseEndTime;

	///脚本重复次数
	///-1：无限循环  0：停止  >0：循环次数
	int repeat;

	///是否起用了脚本
	bool active;
	void nextPhase(int index = -1);
	void on_phaseEnd();
	SceneNpcAIType parseAction(char *);


	///当前的AI和保存的前一个AI
	t_NpcAIDefine curAI;
	t_NpcAIDefine oldAI;
	///活动范围的中心
	zPos actPos;
	///活动范围的宽和高
	int actRegionX, actRegionY;
	bool outOfRegion() const;
	void returnToRegion();

	bool arrived(zPos pos = zPos(0, 0), int x = -1, int y = -1);
	bool dstReached();
	///是否到达目的地
	bool reached;

	///目的地图
	char dstMap[32];
	///目的位置
	zPos dstPos;

public:
	SceneNpcAIController(SceneNpc *);
	void setAI(const t_NpcAIDefine ai, const bool setTime = true);
	void switchAI(const bool setTime = true);
	void setNormalAI();
	void setActRegion(zPos pos = zPos(0, 0), int x = -1, int y = -1);
	void getActRegion(zPos &, int &, int  &);
	bool loadScript(DWORD id);
	void unloadScript();
	void processPhase();
	void setRepeat(int repeat);
	int getRepeat();
	bool isActive();
	void setPhaseTime(const int delay);
	void delayPhaseTime(const int delay);
	bool phaseTimeOver();

	void on_relive();
	void on_find_enemy(const SceneEntryPk *);
	void on_hit(SceneEntryPk *pAtk);
	void on_die();

};

#endif

