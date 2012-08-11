#ifndef STDAFX_CDCE86428F8F4560BFEBCC82B4CC7C51_H
#define STDAFX_CDCE86428F8F4560BFEBCC82B4CC7C51_H

#ifdef _DEBUG
# define dbgOut(x) std::cout << x
#else
# define dbgOut(x)
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

#include <boost/progress.hpp>
#include <boost/smart_ptr.hpp>

#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/token_functions.hpp>
#include <boost/tokenizer.hpp>

#include <boost/filesystem.hpp>

#endif //USE_LIB_BOOST

//#include <project.hxx>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <memory>   // std::auto_ptr
#include <string>

//#include "TestClass.h"
//class __declspec(dllimport) TestClass;

/* jedCONCAT_HELPER works like preprocessor ## operator but also works with macros.
   Taken from wx/chartype.h and wx/cpp.h */
#define jedCONCAT_HELPER(text, line) text ## line

#ifndef _T
#if !defined(UNICODE)
#define _T(x) x
#else /* Unicode */
/* use jedCONCAT_HELPER so that x could be expanded if it's a macro */
#define _T(x) jedCONCAT_HELPER(L, x)
#endif /* ASCII/Unicode */
#endif /* !defined(UNICODE) */

#include <assert.h>
#define ASSERT(x) assert(x)

#endif //STDAFX_CDCE86428F8F4560BFEBCC82B4CC7C51_H
