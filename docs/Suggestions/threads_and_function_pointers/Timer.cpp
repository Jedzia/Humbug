
#include "Timer.hpp"

//-----------------------------------------------------------------------------
Timer::Timer(const boost::posix_time::time_duration& timeToWait,
             TimerReportingCallback reportingCallback) :
  timeToWait_(timeToWait),
  reportingCallback_(reportingCallback)
{
  if ( ! reportingCallback_ )
    throw std::runtime_error("callback given to Timer was not vaild!");

  boost::thread(&Timer::threadMain, this);

}

Timer::~Timer()
{
  internalThread_.interrupt();
  internalThread_.join();

}

//-----------------------------------------------------------------------------
void Timer::threadMain()
{
  try
  {
    boost::this_thread::sleep( timeToWait_ );
    reportingCallback_();

  }
  catch (boost::thread_interrupted& interruption)
  {
    // thread was interrupted, this is expected.

  }
  catch (std::exception& e)
  {
    // an unhandled exception reached this point, this constitutes an error

  }

}

//-----------------------------------------------------------------------------
