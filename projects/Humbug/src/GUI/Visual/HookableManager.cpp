#include "stdafx.h"
#include "HookableManager.h"
#include <stdexcept>
#include <utility>
#include "EventHandler.h"

//#include <build/cmake/include/debug.h>

namespace gui {

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

         //TestHookable *nn = HookCreator<TestHookable>::Create();
}

HookableManager::~HookableManager(void)
{
         //dbgOut(__FUNCTION__ << std::endl);
}

void HookableManager::Close()
{
    dbgOut(__FUNCTION__ << std::endl);
    m_mapHooks.release();
    m_mapRegistry.clear();
}

void HookableManager::AddHookable(std::string key, Hookable *item, bool connectMe )
{
    dbgOut(__FUNCTION__ << " Adding Hook " << key << "(" << item << ")" /*<< std::endl*/);
    if ( m_mapHooks.find(key) == m_mapHooks.end() )
    {
        //m_mapHooks.insert( std::make_pair(key, item) );
        // http://www.boost.org/doc/libs/1_50_0/libs/ptr_container/doc/tutorial.html
        m_mapHooks.insert( key, item );
        item->Init(m_pMaster, item);
        item->OnInit(NULL,NULL);
        if (connectMe)
        {
            //item->Connect();
            EnableHookable(key);
        }
        dbgOut(", [" << typeid( *item ).name() << "] (" << this << ")" << std::endl);
    }
    else
    {
        throw std::runtime_error("AddHookable-Creator method already specified for index=" + key); // interface requirement
    }
}

Hookable* HookableManager::GetHookable( const std::string& key )
{
    dbgOut(__FUNCTION__ << " Searching Hook '" << key << "'." << std::endl);

    HookDictionary::iterator found =  m_mapHooks.find(key);
    if ( found == m_mapHooks.end() )
    {
        HookRegistryDictionary::iterator regfound =  m_mapRegistry.find(key);
        if ( regfound == m_mapRegistry.end() )
        {
            std::string msg = "GetHookable found no matching key ";
            msg += "'" + key + "'.";
            throw std::runtime_error(msg);
        }
        else
        {
            dbgOut(__FUNCTION__ << " Creating Hook '" << key << "' from factory." << std::endl);
            Hookable* hookable = regfound->second->Create();
            AddHookable(key, hookable);
            return hookable;
        }
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
        m_pMaster->GetMainCanvas()->AddUpdateRect(m_pMaster->GetMainCanvas()->GetDimension());
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

void HookableManager::RegisterHookable( std::string key, HookCreatorPtr generator )
{
    m_mapRegistry.insert(std::make_pair(key, generator));
}

void HookableManager::UnregisterHookable( std::string key )
{

}

} // namespace gui

