#include "../stdafx.h"
#include <stdio.h>
#include <windows.h>

//#include <build/cmake/include/debug.h>
namespace HumbugLIB_NAMESPACE {
	namespace internal {

		std::string getExePath()
		{
			char result[ MAX_PATH ];
			return std::string( result, GetModuleFileNameA( NULL, result, MAX_PATH ) );
		}

		std::string buildAppDir(const std::string& exePath)
		{
			std::string::size_type lastdirpos = exePath.find_last_of("\\");
			std::cout << "Dirpos at '" << lastdirpos << "'." << std::endl;
			return exePath.substr(0, lastdirpos + 1);
		}
	}
}
