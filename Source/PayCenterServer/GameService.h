#ifndef __WORLD_SERVICE_H_
#define __WORLD_SERVICE_H_

#include "SrvEngine.h"
#include "DBConnection.h"
#include "Single.h"
#include "MyHTTPServer.h"

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
	virtual bool doConnectServer(const ::config::SerivceInfo& info);
	void netioUpdate(const zTaskTimer* timer);
	
	
public:
	virtual boost::asio::io_service* GetIoService();

private:

	MyHttpServer*		app;
	
};


#endif
