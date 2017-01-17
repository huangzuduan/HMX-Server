#ifndef __UNIQUEL_H_
#define __UNIQUEL_H_

#include "character.pb.h" 

class SceneUser;

enum UniquieItem
{
	UN_ITEM_OBJECT = 1,
	UN_ITEM_CHATMSG = 2,
};

struct UniqueIDItem
{
	int32 itemID;
	int32 startID;
	int32 endID;
	int32 stepLength;
	int32 startCount;
	UniqueIDItem()
	{
		itemID = startID = endID = stepLength = startCount = 0;
	}
};


/*------------------------------------------------------------------
 *
 * @Brief : 玩家唯一ID管理器 
 *
 * @Author: hzd 
 * @File  : MyUnique.h
 * @Date  : 2016/01/08 00:46
 * @Copyright (c) 2016,hzd, All rights reserved.
 *-----------------------------------------------------------------*/
class MyUniqueID
{
public:
	MyUniqueID(SceneUser* _u);
	~MyUniqueID();

	void Serialize(::protobuf::MyUniqueID& proto);
	void UnSerialize(const ::protobuf::MyUniqueID& proto);

	int32 GetUniqueID(int32 itemID);

private:

	SceneUser* u;
	std::map<int32, UniqueIDItem> uuidMap;

};

#endif


