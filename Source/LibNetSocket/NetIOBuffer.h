
/*
 *
 *	Detail: IOBuffer
 *   
 *  Copyright (c) Created by hzd 2012. All rights reserved.
 *
 */

#ifndef _NET_IOBUFFER_H_
#define _NET_IOBUFFER_H_

#include "NetConfig.h"

class NetIOBuffer
{
public:

	NetIOBuffer();
	~NetIOBuffer();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void InitBuffer(int32_t nMax);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void ReleaseBuffer();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	bool Write(char* c, int32_t nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void Read(void** b, int32_t nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32_t ReadRemove(void* pMsg, int32_t nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void RemoveBuffer(int32_t nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32_t GetLen();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32_t GetSpace();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void* GetBuffer();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void* GetStart();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void* GetBufferEnd();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void ClearBuffer();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void MoveBuffer();

protected:

	boost::mutex m_cMutex;		// 读/写锁 
	int32_t m_nBegin;       // 下一次读/写的位置 
	int32_t m_nLen;			// 已经接收数据长度(可能有多个包)  
	char* m_pBuffer;		// 字段容器  
	int32_t m_nMax;         // 最大字段长度  

};

#endif



