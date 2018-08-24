#include "SceneRoomMgr.h"
#include "SceneRoom.h"

SceneRoomMgr::SceneRoomMgr()
{
}

SceneRoomMgr::~SceneRoomMgr()
{
}

SceneRoom* SceneRoomMgr::addRoom(uint64_t room_id, const ::msg_maj::RoomInfo& proto)
{
	SceneRoom* obj = objpool.construct(proto);
	if (!zEntryMgr< zEntryID<0> >::addEntry(obj))
	{
		objpool.destroy(obj);
		return NULL;
	}
	return obj;
}

SceneRoom* SceneRoomMgr::getRoom(uint64_t room_id)
{
	return (SceneRoom*)zEntryMgr< zEntryID<0> >::getEntryByID(room_id);
}

void SceneRoomMgr::removeRoom(uint64_t room_id)
{
	SceneRoom* obj = getRoom(room_id);
	if (obj)
	{
		zEntryMgr< zEntryID<0> >::removeEntry(obj);
	}
}
