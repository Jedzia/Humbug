
#include "boost/thread.hpp"

//*****************************************************************************
/** Class that encapsulates a thread and binds it to it's lifetime.
 *
 * This class is designed to run a thread internally and make sure
 * the data the thread works on remains valid. It does this by
 * binding the lifetime of the thread to it's own lifetime. The thread is
 * started in the constructor after all data is initialised correctly. If
 * the object is destroyed then destruction will block until the thread has
 * finished it's work.
 */
class ThreadClass
{
public: // methods
  /** Constructor
   *
   * starts the internal thread running.
   */
  ThreadClass();

  /** Destructor
   *
   * Blocks until the thread has finished executing, if it hasn't
   * finished already.
   */
  ~ThreadClass();

private: // methods
  /** This is the function that the thread executes.
   *
   * The thread will finish when this function returns.
   */
  void threadMain();

private: // data
  boost::thread internalThread_;

}; // class

//*****************************************************************************
