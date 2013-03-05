//
#include "../../stdafx.h"

//
#include "Console.h"
#include "SDL.h"
#include "../Visual/EventHandler.h"
#include <string.h>

//
#include "DT_drawtext.h"
#include "SDL_console.h"
#include "internal.h"
#include "split.h"

//#include <functional>
//#include <algorithm>
#include <iostream>
//#include <boost/bind.hpp>
//#include "boost/bind/mem_fn.hpp"
//#include <tr1/functional>
//#include "boost/function.hpp"
//#include <vector>
#include <map>

#ifdef MSYS
	//_CRTIMP char* __cdecl __MINGW_NOTHROW	strdup (const char*) __MINGW_ATTRIB_MALLOC;
#endif

namespace gui {

//#include <build/cmake/include/debug.h>
struct CConsole::CConsoleImpl {
   void Command_Handler(ConsoleInformation* console, char* command) {
       return;
//        int argc;
//           char* argv[128];
        //   char* linecopy;
        //linecopy = strdup(command);
       //    argc = splitline(argv, (sizeof argv)/(sizeof argv[0]), linecopy);
       //    if(!argc) {
       //         free(linecopy);
      //          return;
       //    }
        /*	This command handler is very stupid. Normally you would save your commands
                using an array of char* and pointers to functions. You will need something like this
                anyway if you want to make use of the tabfunction because you will have
                to implement the tabulator completion search function yourself

                To make myself clear: I use this construct in my own programs:

                typedef struct {
                        char* commandname;
                        int (*my_func)(int argc, char* argv[]);
                } command_t;

                command_t* cmd_table[] = {
                                                                { "quit", quit_function },
                                                                { "alpha", set_alpha },
                                                                { NULL, NULL }
                                                                };

                and to search for a command:

                command_t* cmd;

                for (cmd = cmd_table; cmd->commandname; cmd++) {
                        if(!strcasecmd(cmd->commandname, argv[0])) {
                                command found, now start the function
                                return cmd->myfunc;
                        }
                }
                if we land here: command not found

                etc..

         */
//        if(!strcmp(argv[0], "quit"))
//                KillProgram();
           //else if(!strcmp(argv[0], "echo"))
             //   Echo(console, argc, argv);
           //else if(!strcmp(argv[0], "drawtextdemo"))
             //   DrawTextDemo();
           //else if(!strcmp(argv[0], "alpha"))
             //   AlphaChange(console, argc, argv);
           //else if(!strcmp(argv[0], "background"))
             //   AddBackground(console, argc, argv);
           //else if(!strcmp(argv[0], "move"))
             //   Move(console, argc, argv);
           //else if(!strcmp(argv[0], "resize"))
             //   Resize(console, argc, argv);
//           else if(!strcmp(argv[0], "listcommands"))
//                ListCommands(console);
           //else if(!strcmp(argv[0], "prompt"))
             //   SetPrompt(console, argc, argv);*/

    }

   void KillProgram()
   {
       m_ceParent->SendMessageQ(CEventHandler::MSGID_QuitApp);
   }

    void ListCommands(ConsoleInformation* console) {
        CON_Out(console, "quit");
        CON_Out(console, "echo");
        CON_Out(console, "drawtextdemo");
        CON_Out(console, "alpha");
        CON_Out(console, "background");
        CON_Out(console, "move");
        CON_Out(console, "resize");
        CON_Out(console, "listcommands");
        CON_Out(console, "prompt");
    }

    ~CConsoleImpl()
    {
        m_vCmdCallbacks.erase(m_pConsole);
    }

    typedef std::map<ConsoleInformation*, CConsole::CConsoleImpl*> callbackDict;
    static callbackDict m_vCmdCallbacks;


    // static wrapper-function to be able to callback the member function Display()
    static void Wrapper_To_Call_CommandHandler(ConsoleInformation* console, char* command)
    {
        callbackDict::iterator it = m_vCmdCallbacks.find(console);
        if(it != m_vCmdCallbacks.end())
        {
            //    cout << "value:" << (*it).second
            CConsole::CConsoleImpl* mySelf =(*it).second;
            // call member
            mySelf->Command_Handler(console, command);
        }
    }

    static void Add_CommandHandler( ConsoleInformation* console, CConsole::CConsoleImpl* cimpl)
    {
        m_vCmdCallbacks.insert(std::make_pair(console, cimpl));
        CON_SetExecuteFunction(console, Wrapper_To_Call_CommandHandler);
    }

    void InitCommandHandler() {
        Add_CommandHandler(m_pConsole, this);
    }

    CConsoleImpl(CEventHandler* parent)
        : m_ceParent(parent)
    {

    }

    std::string s_;
    CEventHandler* m_ceParent;
    ConsoleInformation* m_pConsole;
};

CConsole::CConsoleImpl::callbackDict CConsole::CConsoleImpl::m_vCmdCallbacks;

CConsole::CConsole(CEventHandler* parent, const std::string& fontName, gui::components::CCanvas* displayScreen, int lines,
        gui::components::CRectangle rect ) :
    pimpl_(new CConsole::CConsoleImpl(parent) ) ,
    m_pScreen(displayScreen),
    m_crDimensions(rect){
    dbgOut(__FUNCTION__ << std::endl);

    pimpl_->m_ceParent = parent;
    pimpl_->m_pConsole = CON_Init(fontName.c_str(), displayScreen->GetSurface(), lines, rect);
    pimpl_->ListCommands(pimpl_->m_pConsole);

    //CON_SetExecuteFunction(pimpl_->m_pConsole, Cmd_Handler);
    pimpl_->InitCommandHandler();

    //CON_Show(pimpl_->m_pConsole);
    CON_Topmost(pimpl_->m_pConsole);
    m_bIsVisible = false;
}

CConsole::~CConsole(void){
    CON_Destroy(pimpl_->m_pConsole);

    //delete pimpl_->m_pConsole;
    dbgOut(__FUNCTION__ << std::endl);
}

void CConsole::Draw( void ) const {
    if (pimpl_->m_pConsole->Visible != CON_CLOSED) {
        CON_DrawConsole(pimpl_->m_pConsole);
        m_pScreen->AddUpdateRect(m_crDimensions);
    }
}

void CConsole::Toggle( void ){
    //m_bIsVisible = !m_bIsVisible;
    m_bIsVisible = !(CON_isVisible(pimpl_->m_pConsole) != 0);

    if (m_bIsVisible) {
        CON_Show(pimpl_->m_pConsole);
    }
    else {
        CON_Hide(pimpl_->m_pConsole);
    }
}

bool CConsole::OnEvent( SDL_Event* pEvent ){
    if( !CON_Events(pEvent) ) {
        //continue;
        int abc = 123;
        abc++;
        return true;
    }
    else {
        int abc = 123;
        abc++;
        return false;
    }
}

void CConsole::DoSomething( void )
{
    //m_pScreen->
}

//std::ostream& operator<<(std::ostream& o, const CConsole& r) {
//    return o << "CConsole[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
//        << ", W=" << r.GetW() << ", H=" << r.GetH()
//        <<*/ " ]";
//}

} // namespace gui

