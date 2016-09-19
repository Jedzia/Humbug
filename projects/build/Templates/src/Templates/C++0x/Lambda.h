#ifndef TEMPLATES_CPP0X_LAMBDA_H
#define TEMPLATES_CPP0X_LAMBDA_H


#include "../global.h"
//
#include <vector>

namespace templates {

namespace cpp0x {

class PLATFORM_DECL Lambda {
  public:
    //See http://en.wikipedia.org/wiki/C%2B%2B0x#Lambda_functions_and_expressions
    inline void lambda(const std::vector<int> & test);

};
//See http://en.wikipedia.org/wiki/C%2B%2B0x#Lambda_functions_and_expressions
inline void Lambda::lambda(const std::vector<int> & test) {
  std::vector<int> some_list;
  int total = 0;
  std::for_each(some_list.begin(), some_list.end(), [&total](int x) {
    total += x;
  });
}


} // namespace templates::cpp0x

} // namespace templates
#endif
