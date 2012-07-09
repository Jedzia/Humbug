#include <iostream>
#include <string>
#include <list>
#include "boost/filesystem.hpp"
#include <boost/cstdint.hpp>

#define CSZ_FILESYSTEM_THROW(EX) throw EX

using namespace boost::filesystem;
using namespace std;

using boost::system::error_code;
using boost::system::error_category;
using boost::system::system_category;

boost::uint32_t dreck=4;

class MyClass
{
public:
    MyClass(){ }
    void throwError()
    {
        CSZ_FILESYSTEM_THROW(boost::filesystem::filesystem_error("Cannot Determine Application Executable Path!",
            boost::system::error_code(5, boost::system::system_category())));
    }
};




int main(int argc, char *argv[])
{
    MyClass m;
    try 
    {	        
        m.throwError();
    }
    catch (filesystem_error &e)
    {
        std::cout << "exception is: " << e.what() << std::endl;
    }


    MyClass a,b,c;

    std::list<MyClass*> s_lstUpdate(0);
    s_lstUpdate.push_back(&a);
    s_lstUpdate.remove(&a);

    s_lstUpdate.remove(&b);
    s_lstUpdate.push_back(&b);
    s_lstUpdate.remove(&b);


}