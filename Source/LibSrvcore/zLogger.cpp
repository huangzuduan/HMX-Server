/**
* \brief Zebra项目日志系统定义文件
*
*/
#include "SrvEngine.h"


/**
* \brief 构造一个zLogger 
*
* \param  name zLogger的名字，将会出现在输出的日志中的每一行
*/
zLogger::zLogger(char *name)
{
	fp_console = stdout;
	fp_file    = NULL;

	m_name     = name;
	m_file     = "";
	m_level    = LEVEL_ERROR;
	m_day      = 0;
}

/**
* \brief 析构函数
*/
zLogger::~zLogger()
{
	if (NULL != fp_file)
	{
		fclose(fp_file);
		fp_file = NULL;
	}
}

const std::string& zLogger::getName()
{
	return m_name;
}

/**
* \brief 移除控制台Log输出
*/
void zLogger::removeConsoleLog()
{
	msgMut.lock();
	fp_console = NULL;
	msgMut.unlock();
}

/**
* \brief 加一个本地文件Log输出
*
* \param file 要输出的文件名，Logger会自动地添加时间后缀 
* \return 无
*/
void zLogger::addLocalFileLog(const std::string &file)
{
	msgMut.lock();
	m_day  = 0;
	m_file = file;
	msgMut.unlock();
}

/**
* \brief 设置写日志等级
* \param  zLevelPtr 日志等级.参见 #zLogger::zLevel
*/
void zLogger::setLevel(const zLevel level)
{
	msgMut.lock();
	m_level = level;
	msgMut.unlock();
}

/**
* \brief 设置写日志等级
* \param  level 日志等级
*/
void zLogger::setLevel(const std::string &level)
{
	if ("off" == level) setLevel(LEVEL_OFF);
	else if ("fatal" == level) setLevel(LEVEL_FATAL);
	else if ("error" == level) setLevel(LEVEL_ERROR);
	else if ("warn" == level) setLevel(LEVEL_WARN);
	else if ("info" == level) setLevel(LEVEL_INFO);
	else if ("debug" == level) setLevel(LEVEL_DEBUG);
	else if ("all" == level) setLevel(LEVEL_ALL);
}

void zLogger::logtext(const zLevel level,const char * text)
{
	if (m_level > level) return;
	log(level,"%s",text);  
}

void zLogger::logva(const zLevel level,const char * pattern,va_list vp)
{

	struct tm *now;
	time_t ltime;
	char   szName[260];

	if (m_level > level) return;
	time(&ltime);
	if (NULL == (now=localtime(&ltime))) return;

#ifdef WIN32
	SYSTEMTIME system;
	GetLocalTime(&system);
#else

#endif


	msgMut.lock();

	if (!m_file.empty())
	{
		if (m_day != now->tm_mday)
		{
			if (NULL != fp_file)
			{
				fclose(fp_file);
			}
			m_day = now->tm_mday;
			snprintf(szName,sizeof(szName),"%s%04d%02d%02d.log",m_file.c_str(),now->tm_year + 1900,now->tm_mon + 1,now->tm_mday);
			fp_file = fopen(szName,"at");
		}
	}                 

	if (NULL != fp_console)
	{
		fprintf(fp_console,"[%s] ",m_name.c_str());
	}
	if (NULL != fp_file)
	{
		fprintf(fp_file,"[%s] ",m_name.c_str());
	}

	if (NULL != fp_console)
	{
		fprintf(fp_console,"%04d/%02d/%02d ",now->tm_year + 1900,now->tm_mon + 1,now->tm_mday);
		fprintf(fp_console,"%02d:%02d:%02d.%03d ",system.wHour,system.wMinute,system.wSecond, system.wMilliseconds);
	}
	if (NULL != fp_file)
	{
		fprintf(fp_file,"%04d/%02d/%02d ",now->tm_year + 1900,now->tm_mon + 1,now->tm_mday);
		fprintf(fp_file,"%02d:%02d:%02d.%03d ",system.wHour,system.wMinute,system.wSecond, system.wMilliseconds);
	}

	if (NULL != fp_console)
	{
		vfprintf(fp_console,pattern,vp);
		fprintf(fp_console,"\n");
		fflush(fp_console);
	}
	if (NULL != fp_file)
	{
		vfprintf(fp_file,pattern,vp);
		fprintf(fp_file,"\n");
		fflush(fp_file);
	}

	msgMut.unlock();
}

/**
* \brief 写日志
* \param  zLevelPtr 日志等级参见 #zLogger::zLevel
* \param  pattern 输出格式范例，与printf一样
* \return 无
*/
void zLogger::log(const zLevel level,const char * pattern,...)
{
	va_list vp;

	if (m_level > level) return;
	va_start(vp,pattern);
	logva(level,pattern,vp);
	va_end(vp);
}

/**
* \brief 写fatal程序日志
* \param  pattern 输出格式范例，与printf一样
* \return 无
*/
void zLogger::fatal(const char * pattern,...)
{
	va_list vp;

	if (m_level > LEVEL_FATAL) return;
	va_start(vp,pattern);
	logva(LEVEL_FATAL,pattern,vp);
	va_end(vp);
}

/**
* \brief 写error程序日志
* \param  pattern 输出格式范例，与printf一样
* \return 无
*/
void zLogger::error(const char * pattern,...)
{
	va_list vp;
	if (m_level > LEVEL_ERROR) return;
	va_start(vp,pattern);
	logva(LEVEL_ERROR,pattern,vp);
	va_end(vp);
}

/**
* \brief 写warn程序日志
* \param  pattern 输出格式范例，与printf一样
* \return 无
*/
void zLogger::warn(const char * pattern,...)
{
	va_list vp;

	if (m_level > LEVEL_WARN) return;
	va_start(vp,pattern);
	logva(LEVEL_WARN,pattern,vp);
	va_end(vp);
}

/**
* \brief 写info程序日志
* \param  pattern 输出格式范例，与printf一样
* \return 无
*/
void zLogger::info(const char * pattern,...)
{
	va_list vp;

	if (m_level > LEVEL_INFO) return;
	va_start(vp,pattern);
	logva(LEVEL_INFO,pattern,vp);
	va_end(vp);
}

/**
* \brief 写debug程序日志
* \param  pattern 输出格式范例，与printf一样
* \return 无
*/
void zLogger::debug(const char * pattern,...)
{
	va_list vp;

	if (m_level > LEVEL_DEBUG) return;
	va_start(vp,pattern);
	logva(LEVEL_DEBUG,pattern,vp);
	va_end(vp);
}

/*********************/
/* 输出16进制数据    */
/*********************/
void zLogger::debug16(const char* info, const BYTE* pData, int Datasize)
{
	struct tm *now;
	time_t ltime;
	char   szName[260];

	if (m_level > LEVEL_DEBUG) return;
	time(&ltime);
	if (NULL == (now=localtime(&ltime))) return;

#ifdef WIN32
	SYSTEMTIME system;
	GetLocalTime(&system);
#endif

	msgMut.lock();

	if (!m_file.empty())
	{
		if (m_day != now->tm_mday)
		{
			if (NULL != fp_file)
			{
				fclose(fp_file);
			}
			m_day = now->tm_mday;
			snprintf(szName,sizeof(szName),"%s%04d%02d%02d.log",m_file.c_str(),now->tm_year + 1900,now->tm_mon + 1,now->tm_mday);
			fp_file = fopen(szName,"at");
		}
	}
	if (NULL != fp_console)
	{
		fprintf(fp_console,"[%s] ",m_name.c_str());
	}
	if (NULL != fp_file)
	{
		fprintf(fp_file,"[%s] ",m_name.c_str());
	}

	if (NULL != fp_console)
	{
		fprintf(fp_console,"%04d/%02d/%02d ",now->tm_year + 1900,now->tm_mon + 1,now->tm_mday);
		//fprintf(fp_console,"%02d:%02d:%02d.%03d ",system.wHour,system.wMinute,system.wSecond, system.wMilliseconds);
	}
	if (NULL != fp_file)
	{
		fprintf(fp_file,"%04d/%02d/%02d ",now->tm_year + 1900,now->tm_mon + 1,now->tm_mday);
		//fprintf(fp_file,"%02d:%02d:%02d.%03d ",system.wHour,system.wMinute,system.wSecond, system.wMilliseconds);
	}

	if (NULL != fp_console)
	{
		fprintf(fp_console, "%s 长度 = %u:\n",info, Datasize );
		for(int i = 0; i < Datasize; i ++)
		{
			fprintf(fp_console,"%2.2X ", pData[i]);
		}
		fprintf(fp_console,"\n\n");
		fflush(fp_console);
	}
	if (NULL != fp_file)
	{
		fprintf(fp_file, "%s 长度 = %u :\n",info, Datasize);
		for(int i = 0; i < Datasize;i ++)
		{
			fprintf(fp_file,"%2.2X ", pData[i]);
		}
		fprintf(fp_file,"\n\n");
		fflush(fp_file);
	}

	msgMut.unlock();
}