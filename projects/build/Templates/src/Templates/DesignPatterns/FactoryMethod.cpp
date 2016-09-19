
#include "../stdafx.h"
//
#include "FactoryMethod.h"

//
#include <build/cmake/include/debug.h>
namespace templates {

namespace designpatterns {

void Creator::anOperation() {
}

Creator::~Creator() {
}

//! Creates a new instance of a Product.
/// \overridden In this implementation this function returns only ConcreteProduct's.
Product * ConcreteCreator::FactoryMethod() {
  return new ConcreteProduct();
}


} // namespace templates::designpatterns

} // namespace templates
