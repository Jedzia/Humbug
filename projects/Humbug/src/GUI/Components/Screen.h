#ifndef SCREEN_H
#define SCREEN_H
#include "../Visual/Hookable.h"
#include "../Visual/MessageHandler.h"
#include "GUI/Components/MainCanvas.h"

//class CMainCanvas;
//class CCanvas;

class Screen : public Hookable/*, CMessageHandler*/ {
public:

    Screen(CCanvas *background);
    ~Screen();

    virtual void OnUpdate();
    virtual void OnDraw() = 0;

    //virtual bool OnInit( int argc,char* argv[] );
protected:
    virtual bool OnInit( int argc,char* argv[] );
private:
    GroupId GetGroupID();


    CMainCanvas *m_pMainScreen;
	int i;
};

#endif // SCREEN_H
