#include "DBServer_PCH.h"
#include "ClientCommand.h"
#include <sstream>

#ifdef WIN32 

#include "conio.h"
#else

int _kbhit()
{
    struct timeval tv;
    fd_set rdfs;  
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO( &rdfs );
    FD_SET ( STDIN_FILENO , &rdfs );
    select( STDIN_FILENO + 1 , &rdfs , NULL , NULL , &tv );
    return FD_ISSET( STDIN_FILENO , &rdfs );
}

int _getch()
{
    return getchar();
}

#endif


VectorCommand GameCommand::commands;

GameCommand::GameCommand()
:	mCommandCount( 0 )
{
}

GameCommand::~GameCommand()
{
}

void GameCommand::Init()
{
	//commands.push_back( KeyCommand("0"," ¶Ï¿ªÁ¬½Ó "		,	ClientNetHandler::SendRequestClose));
	//commands.push_back( KeyCommand("11"," µÇÂ¼hzdÕËºÅ "		,	ClientNetHandler::SendLogin));
	//commands.push_back( KeyCommand("22"," µÇÂ¼kfcÕËºÅ "		,	ClientNetHandler::SendLogin2));

}

void GameCommand::LoopInput( float32 nDelay )
{

	if( _kbhit() )
	{
		int32 nKey = _getch();
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
}

bool GameCommand::ParseCommand( char* command )
{
	VectorCommandIter iterEnd = commands.end();
	for ( VectorCommandIter iter = commands.begin() ; iter != iterEnd ; ++iter )
	{
		if ( strstr( command , iter->id.c_str() ) )
		{
// TODO			iter->callBack(this);
			return true;
		}
	}
	printf( "\nUnknown command.\n" );
	return false;
}

void		GameCommand::CommandHelp()
{
	printf("\n");
	VectorCommandIter iterEnd = commands.end();
	for ( VectorCommandIter iter = commands.begin() ; iter != iterEnd ; ++iter )
	{
		 printf( "%-8s  %-3s: %-20s\n" ,  "==========" , iter->id.c_str() ,iter->doc.c_str() );
	}
}

