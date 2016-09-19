/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CanvasRendererImpl.cpp class.
 * \file       CanvasRendererImpl.cpp
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../stdafx.h"
//
#include "../Visual/Hookable.h"
#include "CanvasRendererImpl.h"
//
#include <boost/foreach.hpp>
//
//#include <build/cmake/include/debug.h>

gui::Timing::UpdateTimeFunc gui::components::FadeInOutRenderer::GetTimeUpdateFunction(const Hookable* hookable) {
    if(!hookable) {
        return NULL;
    }

    return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
}

gui::components::FadeInOutRenderer::FadeInOutRenderer(Hookable* hookable,
        Timing::seconds fadeInOutTime,
        FadeMode fadeMode,
        bool fadeOutRemovesText,
        Timing::seconds stayTime,
        Timing::seconds fadeOutTime) : fadeInOutTime(fadeInOutTime), fadeMode(fadeMode), fadeOutRemovesText(fadeOutRemovesText), stayTime(
            stayTime),
    fadeOutTime(fadeOutTime), hookable(hookable), tifadeInOut(GetTimeUpdateFunction(hookable)), timingEnd(GetTimeUpdateFunction(hookable)) {
    fadeDelta = 255.0f / Timing::FRAMESPERSECOND / fadeInOutTime;
}

void gui::components::FadeInOutRenderer::operator()(const CCanvas* target, CCanvas* source, CCanvasRenderModifierData& mdata) {
    // recording: punch in, punch out

    int alpha = 0;

    switch(fadeMode)
    {
    case FadeMode::FadeIn:
        alpha = static_cast<int>(round(tifadeInOut.TicksSinceStart() * fadeDelta));
        if(alpha > 255) {
            alpha = 255;
        }

        break;
    case FadeMode::FadeOut:
        alpha = static_cast<int>(round(255 - tifadeInOut.TicksSinceStart() * fadeDelta));
        if(alpha < 0) {
            alpha = 0;
        }

        break;
    case FadeMode::FadeInOut:
        break;
    default:
        throw std::runtime_error("Illegal fade mode.");
    } // switch

    source->SetTextureAlphaMod(alpha);

    if(tifadeInOut.IsAtOrAfter(fadeInOutTime)) {
        mdata.state++;
        mdata.markedForDeletion = true;
        if(fadeMode == FadeMode::FadeOut && fadeOutRemovesText) {
            //source->Dispose();
        }
    }
} // ()
