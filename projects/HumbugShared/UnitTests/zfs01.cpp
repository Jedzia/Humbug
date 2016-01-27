//  (C) Copyright Gennadiy Rozental 2005.
//  Distributed under the Boost Software License, Version 1.0.
//  (See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org/libs/test for the library home page.

// Boost.Test

// each test module could contain no more then one 'main' file with init function defined
// alternatively you could define init function yourself
#define BOOST_TEST_MAIN
//#include <boost/test/unit_test.hpp>
#define BOOST_TEST_MODULE HumbugShared_ZFS
#include <BoostTestTargetConfig.h>

#define LOGMANAGER_NOLOG 1
//#include <HumbugLib/LogManager.h>
#include <HumbugShared/VFS/zfsystem.h>
#include <iostream>

//
//#include <build/cmake/include/debug.h>
//
using zip_file_system::filesystem;
using zip_file_system::izfstream;

//____________________________________________________________________________//

#define STRX(x) # x
#define STR(x) STRX(x)

#ifndef BUILD_ROOT_PATH
#error BUILD_ROOT_PATH has to be defined !
#endif

struct MyConfig
{
    MyConfig(){
        //: m_pBasepath()
        std::cout << "global setup\n";
        m_pBasepath = STR(BUILD_ROOT_PATH);
        //filesystem fsysx(m_pBasepath.c_str(), "zip", true);
        fsys = new filesystem(m_pBasepath.c_str(), "zip", true);
        //fsys = &fsysx;
    }
    ~MyConfig(){
        std::cout << "global teardown\n";
        delete fsys;
    }
    std::string m_pBasepath;    // = std::string(STR(BUILD_ROOT_PATH));
    //filesystem fsysx;
    static filesystem* fsys;
};

filesystem * MyConfig::fsys = 0;

//____________________________________________________________________________//

BOOST_GLOBAL_FIXTURE( MyConfig );

/*struct F {
    F() : i( 0 ) { BOOST_TEST_MESSAGE( "setup fixture" ); }
    ~F()         { BOOST_TEST_MESSAGE( "teardown fixture" ); }

    int i;
   };


   BOOST_FIXTURE_TEST_CASE( test_case1, F )
   {
    BOOST_CHECK( i == 1 );
   ++i;
   }

   BOOST_FIXTURE_TEST_CASE( test_case2, F )
   {
    BOOST_CHECK_EQUAL( i, 1 );
   }

   BOOST_AUTO_TEST_CASE( test_case3 )
   {
    BOOST_CHECK( true );
   }*/
std::streamoff PrepareRead(const filesystem& fsys, const std::string& filename, izfstream& file){
    std::streamoff bufsize;

    //std::string xxx = file.FullFilePath();
    if ( file.Zipped() ) {
        // File is in ZIP, get size.
        bufsize = fsys.FileSize( filename.c_str() );
    }
    else {
        // File is on disc, get size.
        file.seekg(0, file.end);
        bufsize = file.tellg();
        file.seekg(0, file.beg);
    }

    return bufsize;
} // PrepareRead

// most frequently you implement test cases as a free functions with automatic registration
BOOST_AUTO_TEST_CASE( test1 )
{
    // reports 'error in "test1": test 2 == 1 failed'
    //BOOST_CHECK( 2 == 1 );

    //std::string m_pBasepath = "E:/Projects/C++/Humbug/build2008x64";

    std::string filename = "Blafasel.txt";
    //std::string data;
    char* data;
	int bufsize = 0;
    izfstream file( filename.c_str() );

    BOOST_CHECK( file.is_open() != 0 );
    if (!file) {
        //LOGSTREAM << "ERROR: Cannot open file!";
        std::cout << "ERROR: Cannot open file!" << std::endl;
    }
    else {
        //data.clear();
        bufsize = MyConfig::fsys->FileSize( filename.c_str() );
        //data.reserve(fsize);
        //file.seekg(0, std::ios::beg);
        //data.append(std::istreambuf_iterator<char>(file.rdbuf()),
        //            std::istreambuf_iterator<char>());

        data = new char[bufsize];
        file.read(&data[0], bufsize);

        delete[] data;
    }
	
	BOOST_CHECK_MESSAGE( bufsize == 19, "bufsize is " << bufsize );
    file.close();
}

//____________________________________________________________________________//

/*
// each test file may contain any number of test cases; each test case has to have unique name
BOOST_AUTO_TEST_CASE( test2 )
{
    int i = 0;

    // reports 'error in "test2": check i == 2 failed [0 != 2]'
    BOOST_CHECK_EQUAL( i, 0 );
}
*/
//____________________________________________________________________________//

// EOF
