#ifndef HumbugGLLIB_NAMESPACE_TEST_TESTCLASS_H
#define HumbugGLLIB_NAMESPACE_TEST_TESTCLASS_H


#include "QBounce/global.h"
#include <string>

//namespace HumbugGLLIB_NAMESPACE { namespace test { struct TestClass::Subclass; }  } 

namespace HumbugGLLIB_NAMESPACE {

namespace test {

//Diese Testklasse implementiert das Göttliche an und für sich!
class TestClass {
  public:
    TestClass();

    ~TestClass();

    //Das ist der absolute Dreck!
    void getDreck(std::string & muschi, int & hehe);


  private:
    int pos;

	struct Subclass;
    boost::scoped_ptr<TestClass::Subclass> pimpl;

};

} // namespace HumbugGLLIB_NAMESPACE::test

} // namespace HumbugGLLIB_NAMESPACE
#endif
