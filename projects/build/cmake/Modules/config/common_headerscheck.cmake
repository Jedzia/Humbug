# common_headerscheck.cmake
# Check for common header files.

include(CheckIncludeFile)
include(CheckIncludeFiles)

set(INCLUDES "")
macro (LA_CHECK_INCLUDE_FILE header var)
      CHECK_INCLUDE_FILES("${INCLUDES};${header}" ${var})
      if (${var})
         set(INCLUDES ${INCLUDES} ${header})
      endif (${var})
endmacro (LA_CHECK_INCLUDE_FILE)

# Few headers that must precede other headers
# Must precede sys/extattr.h on FreeBSD
LA_CHECK_INCLUDE_FILE("sys/types.h" HAVE_SYS_TYPES_H)

# Alphabetize the rest unless there's a compelling reason
LA_CHECK_INCLUDE_FILE("acl/libacl.h" HAVE_ACL_LIBACL_H)
LA_CHECK_INCLUDE_FILE("attr/xattr.h" HAVE_ATTR_XATTR_H)
LA_CHECK_INCLUDE_FILE("ctype.h" HAVE_CTYPE_H)
LA_CHECK_INCLUDE_FILE("direct.h" HAVE_DIRECT_H)
LA_CHECK_INCLUDE_FILE("dlfcn.h" HAVE_DLFCN_H)
LA_CHECK_INCLUDE_FILE("errno.h" HAVE_ERRNO_H)
LA_CHECK_INCLUDE_FILE("ext2fs/ext2_fs.h" HAVE_EXT2FS_EXT2_FS_H)
LA_CHECK_INCLUDE_FILE("fcntl.h" HAVE_FCNTL_H)
LA_CHECK_INCLUDE_FILE("grp.h" HAVE_GRP_H)
LA_CHECK_INCLUDE_FILE("inttypes.h" HAVE_INTTYPES_H)
LA_CHECK_INCLUDE_FILE("io.h" HAVE_IO_H)
LA_CHECK_INCLUDE_FILE("langinfo.h" HAVE_LANGINFO_H)
LA_CHECK_INCLUDE_FILE("limits.h" HAVE_LIMITS_H)
LA_CHECK_INCLUDE_FILE("linux/fs.h" HAVE_LINUX_FS_H)
LA_CHECK_INCLUDE_FILE("locale.h" HAVE_LOCALE_H)
LA_CHECK_INCLUDE_FILE("memory.h" HAVE_MEMORY_H)
LA_CHECK_INCLUDE_FILE("paths.h" HAVE_PATHS_H)
LA_CHECK_INCLUDE_FILE("poll.h" HAVE_POLL_H)
LA_CHECK_INCLUDE_FILE("process.h" HAVE_PROCESS_H)
LA_CHECK_INCLUDE_FILE("pwd.h" HAVE_PWD_H)
LA_CHECK_INCLUDE_FILE("regex.h" HAVE_REGEX_H)
LA_CHECK_INCLUDE_FILE("signal.h" HAVE_SIGNAL_H)
LA_CHECK_INCLUDE_FILE("stdarg.h" HAVE_STDARG_H)
LA_CHECK_INCLUDE_FILE("stdint.h" HAVE_STDINT_H)
LA_CHECK_INCLUDE_FILE("stdlib.h" HAVE_STDLIB_H)
LA_CHECK_INCLUDE_FILE("string.h" HAVE_STRING_H)
LA_CHECK_INCLUDE_FILE("strings.h" HAVE_STRINGS_H)
LA_CHECK_INCLUDE_FILE("sys/acl.h" HAVE_SYS_ACL_H)
LA_CHECK_INCLUDE_FILE("sys/extattr.h" HAVE_SYS_EXTATTR_H)
LA_CHECK_INCLUDE_FILE("sys/ioctl.h" HAVE_SYS_IOCTL_H)
LA_CHECK_INCLUDE_FILE("sys/mkdev.h" HAVE_SYS_MKDEV_H)
LA_CHECK_INCLUDE_FILE("sys/param.h" HAVE_SYS_PARAM_H)
LA_CHECK_INCLUDE_FILE("sys/poll.h" HAVE_SYS_POLL_H)
LA_CHECK_INCLUDE_FILE("sys/select.h" HAVE_SYS_SELECT_H)
LA_CHECK_INCLUDE_FILE("sys/stat.h" HAVE_SYS_STAT_H)
LA_CHECK_INCLUDE_FILE("sys/time.h" HAVE_SYS_TIME_H)
LA_CHECK_INCLUDE_FILE("sys/utime.h" HAVE_SYS_UTIME_H)
LA_CHECK_INCLUDE_FILE("sys/wait.h" HAVE_SYS_WAIT_H)
LA_CHECK_INCLUDE_FILE("time.h" HAVE_TIME_H)
LA_CHECK_INCLUDE_FILE("unistd.h" HAVE_UNISTD_H)
LA_CHECK_INCLUDE_FILE("utime.h" HAVE_UTIME_H)
LA_CHECK_INCLUDE_FILE("wchar.h" HAVE_WCHAR_H)
LA_CHECK_INCLUDE_FILE("wctype.h" HAVE_WCTYPE_H)
LA_CHECK_INCLUDE_FILE("windows.h" HAVE_WINDOWS_H)

