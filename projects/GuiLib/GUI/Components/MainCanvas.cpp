#include "../../stdafx.h"
#include "MainCanvas.h"

//#include "sdl.h"

namespace gui {
namespace components {

CMainCanvas::CMainCanvas(int width, int height, int bpp, Uint32 flags):
#if SDL_GUILIB_ENABLED
	CCanvas ( SDL_SetVideoMode ( width , height , bpp, flags ) )
	{
		SDL_Delay ( 10 ) ;
	}
#else
CCanvas ( NULL )
{
	std::cout << "QUIT: CMainCanvas without surface." << std::endl;
	exit(1);
}
#endif

CMainCanvas::~CMainCanvas()
{
    // SDL_FreeSurface ( GetSurface ( ) );
    SetSurface ( NULL ) ;
}

} // namespace components
} // namespace gui
