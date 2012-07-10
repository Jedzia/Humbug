/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SdlInfo.cpp class.
 * \folder     $(folder)
 * \file       SdlInfo.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "SdlInfo.h"
#include "stdafx.h"

//#include <build/cmake/include/debug.h>
SdlInfo::SdlInfo(SDL_Surface* screen){
    dbgOut(__FUNCTION__ << std::endl);
    FillHwInfo();
}

SdlInfo::~SdlInfo(void){
    dbgOut(__FUNCTION__ << std::endl);
}

const SdlInfoHw&  SdlInfo::GetHwInfo() const {
    return m_hwInfo;
}

void SdlInfo::FillHwInfo(){
    if ( true ) {
        printf("RDTSC %s\n", SDL_HasRDTSC() ? "detected" : "not detected");
        printf("MMX %s\n", SDL_HasMMX() ? "detected" : "not detected");
        printf("MMX Ext %s\n", SDL_HasMMXExt() ? "detected" : "not detected");
        printf("3DNow %s\n", SDL_Has3DNow() ? "detected" : "not detected");
        printf("3DNow Ext %s\n", SDL_Has3DNowExt() ? "detected" : "not detected");
        printf("SSE %s\n", SDL_HasSSE() ? "detected" : "not detected");
        printf("SSE2 %s\n", SDL_HasSSE2() ? "detected" : "not detected");
        printf("AltiVec %s\n", SDL_HasAltiVec() ? "detected" : "not detected");
    }

    m_hwInfo.HasRDTSC = CastSDLBool( SDL_HasRDTSC() );
    m_hwInfo.HasMMX = CastSDLBool( SDL_HasMMX() );
    m_hwInfo.HasMMXExt = CastSDLBool( SDL_HasMMXExt() );
    m_hwInfo.Has3DNow = CastSDLBool( SDL_Has3DNow() );
    m_hwInfo.Has3DNowExt = CastSDLBool( SDL_Has3DNowExt() );
    m_hwInfo.HasSSE = CastSDLBool( SDL_HasSSE() );
    m_hwInfo.HasSSE2 = CastSDLBool( SDL_HasSSE2() );
    m_hwInfo.HasAltiVec = CastSDLBool( SDL_HasAltiVec() );
} // FillHwInfo

bool SdlInfo::CastSDLBool( SDL_bool v ){
    if (v = SDL_TRUE) {
        return true;
    }

#ifdef HUMBUG_ENUMCHECK

    if (v != SDL_FALSE) {
        //throw_exception();
        throw "[SdlInfo::CastSDLBool] SDL_bool in an invalid state.";
    }

#endif // HUMBUG_ENUMCHECK
    return false;
}

std::ostream& operator<<(std::ostream& o, const SdlInfo& r) {
    return o << "SdlInfo[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
                                 << ", W=" << r.GetW() << ", H=" << r.GetH()
                                 <<*/" ]";
}

