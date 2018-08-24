#ifndef __SCENES_SERVICE_H_
#define __SCENES_SERVICE_H_

#include "SrvEngine.h"
#include "Single.h"

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
	
	void netioUpdate(const zTaskTimer* timer);
	

public:

	virtual boost::asio::io_service* GetIoService();
	inline zSessionMgr* PlayerSessMgr() const { return mPlayerSessionMgr; }

private:

	zSessionMgr*	mPlayerSessionMgr;
	CWebServer*		m_pWebServer;
};


#endif
