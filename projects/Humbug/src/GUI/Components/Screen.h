#ifndef HUMBUG_GUI_COMPONENTS_SCREEN_H
#define HUMBUG_GUI_COMPONENTS_SCREEN_H
#include "../Visual/Hookable.h"
#include "../Visual/MessageHandler.h"
//#include "GUI/Components/MainCanvas.h"
#include "GUI/Components/Canvas.h"
#include <boost/signals.hpp>

//class CMainCanvas;
//class CCanvas;
class FileLoader;
//class CCanvas;


template <typename T>
class ScreenCreator : public HookCreator {
    FileLoader& m_loader;
    CCanvas *m_background;
public:

    ScreenCreator(FileLoader& loader, CCanvas *background) 
        : m_loader(loader), m_background(background)
    {};
    Hookable* Create(){
        return new T(m_loader, m_background);
    }
};

class Screen : public Hookable/*, CMessageHandler*/ {
public:

    Screen(CCanvas *background);
    virtual ~Screen();

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

    //CMainCanvas *m_pMainScreen;

    boost::signals::connection m_conDraw;
    boost::signals::connection m_conUpdate;
	int i;
};

#endif // HUMBUG_GUI_COMPONENTS_SCREEN_H
