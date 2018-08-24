#ifndef __OFFLINE_USER_H_
#define __OFFLINE_USER_H_


#include "SrvEngine.h"
#include "base/hmx_data.pb.h"


/*
  静态缓存所有用户类
 */
class OfflineUser : public zEntry
{
public:
	OfflineUser(const ::msg_maj::RoleOff& proto);
	~OfflineUser();
	inline uint64_t GetID(){ return dataProto.id(); }
	inline uint64_t GetTempID(){ return _entry_tempid; }
	inline const std::string& GetName(){ return dataProto.nickname(); }
public:

	::msg_maj::RoleOff dataProto;

};

#endif

