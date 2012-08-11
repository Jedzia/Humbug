#ifndef TEMPLATES_TYPES_INTERFACE_H
#define TEMPLATES_TYPES_INTERFACE_H


#include "../global.h"
//
namespace templates {

namespace types {

class PLATFORM_DECL OutputBuilder {
  public:
    void anOperation();

};
class PLATFORM_DECL DOMBuilder : public OutputBuilder {
  public:
    void anOperation();

};
class PLATFORM_DECL XMLBuilder : public OutputBuilder {
  public:
    void anOperation();

};

} // namespace templates::types

} // namespace templates
#endif
