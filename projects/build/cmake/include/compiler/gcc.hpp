//  (C) Copyright John Maddock 2001 - 2003. 
//  (C) Copyright Darin Adler 2001 - 2002. 
//  (C) Copyright Jens Maurer 2001 - 2002. 
//  (C) Copyright Beman Dawes 2001 - 2003. 
//  (C) Copyright Douglas Gregor 2002. 
//  (C) Copyright David Abrahams 2002 - 2003. 
//  (C) Copyright Synge Todo 2003. 
//  Use, modification and distribution are subject to the 
//  Boost Software License, Version 1.0. (See accompanying file 
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  GNU C++ compiler setup:

#if __GNUC__ < 3
#   if __GNUC_MINOR__ == 91
       // egcs 1.1 won't parse shared_ptr.hpp without this:
#      define PLATFORM_NO_AUTO_PTR
#   endif
#   if __GNUC_MINOR__ < 95
      //
      // Prior to gcc 2.95 member templates only partly
      // work - define PLATFORM_MSVC6_MEMBER_TEMPLATES
      // instead since inline member templates mostly work.
      //
#     define PLATFORM_NO_MEMBER_TEMPLATES
#     if __GNUC_MINOR__ >= 9
#       define PLATFORM_MSVC6_MEMBER_TEMPLATES
#     endif
#   endif

#   if __GNUC_MINOR__ < 96
#     define PLATFORM_NO_SFINAE
#   endif

#   if __GNUC_MINOR__ <= 97
#     define PLATFORM_NO_MEMBER_TEMPLATE_FRIENDS
#     define PLATFORM_NO_OPERATORS_IN_NAMESPACE
#   endif

#   define PLATFORM_NO_USING_DECLARATION_OVERLOADS_FROM_TYPENAME_BASE
#   define PLATFORM_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#   define PLATFORM_NO_IS_ABSTRACT
#   define PLATFORM_NO_EXTERN_TEMPLATE
// Variadic macros do not exist for gcc versions before 3.0
#   define PLATFORM_NO_VARIADIC_MACROS
#elif __GNUC__ == 3
#  if defined (__PATHSCALE__)
#     define PLATFORM_NO_TWO_PHASE_NAME_LOOKUP
#     define PLATFORM_NO_IS_ABSTRACT
#  endif
   //
   // gcc-3.x problems:
   //
   // Bug specific to gcc 3.1 and 3.2:
   //
#  if ((__GNUC_MINOR__ == 1) || (__GNUC_MINOR__ == 2))
#     define PLATFORM_NO_EXPLICIT_FUNCTION_TEMPLATE_ARGUMENTS
#  endif
#  if __GNUC_MINOR__ < 4
#     define PLATFORM_NO_IS_ABSTRACT
#  endif
#  define PLATFORM_NO_EXTERN_TEMPLATE
#endif
#if __GNUC__ < 4
//
// All problems to gcc-3.x and earlier here:
//
#define PLATFORM_NO_TWO_PHASE_NAME_LOOKUP
#  ifdef __OPEN64__
#     define PLATFORM_NO_IS_ABSTRACT
#  endif
#endif

#if __GNUC__ < 4 || ( __GNUC__ == 4 && __GNUC_MINOR__ < 4 )
// Previous versions of GCC did not completely implement value-initialization:
// GCC Bug 30111, "Value-initialization of POD base class doesn't initialize
// members", reported by Jonathan Wakely in 2006,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=30111 (fixed for GCC 4.4)
// GCC Bug 33916, "Default constructor fails to initialize array members",
// reported by Michael Elizabeth Chastain in 2007,
// http://gcc.gnu.org/bugzilla/show_bug.cgi?id=33916 (fixed for GCC 4.2.4)
// See also: http://www.boost.org/libs/utility/value_init.htm#compiler_issues
#define PLATFORM_NO_COMPLETE_VALUE_INITIALIZATION
#endif

#if !defined(__EXCEPTIONS) && !defined(PLATFORM_NO_EXCEPTIONS)
# define PLATFORM_NO_EXCEPTIONS
#endif

//
// Threading support: Turn this on unconditionally here (except for
// those platforms where we can know for sure). It will get turned off again
// later if no threading API is detected.
//
#if !defined(__MINGW32__) && !defined(linux) && !defined(__linux) && !defined(__linux__)
# define PLATFORM_HAS_THREADS
#endif 

//
// gcc has "long long"
//
#define PLATFORM_HAS_LONG_LONG

//
// gcc implements the named return value optimization since version 3.1
//
#if __GNUC__ > 3 || ( __GNUC__ == 3 && __GNUC_MINOR__ >= 1 )
#define PLATFORM_HAS_NRVO
#endif

//
// Dynamic shared object (DSO) and dynamic-link library (DLL) support
//
#if __GNUC__ >= 4
#  if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32)) && !defined(__CYGWIN__)
     // All Win32 development environments, including 64-bit Windows and MinGW, define 
     // _WIN32 or one of its variant spellings. Note that Cygwin is a POSIX environment,
     // so does not define _WIN32 or its variants.
#    define PLATFORM_HAS_DECLSPEC
#    define PLATFORM_SYMBOL_EXPORT __attribute__((dllexport))
#    define PLATFORM_SYMBOL_IMPORT __attribute__((dllimport))
#  else
#    define PLATFORM_SYMBOL_EXPORT __attribute__((visibility("default")))
#    define PLATFORM_SYMBOL_IMPORT
#  endif
#  define PLATFORM_SYMBOL_VISIBLE __attribute__((visibility("default")))
#else
// config/platform/win32.hpp will define PLATFORM_SYMBOL_EXPORT, etc., unless already defined  
#  define PLATFORM_SYMBOL_EXPORT
#endif

//
// RTTI and typeinfo detection is possible post gcc-4.3:
//
#if __GNUC__ * 100 + __GNUC_MINOR__ >= 403
#  ifndef __GXX_RTTI
#     ifndef PLATFORM_NO_TYPEID
#        define PLATFORM_NO_TYPEID
#     endif
#     ifndef PLATFORM_NO_RTTI
#        define PLATFORM_NO_RTTI
#     endif
#  endif
#endif

// C++0x features not implemented in any GCC version
//
#define PLATFORM_NO_TEMPLATE_ALIASES

// C++0x features in 4.3.n and later
//
#if (__GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ > 2)) && defined(__GXX_EXPERIMENTAL_CXX0X__)
// C++0x features are only enabled when -std=c++0x or -std=gnu++0x are
// passed on the command line, which in turn defines
// __GXX_EXPERIMENTAL_CXX0X__.
#  define PLATFORM_HAS_DECLTYPE
#  define PLATFORM_HAS_RVALUE_REFS
#  define PLATFORM_HAS_STATIC_ASSERT
#  define PLATFORM_HAS_VARIADIC_TMPL
#else
#  define PLATFORM_NO_DECLTYPE
#  define PLATFORM_NO_FUNCTION_TEMPLATE_DEFAULT_ARGS
#  define PLATFORM_NO_RVALUE_REFERENCES
#  define PLATFORM_NO_STATIC_ASSERT

// Variadic templates compiler: 
//   http://www.generic-programming.org/~dgregor/cpp/variadic-templates.html
#  ifdef __VARIADIC_TEMPLATES
#    define PLATFORM_HAS_VARIADIC_TMPL
#  else
#    define PLATFORM_NO_VARIADIC_TEMPLATES
#  endif
#endif

// C++0x features in 4.4.n and later
//
#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define PLATFORM_NO_AUTO_DECLARATIONS
#  define PLATFORM_NO_AUTO_MULTIDECLARATIONS
#  define PLATFORM_NO_CHAR16_T
#  define PLATFORM_NO_CHAR32_T
#  define PLATFORM_NO_DEFAULTED_FUNCTIONS
#  define PLATFORM_NO_DELETED_FUNCTIONS
#  define PLATFORM_NO_INITIALIZER_LISTS
#  define PLATFORM_NO_SCOPED_ENUMS  
#endif

#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 4)
#  define PLATFORM_NO_SFINAE_EXPR
#endif

// C++0x features in 4.4.1 and later
//
#if (__GNUC__*10000 + __GNUC_MINOR__*100 + __GNUC_PATCHLEVEL__ < 40401) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
// scoped enums have a serious bug in 4.4.0, so define PLATFORM_NO_SCOPED_ENUMS before 4.4.1
// See http://gcc.gnu.org/bugzilla/show_bug.cgi?id=38064
#  define PLATFORM_NO_SCOPED_ENUMS
#endif

// C++0x features in 4.5.n and later
//
#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 5) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#  define PLATFORM_NO_EXPLICIT_CONVERSION_OPERATORS
#  define PLATFORM_NO_LAMBDAS
#  define PLATFORM_NO_RAW_LITERALS
#  define PLATFORM_NO_UNICODE_LITERALS
#endif

// C++0x features in 4.5.n and later
//
#if __GNUC__ < 4 || (__GNUC__ == 4 && __GNUC_MINOR__ < 6) || !defined(__GXX_EXPERIMENTAL_CXX0X__)
#define PLATFORM_NO_CONSTEXPR
#define PLATFORM_NO_NULLPTR
#endif

// ConceptGCC compiler:
//   http://www.generic-programming.org/software/ConceptGCC/
#ifdef __GXX_CONCEPTS__
#  define PLATFORM_HAS_CONCEPTS
#  define PLATFORM_COMPILER "ConceptGCC version " __VERSION__
#else
#  define PLATFORM_NO_CONCEPTS
#endif

#ifndef PLATFORM_COMPILER
#  define PLATFORM_COMPILER "GNU C++ version " __VERSION__
#endif

//
// versions check:
// we don't know gcc prior to version 2.90:
#if (__GNUC__ == 2) && (__GNUC_MINOR__ < 90)
#  error "Compiler not configured - please reconfigure"
#endif
//
// last known and checked version is 4.6 (Pre-release):
#if (__GNUC__ > 4) || ((__GNUC__ == 4) && (__GNUC_MINOR__ > 6))
#  if defined(PLATFORM_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  else
// we don't emit warnings here anymore since there are no defect macros defined for
// gcc post 3.4, so any failures are gcc regressions...
//#     warning "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif


