#include "ProcWorldHandler.h"

#include "GameService.h"
#include "MysqlProtobufHelper.h"
#include "base/hmx_data.pb.h"
#include "curl.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/StreamCopier.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Query.h"
#include "Poco/JSON/PrintHandler.h"

#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPCredentials.h"
#include "Poco/Path.h"
#include "Poco/URI.h"


#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequestHandler.h"
#include "Poco/Net/HTTPRequestHandlerFactory.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/PartHandler.h"
#include "Poco/Net/MessageHeader.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/CountingStream.h"
#include "Poco/NullStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Exception.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include <iostream>


using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using Poco::Net::HTTPMessage;
using Poco::StreamCopier;
using Poco::Path;
using Poco::URI;
using Poco::Exception;

using namespace Poco::Dynamic;
using namespace Poco;

#define SKIP_PEER_VERIFICATION
#define SKIP_HOSTNAME_VERFICATION

ProcWorldHandler::ProcWorldHandler()
{

}

ProcWorldHandler::~ProcWorldHandler()
{

}

void ProcWorldHandler::reqWxPayOrderInfo(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize)
{
//	CurlParm* parm = new CurlParm();
//
//	std::stringstream ss;
//	ss << "appid=wxd678efh567hg6787";
//	ss << "&mch_id=1230000109";
//	ss << "&nonce_str=no_" << time(NULL);
//	ss << "&sign=" << "";
//	ss << "&body=" << "购买8张房卡";
//	ss << "&out_trade_no=t_" << time(NULL);
//	ss << "&total_fee=" << "6.00";
//	ss << "&spbill_create_ip=" << "192.168.16.100";
//	ss << "&notify_url=" << "";
//	ss << "&trade_type=APP";
//
//	std::string platUrl = "https://api.mch.weixin.qq.com/pay/unifiedorder";
//
//	const string postParams;
//
//	CURL *curl;
//	CURLcode res;
//	curl_global_init(CURL_GLOBAL_ALL);
//	curl = curl_easy_init();    // 初始化
//	if (curl)
//	{
//
//		curl_easy_setopt(curl, CURLOPT_POST, 1); // post req  
//		curl_easy_setopt(curl, CURLOPT_URL, platUrl.c_str());
//		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, ss.str().c_str()); // params  
//		curl_easy_setopt(curl, CURLOPT_USERAGENT, "Mozilla/5.0");
//		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 6);
//
//		//https 访问专用：start  
//#ifdef SKIP_PEER_VERIFICATION  
//		//跳过服务器SSL验证，不使用CA证书  
//		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
//		//如果不跳过SSL验证，则可指定一个CA证书目录  
//		//curl_easy_setopt(curl, CURLOPT_CAPATH, "this is ca ceat");  
//#endif  
//
//#ifdef SKIP_HOSTNAME_VERFICATION  
//		//验证服务器端发送的证书，默认是 2(高)，1（中），0（禁用）  
//		curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
//#endif  
//		//https 访问专用：end  
//
//		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &onPayResp);
//		curl_easy_setopt(curl, CURLOPT_WRITEDATA, parm);
//		res = curl_easy_perform(curl);   // 执行
//		curl_easy_cleanup(curl);
//		if (res == CURLE_OPERATION_TIMEDOUT)
//		{
//			fprintf(stderr, "%s\n", curl_easy_strerror(res));
//			::msg_maj::SDKTokenResp proRep;
//			proRep.set_result(::msg_maj::PLAT_REQ_TIMEOUT);
//			pSession->sendMsgProto(::comdef::msg_login, ::msg_maj::sdk_token_resp, proRep);
//		}
//		else if(res != CURLE_OK)
//		{
//			ASSERT(0);
//		}
//		else
//		{
//
//		}
//	}
//	curl_global_cleanup();

//	std::stringstream ss;
//	ss << "appid=wxd678efh567hg6787";
//	ss << "&mch_id=1230000109";
//	ss << "&nonce_str=no_" << time(NULL);
//	ss << "&sign=" << "";
//	ss << "&body=" << "购买8张房卡";
//	ss << "&out_trade_no=t_" << time(NULL);
//	ss << "&total_fee=" << "6.00";
//	ss << "&spbill_create_ip=" << "192.168.16.100";
//	ss << "&notify_url=" << "";
//	ss << "&trade_type=APP";
//
//	std::string platUrl = "https://api.mch.weixin.qq.com/pay/unifiedorder";

	Poco::URI url("http://api.mch.weixin.qq.com/pay/unifiedorder");
	HTTPClientSession session(url.getHost(), url.getPort());
	HTTPRequest request(HTTPRequest::HTTP_POST, url.getPath(), HTTPRequest::HTTP_1_1);
	HTMLForm form;
	form.add("appid", "wxd678efh567hg6787");
	form.add("mch_id", "1230000109");
	form.add("nonce_str", "5555");
	form.add("sign", "1230000109");
	form.add("body", "wxd678efh567hg6787");
	form.add("out_trade_no", "wxd678efh567hg6787");
	form.add("total_fee", "1230000109");
	form.add("spbill_create_ip", "192.168.16.100");
	form.add("notify_url", "http://www.queyiyouxi.com/pay");
	form.add("trade_type", "APP");

	form.prepareSubmit(request);
	form.write(session.sendRequest(request));
	Poco::Net::HTTPResponse res;
	std::istream & is = session.receiveResponse(res);
	StreamCopier::copyStream(is, std::cout);

}

size_t onPayResp(void *buffer, size_t size, size_t nmemb, void *parm)
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
		return dataLength;
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
		return dataLength;
	}

	return dataLength;

}

