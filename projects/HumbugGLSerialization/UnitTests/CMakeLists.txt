# Unit Tests

cmake_minimum_required(VERSION 2.8)

project( HumbugGLSerializationTest )

include(BoostTestTargets)
ADD_BOOST_TEST(unit_test_example_01
 SOURCES
 unit_test_example_01.cpp)

add_definitions("-DBUILD_ROOT_PATH=${BUILD_ROOT_PATH}")
 
#ADD_BOOST_TEST(zfs01
# SOURCES
# zfs01.cpp
# LIBRARIES
# HumbugGLLib HumbugGLSerialization
# RESOURCES resources/UnitTests.zip
#)
#Copy_Files_To_Target(${PROJECT_NAME}-zfs01-boost_test resources/UnitTests.zip)
#Copy_Files_To_Target(boosttest-HumbugGL_HumbugGLSerialization_UnitTests-zfs01 resources/UnitTests.zip)

#target_link_libraries(zfs01 HumbugGLSerialization)

ADD_BOOST_TEST(basicTest
 SOURCES
 Test.cpp
 LIBRARIES
 HumbugGLLib HumbugGLSerialization
# RESOURCES HumbugGLSerialization
) 
#set_property(TARGET unit_test_example_01 PROPERTY FOLDER "${PROJECT_NAME}/UnitTests")
