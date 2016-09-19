
#include "../stdafx.h"
//
#include "Singleton.h"

//
#include <build/cmake/include/debug.h>
namespace templates {

namespace designpatterns {

Singleton Singleton::instance;

Singleton::Singleton() {
}

Singleton& Singleton::getInstance()
{
  return instance;
}

bool Singleton::anOperation() {
  return true;
}

void Singleton::setName(std::string value) {
  name = value;
}


} // namespace templates::designpatterns

} // namespace templates
