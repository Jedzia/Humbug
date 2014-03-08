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
#include <GUI/Components/Text.h>
#include <GUI/Components/TextScroller.h>
#include <GUI/Controls/Button.h>
#include <GUI/Data/ColorData.h>
#include <GUI/Sprite/Sprite.h>
#include <GUI/Sprite/SpriteManager.h>
#include <GUI/Visual/EventHandler.h>

namespace humbug {
  namespace levels {
    using namespace gui::components;
    using namespace gui;

    struct TestLevel::TestLevelImpl {
        //prv::EyeMover eyemover;
        //prv::WormMover wormmover;
        int x;
    };

    TestLevel::TestLevel( FileLoader& loader, gui::components::CCanvas* background) :
        pimpl_(new TestLevel::TestLevelImpl ),
        Screen(background),
        m_Loader(loader),
        m_pArialfont(NULL),
        //m_iUpdateTimes(0),
        m_pScrollText(NULL),
        m_pScroller(NULL),
        m_pSprMgr(new CSpriteManager){
        //,m_pSprEye(NULL),
        //m_pSprWormler(NULL)
        dbgOut(__FUNCTION__ << " " << this);
    }

    TestLevel::~TestLevel(void){
        //if (m_pArialfont) {
        //    TTF_CloseFont(m_pArialfont);
        //}

        delete m_pSprite;
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

    gui::controls::CButton* testbutton;

    /** $(class), OnInit:
     *  Detailed description.
     *  @param argc TODO
     * @param argv TODO
     * @return TODO
     */
    bool TestLevel::OnInit( int argc, char* argv[] ){
        // Master()->GetMainCanvas();
        CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

        testbutton = new gui::controls::CButton(CControl::GetMainControl(), CRectangle(0, 0, 160,
                        40), 21345, "Change Direction");
        testbutton->SetPosition( CPoint(800, 30) );

        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
        //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
        // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
        //m_pArialfont = TTF_OpenFont("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf",
        // 30);
        m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 30);
        mcol = CColor::White();
        SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.FL_LOADIMG("Intro/TestScreenBg.png") );

        //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
        //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
        //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
        //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
        m_pBackground.reset( new CCanvas( tmpfsurf ) );

        //CCanvas tmpCanvas( tmpfsurf );
        m_Loader.FreeLast();

        //m_pSprite = new CSprite(m_Loader, "Sprites/kmail.png", m_pBackground.get()/*,
        // CRectangle(0,0,64,64)*/);
        //m_pSprite = new CSeamlessImage(m_Loader, "Images/Sky01.png", m_pBackground.get()/*,
        // CRectangle(0,0,64,64)*/);
        //m_pSprite = new CSeamlessImage(m_Loader, "Images/Sky02.png", m_pMainCanvas/*,
        // CRectangle(0,0,64,64)*/);
        SDL_Surface* g_pBitmapSurface = SDL_DisplayFormatAlpha( m_Loader.FL_LOADIMG("Images/Sky02.png") );
        m_Loader.FreeLast();
        m_pSprite = new CSeamlessImage( new CCanvas( g_pBitmapSurface ), true );

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

        m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );
        CRectangle frect(700, 500, 185, 185);
        SDL_Color* wavemap = ColorData::Instance()->Wavemap();
        int index = (coldelta * 2 & 63);

        static CPoint sp(-1600, 110);
        //m_pSprite->SetPos(sp);
        //m_pSprite->Draw();
        m_pSprite->Put(m_pMainCanvas, sp);

        if ( testbutton->IsPressed() ) {
            CPoint point(-3, 0);
            sp.Subtract(point);
        }
        else {
            CPoint point(3, 0);
            sp.Subtract(point);
        }

        //m_pMainCanvas->AddUpdateRect( m_pSprite->SprImage()->SrcRect() );
        m_pMainCanvas->AddUpdateRect( m_pMainCanvas->GetDimension() );

        //m_pMainCanvas->FillRect( frect, mcol );
        SDL_Color& fcol = wavemap[index];
        m_pMainCanvas->FillRect( frect, CColor(fcol.r, fcol.g, fcol.b) );
        m_pMainCanvas->AddUpdateRect(frect);

        static int xxx = 0;
        CRectangle dstDims( 0 + xxx, 0 + xxx, 600, 200);
        CRectangle srcDims( 0, 0, 600, 200);
        //m_pScrollText->Put(m_pBackground.get(),dstDims, srcDims );
        m_pScrollText->Put(m_pMainCanvas, dstDims, srcDims );
        m_pMainCanvas->AddUpdateRect(dstDims);
        xxx++;

        testbutton->Invalidate();
        testbutton->Draw();

        coldelta++;

        if (coldelta > 64) {
            coldelta = 0;
        }

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
        //m_iUpdateTimes++;
    }
  }
}
