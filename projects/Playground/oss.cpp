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

#ifdef WIN32
    inline void DoNon();
    
    __forceinline void DoInl(int x)
    {
        x = x+ 1;
        std::cout << x << std::endl;
    }

    //inline int X() const;
    //inline int X() const { return x; }
    __declspec(noinline) int X(int b) 
    { 
        y++;
        return x + b * y; 
    }

    void MyClass::NonInline( )
    {
        x++;
    }

    __declspec(noinline) void MyClass::ForceNonInline( )
    {
        x++;
    }

    inline void MyClass::Inline( )
    {
        x++;
    }

    __forceinline void MyClass::ForceInline( )
    {
        x++;
    }
#endif // WIN32

private:
    int y;
    int x;
};

#ifdef WIN32
//inline int MyClass::X() const { return x; }

inline void MyClass::DoNon( )
{
    x++;
}
#endif // WIN32




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

#ifdef WIN32
    int abc = 5;
    c.DoNon();
    c.DoInl(5);
    abc = c.X(9);
    std::cout << "abc: " << abc << std::endl;

    c.NonInline();
    c.ForceNonInline();
    c.Inline();
    c.ForceInline();
    std::cout << "get X: " << c.X(1) << std::endl;
#endif // WIN32

}