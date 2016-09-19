# Unit Tests

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT( HumbugCoreTest )

INCLUDE(BoostTestTargets)
ADD_BOOST_TEST(unit_test_example_01
 SOURCES
 unit_test_example_01.cpp)

ADD_DEFINITIONS("-DBUILD_ROOT_PATH=${BUILD_ROOT_PATH}")
 
#ADD_BOOST_TEST(zfs01
# SOURCES
# zfs01.cpp
# LIBRARIES
# HumbugLib HumbugCore
# RESOURCES resources/UnitTests.zip
#)
#Copy_Files_To_Target(${PROJECT_NAME}-zfs01-boost_test resources/UnitTests.zip)
#Copy_Files_To_Target(boosttest-Humbug_HumbugCore_UnitTests-zfs01 resources/UnitTests.zip)

#TARGET_LINK_LIBRARIES(zfs01 HumbugCore)

ADD_BOOST_TEST(basicTest
 SOURCES
 Test.cpp
 LIBRARIES
 HumbugLib HumbugCore
# RESOURCES HumbugCore
) 
#SET_PROPERTY(TARGET unit_test_example_01 PROPERTY FOLDER "${PROJECT_NAME}/UnitTests")
