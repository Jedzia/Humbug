#include "../../stdafx.h"
#include "MainCanvas.h"

namespace gui {
namespace components {

CMainCanvas::CMainCanvas(const char * title, int width, int height, int bpp, Uint32 flags):
CCanvas(SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags))
{
    SDL_Delay ( 10 ) ;
}

CMainCanvas::~CMainCanvas()
{
    // SDL_FreeSurface ( GetSurface ( ) );
    SetWindow ( NULL ) ;
}

} // namespace components
} // namespace gui
