//
#include "stdafx.h"

//
#include "Screen.h"
#include "MainCanvas.h"
#include "GUI/Visual/Application.h"
#include "GUI/Visual/EventHandler.h"
#include "boost/signals.hpp"
#include "boost/bind.hpp"

namespace gui {
namespace components {

//#include <build/cmake/include/debug.h>
Screen::Screen( CCanvas *background )
    : Hookable(true)//, CMessageHandler()
   // , m_pMainScreen(mainScreen)
    {

    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

Screen::~Screen(void){

    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

GroupId Screen::GetGroupID(){

    static GroupId grpID = CreateNextGroupID();
    return grpID;

    //throw std::exception("The method or operation is not implemented.");
}

bool Screen::OnInit( int argc,char* argv[] )
{

    //Screen *screen = static_cast<Screen *>(hook);
    bool result = Hookable::OnInit(argc, argv);
    //Master()->ConnectOnDraw(boost::bind(&Screen::OnDraw, boost::ref(*hook)));
    //Master()->ConnectOnDraw((const CApplication::slot_type_event&)boost::bind(&Screen::OnIdle, boost::ref(*hook)));
    //Master()->ConnectOnDraw((const CApplication::slot_type_event&)boost::bind(&Screen::OnDraw, boost::ref(*screen)));

    //m_conDraw = Master()->ConnectOnDraw(boost::bind(&Screen::OnDraw, boost::ref(*this)));
    //m_conUpdate = Master()->ConnectOnUpdate(boost::bind(&Screen::OnUpdate, boost::ref(*this)));
    return result;
}

void Screen::OnUpdate()
{

}

void Screen::OnIdle( int frameNumber )
{
    //throw std::exception("The method or operation is not implemented.");
}

void Screen::OnConnect()
{
    //Hookable::Connect();
    m_conDraw = Master()->ConnectOnDraw(boost::bind(&Screen::OnDraw, boost::ref(*this)));
    m_conUpdate = Master()->ConnectOnUpdate(boost::bind(&Screen::OnUpdate, boost::ref(*this)));
}

void Screen::OnDisconnect()
{
    //Hookable::Disconnect();
    m_conDraw.disconnect();
    m_conUpdate.disconnect();
}

/*bool Screen::OnInit( int argc,char* argv[] )
{
    return Hookable::OnInit(argc, argv);
    //throw std::exception("The method or operation is not implemented.");
    //return true;
}*/

} // namespace components
} // namespace gui
