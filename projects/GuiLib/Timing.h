/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Timing.h class.
 * \file       Timing.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "../Visual/Hookable.h"
#include <boost/function.hpp>

/** @class Timing:
 *  Detailed description.
 *
 */
class Timing {
public:

    typedef float seconds;
    typedef boost::function<int (void)> UpdateTimeFunc;
    typedef boost::function<void (void)> ConditionalTimeFunc;
    typedef boost::function<bool (seconds time, ConditionalTimeFunc func)> UnaryTimeCheckFunc;

private:

    UpdateTimeFunc m_fncUpdateTime;
    int m_iTicks;
    int m_iStartTicks;
    UnaryTimeCheckFunc m_fncLastCheck;
    seconds m_timeLastCheck;

    /** Brief description of Timing, UpdateTimeFunction
     *  Detailed description.
     *
     */
    void UpdateTimeFunction() {
        if(!m_fncUpdateTime) {
            return;
        }

        UpdateIdle(m_fncUpdateTime());
    }

    /** Brief description of Timing, nullfunc
     *  Detailed description.
     *
     */
    static void nullfunc() { }

    /** Brief description of Timing, GetTimeUpdateFunction
     *  Detailed description.
     *  @param hookable TODO
     *  @return TODO
     */
    static UpdateTimeFunc GetTimeUpdateFunction(const gui::Hookable* hookable) {
        if(!hookable) {
            return NULL;
        }

        return boost::bind(&gui::Hookable::GetTicks, boost::ref(*hookable));
    }

public:

    static const int FRAMESPERSECOND = 30;

    explicit Timing(UpdateTimeFunc updateFunction = NULL)
        : Timing(0, updateFunction) {}

    explicit Timing(gui::Hookable* updater)
        : Timing(0, GetTimeUpdateFunction(updater)) {}

    explicit Timing(int startupTicks, UpdateTimeFunc updateFunction = NULL)
        : m_fncUpdateTime(updateFunction), m_iTicks(0), m_iStartTicks(startupTicks), m_fncLastCheck(NULL), m_timeLastCheck(0) {}

    explicit Timing(int startupTicks, gui::Hookable* updater)
        : m_fncUpdateTime(GetTimeUpdateFunction(updater)), m_iTicks(0), m_iStartTicks(startupTicks), m_fncLastCheck(NULL),
        m_timeLastCheck(0) {}

    /** Brief description of Timing, Convert
     *  Detailed description.
     *  @param ticks TODO
     *  @return TODO
     */
    static seconds Convert(int ticks) {
        seconds result = static_cast<seconds>(ticks) / static_cast<seconds>(FRAMESPERSECOND);
        return result;
    }

    /** Brief description of Timing, Reset
     *  Detailed description.
     *  @param ticks TODO
     */
    void Reset(int ticks = 0) {
        m_iStartTicks = ticks;
    }

    /** Brief description of Timing, UpdateIdle
     *  Detailed description.
     *  @param ticks TODO
     */
    void UpdateIdle(int ticks) {
        if(!m_iStartTicks) {
            m_iStartTicks = ticks;
        }

        m_iTicks = ticks;
    }

    /** Brief description of Timing, TicksSinceStart
     *  Detailed description.
     *  @return TODO
     */
    int TicksSinceStart() {
        UpdateTimeFunction();
        return m_iTicks - m_iStartTicks;
    }

    /** Brief description of Timing, SecondsSinceStart
     *  Detailed description.
     *  @return TODO
     */
    seconds SecondsSinceStart() {
        return Convert(TicksSinceStart());
    }

    /** Brief description of Timing, IsBefore
     *  Detailed description.
     *  @param time TODO
     *  @return TODO
     */
    bool IsBefore(seconds time, ConditionalTimeFunc func = NULL) {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing::IsBefore, boost::ref(*this), _1, _2);
        seconds now = SecondsSinceStart();
        bool result = now < time;
        if(result && func) {
            func();
        }

        return result;
    }

    /** Brief description of Timing, IsAfter
     *  Detailed description.
     *  @param time TODO
     *  @return TODO
     */
    bool IsAfter(seconds time, ConditionalTimeFunc func = NULL) {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing::IsAfter, boost::ref(*this), _1, _2);
        seconds now = SecondsSinceStart();
        bool result = now > time;
        if(result && func) {
            func();
        }

        return result;
    }

    /** Brief description of Timing, IsAt
     *  Detailed description.
     *  @param time TODO
     *  @return TODO
     */
    bool IsAt(seconds time, ConditionalTimeFunc func = NULL) {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing::IsAt, boost::ref(*this), _1, _2);
        seconds now = SecondsSinceStart();
        bool result = now == time;
        if(result && func) {
            func();
        }

        return result;
    }

    /** Brief description of Timing, IsAtOrAfter
     *  Detailed description.
     *  @param time TODO
     *  @param func TODO
     *  @return TODO
     */
    bool IsAtOrAfter(seconds time, ConditionalTimeFunc func = NULL) {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing::IsAtOrAfter, boost::ref(*this), _1, _2);
        seconds now = SecondsSinceStart();
        bool result = now >= time;
        if(result && func) {
            func();
        }

        return result;
    }

    operator bool() const
    {
        bool result = m_fncLastCheck(m_timeLastCheck, NULL);
        return result;
    }
};
