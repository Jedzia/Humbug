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
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>

namespace gui {
namespace components {
using namespace boost::numeric::ublas;

#define DEBUGPRINT 1
typedef float vdouble;

/** @class TextMover:
 *  Implementation of a TextAnimator that can move a CText with specified speed to a specified CPoint.
 */
class TextMover : public TextAnimator {
    vector<vdouble> origin;
    vector<vdouble> destination;
    vdouble speed;
    Hookable* hookable;
    Timing timingStart;
    Timing timingEnd;
    bool hasFirstRun;
    bool destinationReached;
    vector<vdouble> current;
    vector<vdouble> delta;

    /** Install timing function of the Hookable.
     *  Get the Timing::UpdateTimeFunc functor of the specified Hookable object.
     *  @param hookable The object with the timing function or NULL when not specified.
     *  @return the functor or NULL if no Hookable was specified.
     */
    static Timing::UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable) {
        if(!hookable) {
            return NULL;
        }

        return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
    }

public:

    /// <summary>
    /// Initializes a new instance of the <see cref="TextMover"/> class.
    /// </summary>
    /// <param name="destination">The destination point.</param>
    /// <param name="speed">The movement speed.</param>
    /// <param name="hookable">The hosting hookable or NULL. This is essentially important for timing.</param>
    explicit TextMover(const CPoint& destination, float speed, Hookable* hookable)
        : destination(destination), speed(static_cast<vdouble>(speed)), hookable(hookable), timingStart(GetTimeUpdateFunction(hookable)),
        timingEnd(GetTimeUpdateFunction(hookable)), hasFirstRun(false), destinationReached(false) {}

    ~TextMover() {}

    /** Calculates the normalized direction.
     *  Calculate the unity direction vector between two points.
     *  @param vA First point.
     *  @param vB Second point.
     *  @param speed Multiplication factor of the result vector.
     *  @return  vA - vB / sqrt(length of  vA - vB) * speed.
     */
    static vector<vdouble> normalizedDirection(const vector<vdouble>& vA, const vector<vdouble>& vB, vdouble speed) {
        auto vdir = vA - vB;
        // not rounding the unity vector length divider or dividing speed outside the norm_2() leads
        // to precision errors.
        return vdir / round(norm_2(vdir / speed));
    }

    /** Calculates the direction.
    *  Calculate the direction vector between two points.
    *  @param vA First point.
    *  @param vB Second point.
    *  @param speed Multiplication factor of the result vector.
    *  @return ( vA - vB ) / speed / 8.
    */
    static vector<vdouble> direction(const vector<vdouble>& vA, const vector<vdouble>& vB, const vdouble speed) {
        auto vdir = vA - vB;
        return vdir / speed / static_cast<vdouble>(8.0);
    }

    /** Compares two vectors with tolerance for equality.
     *  Determines whether two vectors are the same, with a tolerance value to specify the accuracy of the comparison.
     *  @param a First comparision vector.
     *  @param b Second comparision vector.
     *  @param tolerance The margin (+/- tolerance) to accept when comparing for equality.
     *  @return \b true if equal or \b false if not.
     */
    static bool CompareWithTolerance(const vector<vdouble>& a, const vector<vdouble>& b, const vdouble tolerance) {
        bool xcomp = a[0] - tolerance<b[0] && a[0] + tolerance> b[0];
        bool ycomp = a[1] - tolerance<b[1] && a[1] + tolerance> b[1];
        return xcomp || ycomp;
    }

    /** Loop functor, runs in the CText animator queue.
    *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate CText objects.
    *  @param target The target canvas to paint on.
    *  @param text The CText object to modify.
    *  @param mdata Parameters for all TextAnimator's in the transformation loop.
    */
    void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) override {
        using namespace boost::numeric::ublas;
        auto color = CColor::DarkGray();
        target->RenderFillRect(CRectangle(CPoint(destination), CPoint(33, 33)), &color);

        if(!hasFirstRun) {
            origin = text->GetPosition();
            current = text->GetPosition();
            delta = normalizedDirection(destination, origin, speed);
            //delta = direction(destination, origin, speed);
            hasFirstRun = true;
        }

        if(hookable) {
            int ticks = hookable->GetTicks();

            color.SetR(0xa0 | ticks % 255);
            color.SetG(0x5f & ticks % 255);
            color.SetB(ticks % 255);
            text->SetColor(color);

            if(timingStart.IsBefore(1.0f)) {
                return;
            }
        }

#if DEBUGPRINT
        std::ostringstream outstring1;
        outstring1 << "delta: " << delta << std::endl;
        CPoint textPos = CPoint(400, 80);
        CText vresText1(text->GetFont(), outstring1.str(), CColor::Black(), textPos);
        vresText1.RenderPut(target);

#endif

        if(!destinationReached) {
            current += delta;
        }

#if DEBUGPRINT
        std::ostringstream outstring2;
        outstring2 << "destination: " << destination << std::endl;
        textPos += vresText1.VerticalSpacing();
        CText vresText2(text->GetFont(), outstring2.str(), CColor::Black(), textPos);
        vresText2.RenderPut(target);

        std::ostringstream outstring3;
        outstring3 << "current: " << current << std::endl;
        textPos += vresText2.VerticalSpacing();
        CText vresText3(text->GetFont(), outstring3.str(), CColor::Black(), textPos);
        vresText3.RenderPut(target);
#endif // if DEBUGPRINT

        text->SetPosition(CPoint(current));

        const vdouble tolerance = static_cast<vdouble>(0.02);
        if(CompareWithTolerance(current, destination, tolerance)) {
            destinationReached = true;

            if(hookable && timingEnd.IsBefore(2.0f)) {
                return;
            }

            mdata.state++;
            mdata.markedForDeletion = true;
        }
    } // ()
};

/** @class Mover2:
*  Old test implementation. Use TextMover.
*/
class Mover2 : public TextAnimator {
    CPoint destination;
    Hookable* hookable;
    Timing timingStart;
    Timing timingEnd;

    static Timing::UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable) {
        if (!hookable) {
            return NULL;
        }

        return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
    }

public:

    explicit Mover2(const CPoint& destination, Hookable* hookable)
        : destination(destination), hookable(hookable), timingStart(GetTimeUpdateFunction(hookable)),
        timingEnd(GetTimeUpdateFunction(hookable)) {
    }

    ~Mover2() {
        int ix = 0;
        ix++;
    }

    static vector<double> normalizedDirection(
        const vector<double>& vA,
        const vector<double>& vB, double speed) {
        auto vdir = vA - vB;
        return (vdir) / norm_2(vdir) * speed;
    }

    /** Loop functor, runs in the CText animator queue.
    *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate CText objects.
    *  @param target The target canvas to paint on.
    *  @param text The CText object to modify.
    *  @param mdata Parameters for all TextAnimator's in the transformation loop.
    */
    void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) override {
        using namespace boost::numeric::ublas;
        auto color = CColor::DarkGray();
        target->RenderFillRect(CRectangle(90, 90, 33, 33), &color);

        const double speed = 8.0f;

        if (nextAnimator) {
            int r = 0;
            r++;
        }

        if (hookable) {
            int ticks = hookable->GetTicks();
            //timingStart.UpdateIdle(ticks);

            color.SetR(0xa0 | ticks % 255);
            color.SetG(0x5f & ticks % 255);
            color.SetB(ticks % 255);
            text->SetColor(color);

            if (timingStart.IsBefore(1.0f)) {
                mdata.dest.X() += static_cast<int>(ceil(x));
                mdata.dest.Y() -= static_cast<int>(ceil(y));
                return;
            }
        }

        //float r = 564.345f;
        //using namespace boost::math::double_constants;
        //auto xxx = pi * r * r;

        unit_vector<double> vUnit((2));
        vector<double> vA(destination);
        CPoint dest(static_cast<int>(mdata.dest.GetX() + x), static_cast<int>(mdata.dest.GetY() - y));
        vector<double> vB(dest);
        //vector<double> vB(static_cast<CPoint>(mdata.dest));
        vector<double> vresult = normalizedDirection(vA, vB, speed);

        if (mdata.dest.GetX() + x < destination.GetX() - vresult[0]) {
            x += vresult[0];
        }
        else if (mdata.dest.GetX() + x > destination.GetX() + vresult[0]) {
            x -= vresult[0];
        }

        if (mdata.dest.GetY() - y < destination.GetY() + vresult[1]) {
            y += vresult[1];
        }
        else if (mdata.dest.GetY() - y > destination.GetY() - vresult[1]) {
            y -= vresult[1];
        }

        /*CPoint actual3 = CPoint(mdata.dest.GetX() + x + 0, mdata.dest.GetY() - y - 0);
        CPoint actual2 = CPoint(mdata.dest.GetX() + x + 0, mdata.dest.GetY() - y - 1);
        CPoint actual4 = CPoint(mdata.dest.GetX() + x + 1, mdata.dest.GetY() - y - 0);
        CPoint actual = CPoint(mdata.dest.GetX() + x + 1, mdata.dest.GetY() - y - 1);*/

        const int speedInt = static_cast<int>(speed);
        bool xcomp = mdata.dest.GetX() + x - speedInt<destination.GetX() && mdata.dest.GetX() + x + speedInt> destination.GetX();
        bool ycomp = mdata.dest.GetY() - y - speedInt<destination.GetY() && mdata.dest.GetY() - y + speedInt> destination.GetY();

        if (xcomp && ycomp) {
            //if (actual == destination || actual2 == destination || actual3 == destination ||
            // actual4 == destination) {
            if (hookable) {
                /*if (!timingStart)
                {
                //timingEnd.UpdateIdle(hookable->GetTicks());
                }*/

                mdata.dest.X() += static_cast<int>(ceil(x));
                mdata.dest.Y() -= static_cast<int>(ceil(y));

                if (timingEnd.IsBefore(1.0f)) {
                    return;
                }
            }

            mdata.state++;
            mdata.markedForDeletion = true;
        }

        mdata.dest.X() += static_cast<int>(round(x));
        mdata.dest.Y() -= static_cast<int>(round(y));
    } // ()
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
