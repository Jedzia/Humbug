/*---------------------------------------------------------*/
/*!
 * This file is part of Humbug, the strangest game ever.
 * License details can be found in the file COPYING.
 * Copyright (c) 2012, EvePanix. All rights reserved.
 *
 * \brief      This file contains the definition of
 *             the HookableManager.h class.
 * \folder     $(folder)
 * \file       HookableManager.h
 * \date       2012-07-10
 * \author     Jedzia.
 *
 * modified    2012-07-10, Jedzia
 */
/*---------------------------------------------------------*/
#ifndef HUMBUG_GUI_VISUAL_HOOKABLEMANAGER_H
#define HUMBUG_GUI_VISUAL_HOOKABLEMANAGER_H

#include "Hookable.h"
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <string>

namespace gui {
    class HookCreator {
public:
    /*HookCreator()
    {
        dbgOut(__FUNCTION__ << " [" << typeid( *this ).name() << "] (" << this << ")");
    };*/
    virtual Hookable* Create()= 0;

protected:
    virtual ~HookCreator()
    {
#ifdef WIN32
        dbgOut(__FUNCTION__ << " (" << this << ")");
#endif
    };
};

template <typename T>
class DefaultHookCreator : public HookCreator {
public:
    /*DefaultHookCreator()
    {
        dbgOut(__FUNCTION__ << " (" << this << ")");
    };*/
   Hookable* Create(){
        return new T;
    }
};

typedef boost::shared_ptr<HookCreator> HookCreatorPtr;

class HookableManager {
public:

    //HookableManager(CEventHandler* master);
    HookableManager(CMaster* master);
    ~HookableManager();

    // Register a factory hook-type creator.
    void RegisterHookable(std::string key, HookCreatorPtr generator);
    // Unregister it.
    void UnregisterHookable(std::string key);

    // Add an existing hook instance.
    void AddHookable(std::string key, Hookable* item, bool connectMe = false);
    // Request the instance by its key name. Todo: to private and for the public return a shared_ptr/protected ctor for Hookables.
    Hookable * GetHookable(const std::string& key);
    // Remove an existing hook instance. This deletes the instance.
    void RemoveHookable(const std::string& key);

    // Switch the Hookable with the given key to status event-processing ON.
    void EnableHookable(const std::string& key);
    // Switch the Hookable with the given key to status event-processing OFF.
    void DisableHookable(const std::string& key = "");

    // Cleanup all registered and instantiated Hookables.
    void Close();

    void Test1();
    void Test2();

    bool IsHookActive() const
    {
        return m_pActiveHook != NULL;
    }

private:

    CMaster* m_pMaster;

    //typedef std::map<std::string, Hookable*> HookDictionary;
    typedef boost::ptr_map<std::string, Hookable> HookDictionary;
    HookDictionary m_mapHooks;
    boost::ptr_vector<Hookable> m_pvHooks;
    typedef std::map<std::string, HookCreatorPtr> HookRegistryDictionary;
    HookRegistryDictionary m_mapRegistry;
    Hookable* m_pActiveHook;
};

} // namespace gui

#endif // HUMBUG_GUI_VISUAL_HOOKABLEMANAGER_H
