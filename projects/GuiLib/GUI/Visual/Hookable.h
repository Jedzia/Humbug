#ifndef HUMBUG_GUI_VISUAL_HOOKABLE_H
#define HUMBUG_GUI_VISUAL_HOOKABLE_H

//#include "Eventhandler.h"
#include <boost/ptr_container/ptr_vector.hpp>
#include "boost/smart_ptr/scoped_ptr.hpp"
#include <boost/noncopyable.hpp>

namespace gui {
    class CMaster;

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

    /** Get timing ticks.
    *  Retrieves the ticks (or FPS frames per second) run by the application.
    *  @return The current ticks that are run by the application.
    */
    int GetTicks() const;

    friend class HookableManager;

protected:
    static GroupId s_GrpID;

    // add child hook
    Hookable(bool hook);
    virtual GroupId GetGroupID();

    static GroupId CreateNextGroupID();
    CMaster* Master() const { return m_pMaster; }
    void Connect(/*Hookable* controller*/);
    void Disconnect();

    virtual void OnConnect(/*Hookable* controller*/) = 0;
    virtual void OnDisconnect() = 0;

private:
    void Init(CMaster *Master, Hookable *controller);
    void HandleIdle(int ticks);

	//static boost::ptr_vector<Hookable> m_pvHooks;
    //static Hookable* m_pController;
    struct HookableImpl;
    boost::scoped_ptr<HookableImpl> pimpl_;
    CMaster *m_pMaster;
    Hookable *m_pController;
    static GroupId s_NextGrpID;

    GroupId m_grpID;
    bool m_bIsInitialized;
    int m_iTicks;
};

class TestHookable : public Hookable
{
public:
    TestHookable();
    virtual ~TestHookable();

    GroupId GetGroupID() override;

    void OnIdle(int ticks) override;

    void OnConnect() override;

    void OnDisconnect() override;

protected:
private:
};


} // namespace gui

#endif // HUMBUG_GUI_VISUAL_HOOKABLE_H guard
