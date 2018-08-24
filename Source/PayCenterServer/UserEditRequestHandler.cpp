#include "UserEditRequestHandler.h"
#include "MyHttpServer.h"
#include "GameService.h"

UserEditRequestHandler::UserEditRequestHandler(MyHttpServer* httpServer) :_httpServer(httpServer)
{

}

void UserEditRequestHandler::handleRequest(HTTPServerRequest &req, HTTPServerResponse &resp)
{
	resp.setStatus(HTTPResponse::HTTP_OK);
	resp.setContentType("text/html");
	std::ostream& out = resp.send();

	std::map<std::string, std::string> params;
	_httpServer->getRequestArgs(req, params);

	int status = _httpServer->checkAuth(params);
	if (status != 0)
	{
		out << "{\"status\": " << status
			<< ",\"info\":\"Auth Fail!\"}";
		return;
	}

	uint64_t reqNo = 0;

	uint64_t userID = _httpServer->GetKeyValueInt("userid", params);
	uint32_t level = _httpServer->GetKeyValueInt("level", params);
	uint32_t roomcard = _httpServer->GetKeyValueInt("roomcard", params);
	uint64_t fromUID = _httpServer->GetKeyValueInt("from_uid", params);

	out << "{\"status\":"
		<< status
		<< ",\"info\":\"Success!\""
		<< "}";

	out.flush();

	cout << endl
		<< "Response sent for count="
		<< " and URI=" << req.getURI() << endl;

}