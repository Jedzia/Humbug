#ifndef __SimpleMenu_H__
#define __SimpleMenu_H__

#include "Canvas.h"

namespace gui {
namespace components {

//main canvas, abstract primary display surface
class CSimpleMenu : public CCanvas
{
public:
    //constructor
    CSimpleMenu(const char * title, int width, int height, Uint32 flags);
    //destructor
    virtual ~CSimpleMenu ( ) ;
};

} // namespace components
} // namespace gui

#endif
