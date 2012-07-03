#include "sdl.h"
#include <stdlib.h>

const SDL_VideoInfo* g_pVideoInfo = NULL;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);
}