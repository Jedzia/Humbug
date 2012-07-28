/**********************************************************************************************************************
**         __________              ___                              ________                                         **
**         \______   \_____     __| _/ _____  _____     ____       /  _____/ _____     _____    ____    ______       **
**          |       _/\__  \   / __ | /     \ \__  \   /    \     /   \  ___ \__  \   /     \ _/ __ \  /  ___/       **
**          |    |   \ / __ \_/ /_/ ||  Y Y  \ / __ \_|   |  \    \    \_\  \ / __ \_|  Y Y  \\  ___/  \___ \        **
**          |____|_  /(____  /\____ ||__|_|  /(____  /|___|  /     \______  /(____  /|__|_|  / \___  \/____  \       **
**                 \/      \/      \/      \/      \/      \/             \/      \/       \/      \/      \/        **
**                                                         2011                                                      **
**********************************************************************************************************************/

#ifndef RADLIB_CORELIB_GENERICFACTORY_HPP
#define RADLIB_CORELIB_GENERICFACTORY_HPP

#include "boost/function.hpp"

#include <map>

namespace radlib
{
//*********************************************************************************************************************
  /** A generic factory that allows a user to create objects based off configured index associations.
   *
   * @todo at the moment the third template parameter (creator method) is specified as a function returning the
   * factory product type and taking no parameters. It may be desirable to specify creator functions that accept some
   * parameters and this can be supported by either using variadic templates (C++11) or by manually writing template
   * methods that handle 1..N parameters and then executing the creator method.
   * @todo also might want an unregister method.
   */
  template <typename T_FactoryProduct,
            typename T_IndexValue,
            typename T_CreatorMethod = boost::function<T_FactoryProduct()> >
  class GenericFactory
  {
  public: // interface
    /** Register a creator method for the given value
     *
     * @throws if a method has already been registered for the index.
     */
    void registerCreator(const T_IndexValue& index, const T_CreatorMethod& creatorMethod)
    {
      if ( creatorIndex_.find(index) == creatorIndex_.end() )
      {
        creatorIndex_.insert( std::make_pair(index, creatorMethod) );
      }
      else
      {
        throw std::runtime_error("Creator method already specified for index"); // interface requirement
      }
    }

    /** Construct and return a product of the specified type
     *
     * @throws if there is no creator method registered for the index.
     */
    T_FactoryProduct get(const T_IndexValue& index)
    {
      if ( creatorIndex_.find(index) != creatorIndex_.end() )
      {
        return creatorIndex_[index]();
      }
      else
      {
        throw std::runtime_error("Creator method for index has not been registered with the factory");
      }
    }

  private: // types
    typedef std::map<T_IndexValue, T_CreatorMethod> CreatorIndex;

  private: // data
    CreatorIndex creatorIndex_;

  }; // class

//*********************************************************************************************************************

} // namespace

#endif // RADLIB_CORELIB_GENERICFACTORY_HPP
