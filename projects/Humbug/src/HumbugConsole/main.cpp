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
#include <locale>
#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <sstream>

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

//ProjectModel *projectModel;
void parseProject(){
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
    //	delete projectModel;
    const std::string prjname =
        "D:/E/Projects/C++/Humbug/projects/Humbug/XSD/Nummer1.tmplproj";
} // parseProject

void testChars() {
    //CPPSTRUCTZ_NAMESPACE::TestClass testclass;
    //const std::string testInput("Das is soooo Cool 123");
    //const std::string& testOutput = testclass.testChars(testInput);
    //std::cout << "[TEST] testOutput: " << testOutput << std::endl;
}

class my_ctype : public
    std::ctype<char>
{
    mask my_table[table_size];
public:
    my_ctype(size_t refs = 0)
        : std::ctype<char>(&my_table[0], false, refs)
    {
        std::copy_n(classic_table(), table_size, my_table);
        //my_table['-'] = (mask)space;
        //my_table['-'] = (mask)space;
        my_table['\"'] = (mask)space;
        my_table[' '] = (mask)alpha;
    }
};

std::vector<std::string> getNextLineAndSplitIntoTokens(std::istream& str)
{
    std::vector<std::string>   result;
    std::string                line;
    std::getline(str, line);

    std::stringstream          lineStream(line);
    std::string                cell;

    while (std::getline(lineStream, cell, '"'))
    {
        if (!cell.empty())
        {
            result.push_back(cell);
        }
    }
    return result;
}

void SimulateInOut()
{
    using namespace gui::components;

    humbuglib::LogManager *mLogManager;
    if (humbuglib::LogManager::getSingletonPtr() == 0)
    {
        mLogManager = new humbuglib::LogManager();
        mLogManager->createLog("log-console.txt", true, true);
    }

    //std::string exepath = AppGB::Instance().ExePath();
    std::string appDir = AppGB::Instance().AppDir();
    //fl.reset(new HumbugFileLoader(appDir + "base_data"));
    HumbugFileLoader fl(appDir + "base_data");
    auto str = fl.FL_LOADASSTRING("data/levels/LevelA/Map1.map");

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

    std::istringstream instream2;
    instream2.str("\"Older Depp, Du.\"");
    std::locale x(std::locale::classic(), new my_ctype);
    instream2.imbue(x);

    std::string tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    instream2 >> tmp1;
    instream2 >> tmp2;
    instream2 >> tmp3;
    instream2 >> tmp4;
    instream2 >> tmp5;

    std::istringstream instream3;
    instream3.str("\"Older Depp, Du.\" CRect[ Bozer");
    auto spl2 = getNextLineAndSplitIntoTokens(instream3);


}

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

    if ( progOpts.isDebugPrint() ) {
        //LogManager::getLoggerRepository()->setThreshold(
        //        Level::getDebug() );
    }
    else {
        //LogManager::getLoggerRepository()->setThreshold(
        //        Level::getInfo() );
    }

    if (progOpts.isSimulate()) {
        SimulateInOut();
        return 0;
    }

    if ( progOpts.isHelpRequested() ) {
        testChars();
        return 0;
    }

    if ( !progOpts.isValid() ) {
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
    catch (std::exception ex)
    {
        cout << ex.what() << endl;
    }

    return 0;
} // main

