
#include "Hash.hpp"

#include "boost/random.hpp"
#include "boost/date_time.hpp"
#include "boost/progress.hpp"
#include "boost/shared_array.hpp"

#include <iostream>
#include <ctime>

//-----------------------------------------------------------------------------
int main(int argc, char** argv)
{
  try
  {
    /** typdefs to improve readability */
    typedef boost::uniform_real<> UniformDist;
    typedef boost::mt19937 BaseRandomNumberGenerator;
    typedef boost::variate_generator<BaseRandomNumberGenerator&,UniformDist>
        NumberGenerator;

    typedef boost::posix_time::microsec_clock Clock;

    const unsigned int NUM_VALUES = 1E07;

    /** set up the random number generator */
    UniformDist distribution(0, NUM_VALUES);
    BaseRandomNumberGenerator generator;
    NumberGenerator numberGenerator(generator, distribution);
    generator.seed(std::time(0)); // seed with seconds since Jan 1 1970

    std::cout << std::endl << "Generating random numbers to hash..."
              << std::endl;

    boost::shared_array<float> valuesToHash(new float[NUM_VALUES]);
    boost::progress_display showProgress(NUM_VALUES);
    for (int i=0; i<NUM_VALUES; ++i)
    {
      valuesToHash[i] = numberGenerator();
      ++showProgress;
    }

    std::cout << std::endl << "Finished generating numbers, hashing..."
              << std::endl << std::endl;

    boost::posix_time::ptime start = Clock::local_time();
    boost::shared_array<size_t> valueHashes =
        hash::getHashValuesThreaded(valuesToHash.get(), NUM_VALUES);

    std::cout << "Hashing Took: " << Clock::local_time() - start << std::endl;

  }
  catch (std::runtime_error& e)
  {
    std::cout << "Unhandled Exception: \"" << e.what() << "\"" << std::endl;

  }

} // main

//-----------------------------------------------------------------------------
