//
#include "../../stdafx.h"
//
#include "Hookable.h"
#include "EventHandler.h"
#include "boost/signals.hpp"
#include "boost/bind.hpp"

//#include <build/cmake/include/debug.h>


Hookable* Hookable::m_pController = NULL;
CEventHandler* Hookable::m_pMaster = NULL;
boost::ptr_vector<Hookable> Hookable::m_pvHooks;
GroupId Hookable::s_NextGrpID = 0;
GroupId Hookable::s_GrpID = -1;


struct Hookable::HookableImpl {
    bool XXXOnInit(int argc,char* argv[])
    {
        return true;
    }
};


Hookable::Hookable(CEventHandler* master)
    : m_bIsInitialized(false)
{
    dbgOut(__FUNCTION__ << " Hookable master ctor"<< std::endl);
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

        m_grpID = GetGroupID();
        if (m_grpID != 0)
        {
            throw "The base Hookable::Hookable(CEventHandler* master) must be the first in line.";
        }

         m_pController = this;
         m_pMaster = master;
}

Hookable::Hookable(Hookable* hook)
: pimpl_(new Hookable::HookableImpl), m_bIsInitialized(false)
{
    dbgOut(__FUNCTION__ << " Hookable child ctor " << this << std::endl);
    //std::cout << "Hookable child ctor" << std::endl;
    m_pvHooks.push_back(hook);
    Init(hook);
}

Hookable::~Hookable(void)
{
    dbgOut(__FUNCTION__ << " Hookable dtor " << this << std::endl);
         if (IsMaster())
         {
             dbgOut(__FUNCTION__ << " Hookable dtor master kill " << this << std::endl);
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
    std::cout << "Releasing Hookable children. size=" << m_pvHooks.size() << std::endl;
    m_pvHooks.release();
}

GroupId Hookable::CreateNextGroupID()
{
    //return current group id, and increment value
    return(s_NextGrpID++);
}

GroupId Hookable::GetGroupID()
{
    static GroupId grpID = CreateNextGroupID();
    return grpID;
}

bool XXXOnInit(int argc,char* argv[])
{
    return true;
}


void Hookable::Init(Hookable* hook)
{

    if (m_bIsInitialized)
    {
        return;
    }

    m_grpID = GetGroupID();


    //boost::signal<void (int&)> sig;
    //sig.connect(double_slot());
    //sig.connect(plus_slot());

    //sig.connect(plus_slot());

    //int result=12;
    //sig(result);
    //std::cout << "The result is: " << result << '\n';

    //boost::signal<void (int, char**)> sig2;
    //sig2.connect(boost::bind(&CEventHandler::OnPreInit, *this, _1, _2));
    //sig2(1,2);

    //m_pMaster->ConnectOnInit(boost::bind(&Hookable::OnInit, *hook, _1, _2));
    m_pMaster->ConnectOnInit(boost::bind(&Hookable::HookableImpl::XXXOnInit, *pimpl_, _1, _2));
    //m_pMaster->ConnectOnInit(&XXXOnInit);

    m_bIsInitialized = true;
}

bool Hookable::OnInit( int argc,char* argv[] )
{
    return true;
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

GroupId TestHookable::GetGroupID()
{
    static GroupId grpID = CreateNextGroupID();
    return grpID;
}
