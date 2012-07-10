/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the SdlInfo.h class.
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

    friend std::ostream& operator<<(std::ostream& o, const SdlInfo& r);

private:

    void FillGeneralInfo(SDL_Surface* surface);

    void FillHwInfo();

    void FillSurfaceInfo(SDL_Surface* surface);

    bool CastSDLBool(SDL_bool v) const;

    std::string PrintBool(bool v) const;

    SdlInfoHw m_hwInfo;
    SdlInfoGeneral m_stGeneralInfo;
};
std::ostream& operator<<(std::ostream& o, const SdlInfo& r);

#endif // HUMBUG_SDLINFO_H
