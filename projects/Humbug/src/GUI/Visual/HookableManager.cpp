#include "stdafx.h"
#include "HookableManager.h"
#include <stdexcept>
#include <utility>

//#include <build/cmake/include/debug.h>


HookableManager::HookableManager(CEventHandler* master)
: m_pMaster(master)
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

void HookableManager::AddHookable(std::string key, Hookable *item )
{
    dbgOut(__FUNCTION__ << " Adding Hook " << key << "(" << item << ")" << std::endl);
    if ( m_mapHooks.find(key) == m_mapHooks.end() )
    {
        //m_mapHooks.insert( std::make_pair(key, item) );
        // http://www.boost.org/doc/libs/1_50_0/libs/ptr_container/doc/tutorial.html
        m_mapHooks.insert( key, item );
        item->Init(m_pMaster, item);
    }
    else
    {
        throw std::runtime_error("Creator method already specified for index=" + key); // interface requirement
    }
}

Hookable* HookableManager::GetHookable( const std::string& key )
{
    dbgOut(__FUNCTION__ << " Removing Hook " << key << std::endl);

    HookDictionary::iterator found =  m_mapHooks.find(key);
    if ( m_mapHooks.find(key) == m_mapHooks.end() )
    {
        throw std::runtime_error("RemoveHookable found nothing to remove."); // interface requirement
    }

    return found->second;
}

void HookableManager::RemoveHookable( const std::string& key )
{
    //m_mapHooks.release(key);
}

