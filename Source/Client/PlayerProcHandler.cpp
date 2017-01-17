#include "Client_PCH.h"
#include "PlayerProcHandler.h"
#include "NetMsgHandler.h"
#include "Player.h"


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
	C2FepEncryptInfo send;
	player->SendMsg(&send,send.GetPackLength());
}

void PlayerProcHandler::SendLogin(Player* player)
{
	// 使用默认账号与密码 
	C2LAccountLogin send;
	GBKToUTF8("hzd", send.username, sizeof(send.username));
	GBKToUTF8("123", send.password, sizeof(send.password));
	player->SendMsg(&send, send.GetPackLength());
}


void PlayerProcHandler::SendLogin2(Player* player)
{
	// 使用默认账号与密码 
	C2LAccountLogin send;
	GBKToUTF8("kfc", send.username, sizeof(send.username));
	GBKToUTF8("123", send.password, sizeof(send.password));
	player->SendMsg(&send, send.GetPackLength());
}

void PlayerProcHandler::SendRandName(Player* player)
{
	C2LRandNames send;
	player->SendMsg(&send, send.GetPackLength());
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

	int32 nXingIndex = RangedRand(0,9);
	int32 nMingIndex = RangedRand(0,19);

	std::stringstream strName;
	strName << arrXing[nXingIndex] << arrMing[nMingIndex];

	// 创建角色 
	C2WCreateRole send;
	send.accid = player->accid;
	send.roleType = 1;
	char nameUtf8[MAX_NAMESIZE + 1];
	memset(nameUtf8,0,sizeof(nameUtf8));
	GBKToUTF8(strName.str().c_str(),nameUtf8,MAX_NAMESIZE);
	nameUtf8[MAX_NAMESIZE] = '\0';
	strcpy(send.name,nameUtf8);
	strncpy(send.keymd5, player->keymd5, MAX_NAMESIZE);
	send.keytime = player->keytime;

	player->SendMsg(&send,send.GetPackLength());
	printf(" 请求创建角色 \n");
}

void PlayerProcHandler::SendRoleDelete(Player* player)
{
	// 创建角色 
	C2WDeleteRole send;
	send.uid = player->getFirstCharID();
	send.accid = player->accid;
	strncpy(send.keymd5, player->keymd5, MAX_NAMESIZE);
	send.keytime = player->keytime;

	player->SendMsg(&send, send.GetPackLength());
	printf(" 请求创建角色 \n");
}

void PlayerProcHandler::SendSelectRole(Player* player)
{
	// 选择角色
	C2WSelectRole send;
	send.uid = player->getFirstCharID();
	player->SendMsg(&send,send.GetPackLength());
	printf(" 选择角色 \n");


}

void PlayerProcHandler::SendEnterChangeScene(Player* player)
{	
	C2SChanageScene send;
	send.nSceneID = 10001;
	player->SendMsg(&send,send.GetPackLength());
}

void PlayerProcHandler::SendEnterChangeScene2(Player* player)
{
	C2SChanageScene send;
	send.nSceneID = 10004;
	player->SendMsg(&send, send.GetPackLength());
}

void PlayerProcHandler::SendLoadResed(Player* player)
{

}

void PlayerProcHandler::SendReqSceneData(Player* player)
{
	printf(" 我前端初始化该场景资源完成，请求场景所需要的数据\n");
	C2SClientIsReady send;
	send.nLoadDataFlags = C2SClientIsReady::E_DATA_TYPE_ALL;
	player->SendMsg(&send,send.GetPackLength());
}

void PlayerProcHandler::SendMoveTo(Player* player)
{
	C2SPositionMove send;
	send.nNewX = 20;
	send.nNewY = 30;
	player->SendMsg(&send, send.GetPackLength());
}

void PlayerProcHandler::SendChatToWorld(Player* player)
{
	//C2SChatToWorld send;
	//int leng = GBKToUTF8("Hello", send.msg.data, sizeof(send.msg.data));
	//send.msg.len = leng;
	//player->SendMsg(&send, send.GetPackLength());
}

void PlayerProcHandler::SendRelationList(Player* player)
{
	C2SRelationList send;
	player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRelationAdd(Player* player)
{
	C2SRelationAdd send;
	std::string strName = "李雅静";
	char nameUtf8[MAX_NAMESIZE + 1];
	memset(nameUtf8, 0, sizeof(nameUtf8));
	GBKToUTF8(strName.c_str(), nameUtf8, MAX_NAMESIZE);
	strncpy(send.name, nameUtf8, MAX_NAMESIZE);
	player->SendMsg(&send, sizeof(send));
}

void PlayerProcHandler::SendRelationRmove(Player* player)
{
	C2SRelationRemove send;
	send.uid = 100000001;
	player->SendMsg(&send, sizeof(send));
}

////////////////////////////接收//////////////////////////////////////////

void PlayerProcHandler::RecvEncryptInfo(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const F2CEncryptInfo* packet = static_cast<const F2CEncryptInfo*>(pMsg);
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		memcpy(player->session->encrypt, packet->encryptKey, MAX_ENCRYPTSIZE);
	}

}

void PlayerProcHandler::RecvLoginReadyFinish(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	//SendLogin(player);
}

void PlayerProcHandler::RecvEnterScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		SendReqSceneData(player);
	}

}

void PlayerProcHandler::RecvChatWorld(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	int32 a = 1;
	const S2CRepCharWorld* packet = static_cast<const S2CRepCharWorld*>(pMsg);
	printf("Recveid Client ID: %s ,Msg:%s\n", packet->fromName, packet->sayMsg);
}

void PlayerProcHandler::RecvSceneInitResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	int32 a = 1;
}

void PlayerProcHandler::RecvRandNames(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const L2CNamesList* packet = static_cast<const L2CNamesList*>(pMsg);
	for (int32 i = 0; i < packet->nCount; ++i)
	{
		printf("==== %s === \n", Utf8ToGBK(packet->arrNames[i]));
	}
}

void PlayerProcHandler::RecvRelationList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvRelationUpdate(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvRelationDelete(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvUserPackages(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvLoginAccountResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		const L2CAccLogin* packet = static_cast<const L2CAccLogin*>(pMsg);
		switch (packet->result)
		{
		case 1:
		{
			player->accid = packet->accid;
			strncpy(player->keymd5, packet->keymd5, MAX_NAMESIZE);
			player->keytime = packet->keytime;
			printf("Login success!\n");
		}
		break;
		case 0:
		{
			printf("Login fail!\n");
		}
		break;
		}
	}

}

void PlayerProcHandler::RecvCharacterList(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		const W2CUserList* packet = static_cast<const W2CUserList*>(pMsg);
		int32 nCount = 0;
		std::vector<int64> recvieUids;
		for (int32 i = 0; i < sizeof(packet->datas) / sizeof(packet->datas[0]); ++i)
		{
			const W2CUserList::UserInfo& data = packet->datas[i];
			if (data.id)
			{
				printf("ID:%-10lld Name:%-12s Lv:%-8d \n", data.id, Utf8ToGBK(data.name), data.level);
				recvieUids.push_back(data.id);
				nCount++;
			}
		}

		if (nCount)
		{
			player->setCharList(recvieUids);
		}
	}

}

void PlayerProcHandler::RecvRoleCreateResult(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const W2CCreateRet* packet = static_cast<const W2CCreateRet*>(pMsg);
	switch(packet->reasoin)
	{
	case 0:
		printf("创建新角色成功\n");
		break;
	case 1:
		printf("创建失败，数量限制\n");
		break;
	case 2:
		printf("创建失败，昵称同名\n");
		break;
	case 3:
		printf("操作数据库失败\n");
		return;
	}
}

void PlayerProcHandler::RecvCharacterMainData(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvQuestMainData(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvSendDataFinish(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{

}

void PlayerProcHandler::RecvEnterSceneInfo(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	Zebra::logger->info("收到场景信息，发送进入场景");
	Player* player = PlayerMgr::getMe().get(pSession->id);
	if (player)
	{
		SendReqSceneData(player);
	}
}

void PlayerProcHandler::RecvChannelJion(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S2CChannelJion* packet = static_cast<const S2CChannelJion*>(pMsg);
	Zebra::logger->info("%s加入频道%d", Utf8ToGBK(packet->name),packet->channelID);
}

void PlayerProcHandler::RecvChannelLeave(zSession* pSession, const NetMsgSS* pMsg, int32 nSize)
{
	const S2CChannelLeave* packet = static_cast<const S2CChannelLeave*>(pMsg);
	Zebra::logger->info("%s加入频道%d", Utf8ToGBK(packet->name), packet->channelID);
}


