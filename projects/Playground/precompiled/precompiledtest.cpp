#include "stdafx.h"
#include <iostream>
#include <string>
#include "boost/filesystem.hpp"

#define CSZ_FILESYSTEM_THROW(EX) throw EX

using namespace boost::filesystem;
using namespace std;

using boost::system::error_code;
using boost::system::error_category;
using boost::system::system_category;


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
}
