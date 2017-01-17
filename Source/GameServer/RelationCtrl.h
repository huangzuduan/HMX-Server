#ifndef __RELATION_H_
#define __RELATION_H_

#include "character.pb.h"

class SceneUser;

/*
	社会关系
	聊天频道
 */
class Relation
{
public: 
	Relation(SceneUser* user);
	~Relation();
	void serialize(::protobuf::Relation& proto);
	void unserialize(const ::protobuf::Relation& proto);

	bool doAddRel(int64 uid,const char* name,int32 rel);
	bool doRemoveRel(int64 uid);
	void sendAllRelList();

	t_RelData* getRelData(int64 uid);
	int32 getRelVal(int64 uid);

	// channel 
	void doCreateSession();

private:

	SceneUser* pOwner;
	std::map<int64, t_RelData> relations;
};



#endif

