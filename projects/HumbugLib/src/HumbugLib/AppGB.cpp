#include "stdafx.h"
#include "AppGB.h"
#include <stdio.h>

//#include <build/cmake/include/debug.h>
namespace HumbugLIB_NAMESPACE {
namespace internal {

	extern std::string getExePath();
	extern std::string buildAppDir(const std::string& exePath);

}
}

AppGB::AppGB()
{
	using namespace HumbugLIB_NAMESPACE::internal;
	exePath = getExePath();

	std::cout << "Starting at '" << exePath << "'." << std::endl;
	appDir = buildAppDir( exePath );
	std::cout << "appDir '" << appDir << "'." << std::endl;

}

AppGB::~AppGB()
{

}



