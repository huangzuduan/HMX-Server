/**
 * \brief 实现服务器框架类
 *
 * 
 */
#include "SrvEngine.h"


/**
 * \brief CTRL + C等信号的处理函数,结束程序
 *
 * \param signum 信号编号
 */
static void ctrlcHandler(int signum)
{
  H::logger->info("ctrlcHandler");
  fprintf(stderr,"ctrlcHandler\n");
  //如果没有初始化zService实例,表示出错
  zService *instance = zService::getInst();
  instance->Terminate();
}

/**
 * \brief HUP信号处理函数
 *
 * \param signum 信号编号
 */
static void hupHandler(int signum)
{
  H::logger->info("hupHandler");
  //如果没有初始化zService实例,表示出错
  zService *instance = zService::getInst();
  instance->reloadConfig();
}

zService *zService::inst = NULL;

/**
 * \brief 服务程序框架的主函数
 */
void zService::main()
{
  H::logger->debug("zService::main");
  //初始化程序,并确认服务器启动成功
  if(signal(SIGTERM  , ctrlcHandler)==SIG_ERR)
  {
	fprintf(stderr,"信号设置失败\n");
  }

  //初始化随机数
  srand(time(NULL));

  if (init()
  && validate())
  {
    //运行主回调线程
    while(!isTerminate())
    {
      if (!run())
      {
        break;
      }
    }
  }

  //结束程序,释放相应的资源
  finaly();
}

