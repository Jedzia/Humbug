#ifndef HUMBUG_SCREENS_WAVYTEXTFLOAT_H
#define HUMBUG_SCREENS_WAVYTEXTFLOAT_H
#include "GUI/Components/Screen.h"
#include <boost/smart_ptr/scoped_ptr.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

namespace gui { namespace components {
	class CCanvas;
	class CText;
	struct CTextModifierData;
}}

namespace humbug {
  namespace screens {
class WavyTextFloat
{
    int m_iBoatcols;
    int m_iFrames;
    int m_iSteps;
    SDL_Color cmap[256];

public:

    WavyTextFloat(int steps = 16);
    ~WavyTextFloat();

    void operator() (const gui::components::CCanvas *textcanvas, const gui::components::CText *text, gui::components::CTextModifierData& mdata);
};



}
}
#endif // HUMBUG_SCREENS_WAVYTEXTFLOAT_H
