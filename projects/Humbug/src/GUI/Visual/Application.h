//include guards
#ifndef __APPLICATION_H__
#define __APPLICATION_H__

//include message handler(base class)
#include "MessageHandler.h"
class Hookable;

/*
	==CApplication==
	Singleton.
	Base class for all other application classes.
*/
class CApplication : public CMessageHandler
{
private:
    // Frames per second
    static int m_iFramesCap;
	//singleton pointer
	static CApplication* s_pTheApplication;
    //last ticks
    static Uint32 m_uiFPSLastTime;

	//set singleton pointer
	static void SetApplication(CApplication* pTheApp);
protected:
    //initialization
    virtual bool OnPreInit(int argc,char* argv[]) = 0;
    virtual bool AfterInit(int argc,char* argv[]) = 0;

public:
	//constructor
	CApplication();

	//destructor
	virtual ~CApplication();

	//initialization
	virtual bool OnInit(int argc,char* argv[]);

	//event occurrence
	virtual void OnEvent(SDL_Event* pEvent);

	//idle behavior
	virtual void OnIdle();

   	//update loop
	virtual void Update();

	//cleanup
    virtual void OnExiting() = 0;
	virtual void OnExit();

	//execution of application
	static int Execute(int argc,char* argv[]);

	//get singleton
	static CApplication* GetApplication();
};

#endif //#ifndef __APPLICATION_H__
