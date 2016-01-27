#pragma once

#include "../global.h"
//
#include <string>
//

namespace humbug {
namespace serialization {
  /** @class Token:
   *  Detailed description.
   */
  class Token {
public:

      Token();
      ~Token();

      /** Token, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return str; }

      /** Token, Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string val) { str = val; }

      /** Token, Language:
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
