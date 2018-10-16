#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([SimpleNodeStateMachine], [1.0.0])

# Initialize automake
AM_INIT_AUTOMAKE([subdir-objects])

# Initialize libtool
LT_INIT([disable-static])

AC_CONFIG_SRCDIR([NodeStateMachine.h])

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC

# Checks for libraries.
PKG_CHECK_MODULES([GLIBMM], [glibmm-2.4 giomm-2.4])
PKG_CHECK_MODULES([IVILogging], [ivi-logging])

# Checks for header files.
AC_CHECK_HEADERS([stdint.h syslog.h])

# Path to directory for D-Bus policy files.
AC_ARG_WITH([dbuspolicydir],
            AC_HELP_STRING([--with-dbuspolicydir=DIR], [D-Bus policy directory]),
            [dbuspolicydir=${withval}],
            [dbuspolicydir=$(pkg-config --variable=sysconfdir dbus-1)/dbus-1/system.d])
AC_SUBST([dbuspolicydir], [${dbuspolicydir}])

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
