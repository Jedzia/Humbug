#include "../stdafx.h"
#include "../stddefs.h"
//
#include "LoadTest.h"
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace core {
  LoadTest::LoadTest(): i(0)
  {
      dbgOut(__FUNCTION__);
  }

  LoadTest::~LoadTest(void){
      dbgOut(__FUNCTION__);
  }

  /** LoadTest, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  const char * LoadTest::Language(int x) const {
      return "AsciiDoc";
  }
}
}
