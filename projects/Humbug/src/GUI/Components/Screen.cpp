//
#include "stdafx.h"

//
#include "Screen.h"

//#include <build/cmake/include/debug.h>
Screen::Screen() :
    Hookable(this){

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

