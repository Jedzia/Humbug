#include "../../stdafx.h"
#include "MainCanvas.h"

CMainCanvas::CMainCanvas(int width, int height, int bpp, Uint32 flags):
CCanvas ( SDL_SetVideoMode ( width , height , bpp, flags ) )
{
	SDL_Delay ( 10 ) ;
}

CMainCanvas::~CMainCanvas()
{
    // SDL_FreeSurface ( GetSurface ( ) );
    SetSurface ( NULL ) ;
}
