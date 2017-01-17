#include "Client_PCH.h"
#include "PlayerMgr.h"


PlayerMgr::PlayerMgr()
{

}

PlayerMgr::~PlayerMgr()
{

}

Player* PlayerMgr::CreateObj()
{
	return objpool.CreateObj();
}

void PlayerMgr::DestoryObj(Player* obj)
{
	objpool.DestroyObj(obj);
}

Player* PlayerMgr::get(int64 id)
{
	return (Player*)zEntryMgr::getEntryByID(id);
}

bool PlayerMgr::add(Player* obj)
{
	return zEntryMgr::addEntry(obj);
}

void PlayerMgr::remove(Player* obj)
{
	zEntryMgr::removeEntry(obj);
}

void PlayerMgr::Update(const zTaskTimer* timer)
{
	struct MyStruct : public execEntry<Player>
	{
		MyStruct(const zTaskTimer* _timer):timer(_timer)
		{
		}
		virtual bool exec(Player *entry)
		{
			entry->Update(timer);
			return true;
		}
		const zTaskTimer* timer;
	};

	MyStruct exec(timer);
	zEntryMgr::execEveryEntry(exec);
}
