#ifndef TEMPLATES_DESIGNPATTERNS_SINGLETON_H
#define TEMPLATES_DESIGNPATTERNS_SINGLETON_H


#include "../global.h"
//
#include <string>

namespace templates {

namespace designpatterns {

class PLATFORM_DECL Singleton {
  private:
    static Singleton instance;

    std::string name;

    Singleton();


  public:
    static Singleton& getInstance();

    bool anOperation();

    inline const std::string getName() const;

    void setName(std::string value);

};
inline const std::string Singleton::getName() const {
  return name;
}


} // namespace templates::designpatterns

} // namespace templates
#endif
