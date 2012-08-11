#ifndef CPLUG_GLOBAL_H
#define CPLUG_GLOBAL_H

#ifdef __cplusplus
extern "C"
{
#endif

#define STRING2(x) #x
#define STRING(x) STRING2(x)

#define TEMPLATES_NAMESPACE tpl
#define TEMPLATES_BEGIN_NAMESPACE namespace TEMPLATES_NAMESPACE {
#define TEMPLATES_END_NAMESPACE }
#define TEMPLATES_USE_NAMESPACE using namespace TEMPLATES_NAMESPACE;

#undef PRJ_NAMESPACE
#define PRJ_NAMESPACE TEMPLATES_NAMESPACE

// Set the function export visibility and reset all global
// PLATFORM vars cause they interfere with multiple libraries and the
// use of library.cmake. This behavior can be overridden by defining
// EXPLICITELY_USE_PLATFORM_VARS.
#ifndef EXPLICITELY_USE_PLATFORM_VARS
#undef PLATFORM_ALL_DYN_LINK
#ifdef Templates_ALL_DYN_LINK
#	ifndef PLATFORM_ALL_DYN_LINK
#		define PLATFORM_ALL_DYN_LINK 1
#	endif
#endif

#undef PLATFORM_SOURCE
#ifdef Templates_SOURCE
#	define PLATFORM_SOURCE 1
#endif

#undef PLATFORM_ALL_STATIC_LINK
#ifdef Templates_ALL_STATIC_LINK
#	ifndef PLATFORM_ALL_STATIC_LINK
#		define PLATFORM_ALL_STATIC_LINK 1
#	endif
#endif
#endif // EXPLICITELY_USE_PLATFORM_VARS

#undef PLATFORM_DECL
#include "build/cmake/include/platform.h"

#ifndef qWarning
#  define qWarning printf
#endif

#ifdef __cplusplus
}
#endif
#endif //CPLUG_GLOBAL_H
