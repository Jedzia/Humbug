#ifndef __Template_H__
#define __Template_H__

#include "Canvas.h"

namespace gui {
namespace components {

//main canvas, abstract primary display surface
class CTemplate : public CCanvas
{
public:
    //constructor
    CTemplate(const char * title, int width, int height, Uint32 flags);
    //destructor
    virtual ~CTemplate ( ) ;
};

} // namespace components
} // namespace gui

#endif
