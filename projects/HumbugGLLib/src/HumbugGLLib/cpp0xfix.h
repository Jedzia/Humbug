#ifndef HumbugGLLIB_NAMESPACE_CPP0XFIX_H
#define HumbugGLLIB_NAMESPACE_CPP0XFIX_H



// dirty workaround for vector<T>::data() function.
// hmmm, this is dependant on MSVC2008
#include <cstring>
#if _HAS_CPP0X

#undef USE_CSTDINT
#define USE_CSTDINT

namespace HumbugGLLIB_NAMESPACE {
	template<class T>
	inline typename T::value_type *getDataPointer(T &input )
	{
		return input.data();
	};

	template<class T>
	inline const typename T::value_type *getDataPointer(const T &input )
	{
		return input.data();
	};
}
#else
#include <sys/types.h>

#ifdef _MSC_VER
/* Define to `unsigned short' if <sys/types.h> doesn't define. */
#define uint16_t unsigned short

/* Define to `unsigned int' if <sys/types.h> doesn't define. */
/* #undef HAVE_UINT32_T */
#define uint32_t unsigned int

/* Define to `int' if <sys/types.h> doesn't define. */
#define int32_t int

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
#define uint64_t unsigned __int64

/* Define to the widest unsigned integer type if <stdint.h> and <inttypes.h>
   do not define. */
#define uintmax_t uint64_t

/* Define to the type of an integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
#define int64_t __int64

#endif

namespace HumbugGLLIB_NAMESPACE {
	template<class T>
	inline const typename T::value_type *getDataPointer(const T &input )
	{
		return &input[0];
	};

	template<class T>
	inline typename T::value_type *getDataPointer(T &input )
	{
		return &input[0];
	};
}
#endif



namespace HumbugGLLIB_NAMESPACE {


} // namespace HumbugGLLIB_NAMESPACE
#endif
