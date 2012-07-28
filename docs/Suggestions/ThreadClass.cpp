
#include "ThreadClass.hpp"

//-----------------------------------------------------------------------------
ThreadClass::ThreadClass()
{
  // this should always be the last line in the constructor
  internalThread_ = boost::thread(&ThreadClass::threadMain, this);

} // Constructor

ThreadClass::~ThreadClass()
{
  internalThread_.interrupt();
  internalThread_.join(); // make damn sure that the internal thread is gone
                          // before we destroy the class data.
} // Destructor

//-----------------------------------------------------------------------------
void ThreadClass::threadMain()
{
  try
  {
    /* add whatever code you want the thread to execute here. */

  }
  catch (boost::thread_interrupted& interruption)
  {
    // thread was interrupted, this is expected.

  }
  catch (std::exception& e)
  {
    // an unhandled exception reached this point, this constitutes an error

  }

} // threadMain

//-----------------------------------------------------------------------------
