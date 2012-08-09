#include "stdafx.h"
#include "HookableManager.h"
#include <stdexcept>
#include <utility>

//#include <build/cmake/include/debug.h>

class HookBinder
{
public:
	HookBinder();
	~HookBinder();
};
 
HookableManager::HookableManager(CEventHandler* master)
: m_pMaster(master), m_pActiveHook(NULL)
{
         //dbgOut(__FUNCTION__ << std::endl);
         if ( !master )
         {
             throw std::runtime_error("You have to specify a valid master event handler.");
         }
}

HookableManager::~HookableManager(void)
{
         //dbgOut(__FUNCTION__ << std::endl);
}

void HookableManager::Close()
{
    dbgOut(__FUNCTION__ << std::endl);
    m_mapHooks.release();
}

void HookableManager::AddHookable(std::string key, Hookable *item, bool connectMe )
{
    dbgOut(__FUNCTION__ << " Adding Hook " << key << "(" << item << ")" << std::endl);
    if ( m_mapHooks.find(key) == m_mapHooks.end() )
    {
        //m_mapHooks.insert( std::make_pair(key, item) );
        // http://www.boost.org/doc/libs/1_50_0/libs/ptr_container/doc/tutorial.html
        m_mapHooks.insert( key, item );
        item->Init(m_pMaster, item);
        if (connectMe)
        {
            //item->Connect();
            EnableHookable(key);
        }
    }
    else
    {
        throw std::runtime_error("Creator method already specified for index=" + key); // interface requirement
    }
}

Hookable* HookableManager::GetHookable( const std::string& key )
{
    dbgOut(__FUNCTION__ << " Searching Hook '" << key << "'" << std::endl);

    HookDictionary::iterator found =  m_mapHooks.find(key);
    if ( m_mapHooks.find(key) == m_mapHooks.end() )
    {
        throw std::runtime_error("RemoveHookable found nothing to remove."); // interface requirement
    }

    return found->second;
}

void HookableManager::RemoveHookable( const std::string& key )
{
    dbgOut(__FUNCTION__ << " Removing Hook " << key << std::endl);
    // disconnect and release
    //m_mapHooks.release(key);
}

void HookableManager::Test1()
{
    dbgOut(__FUNCTION__ << " Disconnecting the StartScreen Hook " << std::endl);

    //const Hookable& hookable = m_mapHooks["StartScreen"];
    Hookable* hookable = GetHookable("StartScreen");
    //m_mapHooks["StartScreen"].Disconnect();
    hookable->Disconnect();
    //throw std::runtime_error("Bla bla, error in 'void HookableManager::Test1()'."); // interface requirement
    // Todo: Switch on off by name.
}

void HookableManager::Test2()
{
    dbgOut(__FUNCTION__ << " Connecting the StartScreen Hook " << std::endl);
    Hookable* hookable = GetHookable("StartScreen");
    //hookable->Connect(hookable);
    hookable->Connect();
}

void HookableManager::EnableHookable( const std::string& key )
{
    if (m_pActiveHook)
    {
        m_pActiveHook->Disconnect();
        m_pActiveHook = NULL;
    }

    Hookable* hookable = GetHookable(key);
    hookable->Connect();
    m_pActiveHook = hookable;
}

void HookableManager::DisableHookable( const std::string& key )
{
    Hookable* hookable = GetHookable(key);
    hookable->Disconnect();
    if (hookable == m_pActiveHook)
    {
        m_pActiveHook = NULL;
    }
}

