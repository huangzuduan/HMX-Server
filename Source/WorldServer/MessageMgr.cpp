#include "MessageMgr.h"
#include "GameService.h"


zMessage::zMessage()
{

}

MessageMgr::MessageMgr()
{

}


MessageMgr::~MessageMgr()
{
}


void MessageMgr::doUserCmd(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	
}


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
	return zEntryMgr< zEntryID<0> >::addEntry(mess);
}

void MessageMgr::removeMessage(zMessage* mess)
{
	zEntryMgr< zEntryID<0> >::removeEntry(mess);
}

void MessageMgr::removeMessageAll()
{

}

void MessageMgr::removeMessageBefore(int32_t time)
{

}

zMessage* MessageMgr::getMessage(QWORD id)
{
	return (zMessage*)zEntryMgr< zEntryID<0> >::getEntryByID(id);
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
