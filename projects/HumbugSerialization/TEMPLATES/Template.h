#pragma once

#include "../global.h"
//
#include "Token.h"
#include <string>

//

namespace humbug {
namespace serialization {
/** @class Template:
 *  Detailed description.
 */
class Template {
public:

    Template();
    ~Template();

    /** Template, Str:
     *  Detailed description.
     *  @return TODO
     */
    std::string Str() const { return str; }

    /** Template, Str:
     *  Detailed description.
     *  @param val TODO
     */
    void Str(std::string val) { str = val; }

    /** Template, Language:
     *  Detailed description.
     *  @param x TODO
     *  @return TODO
     */
    const char * Language(int x) const;


    friend std::ostream& operator<<(std::ostream& o, const Template& obj);

    friend std::istream& operator>>(std::istream& i, Template& obj);

private:

    int i;
    std::string str;
};
}
}
