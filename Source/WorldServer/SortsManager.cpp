#include "WorldServer_PCH.h"
#include "SortsManager.h"
#include "Utility.h"

void SortsManager::Serialize(::protobuf::LevelTable& proto)
{
	//proto.add_levels();
	std::vector<LevelSortValue> levelTop;
	levels.GetAllList(levelTop, 100);
	for (int i = 0; i < levelTop.size(); ++i)
	{
		LevelSortValue& item = levelTop[i];
		::protobuf::LevelRow* row = proto.add_levels();
		if(row == NULL) continue;
		row->set_sortid(item.sortid);
		row->set_uid(item.uid);
		row->set_name(item.name);
		row->set_level(item.nLevel);
	}
	
}

void SortsManager::UnSerialize(const ::protobuf::LevelTable& proto)
{
	for (int i = 0; i < proto.levels_size(); ++i)
	{
		const ::protobuf::LevelRow& row = proto.levels(i);
		int64 uid = row.uid();
		string name = row.name();

		LevelSortKey key;
		key.uid = uid;
		strncpy(key.name, name.c_str(), MAX_NAMESIZE);
		key.nLevel = row.level();

		LevelSortValue val;
		val.uid = uid;
		strncpy(val.name, name.c_str(), MAX_NAMESIZE);
		val.nLevel = row.level();
		val.sortid = row.sortid();
		val.nLevel = row.level();
		levels.AddSort(key, val);
	}
}


void SortsManager::LoadAllSorts()
{

}
//
//void SortsManager::SaveToDB(MySortItem itemID)
//{
//	switch (itemID)
//	{
//	case SORT_ITEM_LEVEL:
//	{
//		::protobuf::LevelTable proto;
//		Serialize(proto);
//	}
//	break;
//	case SORT_ITEM_POWER:
//		break;
//	case SORT_ITEM_MAX:
//		break;
//	default:
//		break;
//	}
//
//
//
//
//}
//
//
//void SortsManager::Update(MySortItem itemID, const SortKeyBase& key, const SortValueBase& value)
//{
//	switch (itemID)
//	{
//	case SORT_ITEM_LEVEL:
//		levels.UpdateSort((LevelSortKey&)key, (LevelSortValue&)value);
//		break;
//	case SORT_ITEM_MAX:
//		break;
//	default:
//		break;
//	}
//	SaveToDB(itemID);
//}
