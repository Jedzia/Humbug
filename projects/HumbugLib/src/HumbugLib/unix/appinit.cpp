/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the appinit.cpp class.
 * \folder     $(folder)
 * \file       appinit.cpp
 * \date       2012-09-29
 * \author     Jedzia.
 *
 * modified    2012-09-29, Jedzia
 */
/*---------------------------------------------------------*/
#include "../stdafx.h"
#include <stdio.h>

//#include <build/cmake/include/debug.h>
namespace HumbugLIB_NAMESPACE {
namespace internal {
std::string getExePath(){
    return "./";
}

std::string buildAppDir(const std::string& exePath){
    std::string::size_type lastdirpos = exePath.find_last_of("\\");
    std::cout << "Dirpos at '" << lastdirpos << "'." << std::endl;
    //return exePath.substr(0, lastdirpos + 1);
    // Todo: fix path handling for linux!
    return "/home/jedzia/devel/Humbug/build/Humbug/src/";
}
}
}
