
AC_INIT([ThorsStream], [0.1], [Loki.Astari+ThorsAnvil@gmail.com])
AC_PREREQ([2.65])

# Set up the build system
if [[ ! -e build/Notes ]]; then
    git submodule init
    git submodule update
fi
AC_CONFIG_MACRO_DIR([build/autotools/m4])
AC_CONFIG_AUX_DIR([build/autotools/build])
AX_THOR_FUNC_BUILD


AC_CONFIG_SRCDIR([src/SocketStream/ThorsStream.cpp])
AC_PROG_CXX
AX_CHECK_COMPILE_FLAG([-ansi], [AC_SUBST([CXXFLAGS], [" -ansi"])])
AX_THOR_FUNC_LANG_FLAG(17)
AX_THOR_PROG_COV


LT_INIT

AC_CHECK_LIB([curl], [curl_easy_init], [], [AC_MSG_ERROR([
 
Error: Could not find libcurl

                ], [1])]
            )


AC_DEFINE([HEADER_ONLY], [0], [Enable to use header only libraries])
AC_DEFINE([HEADER_ONLY_INCLUDE], [], [For header only convery to inline])
AM_INIT_AUTOMAKE([foreign -Wall -Werror])
AC_CONFIG_HEADERS([src/SocketStream/ThorsStreamConfig.h])
AC_CONFIG_FILES([Makefile.extra Makefile.config:build/autotools/build/Makefile.config.in:Makefile.config.in])
AC_OUTPUT
