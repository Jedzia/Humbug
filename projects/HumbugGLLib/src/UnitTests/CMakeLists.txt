# Unit Tests

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

#PROJECT( HumbugGLLibTest )
PROJECT( HumbugGLLib )

INCLUDE(BoostTestTargets)
ADD_BOOST_TEST(unit_test_example_01
 SOURCES
 unit_test_example_01.cpp)
 
#SET_PROPERTY(TARGET unit_test_example_01 PROPERTY FOLDER "${PROJECT_NAME}/UnitTests")
