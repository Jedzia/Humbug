/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SimpleScreen.h class.
 * \folder     $(folder)
 * \file       SimpleScreen.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_SCREENS_SimpleScreen_H
#define HUMBUG_SCREENS_SimpleScreen_H
#include "GUI/Components/Screen.h"
#include "boost/smart_ptr/scoped_ptr.hpp"

class FileLoader;
namespace gui {
  class CSprite;
  class CSpriteManager;
  namespace components {
    class CCanvas;
    class CText;
    class CTextScroller;
  }
}

namespace humbug {
  class SimpleScreen : public gui::components::Screen {
public:

      SimpleScreen(FileLoader& loader, gui::components::CCanvas* background);
      ~SimpleScreen();

      virtual bool OnInit( int argc, char* argv[] );
      virtual void OnIdle(int ticks);

      virtual void OnDraw();

      virtual void OnUpdate();

private:

      struct SimpleScreenImpl;
      boost::scoped_ptr<SimpleScreenImpl> pimpl_;

      FileLoader& m_Loader;
      boost::shared_ptr<gui::components::CCanvas> m_pBackground;
  };
}

#endif // ifndef HUMBUG_SCREENS_SimpleScreen_H