#ifndef __MAINCANVAS_H__
#define __MAINCANVAS_H__

#include "Canvas.h"

namespace gui {
namespace components {

//main canvas, abstract primary display surface
class CMainCanvas : public CCanvas
{
public:
    //constructor
    CMainCanvas(const char * title, int width, int height, Uint32 flags);
    //destructor
    virtual ~CMainCanvas ( ) ;
};

} // namespace components
} // namespace gui

#endif
