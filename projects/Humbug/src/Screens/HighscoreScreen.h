#ifndef HUMBUG_SCREENS_HIGHSCORESCREEN_H
#define HUMBUG_SCREENS_HIGHSCORESCREEN_H
#include "GUI/Components/Screen.h"
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace gui { namespace components {
	class CCanvas;
	class CText;
	class CTextScroller;
}}
class FileLoader;
class CSprite;
class CSpriteManager;

class HighscoreScreen : public gui::components::Screen {
public:

    HighscoreScreen(FileLoader& loader, gui::components::CCanvas *background);
    ~HighscoreScreen();

    virtual bool OnInit( int argc,char* argv[] );
    virtual void OnIdle(int frameNumber);

    virtual void OnDraw();

    virtual void OnUpdate();

private:
    struct HighscoreScreenImpl;
    boost::scoped_ptr<HighscoreScreenImpl> pimpl_;

    FileLoader& m_Loader;
	Uint8 x;
    gui::components::CColor mcol;
    TTF_Font *m_pArialfont;
    boost::shared_ptr<gui::components::CCanvas> m_pBackground;
    boost::scoped_ptr<gui::components::CText> m_pScrollText;
    boost::ptr_vector<gui::components::CText> m_pvecTexts;
    boost::scoped_ptr<gui::components::CTextScroller> m_pScroller;
    boost::scoped_ptr<CSpriteManager> m_pSprMgr;
    //WavyTextFloat mtextfloat;
};

#endif // HUMBUG_SCREENS_HIGHSCORESCREEN_H
