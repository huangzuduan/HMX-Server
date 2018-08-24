#ifndef __MY_SORT_TEMPLATE_H_
#define __MY_SORT_TEMPLATE_H_

#include "csCommon.h"

/*-------------------------------------------------------------------
 * @Brief : 这里需要打通与DB表相通，当DB启动后，需要加载DB的表的排序榜
 *			数据
 * @Author:hzd 2016:1:28
 *------------------------------------------------------------------*/

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

template<typename TSortKey>
struct SortCompareBase : public std::binary_function<TSortKey,TSortKey,bool>
{
public:
	SortCompareBase(){}
	~SortCompareBase(){}
	bool operator()(const TSortKey lSortKey, const TSortKey rSortKey) const
	{
		return lSortKey.Compare(rSortKey);
	}
};

// 排序类模板类 
template<typename TSortKey,typename TSortValue,typename TSortComparetor = SortCompareBase<TSortKey> >
class MySortTemplate
{
public:
	typedef std::multimap<TSortKey,TSortValue,TSortComparetor>	SortMultiMap;
	typedef typename SortMultiMap::iterator						SortMultiMapIter;
public:

	MySortTemplate(int32_t _itemid,const char* _name, int32_t _mCycle, int32_t _mCountMax)
		:itemid(_itemid)
		,mCycle(_mCycle)
		,mCountMax(_mCountMax)
		,mCurrSortList(mAllSortList[SORT_LIST_CUR])
		,mLastSortList(mAllSortList[SORT_LIST_LAST])
	{
		memcpy(name, _name, sizeof(name));
	};
	~MySortTemplate(void)
	{
		
	};


public:

	int32_t itemid;					/* 排行榜类型 */
	char name[MAX_NAME_LEN];		/* 排行榜名 */
	int32_t mCycle;					/* 周期 */
	int32_t mCountMax;				/* 入榜最大数 */	
	
	SortMultiMap& mCurrSortList;				/* 当前数据容器 */  
	SortMultiMap& mLastSortList;				/* 当前数据容器 */ 
	SortMultiMap mAllSortList[SORT_LIST_MAX];	/* 数据容器 */ 

public:

	inline void AddSort(const TSortKey& key,const TSortValue& value)
	{
		mCurrSortList.insert(std::make_pair(key,value));
	}

	inline void DelSort(const TSortKey& key)
	{
		SortMultiMapIter it = mCurrSortList.find(key);
		if(it != mCurrSortList.end())
		{
			mCurrSortList.erase(it);
		}
	}

	inline void UpdateSort(const TSortKey& key,const TSortValue& value)
	{
		SortMultiMapIter it = mCurrSortList.find(key);
		if(it != mCurrSortList.end())
		{
			it->second = value;
		}
	}

	inline void GetTopList(std::vector<TSortValue>& vecSort,uint32_t nNum = 100)
	{
		SortMultiMapIter it = mCurrSortList.begin();
		SortMultiMapIter itEnd = mCurrSortList.end();
		for (; it != itEnd && vecSort.size() < nNum;++it)
		{
			vecSort.push_back(it->second);
		}
	}

	inline void AddLastSort(const TSortKey& key, const TSortValue& value)
	{
		mLastSortList.insert(std::make_pair(key, value));
	}

	inline void GetLastTopList(std::vector<TSortValue>& vecSort, int32_t nNum = 100)
	{
		SortMultiMapIter it = mLastSortList.begin();
		SortMultiMapIter itEnd = mLastSortList.end();
		for (; it != itEnd && vecSort.size() < nNum; ++it)
		{
			vecSort.push_back(it->second);
		}
	}

	inline void GetAllList(std::vector<TSortValue>& vecSort, uint32_t nNum = 100 )
	{
		GetTopList(vecSort, nNum);
		GetLastTopList(vecSort, nNum);
	}

};

#endif

