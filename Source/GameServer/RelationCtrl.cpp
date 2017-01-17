#include "GameServer_PCH.h"
#include "RelationCtrl.h"
#include "SceneUserMgr.h"


Relation::Relation(SceneUser* user):pOwner(user)
{

}

Relation::~Relation()
{

}

void Relation::serialize(::protobuf::Relation& proto)
{
	std::map<int64, t_RelData>::const_iterator it = relations.begin();
	for (; it != relations.end(); ++it)
	{
		::protobuf::RelInfo* relInfo = proto.add_rels();
		if (relInfo)
		{
			relInfo->set_uid(it->second.uid);
			relInfo->set_rel(it->second.rel);
			relInfo->set_createtime(it->second.createtime);
			relInfo->set_dealreltime(it->second.dealreltime);
		}
	}
}

void Relation::unserialize(const ::protobuf::Relation& proto)
{
	for (int i = 0; i < proto.rels_size(); ++i)
	{
		const ::protobuf::RelInfo& relInfo = proto.rels(i);
		t_RelData relData;
		relData.uid = relInfo.uid();
		relData.rel = relInfo.rel();
		relData.createtime = relInfo.createtime();
		relData.dealreltime = relInfo.dealreltime();
		relations[relData.uid] = relData;
	}
}

bool Relation::doAddRel(int64 uid, const char* name, int32 rel)
{
	t_RelData* relData = getRelData(uid);
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
		t_RelData newRelData;
		newRelData.uid = uid;
		newRelData.rel = rel;
		strncpy(newRelData.name, name, MAX_NAMESIZE);
		newRelData.createtime = Zebra::timeTick->getNowTime();
		newRelData.dealreltime = Zebra::timeTick->getNowTime();
		relations.insert(std::make_pair(uid, newRelData));
		relData = &relations[uid];
	}

	S2CRelationUpdate send;
	memcpy(&send.rel, relData,sizeof(send.rel));

	pOwner->sendCmdToMe(&send, sizeof(send));

	return true;
}

bool Relation::doRemoveRel(int64 uid)
{
	std::map<int64, t_RelData>::iterator it = relations.find(uid);
	if (it != relations.end())
	{
		relations.erase(it);
		S2CRelationDelete send;
		send.uid = uid;
		pOwner->sendCmdToMe(&send, sizeof(send));
	}
	return true;
}

void Relation::sendAllRelList()
{
	BUFFER_CMD(S2CRelationList, send, MAX_BUFFERSIZE);
	send->count = 0;
	std::map<int64, t_RelData>::iterator it = relations.begin();
	for (; it != relations.end(); ++it)
	{
		memcpy(&send->list[send->count], &it->second, sizeof(send->list[0]));
		send->count++;
	}

	pOwner->sendCmdToMe(send, sizeof(S2CRelationList) + send->count * sizeof(send->list[0]));
	Zebra::logger->info("发送好友列表，数量:%d", send->count);
}

t_RelData* Relation::getRelData(int64 uid)
{
	std::map<int64, t_RelData>::iterator it = relations.find(uid);
	if (it != relations.end())
	{
		return &it->second;
	}
	return NULL;
}

int32 Relation::getRelVal(int64 uid)
{
	t_RelData* relData = getRelData(uid);
	if (relData)
	{
		return relData->rel;
	}
	return 0;
}

void Relation::doCreateSession()
{




}


