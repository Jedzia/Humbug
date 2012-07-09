#include "../stdafx.h"
#include "Hud.h"
#include "Filesystem/FileLoader.h"

//#include <build/cmake/include/debug.h>


Hud::Hud()
{
         dbgOut(__FUNCTION__ << std::endl);
}

Hud::~Hud(void)
{
         dbgOut(__FUNCTION__ << std::endl);
}

const char* Hud::language(int x) const
{
    return "AsciiDoc";
}

