#ifndef HUMBUG_GUI_COMPONENTS_TEXT_H
#define HUMBUG_GUI_COMPONENTS_TEXT_H

#include <string>
#include "SDL_ttf.h"
#include "Color.h"
#include "Rectangle.h"
#include <boost/function.hpp>

namespace gui {
namespace components {

class CCanvas;

struct CTextModifierData
{
    int DeltaX;
    int DeltaY;

    CTextModifierData() : DeltaX(0), DeltaY(0)
    {

    };
};

class CText {
public:

    CText(TTF_Font *font, std::string text, CColor textcolor = CColor::Black());
    ~CText();

    // Todo: "const boost::function<void" does not work under gcc
    // typedef const boost::function<void (const CCanvas* ,const CText *text, CTextModifierData& mdata)> TextModifier;
    typedef boost::function<void (const CCanvas* ,const CText *text, CTextModifierData& mdata)> TextModifier;
    //typedef const boost::function<void(CCanvas*, int)> TextModifierPtr;
    void AddModifier(TextModifier updfunc);
    void RenderPut(CCanvas *canvas, const CRectangle& dstRect) const;
    void RenderPut(CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect) const;
	void Put(CCanvas *canvas, const CRectangle& dstRect) const;
    void Put(CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect) const;
    CCanvas * GetCanvas() const { return m_pText.get(); }

    CColor Color() const
    {
        return m_colText;
    }

    void SetColor(const CColor m_col_text);

private:
    void ApplyModifiers() const;
    void RunModifiers(CCanvas *textcanvas) const;

    TTF_Font *m_pFont;
    std::string m_strText;
    CColor m_colText;
    //CCanvas *m_pText;
    boost::scoped_ptr<CCanvas> m_pText;
    typedef std::vector<TextModifier> TextModifierStorage;
    TextModifierStorage m_vecModifierVault;
    SDL_Surface* m_pRenderText;
};

class CTextParagraph
{
public:
    CTextParagraph(TTF_Font *font, std::string text, CColor textcolor = CColor::Black());
    ~CTextParagraph();

};


} // namespace components
} // namespace gui

#endif // HUMBUG_GUI_COMPONENTS_TEXT_H
