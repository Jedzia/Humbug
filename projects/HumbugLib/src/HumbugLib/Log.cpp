/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Logger class.
 * \folder     $(folder)
 * \file       Log.cpp
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "Log.h"
#include "LogManager.h"
#include <time.h>

#if _DEBUG && (WIN32)
#  pragma push_macro("NOMINMAX")
#  define NOMINMAX
#  include <windows.h>
#  pragma pop_macro("NOMINMAX")
#  define HUMBUGLIB_OutputCString(str) ::OutputDebugStringA(str)
#  define HUMBUGLIB_OutputWString(str) ::OutputDebugStringW(str)
#else
#  define HUMBUGLIB_OutputCString(str) std::cerr << str
#  define HUMBUGLIB_OutputWString(str) std::cerr << str
#endif

#define String std::string
#define HUMBUGLIB_LOCK_AUTO_MUTEX

//
#include <debug.h>

HumbugLIB_BEGIN_NAMESPACE
//-----------------------------------------------------------------------
Log::Log( const String& name, bool debuggerOuput, bool suppressFile ) :
    mLogLevel(LL_NORMAL),
    mDebugOut(debuggerOuput),
    mSuppressFile(suppressFile),
    mTimeStamp(true),
    mLogName(name){
    if (!mSuppressFile) {
        mLog.open( name.c_str() );
    }
}

//-----------------------------------------------------------------------
Log::~Log(){
    HUMBUGLIB_LOCK_AUTO_MUTEX;

    if (!mSuppressFile) {
        mLog.close();
    }
}

//-----------------------------------------------------------------------
void Log::logMessage( const String& message, LogMessageLevel lml, bool maskDebug ){
    HUMBUGLIB_LOCK_AUTO_MUTEX;

    if ( (mLogLevel + lml) >= HUMBUGLIB_LOG_THRESHOLD ) {
        bool skipThisMessage = false;

        for( mtLogListener::iterator i = mListeners.begin(); i != mListeners.end(); ++i ) {
            (*i)->messageLogged( message, lml, maskDebug, mLogName, skipThisMessage);
        }

        if (!skipThisMessage) {
            if (mDebugOut && !maskDebug)
#if _DEBUG && (HUMBUGLIB_PLATFORM == HUMBUGLIB_PLATFORM_WIN32 || HUMBUGLIB_PLATFORM == HUMBUGLIB_PLATFORM_WINRT)
            {
                String logMessageString(message);
                logMessageString.append( "\n" );
                HUMBUGLIB_OutputCString( logMessageString.c_str() );
            }

#else
            { std::cerr << message << std::endl; }
#endif

            // Write time into log
            if (!mSuppressFile) {
                if (mTimeStamp) {
                    struct tm* pTime;
                    time_t ctTime;
                    time(&ctTime);
                    pTime = localtime( &ctTime );
                    mLog << std::setw(2) << std::setfill('0') << pTime->tm_hour <<
                    ":" << std::setw(2) << std::setfill('0') << pTime->tm_min <<
                    ":" << std::setw(2) << std::setfill('0') << pTime->tm_sec <<
                    ": ";
                }

                mLog << message << std::endl;

                // Flush stcmdream to ensure it is written (incase of a crash, we need log to be up
                // to date)
                mLog.flush();
            }
        }
    }
} // logMessage

//-----------------------------------------------------------------------
void Log::setTimeStampEnabled(bool timeStamp){
    HUMBUGLIB_LOCK_AUTO_MUTEX;
    mTimeStamp = timeStamp;
}

//-----------------------------------------------------------------------
void Log::setDebugOutputEnabled(bool debugOutput){
    HUMBUGLIB_LOCK_AUTO_MUTEX;
    mDebugOut = debugOutput;
}

//-----------------------------------------------------------------------
void Log::setLogDetail(LoggingLevel ll){
    HUMBUGLIB_LOCK_AUTO_MUTEX;
    mLogLevel = ll;
}

//-----------------------------------------------------------------------
void Log::addListener(LogListener* listener){
    HUMBUGLIB_LOCK_AUTO_MUTEX;
    mListeners.push_back(listener);
}

//-----------------------------------------------------------------------
void Log::removeListener(LogListener* listener){
    HUMBUGLIB_LOCK_AUTO_MUTEX;
    mListeners.erase( std::find(mListeners.begin(), mListeners.end(), listener) );
}

//---------------------------------------------------------------------
Log::Stream Log::stream(LogMessageLevel lml, bool maskDebug){
    return Stream(this, lml, maskDebug);
}

HumbugLIB_END_NAMESPACE
