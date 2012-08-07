//
#include "../../stdafx.h"
//
#include "Hookable.h"
#include "EventHandler.h"
#include "boost/signals.hpp"
#include "boost/bind.hpp"

//#include <build/cmake/include/debug.h>


//Hookable* Hookable::m_pController = NULL;
//CEventHandler* Hookable::m_pMaster = NULL;
//boost::ptr_vector<Hookable> Hookable::m_pvHooks;
GroupId Hookable::s_NextGrpID = 0;
GroupId Hookable::s_GrpID = -1;

class double_slot {
public:
    void operator()(int& i) const {
        i*=2;
    }
};

class plus_slot {
public:
    void operator()(int& i) const {
        i+=3;
    }
};

struct Hookable::HookableImpl {

    boost::signals::connection m_conInit;
    boost::signals::connection m_conIdle;
    
    Hookable *m_pHost;

    HookableImpl(Hookable *host)
        : m_pHost(host)
    {
        dbgOut(__FUNCTION__ << " " << this << std::endl);
    }

    ~HookableImpl()
    {
        dbgOut(__FUNCTION__ << " " << this << std::endl);
    }

    bool OnInit(int argc,char* argv[])
    {
        //return m_pHost->OnInit(argc, argv);
        return true;
    }

    void BlaFoo()
    {

        //boost::signal<void (int&)> sig;
        //sig.connect(double_slot());
        //sig.connect(plus_slot());

        //sig.connect(plus_slot());

        //int resultX=12;
        //sig(resultX);
        //std::cout << "The result is: " << resultX << '\n';

        //signal_type_init2 fuck;
        //boost::signal<void (int&)> fuck;
        //fuck(resultX);
        //bool sigresult = fuck(argc, argv);

        //bool sigresult = m_sigOnInit(argc, argv);


    }
};


/*Hookable::Hookable(CEventHandler* master)
    : m_bIsInitialized(false)
{
    dbgOut(__FUNCTION__ << " Hookable master ctor"<< std::endl);
    //dbgOut("Hookable master ctor" << std::endl);
    //std::cout.flush();
    //std::cerr << "Hookable master ctor" << std::endl;

    //std::ofstream myfile ("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/test2.txt");
    //if (myfile.is_open())
    //{
    //    myfile << "This outputting a line.\n";
    //    myfile << "Guess what, this is another line.\n";
    //    myfile.close();
    //}

        m_grpID = GetGroupID();
        if (m_grpID != 0)
        {
            throw "The base Hookable::Hookable(CEventHandler* master) must be the first in line.";
        }

         //m_pController = this;
}*/

Hookable::Hookable(bool hook)
: pimpl_(new Hookable::HookableImpl(this)), m_bIsInitialized(false), m_pMaster(NULL), m_pController(NULL)
{
    dbgOut(__FUNCTION__ << " Hookable child ctor " << this << std::endl);
    //std::cout << "Hookable child ctor" << std::endl;
    //m_pvHooks.push_back(this);
    //Init(m_pMaster, this);
}

Hookable::~Hookable(void)
{
    dbgOut(__FUNCTION__ << " Hookable dtor " << this << std::endl);
         //if (IsMaster())
         {
             //dbgOut(__FUNCTION__ << " Hookable dtor master kill " << this << std::endl);
            //m_pvHooks.release();
         }
}

/*void Hookable::Close()
{
    //std::cout << "Releasing Hookable children. size=" << m_pvHooks.size() << std::endl;
    //m_pvHooks.release();
}*/

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

void Hookable::Init(CEventHandler* master, Hookable* controller)
{

    if (m_bIsInitialized)
    {
        return;
    }
    m_pMaster = master;
    m_pController = controller;
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

//    pimpl_->m_conInit = master->ConnectOnInit(boost::bind(&Hookable::OnInit, boost::ref(*m_pController), _1, _2));
//    pimpl_->m_conIdle = master->ConnectOnIdle(boost::bind(&Hookable::OnIdle, boost::ref(*m_pController), _1));
    //m_pMaster->ConnectOnDraw(boost::bind(&Hookable::OnIdle, boost::ref(*hook)));
    //m_pMaster->ConnectOnInit(boost::bind(&Hookable::HookableImpl::OnInit, *pimpl_, _1, _2));
    m_bIsInitialized = true;
}

void Hookable::Connect(/*Hookable* controller*/)
{
    //pimpl_->m_conInit = m_pMaster->ConnectOnInit(boost::bind(&Hookable::OnInit, boost::ref(*controller), _1, _2));
    //pimpl_->m_conIdle = m_pMaster->ConnectOnIdle(boost::bind(&Hookable::OnIdle, boost::ref(*controller), _1));
    pimpl_->m_conInit = m_pMaster->ConnectOnInit(boost::bind(&Hookable::OnInit, boost::ref(*m_pController), _1, _2));
    pimpl_->m_conIdle = m_pMaster->ConnectOnIdle(boost::bind(&Hookable::OnIdle, boost::ref(*m_pController), _1));
}

void Hookable::Disconnect()
{
    pimpl_->m_conInit.disconnect();
    pimpl_->m_conIdle.disconnect();
}

bool Hookable::OnInit( int argc,char* argv[] )
{
    m_grpID = GetGroupID();
    dbgOut(__FUNCTION__ << " (" << this << ") m_grpID=" << m_grpID << std::endl);
    
    return true;
    //return Setup();
}

TestHookable::TestHookable()
: Hookable(true)
{
    dbgOut(__FUNCTION__ << std::endl);

}

TestHookable::~TestHookable()
{
    dbgOut(__FUNCTION__ << std::endl);

}

void TestHookable::OnIdle(int frameNumber)
{

}

GroupId TestHookable::GetGroupID()
{
    static GroupId grpID = CreateNextGroupID();
    return grpID;
}
