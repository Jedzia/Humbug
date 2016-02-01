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
#include "InfoText.h"
#include "MenuScreen/SubmenuA.h"
#include "MenuScreen/SubmenuB.h"
#include "MenuScreen/TutorA1.h"
#include "MenuScreen/TutorEasing.h"
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/EasingFunctors.h>
#include <GuiLib/GUI/Components/Rectangle.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextAnimator.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Control.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/Timing2.h>
#include <GuiLib/TimingChain.h>
//
//#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
#include "MenuScreen/MenuScreenPainters.h"

struct MenuScreen::MenuScreenImpl {
    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;

    int x;
    Timing timing;
    DingensPainter painter;

    explicit MenuScreenImpl(MenuScreen* host)
        : x(0), timing{ host }, painter(host) {
    }
};

CMainCanvas * MenuScreen::GetMainCanvas() const {
    return Master()->GetMainCanvas();
}

MenuScreen::MenuScreen(FileLoader& loader, CCanvas* background) :
    pimpl_(new MenuScreenImpl(this)),
    Screen(background),
    m_Loader(loader),
    //m_iUpdateTimes(0),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_HookMgr(new HookableManager(this)), m_pDebugfont(NULL),
    //m_HookMgr(new HookableManager(NULL)),
    m_pSprMgr(new CSpriteManager) {
    dbgOut(__FUNCTION__ << " " << this);
}

MenuScreen::~MenuScreen(void) {
    m_pLineMenu->disconnect(m_connection);
    dbgOut(__FUNCTION__ << " " << this);
}

bool MenuScreen::OnInit(int argc, char* argv[]) {
    TTF_Font* m_pArialfont;
    m_pDebugfont = pimpl_->painter.font = m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);

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

    m_pDebugInfoLabel.reset(new controls::CLabel(NULL, CRectangle(10, 80, 200, 40), 12345, "No Text", m_pArialfont, true, m_colText));
    // m_pDebugInfoLabel->SetPosition(CPoint(10, 40));

    auto keysfont = m_Loader.FL_LOADFONT("Fonts/aaQwertz-Tasten.ttf", 36);
    m_pInfoText.reset(new InfoText3(m_pArialfont, keysfont,
                    Master()->GetMainCanvas()->GetDimension().Pad(CRectangle(60, 500, 60, 40))));
    //Master()->GetMainCanvas()->GetDimension().Pad(CRectangle(60, 500, 60, 40)), CPoint(0,-200)));

    m_colText = CColor::Black();
    std::ostringstream outstring2;
    outstring2 << "This screen shows how to display a simple Submenu. (" << CApplication::ShownFrames();
    outstring2 << ")";
    m_pInfoText->makeCText<CText>(m_pArialfont, outstring2.str(), m_colText);
    m_pInfoText->makeCText<CText>(m_pArialfont, "Use the up and down arrow or [w] and [s] to move the menu cursor up and down.", m_colText);
    m_pInfoText->makeCText<CText>(keysfont, "     K    J      w    s  ");
    m_pInfoText->makeCText<CText>(m_pArialfont, "Enter or [e] selects and Backspace or [q] moves back.", m_colText);
    m_pInfoText->makeCText<CText>(keysfont, " L  e         U     q  ");

    m_pInfoText->makeCText<CText>(m_pArialfont, "Let's fly away ", m_colText)
    //->MoveTo(CPoint(200, 200), this)->MoveTo(CPoint(100, 40), this)->MoveTo(CPoint(300, 440),
    // this);
    ->MoveTo(CPoint(200, 200), this, 4.0f)->MoveTo(CPoint(300, 600), this, 8.0f)->MoveTo(CPoint(900, 40), this, 12.0f)
    ->MoveTo(CPoint(300, 600), this, 16.0f)->MoveTo(CPoint(460, 700), this, 4.0f)
    ->MoveTo(CPoint(20, 20), this, 8.0f)->MoveTo(CPoint(1024 / 2, 768 / 3), this, 12.0f);

    auto text = m_pInfoText->makeCText<CText>(m_pArialfont, " ... to the moon.", m_colText);
    text->FadeIn(this, 4.0f)->Wait(this, 8)->FadeOut(this, 2.5f)->Wait(this, 15)->FadeIn(this, 4.5f);
    text->MoveTo(CPoint(1024 / 2, 768 / 3 + 26), this, 4.0f, 0.005f);
    //text->FadeIn(this, 0.5f)->Wait(this, 3)->FadeOut(this, 2.5f, true);

    // Todo: derive a ScrollingLineMenu
    CRectangle lineMenuRect(100, 100, 800, 300);
    m_pLineMenu.reset(new CLineMenu(m_Loader, NULL, 1, "MenuScreen", lineMenuRect, CRectangle(10, 10, 10, 10)));
    m_pLineMenu->AddTextLabel("Tutor Easing", HookMgr(), boost::make_shared<ScreenCreator<TutorEasing>>(m_Loader, m_pBackground.get()));
    m_pLineMenu->AddTextLabel("Sub Menu A", HookMgr(), boost::make_shared<ScreenCreator<SubmenuA>>(m_Loader, m_pBackground.get()));
    m_pLineMenu->AddTextLabel("Sub Menu B", HookMgr(), boost::make_shared<ScreenCreator<SubmenuB>>(m_Loader, m_pBackground.get()));
    m_pLineMenu->AddTextLabel("Tutor Intro", HookMgr(), boost::make_shared<ScreenCreator<TutorA1>>(m_Loader, m_pBackground.get()));
    m_pLineMenu->AddTextLabel();
    m_pLineMenu->AddTextLabel();
    m_pLineMenu->AddTextLabel();
    m_pLineMenu->AddTextLabel();
    m_pLineMenu->AddTextLabel();
    m_pLineMenu->AddTextLabel();
    // XX uses the functor part ( colored movement) of DingensPainter. XX
    m_pLineMenu->AddChildPainter(DingensPainter(this)); // performs copy
    //m_pLineMenu->AddChildPainter(boost::ref(pimpl_->painter)); // performs no copy
    // XX uses the controls::DetailedControlPainter inheritance of DingensPainter with XX
    // XX After-, Before- and DrawChild() overloaded methods.                          XX
    m_pLineMenu->MakeChildPainter<DingensPainter>(this);
    m_connection = m_pLineMenu->ConnectMenuSChanged(boost::bind(&MenuScreen::MenuSelectionChanged, this, _1));

    // this->AddExclusiveKeyfilters(SDLK_1, SDLK_2) etc.

    return Screen::OnInit(argc, argv);

    //return true;
}   // OnInit

void MenuScreen::OnIdle(int ticks) {
    m_pLineMenu->UpdateIdle(ticks);
    m_pInfoText->UpdateIdle(ticks);
    //m_pScroller->Scroll(4);
    //m_pSprMgr->OnIdle(ticks);
    RaiseOnIdle(ticks);
}

void MenuScreen::OnDraw() {
    if(HookMgr()->IsHookActive()) {
        // When in submenu no Draw() other than the sub-screens should be called.
        RaiseOnDraw();
        return;
    }

    static int coldelta = 0;
    static Timing stopRect(this);
    static Timing2 stopRect2(boost::bind(&Hookable::GetTicks, boost::ref(*this)));

    //CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    //m_pMainCanvas->Lock();

    m_pBackground->RenderCopy();
    SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    SDL_Color& fcol = wavemap[index];
    CColor color = CColor(fcol.r, fcol.g, fcol.b);
    int frectSize = 185;
    CRectangle frect(700, 120, frectSize, frectSize);
    if(stopRect2.IsBefore(1.0f)) {
        frect.W() -= static_cast<int>(frectSize - stopRect.SecondsSinceStart() * frectSize);
        frect.H() -= static_cast<int>(frectSize - stopRect.SecondsSinceStart() * frectSize);
    }

    stopRect.IsBefore(2.0f, [&]() {
        m_pBackground->RenderFillRect(frect, &color);
    });

    // time chaining example. Red, green and blue looping rects..
    {
        CRectangle frect2(760, 620, 64, 64);
        static TimingChain tchain1(this);
        //tchain1.Add(2.0f, [&]() { m_pBackground->RenderFillRect(frect2, CColor::Red()); });
        /*tchain1.Add(1.0f, [&]() { m_pBackground->RenderFillRect(frect2, CColor::Red()); })
            .Add(2.0f, [&]() { m_pBackground->RenderFillRect(frect2, CColor::Blue()); })
            .Add(3.0f, [&]() { m_pBackground->RenderFillRect(frect2, CColor::Green()); });*/

        tchain1
        .At(1.0f, [&]() {
            m_pBackground->RenderFillRect(frect2 - CPoint(80, 0), CColor::Red());
        })
        .At(1.0f, [&]() {
            m_pBackground->RenderFillRect(frect2, CColor::Green());
        })
        .At(1.0f, [&]() {
            m_pBackground->RenderFillRect(frect2 + CPoint(80, 0), CColor::Blue());
        }).Commit(0.01f);
    }

    m_pLineMenu->Draw();

    // timing example, bounce-in info text.
    {
        Timing& timing = pimpl_->timing;
        //static EaseInOutQuad ease;
        //static EaseInOutBounce ease;
        //static EasingOperator ease(2.0f);
        //static EaseOutQuart ease;
        static EaseOutBounce easeBounce;

        //float t1 = timing.RangeMappedSinceStart(-200, 200, -20, 20);
        //float t1 = timing.RangeMappedSinceStart(-600, 0, 0, 4);
        //float t1 = timing.RangeMappedSinceStart(-600, 0, 0, 3.25, -600, 0);
        //float t1 = timing.RangeMappedSinceStart(-600, 0, 0, 3.25, -600, 0,
        // EasingOperator::Func());
        float t1 = timing.RangeMappedSinceStart(-1200, 0, 0, 2.0f, -1200, 0, boost::ref(easeBounce));
        CPoint infotextOffset = CPoint(static_cast<int>(round(t1)), m_pInfoText->GetPosition().GetY());
        static int lastresult = infotextOffset.GetX();
        lastresult -= infotextOffset.GetX();
        std::ostringstream outstring;
        outstring << std::setfill('0') << std::setw(3) << std::fixed << std::setprecision(3) << "t: " << timing.SecondsSinceStart();
        outstring << " t1: " << t1;
        outstring << " last: " << lastresult;
        m_pDebugInfoLabel->SetCaption(outstring.str());
        m_pDebugInfoLabel->Draw();
        lastresult = infotextOffset.GetX();

        m_pInfoText->SetPosition(infotextOffset);
        m_pInfoText->Draw(m_pBackground.get());
    }

    coldelta++;

    if(coldelta > 64) {
        coldelta = 0;
    }

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
    case SDLK_SPACE:
    {
        pimpl_->timing.Reset();
        break;
    }
    default:
        break;
    } // switch
} // MenuScreen::OnEvent

void MenuScreen::MenuSelectionChanged(const std::string&  selectedLabel) const {
    if(selectedLabel == CLineMenu::BackSelected) {
        HookMgr()->DisableHookable();
        return;
    }

    if(HookMgr()->IsHookActive() || selectedLabel.empty()) {
        return;
    }

    HookMgr()->EnableHookable(selectedLabel);

    /*    if (selectedLabel == -1) {
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
       }*/

    dbgOut(__FUNCTION__ << "SelectedLabel: " << selectedLabel << " (" << this << ").");
} // MenuScreen::MenuSelectionChanged
}
