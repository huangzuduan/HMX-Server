
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
	void InitBuffer(int32 nMax);

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
	bool Write(char* c, int32 nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void Read(void** b, int32 nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32 ReadRemove(void* pMsg, int32 nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	void RemoveBuffer(int32 nLen);

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32 GetLen();

	/*
	 *
	 *	Detail: no
	 *   
	 *  Created by hzd 2015/05/31  
	 *
	 */
	int32 GetSpace();

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
	int32 m_nBegin;       // 下一次读/写的位置 
	int32 m_nLen;			// 已经接收数据长度(可能有多个包)  
	char* m_pBuffer;		// 字段容器  
	char* m_pBuffer2;		// 字段容器2 
	int32 m_nMax;         // 最大字段长度  

};

#endif



