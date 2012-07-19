#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "GUI/Components/Screen.h"

class FileLoader;

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
    CColor mcol;
};

#endif // STARTSCREEN_H
