/*
 * \file config.h
 * This file is part of LyX, the document processor.
 * Licence details can be found in the file COPYING.
 *
 * This is the compilation configuration file for LyX.
 * It was generated by cmake.
 * You might want to change some of the defaults if something goes wrong
 * during the compilation.
 */

#ifndef _CONFIG_H
#define _CONFIG_H

// // obligatory flags
// #define QT_NO_STL 1
// #define QT_NO_KEYWORDS 1
// #define HAVE_ICONV 1

#include "configCompiler.h"

// #ifdef LYX_ENABLE_PCH
// #include "pcheaders.h"
// #endif


#cmakedefine PACKAGE "${PACKAGE}"
// #cmakedefine PACKAGE_VERSION "${PACKAGE_VERSION}"
// #define PACKAGE_STRING "LyX ${PACKAGE_VERSION}"
// #cmakedefine PACKAGE_BUGREPORT "${PACKAGE_BUGREPORT}"
// #cmakedefine LYX_DATE "${LYX_DATE}"
// #cmakedefine VERSION_INFO "${VERSION_INFO}"
// #cmakedefine LYX_DIR_VER "${LYX_DIR_VER}"
// #cmakedefine LYX_USERDIR_VER "${LYX_USERDIR_VER}"
// #define LYX_MAJOR_VERSION ${LYX_MAJOR_VERSION}
// #define LYX_MINOR_VERSION ${LYX_MINOR_VERSION}

// #define PROGRAM_SUFFIX "${PROGRAM_SUFFIX}"
// #define LYX_ABS_INSTALLED_DATADIR "${LYX_ABS_INSTALLED_DATADIR}"
// #define LYX_ABS_INSTALLED_LOCALEDIR "${LYX_ABS_INSTALLED_LOCALEDIR}"
// #define LYX_ABS_TOP_SRCDIR "${TOP_SRC_DIR}"

// #cmakedefine USE_POSIX_PACKAGING 1
// #cmakedefine USE_WINDOWS_PACKAGING 1
// #cmakedefine USE_MACOSX_PACKAGING 1
// #cmakedefine PATH_MAX ${PATH_MAX}

// #cmakedefine WORDS_BIGENDIAN 1

// #cmakedefine LYX_MERGE_FILES 1

// #cmakedefine LYX_USE_TR1 1
// #cmakedefine LYX_USE_TR1_REGEX 1

// #cmakedefine ASPELL_FOUND 1
// #ifdef ASPELL_FOUND
// #define USE_ASPELL 1
// #endif

// #cmakedefine AIKSAURUSLIB_FOUND 1
// #ifdef AIKSAURUSLIB_FOUND
// #define HAVE_LIBAIKSAURUS 1
// #define AIKSAURUS_H_LOCATION "${AIKSAURUSLIB_H}"
// #endif

// #cmakedefine ENCHANT_FOUND 1
// #ifdef ENCHANT_FOUND
// #define USE_ENCHANT 1
// #endif

// #cmakedefine HUNSPELL_FOUND 1
// #ifdef HUNSPELL_FOUND
// #define USE_HUNSPELL 1
// #endif

#cmakedefine Humbug_NLS 1
#ifdef Humbug_NLS
#define ENABLE_NLS 1
// These are needed when building included gettext (taken from autoconf macro)
#cmakedefine Humbug_EXTERNAL_LIBINTL 1
#if !defined(Humbug_EXTERNAL_LIBINTL)
// this only makes sense when LYX_EXTERNAL_LIBINTL is OFF.
#define __libc_lock_t                   gl_lock_t
#define __libc_lock_define              gl_lock_define
#define __libc_lock_define_initialized  gl_lock_define_initialized
#define __libc_lock_init                gl_lock_init
#define __libc_lock_lock                gl_lock_lock
#define __libc_lock_unlock              gl_lock_unlock
#define __libc_lock_recursive_t                   gl_recursive_lock_t
#define __libc_lock_define_recursive              gl_recursive_lock_define
#define __libc_lock_define_initialized_recursive  gl_recursive_lock_define_initialized
#define __libc_lock_init_recursive                gl_recursive_lock_init
#define __libc_lock_lock_recursive                gl_recursive_lock_lock
#define __libc_lock_unlock_recursive              gl_recursive_lock_unlock
#define glthread_in_use  libintl_thread_in_use
#define glthread_lock_init     libintl_lock_init
#define glthread_lock_lock     libintl_lock_lock
#define glthread_lock_unlock   libintl_lock_unlock
#define glthread_lock_destroy  libintl_lock_destroy
#define glthread_rwlock_init     libintl_rwlock_init
#define glthread_rwlock_rdlock   libintl_rwlock_rdlock
#define glthread_rwlock_wrlock   libintl_rwlock_wrlock
#define glthread_rwlock_unlock   libintl_rwlock_unlock
#define glthread_rwlock_destroy  libintl_rwlock_destroy
#define glthread_recursive_lock_init     libintl_recursive_lock_init
#define glthread_recursive_lock_lock     libintl_recursive_lock_lock
#define glthread_recursive_lock_unlock   libintl_recursive_lock_unlock
#define glthread_recursive_lock_destroy  libintl_recursive_lock_destroy
#define glthread_once                 libintl_once
#define glthread_once_call            libintl_once_call
#define glthread_once_singlethreaded  libintl_once_singlethreaded
#define hash_string			libintl_hash_string
#endif /* Humbug_EXTERNAL_LIBINTL */
#endif


// Integer stuff from int_typecheck.cmake
#cmakedefine HAVE_UINT32_T

#ifdef HAVE_LIMITS_H
#  include <limits.h>
#endif

#ifdef HAVE_UINT32_T
#  define USE_CSTDINT
#else
/* Define for Solaris 2.5.1 so the uint64_t typedef from <sys/synch.h>,
   <pthread.h>, or <semaphore.h> is not used. If the typedef were allowed, the
   #define below would cause a syntax error. */
#cmakedefine _UINT64_T

/* Define to empty if `const' does not conform to ANSI C. */
#cmakedefine const ${const}

/* Define to `int' if <sys/types.h> doesn't define. */
#cmakedefine gid_t ${gid_t}

/* Define to `unsigned long' if <sys/types.h> does not define. */
#cmakedefine id_t ${id_t}

/* Define to the type of a signed integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
#cmakedefine int64_t ${int64_t}

/* Define to the widest signed integer type if <stdint.h> and <inttypes.h> do
   not define. */
#cmakedefine intmax_t ${intmax_t}

/* Define to `int' if <sys/types.h> does not define. */
#cmakedefine mode_t ${mode_t}

/* Define to `unsigned int' if <sys/types.h> does not define. */
#cmakedefine dev_t ${dev_t}

/* Define to `long long' if <sys/types.h> does not define. */
#cmakedefine off_t ${off_t}

/* Define to `unsigned int' if <sys/types.h> does not define. */
#cmakedefine size_t ${size_t}

/* Define to `int' if <sys/types.h> does not define. */
#cmakedefine ssize_t ${ssize_t}

/* Define to `int' if <sys/types.h> doesn't define. */
#cmakedefine uid_t ${uid_t}

/* Define to `unsigned short' if <sys/types.h> doesn't define. */
#cmakedefine uint16_t ${uint16_t}

/* Define to `unsigned int' if <sys/types.h> doesn't define. */
#cmakedefine uint32_t ${uint32_t}

/* Define to `int' if <sys/types.h> doesn't define. */
#cmakedefine int32_t ${int32_t}

/* Define to the type of an unsigned integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
#cmakedefine uint64_t ${uint64_t}

/* Define to the type of an integer type of width exactly 64 bits if
   such a type exists and the standard includes do not define it. */
#cmakedefine int64_t ${int64_t}

/* Define to the widest unsigned integer type if <stdint.h> and <inttypes.h>
   do not define. */
#cmakedefine uintmax_t ${uintmax_t}

/* Define to `int' if <sys/types.h> does not define. */
#cmakedefine intptr_t ${intptr_t}

/* Define to `unsigned int' if <sys/types.h> does not define. */
#cmakedefine uintptr_t ${uintptr_t}

#endif

#endif // config.h guard



// Unguarded cleanup of global namespace:

// #ifdef ColorMode
// #undef ColorMode
// #endif

// #ifdef FocusOut
// #undef FocusOut
// #endif

// #ifdef FocusIn
// #undef FocusIn
// #endif

// #ifdef KeyRelease
// #undef KeyRelease
// #endif

// #ifdef CursorShape
// #undef CursorShape
// #endif

// #ifdef IGNORE
// #undef IGNORE
// #endif

// #ifdef GrayScale
// #undef GrayScale
// #endif

// #ifdef Status
// #undef Status
// #endif

// #ifdef IN
// #undef IN
// #endif

// #ifdef KeyPress
// #undef KeyPress
// #endif

