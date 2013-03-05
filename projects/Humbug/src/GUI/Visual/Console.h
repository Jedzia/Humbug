#ifndef __HUMBUG_GUI_VISUAL_CCONSOLE_H
#define __HUMBUG_GUI_VISUAL_CCONSOLE_H

#include <string>
#include "../Components/Canvas.h"
#include "../Components/Rectangle.h"
#include "boost/smart_ptr/scoped_ptr.hpp"

class CEventHandler;

class CConsole {
public:

    CConsole(CEventHandler* parent, const std::string& fontName, gui::components::CCanvas* displayScreen, int lines, gui::components::CRectangle rect);
    ~CConsole();

    void Draw(void) const;
    void Toggle(void);
    bool OnEvent(SDL_Event* pEvent);

    void DoSomething(void);
    //friend std::ostream& operator<<(std::ostream& o, const CConsole& r);

private:
    struct CConsoleImpl;
    boost::scoped_ptr<CConsoleImpl> pimpl_;
    gui::components::CCanvas* m_pScreen;
    gui::components::CRectangle m_crDimensions;
    bool m_bIsVisible;
};

//std::ostream& operator<<(std::ostream& o, const CConsole& r);

#endif // __HUMBUG_GUI_VISUAL_CCONSOLE_H guard
