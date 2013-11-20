#include "../stdafx.h"
#include "Template.h"

//#include <build/cmake/include/debug.h>


Template::Template()
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

