/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the ScrollerLevelA.h class.
 * \folder     $(folder)
 * \file       ScrollerLevelA.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_LEVELS_ScrollerLevelA_H
#define HUMBUG_LEVELS_ScrollerLevelA_H
#include <GUI/Components/Screen.h>
#include <boost/smart_ptr/scoped_ptr.hpp>
#include "HumbugShared/GameObjects/Player.h"

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

namespace gui {
  namespace components {
    class CCanvas;
    class CSeamlessImage;
    class CImage;
    class CText;
    class CTextScroller;
  }
}
namespace gui {
  class CSprite;
  class CSpriteManager;
}
class FileLoader;

namespace humbug {
    class DebugOverlay;
    class PlayerKeys4;

  namespace levels {
    class ScrollerLevelA : public gui::components::Screen {
public:

        ScrollerLevelA(FileLoader& loader, gui::components::CCanvas* background);
        ~ScrollerLevelA();

        bool OnInit( int argc, char* argv[] ) override;
        void OnIdle(int ticks) override;
        void OnDraw() override;
        void OnUpdate() override;
        void OnEvent(SDL_Event* pEvent) override;
        void OnKeyDown(SDL_Keycode sym, Uint16) override;

    private:

        struct ScrollerLevelAImpl;
        boost::scoped_ptr<ScrollerLevelAImpl> pimpl_;

        FileLoader& m_Loader;
        Uint8 x;
        int m_iTicks;
        gui::components::CColor mcol;
        TTF_Font* m_pArialfont;
        boost::scoped_ptr<DebugOverlay> m_pOverlay;
        boost::scoped_ptr<gui::components::CCanvas> m_pBackground;
        boost::scoped_ptr<gui::components::CCanvas> m_pBlue;
        boost::scoped_ptr<gui::components::CImage> m_pBanding1;
        boost::scoped_ptr<gui::components::CImage> m_pBanding2;
        boost::scoped_ptr<gui::components::CText> m_pScrollText;
        boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
        boost::scoped_ptr<gui::CSpriteManager> m_pSprMgr;
        gui::components::CSeamlessImage* m_pSeamlessImage;
        gob::Player m_player;

    };
  }
}

#endif // HUMBUG_LEVELS_ScrollerLevelA_H
