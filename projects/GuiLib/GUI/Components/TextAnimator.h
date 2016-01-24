/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TextAnimator.h class.
 * \file       TextAnimator.h
 * \date       2016-01-22
 * \author     Jedzia.
 *
 * modified    2016-01-22, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once
#include "Rectangle.h"
#include <GuiLib/Timing.h>

namespace gui {
class Hookable;
namespace components {
class CText;
class CCanvas;

/** @struct TextAnimatorData:
*  Data used while drawing/modifying with TextAnimator's.
*/
struct TextAnimatorData
{
    /** Storage item, relative x coordinate. */
    int DeltaX;
    /** Storage item, relative y coordinate. */
    int DeltaY;
    /** contains the source rectangle. */
    CRectangle& src;
    /** contains the destination rectangle. */
    CRectangle& dest;
    /** Reference to the calling hookable that provides access to gui::Hookable.GetTicks(). Can be null. */
    Hookable* hookable;
    /** If set to true the TextAnimator will be removed and deleted from the execution queue. 
     The TextAnimator::nextAnimator next animator is added and called on the next run of the queue. */
    bool markedForDeletion;
    int state;

    /// <summary>
    /// Initializes a new instance of the <see cref="TextAnimatorData"/> struct.
    /// </summary>
    /// <param name="src_rect">The source rectangle.</param>
    /// <param name="dst_rect">The destination rectangle.</param>
    TextAnimatorData(CRectangle& src_rect, CRectangle& dst_rect)
        : DeltaX(0), DeltaY(0), src{src_rect}, dest{dst_rect}, hookable(nullptr), markedForDeletion(false), state(1)
    {}
};

/** @class TextAnimator:
 *  An object that can modify CText instances.
 */
class TextAnimator {
public:

    /** Install timing function of the Hookable.
    *  Get the Timing::UpdateTimeFunc functor of the specified Hookable object.
    *  @param hookable The object with the timing function or NULL when not specified.
    *  @return the functor or NULL if no Hookable was specified.
    */
    static Timing::UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable);

    /// <summary>
    /// Initializes a new instance of the <see cref="TextAnimator"/> class.
    /// </summary>
    explicit TextAnimator() : nextAnimator(nullptr), x(0), y(0)
    {}

    /// <summary>
    /// Finalizes an instance of the <see cref="TextAnimator"/> class.
    /// </summary>
    virtual ~TextAnimator(){
        if(nextAnimator) {
            delete nextAnimator;
        }
    }

    /** Loop functor, runs in the CText animator queue.
    *  Functor implementation of the CText::TextModifierFunc that is used to modify or animate CText objects.
    *  @param target The target canvas to paint on.
    *  @param text The CText object to modify.
    *  @param mdata Parameters for all TextAnimator's in the transformation loop. 
    */
    virtual void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) = 0;

    TextAnimator * Wait(Hookable* hookable, Timing::seconds waitTime = 1.0f);
    
    /** Move to position.
    *  Translate the hosting object to the specified position and with specified speed.
    *  @param destination The final point of the object to animate.
    *  @param speed The speed of the translation.
    *  @param hookable hosting object that provides access to Hookable::GetTicks() for timing purposes.
    *  @return a new TextAnimator that can be used to build a method chain initialization.
    *  (like ->MoveTo(CPoint(200, 200), 4.0f, this)->MoveTo(CPoint(300, 600), 8.0f, this)->MoveTo(CPoint(900, 40), 12.0f, this)-> ...
    */
    TextAnimator * FlyTo(CPoint destination, Hookable* hookable = NULL, float speed = 1.0f, Timing::seconds timeIn = 1.0f, Timing::seconds timeOut = 1.0f);

    TextAnimator * Position(CPoint destination);

    TextAnimator * FadeIn(Hookable* hookable, Timing::seconds fadeInTime = 1.0f);
    TextAnimator * FadeOut(Hookable* hookable, Timing::seconds fadeOutTime = 1.0f, bool fadeOutRemovesText = false);

    /** If set the animator is added and called on the next run of the queue when this instance is being finalized/removed from the queue. */
    TextAnimator* nextAnimator;
    /** Storage item, x coordinate. */
    double x;
    /** Storage item, y coordinate. */
    double y;
};
}
}
