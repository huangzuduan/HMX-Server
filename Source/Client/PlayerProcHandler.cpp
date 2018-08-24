#include "PlayerProcHandler.h"
#include "NetMsgHandler.h"
#include "Player.h"
#include "PlayerMgr.h"


PlayerProcHandler::PlayerProcHandler(void)
{
}


PlayerProcHandler::~PlayerProcHandler(void)
{
}

void PlayerProcHandler::SendRequestClose(Player* player)
{
	player->session->socket->OnEventColse();
}

void PlayerProcHandler::SendEncrypt(Player* player)
{
	//C::RqEncryptInfo send;
	//player->SendMsg(&send,sizeof(send));
}

void PlayerProcHandler::SendLogin(Player* player)
{
	// 使用默认账号与密码 
	//C::RqAccountLogin send;
	//strncpy(send.username,"hzd", sizeof(send.username));
	//strncpy(send.password, "123", sizeof(send.password));
	//player->SendMsg(&send, sizeof(send));
}


void PlayerProcHandler::SendLogin2(Player* player)
{
	// 使用默认账号与密码 
	//C::RqAccountLogin send;
	//send.loginType = C::RqAccountLogin::LOGINTYPE_CREATERSA;
	////zUtility::GBKToUTF8("kfc", send.username, sizeof(send.username));
	////zUtility::GBKToUTF8("123", send.password, sizeof(send.password));
	//player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRandName(Player* player)
{
	//C::RqRandAccount send;
	//player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendCharacterList(Player* player)
{

}

void PlayerProcHandler::SendChar2World(Player* player)
{

}

void PlayerProcHandler::SendRoleCreate(Player* player)
{
	std::string arrXing[10];
	arrXing[0] = "李";
	arrXing[1] = "王";
	arrXing[2] = "张";
	arrXing[3] = "刘";
	arrXing[4] = "陈";
	arrXing[5] = "杨";
	arrXing[6] = "赵";
	arrXing[7] = "欧阳";
	arrXing[8] = "上官";
	arrXing[9] = "西门";

	std::string arrMing[20];
	arrMing[0] = "辰逸";
	arrMing[1] = "浩宇";
	arrMing[2] = "瑾瑜";
	arrMing[3] = "皓轩";
	arrMing[4] = "致远";
	arrMing[5] = "文博";
	arrMing[6] = "英杰";
	arrMing[7] = "致远";
	arrMing[8] = "雨泽";
	arrMing[9] = "文昊";
	arrMing[10] = "雅静";
	arrMing[11] = "惠茜";
	arrMing[12] = "梦璐";
	arrMing[13] = "漫妮";
	arrMing[14] = "语嫣";
	arrMing[15] = "倩雪";
	arrMing[16] = "灵芸";
	arrMing[17] = "茹雪";
	arrMing[18] = "美琳";
	arrMing[19] = "莉姿";

	int32_t nXingIndex = randBetween(0,9);
	int32_t nMingIndex = randBetween(0,19);

	std::stringstream strName;
	strName << arrXing[nXingIndex] << arrMing[nMingIndex];

	// 创建角色 
	//C::RqCreateRole send;
	//send.accid = player->accid;
	//send.roleType = 1;
	//char nameUtf8[MAX_NAMESIZE + 1];
	//memset(nameUtf8,0,sizeof(nameUtf8));
	//strncpy(nameUtf8,strName.str().c_str(),MAX_NAMESIZE);
	//nameUtf8[MAX_NAMESIZE] = '\0';
	//strcpy(send.name,nameUtf8);
	//strncpy(send.keymd5, player->keymd5, MAX_NAMESIZE);
	//send.keytime = player->keytime;

	//player->SendMsg(&send, sizeof(send));
	//printf(" 请求创建角色 \n");
}

void PlayerProcHandler::SendRoleDelete(Player* player)
{
	// 创建角色 
	//C::RqDeleteRole send;
	//send.uid = player->getFirstCharID();
	//send.accid = player->accid;
	//strncpy(send.keymd5, player->keymd5, MAX_NAMESIZE);
	//send.keytime = player->keytime;

	//player->SendMsg(&send, sizeof(send));
	//printf(" 请求创建角色 \n");
}

void PlayerProcHandler::SendSelectRole(Player* player)
{
	// 选择角色
	//C::RqSelectRole send;
	//send.uid = player->getFirstCharID();
	//player->SendMsg(&send,sizeof(send));
	//printf(" 选择角色 \n");


}

void PlayerProcHandler::SendEnterChangeScene(Player* player)
{	
	//C::RqChanageScene send;
	//send.nSceneID = 10001;
	//player->SendMsg(&send,sizeof(send));
}

void PlayerProcHandler::SendEnterChangeScene2(Player* player)
{
	//C::RqChanageScene send;
	//send.nSceneID = 10004;
	//player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendLoadResed(Player* player)
{

}

void PlayerProcHandler::SendReqSceneData(Player* player)
{
	printf(" 我前端初始化该场景资源完成，请求场景所需要的数据\n");
	//C::RqClientIsReady send;
	//send.nLoadDataFlags = C::RqClientIsReady::E_DATA_TYPE_ALL;
	//player->SendMsg(&send,sizeof(send));
}

void PlayerProcHandler::SendMoveTo(Player* player)
{
	//C::RqPositionMove send;
	//send.nNewX = 20;
	//send.nNewY = 30;
	//player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendChatToWorld(Player* player)
{
	//RqChatToWorld send;
	//int leng = GBKToUTF8("Hello", send.msg.data, sizeof(send.msg.data));
	//send.msg.len = leng;
	//player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRelationList(Player* player)
{
	//C::RqRelationList send;
	//player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRelationAdd(Player* player)
{
	//C::RqRelationAdd send;
	//std::string strName = "李雅静";
	//char nameUtf8[MAX_NAMESIZE + 1];
	//memset(nameUtf8, 0, sizeof(nameUtf8));
	//strncpy(nameUtf8, strName.c_str(), MAX_NAMESIZE);
	//strncpy(send.name, nameUtf8, MAX_NAMESIZE);
	//player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRelationRmove(Player* player)
{
	//C::RqRelationRemove send;
	//send.uid = 100000001;
	//player->SendMsg(&send, sizeof(send));
}

////////////////////////////接收//////////////////////////////////////////

void PlayerProcHandler::RecvEncryptInfo(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	//const C::RtEncryptInfo* packet = static_cast<const C::RtEncryptInfo*>(pMsg);
	//Player* player = PlayerMgr::getMe().get(pSession->GetID());
	//if (player)
	//{
	//	memcpy(player->session->encrypt, packet->encryptKey, MAX_ENCRYPTSIZE);
	//}

}

void PlayerProcHandler::RecvLoginReadyFinish(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	//SendLogin(player);
}

void PlayerProcHandler::RecvEnterScene(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	Player* player = PlayerMgr::getMe().get(pSession->GetID());
	if (player)
	{
		SendReqSceneData(player);
	}

}

void PlayerProcHandler::RecvChatWorld(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	int32_t a = 1;
	//const C::RtCharWorld* packet = static_cast<const C::RtCharWorld*>(pMsg);
	//printf("Recveid Client ID: %s ,Msg:%s\n", packet->fromName, packet->sayMsg);
}

void PlayerProcHandler::RecvSceneInitResult(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	int32_t a = 1;
}

void PlayerProcHandler::RecvRandNames(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	//const C::RtNamesList* packet = static_cast<const C::RtNamesList*>(pMsg);
	//for (int32_t i = 0; i < packet->count; ++i)
	//{
	//	printf("==== %s === \n", packet->list[i].name);
	//}
}

void PlayerProcHandler::RecvRelationList(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{

}

void PlayerProcHandler::RecvRelationUpdate(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{

}

void PlayerProcHandler::RecvRelationDelete(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{

}

void PlayerProcHandler::RecvUserPackages(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{

}

void PlayerProcHandler::RecvLoginAccountResult(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	//Player* player = PlayerMgr::getMe().get(pSession->GetID());
	//if (player)
	//{
	//	const C::RtAccLogin* packet = static_cast<const C::RtAccLogin*>(pMsg);
	//	switch (packet->result)
	//	{
	//	case 0:
	//	{
	//		player->accid = packet->accid;
	//		strncpy(player->keymd5, packet->keymd5, MAX_NAMESIZE);
	//		player->keytime = packet->keytime;
	//		printf("Login success!\n");
	//	}
	//	break;
	//	default:
	//		printf("Login fail!\n");
	//	break;
	//	}
	//}
}

void PlayerProcHandler::RecvCharacterList(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	//Player* player = PlayerMgr::getMe().get(pSession->GetID());
	//if (player)
	//{
	//	const C::RtUserListLogon* packet = static_cast<const C::RtUserListLogon*>(pMsg);
	//	int32_t nCount = 0;
	//	std::vector<int64_t> recvieUids;
	//	for (int32_t i = 0; i < sizeof(packet->datas) / sizeof(packet->datas[0]); ++i)
	//	{
	//		const C::RtUserListLogon::UserInfo& data = packet->datas[i];
	//		if (data.id)
	//		{
	//			printf("ID:%-10lld Name:%-12s Lv:%-8d \n", data.id, data.name, data.level);
	//			recvieUids.push_back(data.id);
	//			nCount++;
	//		}
	//	}

	//	if (nCount)
	//	{
	//		player->setCharList(recvieUids);
	//	}
	//}

}

void PlayerProcHandler::RecvRoleCreateResult(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	//const C::RtCreateRet* packet = static_cast<const C::RtCreateRet*>(pMsg);
	//switch(packet->reasoin)
	//{
	//case 0:
	//	printf("创建新角色成功\n");
	//	break;
	//case 1:
	//	printf("创建失败，数量限制\n");
	//	break;
	//case 2:
	//	printf("创建失败，昵称同名\n");
	//	break;
	//case 3:
	//	printf("操作数据库失败\n");
	//	return;
	//}
}

void PlayerProcHandler::RecvCharacterMainData(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{

}

void PlayerProcHandler::RecvQuestMainData(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{

}

void PlayerProcHandler::RecvSendDataFinish(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{

}

void PlayerProcHandler::RecvEnterSceneInfo(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	H::logger->info("收到场景信息，发送进入场景");
	Player* player = PlayerMgr::getMe().get(pSession->GetID());
	if (player)
	{
		SendReqSceneData(player);
	}
}

void PlayerProcHandler::RecvChannelJion(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	//const C::RtChannelJion* packet = static_cast<const C::RtChannelJion*>(pMsg);
	//H::logger->info("%s加入频道%d", packet->name,packet->channelID);
}

void PlayerProcHandler::RecvChannelLeave(zSession* pSession, const NetMsgSS* pMsg, int32_t nSize)
{
	//const C::RtChannelLeave* packet = static_cast<const C::RtChannelLeave*>(pMsg);
	//H::logger->info("%s加入频道%d", packet->name, packet->channelID);
}


