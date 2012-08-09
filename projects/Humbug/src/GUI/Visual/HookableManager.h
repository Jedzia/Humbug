#ifndef HOOKABLEMANAGER_H
#define HOOKABLEMANAGER_H

#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_map.hpp>
#include "Hookable.h"
#include <map>
#include <string>

class HookableManager {
public:

    HookableManager(CEventHandler* master);
    ~HookableManager();

    void AddHookable(std::string key, Hookable *item, bool connectMe = false);
    Hookable* GetHookable(const std::string& key);
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

    Hookable *m_pActiveHook;
};

#endif // HOOKABLEMANAGER_H
