// Application.cpp: implementation of the CApplication class.
//
//////////////////////////////////////////////////////////////////////

#include "../../stdafx.h"
#include <stdlib.h>
#include "Application.h"
#include "SdlInfo.h"


//singleton pointer
CApplication* CApplication::s_pTheApplication=NULL;
Uint32 CApplication::m_uiFPSLastTime=0;
int CApplication::m_iFramesCap = 25;

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
CMessageHandler(NULL)
{
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
}

//destructor
CApplication::~CApplication()
{
    dbgOut(__FUNCTION__ << std::endl);
}

//initialization
bool CApplication::OnInit(int argc,char* argv[])
{
	//by default, simply return true
	return(true);
}

//event occurrence
void CApplication::OnEvent(SDL_Event* pEvent)
{
	//by default, do nothing
}

//idle behavior
void CApplication::OnIdle()
{
	//by default, do nothing
}

//update loop
void CApplication::Update()
{
	//by default, do nothing
}

//cleanup
void CApplication::OnExit()
{
	//by default, do nothing
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
	if(!GetApplication()->OnInit(argc,argv))
	{
		//could not initialize
		fprintf(stderr,"Could not initialize application!\n");
		//return
		return(-1);
	}

    {
        // Get SDL Info
        SdlInfo sdlInfo(SDL_GetVideoSurface());
        std::cout << sdlInfo << std::endl;
    }

    //The frame rate regulator
    Timer fps;
    Uint32 curdelay = 0;


	//event structure
	SDL_Event event;
	//forever

    Uint32 shownFrames = 0, loopFrames = 0;
	for(;;)
	{
        //Start the frame timer
        fps.start();

		//poll for an event
		if(SDL_PollEvent(&event)==1)
		{
			//check for a quit event
			if(event.type==SDL_QUIT) break;
			//event occurred
			GetApplication()->OnEvent(&event);
		}
		else
		{
			//no event, so idle
			GetApplication()->OnIdle();
            shownFrames++;

            //Cap the frame rate
            if( fps.get_ticks() < 1000 / m_iFramesCap )
            {
                curdelay = ( 1000 / m_iFramesCap ) - fps.get_ticks();
                SDL_Delay( curdelay );
            }
        }
		GetApplication()->Update();

        loopFrames++;
        if((SDL_GetTicks() - m_uiFPSLastTime) >= 1000)
        {
            //ostringstream FPS;
            //FPS.str("");
            //FPS << ShownFrames;
            int delay = shownFrames - m_iFramesCap;
            fprintf(stdout, "FPS: '%d', Loop: '%d', Delay: '%d'\n", shownFrames, loopFrames, curdelay);


            shownFrames = 0;
            loopFrames = 0;
            m_uiFPSLastTime = SDL_GetTicks();
        }

	}
	//clean up
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

extern int bmain(int argc,char* argv[]);

//main function
int main(int argc,char* argv[])
{
	bmain(argc,argv);
	//run the application
	return(CApplication::Execute(argc,argv));
}