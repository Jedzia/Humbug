/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TileScreen.cpp class.
 * \folder     $(folder)
 * \file       TileScreen.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "stdafx.h"
//
#include "TileScreen.h"

//#include <build/cmake/include/debug.h>
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
//
#include "Filesystem/FileLoader.h"
#include "GUI/Components/Rectangle.h"
#include "GUI/Data/ColorData.h"
#include "GUI/TileEngine/TileEngine.h"
#include "GUI/TileEngine/TileImage.h"
#include "GUI/TileEngine/TileSet.h"
#include "GUI/Visual/EventHandler.h"
#include <cstdlib>

using namespace gui::components;
using namespace gui;

namespace humbug {
  TileScreen::TileScreen( FileLoader& loader, CCanvas* background) :
      Screen(background),
      m_Loader(loader),
      m_pArialfont(NULL),
      m_inScreenDelta(0),
      m_pTileEngine(NULL){
      dbgOut(__FUNCTION__ << " " << this);
  }

  TileScreen::~TileScreen(void){
      delete m_pTileEngine;
      dbgOut(__FUNCTION__ << " " << this);
  }

  bool TileScreen::OnInit( int argc, char* argv[] ){
      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

      // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
      m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
      SDL_Surface* tmpfsurf = ( m_Loader.FL_LOADIMG("Intro/TileScreenBg.png") );
      m_pBackground.reset( new CCanvas( tmpfsurf ) );

      m_Loader.FreeLast();


	  SDL_Surface* loadsurf;
	  SDL_Surface* tmpsurf;
	  tmpsurf = ( loadsurf = m_Loader.FL_LOADIMG("Moo.png") );

	  // delete loadsurf;
	  CCanvas tmpCanvas(tmpsurf);
	  CCanvas* testCanvas = CCanvas::CreateRGBCompatible(NULL, 1024 * 5, 768 - 320);
	  //tmpCanvas->SetColorKey(CColor::Black());

	  testCanvas->Blit( tmpCanvas.GetDimension(), tmpCanvas, tmpCanvas.GetDimension() );
	  //m_pBackground = testCanvas;
	  m_pBackground.reset( testCanvas );

	  //delete tmpsurf;
	  //SDL_FreeSurface( loadsurf );
	  m_Loader.FreeLast();


      CTileSet* tileSet = NULL;
      CTileImageSetup tilesetup;
      tilesetup.TileSetName = "Tiles1";
      tilesetup.TileWidth = 64;
      tilesetup.TileHeight = 64;
      tilesetup.TileCountX = 4;
      tilesetup.TileCountY = 1;
      tilesetup.TransparentX = 0;
      tilesetup.TransparentY = 0;
      tilesetup.Sequences = 0;
      tileSet = new CTileSet( m_pMainCanvas, new CTileImage(m_Loader, "Tiles1.bmp", tilesetup),
              m_pBackground.get(), CRectangle(0, 0, 1024, 768 - 320) );

      m_pTileEngine = new CTileEngine( m_pMainCanvas, m_pBackground.get() );
      m_pTileEngine->AddTileSet(tileSet);
      CTileEngine& eng = (*m_pTileEngine);
	  m_pTileEngine->GetTileSet("Tiles1")->GetTileImage()->ShowTiles( m_pBackground.get() );
	  /*(*m_pTileEngine)["Tiles1"]->GetTileImage()->ShowTiles( m_pBackground.get() );
      CTile tile1 = eng["Tiles1"]->CreateTile(0);
      CTile tile2 = eng["Tiles1"]->CreateTile(1);
      CTile tile3 = eng["Tiles1"]->CreateTile(2);
      CTile tile4 = eng["Tiles1"]->CreateTile(3);*/
	  CTile tile1 = eng.GetTileSet("Tiles1")->CreateTile(0);
	  CTile tile2 = eng.GetTileSet("Tiles1")->CreateTile(1);
	  CTile tile3 = eng.GetTileSet("Tiles1")->CreateTile(2);
	  CTile tile4 = eng.GetTileSet("Tiles1")->CreateTile(3);

      for (int i = 0; i < 20; i += 4)
      {
          const int xdiff = 300;
          tile1.Draw( m_pBackground.get(), CPoint(xdiff * i, 300) );
          tile2.Draw( m_pBackground.get(), CPoint(xdiff * (i + 1), 300) );
          tile3.Draw( m_pBackground.get(), CPoint(xdiff * (i + 2), 300) );
          tile4.Draw( m_pBackground.get(), CPoint(xdiff * (i + 3), 300) );
      }
      m_pMainCanvas->AddUpdateRect( m_pBackground->GetDimension() );

	  return Screen::OnInit(argc, argv);
  } // OnInit

  /** TileScreen, OnIdle:
   *  Detailed description.
   *  @param ticks TODO
   * @return TODO
   */
  void TileScreen::OnIdle(int ticks){
      //m_pScroller->Scroll(4);
      //m_pSprMgr->OnIdle(ticks);

  }

  /** TileScreen, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void TileScreen::OnDraw(){
      static int coldelta = 0;

      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
      m_pMainCanvas->Lock();

	  //CRectangle& screenWithoutHud = m_pMainCanvas->GetDimension().Move(hudsize);
	  //m_pMainCanvas->Blit(screenrect, *m_pBackground, screenrect);
	  static int scrdel = 0;
	  scrdel += m_inScreenDelta;

	  //m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pBackground->GetDimension() );

	  //m_pMainCanvas->Blit( screenWithoutHud, *m_pBackground, screenWithoutHud + CPoint(scrdel, 0) );
	  m_pMainCanvas->Blit( m_pMainCanvas->GetDimension(), *m_pBackground, m_pMainCanvas->GetDimension() + CPoint(scrdel, 0));
      //m_pBackground->RenderCopy(m_pMainCanvas->GetDimension().SDLRectCP(), (m_pMainCanvas->GetDimension() + CPoint(scrdel, 0)).SDLRectCP());
      if (m_inScreenDelta != 0) {
		  m_pMainCanvas->AddUpdateRect( CRectangle( 0, 0, m_pMainCanvas->GetWidth(),
		  //m_pMainCanvas->GetHeight() - m_pHud->GetHeight() ) );
		  	  m_pMainCanvas->GetHeight() - 200 ) );
	  }

      CRectangle frect(700, 500, 185, 185);
      SDL_Color* wavemap = ColorData::Instance()->Wavemap();
      int index = (coldelta * 2 & 63);

      //m_pMainCanvas->FillRect( frect, mcol );
      SDL_Color& fcol = wavemap[index];
      m_pMainCanvas->FillRect( frect, CColor(fcol.r, fcol.g, fcol.b) );
      m_pMainCanvas->AddUpdateRect(frect);

      coldelta++;

      if (coldelta > 64) {
          coldelta = 0;
      }

      m_pMainCanvas->Unlock();
  } // OnDraw

  /** TileScreen, OnUpdate:
   *  Detailed description.
   *  @return TODO
   */
  void TileScreen::OnUpdate(){
      Screen::OnUpdate();
  }

  /** TileScreen, OnMouseMove:
   *  Detailed description.
   *  @param x TODO
   * @param y TODO
   * @param relx TODO
   * @param rely TODO
   * @param bLeft TODO
   * @param bRight TODO
   * @param bMiddle TODO
   * @return TODO
   */
  void TileScreen::OnMouseMove( Uint16 x, Uint16 y, Sint16 relx, Sint16 rely, bool bLeft, bool bRight, bool bMiddle ){
      m_inScreenDelta++;
  }

  /** TileScreen, OnEvent:
   *  Detailed description.
   *  @param pEvent TODO
   * @return TODO
   */
  void TileScreen::OnEvent( SDL_Event* pEvent ){
      switch(pEvent->type)
      {
      case SDL_KEYDOWN:                    //key press
      {
          //key press
          //OnKeyDown(pEvent->key.keysym.sym, pEvent->key.keysym.mod, pEvent->key.keysym.unicode);
          SDL_Keycode sym = pEvent->key.keysym.sym;
		  if( sym == SDLK_a )   {
			  // toggle console
			  m_inScreenDelta++;
		  }
		  else if( sym == SDLK_d )   {
			  // toggle console
			  m_inScreenDelta--;
		  }
		  else if( sym == SDLK_x )   {
			  //CApplication::GetApplication()->SendMessageQ(MsgID,Parm1,Parm2,Parm3,Parm4)
			  //SendMessageQ(MSGID_QuitApp);
			  CApplication::GetApplication()->SendMessageQ(gui::CEventHandler::MSGID_QuitApp);
		  }
          break;
      }

      default:
          break;
      }     // switch
  } // OnEvent
}
