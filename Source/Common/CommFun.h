#ifndef COMMFUN_H_
#define  COMMFUN_H_

#include <cstdlib>
#include<string>
#include<locale.h>
#include<iostream> 
#include <time.h>
#include <vector>
#include <stdint.h>
#include <iostream>

#include "StringUtils.h"

#ifdef _WIN32
#include <windows.h>
#include <conio.h>
#elif defined __linux__
#include<stdio.h>
#include<stdlib.h>
#include<termios.h>
#include<term.h>
#include<curses.h>
#include<unistd.h>
#include<iconv.h> 
#include <fcntl.h>
static struct termios initial_settings, new_settings;  
static int peek_character = -1;  
void init_keyboard();  
void close_keyboard();  
inline int kbhit()  
{  
    char ch;  
    int nread;  
    if(peek_character != -1)  
        return 1;  
    new_settings.c_cc[VMIN]=0;  
    tcsetattr(0, TCSANOW, &new_settings);  
    nread = read(0,&ch,1);  
    new_settings.c_cc[VMIN]=1;  
    tcsetattr(0, TCSANOW, &new_settings);  
    if(nread == 1) {  
        peek_character = ch;  
        return 1;  
    }  
    return 0;  
}  


inline void init_keyboard()  
{  
    tcgetattr(0,&initial_settings);  
    new_settings = initial_settings;  
    new_settings.c_lflag &= ~ICANON;  
    new_settings.c_lflag &= ~ECHO;  
    new_settings.c_lflag &= ~ISIG;  
    new_settings.c_cc[VMIN] = 1;  
    new_settings.c_cc[VTIME] = 0;  
    tcsetattr(0, TCSANOW, &new_settings);  
} 
inline void close_keyboard()  
{  
    tcsetattr(0, TCSANOW, &initial_settings);  
} 

#endif


using namespace std;

inline void AtoPlayerID( const string& str, uint64_t& playerID )
{
#ifndef _WIN32
    playerID = atoll(str.c_str());
#else
    playerID = _atoi64(str.c_str());
#endif
}

/*string替换所有指定字符串 注意用法
    例如将"12212"这个字符串的所有"12"都替换成"21" 
    replace_all    结果为22211
    replace_all_distinct  结果为21221
*/
inline string  replace_all(  string& str, const string& old_value, const string& new_value)     
{     
    while(true)   {     
        string::size_type   pos(0);     
        if(   (pos=str.find(old_value))!=string::npos   )     
            str.replace(pos,old_value.length(),new_value);     
        else   break;     
    }     
    return   str;     
}     

inline string  replace_all_distinct(  string& str,const string& old_value,const string&  new_value)     
{     
    for(string::size_type   pos(0);   pos!=string::npos;   pos+=new_value.length())   {     
        if(   (pos=str.find(old_value,pos))!=string::npos   )     
            str.replace(pos,old_value.length(),new_value);     
        else   break;     
    }     
    return   str;     
}

//string和wstring相互转换,使用CRT库的mbstowcs()函数和wcstombs()函数和平台无关。
//wstring to string
inline string ws2s( wstring ws )
{
	string curLocale = setlocale( LC_ALL, NULL );
	setlocale( LC_ALL, "chs" );
	const wchar_t* _Source = ws.c_str();
	size_t _Dsize = 2*ws.size()+1;
	char* _Dest = new char[_Dsize];
	memset(_Dest,0,_Dsize);
	wcstombs(_Dest,_Source,_Dsize);
	string result = _Dest;
	delete []_Dest;
	setlocale( LC_ALL,curLocale.c_str());
	return result;
}
//string to wstring
inline wstring s2ws( std::string s)
{
	std::string curLocale = setlocale(LC_ALL, NULL); // curLocale = "C";
	setlocale(LC_ALL, "chs");
	const char* _Source = s.c_str();
	size_t _Dsize = s.size() + 1; 
	wchar_t *_Dest = new wchar_t[_Dsize];
	wmemset(_Dest, 0, _Dsize);
	mbstowcs(_Dest,_Source,_Dsize);
	std::wstring result = _Dest;
	delete []_Dest;
	setlocale(LC_ALL, curLocale.c_str());
	return result;
}

inline string GBKToUTF8(const string& strGBK)
{
#ifdef _WIN32
	wchar_t* str1;
	int n = MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, NULL, 0);
	str1 = new wchar_t[n];
	MultiByteToWideChar(CP_ACP, 0, strGBK.c_str(), -1, str1, n);
	n = WideCharToMultiByte(CP_UTF8, 0, str1, -1, NULL, 0, NULL, NULL);
	char * str2 = new char[n];
	WideCharToMultiByte(CP_UTF8, 0, str1, -1, str2, n, NULL, NULL);
	string strOutUTF8(str2);
	delete[]str1;
	str1 = NULL;
	delete[]str2;
	str2 = NULL;
	return strOutUTF8;
#else
    if (strGBK.empty())
    {
        return "";
    }
	iconv_t cd = iconv_open("UTF-8","GB18030");
	size_t inlen = strGBK.length();
	char *outbuf = (char *)malloc(inlen * 4 );
	bzero( outbuf, inlen * 4);
	const char *in = strGBK.c_str();
	char *out = outbuf;
	size_t outlen = inlen *4;
    if ( iconv(cd, (char**)&in, (size_t *)&inlen, &out,&outlen) == (size_t)-1 )
    {
        int nErr=errno; 
        switch( nErr )  
        {  
        case E2BIG:  
            {  
                printf("errno:E2BGI（OutBuf空间不够）\n");  
                break;  
            }  
        case EILSEQ:  
            {  
                printf("errno:EILSEQ（InBuf多字节序无效）\n");  
                break;  
            }  
        case EINVAL:  
            {  
                printf("errno:EINVAL（有残留的字节未转换）\n");  
                break;  
            }  
        default:  
            break;  
        }  
        free(outbuf);
        iconv_close(cd);
        return "";
    }
    else
    {
        outlen = strlen(outbuf);
        string strOutUTF8(outbuf);
        free(outbuf);
        iconv_close(cd);
        return strOutUTF8;
    }
#endif
}

//utf-8 转 gbk
inline string UTF8ToGBK(const string& strUTF8)
{
#ifdef _WIN32
	int len = MultiByteToWideChar(CP_UTF8, 0, strUTF8.c_str(), -1, NULL, 0);
	unsigned short * wszGBK = new unsigned short[len + 1];
    //wchar_t * wszGBK = new wchar_t[len+1];
	memset(wszGBK, 0, len * 2 + 2);
	MultiByteToWideChar(CP_UTF8, 0, (const char*)strUTF8.c_str(), -1, (LPWSTR)wszGBK, len);
	len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
	char *szGBK = new char[len + 1];
	memset(szGBK, 0, len + 1);
	WideCharToMultiByte(CP_ACP,0, (LPCWSTR)wszGBK, -1, szGBK, len, NULL, NULL);
	string strTemp(szGBK);
	delete[]szGBK;
	delete[]wszGBK;
	return strTemp;
#else
	iconv_t cd = iconv_open( "gb18030", "utf-8");
	size_t inlen = strUTF8.length();
	char *outbuf = (char *)malloc(inlen * 4 );
	bzero( outbuf, inlen * 4);
	const char *in = strUTF8.c_str();
	char *out = outbuf;
	size_t outlen = inlen *4;
	if ( iconv(cd, (char**)&in, (size_t *)&inlen, &out,&outlen) == (size_t) -1 )
	{
        int nErr=errno; 
        switch( nErr )  
        {  
        case E2BIG:  
            {  
                printf("errno:E2BGI（OutBuf空间不够）\n");  
                break;  
            }  
        case EILSEQ:  
            {  
                printf("errno:EILSEQ（InBuf多字节序无效）\n");  
                break;  
            }  
        case EINVAL:  
            {  
                printf("errno:EINVAL（有残留的字节未转换）\n");  
                break;  
            }  
        default:  
            break;  
        }  
        free(outbuf);
        iconv_close(cd);
        return "";
	}
    else
    {
        outlen = strlen(outbuf);
        string strOutGBK(outbuf);
        free(outbuf);
        iconv_close(cd);
        return strOutGBK;
    }
   
#endif
}

inline uint64_t StrTouint64_t(const string & s)
{
#ifdef _WIN32
	return _strtoui64(s.c_str(), NULL, 10);
#else
	return strtoull(s.c_str(), NULL, 10);
#endif
}

inline void SplitStringToFloat(const std::string& strSrc, const std::string& strToken, std::vector<float>& vecResult)
{
    vecResult.clear();
    std::string::size_type nBegin = 0;
    std::string::size_type nEnd   = 0;

    while( (nBegin = strSrc.find_first_not_of(strToken.c_str(), nEnd) ) != std::string::npos )
    {
        nEnd = strSrc.find_first_of(strToken.c_str(), nBegin);
        vecResult.push_back( (float)atof( strSrc.substr(nBegin, nEnd - nBegin).c_str()) );
    }
}
inline bool IsDigital(const string &s)
{
	int len = s.length();
	int i=0;
	for (; i<len; ++i)
	{
		if (s[i] < '0' || s[i] > '9')
		{
			return false;
		}
	}

	return i?true:false;
}

inline bool IsDigital_2(const string &s)
{
	int len = s.length();
	int i=0;
	for (; i<len; ++i)
	{
		if (i==0 && s[0] == '-')
		{
			continue;
		}
		if (s[i] < '0' || s[i] > '9')
		{
			return false;
		}
	}

	return i?true:false;
}

inline time_t StringToUnixTime(const char *str)  
{  
    tm tm_;  
    int year = 1900, month = 1, day = 0, hour = 0, minute = 0,second = 0;  
    sscanf(str,"%d-%d-%d %d:%d:%d", &year, &month, &day, &hour, &minute, &second);  
    tm_.tm_year  = year-1900;  
    tm_.tm_mon   = month-1;  
    tm_.tm_mday  = day;  
    tm_.tm_hour  = hour;  
    tm_.tm_min   = minute;  
    tm_.tm_sec   = second;  
    tm_.tm_isdst = 0;  

    return mktime(&tm_); //已经减了8个时区  
}

inline bool CheckIsDigit( string str )
{
    int nCount = str.length(); // 获得字符个数
    for ( int i = 0; i < nCount; i ++ )
    {
        if ( 0 == isdigit( str.at(i) ) ) // 不是数字就置标志位
        {
            return false;
        }
    }
    return true;
}

inline string remove_space(const string & str)
{
	string sNew;

	for (size_t i = 0; i < str.size(); ++i)
	{
		if (/*str[i] == ' ' || */str[i] == '\n' || str[i] == '\r')
		{
			continue;
		}

		sNew.push_back(str[i]);
	}

	return sNew;
}

inline int32_t GetNowSecond()
{
    return time(NULL);
}

inline int32_t GetNextTime(int32_t hour, int32_t min, int32_t sec, int32_t basetime = 0)
{
    hour = hour > 0 ? hour : 0;
    min = min > 0 ? min : 0;
    sec = sec > 0 ? sec : 0;
    hour = hour < 24 ? hour : (hour % 24);
    min = min < 60 ? min : (min % 60);
    sec = sec < 60 ? sec : (sec % 60);
    time_t tmpTime = basetime;

    if (tmpTime <= 0)
    {
        tmpTime = time(NULL);
    }

    tm* tmp_tm = localtime(&tmpTime);
    tmpTime -= tmp_tm->tm_hour * 3600 + tmp_tm->tm_min * 60 + tmp_tm->tm_sec;
    tmpTime += hour * 3600 + min * 60 + sec;

    if (tmpTime > time(NULL))
    {
        return tmpTime;
    }

    return tmpTime + 24 * 3600;
}

// 获取今日0点
inline int32_t GetTodayZero()
{
    int32_t hour =0;
    int32_t min = 0;
    int32_t sec = 0;
    time_t tmpTime = time(NULL);
    tm* tmp_tm = localtime(&tmpTime);
    tmpTime -= tmp_tm->tm_hour * 3600 + tmp_tm->tm_min * 60 + tmp_tm->tm_sec;
    tmpTime += hour * 3600 + min * 60 + sec;
    if (tmpTime > time(NULL))
    {
        return tmpTime;
    }
    return tmpTime + 24 * 3600;
}

// 获取0点 根据时间戳
inline time_t GetZeroByTimeStamp(time_t tTimeStamp)
{
	tm* tmp_tm = localtime(&tTimeStamp);
	tTimeStamp -= tmp_tm->tm_hour * 3600 + tmp_tm->tm_min * 60 + tmp_tm->tm_sec;

	return tTimeStamp;
}

// 获取明日凌晨的时间(今晚24点)
inline int32_t GetNextDateTime()
{
    static int nextTime = 0;

    if (nextTime <= GetNowSecond())
    {
        nextTime = GetNextTime(0, 0, 0);
    }

    return nextTime;
}

// 获取星期
inline int32_t GetWeek()
{
    time_t tmpTime = time(NULL);
    tm* tmp_tm = localtime(&tmpTime);
    return tmp_tm->tm_wday;
}

inline void SplitString(const string & sStr, const char sDelimiter, vector<string> & vArray)
{
	if (sStr.empty())
		return;
	string::size_type nLen = 0;
	string strSub;
	string::size_type nPos = 0;
	string::size_type nPosEnd = 0;
	do
	{
		nPosEnd = sStr.find(sDelimiter, nPos);
		if (nPosEnd == sStr.npos)
		{
			nPosEnd = sStr.length();
		}

		if (nPosEnd == nPos)
		{
			vArray.push_back("");
			continue;
		}

		nLen = nPosEnd - nPos;
		strSub = sStr.substr(nPos, nLen);
		if (!strSub.empty())
		{
			vArray.push_back(remove_space(strSub));
		}
		else
		{
			vArray.push_back("");
		}

	} while ((nPos = nPosEnd + 1) < sStr.length());
}

inline int32_t RoundUp(float fVal, float epsilon = 0.0004f)
{
	int32_t nVal = (int32_t)fVal;
	return (fVal - nVal) < epsilon ? nVal : nVal + 1;
}

inline uint64_t CreateUUID(uint32_t nServerID)
{
	static uint32_t serialID = 0;
	++serialID;

	time_t now_time = time(NULL);

	return (((uint64_t)nServerID << 52)
		| ((uint64_t)now_time << 20)
		| ((uint64_t)(serialID & 0x000FFFFF)));
}

inline uint32_t GetUUIDMin(uint32_t unServerID)
{
	return unServerID << 26;
}

inline uint32_t GetUUIDMax(uint32_t unServerID)
{
	return (++unServerID << 26) - 1;
}

inline uint32_t GetServerIDBySessionID(uint32_t unSessionID)
{
	return (unSessionID >> 26) & 0x3F;
}

inline uint32_t GetServerIDByRoomID(uint32_t unRoomID)
{
	return unRoomID / 100000;
}

inline uint32_t GetMsgID(uint16_t usCmd, uint16_t usCCmd)
{
	return ((uint32_t)usCmd << 16) | ((uint32_t)(usCCmd & 0xFFFF));
}

inline uint16_t GetCmd(uint32_t unMsgID)
{
	return (uint16_t)((unMsgID >> 16) & 0x0000FFFF);
}

inline uint16_t GetCCmd(uint32_t unMsgID)
{
	return (uint16_t)(unMsgID & 0x0000FFFF);
}

inline uint32_t GenerateNewUserID(uint32_t unUserID, uint32_t unProductID)
{
	return (((unProductID % 10000) << 24) & 0xFF000000) + unUserID;
}

inline uint32_t GetDataUint32(const std::string& strData)
{
	std::string strData_copy = strData;
	StringUtils::replaceAll(strData_copy, "=", " ");
	std::stringstream smData(strData_copy);
	std::string strNULL;
	uint32_t unValue = 0;
	smData >> strNULL >> unValue;

	return unValue;
}

inline int32_t GetDataInt32(const std::string& strData)
{
	std::string strData_copy = strData;
	StringUtils::replaceAll(strData_copy, "=", " ");
	std::stringstream smData(strData_copy);
	std::string strNULL;
	int32_t unValue = 0;
	smData >> strNULL >> unValue;
	return unValue;
}

inline uint64_t GetDataUint64(const std::string& strData)
{
	std::string strData_copy = strData;
	StringUtils::replaceAll(strData_copy, "=", " ");
	std::stringstream smData(strData_copy);
	std::string strNULL;
	uint64_t ulValue = 0;
	smData >> strNULL >> ulValue;

	return ulValue;
}

inline std::string GetDataString(const std::string& strData)
{
	std::string strData_copy = strData;
	StringUtils::replaceAll(strData_copy, "=", " ");
	std::stringstream smData(strData_copy);
	std::string strNULL;
	std::string strValue;
	smData >> strNULL >> strValue;

	return strValue;
}

inline time_t GetTurnYmd()
{
	time_t now = time(NULL) - 18000;
	struct tm* t = localtime(&now);
	t->tm_hour = 0;
	t->tm_min = 0;
	t->tm_sec = 0;
	time_t todayStart = mktime(t);
	return todayStart;
}

std::string GetProjectName(const std::string& strPath);

#define DUMP_PROTO_MSG_INFO(msg) \
do { \
		std::cout << "Dump " << (msg).GetTypeName() << ":\n" << \
		(msg).DebugString(); \
} while (0)

#define DUMP_PROTO_MSG_WARNING(msg) \
do { \
		std::cout << "Dump " << (msg).GetTypeName() << ":\n" << \
		(msg).DebugString(); \
} while (0)

#define DUMP_PROTO_MSG_ERROR(msg) \
do { \
		std::cout <<  "Dump " << (msg).GetTypeName() << ":\n" << \
		(msg).DebugString(); \
} while (0)


#endif
