#include "GameServer_PCH.h"
#include "MyUniqueID.h"
#include "SceneUser.h"

MyUniqueID::MyUniqueID(SceneUser* _u):u(_u)
{

}

MyUniqueID::~MyUniqueID()
{
}

void MyUniqueID::Serialize(::protobuf::MyUniqueID& proto)
{

	std::map<int32, UniqueIDItem>::const_iterator it = uuidMap.begin();
	for (; it != uuidMap.end(); ++it)
	{
		::protobuf::UniqueIDItem* item = proto.add_uuids();
		if (item)
		{
			const UniqueIDItem& info = it->second;
			item->set_startid(info.startID);
			item->set_endid(info.endID);
			item->set_steplenght(info.stepLength);
			item->set_startcount(info.startCount);
		}
	}
	
}

void MyUniqueID::UnSerialize(const ::protobuf::MyUniqueID& proto)
{
	uuidMap.clear();
	for (unsigned int i = 0; i < proto.uuids_size(); ++i)
	{
		const ::protobuf::UniqueIDItem& info = proto.uuids(i);
		UniqueIDItem item;
		item.itemID = info.itemid();
		item.startID = info.startid();
		item.stepLength = info.steplenght();
		item.startCount = info.startcount();
		uuidMap.insert(std::make_pair(item.itemID,item));
	}
}

int32 MyUniqueID::GetUniqueID(int32 itemID)
{
	UniqueIDItem& item = uuidMap[itemID];
	if (item.endID == 0)
		item.endID = 1;

	if (item.startID * 100 / item.endID >= 80)
		item.endID += 100;

	if (item.startID >= item.endID)
		return 0;

	item.startID++;

	return item.startID;
}


