#ifndef TEMPLATES_TYPES_HOST_H
#define TEMPLATES_TYPES_HOST_H


#include "../global.h"
//
#include <boost/detail/scoped_enum_emulation.hpp>
namespace templates {

namespace types {

BOOST_SCOPED_ENUM_START( AnotherScoped ){
  first,
  second,
  third

};
BOOST_SCOPED_ENUM_END

//! See http://blogs.msdn.com/b/vcblog/archive/2010/04/06/c-0x-core-language-features-in-vc10-the-table.aspx?PageIndex=2
//! for a MSVC C++0x spec.
class PLATFORM_DECL Host {
  public:
    enum MyEnum {
      first,
      second,
      third

    };

    struct PLATFORM_DECL ScopedEnum {
        enum enum_type {
          first,
          second,
          third

        };

    };
    
    BOOST_SCOPED_ENUM_START( InsideClass ){
      first,
      second,
      third

    };
    BOOST_SCOPED_ENUM_END
    

    inline MyEnum useNormalEnum();

    inline ScopedEnum::enum_type useScopedEnum();

    inline BOOST_SCOPED_ENUM(AnotherScoped) useAnotherScoped();

    inline BOOST_SCOPED_ENUM(Host::InsideClass) useInsideClass();

};
inline Host::MyEnum Host::useNormalEnum() {
  return first;
}

inline Host::ScopedEnum::enum_type Host::useScopedEnum() {
  return ScopedEnum::first;
}

inline BOOST_SCOPED_ENUM(AnotherScoped) Host::useAnotherScoped() {
  //return BOOST_SCOPED_ENUM(AnotherScoped)::first;
  // give a nonstandard extension used: enum 'templates::types::AnotherScoped::enum_type'
  // used in qualified name
  return AnotherScoped::first;
}

inline BOOST_SCOPED_ENUM(Host::InsideClass) Host::useInsideClass() {
  return Host::InsideClass::first;
}


} // namespace templates::types

} // namespace templates
#endif
