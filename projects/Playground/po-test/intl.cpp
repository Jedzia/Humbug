#include <iostream>

#ifdef USE_NLS

#include <iostream>
#include <string>
#include <libintl.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <CppStructz/filesystem/CszGlobals.h>
#include <CppStructz/support/docstring.h>
#include <CppStructz/support/debug.h>
#include <CppStructz/log/LogHelper.h>

#ifndef PACKAGE
#  define PACKAGE "Playground"
#endif
#include <CppStructz/support/gettext.h>
#include <CppStructz/support/Messages.h>


//#include <TCHAR.H>

//#include "boost/filesystem.hpp"

#define CSZ_FILESYSTEM_THROW(EX) throw EX

//using namespace boost::filesystem;
using namespace std;

//using boost::system::error_code;
//using boost::system::error_category;
//using boost::system::system_category;

/*
class MyClass
{
public:
    MyClass(){ }
    void throwError()
    {
        CSZ_FILESYSTEM_THROW(filesystem_error("Cannot Determine Application Executable Path!",
            error_code(5, system_category())));
    }
};
*/

#define _T(string) gettext (string)

string const getEnv(string const & envname);
#ifdef WIN32
#  define HAVE_PUTENV 1
#else
#  define HAVE_SETENV 1
#endif
bool setEnv(string const & name, string const & value);

#ifdef WIN32
# include <windows.h>
#endif

void FirstRealm()
{
    // Some gettext related info at http://php.net/manual/en/ref.gettext.php
    using namespace CPPSTRUCTZ_NAMESPACE;
    namespace csz=CPPSTRUCTZ_NAMESPACE;
    cszerr.setStream(cerr);
    cszerr.setLevel(Debug::ANY);

    std::string instPath = csz::CszGlobals::Instance().getInstallPath();
    instPath += "/locale";


    //const string lang("en");
    //"English_United States.1252"
    //const char *rotz = setlocale( LC_ALL, "en_US" );

    //const string lang(rotz);
    const string lang("en");
    static string oldLC_ALL;
    static string oldLANGUAGE;
    docstring dreck;
    //setEnv("LANGUAGE", lang);

    //setlocale( LC_ALL, "en_US.UTF-8" );
    //setlocale( LC_ALL, "English" );
    //const char *locsettings = setlocale( LC_ALL, NULL );
    //const char *rotz = setlocale( LC_ALL, lang.c_str() );
    //setlocale( LC_MESSAGES , "en" );
    //setlocale( 5 , "en" );
    // From http://www.gnu.org/software/gettext/FAQ.html#windows_setenv
    // http://msdn.microsoft.com/en-us/library/2kzt1wy3%28v=vs.80%29.aspx
    // http://mail.gnome.org/archives/gtk-app-devel-list/2008-May/msg00080.html
    //SetEnvironmentVariableA("LANG", lang.c_str());
    /*if (!SetEnvironmentVariableA("LANGUAGE", lang.c_str()))
        CSZERR(Debug::LOCALE, "Setting LANGUAGE... failed!");
    if (!SetEnvironmentVariableA("LANG", lang.c_str()))
        CSZERR(Debug::LOCALE, "Setting LANG... failed!");
    SetEnvironmentVariableA("LC_ALL", lang.c_str());
    setEnv("LANGUAGE", lang);
    setEnv("LANG", lang);
    setEnv("LC_ALL", lang);

    const char * nowlocale = setlocale( LC_ALL, "" );*/

    //static char *envlang = "LANGUAGE=en\0";
    //putenv(envlang);
    //system("set");
    /*oldLANGUAGE = getEnv("LANGUAGE");
    if ( !lang.empty() ) {
        oldLC_ALL = getEnv("LC_ALL");

        // This GNU extension overrides any language locale
        // wrt gettext.
        CSZERR(Debug::LOCALE, "Setting LANGUAGE to " << lang);
        oldLANGUAGE = getEnv("LANGUAGE");
        CSZERR(Debug::LOCALE, "oldLC_ALL = " << oldLC_ALL);
        CSZERR(Debug::LOCALE, "oldLANGUAGE = " << oldLANGUAGE);

        if ( !setEnv("LANGUAGE", lang) ) {
            CSZERR(Debug::LOCALE, "\t... failed!");
        }
        if ( !setEnv("LANG", lang) ) {
            CSZERR(Debug::LOCALE, "\t... failed!");
        }
    }*/
    CSZERR(Debug::LOCALE, "new LANGUAGE is " << getEnv("LANGUAGE"));

    bindtextdomain( "Playground", instPath.c_str() );
    textdomain( "Playground" );
    printf( gettext( "CHANGE!" ) );
    printf( gettext( "Hello, world!\n" ) );
    printf( "CHANGE!" );
    printf( "\nArschloch!\n" );
    wprintf( L"Fuck, you!\n" );
    wprintf( L"Fuck, yourself!\n" );
    printf( _T("Fuck, yourself!\n") );
    //wprintf(L"Ölder DöppForsch %lc\n", L'Ä');
    //wprintf( gettext( "Hello, world!\n" ) );

    //csz::char_type *c =  L"Ê" ;
    //csz::docstring ds("depp");
    csz::docstring ds;
    ds.push_back(L'a');
    std::string ss = "Arschloch";
    std::cout << ss.c_str() << std::endl;
    //wprintf(L"Die char %ls\n", ds);
}

void docstrLocalization()
{
    using namespace CPPSTRUCTZ_NAMESPACE;
    cout << "MOOOOOO" << endl;
    cszerr.setStream(cerr);
    //cszerr.setStream(csz::dbg);
    cszerr.setLevel(Debug::ANY);
    CSZERR(Debug::KEY, "Lick my Ass of!");
    //CSZERR(Debug::LOCALE, from_utf8(docstring(L"Default language not found!")));
    const char * masc = "Drecks ASCII";
    const wchar_t * wide = L"Drecks Wide";

    const docstring& fasc = from_ascii(masc);
    //const docstring wdocs(L"Older");

    docstring older(_("Thats an docstring!"));
    docstring older2(_("Thats another docstring!"));
    docstring older3(_("Yippieh."));
    CSZERR(Debug::ACTION, older);
    CSZERR(Debug::ACTION, older2);

    CSZERR(Debug::LOCALE, masc);
    //CSZERR(Debug::LOCALE, docstring(from_utf8(wide)));
    CSZERR(Debug::LOCALE, fasc);

    Messages mesgs;
    mesgs.init();
    docstring fckw(mesgs.get("Yippieh."));
    std::cout << "This is _X ->" << _X<Messages>() << std::endl;
    CSZERR(Debug::ACTION, "Trans from Yippieh. is: " << fckw);
    CSZERR(Debug::ACTION, "Trans with _Z(mesgs). is: " << _Z(mesgs));
    CSZERR(Debug::ACTION, "");
    //CSZERR(Debug::ACTION, "Now use _Y(Thats an docstring!). is: " << _Y("Thats an docstring!"));
    CSZERR(Debug::ACTION, "Now use _(Thats an docstring!). is: " << _("Thats an docstring!"));

    CSZERR(Debug::ACTION, "Now use one with args: " << _("The arg %s is now %d"));
    msgs_setlang("ru");
    CSZERR(Debug::ACTION, "CHANGE!: " << _("CHANGE!"));


}

int main(int argc, char *argv[])
{
    using namespace CPPSTRUCTZ_NAMESPACE;
    //using namespace CPPSTRUCTZ_NAMESPACE::text;
    //std::cout << "This is " << PACKAGE << std::endl;

    FirstRealm();
    //docstrLocalization();
    csz::dbg << "Ending Execution" << LOGGER_ENDMSG;





	exit(0);

    /*MyClass m;
    try
    {
        m.throwError();
    }
    catch (filesystem_error &e)
    {
        std::cout << "exception is: " << e.what() << std::endl;
    }*/
}

string const getEnv(string const & envname)
{
    // f.ex. what about error checking?
    char const * const ch = getenv( envname.c_str() );

    //return ch ? to_utf8(from_local8bit(ch)) : string();
    return ch ? string(ch) : string();
}

bool setEnv(string const & name, string const & value)
{
    // CHECK Look at and fix this.
    // f.ex. what about error checking?
    //string const encoded = to_local8bit(from_utf8(value));
    string const encoded = value;
#if defined (HAVE_SETENV)
    return ::setenv(name.c_str(), encoded.c_str(), 1) == 0;

#elif defined (HAVE_PUTENV)
    static map<string, string> varmap;
    varmap[name] = name + '=' + encoded;
    return ::putenv( const_cast<char *>( varmap[name].c_str() ) ) == 0;

#else
#  error No environment-setting function has been defined.
#endif
    return false;
} // setEnv
#else //USE_NLS
int main(int argc, char *argv[])
{
	std::cout << "Not using NLS" << std::endl;
	exit(0);
}


#endif //USE_NLS
