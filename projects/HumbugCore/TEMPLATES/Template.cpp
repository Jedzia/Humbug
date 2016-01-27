#include "../stdafx.h"
#include "../stddefs.h"
//
#include "Template.h"
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace core {
  Template::Template(){
      dbgOut(__FUNCTION__);
  }

  Template::~Template(void){
      dbgOut(__FUNCTION__);
  }

  /** Template, Language:
   *  Detailed description.
   *  @param x TODO
   * @return TODO
   */
  const char * Template::Language(int x) const {
      return "AsciiDoc";
  }
}
}
