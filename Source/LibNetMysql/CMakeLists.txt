file(GLOB_RECURSE headers_DyNetMysql_H *.h)

file(GLOB_RECURSE sources_DyNetMysql_CC *.cc)
file(GLOB_RECURSE sources_DyNetMysql_CPP *.cpp)

#ADD_DEFINITIONS("-DLIB_MYSQL_API")

include_directories(
  ${BOOST_INCLUDE_DIR}
  ${MYSQL_INCLUDE_DIR}
)

set(DyNetMysql_SRCS
  ${headers_DyNetMysql_H}
  ${sources_DyNetMysql_CC}
  ${sources_DyNetMysql_CPP}
)

add_library(LIBMysql STATIC 

  ${DyNetMysql_SRCS}
)

if( WIN32 )
  if ( MSVC )
    SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/)
  endif()
endif()

