#ifndef __RESOURCE_BUFFER_H_
#define __RESOURCE_BUFFER_H_

#include "SrvEngine.h"

// stl include
//#include <stdlib.h>
//#include <fstream>
//#include <string>
//#include <sstream>
//#include <vector>

// self include
//#include "typedef.h"


/*
* 解析指标分隔符间隔的资源文件 
*/
class ResourceBuffer
{
public:
	ResourceBuffer(const std::string& strFileName, uint32 nFlagsRow = 4, uint32 nDataStartRow = 6);

	~ResourceBuffer();

	/*
	* 读取当前行后面的第nLines行  
	*/
	bool NextRow(int32 nLines = 1);

	/*
	* 获得数据块
	*/
	bool			GetInt8(int8& o_nValue);
	bool			GetUInt8(uint8& o_nValue);
	bool			GetInt16(int16& o_nValue);
	bool			GetUInt16(uint16& o_nValue);
	bool			GetInt32(int32& o_nValue);
	bool			GetUInt32(uint32& o_nValue);
	bool			GetInt64(int64& o_nValue);
	bool			GetFloat32(float32& o_fValue);
	bool			GetString(std::string& o_strValue);
	const char*		GetCString();

	// 可用列数 
	int32 UseColCount()
	{
		return m_nUseColCount;
	}

	// 是否可用 
	bool Valid()
	{
		return m_bValid;
	}

private:
	/*
	* 打开资源文件 
	*/
	bool Load(const char* cstrFileName);

	/*
	* 初始化标志列
	*/
	bool ReadFlagsRow();

	/*
	* 解析一行数据
	*/
	void AnalyseLine(const std::string& i_strLine, std::vector<std::string>& o_vecCol);

private:
	int32						m_nFlagsRow;		// 标志行(1:跳过不读取,2:读取,3:读取) 
	int32						m_nDataStartRow;	// 数据起始行 
	uint32						m_nCurrRowIndex;	// 当前读取到的行[0,xx) 

	bool						m_bValid;			// 文件是否可用 
	std::ifstream				m_cFileStream;		// 文件读入流 
	std::vector<bool>			m_vecFlags;			// 列可用状态 

	std::string					m_strLine;			// 当前读取行 
	std::vector<std::string>	m_vecCol;			// 当前读取行各列值 
	uint32						m_nCol;				// 当前读取行列索引 
	int32						m_nUseColCount;		// 可用列数量 
};

#endif

