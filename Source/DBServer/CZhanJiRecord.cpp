#include "CZhanJiRecord.hpp"

CZhanJiRecord::CZhanJiRecord(const ::msg_maj::HistoryRecordS& fromRecord): nRecordID(0), m_nPlayer1(0), m_nPlayer2(0), m_nPlayer3(0), m_nPlayer4(0), m_expireTime(0), m_bIsFinish(true)
{
	m_protoData.CopyFrom(fromRecord);
	this->nRecordID = m_protoData.record_id();
	for (int i = 0; i < m_protoData.role_info().role_list_size(); ++i)
	{
		const ::msg_maj::RoleInfoS& roleInfo = m_protoData.role_info().role_list(i);
		if (roleInfo.seat() == 0)
		{
			this->m_nPlayer1 = roleInfo.uid();
		}
		else if (roleInfo.seat() == 1)
		{
			this->m_nPlayer2 = roleInfo.uid();
		}
		else if (roleInfo.seat() == 2)
		{
			this->m_nPlayer3 = roleInfo.uid();
		}
		else if (roleInfo.seat() == 3)
		{
			this->m_nPlayer4 = roleInfo.uid();
		}
	}

	m_expireTime = m_protoData.time() + 30 * 86400L;
	
}

void CZhanJiRecord::AddInnRecord(const ::msg_maj::InnRecordS& innRecord, const ::msg_maj::InnReplayActionS& innReplay)
{
	m_protoData.mutable_innrecord()->add_inn_list()->CopyFrom(innRecord);
	m_protoData.mutable_inn_replay()->add_replay_list()->CopyFrom(innReplay);
}

bool CZhanJiRecord::IsExpire()
{
	return time(NULL) > m_expireTime;
}

void CZhanJiRecord::CountTotalScore()
{
	// 计算总分 
	std::map<uint32_t, ::msg_maj::SeatTotalScoreS> mapSeatInfo;
	const ::msg_maj::InnRecordListS& innList = m_protoData.innrecord();
	for (int i = 0; i < innList.inn_list_size(); ++i)
	{
		// 第几场
		const ::msg_maj::InnRecordS& innRow = innList.inn_list(i);

		for (int j = 0; j < innRow.seat_result_size(); ++j)
		{
			const ::msg_maj::GameResultSeat& seatInfo = innRow.seat_result(j);
			::msg_maj::SeatTotalScoreS& seatScore = mapSeatInfo[seatInfo.seat()];
			seatScore.set_seat_id(seatInfo.seat());
			seatScore.set_score(seatScore.score() + seatInfo.total_score());
		}
	}

	::msg_maj::SeatTotalS* seatTotalS = m_protoData.mutable_seat_total();
	if (seatTotalS)
	{
		seatTotalS->clear_score_list();
		for (std::map<uint32_t, ::msg_maj::SeatTotalScoreS>::iterator it = mapSeatInfo.begin(); it != mapSeatInfo.end(); ++it)
		{
			seatTotalS->add_score_list()->CopyFrom(it->second);
		}
	}
	
}

void CZhanJiRecord::ClearReplayList()
{
	m_protoData.clear_inn_replay();
}

