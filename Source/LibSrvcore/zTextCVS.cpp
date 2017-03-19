#include "SrvEngine.h"


zTextCVS::zTextCVS(const std::string& strFileName, uint32 nFlagsRow, uint32 nDataStartRow)
	: m_nFlagsRow(nFlagsRow), m_nDataStartRow(nDataStartRow), m_nCurrRowIndex(0), m_bValid(false), m_nCol(0), m_nUseColCount(0)
{
	if (Load(strFileName.c_str()) && ReadFlagsRow() && NextRow())
	{
		m_bValid = true;
	}
}

zTextCVS::~zTextCVS()
{
	if (m_cFileStream.is_open())
		m_cFileStream.close();
}

bool zTextCVS::NextRow(int32 nLines)
{
	for (int32 i = 0; i < nLines; ++i)
	{
		m_nCol = 0;
		m_strLine.clear();
		m_vecCol.clear();

		if (std::getline(m_cFileStream, m_strLine))
		{
			if (m_strLine.empty())
			{
				return false;
			}else
			{
				//printf("Read row comment:%s\n",m_strLine.c_str());
			}
		}
		else
		{
			return false;
		}
	}

	if(strlen(m_strLine.c_str()) == 0 || strcmp(m_strLine.c_str(),"\n") == 0 || strcmp(m_strLine.c_str(),"\t") == 0 || strcmp(m_strLine.c_str(),"\r") == 0)
	{
		return false;
	}

	AnalyseLine(m_strLine, m_vecCol);

	if(m_vecCol.size() < 1)
	{
		return false;
	}
	return true;
}

bool zTextCVS::GetInt8(int8& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<int8>(atoi(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}
	printf("[ERROR]:GetInt8 fail!\n");
	return false;
}

bool zTextCVS::GetUInt8(uint8& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<uint8>(atoi(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}
	printf("[ERROR]:GetUInt8 fail!\n");
	return false;
}

bool zTextCVS::GetInt16(int16& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<int16>(atoi(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}
	printf("[ERROR]:GetInt16 fail!\n");
	return false;
}

bool zTextCVS::GetUInt16(uint16& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<uint16>(atoi(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}
	printf("[ERROR]:GetUInt16 fail!\n");
	return false;
}

bool zTextCVS::GetInt32(int32& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = atoi(m_vecCol[m_nCol - 1].c_str());
			return true;
		}
	}
	printf("[ERROR]:GetInt32 fail!\n");
	return false;
}

bool zTextCVS::GetUInt32(uint32& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = static_cast<uint32>(ATOL(m_vecCol[m_nCol - 1].c_str()));
			return true;
		}
	}
	printf("[ERROR]:GetUInt32 fail!\n");
	return false;
}

bool zTextCVS::GetInt64(int64& o_nValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_nValue = ATOL(m_vecCol[m_nCol - 1].c_str());
			return true;
		}
	}
	printf("[ERROR]:GetInt64 fail!\n");
	return false;
}

bool zTextCVS::GetFloat32(float32& o_fValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_fValue = ATOF(m_vecCol[m_nCol - 1].c_str());
			return true;
		}
	}
	return false;
}


bool zTextCVS::GetString(std::string& o_strValue)
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			o_strValue = m_vecCol[m_nCol - 1];
			return true;
		}
	}
	printf("[ERROR]:GetString fail!\n");
	return false;
}

const char* zTextCVS::GetCString()
{
	while (m_nCol < m_vecCol.size())
	{
		if (m_vecFlags[m_nCol++])
		{
			return m_vecCol[m_nCol - 1].c_str();
		}
	}
	return 0;
}

bool zTextCVS::Load(const char* cstrFileName)
{
	m_cFileStream.open(cstrFileName, std::ios::in);

	if (!m_cFileStream.is_open()	||
		m_cFileStream.fail()		||
		m_cFileStream.bad())
	{
		printf("[ERROR]:file open fail!\n");
		return false;
	}

	return true;
}

bool zTextCVS::ReadFlagsRow()
{
	m_vecFlags.clear();
	m_nUseColCount = 0;

	// 跳过前面行并读取标志行 
	if (!NextRow(m_nFlagsRow))
	{
		printf("[ERROR]:NextRow read fail!\n");
		return false;
	}

	// 设置标记列 
	for (uint32 i = 0; i < m_vecCol.size(); ++i)
	{
		switch (m_vecCol[i].c_str()[0])
		{
		case '2':
		case '3':
		{
			m_vecFlags.push_back(true);
			++m_nUseColCount;
		} break;
		default:
		{
			m_vecFlags.push_back(false);
		} break;
		}
	}

	return true;
}

void zTextCVS::AnalyseLine(const std::string& i_strLine, std::vector<std::string>& o_vecCol)
{
	o_vecCol.resize(0);

	std::string col;
	std::stringstream ss(i_strLine);

	while (true)
	{
		col.clear();
		ss >> col;
		if (col.empty())
		{
			break;
		}
		m_vecCol.push_back(col);
	}
}

