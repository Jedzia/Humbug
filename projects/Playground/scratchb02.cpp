#include <iostream>
#include <sstream>
#include <string>
#include <boost/array.hpp>
#include <boost/algorithm/cxx14/equal.hpp>
#include <array>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <typeinfo>
#include <boost/call_traits.hpp>

template <class T>
struct Contained
{
    // define our typedefs first, arrays are stored by value
    // so value_type is not the same as result_type:
    typedef typename boost::call_traits<T>::param_type       param_type;
    typedef typename boost::call_traits<T>::reference        reference;
    typedef typename boost::call_traits<T>::const_reference  const_reference;
    typedef T                                                value_type;
    typedef typename boost::call_traits<T>::value_type       result_type;

    // stored value:
    value_type v_;

    // constructors:
    Contained() {}
    Contained(param_type p) : v_(p){}
    // return byval:
    result_type value() { return v_; }
    // return by_ref:
    reference get() { return v_; }
    const_reference const_get()const { return v_; }
    // pass value:
    void call(param_type p){}

};

int main(int argc, char *argv[])
{ 
    const int cx = 7;
    Contained<int> c;

    Contained<int>::param_type pt = 6;
    //Contained<int>::reference ref(&cx);
    Contained<int>::const_reference cref = pt;
    int& a = c.get();

    Contained<int>::value_type vt = pt;

    //c::const_reference x;


    std::cout << "End." << std::endl; 
}