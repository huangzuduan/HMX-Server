/*
* ±‡“Î∆˜‘§¥¶¿Ì∫Í
*
* ◊˜’ﬂ£∫bill.allen@163.com
*/

// œµÕ≥ºÏ≤‚ 
#ifndef __COMPILERDEFS_H_
#define __COMPILERDEFS_H_

#define PLATFORM_WINDOWS 1
#define PLATFORM_UNIX    2

#if defined( _WIN64 )
#  define PLATFORM PLATFORM_WINDOWS
#elif defined( __WIN32__ ) || defined( WIN32 ) || defined( _WIN32 )
#  define PLATFORM PLATFORM_WINDOWS
#else
#  define PLATFORM PLATFORM_UNIX
#endif

// ±‡“Î∆˜ºÏ≤‚ 
#define COMPILER_MICROSOFT 1
#define COMPILER_GNU       2

#ifdef _MSC_VER
#  define COMPILER COMPILER_MICROSOFT
#elif defined( __GNUC__ )
#  define COMPILER COMPILER_GNU
#  define GCC_VERSION (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#else
#  error "FATAL ERROR: Unknown compiler."
#endif

// ±‡“Î∏Ò ΩºÏ≤‚ 
#if PLATFORM == PLATFORM_WINDOWS
# if _WIN64
#  define ENVIRONMENT64
# else
#  define ENVIRONMENT32
# endif
#endif

#if __GNUC__
# if __x86_64__ || __ppc64__
#  define ENVIRONMENT64
# else
#  define ENVIRONMENT32
# endif
#endif

#endif

