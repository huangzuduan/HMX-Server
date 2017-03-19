#ifndef __RELATION_H_
#define __RELATION_H_

#include "character.pb.h"
#include "CommandS.h"

class SceneUser;

//typedef std::map<int64, S::t_RelChatMsg, std::greater<int64> > ChatMsgMapType;

/*
 *	单个好友关系
 *
 */
class Relation : public zEntry
{
	friend class RelationM;
public:
	Relation();
	S::t_RelChatMsg* getChatMsg(int64 msgid);
	void addChatMsg(int64 msgid,S::t_RelChatMsg* msg);

private:

	int8 rel;//0陌生人,1申请人,2好友,3黑名单
	int32 createtime;	//创建时间 
	int32 dealreltime;	//

	std::map<int64, S::t_RelChatMsg, std::greater<int64> > chatmsgs;
};

/*
	社会关系
	聊天频道
 */
class RelationM : protected zEntryMgr<zEntryID>
{
public: 
	RelationM(SceneUser* user);
	~RelationM();
	void serialize(::protobuf::RelationProto& proto);
	void unserialize(const ::protobuf::RelationProto& proto);

	Relation* get(int64 id);
	bool add(Relation* obj);
	void remove(Relation* obj);

	bool doAddRel(int64 uid,const char* name,int32 rel);
	bool doRemoveRel(int64 uid);
	void sendAllRelList();

	C::t_RelationData* getRelData(int64 uid);
	int32 getRelVal(int64 uid);

	// channel 
	void doCreateSession();

private:

	SceneUser* pOwner;
	std::map<int64, C::t_RelationData> relations;
};



#endif

