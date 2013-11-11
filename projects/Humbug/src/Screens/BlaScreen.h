/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the BlaScreen.h class.
 * \folder     $(folder)
 * \file       BlaScreen.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_SCREENS_BlaScreen_H
#define HUMBUG_SCREENS_BlaScreen_H
#include "GUI/Components/Screen.h"
#include "boost/smart_ptr/scoped_ptr.hpp"

namespace gui {
  class CSprite;
  class CSpriteManager;
  namespace components {
    class CCanvas;
    class CText;
    class CTextScroller;
  }
}
class FileLoader;

namespace humbug {

	class Hud;
	class gui::CSprite;

  class BlaScreen : public gui::components::Screen {
public:

      BlaScreen(FileLoader& loader, gui::components::CCanvas* background);
      ~BlaScreen();

      virtual bool OnInit( int argc, char* argv[] );
      virtual void OnIdle(int frameNumber);

      virtual void OnDraw();

      virtual void OnUpdate();

private:

      struct BlaScreenImpl;
      boost::scoped_ptr<BlaScreenImpl> pimpl_;

      FileLoader& m_Loader;
      Uint8 x;
      gui::components::CColor mcol;
      TTF_Font* m_pArialfont;
      boost::shared_ptr<gui::components::CCanvas> m_pBackground;
      boost::scoped_ptr<gui::components::CText> m_pScrollText;
      boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
      boost::scoped_ptr<gui::CSpriteManager> m_pSprMgr;
	  Hud* m_pHud;
	  gui::CSprite* m_pSprite;

  };
}

#endif // ifndef HUMBUG_SCREENS_BlaScreen_H
