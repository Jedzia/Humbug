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

namespace gui {
class Hookable;
namespace components {
class CText;
class CCanvas;

/** @struct TextAnimatorData:
*  Detailed description.
*/
struct TextAnimatorData
{
    int DeltaX;
    int DeltaY;
    CRectangle& src;
    CRectangle& dest;
    Hookable* hookable;
    bool markedForDeletion;
    int state;

    TextAnimatorData(CRectangle& src_rect, CRectangle& dst_rect)
        : DeltaX(0), DeltaY(0), src{src_rect}, dest{dst_rect}, hookable(nullptr), markedForDeletion(false), state(1)
    {}
};

/** @class TextAnimator:
 *  Detailed description.
 */
class TextAnimator {
public:

    explicit TextAnimator() : nextAnimator(nullptr), x(0), y(0)
    {}

    virtual ~TextAnimator(){
        if(nextAnimator) {
            delete nextAnimator;
        }
    }

    virtual void operator()(const CCanvas* target, CText* text, TextAnimatorData& mdata) = 0;

    TextAnimator* nextAnimator;
    TextAnimator * FlyTo(CPoint c_point, float speed = 1.0f, Hookable* hookable = NULL);

    double x;
    double y;
};
}
}
