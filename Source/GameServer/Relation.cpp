#include "GameServer_PCH.h"
#include "Relation.h"
#include "SceneUserMgr.h"

Relation::Relation()
{

}

S::t_RelChatMsg* Relation::getChatMsg(int64 msgid)
{
	std::map<int64, S::t_RelChatMsg, std::greater<int64> >::iterator it = chatmsgs.find(msgid);
	if (it != chatmsgs.end())
	{
		return &it->second;
	}
	return NULL;
}

void Relation::addChatMsg(int64 msgid, S::t_RelChatMsg* msg)
{
	chatmsgs.insert(std::make_pair(msgid,*msg));
}

RelationM::RelationM(SceneUser* user):pOwner(user)
{

}

RelationM::~RelationM()
{

}

void RelationM::serialize(::protobuf::RelationProto& proto)
{
	std::map<int64, C::t_RelationData>::const_iterator it = relations.begin();
	for (; it != relations.end(); ++it)
	{
		::protobuf::Relation* relInfo = proto.add_relation();
		if (relInfo)
		{
			relInfo->set_uid(it->second.uid);
			relInfo->set_rel(it->second.rel);
			relInfo->set_createtime(it->second.createtime);
			relInfo->set_dealreltime(it->second.dealreltime);
		}
	}
}

void RelationM::unserialize(const ::protobuf::RelationProto& proto)
{
	for (int i = 0; i < proto.relation_size(); ++i)
	{
		const ::protobuf::Relation& relInfo = proto.relation(i);
		C::t_RelationData relData;
		relData.uid = relInfo.uid();
		relData.rel = relInfo.rel();
		relData.createtime = relInfo.createtime();
		relData.dealreltime = relInfo.dealreltime();
		relations[relData.uid] = relData;
	}
}

Relation* RelationM::get(int64 id)
{
	return (Relation*)zEntryMgr::getEntryByID(id);
}

bool RelationM::add(Relation* obj)
{
	return zEntryMgr::addEntry(obj);
}

void RelationM::remove(Relation* obj)
{
	zEntryMgr::removeEntry(obj);
}

bool RelationM::doAddRel(int64 uid, const char* name, int32 rel)
{
	C::t_RelationData* relData = getRelData(uid);
	if (relData)
	{
		if (relData->rel != rel)
		{
			relData->rel = rel;
		}
		if (strncmp(relData->name,name,MAX_NAMESIZE) != 0)
		{
			strncpy(relData->name,name,MAX_NAMESIZE);
		}
	}
	else
	{
		C::t_RelationData newRelData;
		newRelData.uid = uid;
		newRelData.rel = rel;
		strncpy(newRelData.name, name, MAX_NAMESIZE);
		newRelData.createtime = H::timeTick->now();
		newRelData.dealreltime = H::timeTick->now();
		relations.insert(std::make_pair(uid, newRelData));
		relData = &relations[uid];
	}

	C::RtRelationUpdate send;
	memcpy(&send.rel, relData,sizeof(send.rel));

	pOwner->sendCmdToMe(&send, sizeof(send));

	return true;
}

bool RelationM::doRemoveRel(int64 uid)
{
	std::map<int64, C::t_RelationData>::iterator it = relations.find(uid);
	if (it != relations.end())
	{
		relations.erase(it);
		C::RtRelationDelete send;
		send.uid = uid;
		pOwner->sendCmdToMe(&send, sizeof(send));
	}
	return true;
}

void RelationM::sendAllRelList()
{
	BUFFER_CMD(C::RtRelationList, send, MAX_BUFFERSIZE);
	send->count = 0;
	std::map<int64, C::t_RelationData>::iterator it = relations.begin();
	for (; it != relations.end(); ++it)
	{
		memcpy(&send->list[send->count], &it->second, sizeof(send->list[0]));
		send->count++;
	}

	pOwner->sendCmdToMe(send, sizeof(C::RtRelationList) + send->count * sizeof(send->list[0]));
	H::logger->info("发送好友列表，数量:%d", send->count);
}

C::t_RelationData* RelationM::getRelData(int64 uid)
{
	std::map<int64, C::t_RelationData>::iterator it = relations.find(uid);
	if (it != relations.end())
	{
		return &it->second;
	}
	return NULL;
}

int32 RelationM::getRelVal(int64 uid)
{
	C::t_RelationData* relData = getRelData(uid);
	if (relData)
	{
		return relData->rel;
	}
	return 0;
}

void RelationM::doCreateSession()
{




}


