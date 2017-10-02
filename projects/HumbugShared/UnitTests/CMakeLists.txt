# Unit Tests

cmake_minimum_required(VERSION 2.8)

#project( HumbugSharedTest )

include(BoostTestTargets)
ADD_BOOST_TEST(unit_test_example_01
 SOURCES
 unit_test_example_01.cpp)

add_definitions("-DBUILD_ROOT_PATH=${BUILD_ROOT_PATH}")
 
ADD_BOOST_TEST(zfs01
 SOURCES
 zfs01.cpp
 LIBRARIES
 HumbugLib HumbugShared
 RESOURCES resources/UnitTests.zip
)
#Copy_Files_To_Target(${PROJECT_NAME}-zfs01-boost_test resources/UnitTests.zip)
#Copy_Files_To_Target(boosttest-Humbug_HumbugShared_UnitTests-zfs01 resources/UnitTests.zip)

#target_link_libraries(zfs01 HumbugShared)

ADD_BOOST_TEST(gameobjects
 SOURCES
 GVector2D.cpp
 LIBRARIES
 HumbugLib HumbugShared
# RESOURCES HumbugShared
) 
#set_property(TARGET unit_test_example_01 PROPERTY FOLDER "${PROJECT_NAME}/UnitTests")
