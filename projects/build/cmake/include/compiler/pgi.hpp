//  (C) Copyright Noel Belcourt 2007.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

//  See http://www.boost.org for most recent version.

//  PGI C++ compiler setup:

#define PLATFORM_COMPILER_VERSION __PGIC__##__PGIC_MINOR__
#define PLATFORM_COMPILER "PGI compiler version " PLATFORM_STRINGIZE(PLATFORM_COMPILER_VERSION)

//
// Threading support:
// Turn this on unconditionally here, it will get turned off again later
// if no threading API is detected.
//

#if __PGIC__ >= 11

// options requested by configure --enable-test
#define PLATFORM_HAS_PTHREADS
#define PLATFORM_HAS_THREADS
#define PLATFORM_HAS_PTHREAD_YIELD
#define PLATFORM_HAS_NRVO
#define PLATFORM_HAS_LONG_LONG

// options --enable-test wants undefined
#undef PLATFORM_NO_STDC_NAMESPACE
#undef PLATFORM_NO_EXCEPTION_STD_NAMESPACE
#undef PLATFORM_DEDUCED_TYPENAME

#define PLATFORM_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#define PLATFORM_NO_TWO_PHASE_NAME_LOOKUP
#define PLATFORM_NO_CXX11_AUTO_MULTIDECLARATIONS
#define PLATFORM_NO_CXX11_AUTO_DECLARATIONS

#elif __PGIC__ >= 10

// options requested by configure --enable-test
#define PLATFORM_HAS_THREADS
#define PLATFORM_HAS_NRVO
#define PLATFORM_HAS_LONG_LONG
#if defined(linux) || defined(__linux) || defined(__linux__)
#  define PLATFORM_HAS_STDINT_H
#endif

// options --enable-test wants undefined
#undef PLATFORM_NO_STDC_NAMESPACE
#undef PLATFORM_NO_EXCEPTION_STD_NAMESPACE
#undef PLATFORM_DEDUCED_TYPENAME

#elif __PGIC__ >= 7

#define PLATFORM_FUNCTION_SCOPE_USING_DECLARATION_BREAKS_ADL
#define PLATFORM_NO_TWO_PHASE_NAME_LOOKUP
#define PLATFORM_NO_SWPRINTF
#define PLATFORM_NO_CXX11_AUTO_MULTIDECLARATIONS
#define PLATFORM_NO_CXX11_AUTO_DECLARATIONS

#else

#  error "Pgi compiler not configured - please reconfigure"

#endif
//
// C++0x features
//
//   See boost\config\suffix.hpp for PLATFORM_NO_LONG_LONG
//
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
#define PLATFORM_NO_CXX11_LAMBDAS
#define PLATFORM_NO_CXX11_LOCAL_CLASS_TEMPLATE_PARAMETERS
#define PLATFORM_NO_CXX11_NOEXCEPT
#define PLATFORM_NO_CXX11_NULLPTR
#define PLATFORM_NO_CXX11_NUMERIC_LIMITS
#define PLATFORM_NO_CXX11_RANGE_BASED_FOR
#define PLATFORM_NO_CXX11_RAW_LITERALS
#define PLATFORM_NO_CXX11_RVALUE_REFERENCES
#define PLATFORM_NO_CXX11_SCOPED_ENUMS
#define PLATFORM_NO_SFINAE_EXPR
#define PLATFORM_NO_CXX11_STATIC_ASSERT
#define PLATFORM_NO_SWPRINTF
#define PLATFORM_NO_CXX11_TEMPLATE_ALIASES
#define PLATFORM_NO_CXX11_UNICODE_LITERALS
#define PLATFORM_NO_CXX11_VARIADIC_TEMPLATES
#define PLATFORM_NO_CXX11_VARIADIC_MACROS
#define PLATFORM_NO_CXX11_UNIFIED_INITIALIZATION_SYNTAX

#define PLATFORM_NO_CXX11_HDR_UNORDERED_SET
#define PLATFORM_NO_CXX11_HDR_UNORDERED_MAP
#define PLATFORM_NO_CXX11_HDR_TYPEINDEX
#define PLATFORM_NO_CXX11_HDR_TYPE_TRAITS
#define PLATFORM_NO_CXX11_HDR_TUPLE
#define PLATFORM_NO_CXX11_HDR_THREAD
#define PLATFORM_NO_CXX11_HDR_SYSTEM_ERROR
#define PLATFORM_NO_CXX11_HDR_REGEX
#define PLATFORM_NO_CXX11_HDR_RATIO
#define PLATFORM_NO_CXX11_HDR_RANDOM
#define PLATFORM_NO_CXX11_HDR_MUTEX
#define PLATFORM_NO_CXX11_HDR_INITIALIZER_LIST
#define PLATFORM_NO_CXX11_HDR_FUTURE
#define PLATFORM_NO_CXX11_HDR_FORWARD_LIST
#define PLATFORM_NO_CXX11_HDR_CONDITION_VARIABLE
#define PLATFORM_NO_CXX11_HDR_CODECVT
#define PLATFORM_NO_CXX11_HDR_CHRONO
#define PLATFORM_NO_CXX11_HDR_ARRAY
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
// version check:
// probably nothing to do here?

