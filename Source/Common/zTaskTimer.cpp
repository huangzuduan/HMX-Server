/**
* \brief Zebra项目日志系统定义文件
*
*/
#include "SrvEngine.h"


zTaskTimer::zTaskTimer(int32_t interval, zTaskTimerHandler pHander)
	:m_Interval(interval),m_execTime(0),m_fHandler(pHander),m_ctimer(*this)
{
	m_bIsRunning = b1Sec = b2Sec = b3Sec = b5Sec = b1Min = b5Min = b1Hour = false;
}


zTaskTimer::~zTaskTimer()
{
}

void zTaskTimer::start()
{
	boost::thread t(boost::bind(&zTaskTimer::start_, this));
	boost::this_thread::yield();		// Temporarily give up a CPU time , to other threads
	t.swap(m_cServiceThread);	// Swaps the state of the object with that of mServiceThread
}

void zTaskTimer::start_()
{
	m_ctimer.expires_from_now(boost::posix_time::millisec(m_Interval));
	m_ctimer.async_wait(boost::bind(&zTaskTimer::timeout_,this, boost::asio::placeholders::error));
	if (!m_bIsRunning)
	{
		m_bIsRunning = true;
		io_service::run();
	}
}


void zTaskTimer::cancel()
{	
	m_ctimer.cancel();
	io_service::stop();
}

void zTaskTimer::timeout_(const boost::system::error_code& ec)
{
	if (ec == boost::asio::error::operation_aborted)
	{
		printf("TaskTimer::timeout canceled");
		ASSERT(0);
		m_bIsRunning = false;
		start_();
	}
	else
	{
		diytime_();
		(m_fHandler)(this);
		start_();
	}
}

void zTaskTimer::diytime_()
{
	m_execTime += m_Interval;
	b2Sec = b3Sec = b5Sec = b1Min = b5Min = b1Hour = false;
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

