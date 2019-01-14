#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT([bbee], [1.0], [github.com/RobSis])
AM_INIT_AUTOMAKE([-Wall -Werror foreign])
AM_CONFIG_HEADER(aconfig.h)

use_cc_g_flag=no
AC_PROG_CC
AC_PROG_INSTALL
AC_HEADER_STDC

dnl Checks for programs.
AC_PROG_MAKE_SET

dnl Check for libraries
AC_CHECK_HEADERS(fcntl.h limits.h malloc.h sys/ioctl.h sys/time.h unistd.h)
AC_SEARCH_LIBS([cos], [m])

dnl Checks for typedefs, structures, and compiler characteristics.
AC_C_CONST
AC_C_INLINE
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_HEADER_TIME

dnl Checks for library functions.
AC_FUNC_ALLOCA
AC_PROG_GCC_TRADITIONAL
AC_FUNC_MEMCMP
AC_TYPE_SIGNAL
AC_CHECK_FUNCS(ftime gettimeofday select strdup strstr strtol)

dnl Check for AA-lib
AM_PATH_AALIB(1.4.0, , AC_MSG_ERROR([*** AALIB >= 1.4.0 not installed - please install first ***]))
CFLAGS="$CFLAGS $AALIB_CFLAGS"
LIBS="$LIBS $AALIB_LIBS"

AC_OUTPUT(Makefile)
