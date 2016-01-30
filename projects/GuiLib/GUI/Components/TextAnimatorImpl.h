/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TextAnimatorImpl.h class.
 * \file       TextAnimatorImpl.h
 * \date       2016-01-22
 * \author     Jedzia.
 *
 * modified    2016-01-22, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "Canvas.h"
#include "CanvasRendererImpl.h"
#include "Text.h"
#include "TextAnimator.h"
#include "Timing.h"
#include <boost/numeric/ublas/vector.hpp>

namespace gui {
namespace components {
#define DEBUGPRINT 1

/** @class EasingOperator:
 *  Detailed description.
 *  @param in TODO
 *  @return TODO
 */
class EasingOperator {
    vdouble m_alpha;

public:

    static const TimeEasingFunc& Func(void);
    static EasingOperator& Instance(void);
    explicit EasingOperator(const vdouble alpha = static_cast<vdouble>(2.0f));
    ~EasingOperator();

    vdouble operator()(vdouble in);
};

class EaseNone {
public:

    explicit EaseNone(const vdouble alpha = static_cast<vdouble>(1.0f)) { };

    vdouble operator()(vdouble t) const
    {
        return t;
    }
};

class EaseOutQuad {
public:

    explicit EaseOutQuad(const vdouble alpha = static_cast<vdouble>(1.0f)) { };

    vdouble operator()(vdouble t) const
    {
        return -t*(t - 2);
    }
};

class EaseInQuad {
public:

    explicit EaseInQuad(const vdouble alpha = static_cast<vdouble>(1.0f)) { };

    vdouble operator()(vdouble t) const
    {
        return t*t;
    }
};

class EaseInOutQuad {
public:

    explicit EaseInOutQuad(const vdouble alpha = static_cast<vdouble>(1.0f)) { };

    vdouble operator()(vdouble t)
    {
        t *= vdouble(2.0);
        if (t < 1) {
            return t*t / vdouble(2);
        }
        else {
            --t;
            return vdouble(-0.5) * (t*(t - 2) - 1);
        }
    }
};

class EaseOutInQuad {
    EaseInQuad easeInQuad;
    EaseOutQuad easeOutQuad;
public:

    explicit EaseOutInQuad(const vdouble alpha = static_cast<vdouble>(1.0f)) { };

    vdouble operator()(vdouble t) const
    {
        if (t < vdouble(0.5)) return easeOutQuad(t * 2) / 2;
        return easeInQuad((2 * t) - 1) / 2 + vdouble(0.5);
    }
};

static vdouble easeInElastic_helper(vdouble t, vdouble b, vdouble c, vdouble d, vdouble a, vdouble p)
{
    if (t == 0) return b;
    vdouble t_adj = static_cast<vdouble>(t) / static_cast<vdouble>(d);
    if (t_adj == 1) return b + c;

    vdouble s;
    if (a < fabs(c)) {
        a = c;
        s = p / 4.0f;
    }
    else {
        s = p / (2 * static_cast<vdouble>(M_PI))* std::asin(c / a);
    }

    t_adj -= 1.0f;
    return -(a*std::pow(2.0f, 10 * t_adj) * std::sin((t_adj*d - s)*(2 * static_cast<vdouble>(M_PI)) / p)) + b;
}


static vdouble easeOutElastic_helper(vdouble t, vdouble /*b*/, vdouble c, vdouble /*d*/, vdouble a, vdouble p)
{
    if (t == 0) return 0;
    if (t == 1) return c;

    vdouble s;
    if (a < c) {
        a = c;
        s = p / 4.0f;
    }
    else {
        s = p / (2 * static_cast<vdouble>(M_PI)) * std::asin(c / a);
    }

    return (a* std::pow(2.0f, -10 * t) * std::sin((t - s)*(2 * static_cast<vdouble>(M_PI)) / p) + c);
}

/**
* Easing equation function for an elastic (exponentially decaying sine wave) easing in/out: acceleration until halfway, then deceleration.
*
* @param t		Current time (in frames or seconds).
* @param a		Amplitude.
* @param p		Period.
* @return		The correct value.
*/
static vdouble easeInOutElastic(vdouble t, vdouble a, vdouble p)
{
    if (t == 0) return 0.0;
    t *= 2.0;
    if (t == 2) return 1.0;

    vdouble s;
    if (a < 1.0) {
        a = 1.0;
        s = p / 4.0f;
    }
    else {
        s = p / (2 * static_cast<vdouble>(M_PI)) * std::asin(static_cast<vdouble>(1.0) / a);
    }

    if (t < 1) return vdouble(-.5)*(a*std::pow(2.0f, 10 * (t - 1)) * std::sin((t - 1 - s)*(2 * vdouble(M_PI)) / p));
    return a*std::pow(vdouble(2.0f), -10 * (t - 1)) * std::sin((t - 1 - s)*(2 * vdouble(M_PI)) / p)*vdouble(.5) + vdouble(1.0);
}

class EaseInOutElastic {
    vdouble m_amplitude;
    vdouble m_period;
public:

    explicit EaseInOutElastic(const vdouble amplitude = static_cast<vdouble>(1.0f), const vdouble period = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude), m_period(period)
    { };

    vdouble operator()(vdouble t) const
    {
        return easeInOutElastic(t, m_amplitude, m_period);
    }
};

/**
* Easing equation function for an elastic (exponentially decaying sine wave) easing out/in: deceleration until halfway, then acceleration.
*
* @param t		Current time (in frames or seconds).
* @param a		Amplitude.
* @param p		Period.
* @return		The correct value.
*/
static vdouble easeOutInElastic(vdouble t, vdouble a, vdouble p)
{
    if (t < 0.5) return easeOutElastic_helper(t * 2, 0, 0.5, 1.0, a, p);
    return easeInElastic_helper(2 * t - vdouble(1.0), vdouble(0.5), vdouble(0.5), vdouble(1.0), a, p);
}

class EaseOutInElastic {
    vdouble m_amplitude;
    vdouble m_period;
public:

    explicit EaseOutInElastic(const vdouble amplitude = static_cast<vdouble>(1.0f), const vdouble period = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude), m_period(period)
    { };

    vdouble operator()(vdouble t) const
    {
        return easeOutInElastic(t, m_amplitude, m_period);
    }
};

static vdouble easeOutBounce_helper(vdouble t, vdouble c, vdouble a)
{
    if (t == 1.0) return c;
    const vdouble x1(7.5625);
    const vdouble div1(11.0);
    if (t < (4 / div1)) {
        return c*(x1*t*t);
    }
    else if (t < (8 / div1)) {
        t -= (6 / div1);
        return -a * (vdouble(1.) - (x1*t*t + vdouble(.75))) + c;
    }
    else if (t < (10 / div1)) {
        t -= (9 / div1);
        return -a * (vdouble(1.) - (x1*t*t + vdouble(.9375))) + c;
    }
    else {
        t -= (21 / vdouble(22.0));
        return -a * (vdouble(1.) - (x1*t*t + vdouble(.984375))) + c;
    }
}

/**
* Easing equation function for a bounce (exponentially decaying parabolic bounce) easing out: decelerating from zero velocity.
*
* @param t		Current time (in frames or seconds).
* @param a		Amplitude.
* @return		The correct value.
*/
static vdouble easeOutBounce(vdouble t, vdouble a)
{
    return easeOutBounce_helper(t, 1, a);
}

/**
* Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in: accelerating from zero velocity.
*
* @param t		Current time (in frames or seconds).
* @param a		Amplitude.
* @return		The correct value.
*/
static vdouble easeInBounce(vdouble t, vdouble a)
{
    const vdouble c(1.0);
    return c - easeOutBounce_helper(c - t, c, a);
    }


    /**
    * Easing equation function for a bounce (exponentially decaying parabolic bounce) easing in/out: acceleration until halfway, then deceleration.
    *
    * @param t		Current time (in frames or seconds).
    * @param a		Amplitude.
    * @return		The correct value.
    */
static vdouble easeInOutBounce(vdouble t, vdouble a)
{
    const vdouble x(0.5);
    const vdouble x1(1.0);
    if (t < x) return easeInBounce(2 * t, a) / 2;
    else return (t == x1) ? x1 : easeOutBounce(2 * t - 1, a) / 2 + x;
    }

    class EaseInOutBounce {
    vdouble m_amplitude;
public:

    explicit EaseInOutBounce(const vdouble amplitude = static_cast<vdouble>(1.0f)) : m_amplitude(amplitude)
    { };

    vdouble operator()(vdouble t) const
    {
        return easeInOutBounce(t, m_amplitude);
    }
};



/** @class TextMover:
 *  Implementation of a TextAnimator that can move a CText with specified speed to a specified
 * CPoint.
 */
class TextMover : public TextAnimator {
    vector2d origin;
    vector2d destination;
    vdouble speed;
    Hookable* hookable;
    Timing timingStart;
    Timing timingEnd;
    float timeIn;
    float timeOut;
    vdouble fulldistance;
    bool hasFirstRun;
    bool destinationReached;
    vector2d current;
    //vector2d delta;
    vector2d lastPos;
    TimeEasingFunc m_easingFunc;

    vdouble Easing(vdouble timeTraveledRatio);

public:

    /// <summary>
    /// Initializes a new instance of the <see cref="TextMover"/> class.
    /// </summary>
    /// <param name="destination">The destination point.</param>
    /// <param name="speed">The movement speed.</param>
    /// <param name="hookable">The hosting hookable or NULL. This is essentially important for
    // timing.</param>
    explicit TextMover(const CPoint& destination, Hookable* hookable, float speed, float timeIn, float timeOut, const TimeEasingFunc& easingFunc = NULL);

    /** Calculates the normalized direction.
     *  Calculate the unity direction vector between two points.
     *  @param vA First point.
     *  @param vB Second point.
     *  @param speed Multiplication factor of the result vector.
     *  @return  vA - vB / sqrt(length of  vA - vB) * speed.
     */
    static vector2d normalizedDirection(const vector2d& vA, const vector2d& vB, vdouble speed);

    /** Calculates the direction.
     *  Calculate the direction vector between two points.
     *  @param vA First point.
     *  @param vB Second point.
     *  @param speed Multiplication factor of the result vector.
     *  @return ( vA - vB ) / speed / 8.
     */
    static vector2d direction(const vector2d& vA, const vector2d& vB, const vdouble speed);

    /** Compares two vectors with tolerance for equality.
     *  Determines whether two vectors are the same, with a tolerance value to specify the accuracy
     * of the comparison.
     *  @param a First comparision vector.
     *  @param b Second comparision vector.
     *  @param tolerance The margin (+/- tolerance) to accept when comparing for equality.
     *  @return \b true if equal or \b false if not.
     */

    static bool CompareWithTolerance(const vector2d& a, const vector2d& b, const vdouble tolerance);

    /** Loop functor, runs in the CText animator queue.
     *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate
     * CText objects.
     *  @param target The target canvas to paint on.
     *  @param text The CText object to modify.
     *  @param mdata Parameters for all TextAnimator's in the transformation loop.
     */
    void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) override;

    // ()
};

/** @class Mover2:
 *  Old test implementation. Use TextMover.
 */
class Mover2 : public TextAnimator {
    CPoint destination;
    Hookable* hookable;
    Timing timingStart;
    Timing timingEnd;

public:

    explicit Mover2(const CPoint& destination, Hookable* hookable);

    static vector2d normalizedDirection(
            const vector2d& vA,
            const vector2d& vB, vdouble speed);

    /** Loop functor, runs in the CText animator queue.
     *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate
     * CText objects.
     *  @param target The target canvas to paint on.
     *  @param text The CText object to modify.
     *  @param mdata Parameters for all TextAnimator's in the transformation loop.
     */
    void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) override;

    // ()
};

/** @class WaitingAnimator:
 *  Waits for a specified time before calling the child TextAnimator.
 */
class WaitingAnimator : public TextAnimator {
    Timing::seconds waitTime;
    Hookable* hookable;
    Timing timingStart;

public:

    /// <summary>
    /// Initializes a new instance of the <see cref="WaitingAnimator"/> class.
    /// </summary>
    /// <param name="hookable">The hookable.</param>
    /// <param name="waitTime">The waiting time.</param>
    explicit WaitingAnimator(Hookable* hookable, Timing::seconds waitTime)
        : waitTime(waitTime), hookable(hookable), timingStart(GetTimeUpdateFunction(hookable)){}

    /** Loop functor, runs in the CText animator queue.
     *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate
     * CText objects.
     *  @param target The target canvas to paint on.
     *  @param text The CText object to modify.
     *  @param mdata Parameters for all TextAnimator's in the transformation loop.
     */
    void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) override {
        if(timingStart.IsAtOrAfter(waitTime)) {
            mdata.state++;
            mdata.markedForDeletion = true;
        }
    } // ()

    // ()
};

/** @class FadeInOutAnimator:
 *  Old test implementation. Use TextMover.
 */
class FadeInOutAnimator : public TextAnimator,
                                 FadeInOutRenderer {
public:

    /// <summary>
    /// Initializes a new instance of the <see cref="FadeInOutAnimator"/> class.
    /// </summary>
    /// <param name="hookable">The hookable.</param>
    /// <param name="fadeInOutTime">The fade in time, or fade out time in FadeMode::FadeOut.</param>
    /// <param name="fadeMode">The fade mode. Only FadeMode::FadeIn and FadeMode::FadeOut are
    // implemented.</param>
    /// <param name="stayTime">The stay time. not implemented.</param>
    /// <param name="fadeOutTime">The fade out time. not implemented.</param>
    explicit FadeInOutAnimator(Hookable* hookable, Timing::seconds fadeInOutTime, FadeMode fadeMode = FadeMode::FadeIn,
            bool fadeOutRemovesText = false,
            Timing::seconds stayTime = 1.0f, Timing::seconds fadeOutTime = 1.0f);

    /** Loop functor, runs in the CText animator queue.
     *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate
     * CText objects.
     *  @param target The target canvas to paint on.
     *  @param text The CText object to modify.
     *  @param mdata Parameters for all TextAnimator's in the transformation loop.
     */
    void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) override;
};

///** @class Mover:
//*  Detailed description.
//*  @param vA TODO
//*  @param vB TODO
//*  @return TODO
//*/
//class Mover {
//    CPoint destination;
//    double x;
//    double y;
//
//public:
//
//    explicit Mover(const CPoint& destination)
//        : destination{ destination }, x(0), y(0)
//    {}
//    boost::numeric::ublas::vector<double> normalizedDirection(
//        const boost::numeric::ublas::vector<double>& vA,
//        const boost::numeric::ublas::vector<double>& vB) {
//
//        //boost::numeric::ublas::vector<double> vdir = vA - vB;
//        auto vdir = vA - vB;
//        return (vdir) / norm_2(vdir) * 2.0;
//    }
//    void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) {
//        auto color = CColor::DarkGray();
//        target->RenderFillRect(CRectangle(90, 90, 33, 33), &color);
//        //mdata.dest.X()+=x;
//        //x++;
//        /*if (x == 0 && y == 0)
//        {
//        x = mdata.dest.GetX();
//        y = mdata.dest.GetY();
//        }*/
//
//        float r = 564.345f;
//        using namespace boost::math::double_constants;
//        auto xxx = pi * r * r;
//
//        using namespace boost::numeric::ublas;
//        //vector<double> v(3);
//        //for (unsigned i = 0; i < v.size(); ++i)
//        //   v(i) = i;
//
//        unit_vector<double> vUnit(3);
//        vector<double> vA(3);
//        vA[0] = destination.GetX();
//        vA[1] = destination.GetY();
//
//        vector<double> vB(3);
//        vB[0] = mdata.dest.GetX();
//        vB[1] = mdata.dest.GetY();
//
//        //auto vx = vpos + vdest;
//        //auto v2x = inner_prod(vpos, vdest);
//        //vector<double> vdir = vA - vB;
//        //double len1 = norm_2(vdir);
//        //vector<double> delta = vdir / len1;
//
//        vector<double> delta = normalizedDirection(vA, vB);
//        //vector<double> delta = normalizedDirection(vB, vA);
//
//        //vector<double> vdir2 = vpos - vdest;
//        //unit_<double> unit(2, 1);
//        //vdir2 * unit;
//        //std::ostringstream outstring1;
//        //outstring1 << "delta: " << delta << std::endl;
//
//        /* mapped_vector<double> vmap = unit_vector<double>(2, 1);
//        //vector<double> t = norm(vdir);
//        //boost::numeric::ublas::vector3 lookat;
//        using namespace gmtl;
//        Vec<double, 2> gvecA(100, 200);
//        Vec<double, 2> gvecB(300, 500);
//
//        Vec<double, 2> gresult = gvecA - gvecB;
//        double len2 = length(gresult);
//        std::ostringstream outstring2;
//        outstring2 << "gresult: " << gresult << std::endl;
//        gmtl::normalize(gresult);
//        std::ostringstream outstring3;
//        outstring3 << "norm: " << gresult << std::endl;*/
//
//        //gob::GVector2d vec;
//        //int cx = round(x);
//        //int cy = round(y);
//        int cx = x;
//        int cy = y;
//
//        if (mdata.dest.GetX() + cx <= destination.GetX() - delta[0]) {
//            x += delta[0];
//        }
//        else if (mdata.dest.GetX() + cx >= destination.GetX() + delta[0]) {
//            x -= delta[0];
//        }
//
//        if (mdata.dest.GetY() - cy <= destination.GetY() + delta[1]) {
//            y += delta[1];
//        }
//        else if (mdata.dest.GetY() - cy >= destination.GetY() - delta[1]) {
//            y -= delta[1];
//        }
//
//        mdata.dest.X() += ceil(x);
//        mdata.dest.Y() -= ceil(y);
//    } // ()
//};
}
}
