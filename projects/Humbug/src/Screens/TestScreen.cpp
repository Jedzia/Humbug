/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TestScreen.cpp class.
 * \folder     $(folder)
 * \file       TestScreen.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "TestScreen.h"
#include "stdafx.h"

//#include <build/cmake/include/debug.h>
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
//
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "GUI/Data/ColorData.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/Sprite/SpriteManager.h"
#include "GUI/Visual/EventHandler.h"
#include <cstdlib>

using namespace gui::components;
using namespace gui;

namespace humbug {
  namespace screens {
  struct TestScreen::TestScreenImpl {
      //prv::EyeMover eyemover;
      //prv::WormMover wormmover;
      int x;
  };

  TestScreen::TestScreen( FileLoader& loader, CCanvas* background) :
      pimpl_(new TestScreen::TestScreenImpl ),
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

  TestScreen::~TestScreen(void){
      if (m_pArialfont) {
          TTF_CloseFont(m_pArialfont);
      }

      //delete m_pScrollText;
      //delete m_pScroller;
      //delete m_pBackground;
      //delete m_pSprWormler;
      //delete m_pSprEye;
      dbgOut(__FUNCTION__ << " " << this);
  }

/*GroupId TestScreen::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/
  bool TestScreen::OnInit( int argc, char* argv[] ){
      // Master()->GetMainCanvas();
      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

      //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
      //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
      // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
      m_pArialfont = TTF_OpenFont("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/arial.ttf", 30);
      mcol = CColor::White();
      SDL_Surface* tmpfsurf = ( m_Loader.FL_LOADIMG("Intro/TestScreenBg.png") );

      //SDL_SetColorKey(tmpfsurf, SDL_TRUE, 0xff00ff);
      //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_TRUE, 0xff00ff);
      //SDL_SetSurfaceAlphaMod(tmpfsurf, 0);
      //SDL_SetSurfaceAlphaMod(m_pMainCanvas->GetSurface(), 128);
      m_pBackground.reset( new CCanvas( tmpfsurf ) );

      //CCanvas tmpCanvas( tmpfsurf );
      m_Loader.FreeLast();

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

      m_pScrollText.reset( new CText(m_pArialfont, outstring.str(), m_colText) );

      return Screen::OnInit(argc, argv);

      //return true;
  } // OnInit

  /** TestScreen, OnIdle:
   *  Detailed description.
   *  @param ticks TODO
   * @return TODO
   */
  void TestScreen::OnIdle(int ticks){
      //m_pScroller->Scroll(4);
      //m_pSprMgr->OnIdle(ticks);
  }

  /** TestScreen, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void TestScreen::OnDraw(){
      static int coldelta = 0;

      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
      m_pMainCanvas->Lock();

      m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );
      CRectangle frect(700, 500, 185, 185);
      SDL_Color* wavemap = ColorData::Instance()->Wavemap();
      int index = (coldelta * 2 & 63);

      //m_pMainCanvas->FillRect( frect, mcol );
      SDL_Color& fcol = wavemap[index];
      m_pMainCanvas->FillRect( frect, CColor(fcol.r, fcol.g, fcol.b) );
      m_pMainCanvas->AddUpdateRect(frect);

      CRectangle dstDims( 0, 0, 200, 200);
      m_pScrollText->Put(m_pBackground.get(), dstDims, dstDims );
      m_pMainCanvas->AddUpdateRect(dstDims);

      coldelta++;

      if (coldelta > 64) {
          coldelta = 0;
      }

      m_pMainCanvas->Unlock();
  } // OnDraw

  /** TestScreen, OnUpdate:
   *  Detailed description.
   *  @return TODO
   */
  void TestScreen::OnUpdate(){
      Screen::OnUpdate();
      x += 1 + (rand() << 21);
      mcol.SetR( rand() );
      mcol.SetG( rand() );
      mcol.SetB( rand() );
      //m_iUpdateTimes++;
  }
}
}
