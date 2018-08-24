#include "AccountWx.h"
#include "curl.h"

#include "Poco/JSON/Parser.h"
#include "Poco/JSON/ParseHandler.h"
#include "Poco/JSON/JSONException.h"
#include "Poco/StreamCopier.h"
#include "Poco/Dynamic/Var.h"
#include "Poco/JSON/Query.h"
#include "Poco/JSON/PrintHandler.h"

#include "GameService.h"

using namespace Poco::Dynamic;
using namespace Poco;

AccountWx::AccountWx(const ::data::AccountWxInfo& proto)
{
	m_firstLoginTime = time(NULL);
	m_lastUpdateTime = time(NULL);
	m_nestUpdateTime = time(NULL) + 3600;
	m_wxData.CopyFrom(proto);
}

AccountWx::~AccountWx()
{

}

void AccountWx::Update(const ::data::AccountWxInfo& proto)
{
	m_lastUpdateTime = time(NULL);
	m_nestUpdateTime = time(NULL) + 3600;
	m_wxData.CopyFrom(proto);
}

void AccountWx::Timer()
{
	if (time(NULL) >= m_nestUpdateTime)
	{
		// 访问web刷新
	}

	const zServerMgr* pSrvMgr = GameService::getMe().SrvSerivceMgr()->GetServerMgr(GameService::getMe().GetServerID());
	if (pSrvMgr == NULL)
	{
		H::logger->error("Not found zServerMgr");
		return;
	}

	std::string platUrl = pSrvMgr->GetPlatUrl();
	char destUrl[1024] = { 0 };
	sprintf(destUrl, "%s/refresh_token/4000/%s", platUrl.c_str(), m_wxData.wxtoken().c_str()); 

	CurlParm* parm = new CurlParm();
	//parm->conn = pSession;
	//parm->token = proto.token();
	//parm->sessionID = pMsg->clientSessID;

	CURL *curl;
	CURLcode res;
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();    // 初始化
	if (curl)
	{
		curl_easy_setopt(curl, CURLOPT_URL, destUrl);
		curl_easy_setopt(curl, CURLOPT_TIMEOUT, 3);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, &onTokenRefresh);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, parm);
		res = curl_easy_perform(curl);   // 执行
		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();
}

size_t onTokenRefresh(void *buffer, size_t size, size_t nmemb, void *parm)
{
	CurlParm* pParm = (CurlParm*)parm;
	if (NULL == pParm)
	{
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


	return 0;
}


