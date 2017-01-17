#include "LoginServer_PCH.h"
#include "ProcFepHandler.h"
#include "NamesManager.h"



ProcFepHandler::ProcFepHandler(void)
{
}


ProcFepHandler::~ProcFepHandler(void)
{
}

void ProcFepHandler::RqAccountLogin(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{

	const C2LAccountLogin* packet = static_cast<const C2LAccountLogin*>(pMsg);

	// 检查字符串是否合法 TODO
	char wheres[100];
	bzero(wheres,sizeof(wheres));
	sprintf(wheres, "`username`='%s' AND `password`='%s'", packet->username, packet->password);

	const dbCol fields[] = 
	{
		{"id",DB_QWORD,sizeof(int64)},
		{NULL,0,0}
	};

#pragma pack(push,1)
	struct MyStruct
	{
		int64 id;
		MyStruct()
		{
			id = 0;
		}
	};
#pragma pack(pop)
	
	MyStruct data;
	int32 retsize = NetService::getMe().getDbMysql()->ExecSelectLimit("Account", fields, wheres, NULL, (unsigned char*)&data);
	if (retsize < 1)
	{
		Zebra::logger->warn("登录失败"); // 记录登录失败的次数，达到一定次数，则默认为暴力破解 
	}

	L2CAccLogin sendRet;
	sendRet.sessid = packet->sessid;
	sendRet.fepsid = packet->fepsid;
	sendRet.accid = data.id;
	sendRet.result = retsize == 1 ? 1 : 0;

	if (retsize == 1)
	{
		int32 nowTime = Zebra::timeTick->getNowTime();
		// md5(帐号+密钥+时间)
		std::ostringstream outstr;
		outstr << data.id;
		outstr << SERVERKEY;
		outstr << nowTime;
		unsigned char md5str[MAX_NAMESIZE + 1];
		memset(md5str, 0, sizeof(md5str));
		EncryptMD5(md5str, (unsigned char*)outstr.str().c_str());
		md5str[MAX_NAMESIZE] = '\0';

		strncpy(sendRet.keymd5, (const char*)md5str, MAX_NAMESIZE);
		
		sendRet.keytime = nowTime;

		Zebra::logger->info("生成密钥:%s", md5str);
	}

	pSession->sendMsg(&sendRet, sendRet.GetPackLength());

	Zebra::logger->info("%s登录%s",packet->username,(retsize == 1 ? "成功":"失败"));

	if (retsize)
	{
		// 发送加载角色列表返回给用户 
		L2WLoadList sendWs;
		sendWs.sessid = packet->sessid;
		sendWs.fepsid = packet->fepsid;
		sendWs.accid = data.id;
		NetService::getMe().getSessionMgr().sendToWs(&sendWs, sendWs.GetPackLength());
	}
}

void ProcFepHandler::RqRoleCreate(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	// 发送到db请求创建 
	//ClientSession* pClientSession = ClientSessionMgr::getMe().getSession(pMsg->clientSessionID);
	//ASSERT(pClientSession);

	//const C2LRoleCreate* packet = static_cast<const C2LRoleCreate*>(pMsg);

	//// 检查类型 
	//if(packet->nType <= E_ROLE_TYPE_NULL || packet->nType >= E_ROLE_TYPE_MAX)
	//{
	//	return ;
	//}

	//// 检查名字 
	//if(packet->arrName[MAX_NAME_LENGTH - 1] != '\0')
	//{
	//	return ;
	//}

	//// 名字长度限制 
	//if (strlen(packet->arrName) < 6 || strlen(packet->arrName) > 30)
	//{
	//	return;
	//}

	//L2DRoleCreate sMsg;
	//sMsg.nType = packet->nType;
	//sMsg.nAccountID = packet->nAccountID;
	//memcpy(sMsg.arrName,packet->arrName,MAX_NAME_LENGTH);

	//pClientSession->SendMsgToDp(&sMsg,sMsg.GetPackLength());

}

void ProcFepHandler::RqRandNames(zSession* pSession, const NetMsgSS* pMsg,int32 nSize)
{
	// Login中本来就已经加载了所有的昵称，在这里会选择可能性大没有使用过的昵称 

	//const C2LRandNames* packet = static_cast<const C2LRandNames*>(pMsg);
	//ClientSession* pClientSession = ClientSessionMgr::getMe().getSession(packet->clientSessionID);
	//ASSERT(pClientSession);

	//L2CNamesList sMsg;
	//sMsg.nCount = 0;
	//for (int32 i = 0 ; i < 10; ++i)
	//{
	//	static char arrName[32];
	//	memset(arrName,0,sizeof(arrName));
	//	if(NamesManager::getMe().GetRandTtems(arrName))
	//	{
	//		memcpy(sMsg.arrNames[i],arrName,sizeof(arrName));
	//		sMsg.nCount++;
	//	}else
	//	{
	//		break;
	//	}
	//}
	//
	//pClientSession->sendMsg(&sMsg,sMsg.GetPackLength());

}
