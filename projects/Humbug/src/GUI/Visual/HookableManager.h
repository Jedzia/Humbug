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
#ifndef HOOKABLEMANAGER_H
#define HOOKABLEMANAGER_H

#include "Hookable.h"
#include <boost/shared_ptr.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
#include <map>
#include <string>

class HookCreator {
public:
    virtual Hookable* Create()= 0;
};

typedef boost::shared_ptr<HookCreator> HookCreatorPtr;

class HookableManager {
public:

    HookableManager(CEventHandler* master);
    ~HookableManager();

    void RegisterHookable(std::string key, HookCreatorPtr generator);
    void UnregisterHookable(std::string key);

    void AddHookable(std::string key, Hookable* item, bool connectMe = false);
    Hookable * GetHookable(const std::string& key);
    void RemoveHookable(const std::string& key);

    void EnableHookable(const std::string& key);
    void DisableHookable(const std::string& key);

    void Close();

    void Test1();
    void Test2();

private:

    CEventHandler* m_pMaster;

    //typedef std::map<std::string, Hookable*> HookDictionary;
    typedef boost::ptr_map<std::string, Hookable> HookDictionary;
    HookDictionary m_mapHooks;
    boost::ptr_vector<Hookable> m_pvHooks;
    typedef std::map<std::string, HookCreatorPtr> HookRegistryDictionary;
    HookRegistryDictionary m_mapRegistry;
    Hookable* m_pActiveHook;
};
#endif // HOOKABLEMANAGER_H
