
#include "Hash.hpp"

#include "boost/functional/hash.hpp"
#include "boost/thread.hpp"

namespace hash {

//-----------------------------------------------------------------------------
  boost::shared_array<size_t> getHashValues(float* values,
                                            const int numValues)
  {
    boost::hash<float> hasher;
    boost::shared_array<size_t> hashedValues( new size_t[numValues] );
    for(int i=0; i<numValues; ++i)
    {
      hashedValues[i] = hasher(values[i]);
    }

    return hashedValues;

  }

//-----------------------------------------------------------------------------
boost::shared_array<size_t> getHashValuesThreaded(float* values,
                                                  const int numValues)
{
  /** typedefs and constants to aid comprehensibility */
  typedef boost::packaged_task<boost::shared_array<size_t> > HashingTask;
  typedef boost::unique_future<boost::shared_array<size_t> > HashingFuture;

  const size_t middle = numValues / 2;
  const size_t halfValuesRoundedDown = numValues / 2;
  const size_t halfValuesRoundedUp = numValues - halfValuesRoundedDown;

  /** create a task and bind the hasher with the bottom
    * half of the values. */
  HashingTask hashTask( boost::bind(&hash::getHashValues,
                                    &values[0],
                                    halfValuesRoundedDown) );
  /** get the future from the task */
  HashingFuture hashFuture = hashTask.get_future();

  /** kick off a thread to hash the bottom half */
  boost::thread hashThread( boost::move(hashTask) );

  /** the thread is hashing the bottom half so now hash
    * the top half at the same time */
  boost::shared_array<size_t> topHalfResults =
      getHashValues(&values[middle], halfValuesRoundedUp);

  /** get the results from the future, blocks until they are ready. */
  boost::shared_array<size_t> bottomHalfResults = hashFuture.get();

  /** copy the two halves of the hashed values into the
      final array to be returned. */
  boost::shared_array<size_t> fullResults( new size_t[numValues] );
  std::copy(&bottomHalfResults[0],
            &bottomHalfResults[halfValuesRoundedDown],
            &fullResults[0]);

  std::copy(&topHalfResults[0],
            &topHalfResults[halfValuesRoundedUp],
            &fullResults[numValues/2]);

  return fullResults;

}

//-----------------------------------------------------------------------------

} // namespace
