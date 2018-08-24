#ifndef _SCENE_ROOM_H_
#define _SCENE_ROOM_H_

#include "SrvEngine.h"
#include "Global.hpp"

class SceneRoom : public zEntry
{
public:
	SceneRoom(const ::msg_maj::RoomInfo& proto);
	~SceneRoom() {}
	virtual inline uint64_t GetID(){ return _entry_id; }
	virtual inline uint64_t GetTempID() { return _entry_tempid; }
	virtual inline const std::string& GetName(){ return _entry_name; }

	inline uint64_t GetRoomID() const { return m_usRoomID; }
	inline uint32_t GetCurPerson() const { return m_vecRoleInfos.size(); };
	inline uint32_t GetTotalPerson() const { return 4; };

	void UpdateRoles(const std::vector< ::msg_maj::RoleInfo>& roles);

private:
	uint64_t&							m_usRoomID;
	::msg_maj::RoomInfo				m_roomProtoData;
	std::vector< ::msg_maj::RoleInfo>	m_vecRoleInfos;
};

#endif

