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


	//event structure
	SDL_Event event;
	//forever

    Uint32 shownFrames = 0, loopFrames = 0;
	for(;;)
	{
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
        }
		GetApplication()->Update();

        loopFrames++;
        if((SDL_GetTicks() - m_uiFPSLastTime) >= 1000)
        {
            //ostringstream FPS;
            //FPS.str("");
            //FPS << ShownFrames;
            fprintf(stdout, "FPS: '%d', Loop: '%d'\n", shownFrames, loopFrames);

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