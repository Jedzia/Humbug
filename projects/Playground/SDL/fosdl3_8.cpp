//focus on sdl

//palette demo

//fosdl3_8.cpp
//7MAY2002
//ernest pazera

//requires static linkage to:  
//sdl.lib, sdlmain.lib

//requires dynamic linkage to: 
//sdl.dll

//include SDL stuff
#include "sdl.h"

//include ability to exit program
#include <stdlib.h>

//screen dimensions
const int SCREEN_WIDTH=640;
const int SCREEN_HEIGHT=480;

//display surface
SDL_Surface* g_pDisplaySurface = NULL;

//event structure
SDL_Event g_Event;

//palette
SDL_Color g_PaletteColors[256];

//main function
int main(int argc, char* argv[])
{
	//initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO)==-1)
	{
		//error initializing SDL

		//report the error
		fprintf(stderr,"Could not initialize SDL!\n");

		//end the program
		exit(1);
	}
	else
	{
		//SDL initialized

		//report success
		fprintf(stdout,"SDL initialized properly!\n");

		//set up to uninitialize SDL at exit
		atexit(SDL_Quit);
	}

	//create windowed environment
	g_pDisplaySurface = SDL_SetVideoMode(SCREEN_WIDTH,SCREEN_HEIGHT,8,SDL_FULLSCREEN|SDL_HWPALETTE);

	//error check
	if (g_pDisplaySurface == NULL)
	{
		//report error
		fprintf(stderr,"Could not set up display surface!\n");

		//exit the program
		exit(1);
	}

	//set up colors
	int index;//loop variable
	for(index=0;index<256;index++)
	{
		//make a shade of gray
		g_PaletteColors[index].r=index;
		g_PaletteColors[index].g=index;
		g_PaletteColors[index].b=index;
	}

	//set the palette
	SDL_SetColors(g_pDisplaySurface,g_PaletteColors,0,256);

	//do color fills
	SDL_Rect FillRect;
	for(index=0;index<256;index++)
	{
		FillRect.x=index;
		FillRect.y=index;
		FillRect.w=SCREEN_WIDTH-index;
		FillRect.h=SCREEN_HEIGHT-index;
		SDL_FillRect(g_pDisplaySurface,&FillRect,index);
	}
	//update the screen
	SDL_UpdateRect(g_pDisplaySurface,0,0,0,0);

	//repeat forever
	for(;;)
	{
		//wait for an event
		if(SDL_PollEvent(&g_Event)==0)
		{
			//update the screen
			SDL_UpdateRect(g_pDisplaySurface,0,0,0,0);
		}
		else
		{
			//event occurred, check for quit
			if(g_Event.type==SDL_QUIT) break;

			//if a key was pressed, quit
			if(g_Event.type==SDL_KEYDOWN) break;
		}
	}

	//normal termination
	fprintf(stdout,"Terminating normally.\n");

	//return 0
	return(0);
}