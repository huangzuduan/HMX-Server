#include "GameServer_PCH.h"
#include "MyCounters.h"
#include "SceneUser.h"

MyCounters::MyCounters()
{
}

MyCounters::~MyCounters()
{
}

void MyCounters::serialize(::protobuf::CounterProto& proto)
{
	std::multimap<int32, zUtility::my_streble<int32, int32, int32> >::iterator it = counters.begin();
	std::multimap<int32, zUtility::my_streble<int32, int32, int32> >::iterator itEnd = counters.end();
	for (; it != itEnd; ++it)
	{
		::protobuf::Counter* counter = proto.add_counter();
		if (counter)
		{
			counter->set_itemid(it->first);
			counter->set_itemval(it->second.first);
			counter->set_starttime(it->second.second);
			counter->set_endtime(it->second.third);
		}
		else
		{
			return;
		}
	}
}

void MyCounters::unserialize(const ::protobuf::CounterProto& proto)
{
	counters.clear();
	for (int i = 0; i < proto.counter_size(); ++i)
	{
		const ::protobuf::Counter& info = proto.counter(i);
		counters.insert(std::make_pair(info.itemid(), zUtility::my_streble<int32, int32, int32>(info.itemval(), info.starttime(), info.endtime())));
	}
}

void MyCounters::Timer(int32 curTime)
{
	std::multimap<int32, zUtility::my_streble<int32, int32, int32> >::iterator it = counters.begin();
	std::multimap<int32, zUtility::my_streble<int32, int32, int32> >::iterator itEnd = counters.end();
	for (; it != itEnd;)
	{
		zUtility::my_streble<int32, int32, int32>& info = it->second;
		if (info.first < 1 || curTime < info.second || curTime > info.third)
		{
			counters.erase(it++);
		}
		else
		{
			++it;
		}
	}
}

void MyCounters::AddDay(int32 key, int32 val)
{
	AddBetween(key, val, H::timeTick->getDayStart(), H::timeTick->getDayStart() + 86399);
}

void MyCounters::SubDay(int32 key, int32 val)
{
	int32 todayStart = H::timeTick->getDayStart();
	int32 todayEnd = todayStart + 86399;
	SubBetween(key, val, H::timeTick->getDayStart(), H::timeTick->getDayStart() + 86399);
}

void MyCounters::AddWeek(int32 key, int32 val)
{

}

void MyCounters::SubWeek(int32 key, int32 val)
{

}

void MyCounters::AddMonth(int32 key, int32 val)
{

}

void MyCounters::SubMonth(int32 key, int32 val)
{

}

void MyCounters::AddBetween(int32 key, int32 val, int32 starttime, int32 endtime)
{
	std::multimap<int32, zUtility::my_streble<int32, int32, int32> >::iterator it = counters.lower_bound(key);
	if (it == counters.upper_bound(key))
	{
		counters.insert(std::make_pair(key, zUtility::make_my_streble(val, starttime, endtime)));
	}
	else
	{
		bool found = false;
		for (; it != counters.upper_bound(key); ++it)
		{
			if (it->second.second == starttime && it->second.third == endtime)
			{
				it->second.first += val;
				found = true;
			}
		}
		if (!found) counters.insert(std::make_pair(key, zUtility::make_my_streble(val, starttime, endtime)));
	}
}

void MyCounters::SubBetween(int32 key, int32 val, int32 starttime, int32 endtime)
{
	int32 lastVal = val;
	std::multimap<int32, zUtility::my_streble<int32, int32, int32> >::iterator it = counters.lower_bound(key);
	for (; it != counters.upper_bound(key); ++it)
	{
		if (it->second.second == starttime && it->second.third == endtime)
		{
			if (it->second.first >= lastVal)
			{
				it->second.first -= lastVal;
				lastVal = 0;
			}
			else
			{
				lastVal -= it->second.first;
				it->second.first = 0;
			}
		}
		if (lastVal < 1) break;
	}
}

/* 当前时间的计数 */
int32 MyCounters::GetCounter(int32 key)
{
	int32 total = 0;
	int32 nowTime = H::timeTick->now();
	std::multimap<int32, zUtility::my_streble<int32, int32, int32> >::iterator it = counters.lower_bound(key);
	std::multimap<int32, zUtility::my_streble<int32, int32, int32> >::iterator itEnd = counters.upper_bound(key);
	for (; it != itEnd;++it)
	{
		if (it->second.second <= nowTime && it->second.third >= nowTime)
		{
			total += it->second.first;
		}
	}
	return total;
}

