#include "FogsTimerService.hpp"

namespace fogs
{
using namespace std;


void FogsTimer::start_()
{
//	fogs::FogsTimerTraits::time_type now = fogs::FogsTimerTraits::now();
//	fogs::FogsTimerTraits::time_type from = timer_.expires_at();
//	fogs::FogsTimerTraits::time_type to;
//	timer_.expires_at(
//			FogsTimerTraits::add(timer_.expires_at(),
//					FogsTimerTraits::duration_type(duration_)));

	timer_.expires_from_now(boost::posix_time::milliseconds(duration_));
//	to = timer_.expires_at();

//	std::cout <<
//			"start timer from " << from.ticks_ <<
//			" to " << to.ticks_ <<
//			" now : " << now.ticks_ <<
//			std::endl;

//	struct timeval tv;
//	gettimeofday(&tv, NULL);
//
//	uint32_t t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
//	std::cout << "My timer start  " << "at " <<  t << "\n";

	timer_.async_wait(boost::bind(&FogsTimer::timeout,
			this,  boost::asio::placeholders::error));
}


void FogsTimer::timeout(
    const boost::system::error_code& ec)
{

//	struct timeval tv;
//	gettimeofday(&tv, NULL);
//
//	uint32_t t = tv.tv_sec * 1000 + tv.tv_usec / 1000;
//	std::cout << "TIMEOUT with error code : " << ec.message() <<
//			" at " << t << std::endl;


//	std::cout << "TIMEOUT with error code : " << ec.message() <<

//			" at " <<  timer_.expires_at().ticks_<<  "/" <<
//			fogs::FogsTimerTraits::now().ticks_  <<
//			std::endl;
	if (ec == boost::asio::error::operation_aborted)
	{
		// timer is canceled
//		std::cout << "Timer canceled : "
//				<< ec.message() << std::endl;

		return;
	}
	if (type_ == PERIODICAL_TIMER)
	{
		start_();
	}

	timeoutHandler_(ec);

}





}
