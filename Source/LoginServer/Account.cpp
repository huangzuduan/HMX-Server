#include "LoginServer_PCH.h"
#include "Account.h"


Account::Account()
{
	bzero(password, sizeof(password));
	createtime = lastlogin = 0;
}


Account::~Account()
{
}

bool Account::loadDB()
{
	char buffer[MAX_USERDATASIZE];
	bzero(buffer,sizeof(buffer));
	acc::Record* ret = (acc::Record*)buffer;
	char wheres[100];
	bzero(wheres,sizeof(wheres));
	sprintf(wheres, "`ID`=%lld", this->id);
	int32 retsize = GameService::getMe().getDbMysql()->ExecSelectLimit("ACCOUNT", acc::fields, wheres, NULL, (unsigned char*)ret, 1);
	if (retsize < 1)
	{
		H::logger->error("加载帐号内存失败，找不到数据");
		return false;
	}

	if (strlen(ret->base.username) <= MAX_NAMESIZE)
	{
		strncpy(this->name, ret->base.username, MAX_NAMESIZE);
	}
	else
	{
		unsigned char nameMd5[MAX_NAMESIZE + 1];
		memset(nameMd5, 0, sizeof(nameMd5));
		EncryptMD5(nameMd5, (unsigned char*)password);
		nameMd5[MAX_NAMESIZE] = '\0';
		strncpy(this->name, (const char*)nameMd5, MAX_NAMESIZE);
	}

	strncpy(this->name, ret->base.username, MAX_NAMESIZE);
	strncpy(this->password, ret->base.password, MAX_NAMESIZE);

	this->createtime = ret->base.createtime;
	this->lastlogin = ret->base.lastlogin;

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

void Account::saveDB()
{
	acc::dbID sID;
	char buffer[MAX_USERDATASIZE];
	bzero(buffer, sizeof(buffer));
	acc::Record* ret = (acc::Record*)buffer;
	char wheres[100];
	bzero(wheres, sizeof(wheres));
	sprintf(wheres, "`ID`=%lld", this->id);

	ret->base.id = this->id;
	strncpy(ret->base.username, this->name, MAX_NAMESIZE);
	strncpy(ret->base.password, this->password, MAX_NAMESIZE);
	ret->base.createtime = this->createtime;
	ret->base.lastlogin = this->lastlogin;

	char* data = ret->header.data;
	ret->header.version = 0;
	ret->header.size = writeBinary(data);
	ret->size = sizeof(BinaryHeader) + ret->header.size;

	int32 retsize = GameService::getMe().getDbMysql()->ExecSelectLimit("ACCOUNT", acc::Id, wheres, NULL, (unsigned char*)&sID, 1);
	if (retsize == 1)
	{
		GameService::getMe().getDbMysql()->ExecUpdate("ACCOUNT", acc::fields, (const char*)ret, wheres);
	}
	else
	{
		GameService::getMe().getDbMysql()->ExecInsert("ACCOUNT", acc::fields, (const char*)ret);
	}

}

void Account::readBinary(const char* data, int32 len)
{
	if (len < sizeof(BinaryMember))
		return;

	const BinaryMember* pMember = (const BinaryMember*)data;
	while (pMember->type != BINARY_ACCOUNT_NULL && pMember->type < BINARY_ACCOUNT_MAX)
	{
		//switch (pMember->type)
		//{
		//case BINARY_USER_COUNTER:
		//{
		//	//::protobuf::CounterProto proto;


		//}
		//break;
		//case BINARY_USER_RELATION:
		//{

		//}
		//break;
		//}
		pMember = (const BinaryMember*)(&pMember->data[pMember->size]);
	}
}

int32 Account::writeBinary(char* data)
{
	int32 dwSize = 0;
	BinaryMember* item = (BinaryMember*)data;
	for (int type = BINARY_ACCOUNT_NULL + 1; type < BINARY_ACCOUNT_MAX; ++type)
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
	item->type = BINARY_ACCOUNT_NULL;
	item->size = 0;
	dwSize += sizeof(BinaryMember) + 0;

	return dwSize;
}

void Account::timer()
{


}

