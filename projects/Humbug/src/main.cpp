//
#include "stdafx.h"
#include <malloc.h>
#include <stdio.h>

/*void dumpMallinfo(void) {
    struct mallinfo m = mallinfo();
    printf("uordblks = %d\nfordblks = %d\n", m.uordblks, m.fordblks);
}*/

//
//#include <build/cmake/include/debug.h>

std::string getexepath()
  {
  char result[ MAX_PATH ];
  return std::string( result, GetModuleFileNameA( NULL, result, MAX_PATH ) );
  }

int bmain(int argc, char *argv[])
{

//    _CRT_DEBUG_BLOCK

    //std::ofstream myfile ("D:/E/Projects/C++/Humbug/build/Humbug/src/Debug/test2.txt");
    //xout = myfile;

//    int *depp2 = new int(4);
//    QApplication app(argc, argv);
//	QString plugpath(QString::fromStdString(CszGlobals::Instance().getInstallPath() + "/plugins"));
//	QStringList plugpaths(plugpath);
//	//app.addLibraryPath(plugpath);
//	app.setLibraryPaths(plugpaths);
//	//app.addLibraryPath("D:\\E\\Projects\\C++\\Humbug\\build\\Humbug\\Debug\\plugins\\");
//	//app.addLibraryPath("D:/E/Projects/C++/Humbug/build/Humbug/Debug/plugins");
//	//app.addLibraryPath("D:/E/Projects/C++/Humbug/build/Humbug/Debug/plugins/");
//    //CalculatorForm calculator;
//    //calculator.show();

//    MainWindow mainwindow;
//    mainwindow.resize(1024, 768);
//    mainwindow.show();
//    int *moppen = new int(55);
    


    //std::string *oukk = new std::string("Olde Nase");
    
    
    //TestClass *xxx = new TestClass();
    {
    //TestClass yyy(3);
    //yyy.getSelectedText();
    }
    //delete oukk;
//    int ff = app.exec();
    int ff = 0;
	std::cout << std::endl << "This is Humbug (" << argv[0] << ")." << std::endl;
	std::string exepath(getexepath());
    std::cout << "Starting at '" << exepath << "'." << std::endl;
	std::string::size_type lastdirpos = exepath.find_last_of("\\");
	std::cout << "Dirpos at '" << lastdirpos << "'." << std::endl;
	std::string purepath = exepath.substr(0, lastdirpos + 1);
	std::cout << "purepath '" << purepath << "'." << std::endl;

//    const char* explanation = "Hy there from _RPT1.";
//_RPT1( _CRT_WARN, "\n\n%s:\n**************************************\
//************************************\n", explanation );

    //int *depp = new int(4);

    //freopen( "c:\\log2.txt", "w", stderr);
    //freopen( "log2.txt", "w", stderr);
//    _CrtDumpMemoryLeaks( );
    return ff;
}

