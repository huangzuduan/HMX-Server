#ifndef __ROOM_MANAGER_H_
#define __ROOM_MANAGER_H_

#include "SrvEngine.h"
#include "Global.hpp"

class SceneRoom;

class SceneRoomMgr : protected zEntryMgr< zEntryID<0> >
{
public:
	SceneRoomMgr();
	~SceneRoomMgr();

	SceneRoom* addRoom(uint64_t room_id,const ::msg_maj::RoomInfo& proto);
	SceneRoom* getRoom(uint64_t room_id);
	void removeRoom(uint64_t room_id);

	template <class RoomEntry>
	bool execEveryRoom(execEntry<RoomEntry> &exec)
	{
		return zEntryMgr<  zEntryID<0> >::execEveryEntry<>(exec);
	}

private:

	boost::object_pool<SceneRoom> objpool;

};


#endif

