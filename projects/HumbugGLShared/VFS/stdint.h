#ifndef HUMBUGSHARED_VFS_STDINT_H
#define HUMBUGSHARED_VFS_STDINT_H




#include "static_assert.h"




#if defined _MSC_VER

typedef signed char			int8_t;
typedef unsigned char		uint8_t;
typedef signed short		int16_t;
typedef unsigned short		uint16_t;
typedef signed int			int32_t;
typedef unsigned int		uint32_t;
typedef signed __int64		int64_t;
typedef unsigned __int64	uint64_t;

typedef signed char			int_least8_t;
typedef unsigned char		uint_least8_t;
typedef signed short		int_least16_t;
typedef unsigned short		uint_least16_t;
typedef signed int			int_least32_t;
typedef unsigned int		uint_least32_t;
typedef signed __int64		int_least64_t;
typedef unsigned __int64	uint_least64_t;

#elif defined UNIX

/*typedef signed char			int8_t;
typedef unsigned char		uint8_t;
typedef signed short		int16_t;
typedef unsigned short		uint16_t;
typedef signed int			int32_t;
typedef unsigned int		uint32_t;
typedef signed long long	int64_t;
typedef unsigned long long	uint64_t;

typedef signed char			int_least8_t;
typedef unsigned char		uint_least8_t;
typedef signed short		int_least16_t;
typedef unsigned short		uint_least16_t;
typedef signed int			int_least32_t;
typedef unsigned int		uint_least32_t;
typedef signed long long	int_least64_t;
typedef unsigned long long	uint_least64_t;*/

#endif




inline void __CheckSizedTypes()
{
	// one byte must be exactly 8 bits
	static_assert_l(CHAR_BIT == 8);

	static_assert_l(sizeof(int8_t) == 1);
	static_assert_l(sizeof(uint8_t) == 1);
	static_assert_l(sizeof(int16_t) == 2);
	static_assert_l(sizeof(uint16_t) == 2);
	static_assert_l(sizeof(int32_t) == 4);
	static_assert_l(sizeof(uint32_t) == 4);
	static_assert_l(sizeof(int64_t) == 8);
	static_assert_l(sizeof(uint64_t) == 8);

	static_assert_l(sizeof(int_least8_t) >= 1);
	static_assert_l(sizeof(uint_least8_t) >= 1);
	static_assert_l(sizeof(int_least16_t) >= 2);
	static_assert_l(sizeof(uint_least16_t) >= 2);
	static_assert_l(sizeof(int_least32_t) >= 4);
	static_assert_l(sizeof(uint_least32_t) >= 4);
	static_assert_l(sizeof(int_least64_t) >= 8);
	static_assert_l(sizeof(uint_least64_t) >= 8);
}

#endif // HUMBUGSHARED_VFS_STDINT_H guard
