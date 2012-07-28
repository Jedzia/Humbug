#ifndef HOOKABLEMANAGER_H
#define HOOKABLEMANAGER_H

#include <boost/ptr_container/ptr_vector.hpp>
#include "Hookable.h"
#include <map>
#include <string>

class HookableManager {
public:

    HookableManager(CEventHandler* master);
    ~HookableManager();

    void AddHookable(const std::string& key, Hookable *item);
    Hookable* RemoveHookable(const std::string& key);

    void Close();

private:
    CEventHandler* m_pMaster;
    typedef std::map<std::string, Hookable*> HookDictionary;
    HookDictionary m_mapHooks;
    boost::ptr_vector<Hookable> m_pvHooks;
};

#endif // HOOKABLEMANAGER_H
