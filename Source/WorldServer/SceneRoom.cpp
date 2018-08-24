#include "SceneRoom.h"

SceneRoom::SceneRoom(const ::msg_maj::RoomInfo& proto):m_usRoomID(_entry_id),m_roomProtoData(proto)
{
	m_usRoomID = m_roomProtoData.room_id();
}

void SceneRoom::UpdateRoles(const std::vector< ::msg_maj::RoleInfo>& roles)
{
	m_vecRoleInfos.clear();
	m_vecRoleInfos.resize(roles.size());
	std::copy(roles.begin(), roles.end(), m_vecRoleInfos.begin());
}
