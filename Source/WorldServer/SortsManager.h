#ifndef __SORTS_MANAGER_H_
#define __SORTS_MANAGER_H_

#include "MySortTemplate.h"
#include "sorlists.pb.h"

/* 排行榜数据表，自增ID也是按UID结构，方便合服使用 */
enum MySortItem
{
	SORT_ITEM_LEVEL = 1,
	SORT_ITEM_POWER = 2,
	SORT_ITEM_MAX,
};

#pragma pack(push,1)

template<typename TKey>
struct SortKey
{
	int64 uid;
	char name[MAX_NAMESIZE + 1];
	SortKey()
	{
		uid = 0;
		memset(name,0,sizeof(name));
	}
	virtual bool Compare(const TKey& key) const = 0;
};


struct LevelSortKey : public SortKey<LevelSortKey>
{
	int32 nLevel;
	LevelSortKey()
	{
		nLevel = 0;
	}

	virtual bool Compare(const LevelSortKey& _key) const
	{
		return nLevel > _key.nLevel;
	}

};

struct LevelSortValue : public LevelSortKey
{
	int32 sortid;
	// 后续字段加在后面 

	LevelSortValue()
	{
		sortid = 0;
	}
};


#pragma pack(pop)

/*-------------------------------------------------------------------
 * @Brief : 排序管理器(只对容器中的数据进行排序)
 * 
 * @Author:hzd 2016:1:19
 *------------------------------------------------------------------*/
class SortsManager : public Single<SortsManager>
{
public:
	void Serialize(::protobuf::LevelTable& proto);
	void UnSerialize(const ::protobuf::LevelTable& proto);

	void LoadAllSorts();
	//void SaveToDB(MySortItem itemID);
	//void Update(MySortItem itemID, const SortKey& key, const SortValue& value);

private:
	friend class Single<SortsManager>;

	SortsManager(void):levels(SORT_ITEM_LEVEL," 等级排行榜 ", SORT_CYCLE_DAY, 100)
	{

	}

	~SortsManager(void)
	{
	}

private:

	MySortTemplate<LevelSortKey,LevelSortValue> levels;

};


#endif

