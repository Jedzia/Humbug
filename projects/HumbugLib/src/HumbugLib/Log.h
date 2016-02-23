/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Log.h class.
 * \folder     $(folder)
 * \file       Log.h
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/

#ifndef __Log_H__
#define __Log_H__

#include "global.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iosfwd>
#include <iostream>

namespace humbuglib {

/** \addtogroup Core
 *  @{
 */
/** \addtogroup General
 *  @{
 */
// LogMessageLevel + LoggingLevel > HUMBUGLIB_LOG_THRESHOLD = message logged
#define HUMBUGLIB_LOG_THRESHOLD 4

/** The level of detail to which the log will go into.
 */
enum LoggingLevel {
    LL_LOW = 1,
    LL_NORMAL = 2,
    LL_BOREME = 3
};

/** The importance of a logged message.
 */
enum LogMessageLevel {
    LML_TRIVIAL = 1,
    LML_NORMAL = 2,
    LML_CRITICAL = 3
};

/** @remarks Pure Abstract class, derive this class and register to the Log to listen to log
   messages */
class LogListener {
public:

    virtual ~LogListener() {}

    /**
       @remarks
        This is called whenever the log receives a message and is about to write it out
       @param message
        The message to be logged
       @param lml
        The message level the log is using
       @param maskDebug
        If we are printing to the console or not
       @param logName
        The name of this log (so you can have several listeners for different logs, and identify
           them)
            @param skipThisMessage
                    If set to true by the messageLogged() implementation message will not be logged
     */
    virtual void messageLogged( const std::string& message, LogMessageLevel lml, bool maskDebug,
            const std::string &logName,
            bool& skipThisMessage ) = 0;
};

/**
   @remarks
     Log class for writing debug/log data to files.
   @note
    <br>Should not be used directly, but trough the LogManager class.
 */
class PLATFORM_DECL Log         //: public LogAlloc
{
protected:

    std::ofstream mLog;
    LoggingLevel mLogLevel;
    bool mDebugOut;
    bool mSuppressFile;
    bool mTimeStamp;
    std::string mLogName;

    typedef std::vector<LogListener *> mtLogListener;
    mtLogListener mListeners;

public:

    class Stream;

    //HUMBUGLIB_AUTO_MUTEX; // public to allow external locking
    /**
       @remarks
        Usual constructor - called by LogManager.
     */
    Log( const std::string& name, bool debugOutput = true, bool suppressFileOutput = false);

    /**
       @remarks
       Default destructor.
     */
    ~Log();

    /// Return the name of the log
    const std::string& getName() const { return mLogName; }

    /// Get whether debug output is enabled for this log
    bool isDebugOutputEnabled() const { return mDebugOut; }

    /// Get whether file output is suppressed for this log
    bool isFileOutputSuppressed() const { return mSuppressFile; }

    /// Get whether time stamps are printed for this log
    bool isTimeStampEnabled() const { return mTimeStamp; }

    /** Log a message to the debugger and to log file (the default is
        "<code>HUMBUGLIB.log</code>"),
     */
    void logMessage( const std::string& message, LogMessageLevel lml = LML_NORMAL, bool maskDebug = false );

    /** Get a stream object targeting this log. */
    Stream stream(LogMessageLevel lml = LML_NORMAL, bool maskDebug = false);

    /**
       @remarks
        Enable or disable outputting log messages to the debugger.
     */
    void setDebugOutputEnabled(bool debugOutput);

    /**
       @remarks
       Sets the level of the log detail.
     */
    void setLogDetail(LoggingLevel ll);

    /**
       @remarks
        Enable or disable time stamps.
     */
    void setTimeStampEnabled(bool timeStamp);

    /** Gets the level of the log detail.
     */
    LoggingLevel getLogDetail() const { return mLogLevel; }

    /**
       @remarks
        Register a listener to this log
       @param listener
        A valid listener derived class
     */
    void addListener(LogListener* listener);

    /**
       @remarks
        Unregister a listener from this log
       @param listener
        A valid listener derived class
     */
    void removeListener(LogListener* listener);

    /** Stream object which targets a log.
       @remarks
            A stream logger object makes it simpler to send various things to
            a log. You can just use the operator<< implementation to stream
            anything to the log, which is cached until a Stream::Flush is
            encountered, or the stream itself is destroyed, at which point the
            cached contents are sent to the underlying log. You can use Log::stream()
            directly without assigning it to a local variable and as soon as the
            streaming is finished, the object will be destroyed and the message
            logged.
       @par
            You can stream control operations to this object too, such as
            std::setw() and std::setfill() to control formatting.
       @note
            Each Stream object is not thread safe, so do not pass it between
            threads. Multiple threads can hold their own Stream instances pointing
            at the same Log though and that is threadsafe.
     */
    class /*__attribute__ ((visibility("hidden")))*/ Stream {
protected:

        Log* mTarget;
        LogMessageLevel mLevel;
        bool mMaskDebug; 
		typedef std::stringstream BaseStream;
        BaseStream mCache;

public:
    typedef BaseStream::char_type char_type;
        
        /// Simple type to indicate a flush of the stream to the log
        struct Flush {};

        Stream(Log* target, LogMessageLevel lml, bool maskDebug) :
            mTarget(target),
            mLevel(lml),
            mMaskDebug(maskDebug)
        {}

        // copy constructor
        Stream(const Stream& rhs) :
            mTarget(rhs.mTarget),
            mLevel(rhs.mLevel),
            mMaskDebug(rhs.mMaskDebug){
            // explicit copy of stream required, gcc doesn't like implicit
            mCache.str(rhs.mCache.str());
        }
        ~Stream(){
            // flush on destroy
            if (mCache.tellp() > 0)
               {
                    mTarget->logMessage(mCache.str(), mLevel, mMaskDebug);
               }
        }

        std::locale getloc() const
        {	// get locale
            return std::cout.getloc();
        }

        std::locale imbue(const std::locale& _Loc)
        {	// set locale to argument
//            std::locale _Oldlocale = std::ios_base::imbue(_Loc);
//            if (rdbuf() != 0)
//                rdbuf()->pubimbue(_Loc);
//            return (_Oldlocale);
            return getloc();
        }

        /** $(fclass), operator <<:
         *  Detailed description.
         *  @param v TODO
         * @return TODO
         */
        template <typename T>
        Stream& operator<< (const T& v)                      {
            mCache << v;
            return *this;
        }
        /** $(fclass), operator <<:
         *  Detailed description.
         *  @param v TODO
         * @return TODO
         */
        Stream& operator<< (const Flush& v){
            (void)v;
            mTarget->logMessage(mCache.str(), mLevel, mMaskDebug);
            mCache.str("");
            return *this;
        }
    };
};

/** @} */
/** @} */
}

//#include "HUMBUGLIBHeaderSuffix.h"

#endif // ifndef __Log_H__
