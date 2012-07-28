#ifndef HUMBUG_GUI_VISUAL_HOOKABLE_H
#define HUMBUG_GUI_VISUAL_HOOKABLE_H

//#include "Eventhandler.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include "boost/smart_ptr/scoped_ptr.hpp"

class CEventHandler;

//message id
typedef int GroupId;

class Hookable : boost::noncopyable {
public:

	// initialize master set
    Hookable(CEventHandler* master);
    virtual ~Hookable();

    static void Close();
    bool IsMaster() const;

    //initialization
    virtual bool OnInit(int argc,char* argv[]);

    virtual void OnIdle(int frameNumber);
    friend class HookableManager;

protected:
    static GroupId s_GrpID;

    // add child hook
    Hookable(bool hook);
    virtual GroupId GetGroupID();

    static GroupId CreateNextGroupID();
    CEventHandler* Master() const { return m_pMaster; }

private:
    void Init(CEventHandler* Master, Hookable* controller);

	static boost::ptr_vector<Hookable> m_pvHooks;
    static Hookable* m_pController;
    static CEventHandler* m_pMaster;
    static GroupId s_NextGrpID;

    struct HookableImpl;
    boost::scoped_ptr<HookableImpl> pimpl_;
    GroupId m_grpID;
    bool m_bIsInitialized;
};

class TestHookable : Hookable
{
public:
    TestHookable();
    virtual ~TestHookable();

    virtual GroupId GetGroupID();

protected:
private:
};


#endif // HUMBUG_GUI_VISUAL_HOOKABLE_H guard
