#ifndef __HUMBUG_GUI_VISUAL_CCONSOLE_H
#define __HUMBUG_GUI_VISUAL_CCONSOLE_H

#include <string>
#include "../Components/Canvas.h"
#include "../Components/Rectangle.h"
#include "boost/smart_ptr/scoped_ptr.hpp"


class CConsole {
public:

    CConsole(const std::string& fontName, CCanvas* displayScreen, int lines, CRectangle rect);
    ~CConsole();

    void Draw(void) const;
    void Toggle(void);
    bool OnEvent(SDL_Event* pEvent);

    //friend std::ostream& operator<<(std::ostream& o, const CConsole& r);

private:
    struct CConsoleImpl;
    boost::scoped_ptr<CConsoleImpl> pimpl_;
    CCanvas* m_pScreen;
    CRectangle& m_crDimensions;
    bool m_bIsVisible;
};

//std::ostream& operator<<(std::ostream& o, const CConsole& r);

#endif // __HUMBUG_GUI_VISUAL_CCONSOLE_H guard
