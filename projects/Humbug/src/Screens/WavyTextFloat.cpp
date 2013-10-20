/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the WavyTextFloat.cpp class.
 * \folder     $(folder)
 * \file       WavyTextFloat.cpp
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#include "WavyTextFloat.h"
#include "stdafx.h"

//#include <build/cmake/include/debug.h>
#include "boost/function.hpp"
#include "boost/lambda/lambda.hpp"
//
#include "GUI/Components/Text.h"
#include "GUI/Data/ColorData.h"

using namespace gui::components;

namespace humbug {
  namespace screens {
    WavyTextFloat::WavyTextFloat(int steps) : m_iBoatcols(0),
                                              m_iFrames(0),
                                              m_iSteps(steps){
        dbgOut(__FUNCTION__ << " created:" << " (" << this << ")");
        memset( cmap, 0, sizeof(cmap) );
    }

    WavyTextFloat::~WavyTextFloat(){
        dbgOut(__FUNCTION__ << " " << this);
    }

    /** WavyTextFloat, operator ():
     *  Detailed description.
     *  @param textcanvas TODO
     * @param text TODO
     * @param mdata TODO
     * @return TODO
     */
    void WavyTextFloat::operator()( const CCanvas* textcanvas, const CText* text, CTextModifierData& mdata ){
        SDL_Color* wavemap = gui::ColorData::Instance()->Wavemap();

        for(int i = 0; i < 64; i++) {
            cmap[m_iBoatcols + ( (i + m_iFrames) & 63 )] = wavemap[i];
        }
        //SDL_SetPalette(m_pText->GetSurface(), SDL_LOGPAL, wavemap, boatcols, 32);
        SDL_SetPalette(textcanvas->GetSurface(), SDL_LOGPAL, cmap, 0, 256);
        //boatcols++;
        mdata.DeltaX = m_iFrames % 32;
        mdata.DeltaY = 2 - ( m_iFrames % 16 );
        m_iFrames++;

        //textcanvas->AddUpdateRect(textcanvas->GetDimension());

        if ( m_iFrames > m_iSteps   ) {
            m_iFrames = 0;
        }
    } // ()
  }
}
