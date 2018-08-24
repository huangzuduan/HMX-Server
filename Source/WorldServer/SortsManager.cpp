#include "SortsManager.h"

void SortsManager::Serialize(::protobuf::LevelTable& proto)
{
	//proto.add_levels();
	std::vector<LevelSortValue> levelTop;
	levels.GetAllList(levelTop, 100);
	for (size_t i = 0; i < levelTop.size(); ++i)
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
	for (size_t i = 0; i < proto.levels_size(); ++i)
	{
		const ::protobuf::LevelRow& row = proto.levels(i);
		int64_t uid = row.uid();
		std::string name = row.name();

		LevelSortKey key;
		key.uid = uid;
		key.name = name.c_str();
		key.nLevel = row.level();

		LevelSortValue val;
		val.uid = uid;
		val.name = name;
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
