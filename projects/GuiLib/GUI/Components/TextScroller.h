#ifndef HUMBUG_GUI_COMPONENTS_TEXTSCROLLER_H
#define HUMBUG_GUI_COMPONENTS_TEXTSCROLLER_H

#include "Text.h"
#include "Point.h"
#include "Canvas.h"


namespace gui {
namespace components {

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

} // namespace components
} // namespace gui

#endif // HUMBUG_GUI_COMPONENTS_TEXTSCROLLER_H
