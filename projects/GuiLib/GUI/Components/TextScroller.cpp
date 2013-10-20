//
#include "stdafx.h"

//
#include "TextScroller.h"
#include "Canvas.h"

//#include <build/cmake/include/debug.h>

namespace gui {
namespace components {

CTextScroller::CTextScroller( CCanvas *dstCanvas, const CText& text, CPoint textPosition,
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

void CTextScroller::Draw( )
{
    int textheigth = m_rctText.GetCanvas()->GetHeight();
    CRectangle textDims(xdelta1-xdelta,0, xdelta,textheigth);

    //CRectangle showline(0,m_cpTextPosition.GetY(),1024,textheigth);
    //CRectangle dstRect( m_cpTextPosition.GetX(),m_cpTextPosition.GetY(), m_iWindowWidth ,textheigth);
    CRectangle dstDims( m_cpTextPosition.GetX() + m_iWindowWidth - xdelta, m_cpTextPosition.GetY(), xdelta,textheigth);

    m_rctText.Put(m_rDstCanvas,dstDims, textDims );

}

void CTextScroller::Scroll( int deltaX )
{
    xdelta1 += deltaX;
    if (xdelta1 >= m_rctText.GetCanvas()->GetWidth())
    {
        xdelta1 = 0;
    }
    xdelta =xdelta1;
    if (xdelta > m_iWindowWidth)
    {
        //xdelta1 +=2;
        xdelta = m_iWindowWidth;
    }
}

} // namespace components
} // namespace gui
