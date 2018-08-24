#ifndef FOGSTIMERSERVICE_HPP_
#define FOGSTIMERSERVICE_HPP_

#include <ctime>
#include <time.h>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <boost/date_time/posix_time/posix_time.hpp>


namespace fogs
{


class FogsTimer;

struct FogsTimerTraits
{

  class time_type
  {
  public:
	  time_type() : ticks_(0) {}
  private:
    friend struct FogsTimerTraits;
    friend class FogsTimer;
    uint32_t ticks_;
  };

  // The duration type.
  class duration_type
  {
  public:
	  duration_type() : ticks_(0) {}
	  duration_type(uint32_t ticks) : ticks_(ticks) {}
  private:
    friend struct FogsTimerTraits;
    friend class FogsTimer;
    uint32_t ticks_;
  };

  // Get the current time.
  static time_type now()
  {
	  time_type result;
	  /*struct timeval tv;
	  gettimeofday(&tv, 0);
	  result.ticks_ = tv.tv_sec * 1000 + tv.tv_usec/1000;*/

	  result.ticks_ = time(NULL);
    return result;
  }

  // Add a duration to a time.
  static time_type add(const time_type& t, const duration_type& d)
  {
    time_type result;
    result.ticks_ = t.ticks_ + d.ticks_;
    return result;
  }

  // Subtract one time from another.
  static duration_type subtract(const time_type& t1, const time_type& t2)
  {
    return duration_type(t1.ticks_ - t2.ticks_);
  }

  // Test whether one time is less than another.
  static bool less_than(const time_type& t1, const time_type& t2)
  {
    // DWORD tick count values wrap periodically, so we'll use a heuristic that
    // says that if subtracting t1 from t2 yields a value smaller than 2^31,
    // then t1 is probably less than t2. This means that we can't handle
    // durations larger than 2^31, which shouldn't be a problem in practice.
    return (t2.ticks_ - t1.ticks_) < static_cast<uint32_t>(1 << 31);
  }

  // Convert to POSIX duration type.
  static boost::posix_time::time_duration to_posix_duration(
      const duration_type& d)
  {
    return boost::posix_time::milliseconds(d.ticks_);
  }
};

//typedef boost::asio::basic_deadline_timer<
//    uint32_t, FogsTimerTraits> FogsTickTimer;


typedef boost::asio::deadline_timer FogsTickTimer;




class FogsTimer
{
public:
	typedef enum
	{
		SINGLE_SHOOT_TIMER,
		PERIODICAL_TIMER,
	} TYPE;

	typedef boost::function1<void,
			boost::system::error_code> TimeoutHandler;


	explicit FogsTimer(boost::asio::io_service &ioService)
		:timer_(ioService)
	{
	}


	template<typename WaitHandler>
	void start(uint32_t ms,
			WaitHandler handler,
			TYPE type)
	{
		timeoutHandler_ = boost::bind(handler,
				  boost::asio::placeholders::error);
		duration_ = ms;
		type_ = type;
		start_();
	}

	int cancel()
	{
		return timer_.cancel();
	}


private:
	TYPE type_;
	uint32_t duration_;
	FogsTickTimer timer_;
	TimeoutHandler timeoutHandler_;

	void start_();

	void timeout(const boost::system::error_code& ec);
};




class FogsTimerService
{
public:
	typedef enum {
		SINGLE_SHOOT,
		PERICICAL,
	} timer_type_t;
	typedef uint32_t timer_id_t;


//	timer_id_t createTimer();
//
//	void startTimer(timer_type_t type, TimerHandler handler);
//
//	void stopTimer(timer_id_t id);



private:
	FogsTimerService();

	int initTimerService();

};

}

#endif /* FOGSTIMERSERVICE_HPP_ */
