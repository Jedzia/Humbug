/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Singleton.h class.
 * \folder     $(folder)
 * \file       Singleton.h
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef _SINGLETON_H__
#define _SINGLETON_H__

#include <HumbugLib/global.h>

#if defined( _MSC_VER )
// Turn off warnings generated by this singleton implementation
#  pragma warning (disable : 4311)
#  pragma warning (disable : 4312)
#  pragma warning (disable : 4661)
#endif

#if defined ( _GCC_VISIBILITY )
#  pragma GCC visibility push(default)
#endif

namespace humbuglib {

/** Template class for creating single-instance global classes.
 */
template <typename T>
class Singleton {
private:

    /** @brief Prevent the use of a copy constructor.*/
    Singleton(const Singleton<T> &);

    /** @brief Prevent he use of operator= .*/
    Singleton& operator=(const Singleton<T> &);

protected:

    static T* msSingleton;

public:

    Singleton( void ){
        assert( !msSingleton );
#if defined( _MSC_VER ) && _MSC_VER < 1200
        int offset = (int)(T *)1 - (int)(Singleton <T> *)(T *) 1;
        msSingleton = (T *)( (int)this + offset );
#else
        msSingleton = static_cast< T * >( this );
#endif
    }
    ~Singleton( void )
    {  assert( msSingleton );  msSingleton = 0;  }

    /** $(fclass), getSingleton:
     *  Detailed description.
     *  @return TODO
     */
    static T& getSingleton( void )
    {       assert( msSingleton );  return ( *msSingleton ); }

    /** $(fclass), getSingletonPtr:
     *  Detailed description.
     *  @return TODO
     */
    static T * getSingletonPtr( void )
    { return msSingleton; }
};

/** @} */
/** @} */
}
#if defined ( _GCC_VISIBILITY )
#  pragma GCC visibility pop
#endif

#endif // ifndef _SINGLETON_H__
