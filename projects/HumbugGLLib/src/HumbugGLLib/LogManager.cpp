/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the LogManager.cpp class.
 * \folder     $(folder)
 * \file       LogManager.cpp
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "LogManager.h"
#include <algorithm>
#include <stdexcept>
//#include <boost/thread.hpp>
#define HUMBUGGL_AUTO_MUTEX_NAME mutex
#define HUMBUGGL_LOCK_AUTO_MUTEX
//#define HUMBUGGL_LOCK_AUTO_MUTEX boost::unique_lock<boost::recursive_mutex>
// ogreAutoMutexLock(OGRE_AUTO_MUTEX_NAME)
#ifndef HUMBUGGL_EXCEPT
//#define HUMBUGGL_EXCEPT(num, desc, src) throw HumbugGLLib::ExceptionFactory::create( \
// //	HumbugGLLib::ExceptionCodeType<num>(), desc, src, __FILE__, __LINE__ );
#  define HUMBUGGL_EXCEPT(num, desc, src);
#endif
//
#include <debug.h>

HumbugGLLIB_BEGIN_NAMESPACE

//-----------------------------------------------------------------------
template<>
LogManager * Singleton<LogManager>::msSingleton = 0;
/** LogManager, getSingletonPtr:
 *  Detailed description.
 *  @return TODO
 */
LogManager * LogManager::getSingletonPtr(void){
    return msSingleton;
}

/** LogManager, getSingleton:
 *  Detailed description.
 *  @return TODO
 */
LogManager& LogManager::getSingleton(void){
    assert( msSingleton );
    return ( *msSingleton );
}

//-----------------------------------------------------------------------
LogManager::LogManager(){
    mDefaultLog = NULL;
}

//-----------------------------------------------------------------------
LogManager::~LogManager(){
    HUMBUGGL_LOCK_AUTO_MUTEX;
    // Destroy all logs
    LogList::iterator i;

    for (i = mLogs.begin(); i != mLogs.end(); ++i)
    {
        delete i->second;
    }
}

//-----------------------------------------------------------------------
Log * LogManager::createLog( const std::string& name, bool defaultLog, bool debuggerOutput,
        bool suppressFileOutput){
    HUMBUGGL_LOCK_AUTO_MUTEX;

    Log* newLog = new Log(name, debuggerOutput, suppressFileOutput);

    if( !mDefaultLog || defaultLog ) {
        mDefaultLog = newLog;
    }

    mLogs.insert( LogList::value_type( name, newLog ) );

    return newLog;
}

//-----------------------------------------------------------------------
Log * LogManager::getDefaultLog(){
    HUMBUGGL_LOCK_AUTO_MUTEX;
    return mDefaultLog;
}

//-----------------------------------------------------------------------
Log * LogManager::setDefaultLog(Log* newLog){
    HUMBUGGL_LOCK_AUTO_MUTEX;
    Log* oldLog = mDefaultLog;
    mDefaultLog = newLog;
    return oldLog;
}

//-----------------------------------------------------------------------
Log * LogManager::getLog( const std::string& name){
    HUMBUGGL_LOCK_AUTO_MUTEX;
    LogList::iterator i = mLogs.find(name);

    if ( i != mLogs.end() ) {
        return i->second;
    }
    else {
        HUMBUGGL_EXCEPT(Exception::ERR_INVALIDPARAMS, "Log not found. ", "LogManager::getLog");
        throw std::runtime_error("Log not found. LogManager::getLog");
    }
}

//-----------------------------------------------------------------------
void LogManager::destroyLog(const std::string& name){
    LogList::iterator i = mLogs.find(name);

    if ( i != mLogs.end() ) {
        if (mDefaultLog == i->second) {
            mDefaultLog = 0;
        }

        delete i->second;
        mLogs.erase(i);
    }

    // Set another default log if this one removed
    if ( !mDefaultLog && !mLogs.empty() ) {
        mDefaultLog = mLogs.begin()->second;
    }
} // destroyLog

//-----------------------------------------------------------------------
void LogManager::destroyLog(Log* log){
    if(!log) {
        HUMBUGGL_EXCEPT(Exception::ERR_INVALIDPARAMS, "Cannot destroy a null log.", "LogManager::destroyLog");
        throw std::runtime_error("Cannot destroy a null log. LogManager::destroyLog");
    }

    destroyLog( log->getName() );
}

//-----------------------------------------------------------------------
void LogManager::logMessage( const std::string& message, LogMessageLevel lml, bool maskDebug){
    HUMBUGGL_LOCK_AUTO_MUTEX;

    if (mDefaultLog) {
        mDefaultLog->logMessage(message, lml, maskDebug);
    }
}

//-----------------------------------------------------------------------
void LogManager::setLogDetail(LoggingLevel ll){
    HUMBUGGL_LOCK_AUTO_MUTEX;

    if (mDefaultLog) {
        mDefaultLog->setLogDetail(ll);
    }
}

//---------------------------------------------------------------------
Log::Stream LogManager::stream(LogMessageLevel lml, bool maskDebug){
    HUMBUGGL_LOCK_AUTO_MUTEX;

    if (mDefaultLog) {
        return mDefaultLog->stream(lml, maskDebug);
    }
    else {
        HUMBUGGL_EXCEPT(Exception::ERR_INVALIDPARAMS, "Default log not found. ", "LogManager::stream");
        throw std::runtime_error("Default log not found. LogManager::stream");
    }
}

/*bool Log::getName()
   {
        throw std::exception("The method or operation is not implemented.");
   }*/

HumbugGLLIB_END_NAMESPACE

extern "C" {
    /** $(fclass), _log_from_c:
     *  Detailed description.
     *  @param file TODO
     * @param function TODO
     * @param text TODO
     */
    void _log_from_c(char* file, char* function, char* text ){
        // fprintf(stderr, "ERROR in %s:%s(): %s\n", file, function, text);
        humbuglib::LogManager::getSingleton().stream() << "ERROR in " << file << ":" << function << "(): " << text;
    }
};
