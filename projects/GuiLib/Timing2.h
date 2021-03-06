/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Timing2.h class.
 * \file       Timing2.h
 * \date       2016-01-30
 * \author     Jedzia.
 *
 * modified    2016-01-30, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "TimingDefs.h"

namespace gui {
/** @class Timing2:
 *  Lightweight timing implementation.
 *
 */
class Timing2 {
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

public:

    explicit Timing2(UpdateTimeFunc updateFunction = NULL)
        : Timing2(0, updateFunction) {}

    explicit Timing2(int startupTicks, UpdateTimeFunc updateFunction = NULL)
        : m_fncUpdateTime(updateFunction), m_iTicks(0), m_iStartTicks(startupTicks), m_fncLastCheck(NULL), m_timeLastCheck(0) {}

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
    bool IsBefore(seconds time) {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing2::IsBefore, boost::ref(*this), _1);
        seconds now = SecondsSinceStart();
        return now < time;
    }

    /** Brief description of Timing, IsAfter
     *  Detailed description.
     *  @param time TODO
     *  @return TODO
     */
    bool IsAfter(seconds time) {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing2::IsAfter, boost::ref(*this), _1);
        seconds now = SecondsSinceStart();
        return now > time;
    }

    /** Brief description of Timing, IsAt
     *  Detailed description.
     *  @param time TODO
     *  @return TODO
     */
    bool IsAt(seconds time) {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing2::IsAt, boost::ref(*this), _1);
        seconds now = SecondsSinceStart();
        return now == time;
    }

    /** Brief description of Timing2, IsAtOrAfter
     *  Detailed description.
     *  @param time TODO
     *  @return TODO
     */
    bool IsAtOrAfter(seconds time) {
        m_timeLastCheck = time;
        m_fncLastCheck = boost::bind(&Timing2::IsAtOrAfter, boost::ref(*this), _1);
        seconds now = SecondsSinceStart();
        return now >= time;
    }

    operator bool() const
    {
        bool result = m_fncLastCheck(m_timeLastCheck);
        return result;
    }
};
}
