/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the AnimatedRectangle.h class.
 * \file       AnimatedRectangle.h
 * \date       2016-02-27
 * \author     Jedzia.
 *
 * modified    2016-02-27, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "../Timing.h"
#include <boost/bind.hpp>
#include <boost/noncopyable.hpp>

namespace gui {
/** @class AnimatedRectangle:
 *  Detailed description.
 *
 */
class AnimatedRectangle : public boost::noncopyable {
    components::CRectangle m_recStart;
    components::CRectangle m_recEnd;
    Timing m_Timing;
    vdouble m_duration;
    components::TimeEasingFunc m_easingFunc;

    static int ReNormFloat(float in)
    {
        return static_cast<int>(in);
    }

    static float ReNormInt(int in)
    {
        return static_cast<float>(in);
    }

public:

    AnimatedRectangle(const components::CRectangle& recStart,
            const components::CRectangle& recEnd,
            const Hookable* updater,
            vdouble duration,
            components::TimeEasingFunc easingfunc = NULL)
        : m_recStart{recStart}, m_recEnd{recEnd}, m_Timing(updater), m_duration(duration), m_easingFunc(easingfunc) {}

    AnimatedRectangle(const components::CRectangle& recStart,
            const components::CRectangle& recEnd,
            UpdateTimeFunc updateFunction,
            vdouble duration,
            components::TimeEasingFunc easingfunc = NULL)
        : m_recStart{recStart}, m_recEnd{recEnd}, m_Timing(updateFunction), m_duration(duration), m_easingFunc(easingfunc) {}

    /** Brief description of AnimatedRectangle, Reset
     *  Detailed description.
     *
     */
    void Reset() { m_Timing.Reset(); }

    // conversion
    components::CRectangle Rect()
    {
        float x = m_Timing.RangeMappedSinceStart(ReNormInt(m_recStart.GetX()), ReNormInt(m_recEnd.GetX()), m_duration, m_easingFunc);
        float y = m_Timing.RangeMappedSinceStart(ReNormInt(m_recStart.GetY()), ReNormInt(m_recEnd.GetY()), m_duration, m_easingFunc);
        float w = m_Timing.RangeMappedSinceStart(ReNormInt(m_recStart.GetW()), ReNormInt(m_recEnd.GetW()), m_duration, m_easingFunc);
        float h = m_Timing.RangeMappedSinceStart(ReNormInt(m_recStart.GetH()), ReNormInt(m_recEnd.GetH()), m_duration, m_easingFunc);
        return components::CRectangle(ReNormFloat(x), ReNormFloat(y), ReNormFloat(w), ReNormFloat(h));
    };

    // conversion
    operator components::CRectangle()
    {
        return Rect();
    };
};

struct AnimatedRectangleBindAdapter {

    template<class T>
    AnimatedRectangleBindAdapter(T* sprMgr)
        : fnc{boost::bind(&T::UpdateTimeFunc, boost::ref(*sprMgr))}
    {}

    operator UpdateTimeFunc() const
    {
        return fnc;
    }

private:
    UpdateTimeFunc fnc;
};
}
