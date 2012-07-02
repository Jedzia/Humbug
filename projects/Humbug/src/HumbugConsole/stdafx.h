//---------------------------------------------------------
/*!
 * This file is part of Humbug, the template processor.
 * Licence details can be found in the file COPYING.
 * Copyright (c) 2011, EvePanix. All rights reserved.
 *
 * \brief      This file contains the headers
 *             to precompile.
 * \folder     $(folder)
 * \file       stdafx.h
 * \date       2011-08-11
 * \author     Jedzia.
 *
 * modified    2011-08-21, Jedzia
 */

//---------------------------------------------------------
#ifndef STDAFX_CDCE86428F8F4560BFEBCC82B4CC7C51_H
#define STDAFX_CDCE86428F8F4560BFEBCC82B4CC7C51_H
#ifdef _DEBUG
  #  define dbgOut(x) std::cout << x
#else
  #  define dbgOut(x)
#endif // _DEBUG
/*#include <wchar.h>
   #include <QApplication>
   #include <QtCore>
   #include <QtGui>
   #include <QMainWindow>
   #include <QDomDocument>
 #include <Qsci/qscilexercpp.h>*/
#if defined(USE_LIB_BOOST)

// You MUST use FS Version 3 ! <- is obsolete.
// Since boost 1.46.0 V3 ist the default.
//#define BOOST_FILESYSTEM_VERSION 3
//    #include <boost/filesystem.hpp>
  #  include <boost/filesystem.hpp>
  #  include <boost/program_options/options_description.hpp>
  #  include <boost/program_options/parsers.hpp>
  #  include <boost/program_options/variables_map.hpp>
  #  include <boost/progress.hpp>
  #  include <boost/smart_ptr.hpp>
  #  include <boost/token_functions.hpp>
  #  include <boost/tokenizer.hpp>
#endif //USE_LIB_BOOST
//#include <project.hxx>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>   // std::auto_ptr
#include <string>
#ifdef WIN32
  #  include <process.h>
#endif

//#include "TestClass.h"
//class __declspec(dllimport) TestClass;
/* jedCONCAT_HELPER works like preprocessor ## operator but also works with macros.
   Taken from wx/chartype.h and wx/cpp.h */
#define jedCONCAT_HELPER(text, line) text ## line
#ifndef _T
  #  if !defined(UNICODE)
    #    define _T(x) x
  #  else /* Unicode */
/* use jedCONCAT_HELPER so that x could be expanded if it's a macro */
    #    define _T(x) jedCONCAT_HELPER(L, x)
  #  endif /* ASCII/Unicode */
#endif /* !defined(UNICODE) */
//#include <CppStructz/config/ConfigOptionList.h>
//#include <CppStructz/config/ConfigString.h>
//#include <CppStructz/log/LogHelper.h>
//#include <CppStructz/text/DocLoader.h>
//#include <CppStructz/text/TextDocument.h>
//#include <HumbugShared/GB.h>
//#include <HumbugShared/Project/ProcessProject.h>

//#include "ProgOptions.h"
#endif //STDAFX_CDCE86428F8F4560BFEBCC82B4CC7C51_H
