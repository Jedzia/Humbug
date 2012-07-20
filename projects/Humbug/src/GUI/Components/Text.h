#ifndef TEXT_H
#define TEXT_H

#include <string>
#include "SDL_ttf.h"
#include "Color.h"
#include "Rectangle.h"

class CCanvas;

class CText {
public:

    CText(TTF_Font *font, std::string text, CColor textcolor = CColor::Black());
    ~CText();

    void Put(CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect ) const;
    CCanvas * GetCanvas() const { return m_pText; }
private:
    TTF_Font *m_pFont;
    std::string m_strText;
    CColor m_colText;
    CCanvas *m_pText;
};

#endif // TEXT_H
