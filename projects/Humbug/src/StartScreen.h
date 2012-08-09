#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "GUI/Components/Screen.h"
#include "boost/smart_ptr/scoped_ptr.hpp"

class FileLoader;
class CCanvas;
class CText;
class CTextScroller;
class CSprite;
class CSpriteManager;

class StartScreen : public Screen {
public:

    StartScreen(FileLoader& loader, CCanvas *background);
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
    CColor mcol;
    TTF_Font *m_pArialfont;
    boost::shared_ptr<CCanvas> m_pBackground;
    boost::scoped_ptr<CText> m_pScrollText;
    boost::scoped_ptr<CTextScroller> m_pScroller;
    boost::scoped_ptr<CSpriteManager> m_pSprMgr;
};

#endif // STARTSCREEN_H
