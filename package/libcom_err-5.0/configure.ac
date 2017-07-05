#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.65])
AC_INIT([libcom_err], [5.0])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
LT_PREREQ([2.2])
LT_INIT([shared disable-static])
AC_CONFIG_SRCDIR([com_err.c])

# Checks for programs.
AC_PROG_CC

# Checks for libraries.

# Checks for header files.
AC_CHECK_HEADERS([stddef.h stdlib.h string.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_TYPE_SIZE_T

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([strchr strcspn strdup strerror strrchr])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
