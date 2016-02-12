#include "SDL.h"
#include <stdlib.h>
#include <stdio.h>

//const SDL_VideoInfo* g_pVideoInfo = NULL;
//const SDL_RendererInfo* g_pRenderInfo = NULL;
SDL_RendererInfo g_pRenderInfo;

int wmain(int argc, char* argv[])
{
	SDL_Init(SDL_INIT_VIDEO);
	atexit(SDL_Quit);
    //g_pRenderInfo = SDL_GetVideoInfo();
    int result = SDL_GetRenderDriverInfo(0, &g_pRenderInfo);
	fprintf(stdout, "\nVideo Information:\n");
	fprintf(stdout, "flags? %d\n", g_pRenderInfo.flags);
	fprintf(stdout, "max_texture_height? %d\n", g_pRenderInfo.max_texture_height);
	fprintf(stdout, "max_texture_width? %d\n", g_pRenderInfo.max_texture_width);
	fprintf(stdout, "name? %s\n", g_pRenderInfo.name);
	fprintf(stdout, "num_texture_formats? %d\n", g_pRenderInfo.num_texture_formats);

//    fprintf(stdout, "hw_available? %d\n", g_pRenderInfo->hw_available);
//    fprintf(stdout, "wm_available? %d\n", g_pRenderInfo->wm_available);
//    fprintf(stdout, "blit_hw? %d\n", g_pRenderInfo->blit_hw);
//    fprintf(stdout, "blit_hw_CC? %d\n", g_pRenderInfo->blit_hw_CC);
//    fprintf(stdout, "blit_hw_A? %d\n", g_pRenderInfo->blit_hw_A);
//    fprintf(stdout, "blit_sw? %d\n", g_pRenderInfo->blit_sw);
//    fprintf(stdout, "blit_sw_CC? %d\n", g_pRenderInfo->blit_sw_CC);
//    fprintf(stdout, "blit_sw_A? %d\n", g_pRenderInfo->blit_sw_A);
//    fprintf(stdout, "blit_fill? %d\n", g_pRenderInfo->blit_fill);
//    fprintf(stdout, "video memory(in K)? %d\n", g_pRenderInfo->video_mem);
//    fprintf(stdout, "bits per pixel? %d\n", g_pRenderInfo->vfmt->BitsPerPixel);

	return(0);
}
