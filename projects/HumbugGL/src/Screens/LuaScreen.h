/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the LuaScreen.h class.
 * \folder     $(folder)
 * \file       LuaScreen.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUGGL_SCREENS_LUASCREEN_H
#define HUMBUGGL_SCREENS_LUASCREEN_H
#include "GUI/Components/Screen.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>

namespace gui {
  namespace components {
    class CCanvas;
    class CText;
    class CTextScroller;
  }
}
class FileLoader;
namespace gui {
  class CSprite;
  class CSpriteManager;
}

namespace humbug {
  namespace screens {

	  struct World
	  {
		  int ScreenX;
		  int ScreenY;

		  int FPS;
	  };


    class LuaScreen : public gui::components::Screen {
public:

        LuaScreen(FileLoader& loader, gui::components::CCanvas* background);
        ~LuaScreen();

        virtual bool OnInit( int argc, char* argv[] );

        virtual void OnIdle(int ticks);

        virtual void OnDraw();

        virtual void OnUpdate();

private:

        struct LuaScreenImpl;
        boost::scoped_ptr<LuaScreenImpl> pimpl_;

        FileLoader& m_Loader;
        Uint8 x;
        gui::components::CColor mcol;
        TTF_Font* m_pArialfont;
        boost::shared_ptr<gui::components::CCanvas> m_pBackground;
        boost::scoped_ptr<gui::components::CText> m_pScrollText;
        boost::ptr_vector<gui::components::CText> m_pvecTexts;
        boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
        boost::scoped_ptr<gui::CSpriteManager> m_pSprMgr;
		gui::CSprite* m_pSprEye;
        //WavyTextFloat mtextfloat;
		World world;
    };
  }
}
#endif // HUMBUGGL_SCREENS_LUASCREEN_H
