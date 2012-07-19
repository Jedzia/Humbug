#include "stdafx.h"
#include "StartScreen.h"

//#include <build/cmake/include/debug.h>


StartScreen::StartScreen()
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

GroupId StartScreen::GetGroupID()
{
    static GroupId grpID = CreateNextGroupID();
    return grpID;
    //throw std::exception("The method or operation is not implemented.");
}

