//  (C) Copyright John Maddock 2001 - 2002.
//  (C) Copyright Aleksey Gurtovoy 2002.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  MPW C++ compilers setup:

#   if    defined(__SC__)
#     define PLATFORM_COMPILER "MPW SCpp version " PLATFORM_STRINGIZE(__SC__)
#   elif defined(__MRC__)
#     define PLATFORM_COMPILER "MPW MrCpp version " PLATFORM_STRINGIZE(__MRC__)
#   else
#     error "Using MPW compiler configuration by mistake.  Please update."
#   endif

//
// MPW 8.90:
//
#if (MPW_CPLUS <= 0x890) || !defined(PLATFORM_STRICT_CONFIG)
#  define PLATFORM_NO_CV_SPECIALIZATIONS
#  define PLATFORM_NO_DEPENDENT_NESTED_DERIVATIONS
#  define PLATFORM_NO_DEPENDENT_TYPES_IN_TEMPLATE_VALUE_PARAMETERS
#  define PLATFORM_NO_INCLASS_MEMBER_INITIALIZATION
#  define PLATFORM_NO_INTRINSIC_WCHAR_T
#  define PLATFORM_NO_TEMPLATE_PARTIAL_SPECIALIZATION
#  define PLATFORM_NO_USING_TEMPLATE

#  define PLATFORM_NO_CWCHAR
#  define PLATFORM_NO_LIMITS_COMPILE_TIME_CONSTANTS

#  define PLATFORM_NO_STD_ALLOCATOR /* actually a bug with const reference overloading */

#endif

//
// C++0x features
//
//   See boost\config\suffix.hpp for PLATFORM_NO_LONG_LONG
//
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
#define PLATFORM_NO_CXX11_RVALUE_REFERENCES
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

//
// versions check:
// we don't support MPW prior to version 8.9:
#if MPW_CPLUS < 0x890
#  error "Compiler not supported or configured - please reconfigure"
#endif
//
// last known and checked version is 0x890:
#if (MPW_CPLUS > 0x890)
#  if defined(PLATFORM_ASSERT_CONFIG)
#     error "Unknown compiler version - please run the configure tests and report the results"
#  endif
#endif


