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
#include "SimpleScreen.h"
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

using namespace gui;
using namespace gui::components;

namespace humbug {
  struct SimpleScreen::SimpleScreenImpl {
      //prv::EyeMover eyemover;
      //prv::WormMover wormmover;
      int x;
  };

  SimpleScreen::SimpleScreen( FileLoader& loader, CCanvas* background) :
      pimpl_(new SimpleScreen::SimpleScreenImpl ),
      Screen(background),
      m_Loader(loader)
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
  bool SimpleScreen::OnInit( int argc, char* argv[] ){
      // Master()->GetMainCanvas();
      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

      // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
      SDL_Surface* tmpfsurf =  m_Loader.FL_LOADIMG("Intro/SimpleScreenBg.png");

      //SDL_SetColorKey(tmpfsurf, SDL_SRCCOLORKEY, 0xff00ff);
      //SDL_SetColorKey(m_pMainCanvas->GetSurface(), SDL_SRCCOLORKEY, 0xff00ff);
      //SDL_SetAlpha(tmpfsurf, SDL_SRCALPHA, 0);
      //SDL_SetAlpha(m_pMainCanvas->GetSurface(), SDL_SRCALPHA, 128);
      auto surface = CApplication::GetApplication()->GetMainCanvas()->GetSurface();
      //SDL_PixelFormat my_format = *surface->format;
     // my_format.Amask = 0x000000ff;  // A guess...  Try 0xff000000 too? 
      //SDL_Surface* tmpfsurf2 = SDL_ConvertSurfaceFormat(tmpfsurf, my_format.format, 0);
      
      // only needed when drawing direct 'm_pMainCanvas->Render(m_pBackground->GetSurface());'
      //SDL_Surface* tmpfsurf2 = SDL_ConvertSurfaceFormat(tmpfsurf, surface->format->format, 0);
      SDL_Surface* tmpfsurf2 = tmpfsurf;

      m_pBackground.reset(new CCanvas(tmpfsurf2));

      //CCanvas tmpCanvas( tmpfsurf );
      m_Loader.FreeLast();

      m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

      //"\r\n"
      CColor m_colText = CColor::White();

      return Screen::OnInit(argc, argv);

      //return true;
  } // OnInit

  /** SimpleScreen, OnIdle:
   *  Detailed description.
   *  @param ticks TODO
   * @return TODO
   */
  void SimpleScreen::OnIdle(int ticks){
      //x += 1 + (rand() << 21);
  }

  /** SimpleScreen, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void SimpleScreen::OnDraw(){
      static int coldelta = 0;

      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();   
      // copy background tex to main window renderer (aka paste background)
      m_pBackground->RenderCopyToMain();
      //m_pMainCanvas->Render(m_pBackground->GetSurface());

      //m_pMainCanvas->Lock();
      //m_pMainCanvas->RenderCopy(m_pBackground.get());

      //m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );
      CRectangle frect(700, 500, 185, 185);
      CRectangle frect2(100, 200, 185, 185);
      SDL_Color* wavemap = ColorData::Instance()->Wavemap();
      int index = (coldelta * 2 & 63);

      SDL_Color& fcol = wavemap[index];
      //bool result = m_pBackground->RenderFillRect(frect, CColor(fcol.r, fcol.g, fcol.b));
      
      for (int i = 0; i < 24; i++)
      {
          auto rect = CRectangle(i * 10, i * 10, i*20, 185);
          m_pBackground->RenderFillRect(rect, CColor(fcol.r, fcol.g, fcol.b));
      }
      //result = m_pBackground->FillRect(frect2, CColor(fcol.r, fcol.g, fcol.b));
      //m_pBackground->AddUpdateRect(frect);
      

      //bool result = m_pBackground->RenderFillRect(frect2, CColor(fcol.r, fcol.g, fcol.b));

      //m_pMainCanvas->Render(m_pBackground->GetTexture());
      

      CRectangle dstDims( 0, 0, 200, 200);

      coldelta++;

      if (coldelta > 64) {
          coldelta = 0;
      }

      //m_pBackground->UpdateTexture();
      //m_pMainCanvas->UpdateTexture(m_pBackground.get());
     
      //m_pMainCanvas->RenderCopy(m_pBackground.get());
      
      //SDL_RenderCopy(m_pMainCanvas->m_pRenderer, m_pBackground->GetTexture(), NULL, NULL);
      //m_pMainCanvas->Unlock();
  } // OnDraw

  /** SimpleScreen, OnUpdate:
   *  Detailed description.
   *  @return TODO
   */
  void SimpleScreen::OnUpdate(){
      Screen::OnUpdate();
  }
}
