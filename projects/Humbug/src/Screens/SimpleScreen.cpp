/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SimpleScreen.cpp class.
 * \folder     $(folder)
 * \file       SimpleScreen.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "SimpleScreen.h"
//
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Components/Text.h"
#include "GUI/Components/TextScroller.h"
#include "GUI/Data/ColorData.h"
#include "GUI/Sprite/Sprite.h"
#include "GUI/Sprite/SpriteManager.h"
#include "GUI/Visual/EventHandler.h"
#include <cstdlib>
//
#include <build/cmake/include/debug.h>

using namespace gui::components;
using namespace gui;

namespace humbug {
  struct SimpleScreen::SimpleScreenImpl {
      //prv::EyeMover eyemover;
      //prv::WormMover wormmover;
      const int fontsize = 48;
      int counter;
      int x;
      boost::scoped_ptr<gui::components::CText> m_pScrollText;
      boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;


      SimpleScreenImpl(FileLoader& fl) : x(0){
          counter = 0;
          TTF_Font* iarial = fl.FL_LOADFONT("Fonts/ARIAL.TTF", fontsize);
          m_pScrollText.reset( new CText( iarial, "Hello this is a text", CColor::Red() ) );
      }

      /** $(class), draw:
       *  Detailed description.
       *  @param canvas TODO
       */
      void draw(CCanvas* canvas, SDL_Color& fcol){
          CRectangle screenrect = canvas->GetDimension();
          CPoint sp(20, 540);
          CColor textColor(fcol.r, fcol.g, fcol.b);
          m_pScrollText->SetColor(textColor);
          CRectangle rect = screenrect + sp.Offset(fcol.r, 1 * (fontsize + 10));
          m_pScrollText->Put(canvas, rect);
          canvas->ClearUpdateRects();
          //canvas->RenderCopyToMain(rect, rect);
          canvas->UpdateTexture(canvas, rect, rect);
          counter++;
      }
  };

  SimpleScreen::SimpleScreen(FileLoader& loader, CCanvas* background) :
      pimpl_( new SimpleScreen::SimpleScreenImpl(loader) ),
      Screen(background),
      m_Loader(loader), x(0)
  {
      //m_iUpdateTimes(0),
      //,m_pSprEye(NULL),
      //m_pSprWormler(NULL)
  }

  SimpleScreen::~SimpleScreen(void){
      //dbgOut(__FUNCTION__ << " " << this << std::endl);
  }

  /*GroupId SimpleScreen::GetGroupID()
     {
     static GroupId grpID = CreateNextGroupID();
     return grpID;
     //throw std::exception("The method or operation is not implemented.");
     }*/
  bool SimpleScreen::OnInit(int argc, char* argv[]){
      // Master()->GetMainCanvas();
      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

      // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
      SDL_Surface* tmpfsurf = m_Loader.FL_LOADIMG("Intro/SimpleScreenBg.png");

      //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
      //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
      //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
      //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
      auto surface = m_pMainCanvas->GetSurface();
      //SDL_PixelFormat my_format = *surface->format;
      // my_format.Amask = 0x000000ff;  // A guess...  Try 0xff000000 too?
      //SDL_Surface* tmpfsurf2 = SDL_ConvertSurfaceFormat(tmpfsurf, my_format.format, 0);

      // only needed when drawing direct 'm_pMainCanvas->Render(m_pBackground->GetSurface());'
      //SDL_Surface* tmpfsurf2 = SDL_ConvertSurfaceFormat(tmpfsurf, surface->format->format, surface->flags);
      //m_pDrawCanvas.reset(new CCanvas(SDL_ConvertSurfaceFormat(tmpfsurf, surface->format->format, 0), true));
      //SDL_Surface* tmpfsurf2 = tmpfsurf;

      m_pBackground.reset(new CCanvas(SDL_ConvertSurfaceFormat(tmpfsurf, surface->format->format, surface->flags), true));
      m_pDrawCanvas.reset(new CCanvas(SDL_ConvertSurfaceFormat(tmpfsurf, surface->format->format, surface->flags), true));
      //m_pDrawCanvas.reset(m_pBackground->CreateRGBCompatible(surface->flags, m_pBackground->GetWidth(), m_pBackground->GetHeight()));
     
      
      m_Loader.FreeLast();
      //m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

      //"\r\n"
      CColor m_colText = CColor::White();
      m_pDrawCanvas->Clear(CColor(50, 50, 50));
      //pimpl_->m_pScrollText->RenderPut(m_pBackground.get(), CRectangle(0, 0, 0, 0));
      //m_pBackground->RenderCopyToMain();

      return Screen::OnInit(argc, argv);

      //return true;
  }   // OnInit

  /** SimpleScreen, OnIdle:
   *  Detailed description.
   *  @param ticks TODO
   * @return TODO
   */
  void SimpleScreen::OnIdle(int ticks){
      //x += 1 + (rand() << 21);
      x += 1;
  }

  /** SimpleScreen, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void SimpleScreen::OnDraw(){
      static int coldelta = 0;
      // copy background tex to main window renderer (aka paste background)
      m_pBackground->RenderCopyToMain();

      CRectangle frect(700, 500, 185, 185);
      CRectangle frect2(100, 200, 185, 185);
      SDL_Color* wavemap = ColorData::Instance()->Wavemap();
      int index = (coldelta * 2 & 63);

      SDL_Color& fcol = wavemap[index];

          int i = x % 24;
          auto rect = CRectangle(i * 10, i * 10, 120, 120);
          //m_pBackground->RenderFillRect(rect, CColor(fcol.r, fcol.g, fcol.b));
          CRectangle sdl_rect = rect + CPoint(200,200);
          m_pDrawCanvas->RenderFillRect(sdl_rect, CColor(fcol.r, 255-fcol.g, fcol.b));



      CRectangle screenrect = m_pBackground->GetDimension();
      CPoint sp(220, 240);
      CColor textColor(fcol.r, fcol.g, fcol.b);
      pimpl_->m_pScrollText->SetColor(textColor);
      pimpl_->m_pScrollText->RenderPut(m_pDrawCanvas.get(), CRectangle(0 + coldelta, 0 + coldelta, 0, 0));
      
      CRectangle dstDims(0, 0, 200, 200);

      coldelta++;

      if (coldelta > 64) {
          coldelta = 0;
      }

  }   // OnDraw

  /** SimpleScreen, OnUpdate:
   *  Detailed description.
   *  @return TODO
   */
  void SimpleScreen::OnUpdate(){
      Screen::OnUpdate();
  }
}
