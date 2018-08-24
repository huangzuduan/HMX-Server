#include "ClientCommand.h"
#include "PlayerProcHandler.h"
#include "GameService.h"
#include "Player.h"
#include "PlayerMgr.h"

#ifdef WIN32 
#include "conio.h"
#else
int _kbhit()
{
	struct timeval tv;
	fd_set rdfs;
	tv.tv_sec = 0;
	tv.tv_usec = 0;
	FD_ZERO(&rdfs);
	FD_SET(STDIN_FILENO, &rdfs);
	select(STDIN_FILENO + 1, &rdfs, NULL, NULL, &tv);
	return FD_ISSET(STDIN_FILENO, &rdfs);
}

int _getch()
{
	return getchar();
}
#endif


GameCommand::GameCommand()
:	mCommandCount( 0 )
{
}

GameCommand::~GameCommand()
{
}

void GameCommand::Init()
{
	commands.push_back(KeyCommand("he", "显示所有命令", &GameCommand::CommandHelp));
	commands.push_back(KeyCommand("so", "搜索前缀命令", &GameCommand::PrintSearch));
	commands.push_back(KeyCommand("lh", "登录hzd账号", &GameCommand::LoginAccount));
	commands.push_back(KeyCommand("lk", "登录kfc账号", &GameCommand::LoginAccount2));
	commands.push_back(KeyCommand("rc", "创建角色", &GameCommand::RoleCreate));
	commands.push_back(KeyCommand("rd", "删除角色", &GameCommand::RoleDelete));
	commands.push_back(KeyCommand("rs", "选择第一个角色", &GameCommand::RoleSelect));
	commands.push_back(KeyCommand("sl", "请求加载场景数据", &GameCommand::SceneLoad));
	commands.push_back(KeyCommand("si", "发送进入场景10001", &GameCommand::SceneIn));
	commands.push_back(KeyCommand("ch", "发送聊天信息", &GameCommand::ChatToWorld));
	commands.push_back(KeyCommand("mo", "移动位置", &GameCommand::MovePosition));

	commands.push_back(KeyCommand("rellist", "好友列表", &GameCommand::RelList));
	commands.push_back(KeyCommand("reladd", "好友添加", &GameCommand::RelAdd));
	commands.push_back(KeyCommand("relrm", "好友删除", &GameCommand::RelRemove));
}

void GameCommand::LoopInput()
{

	if( _kbhit() )
	{
		int32_t nKey = _getch();
		switch( nKey )
		{
#ifdef WIN32
		case 13:			// Enter
#else
        case 10:			// Linux
#endif
			{
				if( mCommandCount == 0 )
					break;
				ParseCommand( mArrBuffer );
				// reset command
				mCommandCount = 0;
				memset( mArrBuffer , 0 , MAX_PATH1 );
				printf("\n");
			}
			break;
		case 8:				// BackSpace
			{
				if( mCommandCount > 0 )
				{
					printf( "\b \b" );
					mArrBuffer[mCommandCount] = 0;
					mCommandCount--;
				}
			}
			break;
		case 27:			// ESC
			{
				// clear command
				mCommandCount = 0;
				memset( mArrBuffer , 0 , MAX_PATH1 );
				printf( "...[Cancel]\nCommand: " );
			}
			break;
		default:
			{
				if( mCommandCount >= 255 )
				{
					break;
				}
				mArrBuffer[ mCommandCount ] = (char)nKey;
				mArrBuffer[ mCommandCount + 1 ] = '\0';
				mCommandCount++;
				printf( "%c", nKey );
			}
			break;
		}
	}


	/*
		//std::system("cls"); // 清屏
		//printf("\r");	// 清除本行
		固定行，位置显示
		while (t == 0) {
			a1 = (float)getdata1()*3.3 / 1024;
			a2 = (float)getdata2()*3.3 / 1024;
			a0 = (float)getdata0()*3.3 / 1024;
			printf("d0 = %.2f   d1 = %.2f    d2 = %.2f\r", a0, a1, a2); // '\r'
			sleep(1);
		}
		pthread_join(p_m, &retval);
		return 0;
	
	*/

}



bool GameCommand::ParseCommand(const char* command )
{
	VectorCommandIter iterEnd = commands.end();
	for ( VectorCommandIter iter = commands.begin() ; iter != iterEnd ; ++iter )
	{
		if ( strstr( command , iter->id.c_str() ) )
		{
			(this->*(iter->callBack))(command);
			printf("\n执行命令:%-10s\n",iter->doc.c_str());
			return true;
		}
	}
	printf( "\nUnknown command.\n" );
	return false;
}

void GameCommand::PrintSearch(const char* command)
{
	printf("\n");
	std::list<string> ls;
	stringtok(ls, command);
	int count = 0;
	for (std::list<string>::const_iterator i = ls.begin(); i != ls.end(); ++i)
	{
		if (count++ != 0)
		{
			VectorCommandIter iterEnd = commands.end();
			for (VectorCommandIter iter = commands.begin(); iter != iterEnd; ++iter)
			{
				if (strstr(iter->id.c_str(), (*i).c_str()))
				{
					printf("\n命令:%-10s %-10s\n", iter->id.c_str(), iter->doc.c_str());
				}
			}
		}
		else
		{
			continue;
		}
	}
}

void GameCommand::AnalysisCmd(const char* command)
{

}

void GameCommand::ShowCmd()
{
	CommandHelp("help");
}

void GameCommand::CommandHelp(const char* command)
{
	printf("\n");
	VectorCommandIter iterEnd = commands.end();
	for ( VectorCommandIter iter = commands.begin() ; iter != iterEnd ; ++iter )
	{
		//%-8s 代表输入字符代表从屏幕左边开始第几个位置开始打印，能够整齐排列
		printf( "%-1s%-16s%-20s\n" ,  "-" , iter->id.c_str() ,iter->doc.c_str() );
	}
}

void GameCommand::LoginAccount(const char* command)
{
	struct MyStruct : public execEntry<Player>
	{
		virtual bool exec(Player* player)
		{
			PlayerProcHandler::SendLogin(player);
			return true;
		}
	};

	MyStruct exec;
	PlayerMgr::getMe().execPlayer(exec);
	
}

void GameCommand::LoginAccount2(const char* command)
{
	struct MyStruct : public execEntry<Player>
	{
		virtual bool exec(Player* player)
		{
			PlayerProcHandler::SendLogin2(player);
			return true;
		}
	};

	MyStruct exec;
	PlayerMgr::getMe().execPlayer(exec);

}

void GameCommand::RoleSelect(const char* command)
{
	struct MyStruct : public execEntry<Player>
	{
		virtual bool exec(Player* player)
		{
			PlayerProcHandler::SendSelectRole(player);
			return true;
		}
	};

	MyStruct exec;
	PlayerMgr::getMe().execPlayer(exec);
}

void GameCommand::RoleCreate(const char* command)
{
	struct MyStruct : public execEntry<Player>
	{
		virtual bool exec(Player* player)
		{
			PlayerProcHandler::SendRoleCreate(player);
			return true;
		}
	};

	MyStruct exec;
	PlayerMgr::getMe().execPlayer(exec);
}

void GameCommand::RoleDelete(const char* command)
{
	struct MyStruct : public execEntry<Player>
	{
		virtual bool exec(Player* player)
		{
			PlayerProcHandler::SendRoleDelete(player);
			return true;
		}
	};

	MyStruct exec;
	PlayerMgr::getMe().execPlayer(exec);
}

void GameCommand::SceneLoad(const char* command)
{

}

void GameCommand::SceneIn(const char* command)
{

}

void GameCommand::ChatToWorld(const char* command)
{

}

void GameCommand::MovePosition(const char* command)
{

}

void GameCommand::RelList(const char* command)
{
	struct MyStruct : public execEntry<Player>
	{
		virtual bool exec(Player* player)
		{
			PlayerProcHandler::SendRelationList(player);
			return true;
		}
	};

	MyStruct exec;
	PlayerMgr::getMe().execPlayer(exec);
}

void GameCommand::RelAdd(const char* command)
{
	struct MyStruct : public execEntry<Player>
	{
		virtual bool exec(Player* player)
		{
			PlayerProcHandler::SendRelationAdd(player);
			return true;
		}
	};

	MyStruct exec;
	PlayerMgr::getMe().execPlayer(exec);
}

void GameCommand::RelRemove(const char* command)
{
	struct MyStruct : public execEntry<Player>
	{
		virtual bool exec(Player* player)
		{
			PlayerProcHandler::SendRelationRmove(player);
			return true;
		}
	};

	MyStruct exec;
	PlayerMgr::getMe().execPlayer(exec);
}