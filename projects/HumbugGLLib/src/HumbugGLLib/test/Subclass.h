#ifndef HumbugGLLIB_NAMESPACE_TEST_SUBCLASS_H
#define HumbugGLLIB_NAMESPACE_TEST_SUBCLASS_H


#include "QBounce/global.h"
namespace HumbugGLLIB_NAMESPACE {

namespace test {

//\brief	Private implementation for TestClass.
//	The Pimpl-Idiom.
//
//Yes, this is very cool.
struct TestClass::Subclass {
    //Make something very interresting.
    void doSomething();

};

} // namespace HumbugGLLIB_NAMESPACE::test

} // namespace HumbugGLLIB_NAMESPACE
#endif
