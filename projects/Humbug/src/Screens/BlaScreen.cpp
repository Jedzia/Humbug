/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BlaScreen.cpp class.
 * \folder     $(folder)
 * \file       BlaScreen.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "BlaScreen.h"
#include "stdafx.h"

//#include <build/cmake/include/debug.h>
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
//
#include "../PlayerKeys.h"
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Image.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "GUI/Controls/Button.h"
#include "GUI/Controls/Control.h"
#include "GUI/Data/ColorData.h"
#include "GUI/Hud.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/Sprite/SpriteManager.h"
#include "GUI/Visual/EventHandler.h"
//
#include <cstdlib>

using namespace gui::components;
using namespace gui::controls;
using namespace gui;

namespace humbug {
  struct BlaScreen::BlaScreenImpl {
      //prv::EyeMover eyemover;
      //prv::WormMover wormmover;
      int x;
  };

  BlaScreen::BlaScreen( FileLoader& loader, CCanvas* background) :
      pimpl_(new BlaScreen::BlaScreenImpl ),
      Screen(background),
      m_Loader(loader),
      m_pArialfont(NULL),
      //m_iUpdateTimes(0),
      m_pScrollText(NULL),
      m_pScroller(NULL),
      m_pHud(NULL),
      m_pKeyHandler(NULL),
      m_pKeyHandler2(NULL),
      m_inActiveSprite(0),
      m_pSprite(NULL),
      m_pSprite2(NULL),
      m_pSprMgr(new CSpriteManager){
      //,m_pSprEye(NULL),
      //m_pSprWormler(NULL)
      //dbgOut(__FUNCTION__ << " " << this << std::endl);
  }

  BlaScreen::~BlaScreen(void){
      if (m_pArialfont) {
          TTF_CloseFont(m_pArialfont);
      }

      delete m_pSprite;
      delete m_pSprite2;
      delete m_pKeyHandler;
      delete m_pKeyHandler2;

      //delete m_pScrollText;
      //delete m_pScroller;
      //delete m_pBackground;
      //delete m_pSprWormler;
      //delete m_pSprEye;
      //dbgOut(__FUNCTION__ << " " << this << std::endl);
  }

/*GroupId BlaScreen::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/
  bool BlaScreen::OnInit( int argc, char* argv[] ){
      // Master()->GetMainCanvas();
      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

      //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
      //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
      // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
      m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
      mcol = CColor::White();
      SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.FL_LOADIMG("Intro/HighscoreScreenBg.png") );

      CControl* mainControl = CControl::GetMainControl();
      m_pHud = new Hud(m_Loader, mainControl, new HudBackground(m_Loader, "Hud/footer.png"), 0);

      //create a button
      new CButton(m_pHud, CRectangle(100, 100, 150, 25), 1, "Come on, Press me!");

      {
          // Todo: use SpriteManager of this instance
          SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.FL_LOADIMG("icons/red.png") );
          CCanvas* tmpCanvas = new CCanvas( tmpfsurf );
          m_Loader.FreeLast();
          m_pSprite = new CSprite(m_pMainCanvas, new CImage( tmpCanvas,
                          true ), m_pBackground.get(), true);

          m_pSprite2 = new gui::CSprite( m_Loader, "Sprites/Voiture.bmp", m_pMainCanvas,
                  CRectangle(0, 0, 32, 32), CPoint(32, 0) );
      }

      //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
      //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
      //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
      //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
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

      m_pKeyHandler = new PlayerKeys(200, 200);
      m_pKeyHandler2 = new PlayerKeys(400, 200);

      return Screen::OnInit(argc, argv);

      //return true;
  } // OnInit

  /** BlaScreen, OnIdle:
   *  Detailed description.
   *  @param frameNumber TODO
   * @return TODO
   */
  void BlaScreen::OnIdle(int frameNumber){
      /*CRectangle screenWithoutHud( 0, 0,
              m_pMainCanvas->GetDimension().GetW(), m_pMainCanvas->GetDimension().GetH() -
              m_pHud->GetCanvas()->GetDimension().GetH() );

         //CRectangle& screenWithoutHud = m_pMainCanvas->GetDimension().Move(hudsize);
         //m_pMainCanvas->Blit(screenrect, *m_pBackground, screenrect);
         static int scrdel = 0;
         scrdel += m_inScreenDelta;
         m_pMainCanvas->Blit( screenWithoutHud, *m_pBackground, screenWithoutHud + CPoint(scrdel, 0)
            );*/

      /*if(m_inScreenDelta != 0) {
         m_pMainCanvas->AddUpdateRect( CRectangle( 0, 0, m_pMainCanvas->GetWidth(),
                m_pMainCanvas->GetHeight() - m_pHud->GetHeight() ) );
         }*/

      //m_pScroller->Scroll(4);
      //m_pSprMgr->OnIdle(frameNumber);
      Uint32 now, diff;
      now = SDL_GetTicks();
      diff = now - m_uiLastTicks;

      if(diff > 20) {
          m_pKeyHandler->HookIdle();
          m_pKeyHandler2->HookIdle();
          m_uiLastTicks = now;
      }

      static int spr2pic = 0;
      m_pSprite2->SprOffset(spr2pic);
      spr2pic++;

      if (spr2pic == 16) {
          spr2pic = 0;
      }
  } // OnIdle

  /** BlaScreen, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void BlaScreen::OnDraw(){
      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
      m_pMainCanvas->Lock();

      {
          static int coldelta = 0;
          m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );
          CRectangle frect(700, 100, 185, 185);
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
      }

      m_pSprite->Draw();
      m_pSprite2->Draw();

      if(m_pHud) {
          m_pHud->Invalidate();
          m_pHud->Draw();
      }

      m_pMainCanvas->Unlock();
  } // OnDraw

  /** BlaScreen, OnUpdate:
   *  Detailed description.
   *  @return TODO
   */
  void BlaScreen::OnUpdate(){
      Screen::OnUpdate();
      x += 1 + (rand() << 21);
      mcol.SetR( rand() );
      mcol.SetG( rand() );
      mcol.SetB( rand() );

      m_pSprite->SetPos(m_pKeyHandler->Char() /* + CPoint(50,50)*/);
      m_pSprite2->SetPos( m_pKeyHandler2->Char() );
      //m_pSprite->SetPos(CPoint(50,50));
      //m_iUpdateTimes++;
  }

  /** BlaScreen, OnEvent:
   *  Detailed description.
   *  @param pEvent TODO
   * @return TODO
   */
  void BlaScreen::OnEvent( SDL_Event* pEvent ){

	  if (m_inActiveSprite == 0) {
		  m_pKeyHandler->HookEventloop(pEvent);
	  }
	  else if (m_inActiveSprite == 1)   {
		  m_pKeyHandler2->HookEventloop(pEvent);
	  }

	  // Todo: move this functionality to Screen
      switch(pEvent->type)
      {
      case SDL_KEYDOWN:                //key press
      {
          //key press
          //OnKeyDown(pEvent->key.keysym.sym, pEvent->key.keysym.mod, pEvent->key.keysym.unicode);
          if( pEvent->key.keysym.sym == SDLK_F1 ) {
              //
              m_inActiveSprite ^= 1;
          }
          break;
      }

      default:
          break;
      } // switch
  } // OnEvent
}
