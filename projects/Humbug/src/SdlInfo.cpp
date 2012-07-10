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
#include "stdafx.h"

//
#include "SDL.h"
#include "SdlInfo.h"
#include <sstream>

//#include <build/cmake/include/debug.h>
SdlInfo::SdlInfo(SDL_Surface* surface){
    dbgOut(__FUNCTION__ << std::endl);
    FillHwInfo();
    FillGeneralInfo(surface);
    FillSurfaceInfo(surface);
}

SdlInfo::~SdlInfo(void){
    dbgOut(__FUNCTION__ << std::endl);
}

const SdlInfoGeneral& SdlInfo::GetGeneralInfo() const {
    return m_stGeneralInfo;
}

const SdlInfoHw&  SdlInfo::GetHwInfo() const {
    return m_hwInfo;
}

void SdlInfo::FillGeneralInfo(SDL_Surface* surface){
    SDL_Surface* videosurface = SDL_GetVideoSurface();
    m_stGeneralInfo.IsVideoSurface = videosurface == surface;
    const SDL_VideoInfo* vidinfo = SDL_GetVideoInfo();
}

void SdlInfo::FillHwInfo(){
    m_hwInfo.HasRDTSC = CastSDLBool( SDL_HasRDTSC() );
    m_hwInfo.HasMMX = CastSDLBool( SDL_HasMMX() );
    m_hwInfo.HasMMXExt = CastSDLBool( SDL_HasMMXExt() );
    m_hwInfo.Has3DNow = CastSDLBool( SDL_Has3DNow() );
    m_hwInfo.Has3DNowExt = CastSDLBool( SDL_Has3DNowExt() );
    m_hwInfo.HasSSE = CastSDLBool( SDL_HasSSE() );
    m_hwInfo.HasSSE2 = CastSDLBool( SDL_HasSSE2() );
    m_hwInfo.HasAltiVec = CastSDLBool( SDL_HasAltiVec() );
} // FillHwInfo

void SdlInfo::FillSurfaceInfo( SDL_Surface* surface )
{}

bool SdlInfo::CastSDLBool( SDL_bool v ) const {
    if (v == SDL_TRUE) {
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

std::string SdlInfo::PrintHwInfo() const {
    const char* indent = "    ";
    std::ostringstream result;
    result.str("");
    result << indent << "HasRDTSC \t" << PrintBool(m_hwInfo.HasRDTSC) << std::endl;
    result << indent << "HasMMX \t" << PrintBool(m_hwInfo.HasMMX) << std::endl;
    result << indent << "HasMMXExt \t" << PrintBool(m_hwInfo.HasMMXExt) << std::endl;
    result << indent << "Has3DNow \t" << PrintBool(m_hwInfo.Has3DNow) << std::endl;
    result << indent << "Has3DNowExt\t" << PrintBool(m_hwInfo.Has3DNowExt) << std::endl;
    result << indent << "HasSSE \t" << PrintBool(m_hwInfo.HasSSE) << std::endl;
    result << indent << "HasSSE2 \t" << PrintBool(m_hwInfo.HasSSE2) << std::endl;
    result << indent << "HasAltiVec \t" << PrintBool(m_hwInfo.HasAltiVec) << std::endl;
    return result.str();
}

std::string SdlInfo::PrintBool( bool v ) const {
    return v ? "detected" : "not detected";
}

std::ostream& operator<<(std::ostream& o, const SdlInfo& r) {
    o << "SDL-Info [ " <<
    (r.GetGeneralInfo().IsVideoSurface ? "from the main video surface." : "") <<
    " ]" << std::endl;
    o << "---------------------------------------------------" << std::endl;
    o << "Hardware Info:" << std::endl;
    o << r.PrintHwInfo();
    return o;
}

