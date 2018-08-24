#ifndef __SCENES_SERVICE_H_
#define __SCENES_SERVICE_H_


#include "SrvEngine.h"
#include "SceneUserMgr.h"

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
	virtual bool doConnectServer(const ::config::SerivceInfo& info);
	
	void netioUpdate(const zTaskTimer* timer);
	

public:
	virtual boost::asio::io_service* GetIoService();
	inline SceneUserMgr* getSceneUserMgr(){	return mSceneUserMgr; }

	void SendToWs(uint16_t cmd, uint16_t cmdType, const ::google::protobuf::Message& proto);
	void SendToWs(uint16_t cmd, uint16_t cmdType, uint64_t clientSessID, uint32_t fepServerID, const ::google::protobuf::Message& proto);
	void SendToDp(uint16_t cmd, uint16_t cmdType, const ::google::protobuf::Message& proto);
	void SendToDp(uint16_t cmd, uint16_t cmdType, uint64_t clientSessID, uint32_t fepServerID, const ::google::protobuf::Message& proto);

private:

	SceneUserMgr*	mSceneUserMgr;
	
};


#endif
