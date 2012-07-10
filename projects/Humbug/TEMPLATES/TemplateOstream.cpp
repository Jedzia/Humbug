#include "stdafx.h"
#include "Template.h"

//#include <build/cmake/include/debug.h>


Template::Template(/*SDL_Surface* screen*/)
{
         dbgOut(__FUNCTION__ << std::endl);
}

Template::~Template(void)
{
         dbgOut(__FUNCTION__ << std::endl);
}

const char* Template::language(int x) const
{
    return "AsciiDoc";
}


std::ostream& operator<<(std::ostream& o, const Template& r) {
    return o << "Template[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
        << ", W=" << r.GetW() << ", H=" << r.GetH()
        <<*/ " ]";
}

