/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the CanvasRendererImpl.h class.
 * \file       CanvasRendererImpl.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "Canvas.h"
#include "Timing.h"

namespace gui {
class Hookable;
namespace components {
/** @class FadeInOutRenderer:
 *  test implementation. create base class ... BaseCanvasRenderer?
 */
class FadeInOutRenderer /*: public TextAnimator*/ {
public:

    enum class FadeMode {
        FadeIn,
        FadeOut,
        FadeInOut
    };

    /** Install timing function of the Hookable.
     *  Get the Timing::UpdateTimeFunc functor of the specified Hookable object.
     *  @param hookable The object with the timing function or NULL when not specified.
     *  @return the functor or NULL if no Hookable was specified.
     */
    static Timing::UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable);

    /// <summary>
    /// Initializes a new instance of the <see cref="FadeInOutRenderer"/> class.
    /// </summary>
    /// <param name="hookable">The hookable.</param>
    /// <param name="fadeInOutTime">The fade in time, or fade out time in FadeMode::FadeOut.</param>
    /// <param name="fadeMode">The fade mode. Only FadeMode::FadeIn and FadeMode::FadeOut are
    // implemented.</param>
    /// <param name="stayTime">The stay time. not implemented.</param>
    /// <param name="fadeOutTime">The fade out time. not implemented.</param>
    explicit FadeInOutRenderer(Hookable* hookable, Timing::seconds fadeInOutTime, FadeMode fadeMode = FadeMode::FadeIn,
            bool fadeOutRemovesRenderer = false, Timing::seconds stayTime = 1.0f, Timing::seconds fadeOutTime = 1.0f);

    /** Loop functor, runs in the CCanvas renderer queue.
     *  Functor implementation of the CCanvas::CCanvasRenderer that is used to modify or animate
     *  CCanvas objects.
     *  @param target The target canvas to paint on.
     *  @param source The CCanvas object to modify.
     *  @param mdata Parameters for all Renderers in the transformation loop.
     */
    void operator()(const CCanvas* target, CCanvas* source, CCanvasRenderModifierData& mdata);

private:

    Timing::seconds fadeInOutTime;
    FadeMode fadeMode;
    bool fadeOutRemovesText;
    Timing::seconds stayTime;
    Timing::seconds fadeOutTime;
    float fadeDelta;
    Hookable* hookable;
    Timing tifadeInOut;
    Timing timingEnd;
};
} // namespace components
} // namespace gui
