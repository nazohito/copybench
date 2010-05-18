#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.60)
AC_INIT(copybench)
AM_INIT_AUTOMAKE(copybench,1.0)
AC_CONFIG_SRCDIR([.])
AC_CONFIG_HEADER([config.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_LIBTOOL

# Checks for libraries.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Default Compiler Option
if test x$CC = xgcc; then
  CFLAGS="$CFLAGS -O2 -Wall -Wformat=2 -pipe -Wno-sign-compare -D_FORTIFY_SOURCE=1 -Wcast-qual -Wcast-align -Wpointer-arith -Wwrite-strings -g -fno-omit-frame-pointer -Wswitch-enum"
fi

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
