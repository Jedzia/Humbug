#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "GUI/Components/Screen.h"

class FileLoader;
class CCanvas;

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
};

#endif // STARTSCREEN_H
