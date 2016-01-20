/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TextScroller.h class.
 * \folder     $(folder)
 * \file       TextScroller.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_COMPONENTS_TEXTSCROLLER_H
#define HUMBUG_GUI_COMPONENTS_TEXTSCROLLER_H

#include "Canvas.h"
#include "Point.h"
#include "Text.h"

namespace gui {
namespace components {
/** @class CTextScroller:
 *  Detailed description.
 *
 */
class CTextScroller {
public:

    CTextScroller(CCanvas* dstCanvas, CText& text, CPoint textPosition, int windowWidth);
    ~CTextScroller();

    void Draw() const;

    void Scroll(int deltaX);

    void Render();

private:

    void PrepareDraw(CRectangle& textDims, CRectangle& dstDims) const;

    CCanvas* m_rDstCanvas;
    CText& m_rctText;
    CPoint m_cpTextPosition;
    int m_iWindowWidth;

    int xdelta;
    int xdelta1;
};
} // namespace components
} // namespace gui

#endif // HUMBUG_GUI_COMPONENTS_TEXTSCROLLER_H
