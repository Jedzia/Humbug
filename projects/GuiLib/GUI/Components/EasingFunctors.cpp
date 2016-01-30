/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TextAnimatorImpl.cpp class.
 * \file       TextAnimatorImpl.cpp
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
//
#include "EasingFunctors.h"
//

namespace gui {
namespace components {

vdouble EaseOutQuad::operator()(vdouble t) const {
    return -t * (t - 2);
}

vdouble EaseInQuad::operator()(vdouble t) const {
    return t * t;
}

vdouble EaseInOutQuad::operator()(vdouble t) const {
    t *= vdouble(2.0);
    if(t < 1) {
        return t * t / vdouble(2);
    }
    else {
        --t;
        return vdouble(-0.5) * (t * (t - 2) - 1);
    }
}

vdouble EaseOutInQuad::operator()(vdouble t) const {
    if(t < vdouble(0.5)) { return easeOutQuad(t * 2) / 2; }

    return easeInQuad((2 * t) - 1) / 2 + vdouble(0.5);
}

static vdouble easeInElastic_helper(vdouble t, vdouble b, vdouble c, vdouble d, vdouble a, vdouble p) {
    if(t == 0) { return b; }

    vdouble t_adj = static_cast<vdouble>(t) / static_cast<vdouble>(d);
    if(t_adj == 1) { return b + c; }

    vdouble s;
    if(a < fabs(c)) {
        a = c;
        s = p / 4.0f;
    }
    else {
        s = p / (2 * static_cast<vdouble>(M_PI)) * std::asin(c / a);
    }

    t_adj -= 1.0f;
    return -(a * std::pow(2.0f, 10 * t_adj) * std::sin((t_adj * d - s) * (2 * static_cast<vdouble>(M_PI)) / p)) + b;
} // easeInElastic_helper

static vdouble easeOutElastic_helper(vdouble t, vdouble /*b*/, vdouble c, vdouble /*d*/, vdouble a, vdouble p) {
    if(t == 0) { return 0; }

    if(t == 1) { return c; }

    vdouble s;
    if(a < c) {
        a = c;
        s = p / 4.0f;
    }
    else {
        s = p / (2 * static_cast<vdouble>(M_PI)) * std::asin(c / a);
    }

    return (a * std::pow(2.0f, -10 * t) * std::sin((t - s) * (2 * static_cast<vdouble>(M_PI)) / p) + c);
}

/**
 * Easing equation function for an elastic (exponentially decaying sine wave) easing in/out:
 *acceleration until halfway, then deceleration.
 *
 * @param t             Current time (in frames or seconds).
 * @param a             Amplitude.
 * @param p             Period.
 * @return              The correct value.
 */
static vdouble easeInOutElastic(vdouble t, vdouble a, vdouble p) {
    if(t == 0) { return 0.0; }

    t *= 2.0;
    if(t == 2) { return 1.0; }

    vdouble s;
    if(a < 1.0) {
        a = 1.0;
        s = p / 4.0f;
    }
    else {
        s = p / (2 * static_cast<vdouble>(M_PI)) * std::asin(static_cast<vdouble>(1.0) / a);
    }

    if(t < 1) { return vdouble(-.5) * (a * std::pow(2.0f, 10 * (t - 1)) * std::sin((t - 1 - s) * (2 * vdouble(M_PI)) / p)); }

    return a * std::pow(vdouble(2.0f), -10 * (t - 1)) * std::sin((t - 1 - s) * (2 * vdouble(M_PI)) / p) * vdouble(.5) + vdouble(1.0);
} // easeInOutElastic

/**
 * Easing equation function for an elastic (exponentially decaying sine wave) easing out/in:
 *deceleration until halfway, then acceleration.
 *
 * @param t             Current time (in frames or seconds).
 * @param a             Amplitude.
 * @param p             Period.
 * @return              The correct value.
 */
static vdouble easeOutInElastic(vdouble t, vdouble a, vdouble p) {
    if(t < 0.5) { return easeOutElastic_helper(t * 2, 0, 0.5, 1.0, a, p); }

    return easeInElastic_helper(2 * t - vdouble(1.0), vdouble(0.5), vdouble(0.5), vdouble(1.0), a, p);
}

vdouble EaseInOutElastic::operator()(vdouble t) const {
    return easeInOutElastic(t, m_amplitude, m_period);
}

vdouble EaseOutInElastic::operator()(vdouble t) const {
    return easeOutInElastic(t, m_amplitude, m_period);
}

static vdouble easeOutBounce_helper(vdouble t, vdouble c, vdouble a) {
    if(t == 1.0) { return c; }

    const vdouble x1(7.5625);
    const vdouble div1(11.0);
    if(t < (4 / div1)) {
        return c * (x1 * t * t);
    }
    else if(t < (8 / div1)) {
        t -= (6 / div1);
        return -a * (vdouble(1.) - (x1 * t * t + vdouble(.75))) + c;
    }
    else if(t < (10 / div1)) {
        t -= (9 / div1);
        return -a * (vdouble(1.) - (x1 * t * t + vdouble(.9375))) + c;
    }
    else {
        t -= (21 / vdouble(22.0));
        return -a * (vdouble(1.) - (x1 * t * t + vdouble(.984375))) + c;
    }
} // easeOutBounce_helper

/**
 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing out:
 *decelerating from zero velocity.
 *
 * @param t             Current time (in frames or seconds).
 * @param a             Amplitude.
 * @return              The correct value.
 */
static vdouble easeOutBounce(vdouble t, vdouble a) {
    return easeOutBounce_helper(t, 1, a);
}

/**
 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in:
 *accelerating from zero velocity.
 *
 * @param t             Current time (in frames or seconds).
 * @param a             Amplitude.
 * @return              The correct value.
 */
static vdouble easeInBounce(vdouble t, vdouble a) {
    const vdouble c(1.0);
    return c - easeOutBounce_helper(c - t, c, a);
}

/**
 * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in/out:
 *acceleration until halfway, then deceleration.
 *
 * @param t             Current time (in frames or seconds).
 * @param a             Amplitude.
 * @return              The correct value.
 */
static vdouble easeInOutBounce(vdouble t, vdouble a) {
    const vdouble x(0.5);
    const vdouble x1(1.0);
    if(t < x) { return easeInBounce(2 * t, a) / 2; }
    else { return (t == x1) ? x1 : easeOutBounce(2 * t - 1, a) / 2 + x; }
}

vdouble EaseInOutBounce::operator()(vdouble t) const {
    return easeInOutBounce(t, m_amplitude);
}
}
}
