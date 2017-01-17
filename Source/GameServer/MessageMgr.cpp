#include "GameServer_PCH.h"
#include "MessageMgr.h"


MessageMgr::MessageMgr(SceneUser* u):user(u)
{

}


MessageMgr::~MessageMgr()
{
}

//bool MessageMgr::Serialize(::protobuf::MyChatMsg& proto)
//{
//	
//	return true;
//}
//
//void MessageMgr::UnSerialize(const ::protobuf::MyChatMsg& proto)
//{
//
//}

zMessage* MessageMgr::CreateObj()
{
	return objpool.CreateObj();
}

void MessageMgr::DestroyObj(zMessage* obj)
{
	objpool.DestroyObj(obj);
}

bool MessageMgr::addMessage(zMessage* mess)
{
	return zEntryMgr::addEntry(mess);
}

void MessageMgr::removeMessage(zMessage* mess)
{
	zEntryMgr::removeEntry(mess);
}

void MessageMgr::removeMessageAll()
{

}

void MessageMgr::removeMessageBefore(int32 time)
{

}

zMessage* MessageMgr::getMessage(QWORD id)
{
	return (zMessage*)zEntryMgr::getEntryByID(id);
}

void MessageMgr::getMessageNearest(int num)
{

}

void MessageMgr::getMessageNearestFrom(int num, QWORD fromID)
{

}

void MessageMgr::getMessageFromTo(QWORD formID, QWORD toID)
{

}
