#include "SrvEngine.h"

zMsgHandler::zMsgHandler()
{

}

zMsgHandler::~zMsgHandler()
{

}

const MsgFunc* zMsgHandler::GetMsgHandler(uint32 protocol)
{
	MsgFuncMap::iterator it = msgFuncs.find(protocol);
	if (it != msgFuncs.end())
	{
		return &(it->second);
	}
	return NULL;
}

bool zMsgHandler::RegisterMessage(uint32 msgIdx, int32 packSize, const HandleFunc& handlerFun)
{
	if (!msgFuncs.insert(std::make_pair(msgIdx, MsgFunc(packSize, handlerFun))).second)
	{
		printf("–≠“È÷ÿ∏¥:%u",msgIdx);
		ASSERT(0);
	}
	return true;
}




