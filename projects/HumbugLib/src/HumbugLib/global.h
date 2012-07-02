#ifndef HumbugLIB_GLOBAL_H
#define HumbugLIB_GLOBAL_H

#ifdef __cplusplus
extern "C"
{
#endif

#define STRING2(x) #x
#define STRING(x) STRING2(x)

#define HumbugLIB_NAMESPACE sk64lib
#define HumbugLIB_BEGIN_NAMESPACE namespace Support { namespace HumbugLIB_NAMESPACE {
#define HumbugLIB_END_NAMESPACE } }
#define HumbugLIB_USE_NAMESPACE using namespace Support::HumbugLIB_NAMESPACE;

#undef PRJ_NAMESPACE
#define PRJ_NAMESPACE Support::HumbugLIB_NAMESPACE

// Set the function export visibility and reset all global
// PLATFORM vars cause they interfere with multiple libraries and the
// use of library.cmake. This behavior can be overridden by defining
// EXPLICITELY_USE_PLATFORM_VARS.
#ifndef EXPLICITELY_USE_PLATFORM_VARS
#undef PLATFORM_ALL_DYN_LINK
#ifdef HumbugLib_ALL_DYN_LINK
#	ifndef PLATFORM_ALL_DYN_LINK
#		define PLATFORM_ALL_DYN_LINK 1
#	endif
#endif

#undef PLATFORM_SOURCE
#ifdef HumbugLib_SOURCE
#	define PLATFORM_SOURCE 1
#endif

#undef PLATFORM_ALL_STATIC_LINK
#ifdef HumbugLib_ALL_STATIC_LINK
#	ifndef PLATFORM_ALL_STATIC_LINK
#		define PLATFORM_ALL_STATIC_LINK 1
#	endif
#endif
#endif // EXPLICITELY_USE_PLATFORM_VARS

#undef PLATFORM_DECL
#include "build/cmake/include/platform.h"

/*#ifdef HAVE_CONFIG_H
#	include <config.h>
#endif*/

#ifndef qWarning
#  define qWarning printf
#endif

#ifdef __cplusplus
}
#endif

#include "cpp0xfix.h"

#endif //HumbugLIB_GLOBAL_H