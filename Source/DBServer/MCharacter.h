#ifndef __MUSER_H_
#define __MUSER_H_

#include "Includes.h"
#include "Memory.h"
#include "Collection.h"

#pragma pack(push,1)

struct DUser
{
	int64 id;
	int8 state;
	int64 accid;
	char name[MAX_NAMESIZE + 1];
	int8 status;
	int16 level;
	int64 sceneid;
	int32 mapid;
	int32 size;
};

struct DRelation
{
	int64 id;
	int8 state;
	int64 myuid;
	int64 friuid;
	int32 rel;
	int32 createtime;
	int32 dealreltime;
};

struct DUserRecord
{
	int64 uid;
	int32 size;
	BinaryHeader header;
};

#pragma pack(pop)


/*
	内存管理器，自动从数据库获取，自动更新到数据，支持最大支持两层key结构，如(key1=>key2=>value)
	特别注意是：内存结构存取需要严格按第一次方法来进行（会根据第一次来构建分层结构）
	第一种:get(),put()
	第二种:getMap(); putMap();
	对于同一个表，不能两种同时用，只能使用其中一种
 */
class MCharacter : public Single<MCharacter>
{
public:

	DUser* getUser(int64 uid);
	DWORD getBinary(int64 uid, char* out);

	void getRelation(int64 uid, std::vector<DRelation*>& relList);
	DRelation* getReltion(int64 uid,int64 id);
	void putRelation(int64 uid, int64 id, DRelation* rel);

	int32 writeBinary(char* out);
	int32 readBinary(const char* data,const int size);
	
private:

	DCollection<DUser>& getUserCollection();
	DCollection<DRelation>& getRelationCollection();

private:

	bool isInited;

};

#endif


