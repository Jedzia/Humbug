/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the AppGB.cpp class.
 * \folder     $(folder)
 * \file       AppGB.cpp
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#include "AppGB.h"
#include "stdafx.h"
#include <stdio.h>

//#include <build/cmake/include/debug.h>
namespace HumbugLIB_NAMESPACE {
namespace internal {
extern std::string getExePath();

extern std::string buildAppDir(const std::string& exePath);
}
}
AppGB::AppGB(){
    using namespace HumbugLIB_NAMESPACE::internal;
    exePath = getExePath();
    std::cout << "Starting at '" << exePath << "'." << std::endl;
    appDir = buildAppDir( exePath );
    std::cout << "appDir '" << appDir << "'." << std::endl;
}
AppGB::~AppGB()
{}
