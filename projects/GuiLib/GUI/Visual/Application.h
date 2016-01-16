//include guards
#ifndef HUMBUG___APPLICATION_H__
#define HUMBUG___APPLICATION_H__

//include message handler(base class)
#include "MessageHandler.h"
#include "../Detail/Signals.h"
#include "../Components/MainCanvas.h"
#define slots

union SDL_Event;

namespace gui {

class CConsole;

/** @class CMaster:
*  Represents a master event provider.
*  This component provides OnIdle, OnDraw, OnUpdate and OnEvent signals and the ability to
*  connect to them via the corresponding ConnectXXX methods and to raise them with the
*  RaiseXXX methods.
*/
class CMaster
{
    // * * * * * * * * * * * * * * * * * * * *
    // * signal type definitions and signals *
    // * * * * * * * * * * * * * * * * * * * *

    typedef bs::signal<void(int)> signal_type_idle;
    typedef bs::signal<void()> signal_type_event;
    typedef bs::signal<void(SDL_Event*)> signal_type_sdlevent;

    signal_type_event m_sigOnUpdate;
    signal_type_idle m_sigOnIdle;
    signal_type_event m_sigOnDraw;
    signal_type_sdlevent m_sigOnEvent;

public:
    /// <summary>
    /// Finalizes an instance of the <see cref="CMaster"/> class.
    /// </summary>
    virtual ~CMaster()
    {
    }

    /** Retrieve the hosting canvas.
    *  Use this to get the parent/to-paint-on object like the MainCanvas or a
    *  Screen hosting subscreens.
    *  @return the parent or hosting canvas. This should never be null (see. HookableManager(CMaster* master) ).
    */
    virtual gui::components::CMainCanvas* GetMainCanvas() const = 0;


    // * * * * * * * * * * * * * * * * * * *
    // * slots and connectors              *
    // * * * * * * * * * * * * * * * * * * *
    typedef signal_type_idle::slot_type slot_type_idle;
    bs::connection ConnectOnIdle(const slot_type_idle& s);

    typedef signal_type_event::slot_type slot_type_event;
    bs::connection ConnectOnDraw(const slot_type_event& s);
    bs::connection ConnectOnUpdate(const slot_type_event& s);
    
    typedef signal_type_sdlevent::slot_type slot_type_sdlevent;
    bs::connection ConnectOnEvent(const slot_type_sdlevent& s);

protected:
    /** Raise the Idle event.
    *  @param ticks The ticks parameter forwarded to the OnIdle() event.
    */
    void RaiseOnIdle(int ticks)
    {
        m_sigOnIdle(ticks);
    }

    /** Raise the Draw event.
    */
    void RaiseOnDraw()
    {
        m_sigOnDraw();
    }

    /** Raise the Update event.
    */
    void RaiseOnUpdate()
    {
        m_sigOnUpdate();
    }

    /** Raise the Event-Loop event.
    *  @param sdl_event The SDL_Event parameter forwarded to the OnEvent() event.
    */
    void RaiseOnEvent(SDL_Event* sdl_event)
    {
        m_sigOnEvent(sdl_event);
    }
};

class CConnectable
{
public:
    virtual ~CConnectable()
    {
    }

    typedef bs::signal<void(int, char**)> signal_type_init;
    typedef signal_type_init::slot_type slot_type_init;

    //typedef bs::signal<void(SDL_Keycode sym, Uint16 mod)> signal_type_keydown;
    //typedef signal_type_keydown::slot_type slot_type_keydown;

    virtual bs::connection ConnectOnInit(const slot_type_init& s) = 0;
    //virtual bs::connection ConnectOnKeyDown(const slot_type_keydown& s) = 0;

};

/*
	==CApplication==
	Singleton.
	Base class for all other application classes.
*/
class CApplication : public CMessageHandler, public CConnectable, public CMaster
{
public:

	// bool OnInit(int argc,char* argv[])
	typedef bs::signal<void(int, char**)> signal_type_init;
    typedef signal_type_init::slot_type slot_type_init;

	//constructor
	CApplication();

	//destructor
	virtual ~CApplication();

	gui::components::CMainCanvas* GetMainCanvas() const override
	{ return m_pMainCanvas; }

    // Signal handling
    /*bs::connection ConnectOnIdle(const slot_type_idle& s) override;
    bs::connection ConnectOnDraw(const slot_type_event& s) override;
    bs::connection ConnectOnUpdate(const slot_type_event& s) override;
    bs::connection ConnectOnEvent(const slot_type_sdlevent& s) override;*/

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
    // get the FPS count.
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
