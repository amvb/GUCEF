/*	Public domain	*/

#ifdef _AGAR_AU_BEGIN_H_
#error Nested inclusion of <agar/au/begin.h>
#endif
#define _AGAR_AU_BEGIN_H_

#include <agar/core/types.h>
#include <agar/core/attributes.h>

/* Define internationalization macros if NLS is enabled. */
#if !defined(_)
# include <agar/config/enable_nls.h>
# ifdef ENABLE_NLS
#  include <libintl.h>
#  define _(String) dgettext("agar",String)
#  ifdef dgettext_noop
#   define N_(String) dgettext_noop("agar",String)
#  else
#   define N_(String) (String)
#  endif
#  define _AGAR_AU_DEFINED_NLS
# else
#  undef _
#  undef N_
#  undef ngettext
#  define _(String) (String)
#  define N_(String) (String)
#  define ngettext(Singular,Plural,Number) ((Number==1)?(Singular):(Plural))
#  define _AGAR_AU_DEFINED_NLS
# endif
#endif /* defined(_) */

/* Define __BEGIN_DECLS and __END_DECLS if needed. */
#if !defined(__BEGIN_DECLS) || !defined(__END_DECLS)
# define _AGAR_AU_DEFINED_CDECLS
# if defined(__cplusplus)
#  define __BEGIN_DECLS extern "C" {
#  define __END_DECLS   }
# else
#  define __BEGIN_DECLS
#  define __END_DECLS
# endif
#endif

/*
 * Expand "DECLSPEC" to any compiler-specific keywords, as required for proper
 * visibility of symbols in shared libraries.
 * See: http://gcc.gnu.org/wiki/Visibility
 */
#ifndef DECLSPEC
# if defined(__WIN32__) || defined(__WINRT__)
#  ifdef __BORLANDC__
#   ifdef _AGAR_AU_INTERNAL
#    define DECLSPEC
#    define _AGAR_AU_DEFINED_DECLSPEC
#   else
#    define DECLSPEC    __declspec(dllimport)
#    define _AGAR_AU_DEFINED_DECLSPEC
#   endif
#  else
#   define DECLSPEC __declspec(dllexport)
#   define _AGAR_AU_DEFINED_DECLSPEC
#  endif
# else
#  if defined(__GNUC__) && __GNUC__ >= 4
#   define DECLSPEC __attribute__ ((visibility("default")))
#   define _AGAR_AU_DEFINED_DECLSPEC
#  elif defined(__GNUC__) && __GNUC__ >= 2
#   define DECLSPEC __declspec(dllexport)
#   define _AGAR_AU_DEFINED_DECLSPEC
#  else
#   define DECLSPEC
#   define _AGAR_AU_DEFINED_DECLSPEC
#  endif
# endif
#endif
#ifdef __SYMBIAN32__
#undef DECLSPEC
#define DECLSPEC
#endif /* __SYMBIAN32__ */

/*
 * Force structure packing at 4 byte alignment. This is necessary if the
 * header is included in code which has structure packing set to an alternate
 * value. The packing is reset to the previous value in close.h.
 */
#if defined(_MSC_VER) || defined(__MWERKS__) || defined(__BORLANDC__)
# ifdef _MSC_VER
#  pragma warning(disable: 4103)
# endif
# ifdef __BORLANDC__
#  pragma nopackwarning
# endif
# pragma pack(push,4)
#elif (defined(__MWERKS__) && defined(__MACOS__))
# pragma options align=mac68k4byte
# pragma enumsalwaysint on
#endif

/*
 * Expand "__inline__" to any compiler-specific keyword needed for defining
 * an inline function, if supported.
 */
#ifdef __GNUC__
# define _AGAR_AU_USE_INLINE
#else
# if defined(_MSC_VER) || defined(__BORLANDC__) || defined(__DMC__) || defined(__SC__) || defined(__WATCOMC__) || defined(__LCC__) || defined(__DECC) || defined(__EABI__)
#  ifndef __inline__
#   define __inline__	__inline
#  endif
#  define _AGAR_AU_USE_INLINE
# else
#  if !defined(__MRC__) && !defined(_SGI_SOURCE)
#   ifndef __inline__
#    define __inline__ inline
#   endif
#   define _AGAR_AU_USE_INLINE
#  endif
# endif
#endif /* !__GNUC__ */
#ifndef _AGAR_AU_USE_INLINE
# define __inline__
#endif

/* Define NULL if needed. */
#if !defined(NULL) && !defined(__MACH__)
# ifdef __cplusplus
#  define NULL 0
#  define _AGAR_AU_DEFINED_NULL
# else
#  define NULL ((void *)0)
#  define _AGAR_AU_DEFINED_NULL
# endif
#endif
