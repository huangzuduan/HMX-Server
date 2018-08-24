#ifndef _SCENE_SERVER_MSG_HANDLER_H_
#define _SCENE_SERVER_MSG_HANDLER_H_


#include "SrvEngine.h"
#include "Single.h"

size_t onFindBindInfo(void *buffer, size_t size, size_t nmemb, void *parm);
size_t onBindingAgent(void *buffer, size_t size, size_t nmemb, void *parm);
size_t onInputInviteCode(void *buffer, size_t size, size_t nmemb, void *parm);

class ProcSsHandler : public Single<ProcSsHandler>
{
public:
	ProcSsHandler();
	~ProcSsHandler();

	void TransTerToSceneReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void TransTerToSceneResp(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void NotifyUpdateRankInfo(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnQueryRankRequest(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnAddRoomToWs(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnUpdateRoomToWs(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnRemoveRoomToWs(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	void OnSyncRoleToWs(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnReqRobotJoinRoom(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnReqBindInfoReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnReqBindAgentReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);
	void OnInputInviteCodeReq(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

	/*--------------------------------------------
	 *  @brief    :	请求场景注册，当ss登录ws完成后，请求注册它所属于的地图ID
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RqSceneRegister(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	/*--------------------------------------------
	 *  @brief    :	请求场景注销，主动取消场景地图注册
	 *  @input	  :
	 *  @return   :	
	 *-------------------------------------------*/
	void RqSceneCancel(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	/*--------------------------------------------
	 *  @brief  : 进入场景后返回的结果 
	 *  @input	: 
	 *  @return :	
	 *-------------------------------------------*/
	void RpEnterSceneResult(zSession* pSession, const PbMsgWebSS* pMsg,int32_t nSize);

	void RpChangeScene(zSession* pSession, const PbMsgWebSS* pMsg, int32_t nSize);

};

#endif


