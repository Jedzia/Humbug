#ifndef TEMPLATES_CPP0X_CONSTRUCTORS_H
#define TEMPLATES_CPP0X_CONSTRUCTORS_H


#include "../global.h"
//
namespace templates {

namespace cpp0x {

class PLATFORM_DECL Constructors {
  public:
    int number;

    Constructors(int new_number) : number(new_number) {}
    

/*    Constructors() : Constructors(42) {}  */


    ~Constructors();

};

} // namespace templates::cpp0x

} // namespace templates
#endif
