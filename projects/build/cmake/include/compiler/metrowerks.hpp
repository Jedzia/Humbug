//  (C) Copyright John Maddock 2001.
//  (C) Copyright Darin Adler 2001.
//  (C) Copyright Peter Dimov 2001.
//  (C) Copyright David Abrahams 2001 - 2002.
//  (C) Copyright Beman Dawes 2001 - 2003.
//  (C) Copyright Stefan Slapeta 2004.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  Metrowerks C++ compiler setup:

// locale support is disabled when linking with the dynamic runtime
#   ifdef _MSL_NO_LOCALE
#     define PLATFORM_NO_STD_LOCALE
#   endif

#   if __MWERKS__ <= 0x2301  // 5.3
#     define PLATFORM_NO_FUNCTION_TEMPLATE_ORDERING
#     define PLATFORM_NO_POINTER_TO_MEMBER_CONST
#     define PLATFORM_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#     define PLATFORM_NO_MEMBER_TEMPLATE_KEYWORD
#   endif

#   if __MWERKS__ <= 0x2401  // 6.2
//#     define PLATFORM_NO_FUNCTION_TEMPLATE_ORDERING
#   endif

#   if(__MWERKS__ <= 0x2407)  // 7.x
#     define PLATFORM_NO_MEMBER_FUNCTION_SPECIALIZATIONS
#     define PLATFORM_NO_UNREACHABLE_RETURN_DETECTION
#   endif

#   if(__MWERKS__ <= 0x3003)  // 8.x
#     define PLATFORM_NO_SFINAE
#    endif

// the "|| !defined(PLATFORM_STRICT_CONFIG)" part should apply to the last
// tested version *only*:
#   if(__MWERKS__ <= 0x3207) || !defined(PLATFORM_STRICT_CONFIG) // 9.6
#     define PLATFORM_NO_MEMBER_TEMPLATE_FRIENDS
#     define PLATFORM_NO_IS_ABSTRACT
#    endif

#if !__option(wchar_type)
#   define PLATFORM_NO_INTRINSIC_WCHAR_T
#endif

#if !__option(exceptions) && !defined(PLATFORM_NO_EXCEPTIONS)
#   define PLATFORM_NO_EXCEPTIONS
#endif

#if (__INTEL__ && _WIN32) || (__POWERPC__ && macintosh)
#   if __MWERKS__ == 0x3000
#     define PLATFORM_COMPILER_VERSION 8.0
#   elif __MWERKS__ == 0x3001
#     define PLATFORM_COMPILER_VERSION 8.1
#   elif __MWERKS__ == 0x3002
#     define PLATFORM_COMPILER_VERSION 8.2
#   elif __MWERKS__ == 0x3003
#     define PLATFORM_COMPILER_VERSION 8.3
#   elif __MWERKS__ == 0x3200
#     define PLATFORM_COMPILER_VERSION 9.0
#   elif __MWERKS__ == 0x3201
#     define PLATFORM_COMPILER_VERSION 9.1
#   elif __MWERKS__ == 0x3202
#     define PLATFORM_COMPILER_VERSION 9.2
#   elif __MWERKS__ == 0x3204
#     define PLATFORM_COMPILER_VERSION 9.3
#   elif __MWERKS__ == 0x3205
#     define PLATFORM_COMPILER_VERSION 9.4
#   elif __MWERKS__ == 0x3206
#     define PLATFORM_COMPILER_VERSION 9.5
#   elif __MWERKS__ == 0x3207
#     define PLATFORM_COMPILER_VERSION 9.6
#   else
#     define PLATFORM_COMPILER_VERSION __MWERKS__
#   endif
#else
#  define PLATFORM_COMPILER_VERSION __MWERKS__
#endif

//
// C++0x features
//
//   See boost\config\suffix.hpp for PLATFORM_NO_LONG_LONG
//
#if __MWERKS__ > 0x3206 && __option(rvalue_refs)
#  define PLATFORM_HAS_RVALUE_REFS
#else
#  define PLATFORM_NO_CXX11_RVALUE_REFERENCES
#endif
#define PLATFORM_NO_CXX11_AUTO_DECLARATIONS
#define PLATFORM_NO_CXX11_AUTO_MULTIDECLARATIONS
#define PLATFORM_NO_CXX11_CHAR16_T
#define PLATFORM_NO_CXX11_CHAR32_T
#define PLATFORM_NO_CXX11_CONSTEXPR
#define PLATFORM_NO_CXX11_DECLTYPE
#define PLATFORM_NO_CXX11_DECLTYPE_N3276
#define PLATFORM_NO_CXX11_DEFAULTED_FUNCTIONS
#define PLATFORM_NO_CXX11_DELETED_FUNCTIONS
#define PLATFORM_NO_CXX11_EXPLICIT_CONVERSION_OPERATORS
#define PLATFORM_NO_CXX11_EXTERN_TEMPLATE
#define PLATFORM_NO_CXX11_FUNCTION_TEMPLATE_DEFAULT_ARGS
#define PLATFORM_NO_CXX11_HDR_INITIALIZER_LIST
#define PLATFORM_NO_CXX11_LAMBDAS
#define PLATFORM_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define PLATFORM_NO_CXX11_NOEXCEPT
#define PLATFORM_NO_CXX11_NULLPTR
#define PLATFORM_NO_CXX11_RANGE_BASED_FOR
#define PLATFORM_NO_CXX11_RAW_LITERALS
#define PLATFORM_NO_CXX11_SCOPED_ENUMS
#define PLATFORM_NO_SFINAE_EXPR
#define PLATFORM_NO_CXX11_STATIC_ASSERT
#define PLATFORM_NO_CXX11_TEMPLATE_ALIASES
#define PLATFORM_NO_CXX11_UNICODE_LITERALS
#define PLATFORM_NO_CXX11_VARIADIC_TEMPLATES
#define PLATFORM_NO_CXX11_VARIADIC_MACROS
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

#define PLATFORM_COMPILER "Metrowerks CodeWarrior C++ version " PLATFORM_STRINGIZE(PLATFORM_COMPILER_VERSION)

//
// versions check:
// we don't support Metrowerks prior to version 5.3:
#if __MWERKS__ < 0x2301
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version:
#if (__MWERKS__ > 0x3205)
#  if defined(PLATFORM_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif







