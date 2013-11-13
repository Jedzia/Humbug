/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TileScreen.h class.
 * \folder     $(folder)
 * \file       TileScreen.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_SCREENS_TileScreen_H
#define HUMBUG_SCREENS_TileScreen_H
#include "GUI/Components/Screen.h"
#include "boost/smart_ptr/scoped_ptr.hpp"

namespace gui {
  class CSprite;
  class CSpriteManager;
  class CTileEngine;
  namespace components {
    class CCanvas;
    class CText;
    class CTextScroller;
  }
}
class FileLoader;

namespace humbug {

  class TileScreen : public gui::components::Screen {
public:

      TileScreen(FileLoader& loader, gui::components::CCanvas* background);
      ~TileScreen();

      virtual bool OnInit( int argc, char* argv[] );
      virtual void OnIdle(int frameNumber);

      virtual void OnDraw();

      virtual void OnUpdate();
	  virtual void OnEvent(SDL_Event* pEvent);

	  //mouse move (Todo: that is not used yet, do it per OnEvent oder inheritance ).
	  void OnMouseMove(Uint16 x,Uint16 y,Sint16 relx,Sint16 rely,bool bLeft,bool bRight,bool bMiddle);

private:

      struct TileScreenImpl;
      boost::scoped_ptr<TileScreenImpl> pimpl_;

      FileLoader& m_Loader;
	  int m_inScreenDelta;
      Uint8 x;
      gui::components::CColor mcol;
      TTF_Font* m_pArialfont;
      boost::shared_ptr<gui::components::CCanvas> m_pBackground;
      boost::scoped_ptr<gui::components::CText> m_pScrollText;
      boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
      boost::scoped_ptr<gui::CSpriteManager> m_pSprMgr;

	  gui::CTileEngine* m_pTileEngine;

  };
}

#endif // ifndef HUMBUG_SCREENS_TileScreen_H
