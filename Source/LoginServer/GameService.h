#ifndef __GAME_SERVICE_H_
#define __GAME_SERVICE_H_

#include "SrvIncludes.h"
#include "DBConnection.h"

class AccountWxMgr;

class GameService : public zNetSerivce, public Single<GameService>
{
protected:
	friend class Single<GameService>;
	GameService();
	~GameService();
	virtual bool init();
	virtual bool run();
	virtual void finaly();

	virtual bool doBindServer(const ::config::SerivceInfo& info);
	virtual bool doWebServer(const ::config::SerivceInfo& info);
	virtual bool doConnectServer(const ::config::SerivceInfo& info);
	virtual boost::asio::io_service* GetIoService();

	void netioUpdate(const zTaskTimer* timer);
	
	
public:

	inline AccountWxMgr* getAccountMgr() { return mAccountMgr; }
	inline zSessionMgr* PlayerSessMgr() const { return mPlayerSessMgr; }
	inline void SetIsBrepairing(bool status) { mIsBrepairing = status; };
	inline bool GetIsBrepairing() const { return mIsBrepairing; }

	void SendToWs(uint16_t cmd, uint16_t cmdType, const ::google::protobuf::Message& proto);
	void SendToWs(uint16_t cmd, uint16_t cmdType, uint64_t clientSessID, uint32_t fepServerID, const ::google::protobuf::Message& proto);
	void SendToDp(uint16_t cmd, uint16_t cmdType, const ::google::protobuf::Message& proto);
	void SendToDp(uint16_t cmd, uint16_t cmdType, uint64_t clientSessID, uint32_t fepServerID, const ::google::protobuf::Message& proto);

private:

	zSessionMgr* mPlayerSessMgr;

	CWebServer*	m_pWebServer;
	AccountWxMgr*	mAccountMgr;

	bool			mIsBrepairing;
	
};


#endif
