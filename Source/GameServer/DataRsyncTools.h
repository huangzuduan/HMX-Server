#ifndef __DATA_RSYNC_TOOLS_H_
#define __DATA_RSYNC_TOOLS_H_

#include "DataRsyncStruct.h"

struct NetMsgSS;
class zSession;

/*-------------------------------------------------------------------
 * @Brief : 即使保存数据到数据库，定时查询数据库，如有新数据，则进行
 *          处理，针对玩家可能在线或不在线或不在本场景服，
 *			又要更新他的数据（可延时一点或上线处理都可）
 *			如：充值保存，活动结束发奖励，邮件，个人聊天等
 *			scene->dp->database,dp->database->dp->scene
 * @Author:hzd 2015:12:11
 *------------------------------------------------------------------*/

/*-------------------------------------------------------------------
 * @Brief :所保存的表为指定类型共用表，如单一值（表），多条值（表）
 * 
 * @Author:hzd 2015:12:21
 *------------------------------------------------------------------*/


class DataRsyncTools : public Single<DataRsyncTools>
{
public:

	DataRsyncTools(zSession* pDbServer);

	void SavaMixItemNumber(EMixItemNumberType eType,int64 nValue);

	void SaveMixItemBinary(EMixItemBinaryType eType,const char* data,int32 nLen);

	int64 GetMixNumber(EMixItemNumberType eType);

	void GetMixNumber(EMixItemBinaryType eType,char* o_data);

private:

	zSession* m_pDbServer;

};

#endif


