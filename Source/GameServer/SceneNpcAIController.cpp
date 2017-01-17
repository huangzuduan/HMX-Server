#include "GameServer_PCH.h"
#include "SceneNpcAIController.h"
#include "srvEngine.h"
#include "ScenesServer.h"

const int SceneNpcAIController::npc_call_fellow_rate = 30;///NPC召唤同伴的几率
const int SceneNpcAIController::npc_one_checkpoint_time = 60;///NPC按照路线移动时,走一个路点的最长时间
const int SceneNpcAIController::npc_checkpoint_region = 2;///NPC移动,到达一个路点的判定范围
const int SceneNpcAIController::npc_onhit_stop_time = 2;///任务NPC移动中被攻击时,停止的时间
const int SceneNpcAIController::npc_flee_distance = 4;///NPC逃离攻击者的距离
const int SceneNpcAIController::npc_min_act_region = 5;///NPC逃离攻击者的距离

SceneNpcAIController::SceneNpcAIController(SceneNpc* sceneNpc) :npc(sceneNpc), curPhase(0), repeat(-1), active(false), reached(false)
{
	bzero(dstMap, sizeof(dstMap));
	//if (sn)
	//	strncpy(dstMap, sn->scene->name, MAX_NAMESIZE - 1);
	dstPos = zPos(0, 0);
	curAI.type = NPC_AI_NORMAL;
	phaseEndTime = 0;
}

/**
* \brief 检查各种事件,并切换相应状态
* 该方法在SceneNpc::action中执行，场景中又遍历执行SceneNpc::action 
*
*/
void SceneNpcAIController::processPhase()
{
	switch (curAI.type)
	{
	case NPC_AI_MOVETO:
	{
		if (arrived(curAI.pos))
		{
			setActRegion(curAI.pos, curAI.regionX, curAI.regionY);
			nextPhase();
		}
	}
	break;
	case NPC_AI_PATROL:
	{
		if (arrived(curAI.pos))
			nextPhase();
	}
	break;
	case NPC_AI_RETURN_TO_REGION:
	{
		if (arrived())
		{
			setAI(oldAI);
			//npc->resetSpeedRate();
		}
	}
	break;
	default:
		break;
	}
}

/**
* \brief 设置npc的AI,设置阶段时间
*
* \param ai 要设置的AI（采用引用会有问题
* \param setTime 是否同时设置时间,默认为真
*/
void SceneNpcAIController::setAI(const t_NpcAIDefine ai, const bool setTime)
{
	oldAI = curAI;
	npc->setAI(ai);
	curAI = ai;
	if (setTime)
		setPhaseTime(ai.lasttime * 1000);

	switch (curAI.type)
	{
	case NPC_AI_ATTACK:
	{
		setActRegion(curAI.pos, curAI.regionX, curAI.regionY);
	}
	break;
	case NPC_AI_FLEE:
	{
		npc->randomChat(NPC_CHAT_ON_FLEE);
	}
	break;
	default:
		break;
	}
	//Zebra::logger->debug("setAI(): %s AI=%d",npc->name,ai.type);
}

/**
* \brief 判断Npc是否走出了自身固有范围之外
* 如果没有在跟踪用户状态,需要向范围方向行走
* 追逐时范围扩大10
* \return 是否超出活动范围
*/
bool SceneNpcAIController::outOfRegion() const
{
	//if (!(npc->canMove())) return false;
	//const zPos &pos = npc->getPos();
	////if (npc->getChaseMode() == SceneNpc::CHASE_NONE)
	//if (0 == npc->curTargetID)
	//	return !((pos.x >= actPos.x - actRegionX)
	//		&& (pos.x <= actPos.x + actRegionX)
	//		&& (pos.y >= actPos.y - actRegionY)
	//		&& (pos.y <= actPos.y + actRegionY));
	//else
	//	return !((pos.x >= actPos.x - (actRegionX + 10))
	//		&& (pos.x <= actPos.x + (actRegionX + 10))
	//		&& (pos.y >= actPos.y - (actRegionY + 10))
	//		&& (pos.y <= actPos.y + (actRegionY + 10)));
	return false;
}

/**
* \brief 判断npc是否到达某位置的某范围内
*
* \param pos 中心位置,默认是当前AI的目标位置
* \param regionX 范围宽,默认是当前AI的范围宽
* \param regionY 范围高,默认是当前AI的范围高
* \return 是否在范围内
*/
bool SceneNpcAIController::arrived(zPos pos, int regionX, int regionY)
{
	if (pos == zPos(0, 0)) pos = curAI.pos;
	if (-1 == regionX) regionX = curAI.regionX;
	if (-1 == regionY) regionY = curAI.regionY;

	//zPos npcPos = npc->getPos();
	return (npc->getPos().x >= pos.x - regionX)
		&& (npc->getPos().x <= pos.x + regionX)
		&& (npc->getPos().y >= pos.y - regionY)
		&& (npc->getPos().y <= pos.y + regionY);
}

//回到活动范围,追踪敌人超出范围时以5倍速返回
/**
* \brief 设置回到范围的AI使NPC回到活动范围
* 如果NPC是跟踪敌人而超出了活动范围,则以5倍速返回活动范围内,同时放弃跟踪目标
*
*/
void SceneNpcAIController::returnToRegion()
{
	//t_NpcAIDefine def = curAI;
	//def.type = NPC_AI_RETURN_TO_REGION;
	//def.pos = actPos;
	//def.regionX = randBetween(2, actRegionX);
	//def.regionY = randBetween(2, actRegionY);
	//def.lasttime = 10;
	//setAI(def);
	////if (npc->getChaseMode() != SceneNpc::CHASE_NONE)
	//if (0 != npc->curTargetID)
	//{
	//	npc->randomChat(NPC_CHAT_ON_RETURN);
	//	npc->unChaseUser();
	//	npc->setSpeedRate(npc->getSpeedRate()*4.0);
	//}
	//Channel::sendNine(npc,"我得回到(%d,%d)范围%d,%d以内",curAI.pos.x,curAI.pos.y,def.regionX,def.regionY);
}

/**
* \brief 是否到达目的地
* 目的地的定义是脚本中最后一个移动的位置
* 地图不同不算到达
*
*/
bool SceneNpcAIController::dstReached()
{
	//if (strcmp(dstMap, npc->scene->name)) return false;

	//if (arrived(dstPos, npc_checkpoint_region, npc_checkpoint_region))
	//	return true;

	return false;
}

/**
* \brief 进入下一阶段
*
* \param index 可以指定要进入的阶段编号,-1表示下一阶段
*/
void SceneNpcAIController::nextPhase(int index)
{
	/* //不是特殊npc也要执行脚本
	if (!active)
	{
	setNormalAI();
	return;
	}
	*/

	if (index>-1)
		curPhase = index;
	else
	{
		if (curPhase == phaseVector.size() - 1)
		{
			if (-2 == repeat)
			{
				curPhase = randBetween(0, phaseVector.size() - 1);
			}
			else if (-1 == repeat)
			{
				curPhase = 0;
			}
			else if (1 == repeat)
			{
				active = false;
				phaseVector.clear();
				repeat--;
				npc->on_reached();
				setNormalAI();
				return;
			}
			else if (repeat>1)
			{
				curPhase = 0;
				repeat--;
				//Channel::sendNine(npc,"repeat=%d",repeat);
			}
		}
		else
			curPhase++;
	}

	setPhaseTime(phaseVector[curPhase].lasttime*1000);

	if (phaseVector.size())
		setAI(phaseVector[curPhase]);
	//Channel::sendNine(npc,"进入阶段%d",curPhase);
}


/**
* \brief 设置npc普通AI
* 普通AI时AIDefine的其他参数均无效
*/
void SceneNpcAIController::setNormalAI()
{
	curAI.type = NPC_AI_NORMAL;
	setAI(curAI);
}

/**
* \brief NPC被攻击的事件处理
*
* \param pAtk 攻击者
*/
void SceneNpcAIController::on_hit(SceneEntryPk *pAtk)
{

	npc->randomChat(NPC_CHAT_ON_HIT);

	//[sky] NPC第一次受到攻击激活AI定时器
	if (!npc->m_bFighting)
	{
		npc->m_dwNowTime = GetTickCount();
		npc->m_mobType = false;
		npc->m_bFighting = true;
		npc->m_dwGtime = 0;
	}

	//npc->delayMoveTime(npc->npc->distance/2);//被击动作的延迟
	switch (npc->npc->kind)
	{
	case NPC_TYPE_HUMAN:      ///人型
	case NPC_TYPE_NORMAL:      /// 普通类型
	case NPC_TYPE_BBOSS:      /// 大Boss类型
	case NPC_TYPE_PBOSS:      /// 紫Boss类型
	case NPC_TYPE_LBOSS:      /// 小Boss类型
	case NPC_TYPE_BACKBONE:      /// 精英类型
	case NPC_TYPE_GOLD:        /// 黄金类型
	case NPC_TYPE_SUMMONS:      /// 召唤类型
	case NPC_TYPE_AGGRANDIZEMENT:  /// 强化类型
	case NPC_TYPE_ABERRANCE:    /// 变异类型
	case NPC_TYPE_BACKBONEBUG:    /// 精怪类型
	case NPC_TYPE_TURRET:			/// 炮塔
	case NPC_TYPE_BARRACKS:
	case NPC_TYPE_CAMP:
	case NPC_TYPE_GHOST:			/// 元神
	case NPC_TYPE_ANIMON:        /// 动物类
	{

	}
	break;
	case NPC_TYPE_GUARD:  /// 士兵类型
	case NPC_TYPE_PET:  /// 宠物类型
	case NPC_TYPE_TASK:    /// 任务类型
	case NPC_TYPE_TOTEM:      /// 图腾类型
	case NPC_TYPE_TRADE:  /// 买卖类型
		break;
	default:
		break;
	}
}

/**
* \brief 设置NPC的活动范围
*
* \param pos 中心位置
* \param x,y 范围的宽和高
* \return
*/
void SceneNpcAIController::setActRegion(zPos pos, int x, int y)
{
	if (pos == zPos(0, 0)) 
		pos = npc->getPos();
	npc->SetPosition(pos);
	actPos = pos;
	if (0 <= x) actRegionX = x >= npc_min_act_region ? x : npc_min_act_region;
	if (0 <= y) actRegionY = y >= npc_min_act_region ? y : npc_min_act_region;
	//Channel::sendNine(npc,"活动范围:(%d,%d) x=%d y=%d",actPos.x,actPos.y,actRegionX,actRegionY);
}

/**
* \brief 设置该阶段的结束时间
*
* \param delay 从现在开始的延迟,毫秒为单位
*/
void SceneNpcAIController::setPhaseTime(const int delay)
{
	phaseEndTime = Zebra::timeTick->getMilliTime();
	phaseEndTime += delay;
}

/**
* \brief 检查阶段时间是否结束
*
* \return 是否到了阶段结束时间
*/
bool SceneNpcAIController::phaseTimeOver()
{
	if (NPC_AI_NORMAL != curAI.type)
	{
		return Zebra::timeTick->getMilliTime() >= phaseEndTime;
	}
	else
		return false;
}

