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
#include "TextAnimatorImpl.h"
//
#include "../Visual/Hookable.h"
#include "Canvas.h"
#include "Color.h"
#include "Text.h"
#include <boost/math/constants/constants.hpp>
#include <boost/numeric/ublas/io.hpp>
#include <boost/numeric/ublas/vector_expression.hpp>
//

namespace gui {
namespace components {
using namespace boost::numeric::ublas;

Timing::UpdateTimeFunc TextMover::GetTimeUpdateFunction(const Hookable* hookable) {
    if(!hookable) {
        return NULL;
    }

    return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
}

TextMover::TextMover(const CPoint& destination, Hookable* hookable, float speed, float timeIn, float timeOut) : destination(destination),
    speed(static_cast<vdouble>(speed)), hookable(hookable), timingStart(GetTimeUpdateFunction(hookable)),
    timingEnd(GetTimeUpdateFunction(hookable)), timeIn(timeIn), timeOut(timeOut), hasFirstRun(false), destinationReached(false) {
}

vector2d TextMover::normalizedDirection(const vector2d& vA, const vector2d& vB, vdouble speed) {
    auto vdir = vA - vB;
    // not rounding the unity vector length divider or dividing speed outside the norm_2() leads
    // to precision errors.
    return vdir / round(norm_2(vdir / speed));
}

vector2d TextMover::direction(const vector2d& vA, const vector2d& vB, const vdouble speed) {
    auto vdir = vA - vB;
    return vdir / speed / static_cast<vdouble>(8.0);
}

bool TextMover::CompareWithTolerance(const vector2d& a, const vector2d& b, const vdouble tolerance) {
    bool xcomp = a[0] - tolerance<b[0] && a[0] + tolerance> b[0];
    bool ycomp = a[1] - tolerance<b[1] && a[1] + tolerance> b[1];
    return xcomp || ycomp;
}

void TextMover::operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) {
    using namespace boost::numeric::ublas;
    auto color = CColor::DarkGray();
    target->RenderFillRect(CRectangle(CPoint(destination), CPoint(33, 33)), &color);

    //text->Dispose();
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

        if(timingStart.IsBefore(timeIn)) {
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

        if(hookable && timingEnd.IsBefore(timeOut)) {
            return;
        }

        mdata.state++;
        mdata.markedForDeletion = true;
    }
} // ()

Timing::UpdateTimeFunc Mover2::GetTimeUpdateFunction(const Hookable* hookable) {
    if(!hookable) {
        return NULL;
    }

    return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
}

Mover2::Mover2(const CPoint& destination, Hookable* hookable) : destination(destination), hookable(hookable), timingStart(GetTimeUpdateFunction(
                    hookable)),
    timingEnd(GetTimeUpdateFunction(hookable)) {
}

vector2d Mover2::normalizedDirection(const vector2d& vA, const vector2d& vB, double speed) {
    auto vdir = vA - vB;
    return (vdir) / norm_2(vdir) * speed;
}

void Mover2::operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) {
    using namespace boost::numeric::ublas;
    auto color = CColor::DarkGray();
    target->RenderFillRect(CRectangle(90, 90, 33, 33), &color);

    const double speed = 8.0f;

    if(nextAnimator) {
        int r = 0;
        r++;
    }

    if(hookable) {
        int ticks = hookable->GetTicks();
        //timingStart.UpdateIdle(ticks);

        color.SetR(0xa0 | ticks % 255);
        color.SetG(0x5f & ticks % 255);
        color.SetB(ticks % 255);
        text->SetColor(color);

        if(timingStart.IsBefore(1.0f)) {
            mdata.dest.X() += static_cast<int>(ceil(x));
            mdata.dest.Y() -= static_cast<int>(ceil(y));
            return;
        }
    }

    //float r = 564.345f;
    //using namespace boost::math::double_constants;
    //auto xxx = pi * r * r;

    unit_vector<double> vUnit((2));
    vector2d vA(destination);
    CPoint dest(static_cast<int>(mdata.dest.GetX() + x), static_cast<int>(mdata.dest.GetY() - y));
    vector2d vB(dest);
    //vector2d vB(static_cast<CPoint>(mdata.dest));
    vector2d vresult = normalizedDirection(vA, vB, speed);

    if(mdata.dest.GetX() + x < destination.GetX() - vresult[0]) {
        x += vresult[0];
    }
    else if(mdata.dest.GetX() + x > destination.GetX() + vresult[0]) {
        x -= vresult[0];
    }

    if(mdata.dest.GetY() - y < destination.GetY() + vresult[1]) {
        y += vresult[1];
    }
    else if(mdata.dest.GetY() - y > destination.GetY() - vresult[1]) {
        y -= vresult[1];
    }

    /*CPoint actual3 = CPoint(mdata.dest.GetX() + x + 0, mdata.dest.GetY() - y - 0);
       CPoint actual2 = CPoint(mdata.dest.GetX() + x + 0, mdata.dest.GetY() - y - 1);
       CPoint actual4 = CPoint(mdata.dest.GetX() + x + 1, mdata.dest.GetY() - y - 0);
       CPoint actual = CPoint(mdata.dest.GetX() + x + 1, mdata.dest.GetY() - y - 1);*/

    const int speedInt = static_cast<int>(speed);
    bool xcomp = mdata.dest.GetX() + x - speedInt<destination.GetX() && mdata.dest.GetX() + x + speedInt> destination.GetX();
    bool ycomp = mdata.dest.GetY() - y - speedInt<destination.GetY() && mdata.dest.GetY() - y + speedInt> destination.GetY();

    if(xcomp && ycomp) {
        //if (actual == destination || actual2 == destination || actual3 == destination ||
        // actual4 == destination) {
        if(hookable) {
            /*if (!timingStart)
               {
               //timingEnd.UpdateIdle(hookable->GetTicks());
               }*/

            mdata.dest.X() += static_cast<int>(ceil(x));
            mdata.dest.Y() -= static_cast<int>(ceil(y));

            if(timingEnd.IsBefore(1.0f)) {
                return;
            }
        }

        mdata.state++;
        mdata.markedForDeletion = true;
    }

    mdata.dest.X() += static_cast<int>(round(x));
    mdata.dest.Y() -= static_cast<int>(round(y));
} // ()
}
}
