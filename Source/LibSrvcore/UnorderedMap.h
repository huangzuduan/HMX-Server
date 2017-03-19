/*
* 哈希map头文件预处理
*
* 作者：bill.allen@163.com
*/

#ifndef __UNORDEREDMAP_H_
#define __UNORDEREDMAP_H_

#include "CompilerDefs.h"

#if COMPILER == COMPILER_GNU && GCC_VERSION > 40200
# include <tr1/unordered_map>
#elif COMPILER == COMPILER_GNU && GCC_VERSION >= 30000
# include <ext/hash_map>
#elif COMPILER == COMPILER_MICROSOFT && ((_MSC_VER >= 1500 && _HAS_TR1) || _MSC_VER >= 1700) // VS90(2008) SP1 or VS100(2010) SP1 or // VS110(2012)
# include <unordered_map>
#else
# include <hash_map>
#endif

#if COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1700 // VS110(2012)
#    define UNORDERED_MAP std::unordered_map
#    define UNORDERED_MULTIMAP std::unordered_multimap
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1600 // VS100(2010)
#    define UNORDERED_MAP std::unordered_map
#    define UNORDERED_MULTIMAP std::unordered_multimap
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1500 && _HAS_TR1 // VS90(2008) SP1
#    define UNORDERED_MAP std::tr1::unordered_map
#    define UNORDERED_MULTIMAP std::tr1::unordered_multimap
#elif COMPILER == COMPILER_MICROSOFT && _MSC_VER >= 1300 // VS80(2005)
#    define UNORDERED_MAP stdext::hash_map
#    define UNORDERED_MULTIMAP stdext::hash_multimap
#elif COMPILER == COMPILER_GNU && GCC_VERSION > 40200
#    define UNORDERED_MAP std::tr1::unordered_map
#    define UNORDERED_MULTIMAP std::tr1::unordered_multimap
#elif COMPILER == COMPILER_GNU && GCC_VERSION >= 30000
#    define UNORDERED_MAP __gnu_cxx::hash_map
#    define UNORDERED_MULTIMAP __gnu_cxx::hash_multimap
#else
#    define UNORDERED_MAP std::hash_map
#    define UNORDERED_MULTIMAP std::hash_multimap
#endif

#endif
