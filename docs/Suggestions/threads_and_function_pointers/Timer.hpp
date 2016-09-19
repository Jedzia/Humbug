
#include "boost/thread.hpp"
#include "boost/date_time.hpp"
#include "boost/function.hpp"

//*****************************************************************************
/** Notifies a callback function after a given amount of time has elapsed
 */
class Timer
{
public: // types
  typedef boost::function<void()> TimerReportingCallback;

public: // methods
  /** Constructor
   *
   * @throws if callback passed for reporting is not valid.
   */
  Timer(const boost::posix_time::time_duration& timeToWait,
        TimerReportingCallback reportingCallback);

  ~Timer();

private: // methods
  void threadMain();

private: // data
  boost::thread internalThread_;
  boost::posix_time::time_duration timeToWait_;
  TimerReportingCallback reportingCallback_;

}; // class

//*****************************************************************************
