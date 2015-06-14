
AC_INIT([ThorsStream], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

# Set up the build system
AC_CONFIG_MACRO_DIR([build/autotools/m4])
AX_THOR_FUNC_BUILD
AC_CONFIG_AUX_DIR([build/autotools/build])


AC_CONFIG_SRCDIR([src/SocketStream/ThorsStream.cpp])
AC_PROG_CXX
AX_THOR_PROG_COV
LT_INIT

AX_CHECK_COMPILE_FLAG([-ansi], [AC_SUBST([CXXFLAGS], ["$CXXFLAGS -ansi"])])

AX_THOR_FUNC_LANG_FLAG(14)


AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([ src/SocketStream/SocketStreamConfig.h ])
AC_CONFIG_FILES([Makefile.extra Makefile.config])
AC_OUTPUT