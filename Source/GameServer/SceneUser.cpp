#include "SceneUser.h"
#include "ResourceMgr.h"

#include "def_resource.h"
#include "Relation.h"


SceneUser::SceneUser() : SceneEntryPk(zSceneEntry::SceneEntry_Player)
, objM(this), usm(this), relM(this)
{
	clientReady = false;
	userModity = false;
	initDataFinish = false;
};

SceneUser::~SceneUser()
{

}


bool SceneUser::loadDB(const S::SSRtLoadUser* packet, int32 nSize)
{
	// 拷贝基本的数据
	memcpy(&userbase, &packet->base, sizeof(userbase));

	// 初始化Entry实例数据 
	this->id = userbase.id;
	this->tempid = packet->sessid;
	strncpy(this->name, userbase.name, MAX_NAMESIZE);

	// 解析二进制数据
	if (packet->size == sizeof(packet->header) + packet->header.size)
	{
		this->readBinary(packet->header.data, packet->header.size);
	}
	else
	{
		H::logger->error("数据错误:name=%s", this->name);
		ASSERT(0);
		return false;
	}
	return true;
}

bool SceneUser::saveDB()
{
	BUFFER_CMD(S::SSRqSaveUser, send, MAX_BUFFERSIZE);
	memcpy(&send->base, &userbase, sizeof(send->base));
	send->header.size = this->writeBinary(&send->header.data[send->size]);
	send->size += sizeof(BinaryHeader);
	send->size += send->header.size;
	GameService::getMe().getSessionMgr().sendToDp(send, send->getSize());
	return true;
}

void SceneUser::readBinary(const char* data, int32 len)
{
	if (len < sizeof(BinaryMember))
		return;

	int32 dwSize = 0;
	const BinaryMember* pMember = (const BinaryMember*)data;
	while (pMember->type != BINARY_USER_NULL && pMember->type < BINARY_USER_MAX)
	{
		switch (pMember->type)
		{
			case BINARY_USER_COUNTER:
			{
				::protobuf::CounterProto proto;
				proto.ParseFromArray(pMember->data, pMember->size);
				this->unserialize(proto);
			}
			break;
			case BINARY_USER_RELATION:
			{
				::protobuf::RelationProto proto;
				proto.ParseFromArray(pMember->data, pMember->size);
				relM.unserialize(proto);
			}
			break;
		}
		dwSize += sizeof(BinaryMember);
		dwSize += pMember->size;
		pMember = (const BinaryMember*)(&pMember->data[pMember->size]);
	}
}

int32 SceneUser::writeBinary(char* data)
{
	int32 dwSize = 0;
	BinaryMember* pMember = (BinaryMember*)data;
	for (int type = BINARY_USER_NULL + 1; type < BINARY_USER_MAX; ++type)
	{
		pMember->type = type;
		pMember->size = 0;
		switch (pMember->type)
		{
			case BINARY_USER_COUNTER:
			{
				::protobuf::CounterProto proto;
				this->serialize(proto);
				pMember->size += proto.ByteSize();
				proto.SerializeToArray(pMember->data, pMember->size);
			}
			break;
			case BINARY_USER_RELATION:
			{
				::protobuf::RelationProto proto;
				relM.serialize(proto);
				pMember->size += proto.ByteSize();
				proto.SerializeToArray(pMember->data, pMember->size);
			}
			break;
		}

		if (pMember->size)
		{
			dwSize += sizeof(BinaryMember);
			dwSize += pMember->size;
			pMember = (BinaryMember*)(&pMember->data[pMember->size]);
		}
	}

	pMember = (BinaryMember*)(&pMember->data[dwSize]);
	pMember->type = BINARY_USER_NULL;
	pMember->size = 0;
	dwSize += sizeof(BinaryMember) + 0;

	return dwSize;
}

// 保存数据 
bool SceneUser::serialize(::protobuf::CounterProto& proto)
{
	//proto.SerializeToArray(send->data, MAX_BUFFERSIZE - sizeof(S2DSaveUser));

	return true;
}

// 初始化角色基本数据 
void SceneUser::unserialize(const ::protobuf::CounterProto& proto)
{


}

/* 上线-处理小逻辑方面的功能 */
void SceneUser::online()
{

	/* 加入聊天频道 */
	Channel* wdCh = GameService::getMe().getChannelM().get(CHANNEL_TYPE_WORLD);
	if (wdCh)
	{
		wdCh->add(this);
	}
	else
	{
		H::logger->error("Not Found The World Channel");
	}

	relM.sendAllRelList();
}

void SceneUser::Timer(const zTaskTimer* t)
{
	int32 now = H::timeTick->now();
	if (t->is1Sec())
	{
		ucm.Timer(now);
	}

	if (t->is2Sec())
	{


	}

	if (t->is3Sec())
	{

	}

	if (t->is5Sec())
	{

	}

	if (t->is1Min())
	{

	}

}

void SceneUser::OnExpChange(const ValueType& vOldValue, const ValueType& vNewValue)
{

}

void SceneUser::OnMapIDChange(const ValueType& vOldValue, const ValueType& vNewValue)
{

}

void SceneUser::OnClothesChange(const ValueType& vOldValue, const ValueType& vNewValue)
{

}

void SceneUser::OnWeaponChange(const ValueType& vOldValue, const ValueType& vNewValue)
{

}

void SceneUser::OnMoneyChange(const ValueType& vOldValue, const ValueType& vNewValue)
{
	C::RtCharMoneyData msg;
	msg.nGold = 0;
	msg.nSilver = 0;
	msg.nCopper = 0;
	sendCmdToMe(&msg, sizeof(msg));
}

void SceneUser::sendCmdToMe(NetMsgSS* pMsg, int32 nSize)
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

void SceneUser::sendToFep(NetMsgSS* pMsg, int32 nSize)
{
	zSession* session = GameService::getMe().getSessionMgr().getFep(fepsid);
	if (session)
	{
		pMsg->sessid = this->sessid;
		pMsg->fepsid = this->fepsid;
		session->sendMsg(pMsg, nSize);
	}
}

void SceneUser::sendToDp(NetMsgSS* pMsg, int32 nSize)
{
	pMsg->sessid = this->sessid;
	pMsg->fepsid = this->fepsid;
	GameService::getMe().getSessionMgr().sendToDp(pMsg, nSize);
}

void SceneUser::sendToWs(NetMsgSS* pMsg, int32 nSize)
{
	pMsg->sessid = this->sessid;
	pMsg->fepsid = this->fepsid;
	GameService::getMe().getSessionMgr().sendToWs(pMsg, nSize);
}


void SceneUser::sendMainToMe()
{
	/* 角色基本数据  */
	C::RtCharMainData sMsg;
	//sMsg.userVal = userAttribute;
	//sMsg.pkVal = GetEntryPkValBase();
	sendCmdToMe(&sMsg, sizeof(sMsg));

	/* 道具数据 */
	C::RtUserPackages sendItemMsg;
	std::vector<qObject*> allItems;
	getAllItemSlots(allItems);
	sendItemMsg.nCount = 0;
	for (int i = 0; i < allItems.size(); ++i)
	{
		sendItemMsg.items[sendItemMsg.nCount].nUniqueID = allItems[i]->tempid;
		sendItemMsg.items[sendItemMsg.nCount].nItemID = allItems[i]->itemID;
		sendItemMsg.items[sendItemMsg.nCount].nItemNum = allItems[i]->itemNum;
		sendItemMsg.items[sendItemMsg.nCount].nIndex = allItems[i]->id;
		sendItemMsg.items[sendItemMsg.nCount].nLock = 0;
		sendItemMsg.nCount++;
	}
	H::logger->debug("Items Count:%u", sendItemMsg.nCount);
	sendCmdToMe(&sendItemMsg, sizeof(sendItemMsg));
}

void SceneUser::setupCharBase()
{

}

bool SceneUser::CheckMoneyEnough(int32 nType, int32 nNum)
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

bool SceneUser::TrySubMoney(int32 type, int32 num)
{
	return SubMoney(type, num, false, true);

}

bool SceneUser::SubMoney(int32 nType, int32 nNum, bool notify, bool isTry)
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


bool SceneUser::addSkillToMe(zSkill *skill)
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


bool SceneUser::doSkillCost(const zSkillB *base)
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