#ifndef _GAMECOMMAND_H_
#define _GAMECOMMAND_H_

#include "BaseDefine.h"

#define MAX_PATH1 260

class GameCommand;

typedef void(GameCommand::*DBCommandFun)();

struct KeyCommand
{
	KeyCommand( const char* id , const char* doc , DBCommandFun call )
	{
		this->id = id;
		this->doc = doc;
		this->callBack = call;
	}

	std::string	id;
	std::string	doc;
	DBCommandFun	callBack;
};

typedef std::vector< KeyCommand > VectorCommand;
typedef std::vector< KeyCommand >::iterator VectorCommandIter;

class GameCommand
{
public:

	GameCommand();
	~GameCommand();
    
    void Init();
	void LoopInput( float32 delay );
	bool ParseCommand( char* command );
	void CommandHelp();

private:

	static VectorCommand	commands;
	char			mArrBuffer[ MAX_PATH1 ];
	int32			mCommandCount;
};



#endif


