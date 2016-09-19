#ifndef STDAFX_0662284F7DB45ec699439C6DE3179A19_H
#define STDAFX_0662284F7DB45ec699439C6DE3179A19_H

//#define MyDECLSPEC __declspec(dllexport)
//class __declspec(dllexport) TestClass;

#include <HumbugLib/global.h>

#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif

//#include "HumbugLib/support/strfwd.h"

#include <algorithm>
#include <cerrno>
#include <cassert>
#include <clocale>
#include <csignal>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <deque>
#include <exception>
#include <fstream>
#include <functional>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <memory>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <stack>
#include <string>
#include <utility>
#include <vector>

#include <string.h>

#if defined(USE_LIB_QT4)
    #include <QApplication>
    #include <QtCore>
    #include <QtGui>
    #include <QMainWindow>
    #include <QDomDocument>
    #include <Qsci/qscilexercpp.h>
#endif //defined(USE_LIB_QT4)


#if defined(USE_LIB_BOOST)
// You MUST use FS Version 3 ! <- is obsolete.
// Since boost 1.46.0 V3 ist the default.
//#define BOOST_FILESYSTEM_VERSION 3
    #include "boost/filesystem.hpp"

    #include "boost/regex.hpp"
    #include "boost/progress.hpp"
    #include "boost/scoped_ptr.hpp"

    #include "boost/bind.hpp"
#endif //defined(USE_LIB_BOOST)

//#include <CppStructz/TestClass.h>
//#include "minizip/zip.h"
//#include "minizip/unzip.h"
//#ifndef HumbugLIB_NAMESPACE_HELPERS_H
//#  include "shared/Helpers.h"
//#endif

#endif //STDAFX_0662284F7DB45ec699439C6DE3179A19_H
