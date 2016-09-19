/*---------------------------------------------------------*/
/*!
 * This file is part of HumbugGL, the template processor.
 * License details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the stdafx.h class.
 * \folder     $(folder)
 * \file       stdafx.h
 * \date       2011-08-11
 * \author     Jedzia.
 *
 * modified    2011-09-17, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H
#define STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H
#ifdef _DEBUG
  #  define dbgOut(x) std::cout << x
#else
  #  define dbgOut(x)
#endif // _DEBUG

#include <HumbugGLLib/LogManager.h>
// Standard headers
#include <iostream>
#include <memory>   // std::auto_ptr
#include <wchar.h>

// Standard headers VFS
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iomanip>
#include <map>
#include <string>
#include <vector>

//#include "HumbugGLCore/VFS/stdint.h"


#if defined(USE_LIB_BOOST)

// You MUST use FS Version 3 ! <- is obsolete.
// Since boost 1.46.0 V3 ist the default.
//#define BOOST_FILESYSTEM_VERSION 3
#include <boost/function.hpp>
  #  include <boost/filesystem.hpp>
  #  include <boost/progress.hpp>
  #  include <boost/smart_ptr.hpp>
#endif //USE_LIB_BOOST

#ifdef USE_XSD
#  include <xsd/cxx/pre.hxx>
#  include <xsd/cxx/xml/dom/parsing-source.hxx>
#  include <xsd/cxx/xml/string.hxx>
#endif // USE_XSD

#ifdef WIN32

// \todo: Under linux, the pch generator does not include the correct
// dependency to the xsd generator target.
//  #  include <project.hxx>
#endif
//#include <CppStructz/log/LogHelper.h>
//#include <Crunchy/global.h>
#include <lua.hpp>
#include <luabind/luabind.hpp>

//class __declspec(dllimport) TestClass;
#endif //STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H
