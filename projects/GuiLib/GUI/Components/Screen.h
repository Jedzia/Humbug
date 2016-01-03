#ifndef HUMBUG_GUI_COMPONENTS_SCREEN_H
#define HUMBUG_GUI_COMPONENTS_SCREEN_H
#include "../Visual/Application.h"
#include "../Visual/Hookable.h"
#include "../Visual/HookableManager.h"
#include "../Visual/MessageHandler.h"
//#include "GUI/Components/MainCanvas.h"
#include "../Components/Canvas.h"
#include "../Detail/Signals.h"

//class CMainCanvas;
//class CCanvas;
class FileLoader;
//class CCanvas;


namespace gui {
namespace components {

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

    Screen(CCanvas *background, bool usesSDL2Render = false);
    virtual ~Screen();

    virtual void OnUpdate();
    virtual void OnDraw() = 0;

    //virtual bool OnInit( int argc,char* argv[] );
protected:
    bool OnInit( int argc,char* argv[] ) override;
private:
    GroupId GetGroupID() override;

    void OnIdle( int ticks ) override;
	virtual void OnEvent(SDL_Event* pEvent);
    void OnConnect() override;
    void OnDisconnect() override;

    //CMainCanvas *m_pMainScreen;

	bs::connection m_conDraw;
    bs::connection m_conUpdate;
	bs::connection m_conEvt;
	int i;
    bool m_bUsesSDL2Render;
};

} // namespace components
} // namespace gui

#endif // HUMBUG_GUI_COMPONENTS_SCREEN_H
