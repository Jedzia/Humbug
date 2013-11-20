#include "../stdafx.h"
#include "GVector2D.h"

//#include <build/cmake/include/debug.h>


GVector2D::GVector2D()
{
         dbgOut(__FUNCTION__ << std::endl);
}

GVector2D::~GVector2D(void)
{
         dbgOut(__FUNCTION__ << std::endl);
}

const char* GVector2D::language(int x) const
{
    return "AsciiDoc";
}

