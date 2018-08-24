#include "WebMsgHandler.h"
#include "GameService.h"
#include "MysqlProtobufHelper.h"
#include "curl.h"
#include "AccountWxMgr.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/StreamCopier.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Query.h"
#include "Poco/JSON/PrintHandler.h"

using namespace Poco::Dynamic;
using namespace Poco;

// 在 fep 中 ，client的sessionID为socketID
WebMsgHandler::WebMsgHandler() :zMsgHandler(GameService::Instance())
{
	// to ls
#define REGISTER_LS_MESSAGE(cmd,cmdType,cls)\
	{\
	RegisterMessage(cmd,cmdType,sizeof(cls),boost::bind(&WebMsgHandler::ReqLogin, this, _1, _2,_3));\
	}
	
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::login_weixin_req, PbMsgWebSS);
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::login_account_req, PbMsgWebSS);
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::prelogin_account_req, PbMsgWebSS);
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::logout_req, PbMsgWebSS);
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::login_player_req, PbMsgWebSS);
	REGISTER_LS_MESSAGE(::comdef::msg_login, ::msg_maj::sdk_token_req, PbMsgWebSS);
	
#undef REGISTER_LS_MESSAGE

}


WebMsgHandler::~WebMsgHandler()
{
}

void WebMsgHandler::OnWebMsgEnter(CWebClient* client)
{
	H::logger->info("[网页玩家]连接成功！来自于:id=%d ip=%s", client->GetSessionID(), client->GetIP().c_str());
	zSession* pSession = GameService::getMe().PlayerSessMgr()->addWeb(client->GetSessionID(), client);
	if (pSession == NULL)
	{
		client->close();
		return;
	}
}


void WebMsgHandler::OnWebMsg(CWebClient* client, PbMsgWebSS* pMsg,int32_t nSize)
{
	zSession* pSession = GameService::getMe().PlayerSessMgr()->get(client->GetSessionID());
	if(pSession)
	{
		const MsgFunc* handler = GetMsgHandler(pMsg->protocol);
		if(handler == NULL)
		{
			H::logger->error("[网页玩家]找不该协议,cmd:%d,cmdType:%d,大小:%d", pMsg->cmd,pMsg->cmdType,nSize);
			GameService::getMe().PlayerSessMgr()->remove(pSession);
			client->close();
			return;
		}
		else
		{
			H::logger->info("[网页玩家]收到协议,cmd:%d,cmdType:%d", pMsg->cmd, pMsg->cmdType);
			(handler->handlerFun)(pSession, (PbMsgWebSS*)pMsg ,nSize);
		}
	}
	else
	{
		H::logger->error("[网页玩家]找不到该连接:%lld", client->GetSessionID());
		GameService::getMe().PlayerSessMgr()->remove(pSession);
		client->close();
	}
}

void WebMsgHandler::OnWebMsgExit(CWebClient* client)
{
	zSession* pSession = GameService::getMe().PlayerSessMgr()->get(client->GetSessionID());
	if (pSession)
	{
		GameService::getMe().PlayerSessMgr()->remove(pSession);
		return;
	}	
	H::logger->error("[网页玩家]连接断开:%d,IP:%s", client->GetSessionID(), client->GetIP().c_str());
}

// 发送到 ls 
void WebMsgHandler::ReqLogin(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize)
{
	MSG_MAKE_PLAYER_SESSID(pSession->GetID(),GameService::getMe().GetServerID(),pMsg,nSize);

	switch (pMsg->cmdType)
	{
	case ::msg_maj::sdk_token_req:
	{
		DoLoginToken(pSession,pMsg,nSize);
		break;
	}
	default:
		break;
	}
}



void WebMsgHandler::DoLoginToken(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
	::msg_maj::SDKTokenReq proto;
	proto.ParseFromArray(pMsg->data, pMsg->size);
	DUMP_PROTO_MSG(proto);

	const zServerMgr* pSrvMgr = GameService::getMe().SrvSerivceMgr()->GetServerMgr(GameService::getMe().GetServerID());
	if (pSrvMgr == NULL)
	{
		H::logger->error("Not found zServerMgr");
		ASSERT(0);
		return;
	}

	if (GameService::getMe().GetIsBrepairing())
	{
		::msg_maj::SDKTokenResp proRep;
		proRep.set_result(::msg_maj::PLAT_REQ_TIMEOUT);
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::sdk_token_resp, proRep);
		return;
	}

	JSON::Parser parser;
	Dynamic::Var result;
	parser.reset();

	result = parser.parse(proto.token());
	JSON::Object::Ptr pObj = result.extract<JSON::Object::Ptr>();
	std::stringstream ssKeyVal;
	for (JSON::Object::ValueMap::const_iterator it = pObj->begin(); it != pObj->end(); ++it)
	{
		ssKeyVal << it->first;
		ssKeyVal << "=";
		ssKeyVal << it->second.toString();
		ssKeyVal << "&";
	}

	std::string platUrl = pSrvMgr->GetPlatUrl();
	char destUrl[1024] = {0};
	sprintf(destUrl, "%s/checkTokenLogin/?%s", platUrl.c_str(), ssKeyVal.str().c_str());
	printf("=========ReqLoginInfo===== %s \n", destUrl);

	CurlParm* parm = new CurlParm();
	parm->conn = pSession;
	parm->token = proto.token();
	parm->sessionID = pMsg->clientSessID;

	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();    // 初始化
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, destUrl);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &onTokenLogin);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, parm);
		res = curl_easy_perform(curl);   // 执行
		curl_easy_cleanup(curl);
		if (res == CURLE_OPERATION_TIMEDOUT)
		{
			fprintf(stderr, "%s\n", curl_easy_strerror(res));
			::msg_maj::SDKTokenResp proRep;
			proRep.set_result(::msg_maj::PLAT_REQ_TIMEOUT);
			pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::sdk_token_resp, proRep);
		}
	}
	curl_global_cleanup();
}


size_t onTokenLogin(void *buffer, size_t size, size_t nmemb, void *parm)
{
	CurlParm* pParm = (CurlParm*)parm;
	if (NULL == pParm)
	{
		ASSERT(0);
		return 0;
	}

	int16_t dataLength = (size * nmemb);
	pParm->buff_times++;
	memcpy(&pParm->buffer[pParm->buff_length], (char*)buffer, dataLength);
	pParm->buff_length += dataLength;
	
	std::string jsonStrSrc((char*)pParm->buffer, pParm->buff_length);
	zSession* pSession = pParm->conn;
	std::string token = pParm->token;

	delete pParm;
	pParm = NULL;

	JSON::Parser parser;
	Dynamic::Var result;
	parser.reset();

	result = parser.parse(jsonStrSrc);
	JSON::Object::Ptr pObj = result.extract<JSON::Object::Ptr>();
	int status = atoi(pObj->get("status").toString().c_str());

	::msg_maj::SDKTokenResp proRep;
	if (status == 1)	// 根据参数判断，是否给于通过
	{
		proRep.set_result(::msg_maj::TOKEN_ERROR);
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::sdk_token_resp, proRep);
		return 0;
	}

	std::string gateIP = pObj->get("gateway_ip").toString();
	std::string gatePort = pObj->get("gateway_port").toString();
	std::string account = pObj->get("account").toString();
	std::string icon_add = pObj->get("icon_add").toString();

	if (strncmp(gateIP.c_str(), "0.0.0.0", 7) == 0)
	{
		zSession* pFep = GameService::getMe().SessionMgr()->getFep();
		if (pFep == NULL)
		{
			proRep.set_result(::msg_maj::DATA_EXCEPTION);
			pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::sdk_token_resp, proRep);
			return 0;
		}

		zServerReg* pFegReg = GameService::getMe().ServerRegMgr()->get(pFep->GetRemoteDataProto().serverid());
		if (pFegReg == NULL)
		{
			proRep.set_result(::msg_maj::DATA_EXCEPTION);
			pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::sdk_token_resp, proRep);
			return 0;
		}

		const std::vector< ::config::SerivceInfo>& serivceInfos = pFegReg->GetBroadSerivces();
		for (std::vector< ::config::SerivceInfo>::const_iterator it = serivceInfos.begin(); it != serivceInfos.end(); ++it)
		{
			if (STRNICMP(it->serivcename().c_str(), "server", 6) == 0)
			{
				if (STRNICMP(it->serivcefun().c_str(), "foruser", 7) == 0)
				{
					proRep.set_result(::msg_maj::SUCCESS);
					proRep.set_ip(it->serivceip());
					proRep.set_port(it->serivceport() + 1);

					break;
				}
			}
		}
	}
	else
	{
		proRep.set_result(::msg_maj::SUCCESS);
		proRep.set_ip(gateIP);
		proRep.set_port(atoi(gatePort.c_str()));
	}

	proRep.set_account(account);
	proRep.set_icon_add(icon_add);

	if (proRep.result() != ::msg_maj::SUCCESS)
	{
		pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::sdk_token_resp, proRep);
		return 0;
	}

	JSON::Object::Ptr pWxObj = pObj->getObject("wxdata");

	// 缓存验证通过的一些信息
	Dynamic::Var ret = pWxObj->get("errcode");
	if (ret.isEmpty())
	{
		::data::AccountWxInfo dataWx;
		dataWx.set_openid(pWxObj->getValue<std::string>("openid"));
		dataWx.set_nickname(pWxObj->getValue<std::string>("nickname"));
		dataWx.set_sex(pWxObj->getValue<int32_t>("sex"));
		dataWx.set_province(pWxObj->getValue<std::string>("province"));
		dataWx.set_city(pWxObj->getValue<std::string>("city"));
		dataWx.set_country(pWxObj->getValue<std::string>("country"));
		dataWx.set_headimgurl(pWxObj->getValue<std::string>("headimgurl"));
		dataWx.set_unionid(pWxObj->getValue<std::string>("unionid"));
		dataWx.set_ip(pSession->GetIP());
		GameService::Instance()->getAccountMgr()->LoginAccountWx(dataWx);
	}
	else //测试帐号
	{
		::data::AccountWxInfo dataWx;
		dataWx.set_openid(account);
		dataWx.set_nickname(account);
		dataWx.set_sex(0);
		dataWx.set_province("");
		dataWx.set_city("");
		dataWx.set_country("");
		dataWx.set_headimgurl("");
		dataWx.set_unionid(account);
		dataWx.set_ip(pSession->GetIP());
		GameService::Instance()->getAccountMgr()->LoginAccountWx(dataWx);
	}
	
	pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::sdk_token_resp, proRep);

	return 0;
}




