#include "SceneUser.h"
#include "GameService.h"
#include "def_resource.h"


SceneUser::SceneUser(const ::data::UserInfo& proto) : SceneEntryPk(zSceneEntry::SceneEntry_Player)
{
	clientReady = false;
	userModity = false;
	initDataFinish = false;

	dataProto.CopyFrom(proto);
};

SceneUser::~SceneUser()
{

}

/* 上线-处理小逻辑方面的功能 */
void SceneUser::online()
{

}

void SceneUser::Timer(const zTaskTimer* t)
{

}

void SceneUser::sendCmdToMe(NetMsgSS* pMsg, int32_t nSize)
{
	if (!initDataFinish)
	{
		H::logger->warn("Server Not initDataFinish");
		ASSERT(0);
		return;
	}

	if (!clientReady)
	{
		H::logger->warn("ClientReady Not Ready");
		return;
	}
	sendToFep(pMsg, nSize);
}

void SceneUser::sendToFep(NetMsgSS* pMsg, int32_t nSize)
{
	zSession* session = GameService::getMe().SessionMgr()->getFep(nFepSessionID);
	if (session)
	{
		pMsg->clientSessID = this->nSessionID;
		pMsg->fepServerID = this->nFepSessionID;
		session->sendMsg(pMsg, nSize);
	}
}

void SceneUser::sendToDp(NetMsgSS* pMsg, int32_t nSize)
{
	pMsg->clientSessID = this->nSessionID;
	pMsg->fepServerID = this->nFepSessionID;
	GameService::getMe().SessionMgr()->sendToDp(pMsg, nSize);
}

void SceneUser::sendToWs(NetMsgSS* pMsg, int32_t nSize)
{
	pMsg->clientSessID = this->nSessionID;
	pMsg->fepServerID = this->nFepSessionID;
	GameService::getMe().SessionMgr()->sendToWs(pMsg, nSize);
}


void SceneUser::sendMainToMe()
{
	/* 角色基本数据  */
	//C::RtCharMainData sMsg;
	//sMsg.userVal = userAttribute;
	//sMsg.pkVal = GetEntryPkValBase();
	//sendCmdToMe(&sMsg, sizeof(sMsg));

}

void SceneUser::setupCharBase()
{

}

bool SceneUser::CheckMoneyEnough(int32_t nType, int32_t nNum)
{
	//switch (nType)
	//{
	//case 1:
	//{
	//	return (GetUserAttrInt32(USER_ATTR_GOLD) < nNum);
	//}
	//break;
	//case 2:
	//{
	//	return (GetUserAttrInt32(USER_ATTR_SILVER) < nNum);
	//}
	//break;
	//case 3:
	//{
	//	return (GetUserAttrInt32(USER_ATTR_COPPER) < nNum);
	//}
	//break;
	//default:
	//	break;
	//}
	return false;
}

bool SceneUser::TrySubMoney(int32_t type, int32_t num)
{
	return SubMoney(type, num, false, true);

}

bool SceneUser::SubMoney(int32_t nType, int32_t nNum, bool notify, bool isTry)
{
	//switch (nType)
	//{
	//case 1:
	//{
	//	int32 nGold = GetUserAttrInt32(USER_ATTR_GOLD);
	//	if (nGold < nNum) return false;
	//	if (isTry) return true;
	//	SetUserAttr(USER_ATTR_GOLD, nGold - nNum);
	//}
	//break;
	//case 2:
	//{
	//	int32 nSilver = GetUserAttrInt32(USER_ATTR_SILVER);
	//	if (nSilver < nNum) return false;
	//	if (isTry) return true;
	//	SetUserAttr(USER_ATTR_SILVER, nSilver - nNum);
	//}
	//break;
	//case 3:
	//{
	//	int32 nCopper = GetUserAttrInt32(USER_ATTR_COPPER);
	//	if (nCopper < nNum) return false;
	//	if (isTry) return true;
	//	SetUserAttr(USER_ATTR_COPPER, nCopper - nNum);
	//}
	//break;
	//default:
	//	return false;
	//	break;
	//}

	//if (notify)
	//{
	//	RtCharMoneyData sendMsg;
	//	sendMsg.nGold = GetUserAttrInt32(USER_ATTR_GOLD);
	//	sendMsg.nSilver = GetUserAttrInt32(USER_ATTR_SILVER);
	//	sendMsg.nCopper = GetUserAttrInt32(USER_ATTR_COPPER);
	//	SendToMe(&sendMsg,sizeof(sendMsg));
	//}

	return true;
}

void SceneUser::changeHP(const SDWORD &hp)
{

}

void SceneUser::changeSP(const SDWORD &sp)
{

}

void SceneUser::changeMP(const SDWORD &mp)
{

}


int SceneUser::isEnemy(SceneEntryPk *entry, bool notify, bool good)
{
	return true;
}


SceneEntryPk* SceneUser::getMaster()
{
	return this;
}


SceneEntryPk* SceneUser::getTopMaster()
{
	return this;
}


bool SceneUser::isDie()
{
	return false;
}


DWORD SceneUser::getLevel() const
{
	return 0;
}



bool SceneUser::needType(const DWORD &needtype)
{
	return false;
}

bool SceneUser::needWeapon(DWORD skillid)
{
	return false;
}


bool SceneUser::isPkZone(SceneEntryPk *other)
{
	return false;
}


bool SceneUser::reduce(const DWORD &object, const BYTE num)
{
	return false;
}


bool SceneUser::checkReduce(const DWORD &object, const BYTE num)
{
	return false;
}

void SceneUser::showCurrentEffect(const WORD &state, bool isShow, bool notify)
{

}


bool SceneUser::preAttackMe(SceneEntryPk *pUser, const Cmd::stAttackMagicUserCmd *rev, bool physics, const bool good)
{
	return false;
}

void SceneUser::toDie(const DWORD &dwTempID)
{

}

SWORD SceneUser::directDamage(SceneEntryPk *pAtt, const SDWORD &dam, bool notify)
{

	return 0;
}