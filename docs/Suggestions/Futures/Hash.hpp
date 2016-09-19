
#ifndef __HASH_HPP__
#define __HASH_HPP__

#include "boost/shared_array.hpp"

namespace hash
{
  /** returns a corresponding array of hash values based
      on the values provided. */
  boost::shared_array<size_t> getHashValues(float* values,
                                            int numValues);

  /** uses one additional thread to hash the values
    * provided.  */
  boost::shared_array<size_t> getHashValuesThreaded(float* values,
                                                    int numValues);
}

#endif // __HASH_HPP__
