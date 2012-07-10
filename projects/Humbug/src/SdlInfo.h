#ifndef HUMBUG_SDLINFO_H
#define HUMBUG_SDLINFO_H

#include "SDL.h"

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

    SdlInfo(SDL_Surface* screen);
    ~SdlInfo();

    const SdlInfoHw& GetHwInfo() const;

    friend std::ostream& operator<<(std::ostream& o, const SdlInfo& r);

private:
    void FillHwInfo();
    bool CastSDLBool(SDL_bool v);
	SdlInfoHw m_hwInfo;
};

std::ostream& operator<<(std::ostream& o, const SdlInfo& r);

#endif // HUMBUG_SDLINFO_H
