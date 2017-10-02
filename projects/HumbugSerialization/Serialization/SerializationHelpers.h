#pragma once

#include "../global.h"
//
#include <string>
//

namespace humbug {
namespace serialization {
  /** @class SerializationHelpers:
   *  Detailed description.
   */
  class SerializationHelpers {
public:

      SerializationHelpers();
      ~SerializationHelpers();

      /** SerializationHelpers, Str:
       *  Detailed description.
       *  @return TODO
       */
      std::string Str() const { return str; }

      /** SerializationHelpers, Str:
       *  Detailed description.
       *  @param val TODO
       */
      void Str(std::string val) { str = val; }

      /** SerializationHelpers, Language:
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
