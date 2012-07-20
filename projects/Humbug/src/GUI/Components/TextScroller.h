#ifndef TEXTSCROLLER_H
#define TEXTSCROLLER_H

#include "Text.h"
#include "Point.h"
#include "Canvas.h"


class CTextScroller {
public:

    CTextScroller(CCanvas *dstCanvas, const CText& text, CPoint textPosition, int windowWidth);
    ~CTextScroller();

    void Draw();
    void Scroll(int deltaX);

private:
    CCanvas *m_rDstCanvas;
    const CText& m_rctText;
    CPoint m_cpTextPosition;
    int m_iWindowWidth;

    int xdelta;
    int xdelta1;

};

#endif // TEXTSCROLLER_H
