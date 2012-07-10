/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SdlInfo.h class, a decoupled
 *             SDL-Info provider with iostream support.
 * \folder     $(folder)
 * \file       SdlInfo.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_SDLINFO_H
#define HUMBUG_SDLINFO_H

//
#include <string>

//
struct SDL_Surface;

//
struct SdlInfoGeneral
{
    bool IsVideoSurface;

    bool HasHardwareSurfaces;   /**< hw_available :1 Flag: Can you create hardware surfaces? */
    bool HasWindowManager;      /**< wm_available :1 Flag: Can you talk to a window manager? */
    //Uint32 UnusedBits1  :6;
    //Uint32 UnusedBits2  :1;
    bool HasAccHwToHwBlit; 	    /**< blit_hw :1 Flag: Accelerated blits HW --> HW */
    bool HasAccHwColorkeyBlit;  /**< Uint32 blit_hw_CC :1 Flag: Accelerated blits with Colorkey */
    bool HasAccHwAlphaBlit;     /**< Uint32 blit_hw_A :1 Flag: Accelerated blits with Alpha */
    bool HasAccSwToHwBlit;      /**< Uint32 blit_sw :1 Flag: Accelerated blits SW --> HW */
    bool HasAccSwColorkeyBlit;  /**< Uint32 blit_sw_CC :1 Flag: Accelerated blits with Colorkey */
    bool HasAccSwAlphaBlit;     /**< Uint32 blit_sw_A :1 Flag: Accelerated blits with Alpha */
    bool HasAccColorfill;       /**< Uint32 blit_fill :1 Flag: Accelerated color fill */
    //Uint32 UnusedBits3  :16;
    Uint32 VideoMemorySize;	    /**< Uint32 video_mem - The total amount of video memory (in K) */
    //SDL_PixelFormat *vfmt;	/**< Value: The format of the video surface */
    int VideomodeWidth;	        /**< int current_w - Value: The current video mode width */
    int VideomodeHeight;        /**< int current_h - Value: The current video mode height */

};

//
struct SdlInfoHw
{
    bool HasRDTSC;
    bool HasMMX;
    bool HasMMXExt;
    bool Has3DNow;
    bool Has3DNowExt;
    bool HasSSE;
    bool HasSSE2;
    bool HasAltiVec;
};
class SdlInfo {
public:

    SdlInfo(SDL_Surface * surface);
    ~SdlInfo();
    const SdlInfoGeneral& GetGeneralInfo() const;

    const SdlInfoHw& GetHwInfo() const;

    std::string PrintHwInfo() const;
    std::string PrintGeneralInfo() const;

    friend std::ostream& operator<<(std::ostream& o, const SdlInfo& r);

private:

    void FillGeneralInfo(SDL_Surface* surface);

    void FillHwInfo();

    void FillSurfaceInfo(SDL_Surface* surface);

    bool CastSDLBool(SDL_bool v) const;

    std::string PrintBool(bool v) const;
    static const char* indent;
    SdlInfoHw m_hwInfo;
    SdlInfoGeneral m_stGeneralInfo;
};
std::ostream& operator<<(std::ostream& o, const SdlInfo& r);

#endif // HUMBUG_SDLINFO_H
