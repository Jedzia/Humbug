/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the Line.cpp class.
 * \file       Line.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "../../../stdafx.h"
#include "Line.h"

namespace gui {
namespace components {
void SLine::RenderDrawLine(const CCanvas* target, const CPoint& pStart, const CPoint& pEnd, const CColor* color){
    target->RenderDrawLine(pStart, pEnd, color);
}
}   // namespace components
} // namespace gui
