#include "../../stdafx.h"
#include "MainCanvas.h"

namespace gui {
namespace components {

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

} // namespace components
} // namespace gui
