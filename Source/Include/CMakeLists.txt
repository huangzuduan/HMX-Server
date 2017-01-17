
file(GLOB_RECURSE headers_Include_H ./*.h)
file(GLOB_RECURSE sources_Include_CPP ./*.cpp)


include_directories(
	${MYSQL_INCLUDE_DIR}
	${BOOST_INCLUDE_DIR}
	${ICONV_INCLUDE_DIR}
	${LIBXML_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/LibNetMysql
	${CMAKE_SOURCE_DIR}/LibNetSocket
	${CMAKE_SOURCE_DIR}/LibSrvCore
	${CMAKE_SOURCE_DIR}/LibProtocol
)

set(Include_SRCS
  ${headers_Include_H}
  ${sources_Include_CPP}
)

add_library(Include STATIC
  ${Include_SRCS}
)

target_link_libraries(Include
    ${BOOST_LIBRARIES}
)

if( WIN32 )
  if ( MSVC )
    SET(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/)
  endif()
endif()
