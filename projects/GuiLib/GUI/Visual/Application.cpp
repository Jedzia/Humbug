// Application.cpp: implementation of the CApplication class.
//
//////////////////////////////////////////////////////////////////////

#include "../../stdafx.h"
//
#include <stdlib.h>
#include <exception>
#include "Application.h"
#include "SdlInfo.h"
//#include "Hookable.h"
#include "../Components/MainCanvas.h"
#include <stdexcept>
#include "GUI/Visual/Console.h"
#include <HumbugLib/LogManager.h>

extern int bmain(int argc,char* argv[]);

namespace gui {

humbuglib::LogManager *mLogManager;

//singleton pointer
CApplication* CApplication::s_pTheApplication=NULL;
Uint32 CApplication::m_uiFPSLastTime=0;
int CApplication::m_iFramesCap = 30;
Uint32 CApplication::m_iShownFrames = 0;


//The timer
class Timer
{
private:
    //The clock time when the timer started
    int startTicks;

    //The ticks stored when the timer was paused
    int pausedTicks;

    //The timer status
    bool paused;
    bool started;

public:
    //Initializes variables
    Timer();

    //The various clock actions
    void start();
    void stop();
    void pause();
    void unpause();

    //Gets the timer's time
    int get_ticks();

    //Checks the status of the timer
    bool is_started();
    bool is_paused();
};

Timer::Timer()
{
    //Initialize the variables
    startTicks = 0;
    pausedTicks = 0;
    paused = false;
    started = false;
}

void Timer::start()
{
    //Start the timer
    started = true;

    //Unpause the timer
    paused = false;

    //Get the current clock time
    startTicks = SDL_GetTicks();
}

void Timer::stop()
{
    //Stop the timer
    started = false;

    //Unpause the timer
    paused = false;
}

void Timer::pause()
{
    //If the timer is running and isn't already paused
    if( ( started == true ) && ( paused == false ) )
    {
        //Pause the timer
        paused = true;

        //Calculate the paused ticks
        pausedTicks = SDL_GetTicks() - startTicks;
    }
}

void Timer::unpause()
{
    //If the timer is paused
    if( paused == true )
    {
        //Unpause the timer
        paused = false;

        //Reset the starting ticks
        startTicks = SDL_GetTicks() - pausedTicks;

        //Reset the paused ticks
        pausedTicks = 0;
    }
}

int Timer::get_ticks()
{
    //If the timer is running
    if( started == true )
    {
        //If the timer is paused
        if( paused == true )
        {
            //Return the number of ticks when the timer was paused
            return pausedTicks;
        }
        else
        {
            //Return the current time minus the start time
            return SDL_GetTicks() - startTicks;
        }
    }

    //If the timer isn't running
    return 0;
}

bool Timer::is_started()
{
    return started;
}

bool Timer::is_paused()
{
    return paused;
}


//set singleton pointer
void CApplication::SetApplication(CApplication* pTheApp)
{
	//ensure that there is not already an application
	if(s_pTheApplication!=NULL)
	{
		//more than one application!
		fprintf(stderr,"More than one CApplication created!\n");
		//exit
		exit(1);
	}
	//assign a value to the application
	s_pTheApplication=pTheApp;
}

//constructor
CApplication::CApplication():
	m_pConsole(NULL),
    CMessageHandler(NULL), m_pMainCanvas(NULL)
{
    //_CRT_DEBUG_BLOCK
    //_CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
	//set the application
	SetApplication(this);
	//initialize SDL
	if(SDL_Init(SDL_INIT_EVERYTHING)==-1)
	{
		//failure to initialize
		fprintf(stderr,"Failed to Init SDL:%s\n",SDL_GetError());
		//exit
		exit(1);
	}
	//set up SDL_Quit to be called during exit
	//atexit(SDL_Quit);
	//new std::string("MAUL!");
}

//destructor
CApplication::~CApplication()
{
    const char* explanation = "THIS IS ~CApplication.CPP Destructing.";
    _RPT1( _CRT_WARN, "\n\n%s:\n**************************************************************************\n", explanation );
    //_CrtDumpMemoryLeaks( );
    dbgOut(__FUNCTION__);
	if(mLogManager)
	{
		delete mLogManager;
	}
}

bool CApplication::OnInit(int argc,char* argv[])
{
	//by default, simply return true
	return(true);
}

//event occurrence
void CApplication::OnEvent(SDL_Event* pEvent)
{
	//by default, do nothing
	// m_sigOnEvent(pEvent);
	// signal handling is done in the main loop.
}

//idle behavior
void CApplication::OnIdle(int ticks)
{
	//by default, do nothing
	// Todo: make a DebugTiming sink std::cout << "---APP Before m_sigOnIdle---" << std::endl;
    m_sigOnIdle(ticks);
	// std::cout << "---APP After m_sigOnIdle---" << std::endl;

    //m_pMainCanvas->MainRenderClear();

	m_sigOnDraw();
	// std::cout << "---APP After m_sigOnDraw---" << std::endl;
	if (m_pConsole)
		m_pConsole->Draw();

    components::CRectangle frect(100, 200, 185, 185);
    //bool result = m_pMainCanvas->RenderFillRect(frect, components::CColor(33, 55, 99));
    //bool result = m_pMainCanvas->FillRect(frect, components::CColor(133, 55, 99));

	m_pMainCanvas->UpdateRects ( );
    m_pMainCanvas->MainRenderFinal();
}

//update loop
void CApplication::Update()
{
    m_sigOnUpdate();
    //SDL_Delay( 1 );

}


//cleanup
void CApplication::OnExit()
{
    //m_sigOnDraw.disconnect_all_slots();
    //m_sigOnIdle.disconnect_all_slots();
    //m_sigOnUpdate.disconnect_all_slots();
    //delete main canvas
	if (m_pConsole)
		delete m_pConsole;
    delete m_pMainCanvas;

    //atexit(SDL_Quit);
    SDL_Quit();
}

//execution of application
int CApplication::Execute(int argc,char* argv[])
{
	//check for an application
	if(GetApplication()==NULL)
	{
		//no application
		fprintf(stderr,"No application has been instantiated!\n");
		//return error code
		return(-1);
	}
	//attempt to initialize application
    if(!GetApplication()->OnPreInit(argc,argv))
    {
        //could not initialize
        fprintf(stderr,"Could not pre-initialize application!\n");
        //return
        return(-1);
    }
	if(!GetApplication()->OnInit(argc,argv))
	{
		//could not initialize
		fprintf(stderr,"Could not initialize application!\n");
		//return
		return(-1);
	}
    if(!GetApplication()->OnPostInit(argc,argv))
    {
        //could not initialize
        fprintf(stderr,"Could not initialize application!\n");
        //return
        return(-1);
    }


    if (!GetApplication()->GetMainCanvas())
    {
        //throw std::exception("No MainCanvas set!");
        //more than one application!
        fprintf(stderr,"No MainCanvas set!\n");
        //exit
        exit(1);
    }

    {
        // Get SDL Info
        //SdlInfo sdlInfo(SDL_GetVideoSurface());
        //LOGSTREAM << sdlInfo;
    }

    //The frame rate regulator
    Timer fps;
    //Uint32 curdelay = 0;
    int curdelay = 0;
    int frameNumber = 1;


	//event structure
	SDL_Event event;
	//forever

    Uint32 shownFrames = 0, loopFrames = 0;
	for(;;)
	{
        int delaynumber = 0;
        //Start the frame timer
        fps.start();

		//poll for an event
		if(SDL_PollEvent(&event)==1)
		{
			//check for a quit event
			if(event.type==SDL_QUIT) break;
			//event occurred
			GetApplication()->OnEvent(&event);
			GetApplication()->m_sigOnEvent(&event);
		}
		else
		{
			//std::cout << std::endl << "APPdiff:" << SDL_GetTicks() - m_uiFPSLastTime  << std::endl;
			//no event, so idle
			//GetApplication()->OnIdle(SDL_GetTicks()/60);
			//std::cout << "---APP BeforeIdle---" << std::endl;
			GetApplication()->OnIdle(frameNumber);
			//std::cout << "---APP AfterIdle---" << std::endl;
			shownFrames++;
            GetApplication()->Update();
			//std::cout << "---APP AfterUpdate---" << std::endl;
            frameNumber++;

            //Cap the frame rate
            int framecap = 1000 / m_iFramesCap;
            if( fps.get_ticks() <  framecap)
            {
                const int capfactor = 1;
                curdelay = framecap  - fps.get_ticks();
                //delaynumber++;
                //fprintf(stdout, "Curdelay: '%d', %d \n", curdelay, delaynumber);
                
                //SDL_Delay( curdelay );
                
                /*while (curdelay > 0)
                {
                    SDL_Delay( capfactor );
                    curdelay -= capfactor*2;
                    GetApplication()->Update();
                    loopFrames++;
                    //fprintf(stdout, "UPS: '%d'\n", framecap  - fps.get_ticks());
                }*/

            }
        }

        //for (int ii = 0; ii < 50 ; ii++)
        {
            //GetApplication()->Update();
        }

        loopFrames++;
        if((SDL_GetTicks() - m_uiFPSLastTime) >= 1000)
        {
            //ostringstream FPS;
            //FPS.str("");
            //FPS << ShownFrames;
            int delay = m_iShownFrames - m_iFramesCap;
            //fprintf(stdout, "FPS: '%d', Loop: '%d', Delay: '%d'\n", m_iShownFrames, loopFrames, curdelay);
            LOGSTREAM << "FPS: " << m_iShownFrames << ", Loop: " << loopFrames << ", Delay: '" << curdelay << "'";// << std::endl;

            m_iShownFrames = shownFrames;

            shownFrames = 0;
            loopFrames = 0;
            m_uiFPSLastTime = SDL_GetTicks();
        }
	}
	//clean up
    GetApplication()->OnExiting();
	GetApplication()->OnExit();
	//return
	return(0);
}

//get singleton
CApplication* CApplication::GetApplication()
{
	//return static pointer to application
	return(s_pTheApplication);
}

bs::connection CApplication::ConnectOnIdle( const slot_type_idle& s )
{
    return m_sigOnIdle.connect( s );
}

bs::connection CApplication::ConnectOnDraw( const slot_type_event& s )
{
    return m_sigOnDraw.connect( s );
}

bs::connection CApplication::ConnectOnUpdate( const slot_type_event& s )
{
    return m_sigOnUpdate.connect( s );
}

bs::connection CApplication::ConnectOnEvent( const slot_type_sdlevent& s )
{
	return m_sigOnEvent.connect( s );
}

void doExit()
{
    _CrtDumpMemoryLeaks( );
}

} // namespace gui

//main function
int main(int argc,char* argv[])
{
	using namespace gui;
    //dbgOut(__FUNCTION__ << std::endl);
    _CRT_DEBUG_BLOCK

	// create logging facility
	using namespace humbuglib;
	//dbgOut(__FUNCTION__);
	if(LogManager::getSingletonPtr() == 0)
	{
		mLogManager = new LogManager();
		mLogManager->createLog("log.txt", true, true);
	}
	LogManager::getSingleton().logMessage("Application startup at '" + std::string(__FUNCTION__) + "'.");
	// LogManager::getSingleton().logMessage("Creating FileLoader for '" + basepath + "'.");


    bmain(argc,argv);
	//run the application
    int result = -1;



    try
    {
        result = CApplication::Execute(argc,argv);
    }
//    catch (std::exception const& ex) {
//        std::cerr << "Exception: " << ex.what() << std::endl;
//        return EXIT_FAILURE;  // exit program with ERROR status
//    }
    catch (std::runtime_error ex)
    {
        LOGSTREAM << "";
        LOGSTREAM << "========================= APPLICATION ERROR !!! =========================";
        LOGSTREAM << ex.what();
        LOGSTREAM << "=========================================================================";
        LOGSTREAM << "";
    }
    /*catch (CFileException* e)
    {
    }
    catch (CException* e)
    {
    }*/

/*
    const char* explanation = "XXXXXX THIS IS ~CApplication.CPP";
    _RPT1( _CRT_WARN, "\n\n%s:\n**************************************\
                      ************************************\n", explanation );
    _CrtDumpMemoryLeaks( );
    dbgOut(__FUNCTION__ << std::endl);
*/
    //_CrtDumpMemoryLeaks( );
    //atexit(doExit);
    //new std::string("Maul !");
	
	/*if(LogManager::getSingletonPtr())
	{
		delete mLogManager;
	}*/

	return(result);
}


