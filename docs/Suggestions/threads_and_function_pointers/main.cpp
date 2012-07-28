
#include "Timer.hpp"

#include "boost/date_time.hpp"
#include "boost/thread.hpp"
#include "boost/bind.hpp"

#include <iostream>

namespace
{
  void timerExpired()
  {
    std::cout << "Buzz!!!" << std::endl;
  }

} // namespace

int main(int c, char** argv)
{
  Timer threeSecondTimer(boost::posix_time::seconds(3), 
												 boost::bind(&::timerExpired));
  Timer fiveSecondTimer(boost::posix_time::seconds(5), 
												boost::bind(&::timerExpired));

  for (int i=1; i<=10; ++i)
  {
    boost::this_thread::sleep(boost::posix_time::seconds(1));
    if (i == 3 || i == 5)
      continue;
    std::cout << "Zzzz..." << std::endl;
  }

} // main
