/*
* 哈希set头文件预处理
*
* 作者：bill.allen@163.com
*/

#ifndef __UNORDEREDSET_H_
#define __UNORDEREDSET_H_

#include "CompilerDefs.h"

#if COMPILER == COMPILER_GNU && GCC_VERSION > 40200
# include <tr1/unordered_set>
#elif COMPILER == COMPILER_GNU && GCC_VERSION >= 30000
# include <ext/hash_set>
#elif COMPILER == COMPILER_MICROSOFT && ((_MSC_VER >= 1500 && _HAS_TR1) || _MSC_VER >= 1700) // VS90(2008) SP1 or VS100(2010) SP1 or // VS110(2012)
# include <unordered_set>
#else
# include <hash_set>
#endif

#if COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1700 // VS110(2012)
#    define UNORDERED_SET std::unordered_set
#    define UNORDERED_MULTISET std::unordered_multiset
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1600 // VS100(2010)
#    define UNORDERED_SET std::unordered_set
#    define UNORDERED_MULTISET std::unordered_multiset
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1500 && _HAS_TR1 // VS90(2008) SP1
#    define UNORDERED_SET std::tr1::unordered_set
#    define UNORDERED_MULTISET std::tr1::unordered_multiset
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1300 // VS80(2005)
#    define UNORDERED_SET stdext::hash_set
#    define UNORDERED_MULTISET stdext::hash_multiset
#elif COMPILER == COMPILER_GNU && GCC_VERSION > 40200
#    define UNORDERED_SET std::tr1::unordered_set
#    define UNORDERED_MULTISET std::tr1::unordered_multiset
#elif COMPILER == COMPILER_GNU && GCC_VERSION >= 30000
#    define UNORDERED_SET __gnu_cxx::hash_set
#    define UNORDERED_MULTISET __gnu_cxx::hash_multiset
#else
#    define UNORDERED_SET std::hash_set
#    define UNORDERED_MULTISET std::hash_multiset
#endif

#endif
