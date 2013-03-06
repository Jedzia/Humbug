#include "stdafx.h"
#include "WavyTextFloat.h"

//#include <build/cmake/include/debug.h>
#include "boost/lambda/lambda.hpp"
#include "boost/function.hpp"
//
#include "GUI/Data/ColorData.h"
#include "GUI/Components/Text.h"

namespace humbug {
  namespace screens {
WavyTextFloat::WavyTextFloat(int steps) : m_iBoatcols(0), m_iFrames(0), m_iSteps(steps)
{
    dbgOut(__FUNCTION__ << " created:" << " (" << this << ")" << std::endl);
    memset(cmap, 0, sizeof(cmap));
}

WavyTextFloat::~WavyTextFloat()
{
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

void WavyTextFloat::operator()( const gui::components::CCanvas *textcanvas, const gui::components::CText *text, gui::components::CTextModifierData& mdata )
{
	SDL_Color *wavemap = gui::ColorData::Instance()->Wavemap();
    for(int i = 0; i < 64; i++)
        cmap[m_iBoatcols + ((i + m_iFrames) & 63)] = wavemap[i];

    //SDL_SetPalette(m_pText->GetSurface(), SDL_LOGPAL, wavemap, boatcols, 32);
    SDL_SetPalette(textcanvas->GetSurface(), SDL_LOGPAL, cmap, 0, 256);
    //boatcols++;
    mdata.DeltaX = m_iFrames % 32;
    mdata.DeltaY = 2 - ( m_iFrames % 16 );
    m_iFrames++;

    //textcanvas->AddUpdateRect(textcanvas->GetDimension());

    if ( m_iFrames > m_iSteps   )
    {
        m_iFrames = 0;
    }
}

}
}
