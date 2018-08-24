file(GLOB_RECURSE headers_DyNetSocket_H *.h *.hpp)

file(GLOB_RECURSE sources_DyNetSocket_CC *.cc)
file(GLOB_RECURSE sources_DyNetSocket_CPP *.cpp)

#ADD_DEFINITIONS("-DLIB_SOCKET_API")

include_directories(
  ${BOOST_INCLUDE_DIR}
  ${PROTOBUL_INCLUDE_DIR}
)

set(DyNetSocket_SRCS
  ${headers_DyNetSocket_H}
  ${sources_DyNetSocket_CC}
  ${sources_DyNetSocket_CPP}
)

add_library(LIBSocket STATIC 
  ${DyNetSocket_SRCS}
)

if( WIN32 )
  if ( MSVC )
    SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/)
  endif()
endif()

