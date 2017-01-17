#ifndef __RSYNC_TOOLS_H_
#define __RSYNC_TOOLS_H_

/*-------------------------------------------------------------------
 * @Brief : 同步工具类，即时保存到数据库，定时检查数据是否有更新，
 *			主动通知玩家有新信息
 * 
 * @Author:hzd 2015:12:22
 *------------------------------------------------------------------*/

#include "Includes.h"
#include "DataRsyncStruct.h"

class RsyncTools : public Single<RsyncTools>
{
public:
	RsyncTools(void);
	~RsyncTools(void);

	void LoadDb();

	void Update(int32 nSrvTime);

	void SaveMixItemNumber(int32 eType,int64 nValue);

	void SaveMixItemBinary(int32 eType,char* data,int32 nLen);

private:


	std::map<int32,int64> m_mapMixItemNumber;


	//std::map<int32,char*> m_mapMixItemNumber;

};


#endif

