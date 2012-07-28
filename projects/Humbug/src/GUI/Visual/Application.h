//include guards
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

//include message handler(base class)
#include "MessageHandler.h"
#include "boost/signals.hpp"
#include "boost/signals/connection.hpp"

class Hookable;
class CMainCanvas;

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
    typedef boost::signal<void (int)> signal_type_idle;
    typedef signal_type_idle::slot_type slot_type_idle;
    
	typedef boost::signal<void (int, char**)> signal_type_init;
    typedef signal_type_init::slot_type slot_type_init;

	//constructor
	CApplication();

	//destructor
	virtual ~CApplication();

    CMainCanvas* GetMainCanvas() const { return m_pMainCanvas; }

    // Signal handling
    boost::signals::connection ConnectOnIdle(const slot_type_idle& s);
    boost::signals::connection ConnectOnDraw(const slot_type_event& s);
    boost::signals::connection ConnectOnUpdate(const slot_type_event& s);

	//initialization
	virtual bool OnInit(int argc,char* argv[]);

	//event occurrence
	virtual void OnEvent(SDL_Event* pEvent);

	//idle behavior
	virtual void OnIdle(int frameNumber);

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

    //set singleton pointer
    static void SetApplication(CApplication* pTheApp);
    CMainCanvas* m_pMainCanvas;
protected:
    //initialization
    virtual bool OnPreInit(int argc,char* argv[]) = 0;
    virtual bool OnPostInit(int argc,char* argv[]) = 0;
    //main display surface
    void SetMainCanvas(CMainCanvas* val) { m_pMainCanvas = val; }
};

#endif //#ifndef __APPLICATION_H__
