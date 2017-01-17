#ifndef _SCENE_SERVER_MSG_HANDLER_H_
#define _SCENE_SERVER_MSG_HANDLER_H_

#include "Single.h"

class ProcSsHandler : public Single<ProcSsHandler>
{
public:
	ProcSsHandler();
	~ProcSsHandler();

	/*--------------------------------------------
	 *  @brief    :	请求场景注册，当ss登录ws完成后，请求注册它所属于的地图ID
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RqSceneRegister(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	/*--------------------------------------------
	 *  @brief    :	请求场景注销，主动取消场景地图注册
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RqSceneCancel(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	/*--------------------------------------------
	 *  @brief  : 进入场景后返回的结果 
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RpEnterSceneResult(zSession* pSession, const NetMsgSS* pMsg,int32 nSize);

	void RpChangeScene(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	/* 聊天信息转发 */
	void TurnChatToOne(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void NtBroadcastMsg(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);

	void rqRelAdd(zSession* pSession, const NetMsgSS* pMsg, int32 nSize);
};

#endif


