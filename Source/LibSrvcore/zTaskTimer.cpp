/**
* \brief Zebra项目日志系统定义文件
*
*/
#include "SrvEngine.h"


zTaskTimer::zTaskTimer(int32 interval,int32 maxTimes, zTaskTimerHandler pHander)
	:m_Interval(interval),m_MaxTimes(maxTimes),m_fHandler(pHander),m_ctimer(*this)
{
	m_HadTimes = m_execTime = 0;
	b1Sec = b2Sec = b3Sec = b5Sec = b1Min = b5Min = b1Hour = false;
	bNewHour = bNewDay = bNewWeek = bNewMonth = bNewYear = false;
}


zTaskTimer::~zTaskTimer()
{
}

void zTaskTimer::start()
{
	thread t(boost::bind(&zTaskTimer::doStart, this));
	this_thread::yield();		// Temporarily give up a CPU time , to other threads
	t.swap(m_cServiceThread);	// Swaps the state of the object with that of mServiceThread
}

void zTaskTimer::doStart()
{
	m_ctimer.expires_from_now(posix_time::millisec(m_Interval));
	m_ctimer.async_wait(boost::bind(&zTaskTimer::doHandler,this)); 
	io_service::run();
}


void zTaskTimer::cancel()
{	
	m_ctimer.cancel();
	io_service::stop();
}

void zTaskTimer::doHandler()
{
	m_execTime += m_Interval;

	diyTimeCache();

	m_ctimer.expires_at(m_ctimer.expires_at() + posix_time::millisec(m_Interval));
	m_ctimer.async_wait(boost::bind(&zTaskTimer::doHandler,this));
	(m_fHandler)(this);

	checkCancel();
}

void zTaskTimer::diyTimeCache()
{
	b1Sec = m_execTime % 1000 < m_Interval;
	if (b1Sec)
	{
		b2Sec = m_execTime % 2000 < m_Interval;
		b3Sec = m_execTime % 3000 < m_Interval;
		b5Sec = m_execTime % 5000 < m_Interval;
		if (b5Sec)
		{
			b1Min = m_execTime % 60000 < m_Interval;
			if (b1Min)
			{
				b5Min = m_execTime % 300000 < m_Interval;
				if (b5Min)
				{
					b1Hour = m_execTime % 3600000 < m_Interval;
				}
			}
		}
	}

	b2Sec = false;
	b3Sec = false;
	b5Sec = false;
	b1Min = false;
	b5Min = false;
	b1Hour = false;
}

void zTaskTimer::checkCancel()
{
	if (m_MaxTimes > 0 && m_MaxTimes == m_HadTimes)
	{
		m_ctimer.cancel();
		io_service::stop();
	}
}

bool zTaskTimer::is1Sec() const
{
	return b1Sec;
}

bool zTaskTimer::is2Sec() const
{
	return b2Sec;
}

bool zTaskTimer::is3Sec() const
{
	return b3Sec;
}

bool zTaskTimer::is5Sec() const
{
	return b5Sec;
}

bool zTaskTimer::is1Min() const
{
	return b1Min;
}

bool zTaskTimer::is5Min() const
{
	return b5Min;
}

bool zTaskTimer::is1Hour() const
{
	return b1Hour;
}

bool zTaskTimer::isNewHour() const
{
	return bNewHour;
}

bool zTaskTimer::isNewDay() const
{
	return bNewDay;
}

bool zTaskTimer::isNewWeek() const
{
	return bNewWeek;
}

bool zTaskTimer::isNewMonth() const
{
	return bNewMonth;
}

bool zTaskTimer::isNewYear() const
{
	return bNewYear;
}
