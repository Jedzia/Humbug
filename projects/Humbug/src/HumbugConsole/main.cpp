/********************************************************************
   created: 2011/07/12 01:37
   filename:  main.cpp
   file path: Humbug/src/HumbugConsole
   copyright:  Jedzia (c) 2011
   License: See accompanying file LICENSE_1_0.txt

   purpose: main module for the 'HumbugConsole' command line template
   generation tool.
 *********************************************************************/
#include "HumbugConsole/stdafx.h"
//#include <tchar.h>
//#include <boost/cstdint.hpp>
//const boost::uint32_t dreck=4;

//#include <iterator>
//#include <fstream>
#include <string>
//#include <wchar.h>
//#include <tchar.h>
//#include <QList>
//#include <QTreeWidgetItem>
//#include <CppStructz/log/Logger.h>
// #include <CppStructz/support/environment.h>

//#include <CppStructz/log/LogHelper.h>
//#include <CppStructz/text/DocLoader.h>
//#include <CppStructz/text/TextDocument.h>

//#include <project.hxx>
#include "ProgOptions.h"
#include <GuiLib/GUI/Components/Point.h>
#include <GuiLib/GUI/Components/Rectangle.h>
#include <Humbug/src/HumbugFileLoader.h>
#include <HumbugLib/src/HumbugLib/AppGB.h>
#include <HumbugLib/src/HumbugLib/LogManager.h>
//#include <HumbugShared/GB.h>
//#include <HumbugShared/Project/ProcessProject.h>
#include <HumbugSerialization/Serialization/VersionToken.h>
#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <iterator>
#include <locale>
#include <regex>
#include <sstream>
#include <vector>
#include <iomanip>
#include <boost/function.hpp>
#include <boost/variant.hpp>
#include <boost/variant/variant.hpp>
#include <boost/variant/get.hpp>

#ifdef WIN32
#  include <process.h>
#endif
//#include "CppStructz/filesystem/CszGlobals.h"
//#include "CppStructz/config/ConfigString.h"
//#include "CppStructz/TestClass.h"

//#pragma message("_CRTDATA2:" STRING(_CRTDATA2))
//using namespace CPPSTRUCTZ_NAMESPACE::text;
using std::cout;
using std::endl;
#define REGISTER_DEC_TYPE(NAME) \
    static DerivedRegister<NAME> reg

#define REGISTER_DEF_TYPE(NAME) \
    DerivedRegister<NAME> NAME::reg(#NAME)

//struct Foo { int a = 1; REGISTER_DEC_TYPE("Foo"); };


struct Foo { int a = 1; };
struct Bar { int b = 2; };
struct Baz { int c = 3; };

//typedef boost::variant<Foo, Bar, Baz> variant_type;
typedef boost::variant<Foo> variant_type;

template<typename T> variant_type createInst() {
    return variant_type(T());
}

//typedef std::map<std::string, variant_type(*)()> map_type;
typedef std::map<std::string, boost::function<variant_type()> > map_type;


struct BaseFactory {

    static boost::function<variant_type()> createInstance(std::string const& s) {
        map_type::iterator it = getMap()->find(s);
        if (it == getMap()->end())
            //return;
           return 0;

        //boost::function0<boost::variant<Foo, Bar, Baz>>::result_type re = it->second();
        return it->second;
    }

//protected:
    static map_type * getMap() {
        // never delete'ed. (exist until program termination)
        // because we can't guarantee correct destruction order 
        if (!map) { map = new map_type; }
        return map;
    }

private:
    static map_type * map;
};

template<typename T>
struct DerivedRegister : BaseFactory {
    DerivedRegister(std::string const& s)
    {
        //boost::function<variant_type()> function = &createInst<T>;
        //auto val = std::make_pair(s, function);
        //getMap()->insert(std::make_pair(s, &createInst<T>));
        
        getMap()->insert(std::pair<std::string, boost::function<variant_type()>>(s, &createInst<T>));
    }
};

//void Foo::Bla()
//{
    //DerivedRegister<Foo> reg1("Foo");
//}

void dingens()
{
    DerivedRegister<Foo> reg1("Foo");
    //DerivedRegister<Bar> reg2("Bar");
    //DerivedRegister<Baz> reg3("Baz");
    //BaseFactory::getMap()->insert(std::make_pair("Foo", &createInst<Foo>));
    //BaseFactory::getMap()->insert(std::make_pair("Foo", &createInst<Foo>));
    //BaseFactory::getMap()->insert(std::pair<std::string, boost::function<variant_type()>>("Foo", &createInst<Foo>));

    auto factory = createInst<Foo>();
    //factory.
    auto x = factory.empty();
    auto y = boost::get<Bar>(factory);;


    boost::variant< int, std::string > v;
    v = "hello";
    std::cout << v << std::endl;
    std::string& str = boost::get<std::string>(v);
    str += " world! ";
}

//ProjectModel *projectModel;
void parseProject() {
    /*QList<QTreeWidgetItem *> items;
       for (int i = 0; i < 10; ++i)
       {
            QTreeWidgetItem * topitem;
            items.append(topitem = new QTreeWidgetItem((QTreeWidget*)0, QStringList(QString("item:
               %1").arg(i))));
            QTreeWidgetItem * subitem;
            topitem->addChild(subitem = new QTreeWidgetItem((QTreeWidget*)0,
               QStringList(QString("Arschloch"))));
            cout << topitem->text(0).toStdString() << endl;
       }
       //ui.prjExplorer->insertTopLevelItems(0, items);*/

    //projectModel = new ProjectModel(this);
    //projectModel = new ProjectModel(NULL);
    //ui.prjView->setModel(projectModel);
    //projectModel->setRootNode(ProjectProcessor::test());
    //ProjectNode *xxx = ProjectProcessor::test();
    //if(projectModel != NULL)
    //  delete projectModel;
    const std::string prjname =
        "D:/E/Projects/C++/Humbug/projects/Humbug/XSD/Nummer1.tmplproj";
} // parseProject

void testChars() {
    //CPPSTRUCTZ_NAMESPACE::TestClass testclass;
    //const std::string testInput("Das is soooo Cool 123");
    //const std::string& testOutput = testclass.testChars(testInput);
    //std::cout << "[TEST] testOutput: " << testOutput << std::endl;
}

/** @class my_ctypeComma:
 *  Detailed description.
 *  @param str TODO
 *  @param maxNum TODO
 *  @return TODO
 */
class my_ctypeComma : public
                      std::ctype<char>{
    mask my_table[table_size];

public:

    my_ctypeComma(size_t refs = 0)
        : ctype<char>(&my_table[0], false, refs) {
        std::copy_n(classic_table(), table_size, my_table);
        //my_table['-'] = (mask)space;
        //my_table['-'] = (mask)space;
        //my_table['\"'] = (mask)space;
        //my_table[' '] = (mask)alpha;
        my_table[','] = static_cast<mask>(blank);
        my_table[';'] = static_cast<mask>(blank);
    }
};

/** @class my_ctypeSpace:
 *  Detailed description.
 *  @param str TODO
 *  @param maxNum TODO
 *  @return TODO
 */
class my_ctypeSpace : public
                      std::ctype<char>{
    mask my_table[table_size];

public:

    my_ctypeSpace(size_t refs = 0)
        : ctype<char>(&my_table[0], false, refs) {
        std::copy_n(classic_table(), table_size, my_table);
        //my_table['-'] = (mask)space;
        //my_table['-'] = (mask)space;
        //my_table['\"'] = (mask)space;
        my_table[' '] = (mask)alpha;
        //my_table[','] = static_cast<mask>(blank);
        //my_table[';'] = static_cast<mask>(space);
    }
};

/** @class my_ctypeIgnore:
 *  Detailed description.
 *  @param str TODO
 *  @param maxNum TODO
 *  @return TODO
 */
class my_ctypeIgnore : public
                       std::ctype<char>{
    mask my_table[table_size];

public:

    my_ctypeIgnore(size_t refs = 0)
        : ctype<char>(&my_table[0], false, refs) {
        std::copy_n(classic_table(), table_size, my_table);
        //my_table['-'] = (mask)space;
        //my_table['-'] = (mask)space;
        //my_table['\"'] = (mask)space;
        //my_table[' '] = static_cast<mask>(alpha);
        my_table['"'] = static_cast<mask>(blank);
        my_table[';'] = static_cast<mask>(blank);
        //my_table[';'] = static_cast<mask>(space);
    }
};

std::vector<std::string> getNextLineAndSplitIntoTokens2(std::istream& str, int maxNum = std::numeric_limits<int>::max()) {
    std::vector<std::string> result;
    std::string line;
    getline(str, line);

    std::stringstream lineStream(line);
    std::string cell;

    std::locale x(std::locale::classic(), new my_ctypeIgnore);
    //lineStream.imbue(x);

    while(maxNum-- && getline(lineStream, cell, ','))
    {
        if(!cell.empty()) {
            using namespace boost::algorithm;
            using namespace std;
            if(cell.find_first_of("\"") == 1) {
                string::size_type xx = cell.find_first_of("\"", 1);
                int xxxx = 0;
                xxxx++;
            }

            //trim_right(cell);
            trim(cell, x);
            result.push_back(cell);
        }
    }
    return result;
} // getNextLineAndSplitIntoTokens2

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str, int maxNum = 1) {
    std::vector<std::string> result;

    std::string cell;

    while(maxNum-- && getline(str, cell, '"'))
    {
        if(!cell.empty()) {
            result.push_back(cell);
        }
    }
    return result;
}

std::string ltrim(std::string str) {
    return regex_replace(str, std::regex("^\\s+"), std::string(""));
}

/** @class CStopWatch:
 *  Detailed description.
 *  @return TODO
 */
class CStopWatch {
private:

    clock_t start;
    clock_t finish;

public:

    double GetDuration() { return (double)(finish - start) / CLOCKS_PER_SEC; }

    void Start() { start = clock(); }

    void Stop() { finish = clock(); }
}; // class CStopWatch

/** @class InfoCTextLoader:
 *  Detailed description.
 *  @return TODO
 */
class InfoCTextLoader {
public:

    typedef std::string linedataelement;

    struct InfoCTextLoaderData
    {
        InfoCTextLoaderData(/*const linedataelement& data, const bool is_comment = false*/)
            : /*data(data),*/ isComment(false) {
        }

        std::string token;
        std::string line;
        std::vector<linedataelement> data;
        bool isComment;
    };

    typedef InfoCTextLoaderData linedatatype;

    /** VersionToken, BlaStr:
     *  Detailed description.
     *  @return TODO
     */
    std::string BlaStr() const { return str; }

    /** VersionToken, BlaStr:
     *  Detailed description.
     *  @param val TODO
     */
    void BlaStr(std::string val) { str = val; }

    /** VersionToken, Language:
     *  Detailed description.
     *  @param x TODO
     *  @return true if vector is not empty
     */
    static bool ReadAndSplitTextLineByComma(std::istream& instream, linedatatype& parsedLineData) {
        using namespace boost;
        std::string tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
        std::string line;
        instream >> tmp1;
        trim(tmp1);
        parsedLineData.line = tmp1;
        parsedLineData.token = tmp1;
        if (!tmp1.empty() && tmp1[0] == '#') {
            auto nc = instream.peek();
            getline(instream, line);
            parsedLineData.line += line;
            trim(line);
            //cout << "Comment: " << line << endl;
            parsedLineData.data.push_back(line);
            parsedLineData.isComment = true;
            return true;
        }
        //std::string line = newstr;
        getline(instream, line);
        /*trim(line);
        if(!line.empty() && line[0] == '#') {
            parsedLineData.push_back(InfoCTextLoaderData ( line, true ));
            return true;
        }*/
        //trim(line);
        //cout << "Line: " << line << endl;
        parsedLineData.line += line;

        //std::vector<std::string> parsedLineData;
        tokenizer<escaped_list_separator<char>> tk(
                line, escaped_list_separator<char>('\\', ',', '\"'));

        for(tokenizer<escaped_list_separator<char>>::iterator i(tk.begin());
            i != tk.end(); ++i)
        {
            auto val = *i;
            static std::locale x(std::locale::classic(), new my_ctypeIgnore);
            //lineStream.imbue(x);
            trim(val, x);
            parsedLineData.isComment = false;
            parsedLineData.data.push_back(val);
        }
        return !parsedLineData.data.empty();
    } // ReadAndSplitTextLineByComma

    friend std::ostream& operator<<(std::ostream& o, const InfoCTextLoader& obj);

    friend std::istream& operator>>(std::istream& i, InfoCTextLoader& obj) {
        using namespace humbug::serialization;
        using namespace std;

        const string msgStart = "[std::istream>>InfoCTextLoader] ";

        string tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
        VersionToken vtok1;

        i >> tmp1;
        if(tmp1 != "InfoCText") {
            string message = msgStart + "First argument is not like <InfoCText>: '" + tmp1 + "'.";
            throw TokenParsingException(message);
        }

        i >> vtok1;
        //auto resultCtextLine = ReadAndSplitTextLineByComma(i);
        linedatatype linedata;

        /*while(ReadAndSplitTextLineByComma(i, vec))
        {
            // do something with the vec text
            vec.clear();
        }*/

        for (size_t lnr = 1; ReadAndSplitTextLineByComma(i, linedata); lnr++)
        {
            if (linedata.isComment)
            {
                stdcOut("[" << setfill('0') << setw(3) << lnr << "]Comment: " << linedata.line);
            }
            else
            {
                stdcOut("[" << setfill('0') << setw(3) << lnr << "]Data   : (" << linedata.data.size() << ") " << linedata.line);
                // parse the stuff
            }

            linedata.data.clear();
        }

        i >> tmp2;
        i >> tmp3;
        i >> tmp4;
        i >> tmp5;

        return i;
    } // >>

private:

    std::string str;
};

void SimulateInOut() {
    using namespace gui::components;

    cout << endl;
    cout << endl;
    cout << endl;
    cout << "Start Simulate" << endl;

    humbuglib::LogManager* mLogManager;
    if(humbuglib::LogManager::getSingletonPtr() == 0) {
        mLogManager = new humbuglib::LogManager();
        mLogManager->createLog("log-console.txt", true, true);
    }

    //std::string exepath = AppGB::Instance().ExePath();
    std::string appDir = AppGB::Instance().AppDir();
    //fl.reset(new HumbugFileLoader(appDir + "base_data"));
    HumbugFileLoader fl(appDir + "base_data");
    //auto str = fl.FL_LOADASSTRING("data/levels/LevelA/Map1.map");
    auto str = fl.FL_LOADASSTRING("data/Tutor/CTextExample.txt");
    std::istringstream instreamCText;
    instreamCText.str(str);

    InfoCTextLoader loader;
    instreamCText >> loader;

    //gui::components::CPoint p1(0, 0);
    CRectangle r1(10, 20, 33, 55);
    cout << "Simulate running" << endl;
    cout << r1 << endl;
    std::ostringstream outstring;
    outstring << r1;
    std::string outFromr1 = outstring.str();

    std::istringstream instream;
    instream.str(outFromr1);
    CRectangle r2;
    //std::cin >> r2;
    instream >> r2;
    cout << r2 << endl;

    {
        std::istringstream instream2;
        instream2.str("\"Older Depp, Du.\"");
        std::locale x(std::locale::classic(), new my_ctypeComma);
        instream2.imbue(x);

        std::string tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
        instream2 >> tmp1;
        instream2 >> tmp2;
        instream2 >> tmp3;
        instream2 >> tmp4;
        instream2 >> tmp5;
    }

    //std::string newstr = "CText Arial, \"Use the up and down arrow or[w] and[s] to move the menu
    // cursor up and down.\", DarkRed;";
    std::string newstr = "CText Arial, 34, \"Use the up and down arrow, or[w] and[s] to move the menu cursor up and down.\", DarkRed;";
    {
        // Boost.StringAlgorithm or Boost.Tokenizer would help
        std::string tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
        std::istringstream instream3;
        instream3.str(newstr);
        //std::locale x(std::locale::classic(), new my_ctypeComma);
        //instream3.imbue(x);

        instream3 >> tmp1;
        //instream3 >> tmp2;
        //instream3 >> tmp3;

        auto spl2 = getNextLineAndSplitIntoTokens2(instream3);
        auto spl3 = getNextLineAndSplitIntoTokens(instream3);

        instream3 >> tmp7;
    }
    {
        std::string delimiters("\",;");
        std::vector<std::string> parts;
        split(parts, newstr, boost::is_any_of(delimiters));
    }

    {
        std::istringstream instream4;
        instream4.str(newstr);
        std::string sin((std::istreambuf_iterator<char>(instream4)),
                std::istreambuf_iterator<char>());

        //std::regex
        // word_regex(",(?!(?<=(?:^|,)\s*\"(?:[^\"]|\"\"|\\\")*,)(?:[^\"]|\"\"|\\\")*\"\s*(?:,|$))");
        std::regex word_regex(",(?=([^\"]*\"[^\"]*\")*[^\"]*$)");
        auto what =
            std::sregex_iterator(sin.begin(), sin.end(), word_regex);
        auto wend = std::sregex_iterator();

        std::vector<std::string> v;

        for(; what != wend; ++what) {
            std::smatch match = *what;
            v.push_back(match.str());
        }
    }

    {
        std::istringstream instream3;
        instream3.str(newstr);
        //std::locale x(std::locale::classic(), new my_ctypeComma);
        //instream3.imbue(x);

        std::string tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
        instream3 >> tmp1;

        //std::string line = newstr;
        std::string line;
        getline(instream3, line);

        std::vector<std::string> vec;
        using namespace boost;
        tokenizer<escaped_list_separator<char>> tk(
                line, escaped_list_separator<char>('\\', ',', '\"'));

        for(tokenizer<escaped_list_separator<char>>::iterator i(tk.begin());
            i != tk.end(); ++i)
        {
            auto val = *i;
            std::locale x(std::locale::classic(), new my_ctypeIgnore);
            //lineStream.imbue(x);
            trim(val, x);

            vec.push_back(val);
        }
    }

    cout << endl;
    cout << endl;
    const int iMax = 500;
    const char* versionString = "Version 1.2.3.4";
    stdcOut(iMax << " * Version parse of '" << versionString << "'.");

    CStopWatch sw;
    sw.Start();
    //std::time()
    humbug::serialization::VersionToken vtok1;

    for(int i = 0; i < iMax; ++i)
    {
        std::istringstream instream3;
        instream3.str(versionString);
        instream3 >> vtok1;
        
        
        /*std::istringstream instreamCText2;
        instreamCText2.str(str);
        //instreamCText2.seekg(std::ios_base::beg);
        InfoCTextLoader loader2;
        instreamCText2 >> loader2;*/

    }
    sw.Stop();
    cout << "Time: " << sw.GetDuration() << endl;
    cout << "VersionToken: " << vtok1 << endl;
    cout << endl;
    cout << endl;

    // Todo: create a version class derived from a token class in the serializer lib
    //       that reads in versioned stuff from iostream.
} // SimulateInOut

int wmain(int ac, hchar_t* av[]) {
//    return 0;
//}

//#if WIN32xsf
//int _tmain(int ac, _TCHAR** av) {
//int _tmain(int ac, hchar_t** av) {
//#else
//int xwmain(int ac, char* av[]) {
//#endif // 0
    //using namespace CPPSTRUCTZ_NAMESPACE::log4csz;

    //using namespace CPPSTRUCTZ_NAMESPACE::support;
    //using namespace CPPSTRUCTZ_NAMESPACE::config;

    //CPPSTRUCTZ_NAMESPACE::CszGlobals::Instance().init(ac,av);

    /*LoggerPtr rootLogger = Logger::getRootLogger();
       rootLogger->debug("Schnauze !");

       LogManager::getLoggerRepository()->setThreshold(
        Level::getInfo());
       rootLogger->debug("Das darf nicht gelogged werden !");

       LogManager::getLoggerRepository()->setThreshold(
        Level::getDebug());
       rootLogger->debug("Muss erscheinen !");*/

    //LOGGER_DEBUG(rootLogger, "Maulaff");
    /*if (LOGGER_UNLIKELY(rootLogger->isDebugEnabled()))
       {
        ::CPPSTRUCTZ_NAMESPACE::log4csz::helpers::MessageBuffer oss_;
        rootLogger->forcedLog(::CPPSTRUCTZ_NAMESPACE::log4csz::Level::getDebug(),
            oss_.str(oss_ << "Labersack"), LOGGER_LOCATION);
       }*/

    //logstream logstream();
    //Level myLevel(4,"depp",6);
    //std::string nase("nase");
    //myLevel.toString(nase);
    /*logstream debuglog(rootLogger, Level::getDebug());
       //logstream << "debug message " ;
       debuglog << "debug message " << LOGGER_ENDMSG;
       //logstream << "debug message " <<
       //   (CPPSTRUCTZ_NAMESPACE::log4csz::logstream_manipulator)
       //   CPPSTRUCTZ_NAMESPACE::log4csz::logstream_base::endmsg;*/
    try
    {
        ProgOptions progOpts(ac, av);

        if(progOpts.isDebugPrint()) {
            //LogManager::getLoggerRepository()->setThreshold(
            //        Level::getDebug() );
        }
        else {
            //LogManager::getLoggerRepository()->setThreshold(
            //        Level::getInfo() );
        }
        
        dingens();
        if(progOpts.isSimulate()) {
            SimulateInOut();
            return 0;
        }

        if(progOpts.isHelpRequested()) {
            testChars();
            return 0;
        }

        if(!progOpts.isValid()) {
            cout << "Program-Options error[" << progOpts.getResult() << "].\n";
            return 1;
        }

        cout << endl;
        cout << ">>> ";

        //std::string s;
        //std::cin >> s;

        // \Todo: Das Option-Setup mit den statischen Daten, wie Workpath und Template
        // spezifischen Interna ( START + END ), sollte in eine extra Setup-Klasse.
    }
    catch(std::exception ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
} // main
