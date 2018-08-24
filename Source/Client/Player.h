#ifndef __CLIENT_PLAYER_H_
#define __CLIENT_PLAYER_H_

#include "NetClient.h"
#include "SrvEngine.h"

enum 
{
	MAX_CLIENT_COUNT = 1 ,
};


class Player : public zEntry
{
public:
	Player(zSession* _session);
	~Player();

	inline uint64_t GetID(){ return id; };
	inline uint64_t GetTempID() { return _entry_tempid; };
	inline const std::string& GetName() { return _entry_name; };

	void SendMsg(NetMsgSS* msg, int32_t nSize);
	void Update(const zTaskTimer* timer);

	void setCharList(const std::vector<int64_t>& arrCharID)
	{
		charCount = arrCharID.size();
		for (int32_t i = 0 ; i < charCount; ++i)
		{
			charIDList[i] = arrCharID[i];
		}	
	}

	int64_t getFirstCharID()
	{
		if(charCount)
		{
			return charIDList[0];
		}
		return 0;
	}

	void setSession(zSession* _session)
	{
		session = _session;
	}

public:
	uint64_t id;
	zSession* session;
	bool bChating; // ÊÇ·ñÔÚÁÄÌì 
	int64_t accid;	
	int32_t charCount;
	int64_t charIDList[MAX_ROLE_TYPE_COUNT];

	char keymd5[MAX_NAMESIZE + 1];
	int32_t keytime;

};



#endif
