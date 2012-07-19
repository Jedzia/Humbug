#include "stdafx.h"
#include "StartScreen.h"
#include "GUI/Visual/EventHandler.h"
//#include <build/cmake/include/debug.h>
#include "GUI/Components/Rectangle.h"
#include <cstdlib>


StartScreen::StartScreen(CCanvas *background)
: Screen(background)
{
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

StartScreen::~StartScreen(void)
{
    dbgOut(__FUNCTION__ << " " << this << std::endl);
}

const char* StartScreen::language(int x) const
{
    return "AsciiDoc";
}

/*GroupId StartScreen::GetGroupID()
{
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
}*/

bool StartScreen::OnInit( int argc,char* argv[] )
{
   // Master()->GetMainCanvas();
    mcol = CColor::Green();
    return Screen::OnInit(argc, argv);
    //return true;
}

void StartScreen::OnIdle()
{
    //x+= std::random()*5;
}

void StartScreen::OnDraw()
{
    CMainCanvas* m_pMainCanvas = Master()->GetMainCanvas();
    CRectangle frect(400, 300, 85, 85);
    m_pMainCanvas->FillRect( frect, mcol );
    m_pMainCanvas->AddUpdateRect(frect);
    //mcol.SetR(x);
    //mcol.SetG(x/2);
    //mcol.SetB(x);
}

void StartScreen::OnUpdate()
{
    Screen::OnUpdate();
    x += 1 + (rand() << 21);
    mcol.SetR(rand());
    mcol.SetG(rand());
    mcol.SetB(rand());
}

