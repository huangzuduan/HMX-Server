#ifndef __USER_MEMORY_MGR_H_
#define __USER_MEMORY_MGR_H_

#include "Includes.h"
#include "DbIncludes.h"

// 仅支持定长结构 

template<typename TData>
class DCollection : public zEntry
{
protected:

	typename typedef std::multimap<int64, TData*> KeyValueMap;
	typename typedef std::multimap<int64, TData*>::iterator KeyValueMapIter;

	int32			nowTime;					// 当时时间
	IDbBase*		dbConn;							// 数据库连接
	boost::mutex	mutex;						// 锁  
	char			keyName[MAX_NAMESIZE + 1];
	dbCol			columns[100];

	zObjPool<TData>	objpool;
	KeyValueMap	datas;			// 唯一集合 


public:

	DCollection(IDbBase* _dbConn, const char* _name, const dbCol* _dbCol, const char* _keyName)
	{
		dbConn = _dbConn;
		strncpy(name, _name, sizeof(name));
		strncpy(keyName, _keyName, sizeof(_keyName));
		const dbCol* tempDbCol = _dbCol;
		for (int i = 0; i < sizeof(columns) / sizeof(columns[0]); ++i)
		{
			if (tempDbCol->name)
			{
				memcpy(&columns[i], tempDbCol, sizeof(dbCol));
				tempDbCol++;
			}
			else
			{
				columns[i] = { NULL,0,0 };
				break;
			}
		}
	}

	inline void add(QWORD id, TData* data, bool saveDb = true)
	{
		if (data)
		{
			datas.insert(std::make_pair(id, data));
			if (saveDb)
			{
				data->state = 1;
				saveToDb(id, data);
			}
		}
	}

	inline TData* get(QWORD id)
	{
		KeyValueMapIter it = datas.lower_bound(id);
		if (it != datas.upper_bound(id))
		{
			return it->second;
		}

		if (!dbConn)
		{
			ASSERT(dbConn);
			return NULL;
		}

		TData* data = objpool.CreateObj();
		if (data)
		{
			char wheres[100];
			memset(wheres, 0, sizeof(wheres));
			sprintf(wheres, "`%s`=%llu", keyName, id);
			unsigned int ret = dbConn->ExecSelectLimit(name, columns, wheres, NULL, (unsigned char*)data);
			if (ret == 1)
			{
				add(id, data, false);
				return data;
			}
			else
			{
				objpool.DestroyObj(data);
			}
		}
		return NULL;
	}

	inline void getMap(QWORD multiid,std::vector<TData*>& vecData)
	{
		// 先查找内存 
		for (KeyValueMapIter it = datas.lower_bound(multiid); it != datas.upper_bound(multiid); ++it)
		{
			vecData.push_back(it->second);
		}

		// 如果内存不存在，则从数据库中加载 
		if (vecData.empty())
		{
			if (!dbConn)
			{
				ASSERT(dbConn);
				return ;
			}

			TData* dataList, *dataTmp;
			int ret = dbConn->ExecSelect(name, columns, NULL, NULL, (unsigned char**)&dataList);
			if (ret > 0)
			{
				for (int c = 0; c < ret; ++c)
				{
					dataTmp = &dataList[c];
					TData* obj = objpool.CreateObj();
					memcpy(obj, dataTmp, sizeof(TData));
					add(multiid, obj, false);
					vecData.push_back(obj);
				}
				SAFE_DELETE_VEC(dataList);
			}
		}
	}

	inline TData* getMapOne(QWORD multiid,QWORD keyid,DWORD keyoffset = 0)
	{
		std::vector<TData*> vecData;
		getMap(multiid, vecData);
		if (vecData.empty())
		{
			return NULL;
		}

		for (std::vector<TData*>::iterator it = vecData.begin(); it != vecData.end(); ++it)
		{
			QWORD keyidObj = 0;
			memcpy(&keyidObj,(unsigned char*)(*it) + keyoffset,sizeof(QWORD));
			if (keyidObj == keyid)
			{
				return *it;
			}
		}
		return NULL;
	}

	inline bool putMap(QWORD multiid, std::vector<TData*>& vecData,bool saveDb = true)
	{
		std::vector<TData*>::iterator it = vecData.begin();
		for (; it != vecData.end(); ++it)
		{
			if (!add(multiid, *it, saveDb))
			{
				return false;
			}
		}
		return true;
	}

	inline void Update(int32 _nowtime)
	{
		nowTime = _nowtime;
		mutex::scoped_lock cLock(mutex);
		
		// do somethings

		cLock.unlock();
	}

private:

	inline void saveToDb(QWORD _id,TData* data)
	{
		if (dbConn == NULL)
		{
			H::logger->warn("SaveNow Not Found UserData!");
			ASSERT(dbConn);
			return;
		}

		if (data->state == 1)
		{
			data->state = 0;
			dbConn->ExecInsert(name, columns, (const char*)data);
		}
		else if (data->state == 2)
		{
			data->state = 0;

			char wheres[100];
			memset(wheres, 0, sizeof(wheres));
			sprintf(wheres, "`%s`=%llu", keyName, _id);
			dbConn->ExecUpdate(name, columns, (const char*)data, wheres);
		}
		else if (data->state == 3)
		{
			data->state = 0;
			char wheres[100];
			memset(wheres, 0, sizeof(wheres));
			sprintf(wheres, "`%s`=%llu", keyName, _id);
			dbConn->ExecDelete(name, wheres);
		}
		else
		{
			//data->state = 0;
		}

	}

};


#endif

