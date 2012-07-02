//#include <utility>

#include <functional>
#include <iostream>
//#include <list>
#include <vector>
//#include <array>
//#include <tuple>
#include <string>
//#include <memory>
 #include <ctime>


#include <stdio.h>
#include <stdlib.h>
//#include <CppStructz/filesystem/CszGlobals.h>
//#include <TCHAR.H>

//#include "boost/filesystem.hpp"

#define CSZ_FILESYSTEM_THROW(EX) throw EX

//using namespace boost::filesystem;
using namespace std;

//using boost::system::error_code;
//using boost::system::error_category;
//using boost::system::system_category;

class stopwatch
{
public:
	 stopwatch() : start(std::clock()){} //start counting time
	 ~stopwatch();
private:
	 std::clock_t start;
};

stopwatch::~stopwatch()
{
	 clock_t total = clock()-start; //get elapsed time
	 cout<<"total of ticks for this activity: "<<total<<endl;
	 cout<<"in seconds: "<<double(total)/CLOCKS_PER_SEC<<endl;
}


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

    void throwError()
    {
        //CSZ_FILESYSTEM_THROW(filesystem_error("Cannot Determine Application Executable Path!",
        //    error_code(5, system_category())));
    }
private:
	std::string m_name;
	int cnt;
};

//#define _T(string) gettext (string)

void run1()
{
	cout << "[vector] " << __FUNCTION__ << endl;
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
	/*
	The reference_wrapper Class Template

	reference_wrapper<T> is a copy-constructible and assignable wrapper around an object of type T&. The copy-constructible and assignable properties ensure, among other things, that reference_wrapper object can be used as an element of STL containers.

	The reference_wrapper class and its helper functions are declared in the <utility> header. This header, as you probably know, already contains several other facilities such as auto_ptr.

	There are two helper functions: ref() and cref() create a reference_wrapper object that wraps their argument. cref() returns a const T& wrapper object whereas ref() returns a T& wrapper object.
	*/
	cout << "[vector] " << __FUNCTION__ << endl;
#ifdef LINUX
	std::vector<std::reference_wrapper<MyClass> > vs; // a list of references to MyClass.
#else
	std::vector<std::tr1::reference_wrapper<MyClass> > vs; // a list of references to MyClass.
#endif	
	//std::vector<std::tr1::reference_wrapper<const MyClass> > vs; // a list of const references to MyClass.
	cout << "			" << __FUNCTION__ << "> " << "MyClass m;" << endl;
	MyClass m(__FUNCTION__);
	cout << "			" << __FUNCTION__ << "> " << "MyClass& ref = m;" << endl;
	MyClass& mref = m;
	cout << "			" << __FUNCTION__ << "> " << "vs.push_back(std::tr1::ref(m));" << endl;
#ifdef LINUX
	vs.push_back(std::ref(m));
#else
	vs.push_back(std::tr1::ref(m));
#endif	
	//vs.push_back(std::tr1::cref(m));
	cout << "			" << __FUNCTION__ << "> " << "vs.clear();" << endl;
	vs.clear();
	cout << "			" << __FUNCTION__ << "> " << "MyClass copy(m);" << endl;
	MyClass copy(m);
	cout << "[vector] " << __FUNCTION__ << " returns" << endl;
}

int main(int argc, char *argv[])
{
    //Csz::docstring dreck;
	run1();
	run2();
	run3();

	// Using class stopwatch for Performance Measurements
	// http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=156
	{
		stopwatch sw; // start measuring time
		string *pstr[5000];
		for (int i=0;i<5000;i++)
		{
			pstr[i] = new string;
			for (int x=0;x<1000;x++)
			{
				string k = "Depp";
			}
		}
	} // watch is destroyed here and reports the results

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
