#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ(2.59)
AC_INIT(eChan, 0.5.1, alan.alvarez@us.army.mil)
AC_CONFIG_SRCDIR([src/main.cpp])
AC_CONFIG_HEADER([config.h])
AM_INIT_AUTOMAKE

# Checks for programs.
AC_PROG_CXX
AC_PROG_CC
AC_PROG_MAKE_SET
AC_PROG_CPP

# Checks for libraries.

# Checks for header files.
AC_HEADER_STDC
AC_CHECK_HEADERS([arpa/inet.h fcntl.h netdb.h netinet/in.h string.h sys/socket.h sys/time.h unistd.h])

# Checks for typedefs, structures, and compiler characteristics.
AC_HEADER_STDBOOL
AC_C_CONST
AC_C_INLINE
AC_HEADER_TIME

# Checks for library functions.
AC_FUNC_ERROR_AT_LINE
AC_FUNC_FORK
AC_FUNC_SELECT_ARGTYPES
AC_CHECK_FUNCS([memset pow select socket strcasecmp])

MYSQLPP_LIB=/usr/local/lib
AC_ARG_WITH(mysqlpp-lib,
	AC_HELP_STRING([--with-mysqlpp-lib=MYSQLPPLIBDIR],
			[Specify location to find libmysqlpp.so, default is \
/usr/local/lib]),
	[MYSQLPP_LIB=$withval]
)

MYSQLPP_INCLUDE=/usr/local/include/mysql++/
AC_ARG_WITH(mysqlpp-include,
	AC_HELP_STRING([--with-mysqlpp-include=MYSQLPPINCLUDEDIR],
			[Specify location to find mysql++.h, default is \
/usr/local/include/mysql++]),
	[MYSQLPP_INCLUDE=$withval]
)

AC_MSG_CHECKING(for mysql++.h)
if [test -f "$MYSQLPP_INCLUDE/mysql++.h"]; then
	/bin/true
elif [test -f "/usr/local/include/mysql++.h"]; then
	MYSQLPP_INCLUDE=/usr/local/include
elif [test -f "/usr/include/mysql++.h"]; then
	MYSQLPP_INCLUDE=/usr/include
elif [test -f "/usr/include/mysql++/mysql++.h"]; then
	MYSQLPP_INCLUDE=/usr/include/mysql++
else
	AC_MSG_ERROR( Unable to find mysql++.h )
fi
AC_MSG_RESULT(yes)

AC_MSG_CHECKING(for libmysqlpp.so)
if [test -f "$MYSQLPP_LIB/libmysqlpp.so"]; then
	/bin/true
elif [test -f "/usr/lib/libmysqlpp.so"]; then
	MYSQLPP_LIB=/usr/lib
elif [test -f "/usr/lib/mysql++/libmysqlpp.so"]; then
	MYSQLPP_LIB=/usr/lib/mysql++
elif [test -f "/usr/local/mysql++/lib/libmysqlpp.so"]; then
	MYSQLPP_LIB=/usr/local/mysql++/lib
else
	AC_MSG_ERROR( Unable to find libmysqlpp.so)
fi
AC_MSG_RESULT(yes)

AC_SUBST(MYSQLPP_INCLUDE)
AC_SUBST(MYSQLPP_LIB)

AC_CONFIG_FILES([Makefile
                 src/Makefile])
AC_OUTPUT
