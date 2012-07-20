#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "GUI/Components/Screen.h"
#include "boost/smart_ptr/scoped_ptr.hpp"

class FileLoader;
class CCanvas;
class CText;
class CTextScroller;

class StartScreen : public Screen {
public:

    StartScreen(FileLoader& loader, CCanvas *background);
    ~StartScreen();

    const char *language(int x) const;

    //virtual GroupId GetGroupID();

    virtual bool OnInit( int argc,char* argv[] );
    virtual void OnIdle();

    virtual void OnDraw();

    virtual void OnUpdate();

private:
    FileLoader& m_Loader;
	Uint8 x;
    int m_iUpdateTimes;
    CColor mcol;
    TTF_Font *m_pArialfont;
    CCanvas* m_pBackground;
    CText *m_pScrollText;
    CTextScroller *m_pScroller;
    //boost::scoped_ptr<CCanvas> m_pScrollText;

};

#endif // STARTSCREEN_H
