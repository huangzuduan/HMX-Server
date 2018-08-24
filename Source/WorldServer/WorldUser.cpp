#include "WorldUser.h"

WorldUser::WorldUser(const ::msg_maj::RoleWs& proto):m_usClientSessID(_entry_tempid)
{
	m_dataProto.CopyFrom(proto);
	m_fepSession = NULL;
	m_sceneSession = NULL;
	m_usRoomID = 0;
	m_usRoomSeat = 0;
	m_bDisconnect = false;
	m_bRobotPlaying = false;
	m_usHisConGames = 0;
	m_usHisMaxScore = 0;
}

WorldUser::~WorldUser()
{

}

void WorldUser::sendMsgToFep(uint16_t cmd, uint16_t cmdType, const ::google::protobuf::Message& proto)
{
	if (m_fepSession)
	{
		if (m_usClientSessID && m_fepSession)
		{
			m_fepSession->sendMsgProto(cmd, cmdType, m_usClientSessID, m_fepSession->GetRemoteServerID(), proto);
		}
		else
		{
			m_fepSession->sendMsgProto(cmd, cmdType, proto);
		}
	}
}

void WorldUser::sendMsgToSs(uint16_t cmd, uint16_t cmdType,const ::google::protobuf::Message& proto)
{
	if (m_sceneSession)
	{
		if (m_usClientSessID && m_fepSession)
		{
			m_sceneSession->sendMsgProto(cmd, cmdType, m_usClientSessID, m_fepSession->GetRemoteServerID(), proto);
		}
		else
		{
			m_sceneSession->sendMsgProto(cmd, cmdType, proto);
		}
	}
}

void WorldUser::refreshProxyServerList(const std::vector<int32_t>& serid_list)
{
	m_proxyServerList.clear();
	for (size_t i = 0; i < serid_list.size(); ++i)
	{
		m_proxyServerList.push_back(serid_list[i]);
	}
}

void WorldUser::UpdateRoleFromSs(const ::msg_maj::SyncRoleToWs& proto)
{
	m_usRoomID = proto.room_id();
	m_usRoomSeat = proto.room_seat();
	m_bDisconnect = proto.disconnect();
	m_bRobotPlaying = proto.robotplaying();
	m_usHisConGames = proto.hiscongames();
	m_usHisMaxScore = proto.hismaxscore();
}