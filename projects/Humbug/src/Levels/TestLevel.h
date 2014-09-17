/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the TestLevel.h class.
 * \folder     $(folder)
 * \file       TestLevel.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_LEVELS_TESTLEVEL_H
#define HUMBUG_LEVELS_TESTLEVEL_H
#include <GUI/Components/Screen.h>
#include <boost/smart_ptr/scoped_ptr.hpp>

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;

namespace gui {
  namespace components {
    class CCanvas;
    class CSeamlessImage;
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
  namespace levels {
    class TestLevel : public gui::components::Screen {
public:

        TestLevel(FileLoader& loader, gui::components::CCanvas* background);
        ~TestLevel();

        virtual bool OnInit( int argc, char* argv[] );
        virtual void OnIdle(int ticks);

        virtual void OnDraw();

        virtual void OnUpdate();

private:

        struct TestLevelImpl;
        boost::scoped_ptr<TestLevelImpl> pimpl_;

        FileLoader& m_Loader;
        Uint8 x;
        gui::components::CColor mcol;
        TTF_Font* m_pArialfont;
        boost::shared_ptr<gui::components::CCanvas> m_pBackground;
        boost::scoped_ptr<gui::components::CText> m_pScrollText;
        boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
        boost::scoped_ptr<gui::CSpriteManager> m_pSprMgr;
        gui::components::CSeamlessImage* m_pSprite;
    };
  }
}

#endif // HUMBUG_LEVELS_TESTLEVEL_H
