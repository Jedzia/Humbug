#include "../stdafx.h"
#include "../stddefs.h"
//
#include "SerializationHelpers.h"
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace serialization {
  SerializationHelpers::SerializationHelpers(){
      dbgOut(__FUNCTION__);
  }

  SerializationHelpers::~SerializationHelpers(void){
      dbgOut(__FUNCTION__);
  }

  /** SerializationHelpers, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  const char * SerializationHelpers::Language(int x) const {
      return "AsciiDoc";
  }
}
}
