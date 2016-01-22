#ifndef HUMBUG_GUI_COMPONENTS_TEXT_H
#define HUMBUG_GUI_COMPONENTS_TEXT_H

#include <string>
#include "SDL_ttf.h"
#include "Color.h"
#include "Rectangle.h"
#include <boost/function.hpp>

namespace gui {
    class Hookable;
    namespace components {
        class CText;

        class CCanvas;

struct CTextModifierData
{
    int DeltaX;
    int DeltaY;
    CRectangle& src;
    CRectangle& dest;
    Hookable *hookable;
    bool markedForDeletion;
    int state;

    CTextModifierData(CRectangle& src_rect, CRectangle& dst_rect)
        : DeltaX(0), DeltaY(0), src{ src_rect }, dest{ dst_rect }, hookable(nullptr), markedForDeletion(false), state(1)
    {
    }
};

class Animator {
public:
    explicit Animator() : nextAnimator(nullptr), x(0), y(0)
    {
    }

    virtual ~Animator()
    {
        if (nextAnimator)
        {
            delete nextAnimator;
        }
    }

    virtual void operator()(const CCanvas* target, CText* text, CTextModifierData& mdata) = 0;

    Animator* nextAnimator;
    Animator* FlyTo(CPoint c_point, Hookable* hookable);

    double x;
    double y;
};


class CText {
public:

    CText(TTF_Font *font, std::string text, CColor textcolor = CColor::Black(), const CPoint& position = CPoint(0, 0));
    ~CText();
    
    // Todo: "const boost::function<void" does not work under gcc
    // typedef const boost::function<void (const CCanvas* ,const CText *text, CTextModifierData& mdata)> TextModifier;
    typedef boost::function<void (const CCanvas* ,CText *text, CTextModifierData& mdata)> TextModifier;
    //typedef const boost::function<void(CCanvas*, int)> TextModifierPtr;
    void AddModifier(TextModifier updfunc);
    void AddModifier(Animator* animator);
    Animator* FlyTo(CPoint c_point, Hookable *hookable = NULL);
    
    // render, the only one that takes the position into account.
    void RenderPut(const CCanvas *canvas);
    void RenderPut(const CCanvas *canvas, const CRectangle& dstRect);
    void RenderPut(const CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect);
	void Put(CCanvas *canvas, const CRectangle& dstRect);
    void Put(CCanvas *canvas, const CRectangle& dstRect, const CRectangle& srcRect);
    void Dings(SDL_Color sdl_color);

    CCanvas * GetCanvas() const { return m_pText.get(); }
    CPoint VerticalSpacing() const;
    CPoint HorizontalSpacing() const;

    CColor Color() const
    {
        return m_colText;
    }

    void SetColor(const CColor m_col_text);

    CPoint GetPosition() const
    {
        return m_ptPosition;
    }

    void SetPosition(CPoint m_pt_position)
    {
        m_ptPosition = m_pt_position;
    }

    TTF_Font* GetFont() const
    {
        return m_pFont;
    }

    __declspec(property(get = MPFont, put = set_MPFont)) TTF_Font* MPFont;
    __declspec(property(get = MPtPosition, put = set_MPtPosition)) CPoint MPtPosition;
private:
    void ApplyModifiers(CRectangle& srcRect, CRectangle& dstRect);
    void ApplyAnimators(CRectangle& srcRect, CRectangle& dstRect);
    void RunModifiers(CCanvas *textcanvas) const;

    CPoint m_ptPosition;
    TTF_Font *m_pFont;
    std::string m_strText;
    CColor m_colText;
    //CCanvas *m_pText;
    boost::scoped_ptr<CCanvas> m_pText;
    typedef std::vector<TextModifier> TextModifierStorage;
    TextModifierStorage m_vecModifierVault;
    typedef boost::ptr_vector<Animator> AnimatorStorage;
    AnimatorStorage m_vecAnimatorVault;
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
