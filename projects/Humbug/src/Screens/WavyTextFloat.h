/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the WavyTextFloat.h class.
 * \folder     $(folder)
 * \file       WavyTextFloat.h
 * \date       2013-03-06
 * \author     Jedzia.
 *
 * modified    2013-03-06, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_SCREENS_WAVYTEXTFLOAT_H
#define HUMBUG_SCREENS_WAVYTEXTFLOAT_H
#include "GUI/Components/Screen.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/smart_ptr/scoped_ptr.hpp>

namespace gui {
  namespace components {
    class CCanvas;
    class CText;
    struct TextAnimatorData;
  }
}

namespace humbug {
  namespace screens {
    class WavyTextFloat {
        int m_iBoatcols;
        int m_iFrames;
        int m_iSteps;
        SDL_Color cmap[256];

public:

        WavyTextFloat(int steps = 16);
        ~WavyTextFloat();

        void operator() (const gui::components::CCanvas* textcanvas, const gui::components::CText* text,
                gui::components::TextAnimatorData& mdata);
    };
  }
}
#endif // HUMBUG_SCREENS_WAVYTEXTFLOAT_H
