#ifndef __MY_SORT_TEMPLATE_H_
#define __MY_SORT_TEMPLATE_H_

#include "SrvEngine.h"

#define MAX_NAMESIZE 32

enum // 周期分类 
{
	SORT_CYCLE_HOUR = 0,
	SORT_CYCLE_DAY,
	SORT_CYCLE_WEEK,
	SORT_CYCLE_MONTY,
};

enum // 存储分类 
{
	SORT_LIST_CUR = 0,
	SORT_LIST_LAST,
	SORT_LIST_MAX,
};

// 最大入榜排行条数 
#define MAX_RANK_NUM 100

template<typename TSortKey>
struct SortCompareBase : public std::binary_function<TSortKey, TSortKey, bool>
{
public:
	SortCompareBase() {}
	~SortCompareBase() {}
	bool operator()(const TSortKey lSortKey, const TSortKey rSortKey) const
	{
		return lSortKey.Compare(rSortKey);
	}
};

// 排序类模板类 
template<typename TSortKey, typename TSortValue, typename TSortComparetor = SortCompareBase<TSortKey> >
class CMatchTemplate
{
public:
	typedef std::multimap<TSortKey, TSortValue, TSortComparetor>	SortMultiMap;
	typedef typename SortMultiMap::iterator							SortMultiMapIter;
public:

	CMatchTemplate(int32_t _nItemID, const char* _name, int32_t _nCycle, int32_t _nCountMax)
		:nItemID(_nItemID)
		,nCycle(_nCycle)
		,nCountMax(_nCountMax)
		,nCurrSortList(allSortList[SORT_LIST_CUR])
		,nLastSortList(allSortList[SORT_LIST_LAST])
	{
		memcpy(name, _name, sizeof(name));
	};

	~CMatchTemplate(void)
	{

	};

public:

	int32_t nItemID;				/* 排行榜类型 */
	char name[MAX_NAMESIZE + 1];	/* 排行榜名 */
	int32_t nCycle;					/* 周期 */
	int32_t nCountMax;				/* 入榜最大数 */

	SortMultiMap& nCurrSortList;				/* 当前数据容器 */
	SortMultiMap& nLastSortList;				/* 当前数据容器 */
	SortMultiMap allSortList[SORT_LIST_MAX];	/* 数据容器 */

	time_t startTime;	// 开始时间
	time_t endTime;		// 结束时间

	std::map<uint64_t, uint32_t> mapUserRoom; // 参数的人与参与比赛的房间

public:

	inline bool isHasMe(uint64_t userID) const
	{
		std::map<uint64_t, uint32_t>::const_iterator it = mapUserRoom.find(userID);
		if (it != mapUserRoom.end())
		{
			return true;
		}
		return false;
	}

	inline void LoadInit(time_t _starTime,int32_t lastTime)
	{
		startTime = _starTime;
		endTime = _starTime + lastTime;
	}

	inline void CheckRooms() // 是否超时房间限制
	{
		std::map<uint64_t, uint32_t>::const_iterator it = mapUserRoom.begin();
		for (; it != mapUserRoom.end(); ++it)
		{

		}
	}

	inline void AddSort(const TSortKey& key, const TSortValue& value)
	{
		UpdateSort(key,value);
	}

	inline bool DelSort(const TSortKey& key)
	{
		for (SortMultiMapIter it = nCurrSortList.begin(); it != nCurrSortList.end(); ++it)
		{
			if (it->first.uid == key.uid)
			{
				nCurrSortList.erase(it);
				return true;
			}
		}
		return false;
	}

	inline void UpdateSort(const TSortKey& key, const TSortValue& value)
	{
		DelSort(key);
		if (key.value > 0)
		{
			nCurrSortList.insert(std::make_pair(key, value));
		}	
	}

	inline void GetTopList(std::vector<TSortValue>& vecSort, int32_t nNum)
	{
		SortMultiMapIter it = nCurrSortList.begin();
		for (int32_t i = 1; it != nCurrSortList.end() && vecSort.size() < nNum && i <= MAX_RANK_NUM; ++it,++i)
		{
			it->second.sort = i;
			vecSort.push_back(it->second);
		}
	}

	inline void AddLastSort(const TSortKey& key, const TSortValue& value)
	{
		nLastSortList.insert(std::make_pair(key, value));
	}

	inline const TSortValue* FindSortValue(int64_t uid)
	{
		SortMultiMapIter it = nCurrSortList.begin();
		for (int32_t i = 1; it != nCurrSortList.end() && i <= MAX_RANK_NUM; ++it, ++i)
		{
			if (it->first.uid == uid)
			{
				it->second.sort = i;
				return &it->second;
			}
		}
		return NULL;
	}

	inline void GetLastTopList(std::vector<TSortValue>& vecSort, int32_t nNum = 10)
	{
		for (SortMultiMapIter it = nLastSortList.begin(); it != nLastSortList.end() && vecSort.size() < nNum; ++it)
		{
			vecSort.push_back(it->second);
		}
	}

	inline void GetAllList(std::vector<TSortValue>& vecSort, int32_t nNum = 10)
	{
		GetTopList(vecSort, nNum);
		GetLastTopList(vecSort, nNum);
	}

	// 对数据进行翻转
	inline void TurnLast()
	{
		nLastSortList.clear();
		for (SortMultiMapIter it = nCurrSortList.begin(); it != nCurrSortList.end(); ++it)
		{
			it->second.type = 1; 
			nLastSortList.insert(std::make_pair(it->first,it->second));
		}
		nCurrSortList.clear();
	}

};

#endif

