/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Line.h class.
 * \file       Line.h
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef __SLine_H__
#define __SLine_H__

#include "../Canvas.h"

namespace gui {
namespace components {
/** @class SLine:
 *  Aids in drawing lines to several targets. (At the time only CCanvas).
 *  Todo: isn't deriving from CCanvas to heavy ? (alternative: derive from ../Shape.h, BaseShape)
 */
class SLine : public CCanvas {
public:

    /** Render a Line.
    *  Use this function to draw a line on the specified rendering target.
    *  @param target The canvas to paint on.
    *  @param pStart The start point of the line.
    *  @param pEnd The end point of the line.
    *  @param color The drawing color of the line or NULL if no color change is wanted.
    */
    static void RenderDrawLine(const CCanvas* target, const CPoint& pStart, const CPoint& pEnd, const CColor* color);
};
} // namespace components
} // namespace gui

#endif // ifndef __SLine_H__
