#include <memory>
#include <iostream>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/assign/ptr_list_inserter.hpp> // for 'ptr_push_back()', 'ptr_insert()' and 'ptr_push_front()'
#include <boost/assign/ptr_map_inserter.hpp>  // for 'ptr_map_insert()'
#include <boost/ptr_container/ptr_deque.hpp>
#include <boost/ptr_container/ptr_set.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#define CSZ_FILESYSTEM_THROW(EX) throw EX

using namespace boost::filesystem;
using namespace std;

using boost::system::error_code;
using boost::system::error_category;
using boost::system::system_category;


class MyClass
{
public:
    MyClass() { }
    void throwError()
    {
        CSZ_FILESYSTEM_THROW(boost::filesystem::filesystem_error("Cannot Determine Application Executable Path!",
                             boost::system::error_code(5, boost::system::system_category())));
    }
};


template<typename T>
void machwas(const std::string & category, T & input) {
    std::cout << "Category: " << category << std::endl;

    //boost::ptr_map<int, MyClass>& myMap = input;
    //boost::ptr_map<int, MyClass>::const_pointer yy;
    //const T::mapped_type pos = dynamic_cast<T::mapped_type>( &(*i) );
    //const T::mapped_type pos = NULL;
    boost::ptr_map<int, MyClass>::key_type yy = 5;
    yy = 77;
    typename T::key_type yy2 = 5;
    yy2 = 54;

    boost::ptr_map<int, MyClass>::mapped_type mt1 = new MyClass();
    input.insert(yy, mt1);
    typename T::mapped_type mt2 = new MyClass();
    input.insert(yy, mt2);

}

//int main(int argc, char *argv[])
int main(int , char **)
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

    std::string bobo = "bobo",
                       anna = "anna";
    int a1 = 1, a2 = 2;
a2=2;

    boost::ptr_map<int, MyClass> myMap;
    std::auto_ptr<MyClass> aptr(new MyClass());
    myMap.insert(44, aptr);

    using namespace boost::assign;
    //ptr_map_insert<MyClass>( myMap )( bobo, new MyClass() );
    //myMap.insert(std::make_pair( a1, new MyClass()));
    myMap.insert( a1, new MyClass() );

    machwas(bobo, myMap);


    /*typedef MyClass ItemType;
    typedef std::string KeyType;
    typedef boost::ptr_vector<ItemType> ValueType;
    typedef boost::ptr_map<KeyType, ValueType> MapType;

    ValueType* valList = new ValueType();
    valList->push_back( new MyClass );*/
    //MapType mCategoryDict;
    //mCategoryDict.insert( std::make_pair( std::string("Erste"), valList ) );
    //mCategoryDict.insert( std::string("Erste"), valList );


}
