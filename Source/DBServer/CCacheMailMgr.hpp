#ifndef _CCACHE_MAIL_MGR_H_
#define _CCACHE_MAIL_MGR_H_

#include <boost/pool/object_pool.hpp>
#include "SrvEngine.h"

// 缓存延时处理时间(秒)

const int64_t g_unModifyDelayTime = 60;	// 更新延后时间秒
const int64_t g_unOfflineDelayTime = 600; // 内存生命周期时间,该值要大于g_unModifyDelayTime

class CCacheMail;

/*
 *
 * 邮件缓存管理器(uid)
 *
 */
class CCacheMailMgr : public zEntryMgr< zEntryID<0> >, public Singleton<CCacheMailMgr>
{
public:
	CCacheMailMgr();
	~CCacheMailMgr();

	bool AddMail(CCacheMail* mail);
	CCacheMail* GetByID(uint64_t id);
	void RemoveMail(CCacheMail* mail);

	bool GetByUid(uint64_t uid,std::vector<CCacheMail*>& vecMail);
	void AddQuery(uint64_t uid);
	void AddModify(uint64_t id);
	void AddOffline(uint64_t id);

	void CheckModify();
	void CheckOffline();

private:

	std::map<uint64_t, std::map<uint64_t, CCacheMail*, std::greater<uint64_t> > > mapUidRecords;
	std::set<uint64_t> setUidQuery; // 是否查询

	std::map<uint64_t,time_t> m_mapModifys;	// 有更新的邮件
	std::map<uint64_t,time_t> m_mapOfflines;// 下线的邮件

};

extern ::boost::object_pool<CCacheMail> g_objpoolCacheMail;

#endif // !_CCACHE_MAIL_MGR_H_


