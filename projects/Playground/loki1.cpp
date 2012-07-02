//#include <utility>

#include <functional>
#include <iostream>
//#include <list>
#include <vector>
//#include <array>
//#include <tuple>
#include <string>
//#include <memory>


#include <stdio.h>
#include <stdlib.h>
#include <CppStructz/Loki/Singleton.h>
//#include <TCHAR.H>

//#include "boost/filesystem.hpp"

#define CSZ_FILESYSTEM_THROW(EX) throw EX

//using namespace boost::filesystem;
using namespace std;

//using boost::system::error_code;
//using boost::system::error_category;
//using boost::system::system_category;
 
using namespace Loki;

class KeyboardImpl 
{
	friend struct Loki::CreateStatic< KeyboardImpl >;
public:
    KeyboardImpl() 	{ cout << "++[" << __FUNCTION__ << "-" << "(" << ")] Constructed++" << endl; }
    ~KeyboardImpl()	{ cout << "--[" << __FUNCTION__ << "-" << "(" << ")] Destructed--" << endl; }
    void doSomething()
    {
    		cout << "		[KeyboardImpl-" << "(" << 1 << ")] doSomething() called" << endl; 
	}
  
};
inline unsigned int GetLongevity(KeyboardImpl*) { return 7; }
typedef SingletonHolder<KeyboardImpl, CreateUsingNew, SingletonWithLongevity> Keyboard;

class MaulImpl 
{
	friend struct Loki::CreateStatic< KeyboardImpl >;
public:
    MaulImpl() 	{ cout << "++[" << __FUNCTION__ << "-" << "(" << ")] Constructed++" << endl; }
    ~MaulImpl()	{ cout << "--[" << __FUNCTION__ << "-" << "(" << ")] Destructed--" << endl; }
    void doSomething()
    {
    		cout << "		[MaulImpl-" << "(" << 1 << ")] doSomething() called" << endl; 
	}
  
};
inline unsigned int GetLongevity(MaulImpl*) { return 4; }
typedef SingletonHolder<MaulImpl, CreateUsingNew, SingletonWithLongevity> Maul;

class MyClass
{
public:
    MyClass(const std::string& name)
	{
		m_name = name;
		static int count=0;
		count++;
		cnt = count;
		cout << "++[MyClass-" << m_name << "(" << cnt << ")] Constructed++" << endl; 
	}
    virtual ~MyClass(){ cout << "--[MyClass-" << m_name << "(" << cnt << ")] Destructed--" << endl; }
    
	//MyClass(MyClass& myclass){ cout << "++[MyClass] Copy Constructor++" << endl; }
    MyClass(const MyClass& myclass)
	{ 
		m_name = myclass.m_name;
		cnt = myclass.cnt;
		cout << "++[MyClass-" << m_name << "(" << cnt << ")] Copy Constructor++" << endl; 
	}

    void doSomething()
    {
        //CSZ_FILESYSTEM_THROW(filesystem_error("Cannot Determine Application Executable Path!",
        //    error_code(5, system_category())));
		Maul::Instance().doSomething();
    	cout << "++[MyClass-" << m_name << "(" << cnt << ")] doSomething() called" << endl; 
	}
private:
	std::string m_name;
	int cnt;
};

class OtherClass
{
public:
    OtherClass()
	{
		static int count=0;
		count++;
		cnt = count;
		cout << "++[OtherClass-" << "(" << cnt << ")] Constructed++" << endl; 
	}
    virtual ~OtherClass(){ cout << "--[OtherClass-" << "(" << cnt << ")] Destructed--" << endl; }
    
	//OtherClass(OtherClass& myclass){ cout << "++[OtherClass] Copy Constructor++" << endl; }
    OtherClass(const OtherClass& myclass)
	{ 
		cnt = myclass.cnt;
		cout << "++[OtherClass-" << "(" << cnt << ")] Copy Constructor++" << endl; 
	}

    void doSomething()
    {
        //CSZ_FILESYSTEM_THROW(filesystem_error("Cannot Determine Application Executable Path!",
        //    error_code(5, system_category())));
    		cout << "++[OtherClass-" << "(" << cnt << ")] doSomething() called" << endl; 
	}
private:
	int cnt;
};
//#define _T(string) gettext (string)

void run1()
{
	cout << "[vector] " << __FUNCTION__ << endl;
	Maul::Instance().doSomething();
	vector<MyClass> vs;
	MyClass m(__FUNCTION__);
	vs.push_back(m);
}

void run2()
{
	cout << "[vector] " << __FUNCTION__ << endl;
	vector<MyClass*> vs;
	MyClass *m = new MyClass(__FUNCTION__);
	vs.push_back(m);
	vs.clear();
}

void run3()
{
#ifndef LINUX
	/*
	The reference_wrapper Class Template

	reference_wrapper<T> is a copy-constructible and assignable wrapper around an object of type T&. The copy-constructible and assignable properties ensure, among other things, that reference_wrapper object can be used as an element of STL containers.

	The reference_wrapper class and its helper functions are declared in the <utility> header. This header, as you probably know, already contains several other facilities such as auto_ptr.

	There are two helper functions: ref() and cref() create a reference_wrapper object that wraps their argument. cref() returns a const T& wrapper object whereas ref() returns a T& wrapper object.
	*/
	cout << "[vector] " << __FUNCTION__ << endl;
	std::vector<std::tr1::reference_wrapper<MyClass> > vs; // a list of references to MyClass.	
	//std::vector<std::tr1::reference_wrapper<const MyClass> > vs; // a list of const references to MyClass.
	cout << "			" << __FUNCTION__ << "> " << "MyClass m;" << endl;
	MyClass m(__FUNCTION__);
	cout << "			" << __FUNCTION__ << "> " << "MyClass& ref = m;" << endl;
	MyClass& mref = m;
	cout << "			" << __FUNCTION__ << "> " << "vs.push_back(std::tr1::ref(m));" << endl;
	vs.push_back(std::tr1::ref(m));
	//vs.push_back(std::tr1::cref(m));
	cout << "			" << __FUNCTION__ << "> " << "vs.clear();" << endl;
	vs.clear();
	cout << "			" << __FUNCTION__ << "> " << "MyClass copy(m);" << endl;
	MyClass copy(m);
	cout << "[vector] " << __FUNCTION__ << " returns" << endl;
#endif //ifndef LINUX
}


typedef SingletonHolder<OtherClass, CreateUsingNew> SingleA;

int main(int argc, char *argv[])
{
    //Csz::docstring dreck;
	run1();
	run2();
	run3();
	SingleA::Instance().doSomething();
	SingleA::Instance().doSomething();
	SingleA::Instance().doSomething();
	Keyboard::Instance().doSomething();
	Maul::Instance().doSomething();
	exit(0);

    /*MyClass m;
    try 
    {	        
        m.throwError();
    }
    catch (filesystem_error &e)
    {
        std::cout << "exception is: " << e.what() << std::endl;
    }*/
}
