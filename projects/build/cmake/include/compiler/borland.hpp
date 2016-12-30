//  (C) Copyright John Maddock 2001 - 2003.
//  (C) Copyright David Abrahams 2002 - 2003.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Borland C++ compiler setup:

//
// versions check:
// we don't support Borland prior to version 5.4:
#if __BORLANDC__ < 0x540
#  error "Compiler not supported or configured - please reconfigure"
#endif

// last known compiler version:
#if (__BORLANDC__ > 0x613)
//#  if defined(PLATFORM_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
//#  else
//#     pragma message( "Unknown compiler version - please run the configure tests and report the results")
//#  endif
#elif (__BORLANDC__ == 0x600)
#  error "CBuilderX preview compiler is no longer supported"
#endif

//
// Support macros to help with standard library detection
#if (__BORLANDC__ < 0x560) || defined(_USE_OLD_RW_STL)
#  define PLATFORM_BCB_WITH_ROGUE_WAVE
#elif __BORLANDC__ < 0x570
#  define PLATFORM_BCB_WITH_STLPORT
#else
#  define PLATFORM_BCB_WITH_DINKUMWARE
#endif

//
// Version 5.0 and below:
#   if __BORLANDC__ <= 0x0550
// Borland C++Builder 4 and 5:
#     define PLATFORM_NO_MEMBER_TEMPLATE_FRIENDS
#     if __BORLANDC__ == 0x0550
// Borland C++Builder 5, command-line compiler 5.5:
#       define PLATFORM_NO_OPERATORS_IN_NAMESPACE
#     endif
// Variadic macros do not exist for C++ Builder versions 5 and below
#define PLATFORM_NO_CXX11_VARIADIC_MACROS
#   endif

// Version 5.51 and below:
#if (__BORLANDC__ <= 0x551)
#  define PLATFORM_NO_CV_SPECIALIZATIONS
#  define PLATFORM_NO_CV_VOID_SPECIALIZATIONS
#  define PLATFORM_NO_DEDUCED_TYPENAME
// workaround for missing WCHAR_MAX/WCHAR_MIN:
#ifdef __cplusplus
#include <climits>
#include <cwchar>
#else
#include <limits.h>
#include <wchar.h>
#endif // __cplusplus
#ifndef WCHAR_MAX
#  define WCHAR_MAX 0xffff
#endif
#ifndef WCHAR_MIN
#  define WCHAR_MIN 0
#endif
#endif

// Borland C++ Builder 6 and below:
#if (__BORLANDC__ <= 0x564)

#  if defined(NDEBUG) && defined(__cplusplus)
      // fix broken <cstring> so that Boost.test works:
#     include <cstring>
#     undef strcmp
#  endif
   // fix broken errno declaration:
#  include <errno.h>
#  ifndef errno
#     define errno errno
#  endif

#endif

//
// new bug in 5.61:
#if (__BORLANDC__ >= 0x561) && (__BORLANDC__ <= 0x580)
   // this seems to be needed by the command line compiler, but not the IDE:
#  define PLATFORM_NO_MEMBER_FUNCTION_SPECIALIZATIONS
#endif

// Borland C++ Builder 2006 Update 2 and below:
#if (__BORLANDC__ <= 0x582)
#  define PLATFORM_NO_SFINAE
#  define PLATFORM_BCB_PARTIAL_SPECIALIZATION_BUG
#  define PLATFORM_NO_TEMPLATE_TEMPLATES

#  define PLATFORM_NO_PRIVATE_IN_AGGREGATE

#  ifdef _WIN32
#     define PLATFORM_NO_SWPRINTF
#  elif defined(linux) || defined(__linux__) || defined(__linux)
      // we should really be able to do without this
      // but the wcs* functions aren't imported into std::
#     define PLATFORM_NO_STDC_NAMESPACE
      // _CPPUNWIND doesn't get automatically set for some reason:
#     pragma defineonoption PLATFORM_CPPUNWIND -x
#  endif
#endif

#if (__BORLANDC__ <= 0x613)  // Beman has asked Alisdair for more info
   // we shouldn't really need this - but too many things choke
   // without it, this needs more investigation:
#  define PLATFORM_NO_LIMITS_COMPILE_TIME_CONSTANTS
#  define PLATFORM_NO_IS_ABSTRACT
#  define PLATFORM_NO_FUNCTION_TYPE_SPECIALIZATIONS
#  define PLATFORM_NO_USING_TEMPLATE
#  define PLATFORM_SP_NO_SP_CONVERTIBLE

// Temporary workaround
#define PLATFORM_MPL_CFG_NO_PREPROCESSED_HEADERS
#endif

// Borland C++ Builder 2008 and below:
#  define PLATFORM_NO_INTEGRAL_INT64_T
#  define PLATFORM_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#  define PLATFORM_NO_DEPENDENT_NESTED_DERIVATIONS
#  define PLATFORM_NO_MEMBER_TEMPLATE_FRIENDS
#  define PLATFORM_NO_TWO_PHASE_NAME_LOOKUP
#  define PLATFORM_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
#  define PLATFORM_NO_NESTED_FRIENDSHIP
#  define PLATFORM_NO_TYPENAME_WITH_CTOR
#if (__BORLANDC__ < 0x600)
#  define PLATFORM_ILLEGAL_CV_REFERENCES
#endif

//
//  Positive Feature detection
//
// Borland C++ Builder 2008 and below:
#if (__BORLANDC__ >= 0x599)
#  pragma defineonoption PLATFORM_CODEGEAR_0X_SUPPORT -Ax
#endif
//
// C++0x Macros:
//
#if !defined( PLATFORM_CODEGEAR_0X_SUPPORT ) || (__BORLANDC__ < 0x610)
#  define PLATFORM_NO_CXX11_CHAR16_T
#  define PLATFORM_NO_CXX11_CHAR32_T
#  define PLATFORM_NO_CXX11_DECLTYPE
#  define PLATFORM_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#  define PLATFORM_NO_CXX11_EXTERN_TEMPLATE
#  define PLATFORM_NO_CXX11_RVALUE_REFERENCES
#  define PLATFORM_NO_CXX11_SCOPED_ENUMS
#  define PLATFORM_NO_CXX11_STATIC_ASSERT
#else
#  define PLATFORM_HAS_ALIGNOF
#  define PLATFORM_HAS_CHAR16_T
#  define PLATFORM_HAS_CHAR32_T
#  define PLATFORM_HAS_DECLTYPE
#  define PLATFORM_HAS_EXPLICIT_CONVERSION_OPS
#  define PLATFORM_HAS_REF_QUALIFIER
#  define PLATFORM_HAS_RVALUE_REFS
#  define PLATFORM_HAS_STATIC_ASSERT
#endif

#define PLATFORM_NO_CXX11_AUTO_DECLARATIONS
#define PLATFORM_NO_CXX11_AUTO_MULTIDECLARATIONS
#define PLATFORM_NO_CXX11_CONSTEXPR
#define PLATFORM_NO_CXX11_DECLTYPE_N3276
#define PLATFORM_NO_CXX11_DEFAULTED_FUNCTIONS
#define PLATFORM_NO_CXX11_DELETED_FUNCTIONS
#define PLATFORM_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define PLATFORM_NO_CXX11_HDR_INITIALIZER_LIST
#define PLATFORM_NO_CXX11_LAMBDAS
#define PLATFORM_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define PLATFORM_NO_CXX11_NULLPTR
#define PLATFORM_NO_CXX11_RANGE_BASED_FOR
#define PLATFORM_NO_CXX11_RAW_LITERALS
#define PLATFORM_NO_CXX11_RVALUE_REFERENCES
#define PLATFORM_NO_CXX11_SCOPED_ENUMS
#define PLATFORM_NO_SFINAE_EXPR
#define PLATFORM_NO_CXX11_TEMPLATE_ALIASES
#define PLATFORM_NO_CXX11_UNICODE_LITERALS    // UTF-8 still not supported
#define PLATFORM_NO_CXX11_VARIADIC_TEMPLATES
#define PLATFORM_NO_CXX11_NOEXCEPT
#define PLATFORM_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define PLATFORM_NO_CXX11_USER_DEFINED_LITERALS
#define PLATFORM_NO_CXX11_ALIGNAS
#define PLATFORM_NO_CXX11_TRAILING_RESULT_TYPES
#define PLATFORM_NO_CXX11_INLINE_NAMESPACES
#define PLATFORM_NO_CXX11_REF_QUALIFIERS
#define PLATFORM_NO_CXX11_FINAL
#define PLATFORM_NO_CXX11_THREAD_LOCAL

// C++ 14:
#if !defined(__cpp_aggregate_nsdmi) || (__cpp_aggregate_nsdmi < 201304)
#  define PLATFORM_NO_CXX14_AGGREGATE_NSDMI
#endif
#if !defined(__cpp_binary_literals) || (__cpp_binary_literals < 201304)
#  define PLATFORM_NO_CXX14_BINARY_LITERALS
#endif
#if !defined(__cpp_constexpr) || (__cpp_constexpr < 201304)
#  define PLATFORM_NO_CXX14_CONSTEXPR
#endif
#if !defined(__cpp_decltype_auto) || (__cpp_decltype_auto < 201304)
#  define PLATFORM_NO_CXX14_DECLTYPE_AUTO
#endif
#if (__cplusplus < 201304) // There's no SD6 check for this....
#  define PLATFORM_NO_CXX14_DIGIT_SEPARATORS
#endif
#if !defined(__cpp_generic_lambdas) || (__cpp_generic_lambdas < 201304)
#  define PLATFORM_NO_CXX14_GENERIC_LAMBDAS
#endif
#if !defined(__cpp_init_captures) || (__cpp_init_captures < 201304)
#  define PLATFORM_NO_CXX14_INITIALIZED_LAMBDA_CAPTURES
#endif
#if !defined(__cpp_return_type_deduction) || (__cpp_return_type_deduction < 201304)
#  define PLATFORM_NO_CXX14_RETURN_TYPE_DEDUCTION
#endif
#if !defined(__cpp_variable_templates) || (__cpp_variable_templates < 201304)
#  define PLATFORM_NO_CXX14_VARIABLE_TEMPLATES
#endif

#if __BORLANDC__ >= 0x590
#  define PLATFORM_HAS_TR1_HASH

#  define PLATFORM_HAS_MACRO_USE_FACET
#endif

//
// Post 0x561 we have long long and stdint.h:
#if __BORLANDC__ >= 0x561
#  ifndef __NO_LONG_LONG
#     define PLATFORM_HAS_LONG_LONG
#  else
#     define PLATFORM_NO_LONG_LONG
#  endif
   // On non-Win32 platforms let the platform config figure this out:
#  ifdef _WIN32
#      define PLATFORM_HAS_STDINT_H
#  endif
#endif

// Borland C++Builder 6 defaults to using STLPort.  If _USE_OLD_RW_STL is
// defined, then we have 0x560 or greater with the Rogue Wave implementation
// which presumably has the std::DBL_MAX bug.
#if defined( PLATFORM_BCB_WITH_ROGUE_WAVE )
// <climits> is partly broken, some macros define symbols that are really in
// namespace std, so you end up having to use illegal constructs like
// std::DBL_MAX, as a fix we'll just include float.h and have done with:
#include <float.h>
#endif
//
// __int64:
//
#if (__BORLANDC__ >= 0x530) && !defined(__STRICT_ANSI__)
#  define PLATFORM_HAS_MS_INT64
#endif
//
// check for exception handling support:
//
#if !defined(_CPPUNWIND) && !defined(PLATFORM_CPPUNWIND) && !defined(__EXCEPTIONS) && !defined(PLATFORM_NO_EXCEPTIONS)
#  define PLATFORM_NO_EXCEPTIONS
#endif
//
// all versions have a <dirent.h>:
//
#ifndef __STRICT_ANSI__
#  define PLATFORM_HAS_DIRENT_H
#endif
//
// all versions support __declspec:
//
#if defined(__STRICT_ANSI__)
// config/platform/win32.hpp will define PLATFORM_SYMBOL_EXPORT, etc., unless already defined
#  define PLATFORM_SYMBOL_EXPORT
#endif
//
// ABI fixing headers:
//
#if __BORLANDC__ != 0x600 // not implemented for version 6 compiler yet
#ifndef PLATFORM_ABI_PREFIX
#  define PLATFORM_ABI_PREFIX "boost/config/abi/borland_prefix.hpp"
#endif
#ifndef PLATFORM_ABI_SUFFIX
#  define PLATFORM_ABI_SUFFIX "boost/config/abi/borland_suffix.hpp"
#endif
#endif
//
// Disable Win32 support in ANSI mode:
//
#if __BORLANDC__ < 0x600
#  pragma defineonoption PLATFORM_DISABLE_WIN32 -A
#elif defined(__STRICT_ANSI__)
#  define PLATFORM_DISABLE_WIN32
#endif
//
// MSVC compatibility mode does some nasty things:
// TODO: look up if this doesn't apply to the whole 12xx range
//
#if defined(_MSC_VER) && (_MSC_VER <= 1200)
#  define PLATFORM_NO_ARGUMENT_DEPENDENT_LOOKUP
#  define PLATFORM_NO_VOID_RETURNS
#endif

// Borland did not implement value-initialization completely, as I reported
// in 2007, Borland Report 51854, "Value-initialization: POD struct should be
// zero-initialized", http://qc.embarcadero.com/wc/qcmain.aspx?d=51854
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
// (Niels Dekker, LKEB, April 2010)
#define PLATFORM_NO_COMPLETE_VALUE_INITIALIZATION

#define PLATFORM_COMPILER "Borland C++ version " PLATFORM_STRINGIZE(__BORLANDC__)
