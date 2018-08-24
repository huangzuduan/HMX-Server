file(GLOB_RECURSE headers_LibSrvcore_H ./*.h)
file(GLOB_RECURSE sources_LibSrvcore_CPP ./*.cpp)

include_directories(
	${MYSQL_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
	${PROTOBUL_INCLUDE_DIR}
	${ICONV_INCLUDE_DIR}
	${LIBXML_INCLUDE_DIR}
	${OPENSSL_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/Protocol
	${CMAKE_SOURCE_DIR}/LibNetMysql
	${CMAKE_SOURCE_DIR}/LibNetSocket
)

set(LibSrvcore_SRCS
	${headers_LibSrvcore_H}
	${sources_LibSrvcore_CPP}
)

add_library(LIBCommon STATIC
  ${LibSrvcore_SRCS}
)

if( WIN32 )
  if ( MSVC )
    SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/)
  endif()
endif()
