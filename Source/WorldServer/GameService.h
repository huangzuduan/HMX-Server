#ifndef __WORLD_SERVICE_H_
#define __WORLD_SERVICE_H_

#include "SrvEngine.h"
#include "Single.h"

class WorldUserMgr;
class OfflineUserMgr;
class MyHttpServer;
class MessageMgr;
class SceneRoomMgr;

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
	inline WorldUserMgr* GetWorldUserMgr(){ return mWorldUserMgr;}
	inline OfflineUserMgr* GetOfflineUserMgr(){ return mOfflineUserMgr;}
	inline MessageMgr* GetMessageMgr(){ return mMessageMgr;}
	inline SceneRoomMgr* GetSceneRoomMgr() { return mSceneRoomMgr; }

	int CheckMd5(int64_t accid, int32_t keytime, const char* keymd5);

private:

	WorldUserMgr*		mWorldUserMgr;
	OfflineUserMgr*		mOfflineUserMgr;

	MessageMgr*			mMessageMgr;
	MyHttpServer*		app;

	SceneRoomMgr*		mSceneRoomMgr;
	
};


#endif
