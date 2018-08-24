#include "NetIOBuffer.h"


/*-------------------------------------------------------------------
 * @Brief : IO字节管理器
 * 
 * @Author:hzd 2012/04/03
 *------------------------------------------------------------------*/
NetIOBuffer::NetIOBuffer():m_nBegin(0),m_nLen(0),m_pBuffer(NULL),m_nMax(0)
{

}

NetIOBuffer::~NetIOBuffer()
{
}

void NetIOBuffer::InitBuffer(int32_t nMax)
{
	m_nMax = nMax;
	if(m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
	m_pBuffer = new char[nMax];
}


void NetIOBuffer::ReleaseBuffer()
{
	if(m_pBuffer)
	{
		delete[] m_pBuffer;
		m_pBuffer = NULL;
	}
}

bool NetIOBuffer::Write(char* recvBuf, int32_t bodyLen)
{
	boost::mutex::scoped_lock lock(m_cMutex);
	if(bodyLen > m_nMax - m_nBegin - m_nLen)
	{
		/* 将数据往前移 */ 
		if(m_nBegin < bodyLen)
		{
			lock.unlock();
			assert(0);
			return false;
		}
		memcpy(m_pBuffer,m_pBuffer + m_nBegin,m_nLen);
		m_nBegin = 0;
	}
	memcpy(m_pBuffer + m_nBegin + m_nLen, recvBuf, bodyLen);
	m_nLen += bodyLen;
	lock.unlock();
	return true;
}


void NetIOBuffer::Read(void** pMsg, int32_t nLen)
{
	if(nLen > m_nLen) return;

	*pMsg = m_pBuffer + m_nBegin;
}

int32_t NetIOBuffer::ReadRemove(void* pMsg, int32_t nLen)
{
	if(!m_nLen)	return m_nLen;

	boost::mutex::scoped_lock lock(m_cMutex);

	int nGetLen = 0;
	if(nLen < m_nLen)
		nGetLen = nLen;
	else
		nGetLen = m_nLen;

	memcpy(pMsg, m_pBuffer + m_nBegin, nGetLen);
	m_nLen -= nGetLen;
	if(m_nLen == 0)
		m_nBegin = 0;
	else
		m_nBegin += nGetLen;
	lock.unlock();
	return nGetLen;
}


void NetIOBuffer::RemoveBuffer(int32_t nLen)
{
	boost::mutex::scoped_lock lock(m_cMutex);
	m_nBegin += nLen;
	m_nLen -= nLen;
	if(m_nLen == 0)
		m_nBegin = 0;
	lock.unlock();
}

int32_t NetIOBuffer::GetLen()
{
	return m_nLen;
}
int32_t NetIOBuffer::GetSpace()
{
	return m_nMax - m_nBegin - m_nLen;
}
void* NetIOBuffer::GetBuffer()
{
	return m_pBuffer;
}
void* NetIOBuffer::GetStart()
{
	return m_pBuffer + m_nBegin;
}
void* NetIOBuffer::GetBufferEnd()
{
	return m_pBuffer + m_nBegin + m_nLen;
}

void NetIOBuffer::ClearBuffer()
{
	m_nBegin = 0;
	m_nLen = 0;
	memset(m_pBuffer, 0, m_nMax);
}

void NetIOBuffer::MoveBuffer()
{
	memcpy(m_pBuffer, m_pBuffer + m_nBegin, m_nLen);
	m_nBegin = m_nLen;
}




