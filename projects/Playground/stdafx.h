#ifndef STDAFX_0662284F7DB44ec699439C6DE3179A11_H
#define STDAFX_0662284F7DB44ec699439C6DE3179A11_H

//#define MyDECLSPEC __declspec(dllexport)
//class __declspec(dllexport) TestClass;

//#include "CppStructz/global.h"

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

//#include "CppStructz/support/strfwd.h"

#include <string>
/*#include <cstring>
#include <fstream>
#include <iostream>
#include <list>
#include <vector>*/


/*#if defined(USE_LIB_QT4)
    #include <QApplication>
    #include <QtCore>
    #include <QtGui>
    #include <QMainWindow>
    #include <QDomDocument>
    #include <Qsci/qscilexercpp.h>
#endif //defined(USE_LIB_QT4)
*/

#if defined(USE_LIB_BOOST)
// You MUST use FS Version 3 ! <- is obsolete.
// Since boost 1.46.0 V3 ist the default.
//#define BOOST_FILESYSTEM_VERSION 3
//    #include "boost/bind.hpp"
    #include "boost/filesystem.hpp"
//    #include "boost/progress.hpp"
//    #include "boost/regex.hpp"
//    #include "boost/scoped_ptr.hpp"
#endif //defined(USE_LIB_BOOST)

//#include <CppStructz/TestClass.h>

#endif //STDAFX_0662284F7DB44ec699439C6DE3179A11_H
