
#include "QBounce/stdafx.h"
#include "TestClass.h"
#include "Subclass.h"

#include "QBounce/Test/SubClass.cpp"
namespace HumbugGLLIB_NAMESPACE {

namespace test {

TestClass::TestClass()
: pimpl(new Subclass){
}

TestClass::~TestClass(){
}

//Das ist der absolute Dreck!
void TestClass::getDreck(std::string & muschi, int & hehe) {
  	pimpl->doSomething();
}


} // namespace HumbugGLLIB_NAMESPACE::test

} // namespace HumbugGLLIB_NAMESPACE
