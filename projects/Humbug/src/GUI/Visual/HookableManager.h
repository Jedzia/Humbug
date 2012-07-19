#ifndef HOOKABLEMANAGER_H
#define HOOKABLEMANAGER_H

#include <boost/ptr_container/ptr_vector.hpp>
#include "Hookable.h"

class HookableManager {
public:

    HookableManager();
    ~HookableManager();

    void Close();

private:
    boost::ptr_vector<Hookable> m_pvHooks;
};

#endif // HOOKABLEMANAGER_H
