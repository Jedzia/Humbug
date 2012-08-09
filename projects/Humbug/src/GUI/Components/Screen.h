#ifndef SCREEN_H
#define SCREEN_H
#include "../Visual/Hookable.h"
#include "../Visual/MessageHandler.h"
#include "GUI/Components/MainCanvas.h"
#include "boost/signals.hpp"

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

    virtual void OnIdle( int frameNumber );

    virtual void OnConnect();
    virtual void OnDisconnect();

    CMainCanvas *m_pMainScreen;

    boost::signals::connection m_conDraw;
    boost::signals::connection m_conUpdate;
	int i;
};

#endif // SCREEN_H
