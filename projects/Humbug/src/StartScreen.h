#ifndef STARTSCREEN_H
#define STARTSCREEN_H
#include "GUI/Components/Screen.h"

class StartScreen : public Screen {
public:

    StartScreen(CCanvas *background);
    ~StartScreen();

    const char *language(int x) const;

    //virtual GroupId GetGroupID();

    virtual bool OnInit( int argc,char* argv[] );
    virtual void OnIdle();

    virtual void OnDraw();

    virtual void OnUpdate();

private:
	Uint8 x;
    CColor mcol;
};

#endif // STARTSCREEN_H
