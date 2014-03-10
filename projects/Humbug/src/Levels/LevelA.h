/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2013, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the LevelA.h class.
 * \folder     $(folder)
 * \file       LevelA.h
 * \date       2013-11-22
 * \author     Jedzia.
 *
 * modified    2013-11-22, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_SCREENS_LEVELA_H
#define HUMBUG_SCREENS_LEVELA_H
#include "GUI/Components/Screen.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include "../Screens/LuaScreen.h"

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
  class CTileEngine;
}

namespace humbug {
  namespace levels {

    class LevelA : public gui::components::Screen {
public:

        LevelA(FileLoader& loader, gui::components::CCanvas* background);
        ~LevelA();

        virtual bool OnInit( int argc, char* argv[] );

        virtual void OnIdle(int ticks);

        virtual void OnDraw();

        virtual void OnUpdate();

private:

        struct LevelAImpl;
        boost::scoped_ptr<LevelAImpl> pimpl_;

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
		// Todo: move world to a central place ( under game centric terms )
		screens::World world;
		boost::scoped_ptr<gui::CTileEngine> m_pTileEngine;
    };
  }
}
#endif // HUMBUG_SCREENS_LEVELA_H
