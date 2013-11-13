/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
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
#include "TileScreen.h"
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
#include "GUI/TileEngine/TileSet.h"
#include "GUI/TileEngine/TileImage.h"
#include "GUI/TileEngine/TileEngine.h"

using namespace gui;
using namespace gui::components;

namespace humbug {
  struct TileScreen::TileScreenImpl {
      //prv::EyeMover eyemover;
      //prv::WormMover wormmover;
      int x;
  };

  TileScreen::TileScreen( FileLoader& loader, CCanvas* background) :
      pimpl_(new TileScreen::TileScreenImpl ),
      Screen(background),
      m_Loader(loader),
      m_pArialfont(NULL),
      //m_iUpdateTimes(0),
      m_pScrollText(NULL),
      m_pScroller(NULL),
	  m_inScreenDelta(0),
	  m_pTileEngine(NULL),
      m_pSprMgr(new CSpriteManager){
      //,m_pSprEye(NULL),
      //m_pSprWormler(NULL)
      dbgOut(__FUNCTION__ << " " << this);
  }

  TileScreen::~TileScreen(void){
	  delete m_pTileEngine;
      //delete m_pScrollText;
      //delete m_pScroller;
      //delete m_pBackground;
      //delete m_pSprWormler;
      //delete m_pSprEye;
      dbgOut(__FUNCTION__ << " " << this);
  }

/*GroupId TileScreen::GetGroupID()
   {
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
   }*/
  bool TileScreen::OnInit( int argc, char* argv[] ){
      // Master()->GetMainCanvas();
      CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();

      //m_pBackground = CCanvas::CreateRGBCompatible(NULL, 1024, 768 - 320);
      //m_pBackground = CCanvas::CreateRGBCompatible(NULL, NULL, NULL);
      // Todo: c:\program files\graphviz 2.28\bin\LIBFREETYPE-6.DLL copy from DEPS
	  m_pArialfont = m_Loader.FL_LOADFONT("Fonts/ARIAL.TTF", 24);
      mcol = CColor::White();
      SDL_Surface* tmpfsurf = SDL_DisplayFormatAlpha( m_Loader.FL_LOADIMG("Intro/TileScreenBg.png") );
	  m_pBackground.reset( new CCanvas( tmpfsurf ) );

	  //CCanvas tmpCanvas( tmpfsurf );
	  m_Loader.FreeLast();




	  CTileSet* tileSet = NULL;
	  CTileImageSetup tilesetup;
	  tilesetup.BitmapIdentifier = "Tiles1";
	  tilesetup.TileWidth = 64;
	  tilesetup.TileHeight = 64;
	  tilesetup.TileCountX = 4;
	  tilesetup.TileCountY = 1;
	  tilesetup.TransparentX = 0;
	  tilesetup.TransparentY = 0;
	  tilesetup.Sequences = 0;
	  tileSet = new CTileSet( m_pMainCanvas, new CTileImage(m_Loader, "Tiles1.bmp", tilesetup),
		  m_pBackground.get(), CRectangle(0, 0, 1024, 768 - 320) );


	  m_pTileEngine = new CTileEngine(m_pMainCanvas, m_pBackground.get());
	  m_pTileEngine->AddTileSet(tileSet);
	  CTileEngine& eng = (*m_pTileEngine);
	  (*m_pTileEngine)["Tiles1"]->GetTileImage()->ShowTiles(m_pBackground.get());
	  CTile tile1 = eng["Tiles1"]->CreateTile(0);
	  CTile tile2 = eng["Tiles1"]->CreateTile(1);
	  CTile tile3 = eng["Tiles1"]->CreateTile(2);
	  CTile tile4 = eng["Tiles1"]->CreateTile(3);

	  for (int i = 0; i < 20; i += 4)
	  {
		  const int xdiff = 300;
		  tile1.Draw( m_pBackground.get(), CPoint(xdiff * i, 300) );
		  tile2.Draw( m_pBackground.get(), CPoint(xdiff * (i + 1), 300) );
		  tile3.Draw( m_pBackground.get(), CPoint(xdiff * (i + 2), 300) );
		  tile4.Draw( m_pBackground.get(), CPoint(xdiff * (i + 3), 300) );
	  }



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

  /** TileScreen, OnIdle:
   *  Detailed description.
   *  @param frameNumber TODO
   * @return TODO
   */
  void TileScreen::OnIdle(int frameNumber){
      //m_pScroller->Scroll(4);
      //m_pSprMgr->OnIdle(frameNumber);
  }

  /** TileScreen, OnDraw:
   *  Detailed description.
   *  @return TODO
   */
  void TileScreen::OnDraw(){
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

  /** TileScreen, OnUpdate:
   *  Detailed description.
   *  @return TODO
   */
  void TileScreen::OnUpdate(){
      Screen::OnUpdate();
      x += 1 + (rand() << 21);
      mcol.SetR( rand() );
      mcol.SetG( rand() );
      mcol.SetB( rand() );
      //m_iUpdateTimes++;
  }

  void TileScreen::OnMouseMove( Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle )
  {
	  m_inScreenDelta++;
  }

  void TileScreen::OnEvent( SDL_Event* pEvent )
  {
	  switch(pEvent->type)
	  {
	  case SDL_KEYDOWN:                //key press
		  {
			  //key press
			  //OnKeyDown(pEvent->key.keysym.sym, pEvent->key.keysym.mod, pEvent->key.keysym.unicode);
			  if( pEvent->key.keysym.sym == SDLK_F1 ) {
				  //
				  m_inScreenDelta++;
				  int x = 0;
				  x++;
			  }
			  break;
		  }

	  default:
		  break;
	  } // switch

  }

}
