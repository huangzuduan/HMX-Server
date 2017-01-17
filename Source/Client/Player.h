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
	Player();
	~Player();

	int64 getUid() { return id; }

	void SendMsg(NetMsgSS* msg, int32 nSize);
	void Update(const zTaskTimer* timer);

	void setCharList(const std::vector<int64>& arrCharID)
	{
		charCount = arrCharID.size();
		for (int32 i = 0 ; i < charCount; ++i)
		{
			charIDList[i] = arrCharID[i];
		}	
	}

	int64 getFirstCharID()
	{
		if(charCount)
		{
			return charIDList[0];
		}
		return 0;
	}

public:

	zSession* session;
	bool bChating; // ÊÇ·ñÔÚÁÄÌì 
	int64 accid;	
	int32 charCount;
	int64 charIDList[MAX_ROLE_TYPE_COUNT];

	char keymd5[MAX_NAMESIZE + 1];
	int32 keytime;

};



#endif
