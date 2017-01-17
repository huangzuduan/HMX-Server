#ifndef __GAMECOMMAND_H_
#define __GAMECOMMAND_H_

#define MAX_PATH1 260

#include "NetSocket.h"

class Player;
class GameCommand;

typedef void(GameCommand::*CommandFun)(const char* secondArgs);

struct KeyCommand
{
	KeyCommand( const char* id , const char* doc , CommandFun call )
	{
		this->id = id;
		this->doc = doc;
		this->callBack = call;
	}

	std::string	id;
	std::string	doc;
	CommandFun	callBack;
};

typedef vector< KeyCommand > VectorCommand;
typedef vector< KeyCommand >::iterator VectorCommandIter;


/*
 *  命令容器管理器 
 */
class GameCommand : public Single<GameCommand>
{
protected:
	friend class Single<GameCommand>;
	GameCommand();
	~GameCommand();

public:
    
    void Init();
	void LoopInput();
	void ShowCmd();

private:

	bool ParseCommand(const char* command);
	void PrintSearch(const char* command);

	// 通用分析命令(当找不到合适命令时，则调用该命令进行查找可能的结果)
	void AnalysisCmd(const char* command);

	// 执行命令 
	void CommandHelp(const char* command);

	// 登录帐号hzd
	void LoginAccount(const char* command);

	// 登录帐号kfc
	void LoginAccount2(const char* command);

	// 选择角色
	void RoleSelect(const char* command);

	// 创建角色
	void RoleCreate(const char* command);

	// 删除角色
	void RoleDelete(const char* command);

	// 加载场景
	void SceneLoad(const char* command);

	// 进入场景
	void SceneIn(const char* command);

	// 世界聊天
	void ChatToWorld(const char* command);

	// 移动位置 
	void MovePosition(const char* command);

	void RelList(const char* command);
	void RelAdd(const char* command);
	void RelRemove(const char* command);

private:

	VectorCommand	commands;
	char			mArrBuffer[ MAX_PATH1 ];
	int32			mCommandCount;
};



#endif


