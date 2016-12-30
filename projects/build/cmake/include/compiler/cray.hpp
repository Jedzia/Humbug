//  (C) Copyright John Maddock 2011.
//  (C) Copyright Cray, Inc. 2013
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Greenhills C compiler setup:

#define PLATFORM_COMPILER "Cray C version " PLATFORM_STRINGIZE(_RELEASE)

#if _RELEASE < 8
#  error "Boost is not configured for Cray compilers prior to version 8, please try the configure script."
#endif

//
// Check this is a recent EDG based compiler, otherwise we don't support it here:
//
#ifndef __EDG_VERSION__
#  error "Unsupported Cray compiler, please try running the configure script."
#endif

#include <boost/config/compiler/common_edg.hpp>


//
//
#define PLATFORM_NO_CXX11_STATIC_ASSERT
#define PLATFORM_NO_CXX11_AUTO_DECLARATIONS
#define PLATFORM_NO_CXX11_AUTO_MULTIDECLARATIONS
#define PLATFORM_HAS_NRVO
#define PLATFORM_NO_CXX11_VARIADIC_MACROS
#define PLATFORM_NO_CXX11_VARIADIC_TEMPLATES
#define PLATFORM_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX
#define PLATFORM_NO_CXX11_UNICODE_LITERALS
#define PLATFORM_NO_TWO_PHASE_NAME_LOOKUP
#define PLATFORM_HAS_NRVO
#define PLATFORM_NO_CXX11_TEMPLATE_ALIASES
#define PLATFORM_NO_CXX11_STATIC_ASSERT
#define PLATFORM_NO_SFINAE_EXPR
#define PLATFORM_NO_CXX11_SCOPED_ENUMS
#define PLATFORM_NO_CXX11_RVALUE_REFERENCES
#define PLATFORM_NO_CXX11_RANGE_BASED_FOR
#define PLATFORM_NO_CXX11_RAW_LITERALS
#define PLATFORM_NO_CXX11_NULLPTR
#define PLATFORM_NO_CXX11_NOEXCEPT
#define PLATFORM_NO_CXX11_LAMBDAS
#define PLATFORM_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define PLATFORM_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define PLATFORM_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define PLATFORM_NO_CXX11_DELETED_FUNCTIONS
#define PLATFORM_NO_CXX11_DEFAULTED_FUNCTIONS
#define PLATFORM_NO_CXX11_DECLTYPE_N3276
#define PLATFORM_NO_CXX11_DECLTYPE
#define PLATFORM_NO_CXX11_CONSTEXPR
#define PLATFORM_NO_CXX11_USER_DEFINED_LITERALS
#define PLATFORM_NO_COMPLETE_VALUE_INITIALIZATION
#define PLATFORM_NO_CXX11_CHAR32_T
#define PLATFORM_NO_CXX11_CHAR16_T
#define PLATFORM_NO_CXX11_REF_QUALIFIERS
#define PLATFORM_NO_CXX11_FINAL
#define PLATFORM_NO_CXX11_THREAD_LOCAL


//#define PLATFORM_BCB_PARTIAL_SPECIALIZATION_BUG
#define PLATFORM_MATH_DISABLE_STD_FPCLASSIFY
//#define PLATFORM_HAS_FPCLASSIFY

#define PLATFORM_SP_USE_PTHREADS 
#define PLATFORM_AC_USE_PTHREADS 

/* everything that follows is working around what are thought to be
 * compiler shortcomings.  Revist all of these regularly.
 */

//#define PLATFORM_USE_ENUM_STATIC_ASSERT
//#define PLATFORM_BUGGY_INTEGRAL_CONSTANT_EXPRESSIONS //(this may be implied by the previous #define

// These constants should be provided by the 
// compiler, at least when -hgnu is asserted on the command line.

#ifndef __ATOMIC_RELAXED
#define __ATOMIC_RELAXED 0
#define __ATOMIC_CONSUME 1
#define __ATOMIC_ACQUIRE 2
#define __ATOMIC_RELEASE 3
#define __ATOMIC_ACQ_REL 4
#define __ATOMIC_SEQ_CST 5
#endif



