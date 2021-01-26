
AC_INIT([libepdfcrypt],[0.1])
AC_CONFIG_SRCDIR(lib/epdf.cpp)
AC_CONFIG_HEADERS(include/config.h)
AC_CONFIG_MACRO_DIR([m4])
LT_INIT

AC_PROG_CXX
AC_LANG([C++])

AM_INIT_AUTOMAKE
AC_PROG_INSTALL

PKG_CHECK_MODULES(GMIME, gmime-2.6)
PKG_CHECK_MODULES(ICU, [icu-uc icu-i18n])
AX_BOOST_BASE([1.52])
AX_BOOST_LOCALE

CXXFLAGS="$CXXFLAGS -W -Wall -pthread"
CFLAGS="$CFLAGS -W -Wall -pthread"
CPPFLAGS="$CPPFLAGS -I/usr/local/include"
LIBS="$LIBS -L/usr/local/lib"

AC_ARG_ENABLE(debug,
	      [  --enable-debug          compile with gdb debug information.], 
	      CXXFLAGS="$CXXFLAGS -g")

AC_ARG_ENABLE(optimize,
	      [  --enable-optimize       optimize compiled code (-O2).], 
	      CXXFLAGS="$CXXFLAGS -O2")

AC_CHECK_HEADER(hpdf.h, [], AC_MSG_ERROR([Missing libharu header.]))
AC_SEARCH_LIBS([HPDF_New], [hpdf], [], AC_MSG_ERROR([Missing libharu library.]))
    
AC_CONFIG_FILES([Makefile lib/Makefile tests/Makefile include/Makefile fonts/Makefile])
AC_OUTPUT

