#include "PlayerMgr.h"

PlayerMgr::PlayerMgr()
{

}

PlayerMgr::~PlayerMgr()
{

}

Player* PlayerMgr::CreateObj(zSession* _session)
{
	return objpool.CreateObj(_session);
}

void PlayerMgr::DestoryObj(Player* obj)
{
	objpool.DestroyObj(obj);
}

Player* PlayerMgr::get(int64_t id)
{
	return (Player*)zEntryMgr< zEntryID<0> >::getEntryByID(id);
}

bool PlayerMgr::add(Player* obj)
{
	return zEntryMgr< zEntryID<0> >::addEntry(obj);
}

void PlayerMgr::remove(Player* obj)
{
	zEntryMgr< zEntryID<0> >::removeEntry(obj);
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
	zEntryMgr< zEntryID<0> >::execEveryEntry(exec);
}
