#ifndef HUMBUG_SCREENS_STARTSCREEN_H
#define HUMBUG_SCREENS_STARTSCREEN_H
#include "GUI/Components/Screen.h"
#include <boost/smart_ptr/scoped_ptr.hpp>

namespace gui { namespace components {
	class CCanvas;
	class CText;
	class CTextScroller;
}}
class FileLoader;
class CSprite;
class CSpriteManager;

class StartScreen : public gui::components::Screen {
public:

    StartScreen(FileLoader& loader, gui::components::CCanvas *background);
    ~StartScreen();

    virtual bool OnInit( int argc,char* argv[] );
    virtual void OnIdle(int frameNumber);

    virtual void OnDraw();

    virtual void OnUpdate();

private:
    struct StartScreenImpl;
    boost::scoped_ptr<StartScreenImpl> pimpl_;

    FileLoader& m_Loader;
	Uint8 x;
    gui::components::CColor mcol;
    TTF_Font *m_pArialfont;
    boost::shared_ptr<gui::components::CCanvas> m_pBackground;
    boost::scoped_ptr<gui::components::CText> m_pScrollText;
    boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
    boost::scoped_ptr<CSpriteManager> m_pSprMgr;
};

#endif // HUMBUG_SCREENS_STARTSCREEN_H
