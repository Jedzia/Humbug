#include "../stdafx.h"
#include "../stddefs.h"
//
#include "Template.h"
//
//#include <build/cmake/include/debug.h>

namespace humbug {
namespace serialization {
Template::Template() : i(0) {
    dbgOut(__FUNCTION__);
}

Template::~Template(void) {
    dbgOut(__FUNCTION__);
}

const char * Template::Language(int x) const {
    return "AsciiDoc";
}

std::ostream& operator<<(std::ostream& o, const Template& obj) {
    return o;
}

std::istream& operator>>(std::istream& i, Template& obj) {
    return i;
}
}
}
