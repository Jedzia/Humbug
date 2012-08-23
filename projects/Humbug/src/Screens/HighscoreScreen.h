#ifndef HUMBUG_SCREENS_HIGHSCORESCREEN_H
#define HUMBUG_SCREENS_HIGHSCORESCREEN_H
#include "GUI/Components/Screen.h"
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

class FileLoader;
class CCanvas;
class CText;
class CTextScroller;
class CSprite;
class CSpriteManager;

class HighscoreScreen : public Screen {
public:

    HighscoreScreen(FileLoader& loader, CCanvas *background);
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
    CColor mcol;
    TTF_Font *m_pArialfont;
    boost::shared_ptr<CCanvas> m_pBackground;
    boost::scoped_ptr<CText> m_pScrollText;
    boost::ptr_vector<CText> m_pvecTexts;
    boost::scoped_ptr<CTextScroller> m_pScroller;
    boost::scoped_ptr<CSpriteManager> m_pSprMgr;
    //WavyTextFloat mtextfloat;
};

#endif // HUMBUG_SCREENS_HIGHSCORESCREEN_H
