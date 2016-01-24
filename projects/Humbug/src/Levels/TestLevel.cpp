/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TestLevel.cpp class.
 * \folder     $(folder)
 * \file       TestLevel.cpp
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#include "TestLevel.h"
#include "stdafx.h"

//#include <build/cmake/include/debug.h>
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include <cstdlib>
//
#include "../Input/PlayerKeys3.h"
#include "GUI/DebugOverlay.h"
#include "HumbugShared/GameObjects/Player.h"
#include <GUI/Components/Rectangle.h>
#include <GuiLib/Filesystem/FileLoader.h>
#include <GuiLib/GUI/Components/CoordSystem.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/Image.h>
#include <GuiLib/GUI/Components/SeamlessImage.h>
#include <GuiLib/GUI/Components/Shapes/Line.h>
#include <GuiLib/GUI/Components/Text.h>
#include <GuiLib/GUI/Components/TextScroller.h>
#include <GuiLib/GUI/Controls/Button.h>
#include <GuiLib/GUI/Controls/Label.h>
#include <GuiLib/GUI/Data/ColorData.h>
#include <GuiLib/GUI/Sprite/Sprite.h>
#include <GuiLib/GUI/Sprite/SpriteManager.h>
#include <GuiLib/GUI/Visual/EventHandler.h>

namespace humbug {
namespace levels {
using namespace gui::components;
using namespace gui;

/** @class CanvasStripeRendererOld:
 *  Detailed description.
 *  @param source TODO
 *  @param target TODO
 *  @param mdata TODO
 *  @return TODO
 */
class CanvasStripeRendererOld {
    int m_iBoatcols;
    int m_iFrames;
    int m_iSteps;
    SDL_Color cmap[256];

public:

    // this little bastard should render colored stripes when ready.
    explicit CanvasStripeRendererOld(int steps = 16) : m_iBoatcols(0), m_iFrames(0), m_iSteps(steps)
    {}

    void operator()(gui::components::CCanvas* source, const gui::components::CCanvas* target,
            gui::components::CCanvasRenderModifierData& mdata){
        m_iFrames++;

        if (!mdata.dstRect) {
            return;
        }

        CRectangle dstRect(*mdata.dstRect);

        if (m_iFrames % 3 == 0) {
            // jitter arround
            dstRect.X() += m_iSteps / 2 - rand() % m_iSteps;
            //dstRect.X() += m_iTicks % 5;
            dstRect.Y() += m_iSteps / 2 - rand() % m_iSteps;
            //dstRect.Y() += m_iTicks % 5;
        }

        if (rand() % 12 > 9) {
            // flicker
            CColor bannercolor = CColor::White();
            source->SetTextureColorMod(bannercolor);
        }

        target->FinalRenderCopy(source->GetTexture(), &dstRect, mdata.srcRect);
        //target->RenderCopy(source->GetTexture(), mdata.srcRect, dstRect);

        // prevent rendering the target canvas again.
        mdata.isHandled = true;
    } // ()
};

/** @class CanvasStripeRenderer:
 *  Detailed description.
 *  @param source TODO
 *  @param target TODO
 *  @param dstRect TODO
 *  @param srcRect TODO
 *  @param color TODO
 */
class CanvasStripeRenderer {
    int m_iBoatcols;
    int m_iFrames;
    int m_iSteps;
    SDL_Color cmap[256];
    TTF_Font* m_pDebugFont;
    DebugOverlay* m_pDovl;
    boost::shared_ptr<controls::CLabel> label1;
    int label2;
    int label3;
    int label4;
    int label5;
    int label6;
    CCoordSystem cs;
    static int renderNum;
public:

    // this little bastard should render colored stripes when ready.
    explicit CanvasStripeRenderer(int steps = 16, TTF_Font* debugFont = NULL, DebugOverlay* debug_overlay = NULL)
        : m_iBoatcols(0), m_iFrames(0), m_iSteps(steps), m_pDebugFont(debugFont), m_pDovl(debug_overlay),
        label1(nullptr), label2(0), label3(0), label4(0), cs( "Coords", 400, 400, CPoint(100, 100) ){
        renderNum++;
        if (debug_overlay && debugFont) {
            /*if (!controls::CLabel::GetLabelFont())
               {
                controls::CLabel::SetLabelFont(debugFont);
               }*/

            // manual label creation
            label1.reset( new controls::CLabel( debug_overlay, CRectangle(0, 0, -1, -1), 123, "Label 1", debugFont,
                            true, CColor::Black(), CColor::White() ) );
            Uint16 height = label1->GetHeight();
            label1->SetPosition( CPoint(300, height) );
            m_pDovl->AddChild( label1.get() );

            // automatic labels
            label2 = m_pDovl->AddTextLabel();
            label3 = m_pDovl->AddTextLabel();
            label4 = m_pDovl->AddTextLabel();
            label5 = m_pDovl->AddTextLabel();
            label6 = m_pDovl->AddTextLabel();
        }
    }

    ~CanvasStripeRenderer()
    {
        
    }

    static void Render(gui::components::CCanvas* source, const gui::components::CCanvas* target,
            const CRectangle& dstRect, const CRectangle& srcRect, const CColor& color){
        source->SetTextureColorMod(color);
        target->FinalRenderCopy(source->GetTexture(), &dstRect, &srcRect);
    }
    template<typename T>
    void PrintLabel(const int& id, const char* title, const T& degrees) const {
        if (id) {
            std::ostringstream labelText;
            labelText << "{" << renderNum << "}" << title << "(" << degrees << ")";
            m_pDovl->SetTextLabelText( id, labelText.str() );
        }
    }
    float norm(float ceiling, float floor, float max, float min, float input){
        return 1.0f;
    }
    void operator()(gui::components::CCanvas* source, const gui::components::CCanvas* target,
            gui::components::CCanvasRenderModifierData& mdata){
        m_iFrames++;

        if (!mdata.dstRect) {
            return;
        }

        CRectangle dstRect(*mdata.dstRect);
        CRectangle srcRect( source->GetDimension() );

        CColor color1 = CColor::White();
        //CColor color1 = CColor::Red();
        CColor color2 = CColor::Green();

        /*if (m_iTicks % 16 > 8)
           {
            color1 = CColor::Green();
            color2 = CColor::Red();
           }*/

        const int stepsize = 16;
        const int colorstep = 256 / stepsize;
        srcRect.H() /= stepsize;
        dstRect.H() /= stepsize;

        int rdegrees = (m_iFrames % 360);
        int degrees = (m_iFrames * 8 % 360);
        const float PI = 3.14159265f;
        float radians = degrees * PI / 180.0f;
        float clock = degrees / PI;
        int corrector = 64 + sin(radians) * 64;
        int stepcheck = stepsize + sin( ( (m_iFrames * 2 % 180) + 180 ) * PI / 180.0f ) * stepsize;

        /*if (m_pDebugFont)
           {
            std::ostringstream labelText;
            //labelText << "deg(" << diffx << ", " << diffy << ")";
            labelText << "deg(" << degrees << ")";
            CText label(m_pDebugFont, (labelText.str()), CColor::DarkRed());
            label.RenderPut(source, CRectangle(20,100,0,0));
           }*/

        if (label1) {
            std::ostringstream labelText;
            labelText << "rad(" << radians << ")";
            label1->SetCaption( labelText.str() );
        }

        PrintLabel(label2, "rad", radians);
        PrintLabel(label3, "deg", degrees);
        PrintLabel(label4, "clock", clock);

        // CCoordSystem ?
        target->SetRenderDrawBlendMode(BLENDMODE_NONE);
        CColor color = CColor::LightGreen();
        //target->RenderDrawLine(CPoint(20, 100 + degrees), CPoint(220, 100 + degrees), &color);
        SLine::RenderDrawLine(target, CPoint(20, 100 + degrees), CPoint(220, 100 + degrees), &color);
        target->SetRenderDrawBlendMode(BLENDMODE_MOD);
        CRectangle rect = CRectangle(20, 100 + degrees, 100, 20);
        target->RenderFillRect(rect, &color);
        target->SetRenderDrawBlendMode(BLENDMODE_NONE);

        if (rdegrees == 0) {
            //cs.Reset();
        }

        for (size_t i = 0; i < stepsize; i++)
        {
            //int newColor = (colorstep * ((i * 8 + -m_iTicks / colorstep) % stepsize)) % 255;
            int newColorStep = (colorstep / 2 * i) + 1;
            int newColor = corrector + newColorStep;
            newColor = newColor > 255 ? 255 : newColor;
            newColor = newColor < 0 ? 0 : newColor;

            int newGreen = 25;

            //if ((m_iTicks % (i + 1)) > stepsize / 2)
            if (stepcheck == i) {
                newGreen ^= m_iFrames;
            }

            color2 = CColor(newColor, newGreen, 25);

            //CRectangle src_rect(*mdata.srcRect);
            Render(source, target, dstRect, srcRect, color2);
            srcRect.Y() += srcRect.H();
            dstRect.Y() += dstRect.H();
        }
        cs.AddDatapoint( CPoint(degrees, corrector) );
        PrintLabel( label5, "Datapoints", cs.NumDatapoints() );

        //cs.AddDatapoint(CPoint(rdegrees, rdegrees));
        //cs.AddDatapoint(CPoint(degrees, stepcheck));
        cs.RenderPut(target);

        //srcRect.Y() += srcRect.H();
        //dstRect.Y() += dstRect.H();
        //Render(source, target, dstRect, srcRect, color2);

        // prevent rendering the target canvas again.
        mdata.isHandled = true;
    } // ()
};

int CanvasStripeRenderer::renderNum = 0;


/** @class FadeInOutAnimator:
*  Old test implementation. Use TextMover.
*/
class FadeInOutAnimator /*: public TextAnimator*/ {
public:
    enum class FadeMode {
        FadeIn,
        FadeOut,
        FadeInOut
    };

private:
    Timing::seconds fadeInOutTime;
    FadeMode fadeMode;
    bool fadeOutRemovesText;
    Timing::seconds stayTime;
    Timing::seconds fadeOutTime;
    float fadeDelta;
    Hookable* hookable;
    Timing tifadeInOut;
    Timing timingEnd;

    Timing::UpdateTimeFunc GetTimeUpdateFunction(const Hookable* hookable) const
    {
        if (!hookable) {
            return NULL;
        }

        return boost::bind(&Hookable::GetTicks, boost::ref(*hookable));
    }

public:
    /// <summary>
    /// Initializes a new instance of the <see cref="FadeInOutAnimator"/> class.
    /// </summary>
    /// <param name="hookable">The hookable.</param>
    /// <param name="fadeInOutTime">The fade in time, or fade out time in FadeMode::FadeOut.</param>
    /// <param name="fadeMode">The fade mode. Only FadeMode::FadeIn and FadeMode::FadeOut are implemented.</param>
    /// <param name="stayTime">The stay time. not implemented.</param>
    /// <param name="fadeOutTime">The fade out time. not implemented.</param>
    explicit FadeInOutAnimator(Hookable* hookable, Timing::seconds fadeInOutTime, FadeMode fadeMode = FadeMode::FadeIn, bool fadeOutRemovesText = false,
        Timing::seconds stayTime = 1.0f, Timing::seconds fadeOutTime = 1.0f)
        : fadeInOutTime(fadeInOutTime), fadeMode(fadeMode), fadeOutRemovesText(fadeOutRemovesText), stayTime(stayTime), fadeOutTime(fadeOutTime), hookable(hookable),
        tifadeInOut(GetTimeUpdateFunction(hookable)), timingEnd(GetTimeUpdateFunction(hookable)){
        fadeDelta = 255.0f / Timing::FRAMESPERSECOND / fadeInOutTime;
    }

    /** Loop functor, runs in the CCanvas renderer queue.
    *  Functor implementation of the CCanvas::CCanvasRenderer that is used to modify or animate
    *  CCanvas objects.
    *  @param target The target canvas to paint on.
    *  @param source The CCanvas object to modify.
    *  @param mdata Parameters for all Renderers in the transformation loop.
    */
    void operator()(gui::components::CCanvas* source, const gui::components::CCanvas* target,
        gui::components::CCanvasRenderModifierData& mdata)  {
        // recording: punch in, punch out

        int alpha = 0;

        switch (fadeMode)
        {
        case FadeMode::FadeIn:
            alpha = static_cast<int>(round(tifadeInOut.TicksSinceStart() * fadeDelta));
            if (alpha > 255) {
                alpha = 255;
            }

            break;
        case FadeMode::FadeOut:
            alpha = static_cast<int>(round(255 - tifadeInOut.TicksSinceStart() * fadeDelta));
            if (alpha < 0) {
                alpha = 0;
            }

            break;
        case FadeMode::FadeInOut:
            break;
        default:
            assert(false);
            break;
        } // switch

        source->SetTextureAlphaMod(alpha);

        if (tifadeInOut.IsAtOrAfter(fadeInOutTime)) {
            mdata.state++;
            mdata.markedForDeletion = true;
            if (fadeMode == FadeMode::FadeOut && fadeOutRemovesText)
            {
                //source->Dispose();
            }
        }
    } // ()

    // ()
};

struct TestLevel::TestLevelImpl {
private:

    //prv::EyeMover eyemover;
    //prv::WormMover wormmover;
    int x;
    TestLevel* host;

public:

    explicit TestLevelImpl(TestLevel* host)
        : x(0), host{host}
    {}

    void Draw(){
        auto aaaa = host->m_pBackground->GetDimension();
    }
};

TestLevel::TestLevel( FileLoader& loader, gui::components::CCanvas* background) :
    pimpl_( new TestLevel::TestLevelImpl(this) ),
    Screen(background, true),
    m_Loader(loader),
    m_pArialfont(NULL),
    //m_iUpdateTimes(0),
    m_pScrollText(NULL),
    m_pScroller(NULL),
    m_pSeamlessImage(NULL),
    m_pKeyHandler( new PlayerKeys3(200, 600, false, false, 1.0f) ),
    m_pSprMgr(new CSpriteManager){
    //,m_pSprEye(NULL),
    //m_pSprWormler(NULL)
    dbgOut(__FUNCTION__ << " " << this);
}

TestLevel::~TestLevel(void){
    //if (m_pArialfont) {
    //    TTF_CloseFont(m_pArialfont);
    //}

    delete m_pSeamlessImage;
    //delete m_pScrollText;
    //delete m_pScroller;
    //delete m_pBackground;
    //delete m_pSprWormler;
    //delete m_pSprEye;
    dbgOut(__FUNCTION__ << " " << this);
}

/*GroupId TestLevel::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/

using gui::controls::CControl;

//gui::controls::CButton* testbutton;

/** $(class), OnInit:
 *  Detailed description.
 *  @param argc TODO
 * @param argv TODO
 * @return TODO
 */
bool TestLevel::OnInit( int argc, char* argv[] ){
    // Master()->GetMainCanvas();
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

    //m_pOverlay.reset(new DebugOverlay(m_Loader, controls::CControl::GetMainControl(), 1,
    // "TestLevel"));
    m_pOverlay.reset( new DebugOverlay(m_Loader, NULL, 1, "TestLevel") );

    /*testbutton = new gui::controls::CButton(CControl::GetMainControl(), CRectangle(0, 0, 160,
                    40), 21345, "Change Direction", true);
       testbutton->SetPosition( CPoint(800, 30) );*/

    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
    //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
    // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
    //m_pArialfont = TTF_OpenFont("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf",
    // 30);
    m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 30);
    /*if (!controls::CLabel::GetLabelFont())
       {
        controls::CLabel::SetLabelFont(m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 16));
       }*/

    mcol = CColor::White();
    SDL_Surface* tmpfsurf = ( m_Loader.FL_LOADIMG("Intro/TestScreenBg.png") );

    //SDL_SetColorKey(tmpfsurf, SDL_TRUE, 0xff00ff);
    //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_TRUE, 0xff00ff);
    m_pBackground.reset( new CCanvas( tmpfsurf ) );
    //m_pBackground->GetTexture();

    //CCanvas tmpCanvas( tmpfsurf );
    m_Loader.FreeLast();

    //m_pSprite = new CSprite(m_Loader, "Sprites/kmail.png", m_pBackground.get()/*,
    // CRectangle(0,0,64,64)*/);
    //m_pSprite = new CSeamlessImage(m_Loader, "Images/Sky01.png", m_pBackground.get()/*,
    // CRectangle(0,0,64,64)*/);
    //m_pSprite = new CSeamlessImage(m_Loader, "Images/Sky02.png", m_pMainCanvas/*,
    // CRectangle(0,0,64,64)*/);
    //SDL_Surface* g_pBitmapSurface = (m_Loader.FL_LOADIMG("Images/Sky02.png"));
    SDL_Surface* g_pBitmapSurface = ( m_Loader.FL_LOADIMG("Images/SeamlessB.png") );
    m_pSeamlessImage = new CSeamlessImage( new CCanvas( g_pBitmapSurface ), true );
    m_Loader.FreeLast();
    m_pSeamlessImage->SetLoader(&m_Loader);

    // m_pBlue = new CImage(new CCanvas(fl.FL_LOADIMG("icons/blue.png")), true);
    m_pBlue.reset( new CCanvas( m_Loader.FL_LOADIMG("icons/blue.png") ) );

    //m_pBanding1.reset(new CImage(new
    // CCanvas(m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png")), CRectangle(0, 0, 400, 200),
    // true, CPoint(150,50)));
    m_pBanding1.reset( new CImage(new CCanvas( m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png") ), true) );
    //m_pBanding1->DstRect().Y() -= 200;
    //m_pBanding1->DstRect().H() *= 2;
    m_pBanding1->Scale(0.6f);
    CanvasStripeRenderer stripeModifier( 16, m_pArialfont, m_pOverlay.get() );
    m_pBanding1->GetCanvas()->AddModifier(stripeModifier);

    m_pBanding2.reset( new CImage(new CCanvas( m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png") ), true) );
    //CanvasStripeRenderer stripeModifier2(16, m_pArialfont, m_pOverlay.get());
    //static CanvasStripeRenderer stripeModifier2(16, m_pArialfont, m_pOverlay.get());
    //m_pBanding2->GetCanvas()->AddAnimator(boost::ref(stripeModifier2));
    m_pBanding2->GetCanvas()->AddModifier(stripeModifier);
    FadeInOutAnimator fadeRenderer(this, 3.0f, FadeInOutAnimator::FadeMode::FadeIn);
    m_pBanding2->GetCanvas()->AddModifier(fadeRenderer);


    //m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    //m_pBackground->Blit(m_pBackground->GetDimension(), tmpCanvas, tmpCanvas.GetDimension());
    m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

    //"\r\n"
    CColor m_colText = CColor::White();
    std::ostringstream outstring;
    outstring << "Bla fasel:" << gui::CApplication::ShownFrames();
    outstring << " ";

    //std::string pstr;
    outstring <<
        "The Test Level! \n"
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

    m_pScrollText.reset( new CText(m_pArialfont, outstring.str(), m_colText) );

    return Screen::OnInit(argc, argv);

    //return true;
}     // OnInit

/** $(class), OnIdle:
 *  Detailed description.
 *  @param ticks TODO
 * @return TODO
 */
void TestLevel::OnIdle(int ticks){
    m_pOverlay->IdleSetVars(ticks);
    m_pKeyHandler->HookIdle(ticks, 1.0f);
    //m_pScroller->Scroll(4);
    //m_pSprMgr->OnIdle(ticks);
}

/** $(class), OnDraw:
 *  Detailed description.
 *  @return TODO
 */
void TestLevel::OnDraw(){
    static int coldelta = 0;

    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    m_pMainCanvas->Lock();
    //m_pMainCanvas->MainRenderClear();

    // m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), *m_pBackground,
    // m_pBackground->GetDimension());
    m_pBackground->RenderCopy();
    CRectangle frect(700, 500, 185, 185);
    static SDL_Color* wavemap = ColorData::Instance()->Wavemap();
    int index = (coldelta * 2 & 63);

    //static CPoint sp(-480, 110);
    static CPoint sp(0, 110);
    //m_pSprite->SetPos(sp);
    //m_pSprite->Draw();
    //m_pSeamlessImage->RenderPut(m_pMainCanvas, sp);
    //m_pSeamlessImage->RenderPut(m_pBackground.get(), sp);
    m_pSeamlessImage->RenderPut( m_pBackground.get(), m_pKeyHandler->Char() );

    /*if ( testbutton->IsPressed() ) {
        CPoint point(-3, 0);
        sp.Subtract(point);
       }
       else {
        CPoint point(3, 0);
        sp.Subtract(point);
       }*/

    //m_pMainCanvas->AddUpdateRect( m_pSprite->SprImage()->SrcRect() );
    //m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );

    //m_pMainCanvas->FillRect( frect, mcol );
    SDL_Color& fcol = wavemap[index];
    CColor sdl_color = CColor(fcol.r, fcol.g, fcol.b, fcol.a);
    m_pMainCanvas->RenderFillRect( frect, &sdl_color );
    //m_pMainCanvas->AddUpdateRect(frect);

    static int xxx = 0;
    CRectangle dstDims( 0 + xxx, 0 + xxx, 600, 200);
    CRectangle srcDims(0 + xxx, 0, 600, 200 - xxx);
    //m_pScrollText->Put(m_pBackground.get(),dstDims, srcDims );
//        m_pScrollText->GetCanvas()->SetTextureColorMod(sdl_color);
    m_pScrollText->RenderPut(m_pMainCanvas, dstDims, srcDims );
    //m_pMainCanvas->AddUpdateRect(dstDims);
    xxx++;

    if (xxx > 128) {
        xxx = 0;
    }

    //testbutton->Invalidate();
    //testbutton->Draw();

    m_pBlue->SetTextureColorMod(sdl_color);
    //m_pBlue->ClearColorKey();
    CRectangle sdl_rect = CRectangle(300, 300, 256, 256);
    CPoint point = CPoint(300, 300);
    //m_pBlue->RenderCopy(nullptr, &sdl_rect);
    //m_pBlue->RenderCopy(static_cast<CRectangle*>(nullptr), &sdl_rect);
    m_pBlue->RenderCopy(&sdl_rect);
    //m_pBlue->RenderCopy(point);
    //m_pBlue->RenderCopy(&sdl_rect);

    CColor bannercolor(sdl_color);
    bannercolor.SetR(255 - coldelta);
    //m_pBanding1->GetCanvas()->SetTextureColorMod(bannercolor);
    //m_pBanding1->GetCanvas()->RenderCopy(CPoint(40, 550));
    m_pBanding1->RenderPut( m_pMainCanvas, CPoint(40, 550) );
    //m_pBanding1->RenderPut(m_pBackground.get(), CPoint(40, 550));

    m_pBanding2->RenderPut( m_pBackground.get(), CPoint(140, 250) );
    //m_pBanding2->RenderPut(m_pMainCanvas, CPoint(140, 250));

    pimpl_->Draw();

    coldelta++;

    if (coldelta > 64) {
        coldelta = 0;
    }

    //m_pOverlay->OnDraw();
    m_pOverlay->Draw();
    m_pMainCanvas->Unlock();
}     // OnDraw

/** $(class), OnUpdate:
 *  Detailed description.
 *  @return TODO
 */
void TestLevel::OnUpdate(){
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR( rand() );
    mcol.SetG( rand() );
    mcol.SetB( rand() );

    /*if (testbutton->IsPressed()) {
        m_pKeyHandler->Reset();
       }*/

    //m_iUpdateTimes++;
}

void TestLevel::OnEvent(SDL_Event* pEvent){
    m_pKeyHandler->HookEventloop(pEvent);
}
}
}
