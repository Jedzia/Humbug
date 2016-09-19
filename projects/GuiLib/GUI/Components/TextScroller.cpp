/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TextScroller.cpp class.
 * \folder     $(folder)
 * \file       TextScroller.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "Canvas.h"
#include "TextScroller.h"
//
//#include <build/cmake/include/debug.h>

namespace gui {
namespace components {
CTextScroller::CTextScroller( CCanvas* dstCanvas, CText& text, CPoint textPosition,
        int windowWidth ) :
    m_rDstCanvas(dstCanvas),
    m_rctText(text),
    m_cpTextPosition(textPosition),
    m_iWindowWidth(windowWidth),
    xdelta(0),
    xdelta1(0){
    dbgOut(__FUNCTION__);
}

CTextScroller::~CTextScroller(void){
    dbgOut(__FUNCTION__);
}

/** CTextScroller, Draw:
 *  Detailed description.
 *  @return TODO
 */
void CTextScroller::Draw( ) const
{
    //int textheigth = m_rctText.GetCanvas()->GetHeight();
    //CRectangle textDims(xdelta1 - xdelta, 0, xdelta, textheigth);
    //CRectangle dstDims( m_cpTextPosition.GetX() + m_iWindowWidth - xdelta, m_cpTextPosition.GetY(), xdelta, textheigth);

    CRectangle textDims, dstDims;
    PrepareDraw(textDims, dstDims);
    m_rctText.Put(m_rDstCanvas, dstDims, textDims);
}

/** CTextScroller, Scroll:
 *  Detailed description.
 *  @param deltaX TODO
 * @return TODO
 */
void CTextScroller::Scroll( int deltaX ){
    xdelta1 += deltaX;

    if ( xdelta1 >= m_rctText.GetCanvas()->GetWidth() ) {
        xdelta1 = 0;
    }

    xdelta = xdelta1;

    if (xdelta > m_iWindowWidth) {
        //xdelta1 +=2;
        xdelta = m_iWindowWidth;
    }
}

/** CTextScroller, PrepareDraw:
 *  Detailed description.
 *  @param textDims TODO
 * @param dstDims TODO
 * @return TODO
 */
void CTextScroller::PrepareDraw(CRectangle& textDims, CRectangle& dstDims) const
{
    int textheigth = m_rctText.GetCanvas()->GetHeight();
    textDims = CRectangle(xdelta1 - xdelta, 0, xdelta, textheigth);
    int x = m_cpTextPosition.GetX() + m_iWindowWidth - xdelta;
    dstDims = CRectangle(x, m_cpTextPosition.GetY(), xdelta, textheigth);
}

/** CTextScroller, Render:
 *  Detailed description.
 *  @return TODO
 */
void CTextScroller::Render()
{
    CRectangle textDims, dstDims;
    PrepareDraw(textDims, dstDims);

    m_rctText.RenderPut(m_rDstCanvas, dstDims, textDims);
}
} // namespace components
} // namespace gui
