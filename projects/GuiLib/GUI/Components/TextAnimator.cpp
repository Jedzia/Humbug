/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TextAnimator.cpp class.
 * \file       TextAnimator.cpp
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
//
#include "TextAnimator.h"
//
#include "../Visual/Hookable.h"
#include "TextAnimatorImpl.h"

namespace gui {
namespace components {
Timing::UpdateTimeFunc TextAnimator::GetTimeUpdateFunction(const Hookable* hookable) {
    if(!hookable) {
        return NULL;
    }

    return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
}

TextAnimator * TextAnimator::Wait(Hookable* hookable, Timing::seconds waitTime) {
    auto mover = new WaitingAnimator(hookable, waitTime);
    nextAnimator = mover;
    return mover;
}

TextAnimator * TextAnimator::MoveTo(CPoint c_point, Hookable* hookable, float speed, float timeIn, float timeOut, const TimeEasingFunc& easingFunc) {
    //TextMover mover(c_point, hookable);
    auto mover = new TextMover(c_point, hookable, speed, timeIn, timeOut, easingFunc);
    nextAnimator = mover;
    return mover;
}

TextAnimator * TextAnimator::FadeIn(Hookable* hookable, Timing::seconds fadeInTime) {
    auto mover = new FadeInOutAnimator(hookable, fadeInTime);
    nextAnimator = mover;
    return mover;
}

TextAnimator * TextAnimator::FadeOut(Hookable* hookable, Timing::seconds fadeOutTime, bool fadeOutRemovesText) {
    auto mover = new FadeInOutAnimator(hookable, fadeOutTime, FadeInOutRenderer::FadeMode::FadeOut, fadeOutRemovesText);
    nextAnimator = mover;
    return mover;
}
}   // namespace components
} // namespace gui
