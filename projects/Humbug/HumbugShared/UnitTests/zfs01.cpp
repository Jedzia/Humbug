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
#include <HumbugShared/VFS/zfsystem.h>

using zip_file_system::filesystem;
using zip_file_system::izfstream;

//____________________________________________________________________________//

#define STRX(x) #x
#define STR(x) STRX(x)

// most frequently you implement test cases as a free functions with automatic registration
BOOST_AUTO_TEST_CASE( test1 )
{
	// reports 'error in "test1": test 2 == 1 failed'
	//BOOST_CHECK( 2 == 1 );
	BOOST_CHECK( 2 == 2 ) ;
   
	//std::string m_pBasepath = "E:/Projects/C++/Humbug/build2008x64";
	std::string m_pBasepath = STR(BUILD_ROOT_PATH);
	filesystem fsys(m_pBasepath.c_str(), "zip", true);


	std::string filename = "Blafasel.txt";
	std::string data;
	izfstream file(filename.c_str());

	if (! file)
	//LOGSTREAM << "ERROR: Cannot open file!";
	std::cout << "ERROR: Cannot open file!" << std::endl;
	else
	{
		data.clear();
		data.reserve(file.tellg());
		file.seekg(0, std::ios::beg);
		data.append(std::istreambuf_iterator<char>(file.rdbuf()),
		            std::istreambuf_iterator<char>());
	}

	file.close();
}

//____________________________________________________________________________//

// each test file may contain any number of test cases; each test case has to have unique name
BOOST_AUTO_TEST_CASE( test2 )
{
	int i = 0;

	// reports 'error in "test2": check i == 2 failed [0 != 2]'
	BOOST_CHECK_EQUAL( i, 0 ) ;
}

//____________________________________________________________________________//

// EOF