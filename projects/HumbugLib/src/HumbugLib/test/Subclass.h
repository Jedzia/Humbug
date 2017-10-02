#ifndef HumbugLIB_NAMESPACE_TEST_SUBCLASS_H
#define HumbugLIB_NAMESPACE_TEST_SUBCLASS_H


#include "QBounce/global.h"
namespace HumbugLIB_NAMESPACE {

namespace test {

//\brief	Private implementation for TestClass.
//	The Pimpl-Idiom.
//
//Yes, this is very cool.
struct TestClass::Subclass {
    //Make something very interresting.
    void doSomething();

};

} // namespace HumbugLIB_NAMESPACE::test

} // namespace HumbugLIB_NAMESPACE
#endif
