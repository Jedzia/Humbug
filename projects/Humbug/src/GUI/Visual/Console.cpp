//
#include "../../stdafx.h"

//
#include "Console.h"
#include "SDL.h"

//
#include "DT_drawtext.h"
#include "SDL_console.h"
#include "internal.h"

#include <functional> 
#include <algorithm> 
#include <iostream> 
#include <boost/bind.hpp> 
#include "boost/bind/mem_fn.hpp"
//#include <tr1/functional>
#include "boost/function.hpp"
#include <vector>
#include <map>

//#include <build/cmake/include/debug.h>
struct CConsole::CConsoleImpl {
   void Command_Handler(ConsoleInformation* console, char* command) {
        if (command) {
            int abc = 3;
            abc++;
        }

        /*int argc;
           char* argv[128];
           char* linecopy;*/
        /*linecopy = strdup(command);
           argc = splitline(argv, (sizeof argv)/(sizeof argv[0]), linecopy);
           if(!argc) {
                free(linecopy);
                return;
           }*/
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
        /*if(!strcmp(argv[0], "quit"))
                KillProgram();
           else if(!strcmp(argv[0], "echo"))
                Echo(console, argc, argv);
           else if(!strcmp(argv[0], "drawtextdemo"))
                DrawTextDemo();
           else if(!strcmp(argv[0], "alpha"))
                AlphaChange(console, argc, argv);
           else if(!strcmp(argv[0], "background"))
                AddBackground(console, argc, argv);
           else if(!strcmp(argv[0], "move"))
                Move(console, argc, argv);
           else if(!strcmp(argv[0], "resize"))
                Resize(console, argc, argv);
           else if(!strcmp(argv[0], "listcommands"))
                ListCommands(console);
           else if(!strcmp(argv[0], "prompt"))
                SetPrompt(console, argc, argv);*/
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
    static void* pt2Object;
    
    ~CConsoleImpl()
    {
        m_vCmdCallbacks.erase(m_pConsole);
    }

    // static wrapper-function to be able to callback the member function Display()
    static void Wrapper_To_Call_Display(void* pt2Object, ConsoleInformation* console, char* command)
    {
        // explicitly cast to a pointer to TClassA
        CConsole::CConsoleImpl* mySelf = (CConsole::CConsoleImpl*) pt2Object;

        // call member
        mySelf->Command_Handler(console, command);
    }
    void (*fnc)(ConsoleInformation *, char* );
    //typedef fnc  rotz;
    typedef std::map<ConsoleInformation*, CConsole::CConsoleImpl*> callbackDict;
    static callbackDict m_vCmdCallbacks;


    // static wrapper-function to be able to callback the member function Display()
    static void Wrapper_To_Call_CommandHandler(ConsoleInformation* console, char* command)
    {
        // explicitly cast global variable <pt2Object> to a pointer to TClassB
        // warning: <pt2Object> MUST point to an appropriate object!
        //CConsole::CConsoleImpl* mySelf = (CConsole::CConsoleImpl*) pt2Object;

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
        return;

        using namespace boost;
        //std::cout << s_ << "\n";
        pt2Object = this;
        //fnc = &CConsole::CConsoleImpl::Command_Handler;
        fnc = &CConsole::CConsoleImpl::Wrapper_To_Call_CommandHandler;
        //CON_SetExecuteFunction(m_pConsole, &CConsole::CConsoleImpl::Command_Handler);
        //CON_SetExecuteFunction(m_pConsole, &CConsole::CConsoleImpl::Wrapper_To_Call_CommandHandler);
        CON_SetExecuteFunction(m_pConsole, Wrapper_To_Call_CommandHandler);
        
        //CON_SetExecuteFunction(m_pConsole, bind(Wrapper_To_Call_Display, this));
        //CON_SetExecuteFunction(m_pConsole, bind(&CConsole::CConsoleImpl::Wrapper_To_Call_Display, this, _1));
        
        //CON_SetExecuteFunction(m_pConsole, boost::mem_fn(&CConsole::CConsoleImpl::Wrapper_To_Call_Display);
        
        //CON_SetExecuteFunction(m_pConsole, (void(ConsoleInformation , char* ))&CConsole::CConsoleImpl::Command_Handler);

        //bind(CON_SetExecuteFunction, m_pConsole, _1)( Wrapper_To_Call_CommandHandler);
        //bind(CON_SetExecuteFunction, m_pConsole, bind(&CConsole::CConsoleImpl::Wrapper_To_Call_Display, _1))( this );

        char* crs = "Blafasel";
        //bind(&CConsole::CConsoleImpl::Wrapper_To_Call_Display, this, _1, _2)(m_pConsole, crs);
        // void* CConsole::CConsoleImpl::pt2Object = NULL;
        // 
        //void (*fnc)(ConsoleInformation *, char* );
        //void* olderdepp;

        boost::function<void(CConsole::CConsoleImpl*, ConsoleInformation* console, char* command)> bound;
        bound = &CConsole::CConsoleImpl::Command_Handler;
        //bound = std::bind1st(
         //   std::mem_fun(&CConsole::CConsoleImpl::Command_Handler), this);
        bound(this, m_pConsole, crs);
        
        //CON_SetExecuteFunction(m_pConsole, bound); 

        //olderdepp = static_cast<void*>( &bound);
        //olderdepp = static_cast<void *>( &bound);
        //fnc = (void (__cdecl *)(ConsoleInformation *,char *))olderdepp;
        //fnc(m_pConsole, crs);
        //CON_SetExecuteFunction(m_pConsole, bound); 

        //olderdepp = bind(&CConsole::CConsoleImpl::Wrapper_To_Call_Display, this, _1, _2);
        //boost::mem_fn(&CConsole::CConsoleImpl::Command_Handler)(this, m_pConsole, crs); 
        //CON_SetExecuteFunction(m_pConsole, boost::bind(boost::mem_fn(&CConsole::CConsoleImpl::Command_Handler),this,_1,_2)); 

        // Error	1	error C2664: 'CON_SetExecuteFunction' : cannot convert parameter 2 from 
        // 'void (__cdecl CConsole::CConsoleImpl::* )(ConsoleInformation *,char *)' to 
        // 'void (__cdecl *)(ConsoleInformation *,char *)'

        // void(*CmdFunction)(struct console_information_td *console, char* command);	/*! The Function that is executed if you press 'Return' in the console */
        // char*(*TabFunction)(char* command);	/*! The Function that is executed if you press 'Tab' in the console */
        std::cout << "Uint32 Size: " << sizeof(Uint32) << std::endl;
        //std::cout << "sizeof(&CConsole::CConsoleImpl::Wrapper_To_Call_CommandHandler) Size: " << sizeof(CConsole::CConsoleImpl::Wrapper_To_Call_CommandHandler) << std::endl;
        std::cout << "boost::function<void(CConsole::CConsoleImpl*, ConsoleInformation* console, char* command)> Size: " << sizeof(boost::function<void(CConsole::CConsoleImpl*, ConsoleInformation* console, char* command)>) << std::endl;
        std::cout << "void (*fnc)(ConsoleInformation *, char* ) Size: " << sizeof(fnc) << std::endl;



    }

    struct X
    {
        bool f(int a);
        void g();
    };


    void Depp(){
        using namespace boost;

        X x;

        shared_ptr<X> p(new X);

        int i = 5;

        bind(&X::f, ref(x), _1)(i);		// x.f(i)
        bind(&X::f, &x, _1)(i);			//(&x)->f(i)
        bind(&X::f, x, _1)(i);			// (internal copy of x).f(i)
        bind(&X::f, p, _1)(i);			// (internal copy of p)->f(i)

        std::vector<X> v;
        std::for_each(v.begin(), v.end(), boost::mem_fn(&X::g));

        boost::mem_fn(&X::f)(x, 3); 
    }


    std::tr1::function <void (ConsoleInformation* console, char* command)> _callback;

    void reg_callback(std::tr1::function <void (ConsoleInformation* console, char* command)> callback)
    {
        _callback = callback;
    }


    std::string s_;
    ConsoleInformation* m_pConsole;
};

void* CConsole::CConsoleImpl::pt2Object = NULL;
CConsole::CConsoleImpl::callbackDict CConsole::CConsoleImpl::m_vCmdCallbacks;

// function does something which implies a callback
// note: of course this function can also be a member function
void DoItA(void* pt2Object, void (*pt2Function)(void* pt2Object, char* text))
{
    /* do something */

    pt2Function(pt2Object, "hi, i'm calling back using a argument ;-)");  // make callback
}

typedef void* (CConsole::CConsoleImpl::*MemFun)(void*);

void Cmd_Handler(ConsoleInformation* console, char* command) 
{
    if (command) {
        int abc = 3;
        abc++;
    }
}




CConsole::CConsole( const std::string& fontName, CCanvas* displayScreen, int lines,
        CRectangle rect ) :
    pimpl_(new CConsole::CConsoleImpl ),
    m_pScreen(displayScreen),
    m_crDimensions(rect){
    dbgOut(__FUNCTION__ << std::endl);
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
    m_bIsVisible = !m_bIsVisible;

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

//std::ostream& operator<<(std::ostream& o, const CConsole& r) {
//    return o << "CConsole[ X=" /*<< r.GetX() << ", Y=" << r.GetY()
//        << ", W=" << r.GetW() << ", H=" << r.GetH()
//        <<*/ " ]";
//}
