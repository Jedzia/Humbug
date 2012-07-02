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
//#include <HumbugShared/GB.h>
//#include <HumbugShared/Project/ProcessProject.h>
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

int main(int ac, char* av[]) {
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
    ProgOptions progOpts(ac, av);

    if ( progOpts.isDebugPrint() ) {
        //LogManager::getLoggerRepository()->setThreshold(
        //        Level::getDebug() );
    }
    else {
        //LogManager::getLoggerRepository()->setThreshold(
        //        Level::getInfo() );
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
	
	std::string s;
	std::cin >> s;
	
    // \Todo: Das Option-Setup mit den statischen Daten, wie Workpath und Template 
    // spezifischen Interna ( START + END ), sollte in eine extra Setup-Klasse.

    return 0;
} // main

