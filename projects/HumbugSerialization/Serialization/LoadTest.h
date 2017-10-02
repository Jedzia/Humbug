#pragma once

#include "../global.h"
//
#include <string>
//

namespace humbug {
    namespace serialization {
  /** @class LoadTest:
   *  Detailed description.
   */
  class LoadTest {
public:

      LoadTest();
      ~LoadTest();

      /** LoadTest, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return str; }

      /** LoadTest, Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string val) { str = val; }

      /** LoadTest, Language:
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
