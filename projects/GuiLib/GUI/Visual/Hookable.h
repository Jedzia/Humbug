#ifndef HUMBUG_GUI_VISUAL_HOOKABLE_H
#define HUMBUG_GUI_VISUAL_HOOKABLE_H

//#include "Eventhandler.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include "boost/smart_ptr/scoped_ptr.hpp"
#include <boost/noncopyable.hpp>

namespace gui {

class CEventHandler;

//message id
typedef int GroupId;

class Hookable : boost::noncopyable {
public:

	// initialize master set
    //Hookable(CEventHandler* master);
    virtual ~Hookable();

    //static void Close();
    //bool IsMaster() const;

    //initialization
    virtual bool OnInit(int argc,char* argv[]);

    /** Idle frame-loop.
    *  Is called once per frame, before OnDraw().
    *  @param ticks frame ticks counter.
    */
    virtual void OnIdle(int ticks) = 0;
    friend class HookableManager;

protected:
    static GroupId s_GrpID;

    // add child hook
    Hookable(bool hook);
    virtual GroupId GetGroupID();

    static GroupId CreateNextGroupID();
    CEventHandler* Master() const { return m_pMaster; }
    void Connect(/*Hookable* controller*/);
    void Disconnect();

    virtual void OnConnect(/*Hookable* controller*/) = 0;
    virtual void OnDisconnect() = 0;

private:
    void Init(CEventHandler *Master, Hookable *controller);

	//static boost::ptr_vector<Hookable> m_pvHooks;
    //static Hookable* m_pController;
    struct HookableImpl;
    boost::scoped_ptr<HookableImpl> pimpl_;
    CEventHandler *m_pMaster;
    Hookable *m_pController;
    static GroupId s_NextGrpID;

    GroupId m_grpID;
    bool m_bIsInitialized;
};

class TestHookable : public Hookable
{
public:
    TestHookable();
    virtual ~TestHookable();

    void OnIdle(int ticks);
    virtual GroupId GetGroupID();

    virtual void OnConnect();

    virtual void OnDisconnect();

protected:
private:
};


} // namespace gui

#endif // HUMBUG_GUI_VISUAL_HOOKABLE_H guard
