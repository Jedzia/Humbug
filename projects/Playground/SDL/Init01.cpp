#include "SDL.h"
#include <stdlib.h>

const SDL_VideoInfo* g_pVideoInfo = NULL;

int main(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);
	g_pVideoInfo = SDL_GetVideoInfo();
	fprintf(stdout, "\nVideo Information:\n");
	fprintf(stdout, "hw_available? %d\n", g_pVideoInfo->hw_available);
	fprintf(stdout, "wm_available? %d\n", g_pVideoInfo->wm_available);
	fprintf(stdout, "blit_hw? %d\n", g_pVideoInfo->blit_hw);
	fprintf(stdout, "blit_hw_CC? %d\n", g_pVideoInfo->blit_hw_CC);
	fprintf(stdout, "blit_hw_A? %d\n", g_pVideoInfo->blit_hw_A);
	fprintf(stdout, "blit_sw? %d\n", g_pVideoInfo->blit_sw);
	fprintf(stdout, "blit_sw_CC? %d\n", g_pVideoInfo->blit_sw_CC);
	fprintf(stdout, "blit_sw_A? %d\n", g_pVideoInfo->blit_sw_A);
	fprintf(stdout, "blit_fill? %d\n", g_pVideoInfo->blit_fill);
	fprintf(stdout, "video memory(in K)? %d\n", g_pVideoInfo->video_mem);
	fprintf(stdout, "bits per pixel? %d\n", g_pVideoInfo->vfmt->BitsPerPixel);

	return(0);
}
