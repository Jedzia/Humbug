#ifndef HUMBUG_GUI_VISUAL_HOOKABLE_H
#define HUMBUG_GUI_VISUAL_HOOKABLE_H

//#include "Eventhandler.h"
#include <boost/ptr_container/ptr_vector.hpp>
class CEventHandler;

class Hookable : boost::noncopyable {
public:

	// initialize master set
    Hookable(CEventHandler* master);
    virtual ~Hookable();

    static void Close();
    bool IsMaster() const;

protected:
    // add child hook
    Hookable(Hookable* hook);
private:
	static boost::ptr_vector<Hookable> m_pvHooks;
    static Hookable* m_pController;
    static CEventHandler* m_pMaster;
};

class TestHookable : Hookable
{
public:
    TestHookable();
    virtual ~TestHookable();
protected:
private:
};


#endif // HUMBUG_GUI_VISUAL_HOOKABLE_H guard
