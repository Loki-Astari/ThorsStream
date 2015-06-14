/* src/SocketStream/SocketStreamConfig.h.  Generated from SocketStreamConfig.h.in by configure.  */
/* config.h.in.  Generated from configure.ac by autoheader.  */

/* Define if building universal (internal helper macro) */
/* #undef AC_APPLE_UNIVERSAL_BUILD */

/* Name of the 64/128 bit endian swapping function */
/* #undef BSWAP64 */

/* Define to 1 if you have the <asm/byteorder.h> header file. */
/* #undef HAVE_ASM_BYTEORDER_H */

/* Define to 1 if BSWAP64 is defined to the name of a valid 64 bit endian
   swapping function */
/* #undef HAVE_BSWAP64 */

/* Define to 1 if you have the <dlfcn.h> header file. */
#define HAVE_DLFCN_H 1

/* Define to 1 if you have the <inttypes.h> header file. */
#define HAVE_INTTYPES_H 1

/* Define to 1 if you have the <memory.h> header file. */
#define HAVE_MEMORY_H 1

/* Define to 1 if you have the <stdint.h> header file. */
#define HAVE_STDINT_H 1

/* Define to 1 if you have the <stdlib.h> header file. */
#define HAVE_STDLIB_H 1

/* Define to 1 if you have the <strings.h> header file. */
#define HAVE_STRINGS_H 1

/* Define to 1 if you have the <string.h> header file. */
#define HAVE_STRING_H 1

/* Define to 1 if you have the <sys/endian.h> header file. */
/* #undef HAVE_SYS_ENDIAN_H */

/* Define to 1 if you have the <sys/stat.h> header file. */
#define HAVE_SYS_STAT_H 1

/* Define to 1 if you have the <sys/types.h> header file. */
#define HAVE_SYS_TYPES_H 1

/* Define to 1 if you have the <unistd.h> header file. */
#define HAVE_UNISTD_H 1

/* When on Yaml Serialization code will be compiled */
/* #undef HAVE_YAML */

/* Define to the sub-directory where libtool stores uninstalled libraries. */
#define LT_OBJDIR ".libs/"

/* We have functions to convert host to network byte order for 64/128 bit
   values */
/* #undef NETWORK_BYTE_ORDER */

/* Name of package */
#define PACKAGE "thorsstream"

/* Define to the address where bug reports for this package should be sent. */
#define PACKAGE_BUGREPORT "Loki.Astari+ThorsAnvil@gmail.com"

/* Define to the full name of this package. */
#define PACKAGE_NAME "ThorsStream"

/* Define to the full name and version of this package. */
#define PACKAGE_STRING "ThorsStream 0.1"

/* Define to the one symbol short name of this package. */
#define PACKAGE_TARNAME "thorsstream"

/* Define to the home page for this package. */
#define PACKAGE_URL ""

/* Define to the version of this package. */
#define PACKAGE_VERSION "0.1"

/* Define to 1 if you have the ANSI C header files. */
#define STDC_HEADERS 1

/* Version number of package */
#define VERSION "0.1"

/* Define WORDS_BIGENDIAN to 1 if your processor stores words with the most
   significant byte first (like Motorola and SPARC, unlike Intel). */
#if defined AC_APPLE_UNIVERSAL_BUILD
# if defined __BIG_ENDIAN__
#  define WORDS_BIGENDIAN 1
# endif
#else
# ifndef WORDS_BIGENDIAN
/* #  undef WORDS_BIGENDIAN */
# endif
#endif

/* Define to 1 if `lex' declares `yytext' as a `char *' by default, not a
   `char[]'. */
/* #undef YYTEXT_POINTER */
