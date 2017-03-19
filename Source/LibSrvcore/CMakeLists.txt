file(GLOB_RECURSE headers_LibSrvcore_H ./*.h)
file(GLOB_RECURSE sources_LibSrvcore_CPP ./*.cpp)

include_directories(
	${MYSQL_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
	${PROTOBUL_INCLUDE_DIR}
	${ICONV_INCLUDE_DIR}
	${LIBXML_INCLUDE_DIR}
	${OPENSSL_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/LibNetMysql
	${CMAKE_SOURCE_DIR}/LibNetSocket
	${CMAKE_SOURCE_DIR}/LibProtocol
)

set(LibSrvcore_SRCS
	${headers_LibSrvcore_H}
	${sources_LibSrvcore_CPP}
)

add_library(LibSrvcore STATIC
  ${LibSrvcore_SRCS}
)

target_link_libraries(LibSrvcore
   ${BOOST_LIBRARIES}
   ${LIB_LIBEAY32_DEBUG}
   ${LIB_SSLEAY32_DEBUG}
)

if( WIN32 )
  if ( MSVC )
    SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/)
  endif()
endif()
