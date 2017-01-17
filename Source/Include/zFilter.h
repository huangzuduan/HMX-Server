#ifndef _INC_ZFILTER_H_
#define _INC_ZFILTER_H_

#ifdef __cplusplus
extern "C"{
#endif //__cplusplus

#ifndef ZFILTER_EXPORTS
#define FILTERAPI DECLSPEC_IMPORT
#else //ZFILTER_EXPORTS
#define FILTERAPI
#endif //ZFILTER_EXPORTS

#ifndef _INC_SRVENGINE_H_
typedef enum
    {
      /**
       * \brief 当zLogger等级设置为OFF，否则不会输出任何日志
       */
      LEVEL_OFF   = INT_MAX,
      
      /**
       * \brief 当zLogger等级设置为FATAL，只输出FATAL等级的日志
       *
       * 程序致命错误，已经无法提供正常的服务功能。
       */
      LEVEL_FATAL = 50000,
      
      /**
       * \brief 当zLogger等级设置为ERROR，只输出大于等于此等级的日志
       *
       * 错误，可能不能提供某种服务，但可以保证程序正确运行。
       */
      LEVEL_ERROR = 40000,
      
      /**
       * \brief 当zLogger等级设置为WARN，只输出大于等于此等级的日志
       *
       * 警告，某些地方需要引起注意，比如没有配置文件，但程序用默认选项可以使用。
       */
      LEVEL_WARN  = 30000,
      
      /**
       * \brief 当zLogger等级设置为INFO，只输出大于等于此等级的日志
       *
       * 信息，提供一般信息记录，多用于一些程序状态的记录。
       */
      LEVEL_INFO  = 20000,
      
      /**
       * \brief 当zLogger等级设置为DEBUG，输出所有等级的日志
       */
      LEVEL_DEBUG = 10000,
      
      /**
       * \brief 当zLogger等级设置为ALL，输出所有等级的日志
       */
      LEVEL_ALL   = INT_MIN
    }zLevel;

typedef enum
{
  //UNKNOWNSERVER  =  0, // 未知服务器类型 
  //SUPERSERVER      =  1, // 管理服务器 
  //LOGINSERVER     =  10, // 登陆服务器 
  //RECORDSERVER  =  11, // 档案服务器 
  //BILLSERVER      =  12, // 计费服务器 
  SESSIONSERVER  =  20, // 会话服务器 
  SCENESSERVER  =  21, // 场景服务器 
  //GATEWAYSERVER  =  22, // 网关服务器 
  //MINISERVER      =  23    // 小游戏服务器 
}ServerType;
#endif //_INC_SRVENGINE_H_

typedef PSTR (*PFN_GetConfigValue)(PSTR szName,PSTR szDefault);

#ifdef _INC_SRVENGINE_H_
typedef void (*PFN_WriteLogMsg)(zLogger::zLevel level,char * pattern,...);
#else //_INC_SRVENGINE_H_
typedef void (*PFN_WriteLogMsg)(zLevel level,char * pattern,...);
#endif //_INC_SRVENGINE_H_

typedef struct NZebraUser *PZebraUser;

typedef PZebraUser (*PFN_GetUserByName)(PSTR szName);
typedef PZebraUser (*PFN_GetUserByTempID)(DWORD tempid);
typedef PZebraUser (*PFN_GetUserByID)(DWORD id);

typedef BOOL (*PFN_SendCommand)(PZebraUser pUser,PBYTE pCmd,DWORD dwCmd);

typedef struct
{
  ServerType          eST; //server类型
  PFN_GetConfigValue  GetConfigValue; //读取配置文件里的配置信息,没有的话返回szDefault
  PFN_WriteLogMsg     WriteLogMsg;    //写日志信息
  PFN_GetUserByName   GetUserByName;  //根据用户名得到用户类实例,SESSIONSERVER
  PFN_GetUserByTempID GetUserByTempID;//根据用户临时ID得到用户类实例,SESSIONSERVER
  PFN_GetUserByID     GetUserByID;    //根据用户ID得到用户类实例,SESSIONSERVER
  PFN_SendCommand     SendCommand;    //给用户发送命令,SESSIONSERVER
}NZTFilterContext,*PZTFilterContext;

/*
server启动时调用,其它的所有初始化已经完成.
*/
void FILTERAPI FilterStartup(PZTFilterContext pZTFC);

/*
server每次接收到一个请求时调用,返回TRUE说明filter已经处理此请求.
原则上filter可以改写server内部的处理流程,但是目前的设计是用来处理新增的功能的.
*/
BOOL FILTERAPI FilterProcess(PZTFilterContext pZTFC,PBYTE pCmd,DWORD dwCmd);

/*
server退出时调用,其它的所有清除尚未开始.
*/
void FILTERAPI FilterCleanup(PZTFilterContext pZTFC);

#ifdef __cplusplus
}
#endif //__cplusplus

#endif //_INC_ZFILTER_H_
