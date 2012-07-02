#ifndef STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H
#define STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H

#ifdef _DEBUG
# define dbgOut(x) std::cout << x
#else
# define dbgOut(x) 
#endif // _DEBUG

#include <wchar.h>
#include <QApplication>
#include <QtCore>
#include <QtGui>
#include <QMainWindow>
#include <QDomDocument>
#include <Qsci/qscilexercpp.h>


#if defined(USE_LIB_BOOST)
// You MUST use FS Version 3 ! <- is obsolete.
// Since boost 1.46.0 V3 ist the default.
//#define BOOST_FILESYSTEM_VERSION 3
    #include <boost/filesystem.hpp>

    #include <boost/progress.hpp>
    #include <boost/smart_ptr.hpp>

#endif //USE_LIB_BOOST

#include <iostream>
#include <memory>   // std::auto_ptr
#include <project.hxx>

//#include "TestClass.h"
//class __declspec(dllimport) TestClass;

#endif //STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H
