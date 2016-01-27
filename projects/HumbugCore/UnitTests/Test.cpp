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
#define BOOST_TEST_MODULE HumbugCore_GVector2D
#include <BoostTestTargetConfig.h>

//#define LOGMANAGER_NOLOG 1
#include <HumbugLib/LogManager.h>
#include <HumbugCore/Serialization/Test.h>

using namespace humbug::core;

struct MyConfig
{
	MyConfig()
	{
		std::cout << "global setup\n";
		if (humbuglib::LogManager::getSingletonPtr() == 0)
		{
			mLogManager = new humbuglib::LogManager();
			mLogManager->createLog("log.txt", true, true);
		}
	}

	~MyConfig()
	{
		std::cout << "global teardown\n";
		delete mLogManager;
	}

	humbuglib::LogManager* mLogManager;
};

//filesystem* MyConfig::fsys = 0;

//____________________________________________________________________________//

BOOST_GLOBAL_FIXTURE( MyConfig ) ;

//____________________________________________________________________________//

// most frequently you implement test cases as a free functions with automatic registration
BOOST_AUTO_TEST_CASE( Vector2D_direction_test )
{
	//GVector2D::Up();
	// reports 'error in "test1": test 2 == 1 failed'
	/*if (humbuglib::LogManager::getSingletonPtr() == 0)
	{
		mLogManager = new humbuglib::LogManager();
		mLogManager->createLog("log.txt", true, true);
	}*/


	Template testObject;
    BOOST_CHECK( testObject.Str() == "");
    BOOST_CHECK( testObject.Language(5) == "Bla");

	//delete mLogManager;
}

//____________________________________________________________________________//

// each test file may contain any number of test cases; each test case has to have unique name
BOOST_AUTO_TEST_CASE( test2 )
{
	int i = 0;

	// reports 'error in "test2": check i == 2 failed [0 != 2]'
	//BOOST_CHECK_EQUAL( i, 2 );
}

//____________________________________________________________________________//

// EOF