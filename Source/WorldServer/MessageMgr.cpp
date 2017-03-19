#include "WorldServer_PCH.h"
#include "MessageMgr.h"

zMessage::zMessage()
{

}

bool zMessage::loadDB()
{
	char buffer[MAX_USERDATASIZE];
	bzero(buffer, sizeof(buffer));
	msg::Record* ret = (msg::Record*)buffer;
	char wheres[100];
	bzero(wheres, sizeof(wheres));
	sprintf(wheres, "`ID`=%lld", this->id);
	int32 retsize = GameService::getMe().getDbMysql()->ExecSelectLimit("MESSAGE", msg::fields, wheres, NULL, (unsigned char*)ret, 1);
	if (retsize < 1)
	{
		H::logger->error("加载帐号内存失败，找不到数据");
		return false;
	}

	//this->createtime = ret->base.createtime;
	//this->lastlogin = ret->base.lastlogin;

	if (ret->size == sizeof(ret->header) + ret->header.size)
	{
		this->readBinary(ret->header.data, ret->header.size);
	}
	else
	{
		H::logger->error("数据出错,name=%s", this->name);
		ASSERT(0);
		return false;
	}
	return true;
}

void zMessage::saveDB()
{
	msg::dbID sID;
	char buffer[MAX_USERDATASIZE];
	bzero(buffer, sizeof(buffer));
	msg::Record* ret = (msg::Record*)buffer;
	char wheres[100];
	bzero(wheres, sizeof(wheres));
	sprintf(wheres, "`ID`=%lld", this->id);

	ret->base.id = this->id;
	//strncpy(ret->base.username, this->name, MAX_NAMESIZE);
	//strncpy(ret->base.password, this->password, MAX_NAMESIZE);
	//ret->base.createtime = this->createtime;
	//ret->base.lastlogin = this->lastlogin;

	char* data = ret->header.data;
	ret->header.version = 0;
	ret->header.size = writeBinary(data);
	ret->size = sizeof(BinaryHeader) + ret->header.size;

	int32 retsize = GameService::getMe().getDbMysql()->ExecSelectLimit("MESSAGE", msg::Id, wheres, NULL, (unsigned char*)&sID, 1);
	if (retsize == 1)
	{
		GameService::getMe().getDbMysql()->ExecUpdate("MESSAGE", msg::fields, (const char*)ret, wheres);
	}
	else
	{
		GameService::getMe().getDbMysql()->ExecInsert("MESSAGE", msg::fields, (const char*)ret);
	}
}

void zMessage::readBinary(const char* data, int32 len)
{
	if (len < sizeof(BinaryMember))
		return;

	const BinaryMember* pMember = (const BinaryMember*)data;
	while (pMember->type != BINARY_MESSAGE_NULL && pMember->type < BINARY_MESSAGE_MAX)
	{
		switch (pMember->type)
		{
			case BINARY_MESSAGE_CONENT:
			{
				//::protobuf::CounterProto proto;


			}
			break;
			case BINARY_MESSAGE_MARK:
			{

			}
			break;
		}
		pMember = (const BinaryMember*)(&pMember->data[pMember->size]);
	}
}

int32 zMessage::writeBinary(char* data)
{
	int32 dwSize = 0;
	BinaryMember* item = (BinaryMember*)data;
	for (int type = BINARY_MESSAGE_NULL + 1; type < BINARY_MESSAGE_MAX; ++type)
	{
		item->type = type;
		item->size = 0;
		switch (type)
		{
			//protobuf
			//serilaze
			//item->size += protobuf.ByteSize();
			//serilazetoarray
		}

		if (item->size)
		{
			dwSize += sizeof(BinaryMember);
			dwSize += item->size;
			item = (BinaryMember*)(&item->data[item->size]);
		}
	}

	item = (BinaryMember*)(&item->data[dwSize]);
	item->type = BINARY_MESSAGE_NULL;
	item->size = 0;
	dwSize += sizeof(BinaryMember) + 0;

	return dwSize;
}

bool zMessage::serialize(::protobuf::MsgConent& proto)
{

	return true;
}

void zMessage::unserialize(const ::protobuf::MsgConent& proto)
{

}

MessageMgr::MessageMgr()
{

}


MessageMgr::~MessageMgr()
{
}

void MessageMgr::loadDB()
{

}

void MessageMgr::doUserCmd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	switch (pMsg->protocol)
	{
		case C::RQ_LOOK_MESSAGE:
		{

		}
		break;
		case C::RQ_OPT_MESSAGE:
		{

		}
		break;
		break;
	}
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
