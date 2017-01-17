#include "GameServer_PCH.h"
#include "ScenesServer.h"
#include "SceneUser.h"
#include "Object.h"




void SceneUser::getAllItemSlots(std::vector<qObject*>& slots)
{
	struct MyStruct : public execEntry<qObject>
	{
		std::vector<qObject*>* __slots;
		MyStruct(std::vector<qObject*>* _slots) :__slots(_slots)
		{

		}
		bool exec(qObject *entry)
		{
			__slots->push_back(entry);
			return true;
		}
	};

	MyStruct myExec(&slots);
	objM.execEveryObject(myExec);
}

bool SceneUser::TryAddObject(int32 itemID, int32 itemNum)
{
	return AddObject(itemID,itemNum,false,true);
}

bool SceneUser::AddObject(int32 itemID, int32 itemNum, bool notify, bool isTry)
{
	zItemB* base = itembm.get(itemID);
	if (base == NULL) return false;

	qObject* obj = NULL;
	for (int32 i = 12; i < objM.getCapacity();++i)
	{
		qObject* checkObj = objM.getByIndex(i);
		if (checkObj != NULL) continue;
		
		if (isTry) return true;	

		obj = objM.CreateObj(base);
		if (obj)
		{
			obj->id = i;
			objM.getUniqeID(obj->tempid);
			obj->itemID = itemID;
			obj->itemNum = itemNum;
			if (!objM.addObject(obj))
			{
				objM.putUniqeID(obj->tempid);
				objM.DestroyObj(obj);
				Zebra::logger->error("Buy addObject fail");
				ASSERT(0);
				continue;
			}
		}
		break;
	}

	if (obj == NULL)
	{

		return false;
	}

	if (notify)
	{
		S2CItemSlotUpdate sendMsg;
		sendMsg.nCount = 1;
		sendMsg.items[0].nIndex = obj->id;
		sendMsg.items[0].nItemID = obj->itemID;
		sendMsg.items[0].nItemNum = obj->itemNum;
		sendCmdToMe(&sendMsg,sendMsg.GetPackLength());
	}

	return true;
}


bool SceneUser::TryUseObject(int32 uniqueID, int32 num)
{
	return UseObject(uniqueID,num,false,true);
}

bool SceneUser::UseObject(int32 uniqueID, int32 num, bool notify, bool isTry)
{
	DWORD tempid = uniqueID;
	qObject* obj = objM.getObjectByUUID(tempid);
	if (obj == NULL)
	{
		return false;
	}
	return UseObject(obj,num,notify,isTry);
}

bool SceneUser::UseObject(qObject* obj, int32 num, bool notify, bool isTry)
{
	switch (obj->base->mainType)
	{
	case zItemB::TYPE_ITEM: /* 普通道具 */
	{
		return UseItemObj(obj, num, notify, isTry);
	}
	break;
	case zItemB::TYPE_EQUIP:
	{

	}
	break;
	case zItemB::TYPE_QUEST:
	{

	}
	break;
	case zItemB::TYPE_PKING:
	{

	}
	break;
	}
	return false;
}

bool SceneUser::UseItemObj(qObject* obj, int32 num, bool notify, bool isTry)
{
	bool isUsePass = true;
	
	/* 判断功能 */ 

	for (int32 i= 0; i < 2; ++i)
	{
		if(!isUsePass) break;

		const zItemB::Effect& effect = obj->base->effect1;
		switch (effect.funcType)
		{
		case zItemB::FUNC_MONEY:
		{
			if (isTry)
			{
				isUsePass = isUsePass && true;
			}
			else
			{
				bool result = ExecEffectMoney(effect, num);
				if (!result)
				{
					Zebra::logger->error("Use Object Effect Error:%d", effect.funcType, num);
				}
			}
		}
		break;
		case zItemB::FUNC_EXP:
		{
			if (isTry)
			{
				
			}
			else
			{
				
			}
		}
		break;
		default:
			isUsePass = false;
			break;
		}
	}

	if (isTry)
	{
		return isUsePass;
	}
	else
	{
		int32 uniqueID = obj->tempid;
		int32 indexPos = obj->id;
		int32 lastNum = 0;
		if (obj->itemNum >= num)
		{
			obj->itemNum -= num;
		}
		else
		{
			obj->itemNum = 0;
		}

		lastNum = obj->itemNum;

		if (obj->itemNum < 1)
		{
			/* 删除道具，释放内存 */
			objM.removeObject(obj);
			objM.DestroyObj(obj);
		}

	    if (notify)
		{
			if (lastNum && obj)
			{
				S2CItemSlotUpdate sendMsg;
				sendMsg.nCount = 1;
				sendMsg.items[0].nUniqueID = obj->tempid;
				sendMsg.items[0].nItemID = obj->base->id;
				sendMsg.items[0].nItemNum = obj->itemNum;
				sendMsg.items[0].nIndex = obj->id;
				sendMsg.items[0].nLock = obj->nLock;
				sendCmdToMe(&sendMsg, sendMsg.GetPackLength());
			}
			else
			{
				S2CItemSlotDelete sendMsg;
				sendMsg.nCount = 1;
				sendMsg.nUniqueIDs[0] = uniqueID;
				sendCmdToMe(&sendMsg, sendMsg.GetPackLength());
			}
		}
	}
	return true;
}

bool SceneUser::UseEquip(qObject* obj, int32 num, bool notify, bool isTry)
{
	return false;
}

bool SceneUser::UseQuest(qObject* obj, int32 num, bool notify, bool isTry)
{
	return false;
}

bool SceneUser::UsePking(qObject* obj, int32 num, bool notify, bool isTry)
{
	return false;
}

bool SceneUser::ExecEffectMoney(const zItemB::Effect& effect, int32 num)
{
	//ValueType val;
	//switch (effect.funcID)
	//{
	//case zItemB::FUNC_ID_MONEY_GOLD:
	//{
	//	GetUserAttr(USER_ATTR_GOLD, val);
	//	val += effect.funcVal * num;
	//	SetUserAttr(USER_ATTR_GOLD, val);
	//	return true;
	//}
	//break;
	//case zItemB::FUNC_ID_MONEY_SILVER:
	//{
	//	GetUserAttr(USER_ATTR_SILVER, val);
	//	val += effect.funcVal * num;
	//	SetUserAttr(USER_ATTR_SILVER, val);
	//	return true;
	//}
	//break;
	//case zItemB::FUNC_ID_MONEY_COPPER:
	//{
	//	GetUserAttr(USER_ATTR_COPPER, val);
	//	val += effect.funcVal * num;
	//	SetUserAttr(USER_ATTR_COPPER, val);
	//	return true;
	//}
	//break;
	//default:
	//	break;
	//}

	return false;
}





