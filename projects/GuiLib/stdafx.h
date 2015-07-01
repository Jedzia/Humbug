#ifndef STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H
#define STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H

#include <iostream>
#include <memory>   // std::auto_ptr
#include <vector>
#include <map>
#include <functional>
#include <algorithm>
#include <stdexcept>


#ifdef _DEBUG
/*inline void _moo_bugzor(const char* ff)
{
    std::ofstream myfile ("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/test2.txt");
    if (myfile.is_open())
    {
        myfile << ff << std::endl;
        //myfile << "Guess what, this is another line.\n";
        myfile.close();
    }

}*/
//# define dbgOut(x) std::cout.flush(); std::cout << x
//# define dbgOut(x) std::cout << x  << std::endl

//extern std::ofstream xout;
//# define dbgOut(x) xout << x
#else
//# define dbgOut(x)
#endif // _DEBUG

#include <wchar.h>

/*#ifdef USE_QT
#  include <QApplication>
#  include <QtCore>
#  include <QtGui>
#  include <QMainWindow>
#  include <QDomDocument>
#  include <Qsci/qscilexercpp.h>
#endif // USE_QT*/


#if defined(USE_LIB_BOOST)
// You MUST use FS Version 3 ! <- is obsolete.
// Since boost 1.46.0 V3 ist the default.
//#define BOOST_FILESYSTEM_VERSION 3
    #include <boost/filesystem.hpp>

    #include <boost/system/error_code.hpp>
    #include <boost/system/system_error.hpp>

    #include <boost/progress.hpp>

    #include <boost/smart_ptr.hpp>
    #include <boost/ptr_container/ptr_vector.hpp>
    #include <boost/ptr_container/ptr_map.hpp>

    #include <boost/bind.hpp>
    #include "boost/bind/mem_fn.hpp"
    #include "boost/function.hpp"

    #include "boost/signals2.hpp"
    #include "boost/signals2/connection.hpp"

	#include <boost/cstdint.hpp>
	#include <iostream>
	#include <boost/iostreams/device/array.hpp>
	#include <boost/iostreams/stream.hpp>
	#include <boost/archive/binary_iarchive.hpp>
	#include <boost/archive/binary_oarchive.hpp>

#endif //USE_LIB_BOOST

#define DEBUG_MEMORY_SUMMARY_ON_EXIT 1
#include <build/cmake/include/debug.h>

	#include "SDL.h"
	#include "SDL_image.h"
	#include "SDL_ttf.h"

//#include "GUI/Components/Rectangle.h"

//using namespace gui::components;

//#include "TestClass.h"
//class __declspec(dllimport) TestClass;
#include <HumbugLib/LogManager.h>

#endif //STDAFX_8494D9496E234a5997CCB38FA8AD02F3_H
