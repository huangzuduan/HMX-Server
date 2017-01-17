#ifndef __OFFLINE_USER_H_
#define __OFFLINE_USER_H_

#include "Includes.h"
#include "character.pb.h"


/*
  静态缓存所有用户类
 */
class OfflineUser : public zEntry
{
public:
	OfflineUser();
	~OfflineUser();

	bool loadDB();

public:

	int16 level;
	int8 vip;
	int8 country;
	int32 teamid;

};

#endif

