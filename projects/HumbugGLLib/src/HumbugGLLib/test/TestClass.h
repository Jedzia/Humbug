#ifndef HumbugLIB_NAMESPACE_TEST_TESTCLASS_H
#define HumbugLIB_NAMESPACE_TEST_TESTCLASS_H


#include "QBounce/global.h"
#include <string>

//namespace HumbugLIB_NAMESPACE { namespace test { struct TestClass::Subclass; }  } 

namespace HumbugLIB_NAMESPACE {

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

} // namespace HumbugLIB_NAMESPACE::test

} // namespace HumbugLIB_NAMESPACE
#endif
