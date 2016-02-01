/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BaseDrawable.h class.
 * \file       BaseDrawable.h
 * \date       2016-01-23
 * \author     Jedzia.
 *
 * modified    2016-01-23, Jedzia
 */
/*---------------------------------------------------------*/
#pragma once

#include "../Disposable.h"
#include "Rectangle.h"

namespace gui {
namespace components {
/** @class BaseDrawable:
 *  Base class for all items that draw on their member canvas.
 *  See: BaseShape's are lightweight items that draw themselves to a CCanvas, but don't own a CCanvas.
 *  $(javaparam)
 */
class BaseDrawable : public Disposable {
public:


    explicit BaseDrawable(const CPoint& m_pt_position)
        : m_ptPosition{m_pt_position}
    {
    }

    /** Get current text Position.
        *  Gets the current text position of this instance.
        *  @return the point of the text position.
        */
    CPoint GetPosition() const { return m_ptPosition; }

    /** Set text Position.
    *  Sets the text position of this instance used by RenderPut(const CCanvas* canvas).
    *  @param position The value of the text position.
    */
    void SetPosition(CPoint position) { m_ptPosition = position; }

private:
    CPoint m_ptPosition;

};
}
}
