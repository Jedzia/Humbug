#pragma once

#include "../global.h"
//
#include <string>
//

namespace humbug {
namespace core {
  class Template {
public:

      Template();
      ~Template();

      /** Template, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return str; }

      /** Template, Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string val) { str = val; }

      /** Template, Language:
       *  Detailed description.
       *  @param x TODO
       *  @return TODO
       */
      const char * Language(int x) const;

private:

      int i;
      std::string str;
  };
}
}
