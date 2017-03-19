#ifndef __SRV_ENGINE_H_
#define __SRV_ENGINE_H_

#include "csCommon.h"
#include "NetIncludes.h"

class zLogger;
class zProperties;
class zCond;
class zLock;
class zMutex;
class zMutex_scope_lock;
class zRWLock;
class zRWLock_scope_rdlock;
class zRWLock_scope_wrlock;
class zThread;
class zThreadGroup;
class zTCPTask;
class zTCPTaskPool;
class zSyncThread;
class zRecycleThread;
class zCheckconnectThread;
class zCheckwaitThread;
class zTCPClientTaskThread;
class zTimeTick;
class zTaskTimer;
class zRSA;
class zUtility;
class zTextCVS;

namespace H
{
	/**
	* \brief 游戏时间
	*
	*/
	extern volatile QWORD qwGameTime;

	/**
	* \brief 日志指针
	*
	*/
	extern zLogger *logger;

	/**
	* \brief 存取全局变量的容器
	*
	*/
	extern zProperties global;

	/**
	* \brief 时间缓存器
	*
	*/
	extern zTimeTick* timeTick;

	/**
	* \brief 密码生成器
	*
	*/
	extern zRSA* rsa;
};

template <typename Container>
inline void stringtok(Container &container, std::string const &in,
	const char * const delimiters = " \t\n",
	const int deep = 0)
{
	const std::string::size_type len = in.length();
	std::string::size_type i = 0;
	int count = 0;

	while (i < len)
	{
		i = in.find_first_not_of(delimiters, i);
		if (i == std::string::npos)
			return;   // nothing left

					  // find the end of the token
		std::string::size_type j = in.find_first_of(delimiters, i);

		count++;
		// push token
		if (j == std::string::npos
			|| (deep > 0 && count > deep)) {
			container.push_back(in.substr(i));
			return;
		}
		else
			container.push_back(in.substr(i, j - i));

		// set up for next loop
		i = j + 1;
	}
}

//手动调用构造函数，不分配内存
template<class _T1>
inline  void constructInPlace(_T1  *_Ptr)
{
	new (static_cast<void*>(_Ptr)) _T1();
}
/// 声明变长指令
#define BUFFER_CMD(cmd,name,len) char buffer##name[len];\
	cmd *name=(cmd *)buffer##name;memset(buffer##name,0,len);constructInPlace(name);

#define MAX_USERDATASIZE 64000

template <typename T>
class SingletonBase
{
public:
	SingletonBase() {}
	virtual ~SingletonBase() {}
	static T& getInstance()
	{
		assert(instance);
		return *instance;
	}
	static void newInstance()
	{
		SAFE_DELETE(instance);
		instance = new T();
	}
	static void delInstance()
	{
		SAFE_DELETE(instance);
	}
protected:
	static T* instance;
private:
	SingletonBase(const SingletonBase&);
	SingletonBase & operator= (const SingletonBase &);
};
template <typename T> T* SingletonBase<T>::instance = NULL;

using namespace std;

/**
* \brief 使所有的子类禁用拷贝构造函数和赋值符号
*
*/
class zNoncopyable
{

protected:

	/**
	* \brief 缺省构造函数
	*
	*/
	zNoncopyable() {};

	/**
	* \brief 缺省析构函数
	*
	*/
	~zNoncopyable() {};

private:

	/**
	* \brief 拷贝构造函数，没有实现，禁用掉了
	*
	*/
	zNoncopyable(const zNoncopyable&);

	/**
	* \brief 赋值操作符号，没有实现，禁用掉了
	*
	*/
	const zNoncopyable & operator= (const zNoncopyable &);

};

struct odds_t
{
	DWORD upNum;
	DWORD downNum;
};

//随机产生min~max之间的数字，包括min和max
int randBetween(int min, int max);

//获取几分之的几率
bool selectByOdds(const DWORD upNum, const DWORD downNum);

//获取几分之几的几率
bool selectByt_Odds(const odds_t &odds);

//获取百分之的几率
bool selectByPercent(const DWORD percent);

//获取万分之的几率
bool selectByTenTh(const DWORD tenth);


//获取十万分之的几率
bool selectByLakh(const DWORD lakh);

//获取亿分之之的几率
bool selectByOneHM(const DWORD lakh);



#pragma pack(push,1)

typedef UNORDERED_SET<void*> UsingBlocksSet;

// 自动扩展内存池(线程安全) 
class MemPool
{
public:
	MemPool(bool bInit, uint32 nSizeBlock, uint32 nNumPerSlice = 256)
		: m_bInit(bInit), m_nBlockSize(nSizeBlock), m_nBlockNumPerSlice(nNumPerSlice), m_nSliceSize(nSizeBlock * nNumPerSlice)
	{
		// 初始化不申请任何内存 
	}

	virtual ~MemPool()
	{
		// 释放申请的内存片 
		while (!m_staMemSlices.empty())
		{
			void* pSlice = m_staMemSlices.top();
			free(pSlice);
			m_staMemSlices.pop();
		}
	}

protected:
	virtual void* Create()
	{
		if (m_staBlocks.empty())
		{
			if (!enlarge())
			{
				return 0;
			}
		}

		void* pNewBlock = m_staBlocks.top();
		m_staBlocks.pop();
		m_setUsingBlocks.insert(pNewBlock);

		return pNewBlock;
	}

	virtual bool Destroy(void* pAllocatedBlock)
	{
		UsingBlocksSet::iterator iter = m_setUsingBlocks.find(pAllocatedBlock);
		if (iter != m_setUsingBlocks.end())
		{
			m_staBlocks.push(pAllocatedBlock);
			m_setUsingBlocks.erase(iter);

			return true;
		}
		else
		{
			return false;
		}
	}

private:

	// 申请内存片并管理内存块 
	bool enlarge()
	{
		// 内存片指针 
		void* pNewSlice = 0;

		// 申请内存片 
		if (m_bInit)
		{// 初始化0 
			pNewSlice = calloc(m_nBlockNumPerSlice, m_nBlockSize);
		}
		else
		{// 未初始化 
			pNewSlice = malloc(m_nSliceSize);
		}

		if (!pNewSlice)
		{
			return false;
		}

		// 管理内存片 
		m_staMemSlices.push(pNewSlice);

		// 管理内存块 
		int8* pBlock = reinterpret_cast<int8*>(pNewSlice);
		for (uint32 i = 0; i < m_nBlockNumPerSlice; ++i)
		{
			m_staBlocks.push(pBlock + m_nBlockSize * i);
		}

		return true;
	}

protected:
	UsingBlocksSet		m_setUsingBlocks;		// 使用中的内存块 

private:
	const bool			m_bInit;					// 是否初始化申请的内存 
	const uint32		m_nBlockSize;				// 内存块大小 
	const uint32		m_nBlockNumPerSlice;		// 内存片中内存块数量 
	const uint32		m_nSliceSize;				// 内存片大小 
	std::stack<void*>	m_staMemSlices;				// 内存片 
	std::stack<void*>	m_staBlocks;				// 内存块引用 
};

// 对象内存使用状态 
struct ObjMemInfo
{
	bool		bUsing;			// 正在使用 
	uint64		nMark;			// 内存标记(同一块内存分配给不同对象时标记不同，永不为0,目前为内存使用次数) 
};

// 使用管理信息的内存块 
class ManageInfoUsingBlocks
{
public:
	// 获取内存使用标记,返回0为获取失败 
	template<typename T>
	static uint64 GetMark(T* pAllocatedObj)
	{
		if (HaveManageInfo(pAllocatedObj))
		{
			ObjMemInfo& rInfo = *reinterpret_cast<ObjMemInfo*>(pAllocatedObj + sizeof(T));

			return rInfo.nMark;
		}

		return 0;
	}

	// 检测正在使用中的内存与标记是否一致 
	template<typename T>
	static bool CheckMark(T* pAllocatedObj, uint64 nMark)
	{
		if (HaveManageInfo(pAllocatedObj))
		{
			ObjMemInfo& rInfo = *reinterpret_cast<ObjMemInfo*>(pAllocatedObj + sizeof(T));

			return rInfo.bUsing && !(rInfo.nMark ^ nMark);
		}

		return false;
	}

public:
	static UsingBlocksSet s_setBlocks;	// 使用中含管理信息的内存块 

private:
	// 检测内存是否被管理 
	static bool HaveManageInfo(void* pAllocatedObj)
	{
		return s_setBlocks.find(pAllocatedObj) != s_setBlocks.end();
	}
};


// 对象池(必须实现CreateObj才可使用) 
template<typename T>
class zObjPool : protected MemPool
{
public:
	zObjPool(bool bIsManageInfo = false, uint32 nNumPerSlice = 256)
		: MemPool(bIsManageInfo, (bIsManageInfo ? (sizeof(T) + sizeof(ObjMemInfo)) : sizeof(T)), nNumPerSlice), m_bManageInfo(bIsManageInfo)
	{
	}

	virtual ~zObjPool()
	{
		// 保证在释放内存片之前,调用正在使用的内存块上对象的析构函数 
		for (UsingBlocksSet::iterator iter = m_setUsingBlocks.begin();
			iter != m_setUsingBlocks.end(); ++iter)
		{
			T* pT = reinterpret_cast<T*>(*iter);
			pT->~T();
		}
	}

	// T* CreateObj(...)
	T* CreateObj()
	{
		if (void* pMem = Create())
		{
			return new(pMem)T();
		}
		return 0;
	}

	template<typename PT1>
	T* CreateObj(PT1 param1)
	{
		if (void* pMem = Create())
		{
			return new(pMem)T(param1);
		}
		return 0;
	}

	template<typename PT1, typename PT2>
	T* CreateObj(PT1 param1, PT2 param2)
	{
		if (void* pMem = Create())
		{
			return new(pMem)T(param1, param2);
		}
		return 0;
	}

	template<typename PT1, typename PT2, typename PT3>
	T* CreateObj(PT1 param1, PT2 param2, PT3 param3)
	{
		if (void* pMem = Create())
		{
			return new(pMem)T(param1, param2, param3);
		}
		return 0;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4>
	T* CreateObj(PT1 param1, PT2 param2, PT3 param3, PT4 param4)
	{
		if (void* pMem = Create())
		{
			return new(pMem)T(param1, param2, param3, param4);
		}
		return 0;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4, typename PT5>
	T* CreateObj(PT1 param1, PT2 param2, PT3 param3, PT4 param4, PT5 param5)
	{
		if (void* pMem = Create())
		{
			return new(pMem)T(param1, param2, param3, param4, param5);
		}
		return 0;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6>
	T* CreateObj(PT1 param1, PT2 param2, PT3 param3, PT4 param4, PT5 param5, PT6 param6)
	{
		if (void* pMem = Create())
		{
			return new(pMem)T(param1, param2, param3, param4, param5, param6);
		}
		return 0;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6, typename PT7>
	T* CreateObj(PT1 param1, PT2 param2, PT3 param3, PT4 param4, PT5 param5, PT6 param6, PT7 param7)
	{
		if (void* pMem = Create())
		{
			return new(pMem)T(param1, param2, param3, param4, param5, param6, param7);
		}
		return 0;
	}

	template<typename PT1, typename PT2, typename PT3, typename PT4, typename PT5, typename PT6, typename PT7, typename PT8>
	T* CreateObj(PT1 param1, PT2 param2, PT3 param3, PT4 param4, PT5 param5, PT6 param6, PT7 param7, PT8 param8)
	{
		if (void* pMem = Create())
		{
			return new(pMem)T(param1, param2, param3, param4, param5, param6, param7, param8);
		}
		return 0;
	}

	bool DestroyObj(T* pAllocatedObj)
	{
		if (Destroy(pAllocatedObj))
		{
			pAllocatedObj->~T();

			return true;
		}
		else
		{
			return false;
		}
	}

protected:
	virtual void* Create()
	{
		if (uint8* pNewBlock = reinterpret_cast<uint8*>(MemPool::Create()))
		{
			if (m_bManageInfo)
			{
				ObjMemInfo& rInfo = *reinterpret_cast<ObjMemInfo*>(pNewBlock + sizeof(T));
				rInfo.bUsing = true;
				++rInfo.nMark;				// 使用标记永不为0 

				ManageInfoUsingBlocks::s_setBlocks.insert(pNewBlock);
			}

			return pNewBlock;
		}
		else
		{
			return 0;
		}
	}

	virtual bool Destroy(void* pAllocatedBlock)
	{
		if (MemPool::Destroy(pAllocatedBlock))
		{
			if (m_bManageInfo)
			{
				UsingBlocksSet::iterator iter = ManageInfoUsingBlocks::s_setBlocks.find(pAllocatedBlock);
				if (iter != ManageInfoUsingBlocks::s_setBlocks.end())
				{
					uint8* pBlock = reinterpret_cast<uint8*>(pAllocatedBlock);
					ObjMemInfo& rInfo = *reinterpret_cast<ObjMemInfo*>(pBlock + sizeof(T));
					rInfo.bUsing = false;

					ManageInfoUsingBlocks::s_setBlocks.erase(iter);
				}
			}

			return true;
		}
		else
		{
			return false;
		}
	}

private:
	bool						m_bManageInfo;				// 是否有内存管理信息 
};

template<typename T>
class ObjPoolFactory
{
protected:
	static zObjPool<T> objpool;
};

template< typename T >
zObjPool<T> ObjPoolFactory< T >::objpool;

// 对象池管理接口(用于不符合谁创建谁销毁的情况) 
struct IObjPoolManagement
{
public:
	virtual void recycle() = 0;
};



#pragma pack(pop)


/**
* \brief 临界区，封装了系统临界区，避免了使用系统临界区时候需要手工初始化和销毁临界区对象的操作
*
*/
class zMutex : private zNoncopyable
{

	friend class zCond;

public:

	//	/**
	//	* \brief 构造函数，构造一个临界区对象
	//	*
	//	*/
	//	zMutex() 
	//	{
	//		InitializeCriticalSection(&m_critical);
	//	}
	//
	//	/**
	//	* \brief 析构函数，销毁一个临界区对象
	//	*
	//	*/
	//	~zMutex()
	//	{
	//		DeleteCriticalSection(&m_critical);
	//	}
	//
	//	/**
	//	* \brief 加锁一个临界区
	//	*
	//	*/
	//	inline void lock()
	//	{
	////		Zebra::logger->debug("Locking - %0.8X - %s(%u)", (DWORD)this, file,line );
	//		EnterCriticalSection(&m_critical);
	////		Zebra::logger->debug("Locked - %0.8X - %s(%u)", (DWORD)this, file,line );
	//	}
	//
	//	/**
	//	* \brief 解锁一个临界区
	//	*
	//	*/
	//	inline void unlock()
	//	{
	////		Zebra::logger->debug("UnLock - %0.8X - %s(%u)", (DWORD)this, file,line );
	//		LeaveCriticalSection(&m_critical);
	//	}
	//
	//private:
	//
	//	CRITICAL_SECTION    m_critical; // 系统临界区
	/**
	* \brief 构造函数，构造一个互斥体对象
	*
	*/
	zMutex()
	{
		//m_hMutex = CreateMutex(NULL, FALSE, NULL);
	}

	/**
	* \brief 析构函数，销毁一个互斥体对象
	*
	*/
	~zMutex()
	{
		//CloseHandle(m_hMutex);
	}

	/**
	* \brief 加锁一个互斥体
	*
	*/
	inline void lock()
	{
		//if (WaitForSingleObject(m_hMutex, 10000) == WAIT_TIMEOUT)
		//{
		//	char szName[MAX_PATH];
		//	GetModuleFileName(NULL, szName, sizeof(szName));
		//	::MessageBox(NULL, "发生死锁！", szName, MB_ICONERROR);
		//}
	}

	/**
	* \brief 解锁一个互斥体
	*
	*/
	inline void unlock()
	{
		//ReleaseMutex(m_hMutex);
	}

private:

	//HANDLE m_hMutex;    /**< 系统互斥体 */

};

/**
* \brief Wrapper
* 方便在复杂函数中锁的使用
*/
class zMutex_scope_lock : private zNoncopyable
{

public:

	/**
	* \brief 构造函数
	* 对锁进行lock操作
	* \param m 锁的引用
	*/
	zMutex_scope_lock(zMutex &m) : mlock(m)
	{
		mlock.lock();
	}

	/**
	* \brief 析购函数
	* 对锁进行unlock操作
	*/
	~zMutex_scope_lock()
	{
		mlock.unlock();
	}

private:

	/**
	* \brief 锁的引用
	*/
	zMutex &mlock;

};

/**
* \brief 时间定义
*
*
*/
/**
* \brief 真实时间类,对timeval结构简单封装,提供一些常用时间函数
* 时间精度精确到毫秒，
* 关于timeval请man gettimeofday
*/
class zRTime
{

private:

	/**
	* \brief 真实时间换算为毫秒
	*
	*/
	QWORD _msecs;

	/**
	* \brief 得到当前真实时间
	*
	* \return 真实时间，单位毫秒
	*/
	QWORD _now()
	{
		QWORD retval = 0LL;
		struct tm tv;
		getLocalTime(tv, NULL);
		retval = tv.tm_sec;
		return retval;
	}

	/**
	* \brief 得到当前真实时间延迟后的时间
	* \param delay 延迟，可以为负数，单位毫秒
	*/
	void nowByDelay(int delay)
	{
		_msecs = _now();
		addDelay(delay);
	}

public:

	/**
	* \brief 构造函数
	*
	* \param delay 相对于现在时间的延时，单位毫秒
	*/
	zRTime(const int delay = 0)
	{
		nowByDelay(delay);
	}

	/**
	* \brief 拷贝构造函数
	*
	* \param rt 拷贝的引用
	*/
	zRTime(const zRTime &rt)
	{
		_msecs = rt._msecs;
	}

	/**
	* \brief 获取当前时间
	*
	*/
	void now()
	{
		_msecs = _now();
	}

	/**
	* \brief 返回秒数
	*
	* \return 秒数
	*/
	DWORD sec() const
	{
		return _msecs / 1000;
	}

	/**
	* \brief 返回毫秒数
	*
	* \return 毫秒数
	*/
	DWORD msec() const
	{
		return _msecs % 1000;
	}

	/**
	* \brief 返回总共的毫秒数
	*
	* \return 总共的毫秒数
	*/
	QWORD msecs() const
	{
		return _msecs;
	}

	/**
	* \brief 返回总共的毫秒数
	*
	* \return 总共的毫秒数
	*/
	void setmsecs(QWORD data)
	{
		_msecs = data;
	}

	/**
	* \brief 加延迟偏移量
	*
	* \param delay 延迟，可以为负数，单位毫秒
	*/
	void addDelay(int delay)
	{
		_msecs += delay;
	}

	/**
	* \brief 重载=运算符号
	*
	* \param rt 拷贝的引用
	* \return 自身引用
	*/
	zRTime & operator= (const zRTime &rt)
	{
		_msecs = rt._msecs;
		return *this;
	}

	/**
	* \brief 重构+操作符
	*
	*/
	const zRTime & operator+ (const zRTime &rt)
	{
		_msecs += rt._msecs;
		return *this;
	}

	/**
	* \brief 重构-操作符
	*
	*/
	const zRTime & operator- (const zRTime &rt)
	{
		_msecs -= rt._msecs;
		return *this;
	}

	/**
	* \brief 重构>操作符，比较zRTime结构大小
	*
	*/
	bool operator > (const zRTime &rt) const
	{
		return _msecs > rt._msecs;
	}

	/**
	* \brief 重构>=操作符，比较zRTime结构大小
	*
	*/
	bool operator >= (const zRTime &rt) const
	{
		return _msecs >= rt._msecs;
	}

	/**
	* \brief 重构<操作符，比较zRTime结构大小
	*
	*/
	bool operator < (const zRTime &rt) const
	{
		return _msecs < rt._msecs;
	}

	/**
	* \brief 重构<=操作符，比较zRTime结构大小
	*
	*/
	bool operator <= (const zRTime &rt) const
	{
		return _msecs <= rt._msecs;
	}

	/**
	* \brief 重构==操作符，比较zRTime结构是否相等
	*
	*/
	bool operator == (const zRTime &rt) const
	{
		return _msecs == rt._msecs;
	}

	/**
	* \brief 计时器消逝的时间，单位毫秒
	* \param rt 当前时间
	* \return 计时器消逝的时间，单位毫秒
	*/
	QWORD elapse(const zRTime &rt) const
	{
		if (rt._msecs > _msecs)
			return (rt._msecs - _msecs);
		else
			return 0LL;
	}

	static std::string & getLocalTZ(std::string & s);
	static void getLocalTime(struct tm & tv1, time_t timValue)
	{
		timValue += 8 * 60 * 60;
		tv1 = *gmtime(&timValue);
	}

};

/**
* \brief 时间类,对struct tm结构简单封装
*/

class zTime
{

public:

	/**
	* \brief 构造函数
	*/
	zTime()
	{
		time(&secs);
		zRTime::getLocalTime(tv, secs);
	}

	/**
	* \brief 拷贝构造函数
	*/
	zTime(const zTime &ct)
	{
		secs = ct.secs;
		zRTime::getLocalTime(tv, secs);
	}

	/**
	* \brief 获取当前时间
	*/
	void now()
	{
		time(&secs);
		zRTime::getLocalTime(tv, secs);
	}

	/**
	* \brief 返回存储的时间
	* \return 时间，秒
	*/
	time_t sec() const
	{
		return secs;
	}

	/**
	* \brief 重载=运算符号
	* \param rt 拷贝的引用
	* \return 自身引用
	*/
	zTime & operator= (const zTime &rt)
	{
		secs = rt.secs;
		return *this;
	}

	/**
	* \brief 重构+操作符
	*/
	const zTime & operator+ (const zTime &rt)
	{
		secs += rt.secs;
		return *this;
	}

	/**
	* \brief 重构-操作符
	*/
	const zTime & operator- (const zTime &rt)
	{
		secs -= rt.secs;
		return *this;
	}

	/**
	* \brief 重构-操作符
	*/
	const zTime & operator-= (const time_t s)
	{
		secs -= s;
		return *this;
	}

	/**
	* \brief 重构>操作符，比较zTime结构大小
	*/
	bool operator > (const zTime &rt) const
	{
		return secs > rt.secs;
	}

	/**
	* \brief 重构>=操作符，比较zTime结构大小
	*/
	bool operator >= (const zTime &rt) const
	{
		return secs >= rt.secs;
	}

	/**
	* \brief 重构<操作符，比较zTime结构大小
	*/
	bool operator < (const zTime &rt) const
	{
		return secs < rt.secs;
	}

	/**
	* \brief 重构<=操作符，比较zTime结构大小
	*/
	bool operator <= (const zTime &rt) const
	{
		return secs <= rt.secs;
	}

	/**
	* \brief 重构==操作符，比较zTime结构是否相等
	*/
	bool operator == (const zTime &rt) const
	{
		return secs == rt.secs;
	}

	/**
	* \brief 计时器消逝的时间，单位秒
	* \param rt 当前时间
	* \return 计时器消逝的时间，单位秒
	*/
	time_t elapse(const zTime &rt) const
	{
		if (rt.secs > secs)
			return (rt.secs - secs);
		else
			return 0;
	}

	/**
	* \brief 计时器消逝的时间，单位秒
	* \return 计时器消逝的时间，单位秒
	*/
	time_t elapse() const
	{
		zTime rt;
		return (rt.secs - secs);
	}

	/**
	* \brief 得到当前分钟，范围0-59点
	*
	* \return
	*/
	int getSec()
	{
		return tv.tm_sec;
	}

	/**
	* \brief 得到当前分钟，范围0-59点
	*
	* \return
	*/
	int getMin()
	{
		return tv.tm_min;
	}

	/**
	* \brief 得到当前小时，范围0-23点
	*
	* \return
	*/
	int getHour()
	{
		return tv.tm_hour;
	}

	/**
	* \brief 得到天数，范围1-31
	*
	* \return
	*/
	int getMDay()
	{
		return tv.tm_mday;
	}

	/**
	* \brief 得到当前星期几，范围1-7
	*
	* \return
	*/
	int getWDay()
	{
		return tv.tm_wday;
	}

	/**
	* \brief 得到当前月份，范围1-12
	*
	* \return
	*/
	int getMonth()
	{
		return tv.tm_mon + 1;
	}

	/**
	* \brief 得到当前年份
	*
	* \return
	*/
	int getYear()
	{
		return tv.tm_year + 1900;
	}

private:

	/**
	* \brief 存储时间，单位秒
	*/
	time_t secs;

	/**
	* \brief tm结构，方便访问
	*/
	struct tm tv;


};

class Timer
{
public:
	Timer(const float how_long, const int delay = 0) : _long((int)(how_long * 1000)), _timer(delay * 1000)
	{

	}
	Timer(const float how_long, const zRTime cur) : _long((int)(how_long * 1000)), _timer(cur)
	{
		_timer.addDelay(_long);
	}
	void next(const zRTime &cur)
	{
		_timer = cur;
		_timer.addDelay(_long);
	}
	bool operator() (const zRTime& current)
	{
		if (_timer <= current) {
			_timer = current;
			_timer.addDelay(_long);
			return true;
		}

		return false;
	}
private:
	int _long;
	zRTime _timer;
};

/**
* \brief 场景上物件定义
*/
#pragma pack(1)


/**
* \brief 封装了系统读写锁，使用上要简单，省去了手工初始化和销毁系统读写锁的工作，这些工作都可以由构造函数和析构函数来自动完成
*
*/
class zRWLock : private zNoncopyable
{

public:
	/**
	* \brief 构造函数，用于创建一个读写锁
	*
	*/
	zRWLock()
	{
		//m_hMutex = CreateMutex(NULL, FALSE, NULL);
	}

	/**
	* \brief 析构函数，用于销毁一个读写锁
	*
	*/
	~zRWLock()
	{
		//CloseHandle(m_hMutex);
	}

	/**
	* \brief 对读写锁进行读加锁操作
	*
	*/
	inline void rdlock()
	{
		//WaitForSingleObject(m_hMutex, INFINITE);
	};

	/**
	* \brief 对读写锁进行写加锁操作
	*
	*/
	inline void wrlock()
	{
		//WaitForSingleObject(m_hMutex, INFINITE);
	}

	/**
	* \brief 对读写锁进行解锁操作
	*
	*/
	inline void unlock()
	{
		//ReleaseMutex(m_hMutex);
	}

private:

	//HANDLE m_hMutex;    /**< 系统读写锁 */

};

template <typename V>
class Parse
{
public:
	V* operator () (const std::string& down, const std::string& separator_down)
	{
		std::string::size_type pos = 0;
		if ((pos = down.find(separator_down)) != std::string::npos) {

			std::string first_element = down.substr(0, pos);
			std::string second_element = down.substr(pos + separator_down.length());
			return new V(first_element, second_element);
		}

		return NULL;
	}
};

template <typename V>
class Parse3
{
public:
	V* operator () (const std::string& down, const std::string& separator_down)
	{
		std::string::size_type pos = 0;
		if ((pos = down.find(separator_down)) != std::string::npos) {

			std::string first_element = down.substr(0, pos);
			std::string::size_type npos = 0;
			if ((npos = down.find(separator_down, pos + separator_down.length())) != std::string::npos) {
				std::string second_element = down.substr(pos + separator_down.length(), npos - pos);
				std::string third_element = down.substr(npos + separator_down.length());
				return new V(first_element, second_element, third_element);
			}
		}

		return NULL;
	}
};


/**
* \brief  分隔由二级分隔符分隔的字符串
* \param list 待分隔的字符串
* \param dest 存储分隔结果，必须满足特定的语义要求
* \param separator_up 一级分隔符
* \param separator_down 二级分隔符
*/
template <template <typename> class P = Parse>
class Split
{
public:

	template <typename T>
	void operator() (const std::string& list, T& dest, const std::string& separator_up = ";", const std::string& separator_down = ",")
	{
		typedef typename T::value_type value_type;
		typedef typename T::pointer pointer;

		std::string::size_type lpos = 0;
		std::string::size_type pos = 0;
		P<value_type> p;


		while ((lpos = list.find(separator_up, pos)) != std::string::npos) {
			/*
			std::string down = list.substr(pos,lpos - pos);
			std::string::size_type dpos = 0;
			if  ( (dpos = down.find(separator_down)) != std::string::npos ) {

			std::string first_element = down.substr(0,dpos);
			std::string second_element = down.substr(dpos+separator_down.length());
			dest.push_back(typename T::value_type(first_element,second_element));
			}
			pos = lpos+1;
			*/
			std::string down = list.substr(pos, lpos - pos);
			pointer v = p(down, separator_down);
			if (v) {
				dest.push_back(*v);
				SAFE_DELETE(v);
			}
			pos = lpos + 1;
		}

		std::string down = list.substr(pos, lpos - pos);
		pointer v = p(down, separator_down);
		if (v) {
			dest.push_back(*v);
			SAFE_DELETE(v);
		}
	}
};


/**
* \brief zUniqueID模板
* 本模板实现了唯一ID生成器，并保证线程安全。
* 可以用各种长度的无符号整数作为ID。
*/
template <class T>
class zUniqueID :private zNoncopyable
{
private:
	zMutex mutex;
	//std::list<T,__pool_alloc<T> > ids;
	std::list<T> ids;
	T maxID;
	T minID;
	T curMaxID;
	void init(T min, T max)
	{
		minID = min;
		maxID = max;
		curMaxID = minID;
	}

public:
	/**
	* \brief 默认构造函数
	* 开始ID为1，最大有效ID为(T)-2,无效ID为(T)-1
	*/
	zUniqueID()
	{
		init(1, (T)-1);
	}

	/**
	* \brief 构造函数
	* 用户自定义起始ID，最大有效ID为(T)-2,无效ID为(T)-1
	* \param startID 用户自定义的起始ID
	*/
	zUniqueID(T startID)
	{
		init(startID, (T)-1);
	}

	/**
	* \brief 构造函数
	* 用户自定义起始ID，及最大无效ID,最大有效ID为最大无效ID-1
	* \param startID 用户自定义的起始ID
	* \param endID 用户自定义的最大无效ID
	*/
	zUniqueID(T startID, T endID)
	{
		init(startID, endID);
	}

	/**
	* \brief 析构函数
	* 回收已分配的ID内存。
	*/
	~zUniqueID()
	{
		//mutex.lock();
		ids.clear();
		//mutex.unlock();
	}

	/**
	* \brief 得到最大无效ID
	* \return 返回最大无效ID
	*/
	T invalid()
	{
		return maxID;
	}

	/**
	* \brief 测试这个ID是否被分配出去
	* \return 被分配出去返回true,无效ID和未分配ID返回false
	*/
	bool hasAssigned(T testid)
	{
		//mutex.lock();
		if (testid<maxID && testid >= minID)
		{
			typename std::list<T/*,__pool_alloc<T>*/ >::iterator iter = ids.begin();
			for (; iter != ids.end(); iter++)
			{
				if (*iter == testid)
				{
					mutex.unlock();
					return false;
				}
			}
			/*
			for(int i=0,n=ids.size() ;i<n;i++)
			{
			if (ids[i]==testid)
			{
			mutex.unlock();
			return false;
			}
			}
			// */
			mutex.unlock();
			return true;
		}
		//mutex.unlock();
		return false;
	}

	/**
	* \brief 得到一个唯一ID
	* \return 返回一个唯一ID，如果返回最大无效ID，比表示所有ID都已被用，无可用ID。
	*/
	T get()
	{
		T ret;
		mutex.lock();
		if (maxID>curMaxID)
		{
			ret = curMaxID;
			curMaxID++;
		}
		else
			ret = maxID;
		if (ret == maxID && !ids.empty())
		{
			ret = ids.back();
			ids.pop_back();
		}
		mutex.unlock();
		return ret;
	}

	/**
	* \brief 一次得到多个ID，这些ID都是相邻的,并且不回被放回去
	* \param size 要分配的ID个数
	* \param count 实际分配ID的个数
	* \return 返回第一个ID，如果返回最大无效ID，比表示所有ID都已被用，无可用ID。
	*/
	T get(int size, int & count)
	{
		T ret;
		mutex.lock();
		if (maxID>curMaxID)
		{
			count = (maxID - curMaxID)>size ? size : (maxID - curMaxID);
			ret = curMaxID;
			curMaxID += count;
		}
		else
		{
			count = 0;
			ret = maxID;
		}
		mutex.unlock();
		return ret;
	}

	/**
	* \brief 将ID放回ID池，以便下次使用。
	*
	* 放回的ID必须是由get函数得到的。并且不能保证放回的ID,没有被其他线程使用。
	* 所以用户要自己保证还在使用的ID不会被放回去。以免出现ID重复现象。
	* \param id 由get得到的ID.
	*/
	void put(T id)
	{
		mutex.lock();
		if (id<maxID && id >= minID)
		{
			bool hasID = false;
			typename std::list<T/*,__pool_alloc<T> */>::iterator iter = ids.begin();
			for (; iter != ids.end(); iter++)
			{
				if (*iter == id)
				{
					hasID = true;
					break;
				}
			}
			/*
			for(int i=0,n=ids.size() ;i<n;i++)
			{
			if (ids[i]==id)
			{
			hasID=true;
			break;
			}
			}
			// */
			if (!hasID) ids.push_front(id);
			//if (!hasID) ids.insert(ids.begin(),id);
			//if (!hasID) ids.push_back(id);
		}
		//mutex.unlock();
	}
};

typedef zUniqueID<QWORD> zUniqueDWORDID;

#pragma pack(1)

struct zEntryC
{
	/**
	* \brief entry的数据ID，不同类型的Entry可能会重复,此时不能实现从ID查找entry
	*/
	QWORD id;
	/**
	* \brief entry的临时id,建议在实现EntryManager时，保证分配唯一
	*/
	QWORD tempid;
	/**
	* \brief entry的名字，不同类型的Entry可能会重复,此时不能实现从名字查找entry
	*/
	char name[MAX_NAMESIZE + 1];
	zEntryC()
	{
		id = 0;
		tempid = 0;
		bzero(name, sizeof(name));
	};
};


#define CreateEntryC(TempName) \
struct zEntryC##TempName \
{\
	QWORD id;\
	QWORD TempName;\
	char name[MAX_NAMESIZE + 1];\
	zEntryC##TempName()\
	{\
		id = 0;\
		TempName = 0;\
		bzero(name, sizeof(name));\
	};\
};


/**
* \brief 回调函数类模板
*/
template <typename T, typename RTValue = bool>
struct zEntryCallback
{
	virtual RTValue exec(T *e) = 0;
	virtual ~zEntryCallback() {};
};


struct zEntry :public zEntryC, private zNoncopyable
{
	virtual ~zEntry() {};
	zEntry() :zEntryC()
	{
	};
};

#define CreateEntry(TempName) \
struct zEntry##TempName :public zEntryC##TempName, private zNoncopyable \
{\
	virtual ~zEntry##TempName() {};\
	zEntry##TempName() :zEntryC##TempName()\
	{\
	};\
};

/**
* \brief key值等值比较,目前支持 (DWORD,char *)，两种类型
*/
template <class keyT>
struct my_key_equal : public std::binary_function<keyT, keyT, bool>
{
	inline bool operator()(const keyT s1, const keyT s2) const;
};

/**
* \brief 模板偏特化
* 对字符串进行比较
*/
template<>
inline bool my_key_equal<const char *>::operator()(const char * s1, const char * s2) const
{
	return strcmp(s1, s2) == 0;
}

/**
* \brief 模板偏特化
* 对整数进行比较
*/
template<>
inline bool my_key_equal<DWORD>::operator()(const DWORD s1, const DWORD s2) const
{
	return s1 == s2;
}

/**
* \brief 有限桶Hash管理模板,非线程安全
*
* 目前支持两种key类型(DWORD,char *),value类型不作限制,但此类型要可copy的。
* \param keyT key类型(DWORD,char *)
* \param valueT value类型
*/
template <class keyT, class valueT>
class LimitHash :private zNoncopyable
{
protected:

	/**
	* \brief hash_map容器
	*/
	//typedef hash_map<keyT,valueT,hash<keyT>,my_key_equal<keyT> > hashmap;
	typedef UNORDERED_MAP<keyT, valueT> hashmap;
	typedef typename hashmap::iterator iter;
	typedef typename hashmap::const_iterator const_iter;
	hashmap ets;

	/**
	* \brief 插入数据，如果原来存在相同key值的数据，原来数据将会被替换
	* \param key key值
	* \param value 要插入的数据
	* \return 成功返回true，否则返回false
	*/
	inline bool insert(const keyT &key, valueT &value)
	{
		ets[key] = value;
		return true;
	}

	/**
	* \brief 根据key值查找并得到数据
	* \param key 要寻找的key值
	* \param value 返回结果将放入此处,未找到将不会改变此值
	* \return 查找到返回true，未找到返回false
	*/
	inline bool find(const keyT &key, valueT &value) const
	{
		const_iter it = ets.find(key);
		if (it != ets.end())
		{
			value = it->second;
			return true;
		}
		else
			return false;
	}

	/**
	* \brief 查找并得到一个数据
	* \param value 返回结果将放入此处,未找到将不会改变此值
	* \return 查找到返回true，未找到返回false
	*/
	inline bool findOne(valueT &value) const
	{
		if (!ets.empty())
		{
			value = ets.begin()->second;
			return true;
		}
		return false;
	}

	/**
	* \brief 构造函数
	*
	*/
	LimitHash()
	{
	}

	/**
	* \brief 析构函数,清除所有数据
	*/
	~LimitHash()
	{
		clear();
	}

	/**
	* \brief 移除数据
	* \param key 要移除的key值
	*/
	inline void remove(const keyT &key)
	{
		ets.erase(key);
	}

	/**
	* \brief 清除所有数据
	*/
	inline void clear()
	{
		ets.clear();
	}

	/**
	* \brief 统计数据个数
	*/
	inline DWORD size() const
	{
		return ets.size();
	}

	/**
	* \brief 判断容器是否为空
	*/
	inline bool empty() const
	{
		return ets.empty();
	}
};

/**
* \brief 有限桶MultiHash管理模板,非线程安全
*
* 目前支持两种key类型(DWORD,char *),value类型不作限制,但此类型要可copy的。
* \param keyT key类型(DWORD,char *)
* \param valueT value类型
*/
template <class keyT, class valueT>
class MultiHash :private zNoncopyable
{
protected:

	/**
	* \brief hash_multimap容器
	*/
	//typedef hash_multimap<keyT,valueT,hash<keyT>,my_key_equal<keyT> > hashmap;
	typedef UNORDERED_MULTIMAP<keyT, valueT> hashmap;
	typedef typename hashmap::iterator iter;
	typedef typename hashmap::const_iterator const_iter;
	hashmap ets;

	/**
	* \brief 插入数据，如果原来存在相同key值的数据，原来数据将会被替换
	* \param key key值
	* \param value 要插入的数据
	* \return 成功返回true，否则返回false
	*/
	inline bool insert(const keyT &key, valueT &value)
	{
		//if(ets.find(key) == ets.end())
		ets.insert(std::pair<keyT, valueT>(key, value));
		return true;
	}

	/**
	* \brief 构造函数
	*
	*/
	MultiHash()
	{
	}

	/**
	* \brief 析构函数,清除所有数据
	*/
	~MultiHash()
	{
		clear();
	}

	/**
	* \brief 清除所有数据
	*/
	inline void clear()
	{
		ets.clear();
	}

	/**
	* \brief 统计数据个数
	*/
	inline DWORD size() const
	{
		return ets.size();
	}

	/**
	* \brief 判断容器是否为空
	*/
	inline bool empty() const
	{
		return ets.empty();
	}
};

/**
* \brief Entry以临时ID为key值的指针容器，需要继承使用
*/

class zEntryTempID :public LimitHash<QWORD, zEntry *>
{
protected:

	zEntryTempID() {}
	virtual ~zEntryTempID() {}

	/**
	* \brief 将Entry加入容器中,tempid重复添加失败
	* \param e 要加入的Entry
	* \return 成功返回true,否则返回false
	*/
	inline bool push(zEntry* e)
	{
		if (e != NULL && getUniqeID(e->tempid))
		{
			zEntry *temp;
			if (!find(e->tempid, temp))
			{
				if (insert(e->tempid, e))
					return true;
			}
			putUniqeID(e->tempid);
		}
		return false;
	}

	/**
	* \brief 移除Entry
	* \param e 要移除的Entry
	*/
	inline void remove(zEntry* e)
	{
		if (e != NULL)
		{
			putUniqeID(e->tempid);
			LimitHash<QWORD, zEntry *>::remove(e->tempid);
		}
	}

	/**
	* \brief 通过临时ID得到Entry
	* \param tempid 要得到Entry的临时ID
	* \return 返回Entry指针,未找到返回NULL
	*/
	inline zEntry* getEntryByTempID(const QWORD tempid) const
	{
		zEntry *ret = NULL;
		LimitHash<QWORD, zEntry *>::find(tempid, ret);
		return ret;
	}

	/**
	* \brief 得到一个临时ID
	* \param tempid 存放要得到的临时ID
	* \return 得到返回true,否则返回false
	*/
	virtual bool getUniqeID(QWORD &tempid) = 0;
	/**
	* \brief 放回一个临时ID
	* \param tempid 要放回的临时ID
	*/
	virtual void putUniqeID(const QWORD &tempid) = 0;
};

#define CreateEntryTempID(TempName) \
class zEntryTempID##TempName :public LimitHash<QWORD, zEntry##TempName *>\
{\
protected:\
	zEntryTempID##TempName() {}\
	virtual ~zEntryTempID##TempName() {}\
	inline bool push(zEntry##TempName* e)\
	{\
		if (e != NULL && getUniqeID(e->##TempName))\
		{\
			zEntry##TempName *temp;\
			if (!find(e->##TempName, temp))\
			{\
				if (insert(e->##TempName, e))\
					return true;\
			}\
			putUniqeID(e->##TempName);\
		}\
		return false;\
	}\
	inline void remove(zEntry##TempName* e)\
	{\
		if (e != NULL)\
		{\
			putUniqeID(e->##TempName);\
			LimitHash<QWORD, zEntry##TempName *>::remove(e->##TempName);\
		}\
	}\
	inline zEntry##TempName* getEntryBy##TempName(const QWORD TempName) const\
	{\
		zEntry##TempName *ret = NULL;\
		LimitHash<QWORD, zEntry##TempName *>::find(TempName, ret);\
		return ret;\
	}\
	virtual bool getUniqeID(QWORD &##TempName) = 0;\
	virtual void putUniqeID(const QWORD &##TempName) = 0;\
};

/**
* \brief Entry以ID为key值的指针容器，需要继承使用
*/
class zEntryID :public LimitHash<QWORD, zEntry *>
{
protected:
	/**
	* \brief 将Entry加入容器中
	* \param e 要加入的Entry
	* \return 成功返回true,否则返回false
	*/
	inline bool push(zEntry * &e)
	{
		zEntry *temp;
		if (!find(e->id, temp))
			return insert(e->id, e);
		else
			return false;
	}

	/**
	* \brief 移除Entry
	* \param e 要移除的Entry
	*/
	inline void remove(zEntry * e)
	{
		if (e != NULL)
		{
			LimitHash<QWORD, zEntry *>::remove(e->id);
		}
	}

	/**
	* \brief 通过ID得到Entry
	* \param id 要得到Entry的ID
	* \return 返回Entry指针,未找到返回NULL
	*/
	inline zEntry * getEntryByID(const QWORD id) const
	{
		zEntry *ret = NULL;
		LimitHash<QWORD, zEntry *>::find(id, ret);
		return ret;
	}
};

#define CreateEntryID(TempName) \
class zEntryID##TempName :public LimitHash<QWORD, zEntry##TempName *>\
{\
protected:\
	inline bool push(zEntry##TempName * &e)\
	{\
		zEntry##TempName *temp;\
		if (!find(e->id, temp))\
			return insert(e->id, e);\
		else\
			return false;\
	}\
	inline void remove(zEntry##TempName * e)\
	{\
		if (e != NULL)\
		{\
			LimitHash<QWORD, zEntry##TempName *>::remove(e->id);\
		}\
	}\
	inline zEntry##TempName * getEntryByID(const QWORD id) const\
	{\
		zEntry##TempName *ret = NULL;\
		LimitHash<QWORD, zEntry##TempName *>::find(id, ret);\
		return ret;\
	}\
};

/**
* \brief Entry以名字为key值的指针容器，需要继承使用
*/
class zEntryName :public LimitHash<std::string, zEntry *>
{
protected:
	/**
	* \brief 将Entry加入容器中,如果容器中有相同key值的添加失败
	* \param e 要加入的Entry
	* \return 成功返回true,否则返回false
	*/
	inline bool push(zEntry * &e)
	{
		zEntry *temp;
		if (!find(std::string(e->name), temp))
			return insert(std::string(e->name), e);
		else
			return false;
	}

	/**
	* \brief 移除Entry
	* \param e 要移除的Entry
	*/
	inline void remove(zEntry * e)
	{
		if (e != NULL)
		{
			LimitHash<std::string, zEntry *>::remove(std::string(e->name));
		}
	}

	/**
	* \brief 通过名字得到Entry
	* \param name 要得到Entry的名字
	* \return 返回Entry指针,未找到返回NULL
	*/
	inline zEntry * getEntryByName(const char * name) const
	{
		zEntry *ret = NULL;
		LimitHash<std::string, zEntry *>::find(std::string(name), ret);
		return ret;
	}

	/**
	* \brief 通过名字得到Entry
	* \param name 要得到Entry的名字
	* \return 返回Entry指针,未找到返回NULL
	*/
	inline zEntry * getEntryByName(const std::string  &name) const
	{
		return getEntryByName(name.c_str());
	}
};

#define CreateEntryName(TempName) \
class zEntryName##TempName :public LimitHash<std::string, zEntry##TempName *>\
{\
protected:\
	inline bool push(zEntry##TempName * &e)\
	{\
		zEntry##TempName *temp;\
		if (!find(std::string(e->name), temp))\
			return insert(std::string(e->name), e);\
		else\
			return false;\
	}\
	inline void remove(zEntry##TempName * e)\
	{\
		if (e != NULL)\
		{\
			LimitHash<std::string, zEntry##TempName *>::remove(std::string(e->name));\
		}\
	}\
	inline zEntry##TempName * getEntryByName(const char * name) const\
	{\
		zEntry##TempName *ret = NULL;\
		LimitHash<std::string, zEntry##TempName *>::find(std::string(name), ret);\
		return ret;\
	}\
	inline zEntry##TempName * getEntryByName(const std::string  &name) const\
	{\
		return getEntryByName(name.c_str());\
	}\
};

/**
* \brief Entry以名字为key值的指针容器，需要继承使用
*/
class zMultiEntryName :public MultiHash</*const char **/std::string, zEntry *>
{
protected:
	/**
	* \brief 将Entry加入容器中,如果容器中有相同key值的添加失败
	* \param e 要加入的Entry
	* \return 成功返回true,否则返回false
	*/
	inline bool push(zEntry * &e)
	{
		return insert(std::string(e->name), e);
	}

	/**
	* \brief 将Entry从容器中移除
	* \param e 需要移除的Entry
	*/
	inline void remove(zEntry * &e)
	{
		pair<iter, iter> its = ets.equal_range(std::string(e->name));
		for (iter it = its.first; it != its.second; it++)
		{
			if (it->second == e)
			{
				ets.erase(it);
				return;
			}
		}
	}

	/**
	* \brief 根据key值查找并得到数据
	* \param name 要寻找的name值
	* \param e 返回结果将放入此处,未找到将不会改变此值
	* \param r 如果有多项匹配，是否随机选择
	* \return 查找到返回true，未找到返回false
	*/
	inline bool find(const char * &name, zEntry * &e, const bool r = false) const
	{
		int rd = ets.count(std::string(name));
		if (rd > 0)
		{
			int mrd = 0, j = 0;
			if (r)
				randBetween(0, rd - 1);
			pair<const_iter, const_iter> its = ets.equal_range(std::string(name));
			for (const_iter it = its.first; it != its.second && j < rd; it++, j++)
			{
				if (mrd == j)
				{
					e = it->second;
					return true;
				}
			}
		}
		return false;
	}

};

template<int i>
class zEntryNone
{
protected:
	inline bool push(zEntry * &e) { return true; }
	inline void remove(zEntry * &e) { }
	inline void clear() {}
};

#define CreateEntryNone(TempName) \
template<int i>\
class zEntryNone##TempName\
{\
protected:\
	inline bool push(zEntry##TempName * &e) { return true; }\
	inline void remove(zEntry##TempName * &e) { }\
	inline void clear() {}\
};

template<int i>
class zEntryNoneQ
{
protected:
	inline bool push(zEntry * &e) { return true; }
	inline void remove(zEntry * &e) { }
	inline void clear() {}
};

/**
* \brief Entry处理接口,由<code>zEntryMgr::execEveryEntry</code>使用
*/
template <class YourEntry>
struct execEntry
{
	virtual bool exec(YourEntry *entry) = 0;
	virtual ~execEntry() {}
};

/**
* \brief Entry删除条件接口,由<code>zEntryMgr::removeEntry_if</code>使用
*/
template <class YourEntry>
struct removeEntry_Pred
{
	/**
	* \brief 被删除的entry存储在这里
	*/
	std::vector<YourEntry *> removed;
	/**
	* \brief 测试是否要删除的entry,需要实现
	* \param 要被测试的entry
	*/
	virtual bool isIt(YourEntry *entry) = 0;
	/**
	* \brief 析构函数
	*/
	virtual ~removeEntry_Pred() {}
};

/**
* \brief Entry管理器接口,用户应该根据不同使用情况继承它
*/

template<typename e1, typename e2 = zEntryNone<1>, typename e3 = zEntryNone<2> >
class zEntryMgr :protected e1, protected e2, protected e3
{
protected:

	//unsigned long count;

	/**
	* \brief 添加Entry,对于重复索引的Entry添加失败
	* \param e 被添加的 Entry指针
	* \return 成功返回true，否则返回false
	*/
	inline bool addEntry(zEntry * e)
	{

		if (NULL == e)
			return false;
		//++count;
		// unsigned long t = count;

		//if( 765 == count)
		//{
		//Zebra::logger->error("%u\n",count);
		//fprintf(stderr,"%u\n",count);
		//  }
		if (e1::push(e))
		{
			//zEntry *ee = e1::getEntryByName(e->name); 
			if (e2::push(e))
			{

				if (e3::push(e))
					return true;
				else
				{
					e2::remove(e);
					e1::remove(e);
				}
			}
			else
				e1::remove(e);
		}
		return false;
	}

	/**
	* \brief 删除Entry
	* \param e 被删除的Entry指针
	*/
	inline void removeEntry(zEntry * e)
	{
		e1::remove(e);
		e2::remove(e);
		e3::remove(e);
	}


	zEntryMgr() { }
	/**
	* \brief 虚析构函数
	*/
	~zEntryMgr() { };

	/**
	* \brief 统计管理器中Entry的个数
	* \return 返回Entry个数
	*/
	inline int size() const
	{
		return e1::size();
	}

	/**
	* \brief 判断容器是否为空
	*/
	inline bool empty() const
	{
		return e1::empty();
	}

	/**
	* \brief 清除所有Entry
	*/
	inline void clear()
	{
		e1::clear();
		e2::clear();
		e3::clear();
	}

	/**
	* \brief 对每个Entry进行处理
	* 当处理某个Entry返回false时立即打断处理返回
	* \param eee 处理接口
	* \return 如果全部执行完毕返回true,否则返回false
	*/
	template <class YourEntry>
	inline bool execEveryEntry(execEntry<YourEntry> &eee)
	{
		typedef typename e1::iter my_iter;
		for (my_iter it = e1::ets.begin(); it != e1::ets.end(); it++)
		{
			if (!eee.exec((YourEntry *)it->second))
				return false;
		}
		return true;
	}

	/**
	* \brief 删除满足条件的Entry
	* \param pred 测试条件接口
	*/
	template <class YourEntry>
	inline void removeEntry_if(removeEntry_Pred<YourEntry> &pred)
	{
		typedef typename e1::iter my_iter;
		my_iter it = e1::ets.begin();
		while (it != e1::ets.end())
		{
			if (pred.isIt((YourEntry *)it->second))
			{
				pred.removed.push_back((YourEntry *)it->second);
			}
			it++;
		}

		for (DWORD i = 0; i<pred.removed.size(); i++)
		{
			removeEntry(pred.removed[i]);
		}
	}
};

#define CreateEntryManager(TempName) \
template<typename e1, typename e2 = zEntryNone##TempName<1>, typename e3 = zEntryNone##TempName<2> > \
class zEntryMgr##TempName :protected e1, protected e2, protected e3 \
{\
protected:\
	inline bool addEntry(zEntry##TempName * e)\
	{\
		if (NULL == e)\
			return false;\
		if (e1::push(e))\
		{\
			if (e2::push(e))\
			{\
				if (e3::push(e))\
					return true;\
				else\
				{\
					e2::remove(e);\
					e1::remove(e);\
				}\
			}\
			else\
				e1::remove(e);\
		}\
		return false;\
	}\
	inline void removeEntry(zEntry##TempName * e)\
	{\
		e1::remove(e);\
		e2::remove(e);\
		e3::remove(e);\
	}\
	zEntryMgr##TempName() { }\
	~zEntryMgr##TempName() { };\
	inline int size() const\
	{\
		return e1::size();\
	}\
	inline bool empty() const\
	{\
		return e1::empty();\
	}\
	inline void clear()\
	{\
		e1::clear();\
		e2::clear();\
		e3::clear();\
	}\
	template <class YourEntry>\
	inline bool execEveryEntry(execEntry<YourEntry> &eee)\
	{\
		typedef typename e1::iter my_iter;\
		for (my_iter it = e1::ets.begin(); it != e1::ets.end(); it++)\
		{\
			if (!eee.exec((YourEntry *)it->second))\
				return false;\
		}\
		return true;\
	}\
	template <class YourEntry>\
	inline void removeEntry_if(removeEntry_Pred<YourEntry> &pred)\
	{\
		typedef typename e1::iter my_iter;\
		my_iter it = e1::ets.begin();\
		while (it != e1::ets.end())\
		{\
			if (pred.isIt((YourEntry *)it->second))\
			{\
				pred.removed.push_back((YourEntry *)it->second);\
			}\
			it++;\
		}\
		for (DWORD i = 0; i<pred.removed.size(); i++)\
		{\
			removeEntry(pred.removed[i]);\
		}\
	}\
};


template <class TData>
class zDatabaseCallBack
{
public:
	virtual bool exec(TData *entry) = 0;
	virtual ~zDatabaseCallBack() {};
};

typedef zEntryMgr< zEntryID, zMultiEntryName> zDataManager;
template <class TData, class TBase>
class  zDataBM :public zDataManager
{
private:
	static zDataBM<TData, TBase> *me;
	zRWLock rwlock;
	zDataBM()
	{

	}

	class deleteEvery :public zDatabaseCallBack<TData>
	{
		bool exec(TData *entry)
		{
			delete entry;
			return true;
		}
	};

	~zDataBM()
	{
		deleteEvery temp;
		execAll(temp);
		rwlock.wrlock();
		clear();
		rwlock.unlock();
	}

	zEntry* getEntryByID(DWORD id)
	{
		zEntry* ret = NULL;
		zEntryID::find(id, ret);
		return ret;
	}

	void removeEntryByID(DWORD id)
	{
		zEntry * ret = NULL;
		if (zEntryID::find(id, ret))
			removeEntry(ret);
	}

	zEntry* getEntryByName(const char * name)
	{
		zEntry * ret = NULL;
		zMultiEntryName::find(name, ret, true);
		return ret;
	}

	void removeEntryByName(const char * name)
	{
		zEntry * ret = NULL;
		if (zMultiEntryName::find(name, ret))
			removeEntry(ret);
	}


public:

	static zDataBM & getMe()
	{
		if (me == NULL)
			me = new zDataBM();
		return *me;
	}

	static void delMe()
	{
		SAFE_DELETE(me);
	}

	bool refresh(TBase &base)
	{
		static DWORD id = base.getUniqueID();
		TData *o = (TData *)getEntryByID(base.getUniqueID());
		if (o == NULL)
		{
			o = new TData();
			if (o == NULL)
			{
				printf("无法分配内存\n");
				return false;
			}
			o->fill(base);
			if (!zDataManager::addEntry(o))
			{
				printf("添加Entry错误(%ld)(id=%ld,name=%s)\n", base.field0, o->id, o->name);
				SAFE_DELETE(o);
				return false;
			}
		}
		else
		{
			o->fill(base);
			//重新调整名字hash中的位置，这样即使名称改变也可以查询到
			zMultiEntryName::remove((zEntry * &)o);
			zMultiEntryName::push((zEntry * &)o);
		}
		return true;
	}

	TData *get(DWORD dataid)
	{
		rwlock.rdlock();
		TData *ret = (TData *)getEntryByID(dataid);
		rwlock.unlock();
		return ret;
	}

	TData *get(const char *name)
	{
		rwlock.rdlock();
		TData *ret = (TData *)getEntryByName(name);
		rwlock.unlock();
		return ret;
	}

	void execAll(zDatabaseCallBack<TData> &base)
	{
		rwlock.rdlock();
		for (zEntryID::hashmap::iterator it = zEntryID::ets.begin(); it != zEntryID::ets.end(); it++)
		{
			if (!base.exec((TData *)it->second))
			{
				rwlock.unlock();
				return;
			}
		}
		rwlock.unlock();
	}

	void listAll()
	{
		class listevery :public zDatabaseCallBack<TData>
		{
		public:
			int i;
			listevery()
			{
				i = 0;
			}
			bool exec(TData *zEntry)
			{
				i++;
				printf("%ld\t%s\n", zEntry->id, zEntry->name);
				return true;
			}
		};
		listevery le;
		execAll(le);
		printf("Total %d\n", le.i);
	}
};





struct aTypeS {
	aTypeS()
	{
		byValue[0] = 0;
		byValue[1] = 0;
	}
	union {
		struct {
			BYTE byAType;
			BYTE byAction;
		};
		BYTE byValue[2];
	};
};

struct CarryObject
{
	DWORD id;
	int   rate;
	int   minnum;
	int   maxnum;
	CarryObject()
	{
		id = 0;
		rate = 0;
		minnum = 0;
		maxnum = 0;
	}
};

typedef std::vector<CarryObject> NpcLostObject;

struct NpcCarryObject : private zNoncopyable
{
	NpcCarryObject() {};
	bool set(const char *objects)
	{
		bool retval = true;
		//mlock.lock();
		cov.clear();
		if (strcmp(objects, "0"))
		{
			std::vector<std::string> obs;
			stringtok(obs, objects, ";");
			for (std::vector<std::string>::const_iterator it = obs.begin(); it != obs.end(); it++)
			{
				std::vector<std::string> rt;
				stringtok(rt, *it, ":");
				if (3 == rt.size())
				{
					CarryObject co;
					co.id = atoi(rt[0].c_str());
					co.rate = atoi(rt[1].c_str());
					std::vector<std::string> nu;
					stringtok(nu, rt[2], "-");
					if (2 == nu.size())
					{
						co.minnum = atoi(nu[0].c_str());
						co.maxnum = atoi(nu[1].c_str());
						cov.push_back(co);
					}
					else
						retval = false;
				}
				else
					retval = false;
			}
		}
		//mlock.unlock();
		return retval;
	}

	/**
	* \brief 物品掉落处理
	* \param nlo npc携带物品集合
	* \param value 掉落率打折比
	* \param value1 掉落率增加
	* \param value2 银子掉落率增加
	*/
	void lost(NpcLostObject &nlo, int value, int value1, int value2, int vcharm, int vlucky, int player_level, int DropRate, int DropRateLevel)
	{
		//mlock.lock();
		if (vcharm>1000) vcharm = 1000;
		if (vlucky>1000) vlucky = 1000;
		for (std::vector<CarryObject>::const_iterator it = cov.begin(); it != cov.end(); it++)
		{
			//Zebra::logger->debug("%u,%u,%u,%u",(*it).id,(*it).rate,(*it).minnum,(*it).maxnum);
			switch ((*it).id)
			{
			case 665:
			{
				int vrate = (int)(((*it).rate / value)*(1 + value1 / 100.0f)*(1 + value2 / 100.0f)*(1 + vcharm / 1000.0f)*(1 + vlucky / 1000.0f));
				/*if (selectByTenTh(vrate))
				{
				nlo.push_back(*it);
				}*/
			}
			break;
			default:
			{
				int vrate = (int)(((*it).rate / value)*(1 + value1 / 100.0f)*(1 + vcharm / 1000.0f)*(1 + vlucky / 1000.0f));
				if (player_level <= DropRateLevel)
				{
					/*if (selectByTenTh(vrate * DropRate))
					{
					nlo.push_back(*it);
					}*/
				}
				else
				{
					/*if (selectByTenTh(vrate))
					{
					nlo.push_back(*it);
					}*/
				}
			}
			break;
			}
		}
		//mlock.unlock();
	}
	/**
	* \brief 全部物品掉落处理
	* \param nlo npc携带物品集合
	* \param value 掉落率打折比
	* \param value1 掉落率增加
	* \param value2 银子掉落率增加
	*/
	void lostAll(NpcLostObject &nlo)
	{
		for (std::vector<CarryObject>::const_iterator it = cov.begin(); it != cov.end(); it++)
		{
			nlo.push_back(*it);
		}
	}

	/**
	* \brief 装备物品全部掉落处理(绿怪专用)
	* \param nlo npc携带物品集合
	* \param value 掉落率打折比
	* \param value1 掉落率增加
	* \param value2 银子掉落率增加
	*/
	void lostGreen(NpcLostObject &nlo, int value = 1, int value1 = 0, int value2 = 0, int vcharm = 0, int vlucky = 0);
private:
	std::vector<CarryObject> cov;
	//zMutex mlock;
};


#pragma pack()

///npc使用一个技能的描述
struct npcSkill
{
	DWORD id;///技能id
	int needLevel;///技能id
	int rate;///使用几率
	int coefficient;///升级系数

	npcSkill() :id(0), needLevel(0), rate(0), coefficient(0) {}
	npcSkill(const npcSkill &skill)
	{
		id = skill.id;
		needLevel = skill.needLevel;
		rate = skill.rate;
		coefficient = skill.coefficient;
	}
	npcSkill& operator = (const npcSkill &skill)
	{
		id = skill.id;
		needLevel = skill.needLevel;
		rate = skill.rate;
		coefficient = skill.coefficient;
		return *this;
	}
};

struct npcRecover
{
	DWORD start;
	BYTE type;
	DWORD num;

	npcRecover()
	{
		start = 0;
		type = 0;
		num = 0;
	}

	void parse(const char * str)
	{
		if (!str) return;

		std::vector<std::string> vec;

		vec.clear();
		stringtok(vec, str, ":");
		if (3 == vec.size())
		{
			start = atoi(vec[0].c_str());
			type = atoi(vec[1].c_str());
			num = atoi(vec[2].c_str());
		}
	}
};




/**
* \brief A*寻路算法
*/
/**
* \brief A*寻路算法模板
* 其中step表示步长，radius表示搜索半径
*/
template <int step = 1, int radius = 12>
class zAStar
{

private:

	/**
	* \brief 路径坐标点
	*/
	struct zPathPoint
	{
		/**
		* \brief 坐标
		*/
		zPos pos;
		/**
		* \brief 当前距离
		*/
		int cc;
		/**
		* \brief 路径上一个结点指针
		*/
		zPathPoint *father;
	};

	/**
	* \brief 路径头
	*/
	struct zPathQueue
	{
		/**
		* \brief 路径节点头指针
		*/
		zPathPoint *node;
		/**
		* \brief 路径消耗距离
		*/
		int cost;
		/**
		* \brief 构造函数
		* \param node 初始化的路径节点头指针
		* \param cost 当前消耗距离
		*/
		zPathQueue(zPathPoint *node, int cost)
		{
			this->node = node;
			this->cost = cost;
		}
		/**
		* \brief 拷贝构造函数
		* \param queue 待拷贝的源数据
		*/
		zPathQueue(const zPathQueue &queue)
		{
			node = queue.node;
			cost = queue.cost;
		}
		/**
		* \brief 赋值操作符号
		* \param queue 待赋值的源数据
		* \return 返回结构的引用
		*/
		zPathQueue & operator= (const zPathQueue &queue)
		{
			node = queue.node;
			cost = queue.cost;
			return *this;
		}
	};

	/**
	* \brief 定义所有路径的链表
	*/
	typedef std::list<zPathQueue> zPathQueueHead;
	typedef typename zPathQueueHead::iterator iterator;
	typedef typename zPathQueueHead::reference reference;

	/**
	* \brief 估价函数
	* \param midPos 中间临时坐标点
	* \param endPos 最终坐标点
	* \return 估算出的两点之间的距离
	*/
	int judge(const zPos &midPos, const zPos &endPos)
	{
		int distance = abs((long)(midPos.x - endPos.x)) + abs((long)(midPos.y - endPos.y));
		return distance;
	}

	/**
	* \brief 进入路径队列
	* \param queueHead 路径队列头
	* \param pPoint 把路径节点添加到路径中
	* \param currentCost 路径的估算距离
	*/
	void enter_queue(zPathQueueHead &queueHead, zPathPoint *pPoint, int currentCost)
	{
		zPathQueue pNew(pPoint, currentCost);
		if (!queueHead.empty())
		{
			for (iterator it = queueHead.begin(); it != queueHead.end(); it++)
			{
				//队列按cost由小到大的顺序排列
				if ((*it).cost > currentCost)
				{
					queueHead.insert(it, pNew);
					return;
				}
			}
		}
		queueHead.push_back(pNew);
	}

	/**
	* \brief 从路径链表中弹出最近距离
	* \param queueHead 路径队列头
	* \return 弹出的最近路径
	*/
	zPathPoint *exit_queue(zPathQueueHead &queueHead)
	{
		zPathPoint *ret = NULL;
		if (!queueHead.empty())
		{
			reference ref = queueHead.front();
			ret = ref.node;
			queueHead.pop_front();
		}
		return ret;
	}

public:

	/**
	* \brief 寻路过程中判断中间点是否可达目的地
	*
	*  return (scene->zPosShortRange(tempPos,destPos,radius)
	*      && (!scene->checkBlock(tempPos) //目标点可达，或者是最终目标点
	*        || tempPos == destPos));
	*
	* \param tempPos 寻路过程的中间点
	* \param destPos 目的点坐标
	* \param radius 寻路范围，超出范围的视为目的地不可达
	* \return 返回是否可到达目的地
	*/
	virtual bool moveable(const zPos &tempPos, const zPos &destPos, const int _radius = radius) = 0;
	/**
	* \brief 物件向某一个方向移动
	* \param direct 方向
	* \param step 表示步长
	* \return 移动是否成功
	*/
	virtual bool move(const int direct, const int _step = step) = 0;
	/**
	* \brief 使物件向某一个点移动
	* 带寻路算法的移动
	* \param srcPos 起点坐标
	* \param destPos 目的地坐标
	* \return 移动是否成功
	*/
	bool gotoFindPath(const zPos &srcPos, const zPos &destPos);
	/**
	* \brief Npc向某一个点移动
	* \param srcPos 起点坐标
	* \param destPos 目的地坐标
	* \return 移动是否成功
	*/
	bool goTo(const zPos &srcPos, const zPos &destPos);
	/**
	* \brief Npc随机向某一个方向移动
	* \param direct 随机方向
	* \return 移动是否成功
	*/
	bool shiftMove(const int direct);

};

template<int step, int radius>
bool zAStar<step, radius>::gotoFindPath(const zPos &srcPos, const zPos &destPos)
{
	//DisMap是以destPos为中心的边长为2 * radius + 1 的正方形
	const int width = (2 * radius + 1);
	const int height = (2 * radius + 1);
	const int MaxNum = width * height;
	//把所有路径距离初始化为最大值
	std::vector<int> pDisMap(MaxNum, MaxNum);
	std::vector<zPathPoint> stack(MaxNum * 8 + 1);//在堆栈中分配内存
	zPathQueueHead queueHead;

	//从开始坐标进行计算
	zPathPoint *root = &stack[MaxNum * 8];
	root->pos = srcPos;
	root->cc = 0;
	root->father = NULL;
	enter_queue(queueHead, root, root->cc + judge(root->pos, destPos));

	int Count = 0;
	//无论如何,循环超过MaxNum次则放弃
	while (Count < MaxNum)
	{
		root = exit_queue(queueHead);
		if (NULL == root)
		{
			//目标点不可达
			return false;
		}

		if (root->pos == destPos)
		{
			//找到到达目的地的路径
			break;
		}

		const zAdjust adjust[8] =
		{
			{ 1 * step,0 * step },
			{ 0 * step,-1 * step },
			{ 0 * step,1 * step },
			{ -1 * step,0 * step },
			{ 1 * step,-1 * step },
			{ -1 * step,-1 * step },
			{ -1 * step,1 * step },
			{ 1 * step,1 * step }
		};
		for (int i = 0; i < 8; i++)
		{
			//分别对周围8个格点进行计算路径
			bool bCanWalk = true;
			zPos tempPos = root->pos;
			tempPos += adjust[i];

			if (moveable(tempPos, destPos))
			{
				//对路径进行回溯
				zPathPoint *p = root;
				while (p)
				{
					if (p->pos == tempPos)
					{
						//发现坐标点已经在回溯路径中，不能向前走
						bCanWalk = false;
						break;
					}
					p = p->father;
				}

				//如果路径回溯成功，表示这个点是可行走的
				if (bCanWalk)
				{
					int cost = root->cc + 1;
					int index = (tempPos.y - destPos.y + radius) * width + (tempPos.x - destPos.x + radius);
					if (index >= 0
						&& index < MaxNum
						&& cost < pDisMap[index])
					{
						//这条路径比上次计算的路径还要短，需要加入到最短路径队列中
						pDisMap[index] = cost;
						zPathPoint *pNewEntry = &stack[Count * 8 + i];
						pNewEntry->pos = tempPos;
						pNewEntry->cc = cost;
						pNewEntry->father = root;
						enter_queue(queueHead, pNewEntry, pNewEntry->cc + judge(pNewEntry->pos, destPos));
					}
				}
			}
		}

		Count++;
	}

	if (Count < MaxNum)
	{
		//最终路径在PointHead中,但只走一步
		while (root)
		{
			//倒数第二个节点
			if (root->father != NULL
				&& root->father->father == NULL)
			{
				return move(srcPos.getDirect(root->pos));
			}

			root = root->father;
		}
	}

	return false;
}

template<int step, int radius>
inline bool zAStar<step, radius>::goTo(const zPos &srcPos, const zPos &destPos)
{
	int direct = srcPos.getDirect(destPos);

	if (!move(direct)) {
		int r = randBetween(0, 1);
		int deep = 0;
		while (deep < 3) {
			switch (r) {
			case 0://顺时针
				direct++;
				break;
			case 1://逆时针
				direct += 7;
				break;
			}
			direct %= 8;
			if (move(direct))
				return true;
			deep++;
		}
	}

	return false;
}

template<int step, int radius>
inline bool zAStar<step, radius>::shiftMove(const int direct)
{
	return move(direct);
}


/**
* \brief 场景屏坐标
*/
typedef DWORD zPosI;

/**
* \brief 存放屏编号的向量
*
*/
typedef std::vector<zPosI> zPosIVector;
typedef std::vector<zPos> zPosVector;

typedef std::list<WORD> SceneEntryStateList;


//class zSceneEntryIndex;
/**
* \brief 场景上物件，比如人物,NPC,建筑，地上物品等
*
* 作用有两个
*
* 1.建立屏索引
* 2.定义阻挡
*/
struct zSceneEntry :public zEntry
{
	//friend class zSceneEntryIndex;
public:

	unsigned short dupIndex;
	/**
	* \brief 物件类型
	*/
	enum SceneEntryType
	{
		SceneEntry_Player,/**< 玩家角色*/
		SceneEntry_NPC,  /**< NPC*/
		SceneEntry_Build,/**< 建筑*/
		SceneEntry_Object,/**< 地上物品*/
		SceneEntry_Pet,  /**< 宠物*/
		SceneEntry_MAX
	};
	/**
	* \brief 物件状态
	*
	*/
	enum SceneEntryState
	{
		SceneEntry_Normal,  /**< 普通状态 */
		SceneEntry_Death,  /**< 死亡状态 */
		SceneEntry_Hide      /**< 隐藏状态 */
	};
	/**
	* \brief 坐标转化
	* \param screenWH 地图宽和高
	* \param pos 源坐标
	* \param posi 目的坐标
	*/
	static void zPos2zPosI(const zPos &screenWH, const zPos &pos, zPosI &posi)
	{
		posi = ((screenWH.x + SCREEN_WIDTH - 1) / SCREEN_WIDTH) * (pos.y / SCREEN_HEIGHT) + (pos.x / SCREEN_WIDTH);
	}
protected:
	/**
	* \brief 构造函数
	*/
	zSceneEntry(SceneEntryType type, const SceneEntryState state = SceneEntry_Normal) :sceneentrytype(type), sceneentrystate(state)
	{
		bzero(byState, sizeof(byState));
		dir = _DIR_DOWN;
		inserted = false;
		dupIndex = 0;
	}

	/**
	* \brief 坐标
	*/
	zPos pos;
	/**
	* \brief 屏坐标
	*/
	zPosI posi;
	/**
	* \brief 方向
	*
	*/
	BYTE dir;

	zPos lastPos1;
	zPos lastPos2;

private:
	/**
	* \brief 物件类型
	*/
	const SceneEntryType sceneentrytype;
	/**
	* \brief 物件状态
	*
	*/
	SceneEntryState sceneentrystate;
	/**
	* \brief 物件是否在场景上
	*/
	bool inserted;

	/**
	* \brief 设置物件坐标
	* \param screenWH 场景的宽高
	* \param newPos 物件的新坐标
	* \return 坐标超出场景宽高返回false,否则返回true
	*/
	bool setPos(const zPos &screenWH, const zPos &newPos)
	{
		if (screenWH.x>newPos.x && screenWH.y>newPos.y)
		{
			pos = newPos;
			zPos2zPosI(screenWH, newPos, posi);
			return true;
		}
		else
			return false;
	}

private:
	/**
	* \brief 物件状态，与魔法等相关的
	* 这种状态是外观可以表现的，带上某种状态客户端就可以以一种方式来表现
	* 详细的状态参见Command.h中
	*/
	BYTE byState[(Cmd::MAX_STATE + 7) / 8];
protected:
	SceneEntryStateList stateList;
public:
	/**
	* \brief 填充物件状态
	* \param state 填充位置
	* \return 状态个数
	*/
	inline BYTE full_UState(WORD *state)
	{
		BYTE ret = stateList.size();
		SceneEntryStateList::iterator iter = stateList.begin();
		for (int i = 0; i < ret; i++)
		{
			state[i] = *iter;
			iter++;
		}
		return ret;
	}
	/**
	* \brief 填充物件所有状态
	* \param state 填充位置
	*/
	inline void full_all_UState(void *state, DWORD maxSize)
	{
		bcopy(byState, state, sizeof(byState), maxSize);
	}

	/**
	* \brief 得到物件坐标
	* \return 物件坐标
	*/
	inline const zPos &getPos() const
	{
		return pos;
	}

	/**
	* \brief 得到物件刚才的坐标
	* \return 物件坐标
	*/
	inline const zPos &getOldPos1() const
	{
		return lastPos1;
	}

	/**
	* \brief 得到物件刚才的坐标
	* \return 物件坐标
	*/
	inline const zPos &getOldPos2() const
	{
		return lastPos2;
	}

	/**
	* \brief 得到物件屏坐标
	* \return 物件屏坐标
	*/
	inline const zPosI &getPosI() const
	{
		return posi;
	}
	/**
	* \brief 测试物件是否在场景中
	* \return 物件在场景中返回true,否则返回false
	*/
	inline bool hasInScene() const
	{
		return inserted;
	}

	/**
	* \brief 得到物件类型
	* \return 物件类型
	*/
	inline const SceneEntryType & getType() const
	{
		return sceneentrytype;
	}

	/**
	* \brief 获取物件状态
	* \return 状态
	*/
	inline const SceneEntryState & getState() const
	{
		return sceneentrystate;
	}

	/**
	* \brief 设置物件状态
	* \param state 需要设置的状态
	*/
	void setState(const SceneEntryState & state)
	{
		sceneentrystate = state;
	}

	/**
	* \brief 获取方向
	* \return 方向
	*/
	inline const BYTE getDir() const
	{
		return dir % 8;
	}

	/**
	* \brief 设置方向
	* \param dir 方向
	*/
	void setDir(const BYTE dir)
	{
		this->dir = dir % 8;
	}

	/**
	* \brief 检查某种状态是否设置
	* \param state 待检查的状态
	* \return 这种状态是否已经设置
	*/
	inline bool issetUState(const int state) const
	{
		return Cmd::isset_state(byState, state);
	}

	/**
	* \brief 设置某种状态
	* \param state 待设置的状态
	* \return 如果已经设置该状态返回false,否则返回true
	*/
	inline bool setUState(const int state)
	{
		if (!issetUState(state))
		{
			stateList.push_back(state);
			Cmd::set_state(byState, state);
			return true;
		}
		return false;
	}

	/**
	* \brief 清除某种状态
	* \param state 待清除的状态
	* \return 如果已经设置该状态返回true,否则返回false
	*/
	inline bool clearUState(const int state)
	{
		Cmd::clear_state(byState, state);
		SceneEntryStateList::iterator iter = stateList.begin();
		for (; iter != stateList.end(); ++iter)
		{
			if (*iter == state)
			{
				stateList.erase(iter);
				return true;
			}
		}
		return false;
	}
};

/**
* \brief 场景管理器定义
*/
enum enumSceneRunningState {
	SCENE_RUNNINGSTATE_NORMAL,//正常运行
	SCENE_RUNNINGSTATE_UNLOAD,//正在卸载
	SCENE_RUNNINGSTATE_REMOVE,//正在卸载
};
/**
* \brief 场景基本信息定义
*/
struct zScene :public zEntry
{
private:
	DWORD running_state;
public:
	zScene() :running_state(SCENE_RUNNINGSTATE_NORMAL) {}
	DWORD getRunningState() const
	{
		return running_state;
	}
	DWORD setRunningState(DWORD set)
	{
		running_state = set;
		return running_state;
	}
};

/**
* \brief 场景管理器
*
* 以名字和临时ID索引,没有ID索引，因为场景可能重复
*/
class zSceneManager :public zEntryMgr<zEntryID, zEntryTempID, zEntryName >
{
protected:
	/**
	* \brief 访问管理器的互斥锁
	*/
	zRWLock rwlock;

	zScene * getSceneByName(const char * name)
	{
		rwlock.rdlock();
		zScene *ret = (zScene *)getEntryByName(name);
		rwlock.unlock();
		return ret;
	}



	zScene * getSceneByID(DWORD id)
	{
		rwlock.rdlock();
		zScene *ret = (zScene *)getEntryByID(id);
		rwlock.unlock();
		return ret;
	}

	zScene * getSceneByTempID(DWORD tempid)
	{
		rwlock.rdlock();
		zScene *ret = (zScene *)getEntryByTempID(tempid);
		rwlock.unlock();
		return ret;
	}

	template <class YourSceneEntry>
	bool execEveryScene(execEntry<YourSceneEntry> &exec)
	{
		rwlock.rdlock();
		bool ret = execEveryEntry<>(exec);
		rwlock.unlock();
		return ret;
	}

	/**
	* \brief 移出符合条件的角色
	* \param pred 条件断言
	*/
	template <class YourSceneEntry>
	void removeScene_if(removeEntry_Pred<YourSceneEntry> &pred)
	{
		rwlock.wrlock();
		removeEntry_if<>(pred);
		rwlock.unlock();
	}

public:
	/**
	* \brief 构造函数
	*/
	zSceneManager()
	{
	}

	/**
	* \brief 析构函数
	*/
	virtual ~zSceneManager()
	{
		clear();
	}

};



/**
* \brief 角色管理器定义
*/
/**
* \brief 角色定义类,有待扩充
*/
struct zUser :public zSceneEntry
{
	zUser() :zSceneEntry(SceneEntry_Player)
	{
	}
	void lock()
	{
		//Zebra::logger->debug("lockuser");
		mlock.lock();
	}

	void unlock()
	{
		//Zebra::logger->debug("unlockuser");
		mlock.unlock();
	}

private:
	zMutex mlock;
};


/**
* \brief 角色管理器
* uid,sessionid,name
* 实现了ID、临时ID和名字的索引,所以这些值不能重复
*/
class zUserManager :public zEntryMgr< zEntryID, zEntryTempID, zEntryName >
{
protected:
	/**
	* \brief 管理器访问互斥锁
	*/
	zRWLock rwlock;

public:
	/**
	* \brief 构造函数
	*/
	zUserManager()
	{
	}

	/**
	* \brief 析构函数
	*/
	virtual ~zUserManager()
	{
		clear();
	}

	/**
	* \brief 根据角色名字得到角色
	* \param name 角色名字
	* \return 角色指针,如果返回NULL表示没找到角色
	*/
	zUser * getUserByName(const char * name)
	{
		rwlock.rdlock();
		zUser *ret = (zUser *)getEntryByName(name);
		rwlock.unlock();
		return ret;
	}

	/**
	* \brief 根据角色ID得到角色
	* \param id 角色ID
	* \return 角色指针,如果返回NULL表示没找到角色
	*/
	zUser * getUserByID(QWORD id)
	{
		rwlock.rdlock();
		zUser *ret = (zUser *)getEntryByID(id);
		rwlock.unlock();
		return ret;
	}

	/**
	* \brief 根据角色临时ID得到角色
	* \param tempid 角色临时ID
	* \return 角色指针,如果返回NULL表示没找到角色
	*/
	zUser * getUserBySessID(QWORD sessid)
	{
		rwlock.rdlock();
		zUser *ret = (zUser *)getEntryByTempID(sessid);
		rwlock.unlock();
		return ret;
	}

	/**
	* \brief 添加角色
	* \param user 角色
	* \return 添加是否成功
	*/
	bool addUser(zSceneEntry *user)
	{
		rwlock.wrlock();
		bool ret = addEntry((zEntry *)user);
		rwlock.unlock();
		return ret;
	}

	/**
	* \brief 移出角色
	* \param user 角色
	*/
	void removeUser(zSceneEntry *user)
	{
		rwlock.wrlock();
		removeEntry((zEntry *)user);
		rwlock.unlock();
	}

	/**
	* \brief 移出符合条件的角色
	* \param pred 条件断言
	*/
	template <class YourUserEntry>
	void removeUser_if(removeEntry_Pred<YourUserEntry> &pred)
	{
		rwlock.wrlock();
		removeEntry_if<>(pred);
		rwlock.unlock();
	}

	/**
	* \brief 对每个用户执行
	* \param exec 执行接口
	*/
	template <class YourUserEntry>
	bool execEveryUser(execEntry<YourUserEntry> &exec)
	{
		rwlock.rdlock();
		bool ret = execEveryEntry<>(exec);
		rwlock.unlock();
		return ret;
	}
};

class zLock
{
public:

	/**
	* \brief 构造函数，构造一个临界区对象
	*
	*/
	zLock()
	{
		//InitializeCriticalSection(&m_critical);
	}

	/**
	* \brief 析构函数，销毁一个临界区对象
	*
	*/
	~zLock()
	{
		//DeleteCriticalSection(&m_critical);
	}

	/**
	* \brief 加锁一个临界区
	*
	*/
	inline void lock()
	{
		//EnterCriticalSection(&m_critical);
	}

	/**
	* \brief 解锁一个临界区
	*
	*/
	inline void unlock()
	{
		//LeaveCriticalSection(&m_critical);
	}

private:

	//CRITICAL_SECTION    m_critical; // 系统临界区
};


/**
* \brief Zebra项目的日志类。
*
* 目前实现了两种写日志方式，即控制台、本地文件。
*
* 默认日志级别是#DEBUG
*
* 此类为线程安全类。
*/
class zLogger
{
public:
	/**
	* \brief zLevel声明了几个日志等级
	*
	* 除了用log4cxx提供的标准日志等级作为日志等级外，还自定义了游戏日志等级.
	*
	* 程序日志等级关系为 #OFF> #FATAL> #ERROR> #WARN> #INFO> #DEBUG> #ALL
	*
	*/

	/**
	* \brief Zebra项目所支持日志等级数字定义
	*/
	typedef enum
	{
		/**
		* \brief 当zLogger等级设置为OFF，否则不会输出任何日志
		*/
		LEVEL_OFF = INT_MAX,

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
		LEVEL_WARN = 30000,

		/**
		* \brief 当zLogger等级设置为INFO，只输出大于等于此等级的日志
		*
		* 信息，提供一般信息记录，多用于一些程序状态的记录。
		*/
		LEVEL_INFO = 20000,

		/**
		* \brief 当zLogger等级设置为DEBUG，输出所有等级的日志
		*/
		LEVEL_DEBUG = 10000,

		/**
		* \brief 当zLogger等级设置为ALL，输出所有等级的日志
		*/
		LEVEL_ALL = INT_MIN
	}zLevel;

	zLogger(char *name = "Zebra");
	~zLogger();

	const std::string& getName();
	void removeConsoleLog();
	void addLocalFileLog(const std::string &file);

	void setLevel(const zLevel level);
	void setLevel(const std::string &level);

	void logtext(const zLevel level, const char * text);
	void logva(const zLevel level, const char * pattern, va_list vp);
	void log(const zLevel level, const char * pattern, ...);

	void debug(const char * pattern, ...);
	void debug16(const char* info, const BYTE* pData, int Datasize);
	void error(const char * pattern, ...);
	void info(const char * pattern, ...);
	void fatal(const char * pattern, ...);
	void warn(const char * pattern, ...);

private:
	zLock msgMut;

	zLevel      m_level;
	FILE        *fp_console;
	FILE        *fp_file;
	int         m_day;
	std::string m_name;
	std::string m_file;
};


/**
* \brief 属性关联类容器，所有属性关键字和值都使用字符串代表，关键字不区分大小写
*
*/
class zProperties
{

public:

	/**
	* \brief 获取一个属性值
	*
	* \param key 关键字
	* \return 返回与关键字对应的属性值
	*/
	const std::string &getProperty(const std::string &key)
	{
		return properties[key];
	}

	/**
	* \brief 设置一个属性
	*
	* \param key 关键字
	* \param value 关键字对应的属性
	*/
	void setProperty(const std::string &key, const std::string &value)
	{
		properties[key] = value;
	}

	/**
	* \brief 重载操作符，返回与关键字对应的属性值
	*
	* \param key 关键字
	* \return 属性值
	*/
	std::string & operator[] (const std::string &key)
	{
		//fprintf(stderr,"properties operator[%s]\n",key.c_str());
		return properties[key];
	}

	/**
	* \brief 输出存储的所有属性值
	*
	*/
	void dump(std::ostream &out)
	{
		property_hashtype::const_iterator it;
		for (it = properties.begin(); it != properties.end(); it++)
			out << it->first << " = " << it->second << std::endl;
	}

	DWORD parseCmdLine(const std::string &cmdLine);
	DWORD parseCmdLine(const char *cmdLine);

protected:

	/**
	* \brief hash函数
	*
	*/
	/*struct key_hash : public std::unary_function<const std::string,size_t>
	{
	size_t operator()(const std::string &x) const
	{
	std::string s = x;
	hash<string> H;
	// _Hash<string> H;
	//转化字符串为小写
	to_lower(s);
	//tolower(s);
	//return H(s);
	return 0;
	}
	};*/
	/**
	* \brief 判断两个字符串是否相等
	*
	*/
	/*struct key_equal : public std::binary_function<const std::string,const std::string,bool>
	{
	bool operator()(const std::string &s1,const std::string &s2) const
	{
	// return strcasecmp(s1.c_str(),s2.c_str()) == 0;
	return (s1==s2);
	}
	};*/

	/**
	* \brief 字符串的hash_map
	*
	*/
	//typedef hash_map<std::string,std::string,key_hash,key_equal> property_hashtype;

	//typedef hash_map<std::string,std::string,key_hash,key_equal> property_hashtype;
	typedef UNORDERED_MAP<std::string, std::string> property_hashtype;

	property_hashtype properties;      /**< 保存属性的键值对 */

};


/**
* \brief 配置文件解析器声明
*/
/**
* \brief zXMLParser定义
*
* 主要提供了节点的浏览,和其属性的得到.
*/
class zXMLParser
{
public:
	zXMLParser();
	~zXMLParser();

	bool initFile(const std::string &xmlFile);
	bool initFile(const char *xmlFile);
	bool initStr(const std::string &xmlStr);
	bool initStr(const char *xmlStr);
	bool init();
	void final();
	std::string & dump(std::string & s, bool format = false);
	std::string & dump(xmlNodePtr dumpNode, std::string & s, bool head = true);
	xmlNodePtr getRootNode(const char *rootName);
	xmlNodePtr getChildNode(const xmlNodePtr parent, const char *childName);
	xmlNodePtr getNextNode(const xmlNodePtr node, const char *nextName);
	DWORD getChildNodeNum(const xmlNodePtr parent, const char *childName);

	xmlNodePtr newRootNode(const char *rootName);
	xmlNodePtr newChildNode(const xmlNodePtr parent, const char *childName, const char *content);
	bool newNodeProp(const xmlNodePtr node, const char *propName, const char *prop);

	bool getNodePropNum(const xmlNodePtr node, const char *propName, void *prop, int propSize);
	bool getNodePropStr(const xmlNodePtr node, const char *propName, void *prop, int propSize);
	bool getNodePropStr(const xmlNodePtr node, const char *propName, std::string &prop);
	bool getNodeContentNum(const xmlNodePtr node, void *content, int contentSize);
	bool getNodeContentStr(const xmlNodePtr node, void *content, int contentSize);
	bool getNodeContentStr(const xmlNodePtr node, std::string &content);
	bool getNodeContentStr(const xmlNodePtr node, std::string &content, bool head);
private:
	BYTE *charConv(BYTE *in, const char *fromEncoding, const char *toEncoding);
	xmlDocPtr doc;
};

using namespace boost::gregorian;
using namespace boost::posix_time;

/*

时钟的滴答器，缓存秒，daystart,weekstart,monthstart等
精确到秒，需要秒内的定时器调用update来驱动更新

*/

class zTimeTick
{
public:
	zTimeTick();
	~zTimeTick();

	void update();

	inline int32 now() const
	{
		return nowtime;
	}

	inline int64 getMilliTime()
	{
		return MilliTime();
	}

	inline int32 getDayStart() const
	{
		return daystart;
	}

	inline int32 getDayYmd() const
	{
		return dayymd;
	}

	inline int32 getWeekStart() const
	{
		return weekstart;
	}

	inline int32 getWeekYmd() const
	{
		return weekymd;
	}

private:

	//  获得系统时间戳 
	inline uint32 GetCurrentSeconds()
	{
		time_duration time_from_epoch = second_clock::universal_time() - epochStd;
		return time_from_epoch.total_seconds();
	}

	// 获得系统时间戳(微秒)
	inline uint64 GetCurrentMircoseconds()
	{
		time_duration time_from_epoch = microsec_clock::universal_time() - epochStd;
		return time_from_epoch.total_microseconds();
	}

	// 获得时间戳（秒）
	inline int32 NowTime()
	{
		time_duration time_from_epoch = second_clock::universal_time() - epochStd;
		return static_cast<int32>(time_from_epoch.total_seconds());
	}

	// 获得时间戳（毫秒）
	inline int64 MilliTime()
	{
		time_duration time_from_epoch = microsec_clock::universal_time() - epochStd;
		return static_cast<int64>(time_from_epoch.total_milliseconds());
	}

	// 获得今天0点时间
	inline int32 TodayStart()
	{
		ptime nowt = microsec_clock::universal_time();
		time_duration time_from_epoch = (nowt - epochStd);
		return time_from_epoch.total_seconds() - (nowt.time_of_day().total_seconds() + beijingDuration.total_seconds()) % 86400;
	}

	// 获得时间戳（微秒）
	inline int64 MicroTime()
	{
		time_duration time_from_epoch = microsec_clock::universal_time() - epochStd;
		return static_cast<int64>(time_from_epoch.total_microseconds());
	}

	// 检查其他以小时为单元的时间缓存 
	void checkHourUnit();

private:

	/* 1970年1月1日 01:00:00（标准时间计算） */
	ptime epochStd;

	/* 1970年1月1日 08:00:00（北京时间计算），用于计算天与天之间则需要用此值来求差 */
	time_duration beijingDuration;

private:

	int32 nowtime;
	int32 daystart;
	int32 dayymd;
	int32 weekstart;
	int32 weekymd;

};

/*
*
*	Detail: 采用策略设计模式（因为每一种的定时器都不一样）
*
*
*  Created by hzd 2015-6-4
*
*/


/*
*
*	Detail: 异步定时器
*
* Copyright (c) Created by hzd 2015-6-4.All rights reserved
*
*/

typedef boost::function<void(const zTaskTimer* timer)> zTaskTimerHandler;

class zTaskTimer : public io_service
{
public:

	// Detail: 回调时间(毫秒)，次数，回调函数
	zTaskTimer(int32 interval, int32 maxTimes, zTaskTimerHandler pHander);

	// 
	~zTaskTimer();

	// 开始启动
	void start();

	// 停止（最后一次回调）
	void cancel();

	// 时长判断 
	bool is1Sec() const;
	bool is2Sec() const;
	bool is3Sec() const;
	bool is5Sec() const;
	bool is1Min() const;
	bool is5Min() const;
	bool is1Hour() const;

	// 跨时天周月年判断
	bool isNewHour() const;
	bool isNewDay() const;
	bool isNewWeek() const; //周日为一周的开始 
	bool isNewMonth() const;
	bool isNewYear() const;

private:

	void doStart();
	void doHandler();

	void diyTimeCache();
	void checkCancel();

private:

	int32 m_Interval;	// 每次间隔时间(毫秒) 
	int32 m_MaxTimes;   // 最大调用次数(0无限次，1次) 
	int32 m_HadTimes;   // 已经调用次数 
	int64 m_execTime;	// 已经执行的时间 

	zTaskTimerHandler	m_fHandler;  // 回调函数 
	deadline_timer		m_ctimer;

	boost::thread  m_cServiceThread;		// 定时器线程  

	bool b1Sec;
	bool b2Sec;
	bool b3Sec;
	bool b5Sec;
	bool b1Min;
	bool b5Min;
	bool b1Hour;

	bool bNewHour;
	bool bNewDay;
	bool bNewWeek;
	bool bNewMonth;
	bool bNewYear;

};


/**
* \brief 定义了服务器的框架基类
*
* 所有服务器程序实体需要继承这个类，并且不管是其有多少个子类，整个运行环境只有一个类的实例<br>
* 只要派生类使用Singleton设计模式实现就可以了
*
*/
class zService : private zNoncopyable
{
public:
	/**
	* \brief 虚析构函数
	*
	*/
	virtual ~zService() { inst = NULL; };

	/**
	* \brief 重新读取配置文件，为HUP信号的处理函数
	*
	* 缺省什么事情都不干，只是简单输出一个调试信息，重载这个函数干想干的事情
	*
	*/
	virtual void reloadConfig()
	{
	}

	/**
	* \brief 判断主循环是否结束
	*
	* 如果返回true，将结束主回调
	*
	* \return 主循环是否结束
	*/
	bool isTerminate() const
	{
		return terminate;
	}

	/**
	* \brief 结束主循环，也就是结束主回调函数
	*
	*/
	void Terminate()
	{
		terminate = true;
	}

	void main();

	/**
	* \brief 返回服务的实例指针
	*
	* \return 服务的实例指针
	*/
	static zService *getInst()
	{
		return inst;
	}


	virtual bool init() = 0;

	/**
	* \brief 确认服务器初始化成功，即将进入主回调函数
	*
	* \return 确认是否成功
	*/
	virtual bool validate()
	{
		return true;
	}

	/**
	* \brief 服务程序的主回调函数，主要用于监听服务端口，如果返回false将结束程序，返回true继续执行服务
	*
	* \return 回调是否成功
	*/
	virtual bool run() = 0;

	/**
	* \brief 结束服务器程序，回收资源，纯虚函数，子类需要实现这个函数
	*
	*/
	virtual void finaly() = 0;

public:

	static zService *inst;	/**< 类的唯一实例指针，包括派生类，初始化为空指针 */

	zProperties env;        /**< 存储当前运行系统的环境变量 */
	std::string name;       /**< 服务名称 */
	bool terminate;         /**< 服务结束标记 */

protected:

	/**
	* \brief 构造函数
	*/
	zService(const std::string &_name) : name(_name)
	{
		inst = this;
		terminate = false;
	}
};

// 游戏区
struct GameZone_t
{
	int32 gameID;
	int32 zoneID;
};

// 通用区
struct GeneralZone_t
{
	int8 type;
	int8 actID;
	int32 flatID;
	GameZone_t zone;
};

/*
 * 路由头信息，来自zone,去往zone
 * 模拟以太网包消息,包结构为[fromZone,toZone,prootol][GOTOdata/SENDTOdata]
 * GOTO为进入跨服协议，gotoServerZone所在的区
 * SENDTO为转发跨服协议,sendToServerZone所在的区
 */
struct GeneralRoute_t
{
	GeneralZone_t fromZone;
	GeneralZone_t toZone;
	BYTE formType;	//来自于:0源服务器,1玩家
	QWORD formID;	//来源ID
	BYTE toType;	//接收类型:0服务器,1玩家
	QWORD toID;		//接收ID
	BYTE routeCount;//转发计数
	BYTE dirType;	//指令类型0向前,1回退
	BYTE errType;	//0无,1失败返回,2解包发送
	bool needFailBack()
	{
		return errType & 0x01;
	}
	bool needUppack()
	{
		return errType & 0x02;
	}
};


/*
 * 网络服务器框架基类
 *
 */
class zNetSerivce : public zService
{
public:

	virtual ~zNetSerivce() { };

	// 将消息发到某区
	void sendToServerZone(GeneralRoute_t route, const NetMsgSS* cmd,int32 len); // S协议
	void sendToServerZoneUser(GeneralRoute_t route,int64 toUserID,const NetMsgSS* cmd, int32 len); //c协议

	// 将自己转移到某区登录(本区下线,某区上线)
	void gotoServerZone(GeneralRoute_t route);

protected:

	zNetSerivce(const std::string &_name) : zService(_name)
	{

	}

	void sendToServerZone(GeneralRoute_t route, std::pair<int32, int64> toPair, const NetMsgSS* cmd, int32 len);

private:

	// 平台数据
	int32 flatID;	//平台ID
	int32 flatZone;	//区服ID

	// 区数据 平台id=>区ID(区id=>合服ID)
	std::map<int32, int32> flatZonelist;
	std::map<int32, int32> gameZoneList;
};

/*
*	加密、解类类
*/
class zEncrypt
{
	// 协议加解密使用 
public:
	// 获得随机密钥(默认32位)
	static void getRandKey(char* outKey, int32 length = 32);

	// 异或加解密
	static int32 xorCode(uint32 nRandNum, const char* inKey, char *pSrc, uint32 nSrcLen);

	// 在[x,y]取随机数据
	static int32 randBetween(int x,int y);

};

/*

关于C++版本MD5，网上有很多C++版本的MD5，但不同的版本算法稍有不同
而C#,Java,Php它们是通用一套，所以该版本实现也与它们一样

使用方法
unsigned char a[] = "a";
char md5str[50] = { 0 };
EncryptMD5str(md5str, a, 1);
printf("MD5 String is %s\n", md5str);

*/

#ifdef __cplusplus
extern "C" {
#endif
	/*————————————————————————.
	| md5 encrypt function
	.————————————————————————*/
	void EncryptMD5(unsigned char *output, unsigned char *input);
	void EncryptMD5str(char *output, unsigned char *input, int len);

#ifdef __cplusplus
}
#endif

class zUUID
{

	//twitter snowflake 算法
	//64     63--------------22-----------12------0
	//符号位 |    41位时间   | 10位机器吗| 12位自增码|
public:
	zUUID();
	~zUUID();
	uint64_t get_time();

	void set_epoch(uint64_t epoch);
	void set_machine(int32_t machine);

	int64_t generate();
private:
	uint64_t epoch_;
	uint64_t time_;
	uint64_t machine_;
	int32_t sequence_;

};


/*
 * 连接管理器 
 */ 

CreateEntryC(serivceid);
CreateEntry(serivceid);
CreateEntryTempID(serivceid);
CreateEntryID(serivceid);
CreateEntryNone(serivceid);
CreateEntryName(serivceid);
CreateEntryManager(serivceid);

CreateEntryC(serverid);
CreateEntry(serverid);
CreateEntryTempID(serverid);
CreateEntryID(serverid);
CreateEntryNone(serverid);
CreateEntryName(serverid);
CreateEntryManager(serverid);

CreateEntryC(sessid);
CreateEntry(sessid);
CreateEntryTempID(sessid);
CreateEntryID(sessid);
CreateEntryNone(sessid);
CreateEntryName(sessid);
CreateEntryManager(sessid);

CreateEntryC(mapid);
CreateEntry(mapid);
CreateEntryTempID(mapid);
CreateEntryID(mapid);
CreateEntryNone(mapid);
CreateEntryName(mapid);
CreateEntryManager(mapid);

CreateEntryC(uid);
CreateEntry(uid);
CreateEntryTempID(uid);
CreateEntryID(uid);
CreateEntryNone(uid);
CreateEntryName(uid);
CreateEntryManager(uid);


// 用来取代serversession与clientsession
#define EncryptDef "1234567890ABCDEFGHIJKLMNOPQSRT\0"

// id = socketid,tempid = serivceid

class zSession : public zEntryserivceid
{
public:
	zSession(NetSocket* _socket):socket(_socket)
	{
		initEncrypt();
	}

	~zSession()
	{
		
	}

	void sendMsg(const void* msg, int32 size)
	{
		if (socket)
		{
			socket->ParkMsg((const NetMsgSS*)msg, size);
			socket->SendMsg();
		}
	}

	void exist()
	{
		if (socket)
		{
			socket->OnEventColse();
		}
	}

	enum ServerType
	{
		SERVER_TYPE_NULL,
		SERVER_TYPE_SERVER,
		SERVER_TYPE_CLIENT
	};

	enum SessionType
	{
		FOR_NULL,
		FOR_FEP,
		FOR_LOGIN,
		FOR_WORLD,
		FOR_SCENE,
		FOR_DP,
		FOR_PLAYER,
	};

	void setServerType(ServerType _serverType)
	{
		serverType = _serverType;
	}

	void setSessionType(SessionType _sessionType)
	{
		sessionType = _sessionType;
	}

	void setServerID(int32 _serverID)
	{
		serverid = _serverID;
	}

	void initEncrypt()
	{
		memcpy(encrypt, EncryptDef, MAX_NAMESIZE);
	}

public:

	NetSocket* socket;
	ServerType serverType;// 1 服务器,2客户端 
	SessionType sessionType;

	// 其他功能用途定义字段 
	int32 serverid;
	int32 status;
	int32 lastasktime;		// 上次访问时间 
	int32 lastaskprotocol;	// 上次访问协议
	char encrypt[MAX_NAMESIZE + 1];

	
};

/*
*
*  Detail: 连接外部服务器连接管理
*
*/
class zSessionMgr : protected zEntryMgrserivceid<zEntryIDserivceid>
{
protected:
	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);

public:
	typedef PNetServerEnterHandler NetMsgEnter;
	typedef PNetServerOnMsgHandler NetMsgOn;
	typedef PNetServerExistHandler NetMsgExit;
	zSessionMgr();
	~zSessionMgr();

	bool bind(int32 id, const char* ip, int16 port,int16 maxConnects,NetMsgEnter fEnter, NetMsgOn fMsg, NetMsgExit fExit);
	zSession* connect(int32 id, const char* ip, int16 port, NetMsgEnter fEnter, NetMsgOn fMsg, NetMsgExit fExit);
	zSession* CreateObj(NetSocket* socket)
	{
		return sessionobjpool.CreateObj(socket);
	}

	void DestoryObj(zSession* obj)
	{
		sessionobjpool.DestroyObj(obj);
	}

	bool add(zSession* conn)
	{
		return zEntryMgrserivceid::addEntry(conn);
	}

	void remove(zSession* conn)
	{
		zEntryMgrserivceid::removeEntry(conn);
	}

	zSession* get(QWORD id)
	{
		return (zSession*)zEntryMgrserivceid::getEntryByID(id);
	}

	// 查找某个服务器Session 
	zSession* getByServerID(zSession::SessionType fun, int32 serverid);

	zSession* getWs(int32 serverid = 3001);
	zSession* getLs(int32 serverid = 2001);
	zSession* getFep(int32 serverid = 1001);
	zSession* getSs(int32 serverid = 4001);
	zSession* getDp(int32 serverid = 5001);
	bool sendMsg(int64 sessid, const NetMsgSS* pMsg, int32 nSize);
	bool sendToWs(const NetMsgSS* pMsg,int32 nSize);
	bool sendToDp(const NetMsgSS* pMsg, int32 nSize);
	bool sendToLs(const NetMsgSS* pMsg, int32 nSize);
	bool sendToSs(int32 serverid,const NetMsgSS* pMsg, int32 nSize);
	bool sendToFep(int32 serverid, const NetMsgSS* pMsg, int32 nSize);

	template <class YourSessionEntry>
	bool execEveryConn(execEntry<YourSessionEntry> &exec)
	{
		return execEveryEntry<>(exec);;
	}

	void updateIO(const zTaskTimer* timer);

	void updateServerIO(const zTaskTimer* timer);

	void updateClientIO(const zTaskTimer* timer);

	int32 CountConnected()
	{
		return zEntryMgrserivceid::size();
	}

private:

	zObjPool<NetServer>  serverobjpool;
	zObjPool<NetClient>  clientobjpool;
	zObjPool<zSession>	sessionobjpool;

	// 等待加入到used列表中 
	std::vector<NetServer*> serverListAdd;
	std::vector<NetClient*> clientListAdd;

	// 正在使用中的列表
	std::vector<NetServer*> serverListUsed;
	std::vector<NetClient*> clientListUsed;

};

enum EServerStatus
{
	E_SERVER_STATUS_INIT = 0,
	E_SERVER_STATUS_CONNETED,
	E_SERVER_STATUS_LOGINED,
	E_SERVER_STATUS_OK,
};

typedef boost::function<void(zSession*, const NetMsgSS*, int32 nSize)> HandleFunc;

// 协议与对应的调用函数 
struct MsgFunc
{
	MsgFunc(int32 _packSize, const HandleFunc& _handlerFun):packSize(_packSize),handlerFun(_handlerFun)
	{
	}
	MsgFunc(const MsgFunc& info)
	{
		operator=(info);
	}
	const MsgFunc& operator=(const MsgFunc& info)
	{
		memcpy(this, &info, sizeof(MsgFunc));
		return *this;
	}
	int32 packSize;		// 数据大小 
	HandleFunc handlerFun;	// 处理函数 
};

typedef	map< uint32, MsgFunc > MsgFuncMap;

class zMsgHandler
{
public:
	virtual void OnNetMsgEnter(NetSocket& rSocket) = 0;
	virtual void OnNetMsg(NetSocket& rSocket, NetMsgSS* pMsg, int32 nSize) = 0;
	virtual void OnNetMsgExit(NetSocket& rSocket) = 0;

protected:
	zMsgHandler();
	~zMsgHandler();
	const MsgFunc* GetMsgHandler(uint32 protocol);
	bool RegisterMessage(uint32 msgIdx, int32 packSize, const HandleFunc& handlerFun);

private:

	MsgFuncMap msgFuncs;

};


/*
 * 服务器注册信息
 * id=>serverid,tempid=>sessid
 */
class zServerReg : public zEntrysessid
{
public:
	zServerReg()
	{

	}
public:
	// 其他信息，如场景等 
	// 
};


class zServerRegMgr : protected zEntryMgrsessid<zEntryIDsessid, zEntryTempIDsessid>
{
public:
	zServerRegMgr();
	~zServerRegMgr();
	bool getUniqeID(QWORD& tempid);
	void putUniqeID(const QWORD& tempid);
	zServerReg* CreateObj();
	void DestroyObj(zServerReg* obj);

	bool add(zServerReg* obj);
	void remove(zServerReg* obj);
	zServerReg* get(int64 id);
	zServerReg* getBySessID(int64 id);

	template <class YourSessionEntry>
	bool execEveryServer(execEntry<YourSessionEntry> &exec)
	{
		return execEveryEntry<>(exec);;
	}

private:

	zObjPool<zServerReg> objpool;

};


class zSerivceCfgMgr
{
public:

	struct Serivce
	{
		Serivce()
		{
			id = remoteid = port = maxConnects = broadcast = 0;
		}

		int32 id;
		std::string name;
		std::string fun;
		int32 remoteid;
		std::string ip;
		int16 port;
		int16 maxConnects;
		std::string user;
		std::string passwd;
		std::string value;
		int32 broadcast;

	};

	struct Server
	{
		Server()
		{
			id = recvsrvlist = broadcastlist = 0;
		}

		zSession::SessionType getSessType() const
		{
			if (stricmp(name.c_str(), "gatewayserver") == 0)
			{
				return zSession::FOR_FEP;
			}
			else if (stricmp(name.c_str(), "loginserver") == 0)
			{
				return zSession::FOR_LOGIN;
			}
			else if (stricmp(name.c_str(), "worldserver") == 0)
			{
				return zSession::FOR_WORLD;
			}
			else if (stricmp(name.c_str(), "sceneserver") == 0)
			{
				return zSession::FOR_SCENE;
			}
			else if (stricmp(name.c_str(), "dbserver") == 0)
			{
				return zSession::FOR_DP;
			}
			else
			{
				return zSession::FOR_NULL;
			}
		}

		int32 id;
		string name;
		int32 recvsrvlist;
		int32 broadcastlist;
		std::map<int32, Serivce> serivces;
	};

	zSerivceCfgMgr();
	~zSerivceCfgMgr();

	bool loadConfig(const std::string& filename);
	const std::map<int32, Server>& getServer() const;
	const Server* getServer(int32 serverid) const;
	const Serivce* getSerivce(int32 serverid, int32 serivceid) const;

private:

	std::map<int32, Server > allServers;

};


/*
 * RSA加密解密	
 *
 */
class zRSA
{
public:
	zRSA(const char* _pubfilename,const char* _prifilename,const char* _password);
	~zRSA();
	bool generateKey();
	std::string bio_read_privateKey(std::string data);
	std::string bio_read_publicKey(std::string data);
	void encryptFile(std::string inputfile, std::string outputfile);
	void decryptFile(std::string inputfile, std::string outputfile);
	int testEncodeUncode();

	const char* getPubfilename() const;
	const char* getPrifilename() const;
	const char* getPassword() const;

private:

	char pubfilename[MAX_NAMESIZE + 1];
	char prifilename[MAX_NAMESIZE + 1];
	char password[MAX_NAMESIZE + 1];

};

/*
 * 常用工具类	
 */
class zUtility
{
public:
	inline static int RangedRand(int nMin, int nMax)
	{
		return static_cast<int>(nMin + rand() * 1.f / (RAND_MAX + 1) * (nMax - nMin));
	}

	inline static int GBKToUTF8(const char * lpGBKStr, char * lpUTF8Str, int nUTF8StrLen)
	{
		wchar_t * lpUnicodeStr = NULL;
		int nRetLen = 0;

		if (!lpGBKStr)  // 如果GBK字符串为NULL则出错退出  
			return 0;

		nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char *)lpGBKStr, -1, NULL, NULL);  // 获取转换到Unicode编码后所需要的字符空间长度 
		lpUnicodeStr = new WCHAR[nRetLen + 1];  // 为Unicode字符串空间 
		nRetLen = ::MultiByteToWideChar(CP_ACP, 0, (char *)lpGBKStr, -1, lpUnicodeStr, nRetLen);  // 转换到Unicode编码 
		if (!nRetLen)  // 转换失败则出错退出
			return 0;

		nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, NULL, 0, NULL, NULL);  // 获取转换到UTF8编码后所需要的字符空间长度 

		if (!lpUTF8Str)  // 输出缓冲区为空则返回转换后需要的空间大小 
		{
			if (lpUnicodeStr)
				delete[]lpUnicodeStr;
			return nRetLen;
		}

		if (nUTF8StrLen < nRetLen)  // 如果输出缓冲区长度不够则退出 
		{
			if (lpUnicodeStr)
				delete[]lpUnicodeStr;
			return 0;
		}

		nRetLen = ::WideCharToMultiByte(CP_UTF8, 0, lpUnicodeStr, -1, (char *)lpUTF8Str, nUTF8StrLen, NULL, NULL);  // 转换到UTF8编码 

		if (lpUnicodeStr)
			delete[]lpUnicodeStr;

		return nRetLen;
	}

	inline static char* Utf8ToGBK(const char* strUtf8)
	{
		int len = MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, NULL, 0);
		unsigned short * wszGBK = new unsigned short[len + 1];
		memset(wszGBK, 0, len * 2 + 2);
		MultiByteToWideChar(CP_UTF8, 0, strUtf8, -1, (LPWSTR)wszGBK, len);
		len = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, NULL, 0, NULL, NULL);
		char *szGBK = new char[len + 1];
		memset(szGBK, 0, len + 1);
		WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)wszGBK, -1, (LPSTR)szGBK, len, NULL, NULL);
		return szGBK;
	}

	inline static int CalcGroupCount(int count, int max_pile_count)
	{
		if (max_pile_count == 0)
		{
			return 1;
		}
		int group_count = count / max_pile_count;
		if (count % max_pile_count != 0)
		{
			++group_count;
		}
		return group_count;
	}

	/*
	*	给Map中Value值加值
	*/
	template <typename MapType>
	inline void AddValueInMap(MapType& map_obj, typename MapType::key_type key, typename MapType::mapped_type value)
	{
		typename MapType::iterator iter = map_obj.find(key);
		if (iter != map_obj.end())
		{
			iter->second += value;
		}
		else
		{
			map_obj.insert(std::make_pair(key, value));
		}
	}

	/*
	*	获得Map中Value指针，如果Key不存在，则返回NULL
	*/
	template <typename MapType>
	inline typename MapType::mapped_type* GetValPtrFromMap(MapType& map_obj, typename MapType::key_type& key)
	{
		typename MapType::iterator iter = map_obj.find(key);
		return iter == map_obj.end() ? NULL : &iter->second;
	}

	/*
	* 给Map中插入一个Key，如果存在则返回false，成功则返回true
	*/
	template <typename MapType>
	inline bool InsertToMap(MapType& map_obj, typename MapType::key_type& key, typename MapType::mapped_type& value)
	{
		typename MapType::iterator iter = map_obj.find(key);
		if (iter != map_obj.end())
			return false;
		map_obj.insert(std::make_pair(key, value));
		return true;
	}

	/*
	*   值类型一定为指针
	*	获得Map中Value指针，如果Key不存在，则返回NULL
	*/
	template <typename MapType>
	inline typename MapType::mapped_type GetValFromMap(MapType& map_obj, typename MapType::key_type key)
	{
		typename MapType::iterator iter = map_obj.find(key);
		return iter == map_obj.end() ? NULL : iter->second;
	}

	/*
	*	查找一个数组中第一个值不为elem的下标
	*/
	template <typename T, unsigned int count>
	inline unsigned int FindFirstNotOf(const T(&arr)[count], const T& elem)
	{
		unsigned int index = 0;
		for (unsigned int i = 0; i < count; ++i)
		{
			if (elem != arr[i])
			{
				index = i;
				break;
			}
		}
		return index;
	}

	/*
	*	查找一个数组中第一个值为elem的下标
	*/
	template <typename T, unsigned int count>
	inline unsigned int FindFirstOf(const T(&arr)[count], const T& elem)
	{
		unsigned int index = 0;
		for (unsigned int i = 0; i < count; ++i)
		{
			if (elem == arr[i])
			{
				index = i;
				break;
			}
		}
		return index;
	}


#ifdef TWP_SNPRINTF
# undef	TWP_SNPRINTF
#endif // TWP_SNPRINTF
#if defined(linux) || defined(__linux) || defined(__linux__)
#  define TWP_SNPRINTF snprintf
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32)
#  define TWP_SNPRINTF(str, size, fmt, ...) _snprintf_s(str, size, (size) - 1, fmt, ##__VA_ARGS__)
#endif

	/**
	* \brief 把字符串根据token转化为多个字符串
	*
	* 下面是使用例子程序：
	*    <pre>
	*    std::list<string> ls;
	*    stringtok (ls," this  \t is\t\n  a test  ");
	*    for(std::list<string>const_iterator i = ls.begin(); i != ls.end(); ++i)
	*        std::cerr << ':' << (*i) << ":\n";
	*     </pre>
	*
	* \param container 容器，用于存放字符串
	* \param in 输入字符串
	* \param delimiters 分隔符号
	* \param deep 深度，分割的深度，缺省没有限制
	*/
	template <typename Container>
	inline void my_stringtok(Container &container, std::string const &in,
		const char * const delimiters = " \t\n",
		const int deep = 0)
	{
		const std::string::size_type len = in.length();
		std::string::size_type i = 0;
		int count = 0;

		while (i < len)
		{
			i = in.find_first_not_of(delimiters, i);
			if (i == std::string::npos)
				return;   // nothing left

						  // find the end of the token
			std::string::size_type j = in.find_first_of(delimiters, i);

			count++;
			// push token
			if (j == std::string::npos
				|| (deep > 0 && count > deep)) {
				container.push_back(in.substr(i));
				return;
			}
			else
				container.push_back(in.substr(i, j - i));

			// set up for next loop
			i = j + 1;
		}
	}

	template<typename T1, typename T2, typename T3> struct my_streble
	{
		T1 first;
		T2 second;
		T3 third;
		my_streble() :first(), second(), third() {}
		my_streble(const T1& t1, const T2& t2, const T3& t3) :first(t1), second(t2), third(t3) {}
		template<typename U1, typename U2, typename U3> my_streble(const my_streble<U1, U2, U3>& _streble) : first(_streble.first), second(_streble.second), third(_streble.third) {}
	};
	template<typename T1, typename T2, typename T3> inline static my_streble<T1, T2, T3> make_my_streble(T1 x, T2 y, T3 z)
	{
		return my_streble<T1, T2, T3>(x, y, z);
	}

};


/*
 * 解析指定分隔符间隔的资源文件
 * 如 Excel转为CVS的txt文件
 */
class zTextCVS
{
public:
	zTextCVS(const std::string& strFileName, uint32 nFlagsRow = 4, uint32 nDataStartRow = 6);

	~zTextCVS();

	/*
	* 读取当前行后面的第nLines行
	*/
	bool NextRow(int32 nLines = 1);

	/*
	* 获得数据块
	*/
	bool GetInt8(int8& o_nValue);
	bool GetUInt8(uint8& o_nValue);
	bool GetInt16(int16& o_nValue);
	bool GetUInt16(uint16& o_nValue);
	bool GetInt32(int32& o_nValue);
	bool GetUInt32(uint32& o_nValue);
	bool GetInt64(int64& o_nValue);
	bool GetFloat32(float32& o_fValue);
	bool GetString(std::string& o_strValue);
	const char*	GetCString();

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



