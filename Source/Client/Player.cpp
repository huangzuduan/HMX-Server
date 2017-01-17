#include "Client_PCH.h"
#include "Player.h"

Player::Player()
{
	bChating = false;
	accid = charCount = keytime = 0;
	memset(charIDList, 0, sizeof(charIDList));
	session = NULL;
	memset(keymd5, 0, sizeof(keymd5));
}


Player::~Player()
{
	
}

void Player::Update(const zTaskTimer* timer)
{
	
}


void Player::SendMsg(NetMsgSS* pMsg ,int32 nSize)
{
	// ¼ÓÃÜ´¦Àí 
	static char arrUnBuffer[65536];
	static char arrEnBuffer[65536];
	int nCHeadSize = sizeof(NetMsgC);
	int nSHeadSize = sizeof(NetMsgSS);
	int nCSize = nSize - (nSHeadSize - nCHeadSize);
	memcpy(&arrUnBuffer[0], pMsg, nSize);
	memcpy(&arrEnBuffer[0], &arrUnBuffer[0], nCHeadSize);
	memcpy(&arrEnBuffer[nCHeadSize], &arrUnBuffer[nSHeadSize], nSize - nSHeadSize);
	zEncrypt::xorCode(nCSize, session->encrypt, arrEnBuffer, nCSize);
	session->socket->ParkMsg((NetMsgSS*)&arrEnBuffer[0], nCSize);
	session->socket->SendMsg();
}


