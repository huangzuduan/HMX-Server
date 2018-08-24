#ifndef _SendRoomCardRequestHandler_H_
#define _SendRoomCardRequestHandler_H_

#include "Poco/Net/HTTPRequestHandler.h"

class MyHttpServer;

using namespace Poco::Net;

enum RequestType
{
	eRequest_Type_None = 0,
	eSendRoomCard,
	eSendMail,
	eSendNotice,
	eIosCharge,
	eRoomInfoList,
	eMyRoom,
	eUserEdit,
	eExitGame,
	eReloadConfig,
	eSceneList,
};

class AdminRequestHandler : public HTTPRequestHandler
{
public:
	AdminRequestHandler(MyHttpServer* httpServer, RequestType queryType);
	virtual void handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp);
private:
	MyHttpServer* _httpServer;
	RequestType _queryType;
	int32_t reload_config_product_id;

private:

	void DoSendRoomCard(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoSendMail(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoSendNotice(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoIosCharge(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoRoomInfo(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoMyRoom(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoUserEdit(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoExitGame(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoReloadConfig(HTTPServerRequest &req, HTTPServerResponse &resp);
	void DoSceneList(HTTPServerRequest &req, HTTPServerResponse &resp);
};

#endif

