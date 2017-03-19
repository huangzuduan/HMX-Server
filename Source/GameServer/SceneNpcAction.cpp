#include "SceneNpc.h"
#include "SceneNpcAIController.h"


bool SceneNpc::moveable(const zPos &tempPos, const zPos &destPos, const int radius)
{

	return true;
}

bool SceneNpc::move(const int direct, const int step)
{

	return true;
}

/**
* \brief 设置NPC的AI
*
* \param ai 要设置的AI结构的引用
*/
void SceneNpc::setAI(const t_NpcAIDefine &ai)
{
	aiDefine = ai;
}

void SceneNpc::action(int32 now)
{
	//AIC->processPhase();
}

bool SceneNpc::normalAction()
{
	switch (aiDefine.type)
	{
	case NPC_AI_NORMAL:
	{
		int ret = doNormalAI();
		return ret;
	}
	break;
	case NPC_AI_SAY:
	{
		return doSayAI();
	}
	break;
	case NPC_AI_MOVETO:
	{
		return doMovetoAI();
	}
	break;
	case NPC_AI_ATTACK:
	{
		return doAttackAI();
	}
	break;
	case NPC_AI_GO_ON_PATH:
	{
		return doGoOnPathAI();
	}
	break;
	case NPC_AI_PATROL:
	{
		return doPatrolAI();
	}
	break;
	case NPC_AI_FLEE:
	{
		return doFleeAI();
	}
	break;
	case NPC_AI_RETURN_TO_REGION:
	{
		return doReturnToRegionAI();
	}
	break;
	case NPC_AI_CHANGE_MAP:
	{
		return doChangeMapAI();
	}
	break;
	case NPC_AI_WARP:
	{
		return doWarpAI();
	}
	break;
	case NPC_AI_CLEAR:
	{
		return doClearAI();
	}
	break;
	case NPC_AI_DROP_ITEM:
	{
		return doDropItemAI();
	}
	break;
	case NPC_AI_RANDOM_CHAT:
	{
		return doRandomChatAI();
	}
	break;
	case NPC_AI_WAIT:
	{
		return true;
	}
	break;
	default:
	{
		return false;
	}
	break;
	}
	return true;
}


bool SceneNpc::doNormalAI()
{

	
	return true;
}

bool SceneNpc::doSayAI()
{
	return true;
}

bool SceneNpc::doRandomChatAI()
{
	return true;
}

bool SceneNpc::doMovetoAI()
{
	if (!AIC->phaseTimeOver())
	{
		if (checkMoveTime(H::timeTick->getMilliTime()) && canMove())
		{
			if (!gotoFindPath(getPos(), aiDefine.pos))//向目标移动
				goTo(aiDefine.pos);//换一种方式向目标移动
			if (AIC)
				if (NPC_AI_PATROL == aiDefine.type)
					AIC->setActRegion(getPos(), 5, 5);
				else
					AIC->setActRegion(getPos());
		}
	}
	return true;
}

bool SceneNpc::doAttackAI()
{
	return true;
}

bool SceneNpc::doGoOnPathAI()
{
	return true;
}

bool SceneNpc::doPatrolAI()
{
	return true;
}

bool SceneNpc::doFleeAI()
{
	return true;
}

bool SceneNpc::doChangeMapAI()
{
	return true;
}

bool SceneNpc::doWarpAI()
{
	return true;
}

bool SceneNpc::doReturnToRegionAI()
{
	return true;
}

bool SceneNpc::doClearAI()
{
	return true;
}

bool SceneNpc::doDropItemAI()
{
	return true;
}

/**
* \brief 是否可以移动
*
* \return 是否可以移动
*/
bool SceneNpc::canMove()
{
	if (npc->kind == NPC_TYPE_TURRET ||
		npc->kind == NPC_TYPE_BARRACKS ||
		npc->kind == NPC_TYPE_CAMP)
		return false;

	return (!(aif&AIF_NO_MOVE)/* && moveAction*/);
}

bool SceneNpc::checkMoveTime(const int32 ct)
{

	return true;
}

void SceneNpc::setMoveTime(const int32 ct)
{

}

void SceneNpc::setMoveTime(const int32 ct, const int delay)
{

}

void SceneNpc::delayMoveTime(const int delay)
{

}

bool SceneNpc::checkAttackTime(const int32 ct) const
{
	return true;
}

void SceneNpc::setAttackTime(const int32 ct)
{

}

void SceneNpc::setAttackTime(const int32 ct, const int delay)
{

}

/**
* \brief npc随机说话
*
* \param type 说话的类型
*/
void SceneNpc::randomChat(NpcChatType type)
{

}

/**
* \brief 瞬间移动
*
*
* \param newPos 目标位置
* \return 是否成功
*/
bool SceneNpc::warp(const zPos &newPos, bool ignore)
{
	return true;
}

/**
* \brief 使物件向某一个点移动
* 带寻路算法的移动,不过这里只是封装了一下,由于不同的npc步长不同,在这里调用不同步长的A*算法
* \param srcPos 起点坐标
* \param destPos 目的地坐标
* \return 移动是否成功
*/
bool SceneNpc::gotoFindPath(const zPos &srcPos, const zPos &destPos)
{
	return zAStar<>::gotoFindPath(srcPos, destPos);
}

/**
* \brief Npc向某一个点移动
* 不带寻路算法的移动,不过这里只是封装了一下,由于不同的npc步长不同,在这里调用不同步长的A*算法
* \param pos 目的地坐标
* \return 移动是否成功
*/
bool SceneNpc::goTo(const zPos &pos)
{
	return zAStar<>::goTo(getPos(), pos);
}

/**
* \brief Npc随机向某一个方向移动
* 不过这里只是封装了一下,由于不同的npc步长不同,在这里调用不同步长的A*算法
* \param direct 随机方向
* \return 移动是否成功
*/
bool SceneNpc::shiftMove(const int direct)
{
	return zAStar<>::shiftMove(direct);
}



