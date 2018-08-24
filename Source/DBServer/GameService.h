#ifndef __SCENES_SERVICE_H_
#define __SCENES_SERVICE_H_

#include "Single.h"
#include "SrvEngine.h"
#include "DBConnection.h"

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
	virtual boost::asio::io_service* GetIoService() { return NULL; };

	void netioUpdate(const zTaskTimer* timer);
	

private:


};



#endif
