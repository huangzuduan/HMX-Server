
#ifndef _CSTURN_H
#define _CSTURN_H
#include "csCommon.h"

#pragma pack(1)


/////////////////////////////////////////////////////////////
/// 暂定转生相关指令
////////////////////////////////////////////////////////////

namespace Cmd
{

	struct stTurnUserCmd : public stNullUserCmd
	{
		stTurnUserCmd()
		{
			byCmd = TURN_USERCMD;
		}
	};
    
	//请求转生
	#define SET_TRUN_REQUEST_PARAMETER 1
	struct stTurnRequestCmd : public stTurnUserCmd
	{
		stTurnRequestCmd()
		{
			byParam = SET_TRUN_REQUEST_PARAMETER;
		}
	};


	//enum stata{
	//	relationClear;


	//};
    
	//转生请求结果
	#define SET_TRUN_RESULT_PARAMETER 2
	struct  stTurnResultCmd : public stTurnUserCmd
	{
		//true成功;

		bool turnSucceed;

		stTurnResultCmd()
		{
			byParam = SET_TRUN_RESULT_PARAMETER;
		}
	};


		//会话服务器向场景服务器返回关系检查结果
	const BYTE PARA_CHECKRELATION_RESULT = 248;// 3
	struct t_CheckRelationEmptyResult : public t_NullCmd
	{
		DWORD dwUserID;//用户ID
		bool isEmpty;
		//t_CheckRelationEmptyResult()
		//{
		//	byParam = PARA_CHECKRELATION_RESULT;
		//}
		t_CheckRelationEmptyResult()
			: t_NullCmd(Session::CMD_SCENE,PARA_CHECKRELATION_RESULT) {}
	};


    //场景服务器向会话服务器请求检查用户除好友关系以外的关系是否为空

	#define PARA_CHECKRELATION_EMPTY 4
	struct t_CheckRelationEmpty : public stTurnUserCmd
	{
		t_CheckRelationEmpty()
		{
			byParam = PARA_CHECKRELATION_EMPTY;
		}
			//: t_NullCmd(CMD_SCENE,PARA_CHECKRELATION_EMPTY) {}
	};


    //场景服务器向会话服务器请求检查用户除好友关系以外的关系是否为空

    //const BYTE PARA_CHECKRELATION_EMPTY 248;
	//struct t_CheckRelationEmpty : t_NullCmd
	//{

		//t_CheckRelationEmpty()
		//{
		//	byParam = PARA_CHECKRELATION_EMPTY;
		//}

	//	DWORD dwUserID;//用户ID
	//	t_CheckRelationEmpty_SceneSession()
	//		: t_NullCmd(Cmd::Session::CMD_SCENE,PARA_CHECKRELATION_EMPTY) {}
	//};


}

#pragma pack()


#endif