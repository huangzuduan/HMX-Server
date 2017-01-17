#include "GameServer_PCH.h"
#include "ObjectManager.h"
#include "SceneUser.h"
#include "Object.h"


ObjectManager::ObjectManager(SceneUser* _u):u(_u)
{
	nCapacity = 0;
	nUseCapacity = 0;
}

ObjectManager::~ObjectManager()
{

}

bool ObjectManager::Serialize(::protobuf::Itemslots& proto)
{
	proto.set_char_id(u->GetUid());
	proto.set_capacity(nCapacity);
	proto.set_usecapacity(nUseCapacity);

	::protobuf::ItemBinaryData* binData = proto.mutable_binary_data();
	struct MyStruct : public execEntry<qObject>
	{
		::protobuf::ItemBinaryData* bin_item;
		MyStruct(::protobuf::ItemBinaryData* _bin_item) :bin_item(_bin_item)
		{

		}

		bool exec(qObject *entry)
		{
			::protobuf::ItemInfo* itemInfo = bin_item->add_items();
			itemInfo->set_index(entry->id);
			itemInfo->set_itemid(entry->itemID);
			itemInfo->set_itemnum(entry->itemNum);
			itemInfo->set_uniqueid(entry->tempid);
			return true;
		}
	};

	MyStruct myExec(binData);
	execEveryObject(myExec);

	return true;
}

void ObjectManager::UnSerialize(const ::protobuf::Itemslots& proto)
{
	nCapacity = proto.capacity();
	nUseCapacity = proto.usecapacity();
	const ::protobuf::ItemBinaryData& binData = proto.binary_data();
	for (int i = 0; i < binData.items_size(); ++i)
	{
		const ::protobuf::ItemInfo& item = binData.items(i);
		int32 itemid = item.itemid();
		zItemB* base = itembm.get(itemid);
		if (base == NULL) continue;

		qObject* obj = CreateObj(base);
		if (obj)
		{
			obj->id = item.index();
			obj->tempid = item.uniqueid();
			obj->itemID = item.itemid();
			obj->itemNum = item.itemnum();
			if (!addObject(obj))
			{
				DestroyObj(obj);
				Zebra::logger->error("Load addObject fail");
				ASSERT(0);
			}
		}
	}
	nCapacity += 3; //test
}

qObject* ObjectManager::CreateObj(zItemB* base)
{
	qObject* obj = objpool.CreateObj(base);
	if (!getUniqeID(obj->tempid))
	{
		DestroyObj(obj);
		return NULL;
	}
	return obj;
}

void ObjectManager::DestroyObj(qObject* obj)
{
	putUniqeID(obj->tempid);
	objpool.DestroyObj(obj);
}

qObject* ObjectManager::getObjectByUUID(DWORD uniqueID)
{
	return (qObject*)zItemManager::getItemEntryByTempID(uniqueID);
}

bool ObjectManager::getUniqeID(QWORD& tempid)
{
	tempid = u->uuid.GetUniqueID(UN_ITEM_OBJECT);;
	return true;
}

void ObjectManager::putUniqeID(const QWORD& tempid)
{

}

qObject* ObjectManager::getByIndex(DWORD id)
{
	return (qObject*)zItemManager::getItemEntryByID(id);
}


bool ObjectManager::addObject(qObject* obj)
{
	return zItemManager::addItem(obj);
}

void ObjectManager::removeObject(qObject* obj)
{
	zItemManager::removeItem(obj);
}

void ObjectManager::removeAllObject()
{
	// ±éÀú£¬Öð¸öÉ¾³ý 
}



