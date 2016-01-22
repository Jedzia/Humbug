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
//typedef int vdouble;
/** @class TextMover:
 *  Detailed description.
 *  @param vA TODO
 *  @param vB TODO
 *  @return TODO
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

    /** Brief description of TextMover, GetTimeUpdateFunction
     *  Detailed description.
     *  @param hookable TODO
     *  @return TODO
     */
    static Timing::UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable) {
        if(!hookable) {
            return NULL;
        }

        return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
    }

public:

    explicit TextMover(const CPoint& destination, float speed, Hookable* hookable)
        : destination(destination), speed(static_cast<vdouble>(speed)), hookable(hookable), timingStart(GetTimeUpdateFunction(hookable)),
        timingEnd(GetTimeUpdateFunction(hookable)), hasFirstRun(false), destinationReached(false) {}

    ~TextMover() {}

    /** Brief description of TextMover, normalizedDirection
     *  Detailed description.
     *  @param vA TODO
     *  @param vB TODO
     *  @param speed TODO
     *  @return TODO
     */
    static vector<vdouble> normalizedDirection(const vector<vdouble>& vA, const vector<vdouble>& vB, vdouble speed) {
        auto vdir = vA - vB;
        // not rounding the unity vector length divider or dividing speed outside the norm_2() leads
        // to precision errors.
        return vdir / round(norm_2(vdir / speed));
    }

    /** Brief description of TextMover, direction
     *  Detailed description.
     *  @param vA TODO
     *  @param vB TODO
     *  @param speed TODO
     *  @return TODO
     */
    static vector<vdouble> direction(
            const vector<vdouble>& vA,
            const vector<vdouble>& vB, const vdouble speed) {
        auto vdir = vA - vB;
        return vdir / speed / static_cast<vdouble>(8.0);
    }

    /** Brief description of TextMover, CompareWithTolerance
     *  Detailed description.
     *  @param cur TODO
     *  @param des TODO
     *  @param tolerance TODO
     *  @return TODO
     */
    static bool CompareWithTolerance(const vector<vdouble>& cur, const vector<vdouble>& des, const vdouble tolerance) {
        bool xcomp = cur[0] - tolerance<des[0] && cur[0] + tolerance> des[0];
        bool ycomp = cur[1] - tolerance<des[1] && cur[1] + tolerance> des[1];
        return xcomp || ycomp;
    }

    /** Brief description of TextMover, operator ()
     *  Detailed description.
     *  @param target TODO
     *  @param text TODO
     *  @param mdata TODO
     *  @return TODO
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
}
}
