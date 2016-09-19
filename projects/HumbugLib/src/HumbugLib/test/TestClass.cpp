
#include "QBounce/stdafx.h"
#include "TestClass.h"
#include "Subclass.h"

#include "QBounce/Test/SubClass.cpp"
namespace HumbugLIB_NAMESPACE {

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


} // namespace HumbugLIB_NAMESPACE::test

} // namespace HumbugLIB_NAMESPACE
