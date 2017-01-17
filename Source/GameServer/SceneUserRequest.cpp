#include "SceneUser.h"


bool SceneUser::ReqMove(Cmd::stUserMoveMoveUserCmd *rev)
{

	//bool canmove = false;
	//Cmd::stUserMoveMoveUserCmd ret;
	//ret.dwUserTempID = tempid;

	//int xlen = abs((long)(pos.x - rev->x));
	//int ylen = abs((long)(pos.y - rev->y));

	//setDir(rev->byDirect);
	//lastPos2 = lastPos1;
	//lastPos1 = pos;

	//zPosI oldPosI = getPosI();
	//zPos oldPos = getPos();

	//WORD speed = rev->bySpeed > 3 ? 1 : rev->bySpeed;

	////保证坐标合法
	//if ((xlen + ylen) > ((getDir() % 2) ? (speed * 2) : speed))
	//{
	//	return false;
	//}

	////sprintf(stderr,"walk here2\n");
	//zPos newPos(rev->x, rev->y);
	//if (moveAction && (!scene->checkBlock(newPos, TILE_BLOCK) && (!scene->checkBlock(newPos, TILE_ENTRY_BLOCK) || this->liquidState)))
	//{
	//	if (scene->refresh(this, newPos))
	//	{
	//		//高8位表示跑得步数,低8位表示走的步数
	//		if (!horse.mount() && speed == 2) step_state += 0x0100;
	//		if (!horse.mount() && speed == 1) ++step_state;

	//		canmove = true;
	//		scene->setBlock(newPos);
	//		scene->clearBlock(oldPos);

	//		ret.byDirect = getDir();
	//		ret.bySpeed = speed;
	//		ret.x = newPos.x;
	//		ret.y = newPos.y;
	//		//检查是否隐身
	//		if (SceneEntry_Hide != getState() && !this->hideme && !Soulflag)
	//			scene->sendCmdToNine(oldPosI, &ret, sizeof(ret), dupIndex);
	//		else
	//		{
	//			//隐身则不占用block
	//			scene->clearBlock(newPos);
	//			sendCmdToMe(&ret, sizeof(ret));
	//			scene->sendCmdToWatchTrap(oldPosI, &ret, sizeof(ret));
	//		}

	//		if (oldPosI != getPosI())
	//		{

	//			Cmd::stRemoveUserMapScreenUserCmd removeUser;
	//			removeUser.dwUserTempID = tempid;
	//			scene->sendCmdToReverseDirect(oldPosI,
	//				scene->getScreenDirect(oldPosI, getPosI()), &removeUser, sizeof(removeUser), dupIndex);

	//			sendMeToNineDirect(scene->getScreenDirect(oldPosI, getPosI()));
	//			sendNineToMeDirect(scene->getScreenDirect(oldPosI, getPosI()));

	//			//校验9屏所有玩家以及Npc坐标

	//			GetAllRemovePosNpc allNpcs(this);
	//			GetAllRemovePosUser allUsers(this);
	//			//const zPosIVector &pv = scene->getNineScreen(getPosI());
	//			const zPosIVector &pv = scene->getReverseDirectScreen(oldPosI, scene->getScreenDirect(oldPosI, getPosI()));
	//			//{
	//			for (zPosIVector::const_iterator it = pv.begin(); it != pv.end(); it++)
	//			{
	//				scene->execAllOfScreen(zSceneEntry::SceneEntry_NPC, *it, allNpcs);
	//				scene->execAllOfScreen(zSceneEntry::SceneEntry_Player, *it, allUsers);
	//			}
	//			//}
	//			if (allNpcs.canSend())
	//			{
	//				sendCmdToMe(allNpcs.getSendBuffer(), allNpcs.getSize());
	//			}
	//			if (allUsers.canSend())
	//			{
	//				sendCmdToMe(allUsers.getSendBuffer(), allUsers.getSize());
	//			}

	//		}
	//	}
	//}

	return true;
}










