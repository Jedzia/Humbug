#include "../stdafx.h"
#include "../stddefs.h"
//
#include "Token.h"
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace serialization {
  Token::Token(){
      dbgOut(__FUNCTION__);
  }

  Token::~Token(void){
      dbgOut(__FUNCTION__);
  }

  /** Token, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  const char * Token::Language(int x) const {
      return "AsciiDoc";
  }
}
}
