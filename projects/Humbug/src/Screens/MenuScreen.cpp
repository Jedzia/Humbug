/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the MenuScreen.cpp class.
 * \file       MenuScreen.cpp
 * \date       2016-01-09
 * \author     Jedzia.
 *
 * modified    2016-01-09, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "MenuScreen.h"
//
#include "../GUI/DebugOverlay.h"
#include "MenuScreen/SubmenuA.h"
#include "MenuScreen/SubmenuB.h"
#include "InfoText.h"
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/Rectangle.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Control.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Visual/EventHandler.h>
#include <boost/foreach.hpp>
#include <cstdlib>
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
struct MenuScreen::MenuScreenImpl {
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
};

CMainCanvas * MenuScreen::GetMainCanvas() const {
    return Master()->GetMainCanvas();
}

MenuScreen::MenuScreen(FileLoader& loader, CCanvas* background) :
    pimpl_(new MenuScreenImpl),
    Screen(background),
    m_Loader(loader),
    //m_iUpdateTimes(0),
    m_pScrollText(NULL),
    m_pScroller(NULL), m_iFrames(0),
    m_HookMgr(new HookableManager(this)),
    //m_HookMgr(new HookableManager(NULL)),
    m_pSprMgr(new CSpriteManager) {
    dbgOut(__FUNCTION__ << " " << this);
}

MenuScreen::~MenuScreen(void) {
    m_pLineMenu->disconnect(m_connection);
    dbgOut(__FUNCTION__ << " " << this);
}

/** @class InfoText:
 *  Detailed description.
 *  @return TODO
 */
class InfoText {
    int m_iFrames;
    int m_iInitFrame;
    TTF_Font* m_pTextFont;
    TTF_Font* m_pKeysFont;
    CRectangle m_rectPaint;
    boost::scoped_ptr<CText> m_pInfoText1;
    boost::scoped_ptr<CText> m_pInfoText2;
    boost::scoped_ptr<CText> m_pInfoText3;
    boost::scoped_ptr<CText> m_pInfoText4;
    boost::scoped_ptr<CText> m_pInfoText5;
    typedef float seconds;

    seconds GetTime() const {
        return (m_iFrames - m_iInitFrame) / 30.0f;
    }
#define FROMTIME(x) if(GetTime() > (x)) {
#define ENDTIMEBLOCK \
    }

public:

    InfoText(TTF_Font* textFont, TTF_Font* keysFont, const CRectangle& paintDimensions) : m_iFrames(0), m_iInitFrame(0),
        m_pTextFont(textFont), m_pKeysFont(keysFont), m_rectPaint(paintDimensions) {
        CColor m_colText = CColor::Black();
        std::ostringstream outstring;
        outstring << "This screen shows how to display a simple Submenu. (" << CApplication::ShownFrames();
        outstring << ")";
        m_pInfoText1.reset(new CText(m_pTextFont, outstring.str(), m_colText));
        m_pInfoText2.reset(new CText(m_pTextFont,
                        "Use the up and down arrow or [w] and [s] to move the menu cursor up and down.", m_colText));
        m_pInfoText3.reset(new CText(m_pKeysFont, "     K    J      w    s  "));
        m_pInfoText4.reset(new CText(m_pTextFont, "Enter or [e] selects and Backspace or [q] moves back.",
                        m_colText));
        m_pInfoText5.reset(new CText(m_pKeysFont, " L  e         U     q  "));
    }
    ~InfoText() {}

    void Draw(const CCanvas* canvas) const {
        CRectangle rect = m_rectPaint;
        m_pInfoText1->RenderPut(canvas, rect);
        FROMTIME(0.25f)
        rect += m_pInfoText1->VerticalSpacing();
        m_pInfoText2->RenderPut(canvas, rect);
        ENDTIMEBLOCK
            FROMTIME(0.5f)
        rect += m_pInfoText2->VerticalSpacing();
        m_pInfoText3->RenderPut(canvas, rect);
        ENDTIMEBLOCK
            FROMTIME(0.75f)
        rect += m_pInfoText3->VerticalSpacing();
        m_pInfoText4->RenderPut(canvas, rect);
        ENDTIMEBLOCK
            FROMTIME(1.0f)
        rect += m_pInfoText4->VerticalSpacing();
        m_pInfoText5->RenderPut(canvas, rect);
        ENDTIMEBLOCK
    } // Draw
    void Idle(int ticks) {
        if(!m_iInitFrame) {
            m_iInitFrame = ticks;
        }

        m_iFrames = ticks;
    }
};


/** @class MenuScreen:
 *  Detailed description.
 *  @param parent TODO
 *  @param pChild TODO
 *  @param param TODO
 */
class MenuScreen::DingensPainter : public controls::DetailedControlPainter {
    int x;
    int k;
    const MenuScreen* m_pHost;
    CPoint lastPos;

    void BeforeDrawChild(const controls::CControl& parent, controls::CControl* pChild, controls::ControlPainterParameters& param)  override {
        static int e = 0;
        e++;
        //param.SetDrawn(true);
        lastPos = pChild->GetPosition();
    }
    void DrawChild(const controls::CControl& parent, controls::CControl* pChild, controls::ControlPainterParameters& param)  override {
        static int e = 0;
        const int varX = 1;
        pChild->SetPosition(CPoint(lastPos.GetX() + (varX - cos(m_pHost->m_iFrames / 6.0f) * 4), lastPos.GetY() + (varX - sin(m_pHost->m_iFrames / 6.0f) * 4)));
        e++;
        //param.SetDrawn(true);
        CColor sdl_color = CColor::DarkMagenta();
        pChild->GetCanvas()->RenderFillRect(CRectangle(333 + e, 333, 55, 55), &sdl_color);
    }
    void AfterDrawChild(const controls::CControl& parent, controls::CControl* pChild, controls::ControlPainterParameters& param)  override {
        static int e = 0;
        e++;
        //param.SetDrawn(true);
        pChild->SetPosition(lastPos);
    }
public:

    explicit DingensPainter(const MenuScreen* host)
        : DetailedControlPainter(), x(0), k(0), m_pHost(host)
    {}

    virtual ~DingensPainter()
    {}

    void operator()(const controls::CControl& parent, controls::CControl* pChild, controls::ControlPainterParameters& param) {
        int rnd = 4 - (rand() % 4);
        x += rnd;
        k++;

        //auto label = static_cast<controls::CLabel>(pChild);
        auto label = dynamic_cast<controls::CLabel *>(pChild);

        if(label) {
            CColor cl = label->GetTextColor();
            CColor clred = CColor::Red();

            if(cl != clred) {
                //int rdegrees = (m_pHost->m_iFrames + r % 360);
                int degrees = (m_pHost->m_iFrames) * 8 % 360;
                const float PI = 3.14159265f;
                float radians = degrees * PI / 180.0f;
                float clock = degrees / PI;
                int corrector = 64 + sin(radians) * 64;

                int sval = cos(m_pHost->m_iFrames / 6.0f) * 4;
                int c = x % 200;
                //CColor color(c, c, c | 0xa0, c);
                CColor color(corrector, corrector, corrector | 0xa0, corrector);
                //const int kfac = parent.GetNumChildren();
                //CColor color((k % kfac) * 32 + corrector, (k % kfac) * 32, (k % kfac) * 32 | 0xa0,
                // corrector);
                label->SetTextColor(color);
            }

            //pChild->GetCanvas()->SetColorKey(color);
        }

        const int varX = 1;
        //CPoint lastPos = pChild->GetPosition();
        //pChild->SetPosition(CPoint(lastPos.GetX() + (varX - sin(m_pHost->m_iFrames / 6.0f) * 4),
        // lastPos.GetY()));
        //pChild->Draw();
        //pChild->SetPosition(lastPos);
        //param.SetDrawn(true);

        CColor sdl_color = CColor::DarkMagenta();
        pChild->GetCanvas()->RenderFillRect(CRectangle(333 + x, 333, 55, 55), &sdl_color);
    } // ()
};

bool MenuScreen::OnInit(int argc, char* argv[]) {
/*
    CRectangle lineMenuRect = Master()->GetMainCanvas()->GetDimension();
    lineMenuRect.X() += 100;
    lineMenuRect.W() -= 400;
    lineMenuRect.Y() += 100;
    lineMenuRect.H() -= 600;
 */
    // Todo: derive a ScrollingLineMenu
    CRectangle lineMenuRect(100, 100, 800, 300);
    m_pLineMenu.reset(new LineMenu(m_Loader, NULL, 1, "MenuScreen", lineMenuRect, CRectangle(10, 10, 10, 10)));
    label1 = m_pLineMenu->AddTextLabel("Sub Menu A");
    label2 = m_pLineMenu->AddTextLabel("Sub Menu B");
    label3 = m_pLineMenu->AddTextLabel();
    label4 = m_pLineMenu->AddTextLabel();
    label4 = m_pLineMenu->AddTextLabel();
    label4 = m_pLineMenu->AddTextLabel();
    label4 = m_pLineMenu->AddTextLabel();
    label4 = m_pLineMenu->AddTextLabel();

    //static DingensPainter painter(this);
    DingensPainter painter(this);
    //m_pLineMenu->AddChildPainter(boost::ref(painter)); // uses ref, object must be valid
    m_pLineMenu->AddChildPainter(painter); // performs copy

    //m_pLineMenu->OwnChildPainter(new DingensPainter(this));
    //m_pLineMenu->OwnChildPainter(boost::make_shared<DingensPainter>(this));
    //m_pLineMenu->OwnChildPainter(DingensPainter::make_shared<DingensPainter>(this));

    m_pLineMenu->OwnChildPainter<DingensPainter>(this);

    m_connection = m_pLineMenu->connect(boost::bind(&MenuScreen::MenuSelectionChanged, this, _1));

    TTF_Font* m_pArialfont;
    m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
    mcol = CColor::White();

    SDL_Surface* tmpfsurf = (m_Loader.FL_LOADIMG("Intro/MenuScreenBg.png"));
    //m_pBackground.reset(new CCanvas(tmpfsurf));
    m_pBackground = boost::make_shared<CCanvas>(tmpfsurf);
    m_Loader.FreeLast();

    CColor m_colText = CColor::White();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << CApplication::ShownFrames();
    outstring << " ";

    //std::string pstr;
    outstring <<
        "Error error C2248: 'boost::noncopyable_::noncopyable::noncopyable' : cannot access private member "
              <<
        "declared in class " <<
        "'boost::noncopyable_::noncopyable'" << "\t" <<
        "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" <<
        "\t" << "48" << "\t" << "Humbug" << "\r\n" <<
        "\r\n" <<
        "Error" << "\t" << "3" << "\t" <<
        "error C2248: 'boost::scoped_ptr<T>::scoped_ptr' : cannot access private member declared in "
              <<
        "class " <<
        "'boost::scoped_ptr<T>'" << "\t" <<
        "d:/e/projects/c++/humbug/projects/humbug/src/gui/visual/Hookable.h" << "\t" << "48" << "\t" <<
        "Humbug" << "\r\n" <<
        "";

    m_pScrollText.reset(new CText(m_pArialfont, outstring.str(), m_colText));

    auto keysfont = m_Loader.FL_LOADFONT("Fonts/aaQwertz-Tasten.ttf", 36);
    m_pInfoText.reset(new InfoText2(m_pArialfont, keysfont,
                    Master()->GetMainCanvas()->GetDimension().Pad(CRectangle(60, 500, 60, 40))));
    m_colText = CColor::Black();
    std::ostringstream outstring2;
    outstring2 << "This screen shows how to display a simple Submenu. (" << CApplication::ShownFrames();
    outstring2 << ")";
    m_pInfoText->makeCText<CText>(m_pArialfont, outstring2.str(), m_colText);
    m_pInfoText->makeCText<CText>(m_pArialfont, "Use the up and down arrow or [w] and [s] to move the menu cursor up and down.", m_colText);
    m_pInfoText->makeCText<CText>(keysfont, "     K    J      w    s  ");
    m_pInfoText->makeCText<CText>(m_pArialfont, "Enter or [e] selects and Backspace or [q] moves back.", m_colText);
    m_pInfoText->makeCText<CText>(keysfont, " L  e         U     q  ");

    HookMgr()->RegisterHookable("SubmenuA", boost::make_shared<ScreenCreator<SubmenuA>>(m_Loader, m_pBackground.get()));
    HookMgr()->RegisterHookable("SubmenuB", boost::make_shared<ScreenCreator<SubmenuB>>(m_Loader, m_pBackground.get()));

    // this->AddExclusiveKeyfilters(SDLK_1, SDLK_2) etc.

    return Screen::OnInit(argc, argv);

    //return true;
}   // OnInit

void MenuScreen::OnIdle(int ticks) {
    m_iFrames = ticks;
    m_pLineMenu->IdleSetVars(ticks);
    m_pInfoText->Idle(ticks);
    //m_pScroller->Scroll(4);
    //m_pSprMgr->OnIdle(ticks);
    RaiseOnIdle(ticks);
}

void MenuScreen::OnDraw() {
    if(HookMgr()->IsHookActive()) {
        // When in submenu no draw other than the sub-screens should occur.
        RaiseOnDraw();
        return;
    }

    static int coldelta = 0;

    //CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    //m_pMainCanvas->Lock();

    m_pBackground->RenderCopy();
    SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    SDL_Color& fcol = wavemap[index];
    CColor color = CColor(fcol.r, fcol.g, fcol.b);
    CRectangle frect(700, 120, 185, 185);
    m_pBackground->RenderFillRect(frect, &color);

    CRectangle dstDims(0, 0, 200, 200);
    //m_pScrollText->RenderPut(m_pBackground.get(), dstDims, dstDims );
    //m_pMainCanvas->AddUpdateRect(dstDims);

    coldelta++;

    if(coldelta > 64) {
        coldelta = 0;
    }

    m_pLineMenu->Draw();
    m_pInfoText->Draw(m_pBackground.get());

    //m_pMainCanvas->Unlock();
}   // OnDraw

void MenuScreen::OnUpdate() {
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR(rand());
    mcol.SetG(rand());
    mcol.SetB(rand());
    //m_iUpdateTimes++;

    RaiseOnUpdate();
}

void MenuScreen::OnEvent(SDL_Event* pEvent) {
    m_pLineMenu->HookEventloop(pEvent, HookMgr()->IsHookActive());
    RaiseOnEvent(pEvent);

    if(pEvent->type != SDL_KEYDOWN) {
        return;
    }

    switch(pEvent->key.keysym.sym) {
    case SDLK_r:
    {
        auto rect = m_pLineMenu->GetOffset();
        rect.Y()--;
        m_pLineMenu->SetOffset(rect);
        break;
    }
    case SDLK_f:
    {
        auto rect = m_pLineMenu->GetOffset();
        rect.Y()++;
        m_pLineMenu->SetOffset(rect);
        break;
    }
    default:
        break;
    } // switch
} // MenuScreen::OnEvent

void MenuScreen::MenuSelectionChanged(int selectedLabel) const {
    if(selectedLabel == -1) {
        HookMgr()->DisableHookable();
    }

    // When in submenu no selection other than the "back" key should occur.
    if(HookMgr()->IsHookActive()) {
        return;
    }

    if(selectedLabel == label1) {
        HookMgr()->EnableHookable("SubmenuA");
    }
    else if(selectedLabel == label2) {
        HookMgr()->EnableHookable("SubmenuB");
    }

    dbgOut(__FUNCTION__ << "SelectedLabel: " << selectedLabel << " (" << this << ").");
} // MenuScreen::MenuSelectionChanged
}
