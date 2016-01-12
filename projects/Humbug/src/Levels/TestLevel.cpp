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
#include <Filesystem/FileLoader.h>
#include <GUI/Components/Image.h>
#include <GUI/Components/Rectangle.h>
#include <GUI/Components/SeamlessImage.h>
#include <GUI/Components/Image.h>
#include <GUI/Components/Text.h>
#include <GUI/Components/TextScroller.h>
#include <GUI/Controls/Button.h>
#include <GUI/Data/ColorData.h>
#include <GUI/Sprite/Sprite.h>
#include <GUI/Sprite/SpriteManager.h>
#include <GUI/Visual/EventHandler.h>
#include "../Input/PlayerKeys3.h"
#include "HumbugShared/GameObjects/Player.h"
#include "GUI/DebugOverlay.h"
#include <GUI/Controls/Label.h>


namespace humbug {
  namespace levels {
    using namespace gui::components;
    using namespace gui;
    
    class CanvasStripeRendererOld {
        int m_iBoatcols;
        int m_iFrames;
        int m_iSteps;
        SDL_Color cmap[256];

    public:

        // this little bastard should render colored stripes when ready.
        explicit CanvasStripeRendererOld(int steps = 16) : m_iBoatcols(0), m_iFrames(0), m_iSteps(steps)
        {
        }

        void operator()(gui::components::CCanvas* source, const gui::components::CCanvas* target,
            gui::components::CCanvasRenderModifierData& mdata)
        {
            m_iFrames++;

            if (!mdata.dstRect)
            {
                return;
            }

            CRectangle dstRect(*mdata.dstRect);
            if (m_iFrames % 3 == 0)
            {
                // jitter arround
                dstRect.X() += m_iSteps / 2 - rand() % m_iSteps;
                //dstRect.X() += m_iFrames % 5;
                dstRect.Y() += m_iSteps / 2 - rand() % m_iSteps;
                //dstRect.Y() += m_iFrames % 5;
            }

            if (rand() % 12 > 9)
            {
                // flicker
                CColor bannercolor = CColor::White();
                source->SetTextureColorMod(bannercolor);
            }
            
            target->FinalRenderCopy(source->GetTexture(), mdata.srcRect, &dstRect);
            //target->RenderCopy(source->GetTexture(), mdata.srcRect, dstRect);

            // prevent rendering the target canvas again.
            mdata.isHandled = true;
        }
    };

    class CanvasStripeRenderer {
        int m_iBoatcols;
        int m_iFrames;
        int m_iSteps;
        SDL_Color cmap[256];
        TTF_Font* m_pDebugFont;
        DebugOverlay* m_pDovl;
        controls::CLabel *label1;

    public:

        // this little bastard should render colored stripes when ready.
        explicit CanvasStripeRenderer(int steps = 16, TTF_Font* debugFont = NULL, DebugOverlay* debug_overlay = NULL)
            : m_iBoatcols(0), m_iFrames(0), m_iSteps(steps), m_pDebugFont(debugFont), m_pDovl(debug_overlay), label1(nullptr)
        {
            if (debug_overlay && debugFont)
            {
                if (!controls::CLabel::GetLabelFont())
                {
                    controls::CLabel::SetLabelFont(debugFont);
                }

                label1 = new controls::CLabel(debug_overlay, CRectangle(80, 440, 200, 40), 123, "Rotzbock", true);
                label1->SetPosition(CPoint(80, 400));
                m_pDovl->AddChild(label1);
            }
        }

        static void Render(gui::components::CCanvas* source, const gui::components::CCanvas* target, const CRectangle& dstRect, const CRectangle& srcRect, const CColor& color)
        {
            source->SetTextureColorMod(color);
            target->FinalRenderCopy(source->GetTexture(), &srcRect, &dstRect);
        }

        void operator()(gui::components::CCanvas* source, const gui::components::CCanvas* target,
            gui::components::CCanvasRenderModifierData& mdata)
        {
            m_iFrames++;

            if (!mdata.dstRect)
            {
                return;
            }

            CRectangle dstRect(*mdata.dstRect);
            CRectangle srcRect(source->GetDimension());

            CColor color1 = CColor::White();
            //CColor color1 = CColor::Red();
            CColor color2 = CColor::Green();

            /*if (m_iFrames % 16 > 8)
            {
                color1 = CColor::Green();
                color2 = CColor::Red();
            }*/

            const int stepsize = 16;
            const int colorstep = 256 / stepsize;
            srcRect.H() /= stepsize;
            dstRect.H() /= stepsize;


            int degrees = (m_iFrames * 8 % 360);
            const float PI = 3.14159265f;
            float radians = degrees*PI / 180.0f;
            float clock = degrees / PI;
            int corrector = 64 + sin(radians) * 64;
            int stepcheck = stepsize + sin(((m_iFrames * 2 % 180)+180)*PI / 180.0f) * stepsize;

            if (m_pDebugFont)
            {
                std::ostringstream labelText;
                //labelText << "deg(" << diffx << ", " << diffy << ")";
                labelText << "deg(" << degrees << ")";
                CText label(m_pDebugFont, (labelText.str()), CColor::DarkRed());
                label.RenderPut(source, CRectangle(20,100,0,0));
            }

            if (label1)
            {
                std::ostringstream labelText;
                labelText << "rad(" << radians << ")";
                label1->SetCaption(labelText.str());
            }

            for (size_t i = 0; i < stepsize; i++)
            {
                //int newColor = (colorstep * ((i * 8 + -m_iFrames / colorstep) % stepsize)) % 255;
                int newColorStep = (colorstep / 2 * i) + 1;
                int newColor = corrector + newColorStep;
                newColor = newColor > 255 ? 255 : newColor;
                newColor = newColor < 0 ? 0 : newColor;

                int newGreen = 25;
                //if ((m_iFrames % (i + 1)) > stepsize / 2)
                if (stepcheck == i)
                {
                    newGreen ^= m_iFrames;
                }
                color2 = CColor(newColor, newGreen, 25);
                
                //CRectangle src_rect(*mdata.srcRect);
                Render(source, target, dstRect, srcRect, color2);
                srcRect.Y() += srcRect.H();
                dstRect.Y() += dstRect.H();

            }

            //srcRect.Y() += srcRect.H();
            //dstRect.Y() += dstRect.H();
            //Render(source, target, dstRect, srcRect, color2);

            // prevent rendering the target canvas again.
            mdata.isHandled = true;
        }
    };


    struct TestLevel::TestLevelImpl {
        //prv::EyeMover eyemover;
        //prv::WormMover wormmover;
        int x;
    };

    TestLevel::TestLevel( FileLoader& loader, gui::components::CCanvas* background) :
        pimpl_(new TestLevel::TestLevelImpl ),
        Screen(background, true),
        m_Loader(loader),
        m_pArialfont(NULL),
        //m_iUpdateTimes(0),
        m_pScrollText(NULL),
        m_pScroller(NULL),
        m_pSeamlessImage(NULL),
        m_pKeyHandler(new PlayerKeys3(200, 600,false, false, 1.0f)),
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

        m_pOverlay.reset(new DebugOverlay(m_Loader, controls::CControl::GetMainControl(), 1));


        /*testbutton = new gui::controls::CButton(CControl::GetMainControl(), CRectangle(0, 0, 160,
                        40), 21345, "Change Direction", true);
        testbutton->SetPosition( CPoint(800, 30) );*/

        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
        // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
        //m_pArialfont = TTF_OpenFont("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf",
        // 30);
        m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 30);
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
        SDL_Surface* g_pBitmapSurface = (m_Loader.FL_LOADIMG("Images/SeamlessB.png"));
        m_pSeamlessImage = new CSeamlessImage( new CCanvas( g_pBitmapSurface ), true );
        m_Loader.FreeLast();
        m_pSeamlessImage->SetLoader(&m_Loader);


        // m_pBlue = new CImage(new CCanvas(fl.FL_LOADIMG("icons/blue.png")), true);
        m_pBlue.reset(new CCanvas(m_Loader.FL_LOADIMG("icons/blue.png")));

        //m_pBanding1.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png")), CRectangle(0, 0, 400, 200), true, CPoint(150,50)));
        m_pBanding1.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png")), true));
        //m_pBanding1->DstRect().Y() -= 200;
        //m_pBanding1->DstRect().H() *= 2;
        m_pBanding1->Scale(0.6f);
        CanvasStripeRenderer stripeModifier(16, m_pArialfont, m_pOverlay.get());
        m_pBanding1->GetCanvas()->AddModifier(stripeModifier);
        
        m_pBanding2.reset(new CImage(new CCanvas(m_Loader.FL_LOADIMG("Text/ColorBandedTextWhite01.png")), true));
        m_pBanding2->GetCanvas()->AddModifier(stripeModifier);

        
        
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
    } // OnInit

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

        // m_pMainCanvas->Blit(m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension());
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
        m_pSeamlessImage->RenderPut(m_pBackground.get(), m_pKeyHandler->Char());

        /*if ( testbutton->IsPressed() ) {
            CPoint point(-3, 0);
            sp.Subtract(point);
        }
        else {
            CPoint point(3, 0);
            sp.Subtract(point);
        }*/

        //m_pMainCanvas->AddUpdateRect( m_pSprite->SprImage()->SrcRect() );
        m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );

        //m_pMainCanvas->FillRect( frect, mcol );
        SDL_Color& fcol = wavemap[index];
        CColor sdl_color = CColor(fcol.r, fcol.g, fcol.b, fcol.a);
        m_pMainCanvas->RenderFillRect( frect, sdl_color );
        m_pMainCanvas->AddUpdateRect(frect);

        static int xxx = 0;
        CRectangle dstDims( 0 + xxx, 0 + xxx, 600, 200);
        CRectangle srcDims(0 + xxx, 0, 600, 200 - xxx);
        //m_pScrollText->Put(m_pBackground.get(),dstDims, srcDims );
//        m_pScrollText->GetCanvas()->SetTextureColorMod(sdl_color);
        m_pScrollText->RenderPut(m_pMainCanvas, dstDims, srcDims );
        m_pMainCanvas->AddUpdateRect(dstDims);
        xxx++;
        if (xxx > 128) {
            xxx = 0;
        }

        //testbutton->Invalidate();
        //testbutton->Draw();

        m_pBlue->SetTextureColorMod(sdl_color);
        //m_pBlue->ClearColorKey();
        CRectangle sdl_rect = CRectangle(300,300,256,256);
        m_pBlue->RenderCopy(nullptr, &sdl_rect);

        CColor bannercolor(sdl_color);
        bannercolor.SetR(255 - coldelta);
        //m_pBanding1->GetCanvas()->SetTextureColorMod(bannercolor);
        //m_pBanding1->GetCanvas()->RenderCopy(CPoint(40, 550));
        m_pBanding1->RenderPut(m_pMainCanvas, CPoint(40, 550));
        //m_pBanding1->RenderPut(m_pBackground.get(), CPoint(40, 550));
        
        m_pBanding2->RenderPut(m_pBackground.get(), CPoint(140, 250));
        //m_pBanding2->RenderPut(m_pMainCanvas, CPoint(140, 250));

        coldelta++;

        if (coldelta > 64) {
            coldelta = 0;
        }

        //m_pOverlay->OnDraw();
        CControl::Redraw();
        m_pMainCanvas->Unlock();
    } // OnDraw

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

      void TestLevel::OnEvent(SDL_Event* pEvent)
      {
          m_pKeyHandler->HookEventloop(pEvent);
      }
  }
}
