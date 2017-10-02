# Unit Tests

cmake_minimum_required(VERSION 2.8)

#project( HumbugLibTest )
project( HumbugLib )

include(BoostTestTargets)
ADD_BOOST_TEST(unit_test_example_01
 SOURCES
 unit_test_example_01.cpp)
 
#set_property(TARGET unit_test_example_01 PROPERTY FOLDER "${PROJECT_NAME}/UnitTests")
