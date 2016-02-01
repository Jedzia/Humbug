/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Timing.h class.
 * \file       Timing.h
 * \date       2016-01-30
 * \author     Jedzia.
 *
 * modified    2016-01-30, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "TimingDefs.h"

namespace gui {
class Hookable;

/** @class Timing:
 *  Detailed description.
 *
 */
class Timing {
public:

    typedef seconds seconds;
    typedef UpdateTimeFunc UpdateTimeFunc;
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
    void UpdateTimeFunction();

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
    static UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable);

public:

    static const int FRAMESPERSECOND = gui::FRAMESPERSECOND;

    explicit Timing(UpdateTimeFunc updateFunction = NULL);
    explicit Timing(Hookable* updater);
    explicit Timing(int startupTicks, UpdateTimeFunc updateFunction = NULL);
    explicit Timing(int startupTicks, Hookable* updater);

    /** Brief description of Timing, Convert
     *  Detailed description.
     *  @param ticks TODO
     *  @return TODO
     */
    static seconds Convert(int ticks);

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

    /** Brief description of Timing, UpdateIdle
    *  With no updateFunction or Hookable set, you have to call this manually.
    *  @param ticks TODO
    */
    void UpdateIdle() {
        m_iTicks++;
    }

    /** Brief description of Timing, TicksSinceStart
     *  Detailed description.
     *  @return TODO
     */
    int TicksSinceStart();

    /** Brief description of Timing, SecondsSinceStart
     *  Detailed description.
     *  @return TODO
     */
    seconds SecondsSinceStart();

    typedef boost::function<float(float)> TimeEasingFunc;
    float RangeMappedSinceStart(float outMin, float outMax, float inMin = 0.0f, float inMax = 1.0f,
        float outMinClamp = -std::numeric_limits<float>::max(), float outMaxClamp = std::numeric_limits<float>::max(), 
        //float outMinClamp = -1000000, float outMaxClamp = +1000000,
        TimeEasingFunc functor = 0, float foutMinClamp = 0.0f, float foutMaxClamp = 1.0f);
    // for testing
    float A, B, C;

    /** Brief description of Timing, IsBefore
     *  Detailed description.
     *  @param time TODO
     *  @return TODO
     */
    bool IsBefore(seconds time, const ConditionalTimeFunc& func = NULL);

    /** Brief description of Timing, IsAfter
    *  Detailed description.
    *  @param time TODO
    *  @return TODO
    */
    bool IsAfter(seconds time, const ConditionalTimeFunc& func = NULL);

    /** Brief description of Timing, IsAfter
    *  Detailed description.
    *  @param time TODO
    *  @return TODO
    */
    bool IsAfterAndBefore(seconds after, seconds before, const ConditionalTimeFunc& func = NULL);

    /** Brief description of Timing, IsAt
     *  Detailed description.
     *  @param time TODO
     *  @return TODO
     */
    bool IsAt(seconds time, const ConditionalTimeFunc& func = NULL);

    /** Brief description of Timing, IsAtOrAfter
     *  Detailed description.
     *  @param time TODO
     *  @param func TODO
     *  @return TODO
     */
    bool IsAtOrAfter(seconds time, const ConditionalTimeFunc& func = NULL);

    operator bool() const;
};
}
