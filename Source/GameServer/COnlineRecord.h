#ifndef __CONLINE_RECORD_H_
#define __CONLINE_RECORD_H_

#include "Global.hpp"
#include "FogsTimerService.hpp"

class COnlineRecord : public Singleton<COnlineRecord>
{
public:
	COnlineRecord();
	~COnlineRecord();

	void Init();
	void AddRoomcard(int32_t num);

private:

	void doRecord();

private:

	fogs::FogsTimer* m_pSaveDataTimer;

	uint32_t m_online_num;
	uint32_t m_roomcard_num;
	uint32_t m_inn_num;

};


#endif



