#ifndef BUILD_CMAKE_INCLUDE_DEBUG_H
#define BUILD_CMAKE_INCLUDE_DEBUG_H
#ifdef _DEBUG
#  include <iostream>
#  if defined(_MSC_VER)
#    include <windows.h>
#    ifdef DEBUG_MEMORY
#      define _CRTDBG_MAP_ALLOC
#      include <crtdbg.h>
#      include <stdlib.h>
#      ifndef DEBUG_NEW
#        define DEBUG_NEW new (_NORMAL_BLOCK, __FILE__, __LINE__)
#        define new DEBUG_NEW
#      endif
#    if defined(DEBUG_MEMORY_STDOUT)

#define _CRT_DEBUG_BLOCK_MODE _CRTDBG_MODE_DEBUG
// #define _CRT_DEBUG_BLOCK_MODE _CRTDBG_MODE_FILE
//#        define _CRT_DEBUG_BLOCK_MODE _CRTDBG_MODE_WNDW
#        define _CRT_DEBUG_BLOCK_OUTPUT _CRTDBG_FILE_STDOUT

//#define _CRT_DEBUG_BLOCK_OUTPUT _CRTDBG_FILE_STDERR
#        define _CRT_DEBUG_BLOCK  \
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); \
    _RPT0(_CRT_WARN, __FILE__ ); \
                                \
    _CrtSetReportMode(_CRT_WARN, _CRT_DEBUG_BLOCK_MODE); \
    _CrtSetReportFile(_CRT_WARN, _CRT_DEBUG_BLOCK_OUTPUT); \
    _CrtSetReportMode(_CRT_ERROR, _CRT_DEBUG_BLOCK_MODE);  \
    _CrtSetReportFile(_CRT_ERROR, _CRT_DEBUG_BLOCK_OUTPUT); \
    _CrtSetReportMode(_CRT_ASSERT, _CRT_DEBUG_BLOCK_MODE); \
    _CrtSetReportFile(_CRT_ASSERT, _CRT_DEBUG_BLOCK_OUTPUT); \
\
\
\
\
    _CrtDumpMemoryLeaks(); \
    _RPT0(_CRT_ERROR, "XXXXXXXXXX AFTER APP\n"); \
    _RPT0(_CRT_WARN, "file message\n"); \
    _RPT0(_CRT_WARN, __FILE__ ); \
    _RPT0(_CRT_WARN, "\n");
#      else //DEBUG_MEMORY_STDOUT
#   ifdef DEBUG_MEMORY_SUMMARY_ON_EXIT 
#   define _CRT_DEBUG_BLOCK  \
    HANDLE hLogFile; \
    hLogFile = CreateFile("D:\\debug_log.txt", GENERIC_WRITE, \
        FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, \
        FILE_ATTRIBUTE_NORMAL, NULL); \
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE); \
    _CrtSetReportFile(_CRT_WARN, hLogFile); \
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);  \
    _CrtSetReportFile(_CRT_ERROR, hLogFile); \
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE); \
    _CrtSetReportFile(_CRT_ASSERT, hLogFile); \
\
    _RPT0(_CRT_WARN, "file message\n"); \
/*   CloseHandle(hLogFile);*/ \
\
    _RPT0(_CRT_WARN, __FILE__ ); \
\
/*    _CrtDumpMemoryLeaks();*/ \
    _RPT0(_CRT_WARN, "file message\n"); \
    _RPT0(_CRT_WARN, __FILE__ ); \
    _RPT0(_CRT_WARN, "\n"); \
    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF ); \

#   else //DEBUG_MEMORY_SUMMARY_ON_EXIT

#   define _CRT_DEBUG_BLOCK  \
    HANDLE hLogFile; \
    hLogFile = CreateFile(L"c:\\debug_log.txt", GENERIC_WRITE, \
    FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, \
    FILE_ATTRIBUTE_NORMAL, NULL); \
    _CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE); \
    _CrtSetReportFile(_CRT_WARN, hLogFile); \
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);  \
    _CrtSetReportFile(_CRT_ERROR, hLogFile); \
    _CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE); \
    _CrtSetReportFile(_CRT_ASSERT, hLogFile); \
    \
    _RPT0(_CRT_WARN, "file message\n"); \
    /*   CloseHandle(hLogFile);*/ \
\
    _RPT0(_CRT_WARN, __FILE__ ); \
\
/*    _CrtDumpMemoryLeaks();*/ \
    _RPT0(_CRT_WARN, "file message\n"); \
    _RPT0(_CRT_WARN, __FILE__ ); \
    _RPT0(_CRT_WARN, "\n");

#   endif //DEBUG_MEMORY_SUMMARY_ON_EXIT

#      endif //DEBUG_MEMORY_STDOUT
#    else //DEBUG_MEMORY
#      define _CRT_DEBUG_BLOCK
#    endif //DEBUG_MEMORY
#  else // defined(_MSC_VER)
#    define _CRT_DEBUG_BLOCK
#    define _RPT0(x)
#    define _RPT1(x, y, z)
#    define _CrtDumpMemoryLeaks(x)
#  endif // defined(_MSC_VER)
#  define DEBUG_CTORDTOR //Todo: move this definition to cmake options.
#  ifdef DEBUG_CTORDTOR
#    define _DEBUG_CTORDTOR(_XXX) std::cout << __FUNCTION__ << "| " << _XXX << " called" << \
    std::endl
#  else
#    define _DEBUG_CTORDTOR(_XXX)
#  endif // DEBUG_CTORDTOR
#  define _DEBUG_COUT(_XXX) std::cout << _XXX << std::endl
#  define _DEBUG_CERR(_XXX) std::cout << _XXX << std::endl
#else //_DEBUG
#  ifndef _MSC_VER
#    define _RPT0(x)
#    define _RPT1(x, y, z)
#    define _CrtDumpMemoryLeaks(x)
#  endif
#  define _CRT_DEBUG_BLOCK
#  define _DEBUG_CTORDTOR(_XXX)
#  define _DEBUG_COUT(_XXX)
#  define _DEBUG_CERR(_XXX)
#endif //_DEBUG
#endif // BUILD_CMAKE_INCLUDE_DEBUG_H
