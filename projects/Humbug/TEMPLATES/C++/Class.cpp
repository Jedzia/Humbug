#include "stdafx.h"
#include "$Filename$.h"

//#include <build/cmake/include/debug.h>


$Filename$::$Filename$()
{
         dbgOut(__FUNCTION__ << std::endl);
}

$Filename$::~$Filename$(void)
{
         dbgOut(__FUNCTION__ << std::endl);
}

const char* $Filename$::$Filename$(int x) const
{
    return "AsciiDoc";
}

