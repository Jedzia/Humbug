//include guards
#ifndef HUMBUG___APPLICATION_H__
#define HUMBUG___APPLICATION_H__

//include message handler(base class)
#include "MessageHandler.h"
#include "boost/signals.hpp"
#include "boost/signals/connection.hpp"
#include "../Components/MainCanvas.h"

union SDL_Event;

namespace gui {

class CConsole;
class SdlForwarder
{
	int bla;
};

/*
	==CApplication==
	Singleton.
	Base class for all other application classes.
*/
class CApplication : public CMessageHandler
{
public:
    // signal types
    typedef boost::signal<void ()> signal_type_event;
    typedef signal_type_event::slot_type slot_type_event;

	//SDL_Event* pEvent
	typedef boost::signal<void (SDL_Event*)> signal_type_sdlevent;
	typedef signal_type_sdlevent::slot_type slot_type_sdlevent;

    typedef boost::signal<void (int)> signal_type_idle;
    typedef signal_type_idle::slot_type slot_type_idle;

	// bool OnInit(int argc,char* argv[])
	typedef boost::signal<void (int, char**)> signal_type_init;
    typedef signal_type_init::slot_type slot_type_init;

	//constructor
	CApplication();

	//destructor
	virtual ~CApplication();

	gui::components::CMainCanvas* GetMainCanvas() const { return m_pMainCanvas; }

    // Signal handling
    boost::signals::connection ConnectOnIdle(const slot_type_idle& s);
    boost::signals::connection ConnectOnDraw(const slot_type_event& s);
	boost::signals::connection ConnectOnUpdate(const slot_type_event& s);
	boost::signals::connection ConnectOnEvent(const slot_type_sdlevent& s);

	//initialization
	virtual bool OnInit(int argc,char* argv[]);

	//event occurrence
	virtual void OnEvent(SDL_Event* pEvent);

	//idle behavior
	virtual void OnIdle(int ticks);

   	//update loop
	virtual void Update();

	//cleanup
    virtual void OnExiting() = 0;
	virtual void OnExit();

	//execution of application
	static int Execute(int argc,char* argv[]);

	//get singleton
	static CApplication* GetApplication();
    static Uint32 ShownFrames() { return m_iShownFrames; }
	static int FramesCap() { return m_iFramesCap; }

private:
    // Frames per second
    static int m_iFramesCap;
	static Uint32 m_iShownFrames;
    //singleton pointer
    static CApplication* s_pTheApplication;
    //last ticks
    static Uint32 m_uiFPSLastTime;

    signal_type_event m_sigOnUpdate;
    signal_type_idle m_sigOnIdle;
	signal_type_event m_sigOnDraw;
	signal_type_sdlevent m_sigOnEvent;

    //set singleton pointer
    static void SetApplication(CApplication* pTheApp);
    gui::components::CMainCanvas* m_pMainCanvas;
protected:
    //initialization
    virtual bool OnPreInit(int argc,char* argv[]) = 0;
    virtual bool OnPostInit(int argc,char* argv[]) = 0;
    //main display surface
    void SetMainCanvas(gui::components::CMainCanvas* val) { m_pMainCanvas = val; }
	CConsole* m_pConsole;

};

} // namespace gui

#endif //#ifndef HUMBUG___APPLICATION_H__
