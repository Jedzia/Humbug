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

    void AddHookable(std::string key, Hookable *item);
    Hookable* GetHookable(const std::string& key);
    void RemoveHookable(const std::string& key);

    void Close();

private:
    CEventHandler* m_pMaster;
    //typedef std::map<std::string, Hookable*> HookDictionary;
    typedef boost::ptr_map<std::string, Hookable> HookDictionary;
    HookDictionary m_mapHooks;
    boost::ptr_vector<Hookable> m_pvHooks;
};

#endif // HOOKABLEMANAGER_H
