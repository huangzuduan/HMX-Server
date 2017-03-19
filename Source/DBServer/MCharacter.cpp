#include "DBServer_PCH.h"
#include "MCharacter.h"
#include "Memory.h"

DCollection<DUser>& MCharacter::getUserCollection()
{
	static dbCol columns[] =
	{
		{ "id", DB_QWORD, sizeof(int64) },
		{ "state",DB_BYTE, sizeof(int8) },
		{ "accid", DB_QWORD, sizeof(int64) },
		{ "name",DB_STR,MAX_NAMESIZE + 1 },
		{ "status",DB_BYTE, sizeof(int8) },
		{ "level",DB_DWORD, sizeof(int16) },
		{ "sceneid",DB_DWORD, sizeof(int64) },
		{ "mapid",DB_DWORD, sizeof(int32) },
		{ NULL,0,0 }
	};
	return dbmem::Memory::data.getCollection<DUser>("USER", columns, "id");
}

DCollection<DRelation>& MCharacter::getRelationCollection()
{
	static dbCol columns[] =
	{
		{ "id", DB_QWORD, sizeof(int64) },
		{ "state",DB_BYTE, sizeof(int8) },
		{ "myuid", DB_QWORD, sizeof(int64) },
		{ "friuid",DB_QWORD, sizeof(int8) },
		{ "createtime",DB_DWORD, sizeof(int32) },
		{ "dealreltime",DB_DWORD, sizeof(int32) },
		{ NULL,0,0 }
	};
	return dbmem::Memory::data.getCollection<DRelation>("Relation", columns, "id");
}

DUser* MCharacter::getUser(int64 id)
{
	return getUserCollection().get(id);
}

DWORD MCharacter::getBinary(int64 uid,char* out)
{
	static dbCol columns[] =
	{
		{ "id", DB_QWORD, sizeof(int64) },
		{ "INFO",DB_BIN2,0 },
		{ NULL,0,0 }
	};

	static char buffer[10000];
	memset(buffer, 0, sizeof(buffer));
	char wheres[100];
	memset(wheres, 0, sizeof(wheres));
	sprintf(wheres, "`id`=%llu", uid);
	unsigned int ret = dbmem::Memory::data.getDB()->ExecSelectLimit("USER", columns, wheres, NULL, (unsigned char*)buffer);
	if (ret == 1)
	{

	}
	else
	{
		
		return 0;
	}


	DUserRecord* data = (DUserRecord*)buffer;
	int64 datauid = data->uid;
	int32 datasize = data->size;

	memcpy(out,&data->header, datasize);
	return datasize;

}

void MCharacter::getRelation(int64 uid, std::vector<DRelation*>& relList)
{
	getRelationCollection().getMap(uid, relList);
}

DRelation* MCharacter::getReltion(int64 uid, int64 id)
{
	return getRelationCollection().getMapOne(uid,id);
}

void MCharacter::putRelation(int64 uid, int64 id, DRelation* rel)
{

}



int32 MCharacter::writeBinary(char* out)
{
	//int32 dwSize = 0;
	//BinaryMember* pMember = (BinaryMember*)out;
	//for (BYTE type = BINARY_NORMAL; type < BINARY_MAX; ++type)
	//{
	//	pMember->type = type;
	//	pMember->size = 0;
	//	switch (type)
	//	{
	//	case BINARY_NORMAL:
	//	{
	//		::protobuf::Relation proto;
	//		// serialize(proto);
	//		pMember->size += proto.ByteSize();
	//		proto.SerializeToArray(pMember->data, pMember->size);
	//		
	//	}
	//	break;
	//	default:
	//		break;
	//	}

	//	if (pMember->size)
	//	{
	//		dwSize += sizeof(BinaryMember);
	//		dwSize += pMember->size;
	//		pMember = (BinaryMember*)(&pMember->data[pMember->size]);
	//	}
	//}
	return 0;
	
}

int32 MCharacter::readBinary(const char* data, const int size)
{

	return 0;
}

