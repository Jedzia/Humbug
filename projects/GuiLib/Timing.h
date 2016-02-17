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
#include "MathDefs.h"
#include "TimingDefs.h"

namespace gui {
class Hookable;

/** @class Timing:
 *  Provides timing related methods.
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

    void UpdateTimeFunction();
    static void nullfunc() { }
    static UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable);

public:

    static const int FRAMESPERSECOND = gui::FRAMESPERSECOND;

    explicit Timing(UpdateTimeFunc updateFunction = NULL);
    explicit Timing(const Hookable* updater);
    explicit Timing(int startupTicks, UpdateTimeFunc updateFunction = NULL);
    explicit Timing(int startupTicks, Hookable* updater);

    /** Convert ticks to seconds.
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

    /** Time Easing Function
     *  A functor or function that transforms the input range 0.0f to 1.0f into an output value
     *between 0.0f and 1.0f.
     */
    typedef boost::function<float (float)> TimeEasingFunc;

    /** Timing, input/output range mapper
     *  Maps the timing to the specified output range.
     *  @param now Actual input value.
     *  @param outStart The lower range of the output value.
     *  @param outEnd The upper range of the output value.
     *  @param inMin The lower range of the input value. The input value is always
     *SecondsSinceStart().
     *  @param inMax The upper range of the input value. The input value is always
     *SecondsSinceStart().
     *  @param outMinClamp Minimum clamping for the return value.
     *  @param outMaxClamp Maximum clamping for the return value.
     *  @param functor Time easing functor.
     *  @param foutMinClamp Minimum clamping for the value that should be fed into the easing
     *functor.
     *  @param foutMaxClamp Maximum clamping for the value that should be fed into the easing
     *functor.
     *  @param loop Apply std::fmod(now, inMax) looping.
     *  @return the range-mapped value of SecondsSinceStart().
     */
    static float RangeMappedSinceStart(float now, float outStart, float outEnd, float inMin = 0.0f, float inMax = 1.0f,
            float outMinClamp = -std::numeric_limits<float>::max(), float outMaxClamp = std::numeric_limits<float>::max(),
            TimeEasingFunc functor = 0, float foutMinClamp = 0.0f, float foutMaxClamp = 1.0f, bool loop = false);

    /** Timing, duration range mapper
     *  Maps a duration to the specified output range.
     *  @param now Actual input value.
     *  @param outStart The lower range of the output value.
     *  @param outEnd The upper range of the output value.
     *  @param duration The duration it should take to come from outMin to outMax.
     *  @param functor Time easing functor.
     *  @param foutMinClamp Minimum clamping for the value that should be fed into the easing
     *functor.
     *  @param foutMaxClamp Maximum clamping for the value that should be fed into the easing
     *functor.
     *  @return the range-mapped value of SecondsSinceStart().
     */
    static float RangeMappedSinceStart(float now, float outStart, float outEnd, seconds duration = 1.0f,
            TimeEasingFunc functor = 0, bool loop = false, float foutMinClamp = 0.0f, float foutMaxClamp = 1.0f);

    /** Timing, input/output range mapper
     *  Maps the timing to the specified output range.
     *  @param outStart The lower range of the output value.
     *  @param outEnd The upper range of the output value.
     *  @param inMin The lower range of the input value. The input value is always
     *SecondsSinceStart().
     *  @param inMax The upper range of the input value. The input value is always
     *SecondsSinceStart().
     *  @param outMinClamp Minimum clamping for the return value.
     *  @param outMaxClamp Maximum clamping for the return value.
     *  @param functor Time easing functor.
     *  @param foutMinClamp Minimum clamping for the value that should be fed into the easing
     *functor.
     *  @param foutMaxClamp Maximum clamping for the value that should be fed into the easing
     *functor.
     *  @param loop Apply std::fmod(now, inMax) looping.
     *  @return the range-mapped value of SecondsSinceStart().
     */
    float RangeMappedSinceStart(float outStart, float outEnd, float inMin = 0.0f, float inMax = 1.0f,
            float outMinClamp = -std::numeric_limits<float>::max(), float outMaxClamp = std::numeric_limits<float>::max(),
            TimeEasingFunc functor = 0, float foutMinClamp = 0.0f, float foutMaxClamp = 1.0f, bool loop = false);

    /** Timing, duration range mapper
     *  Maps a duration to the specified output range.
     *  @param outStart The lower range of the output value.
     *  @param outEnd The upper range of the output value.
     *  @param duration The duration it should take to come from outMin to outMax.
     *  @param functor Time easing functor.
     *  @param foutMinClamp Minimum clamping for the value that should be fed into the easing
     *functor.
     *  @param foutMaxClamp Maximum clamping for the value that should be fed into the easing
     *functor.
     *  @return the range-mapped value of SecondsSinceStart().
     */
    float RangeMappedSinceStart(float outStart, float outEnd, seconds duration = 1.0f,
            TimeEasingFunc functor = 0, bool loop = false, float foutMinClamp = 0.0f, float foutMaxClamp = 1.0f);

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

/** @class RingBounce:
 *  Ring module calculator.
 */
class RingBounce {
public:

    explicit RingBounce(const vdouble alpha = static_cast<vdouble>(1.0f)) { }

    /** Calculate the ring result.
    *  Calculates the modulo of the input value.
    *  @param t Input value
    *  @return the ring module of the input value.
    */
    vdouble operator()(vdouble t) const {
        if(t >= vdouble(0.5)) {
            return vdouble(1.0) - ((t - vdouble(0.5)) * 2);
        }
        else {
            return t * 2;
        }
    }
};

/** @class Ring:
 *  Ring module calculator.
 */
class Ring {
    const int m_iRing;

public:

    explicit Ring(const int ring = gui::FRAMESPERSECOND) : m_iRing(ring)
    { }

    explicit Ring(const seconds ringTime) : m_iRing(static_cast<int>(ringTime * FRAMESPERSECOND))
    { }

    /** Convert the ring result to seconds.
     *  @return the ring result as seconds.
     */
    seconds RingSeconds() const {
        return Timing::Convert(m_iRing);
    }

    /** Calculate the ring result.
     *  Calculates the modulo of the input value.
     *  @param in Input value
     *  @return the ring module of the input value.
     */
    int operator()(int in) const {
        int t = in % (m_iRing);
        if(t >= m_iRing / 2) {
            return m_iRing - ((t - m_iRing / 2) * 2);
        }
        else {
            return t * 2;
        }
    }

    /** Calculate the ring result as seconds.
     *  Calculates the modulo of the input value as seconds.
     *  @param in Input value
     *  @return the ring module of the input value.
     */
    seconds Timed(int in) const {
        return Timing::Convert(operator()(in));
    }

    /*seconds operator()(seconds in) const {
        int t = in % (m_iRing);
        if (t >= m_iRing / 2) {
            return  m_iRing - ((t - m_iRing / 2) * 2);
        }
        else {
            return t * 2;
        }
       }*/
};
}
