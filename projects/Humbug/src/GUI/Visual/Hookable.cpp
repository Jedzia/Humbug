//
#include "../../stdafx.h"
//
#include "Hookable.h"

//#include <build/cmake/include/debug.h>


Hookable* Hookable::m_pController = NULL;
CEventHandler* Hookable::m_pMaster = NULL;
boost::ptr_vector<Hookable> Hookable::m_pvHooks;


Hookable::Hookable(CEventHandler* master)
{
    //dbgOut("Hookable master ctor" << std::endl);
    //std::cout.flush();
    //std::cerr << "Hookable master ctor" << std::endl;

    /*std::ofstream myfile ("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/test2.txt");
    if (myfile.is_open())
    {
        myfile << "This outputting a line.\n";
        myfile << "Guess what, this is another line.\n";
        myfile.close();
    }*/

         m_pController = this;
         m_pMaster = master;
}

Hookable::Hookable(Hookable* hook)
{
    //std::cout << "Hookable child ctor" << std::endl;
         m_pvHooks.push_back(hook);
}

Hookable::~Hookable(void)
{
    dbgOut(__FUNCTION__ << " Hookable dtor"<< std::endl);
         if (IsMaster())
         {
             dbgOut(__FUNCTION__ << " Hookable dtor master kill" << std::endl);
            m_pvHooks.release();
         }
}

bool Hookable::IsMaster() const
{
    //return(this==GetMainControl());
    return(this == m_pController);
}

void Hookable::Close()
{
    std::cout << "Releasing Hookable children." << std::endl;
    m_pvHooks.release();
}

TestHookable::TestHookable()
: Hookable(this)
{
    dbgOut(__FUNCTION__ << std::endl);

}

TestHookable::~TestHookable()
{
    dbgOut(__FUNCTION__ << std::endl);

}
