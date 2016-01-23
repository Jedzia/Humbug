/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
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

TextAnimator * TextAnimator::FlyTo(CPoint c_point, Hookable* hookable, float speed, float timeIn, float timeOut) {
    //TextMover mover(c_point, hookable);
    auto mover = new TextMover(c_point, hookable, speed, timeIn, timeOut);
    nextAnimator = mover;
    return mover;
}

TextAnimator * TextAnimator::FadeOut(Hookable* hookable, float fadespeed) {
    return NULL;
}

TextAnimator * TextAnimator::FadeIn(Hookable* hookable, float fadespeed) {
    auto mover = new FadeInAnimator(hookable, fadespeed);
    nextAnimator = mover;
    return mover;
}
}   // namespace components
} // namespace gui
