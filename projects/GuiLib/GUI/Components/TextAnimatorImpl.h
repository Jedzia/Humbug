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
#include "TextAnimator.h"
#include "Timing.h"
#include <boost/numeric/ublas/vector.hpp>

namespace gui {
namespace components {
#define DEBUGPRINT 1
typedef float vdouble;
typedef boost::numeric::ublas::vector<double> vector2d;

/** @class TextMover:
 *  Implementation of a TextAnimator that can move a CText with specified speed to a specified
 *CPoint.
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
    bool hasFirstRun;
    bool destinationReached;
    vector2d current;
    vector2d delta;

public:

    /// <summary>
    /// Initializes a new instance of the <see cref="TextMover"/> class.
    /// </summary>
    /// <param name="destination">The destination point.</param>
    /// <param name="speed">The movement speed.</param>
    /// <param name="hookable">The hosting hookable or NULL. This is essentially important for
    // timing.</param>
    explicit TextMover(const CPoint& destination, Hookable* hookable, float speed, float timeIn, float timeOut);

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
     *of the comparison.
     *  @param a First comparision vector.
     *  @param b Second comparision vector.
     *  @param tolerance The margin (+/- tolerance) to accept when comparing for equality.
     *  @return \b true if equal or \b false if not.
     */
    static bool CompareWithTolerance(const vector2d& a, const vector2d& b, const vdouble tolerance);

    /** Loop functor, runs in the CText animator queue.
     *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate
     *CText objects.
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
            const vector2d& vB, double speed);

    /** Loop functor, runs in the CText animator queue.
     *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate
     *CText objects.
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
class FadeInAnimator : public TextAnimator {
    float fadeSpeed;
    Hookable* hookable;
    Timing timingStart;
    Timing timingEnd;

public:

    explicit FadeInAnimator(Hookable* hookable, float fadeSpeed)
        :fadeSpeed(fadeSpeed), hookable(hookable), timingStart(GetTimeUpdateFunction(
        hookable)),
        timingEnd(GetTimeUpdateFunction(hookable)) {
    }

    /** Loop functor, runs in the CText animator queue.
    *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate
    *CText objects.
    *  @param target The target canvas to paint on.
    *  @param text The CText object to modify.
    *  @param mdata Parameters for all TextAnimator's in the transformation loop.
    */
    void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) override
    {
        int i = 0;
        i++;
        if (timingStart.IsBefore(2)) {
            return;
        }



    }

    // ()
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
