########### DBServer ###############

file(GLOB_RECURSE ShiftServer_SRCS *.h *.cpp *.cc)

# precompiled header
if (USE_COREPCH)
  set(ShiftServer_PCH_HDR ShiftServer_PCH.h)
  set(ShiftServer_PCH_SRC ShiftServer_PCH.cpp)
endif ()

include_directories(
    ${MYSQL_INCLUDE_DIR}
    ${BOOST_INCLUDE_DIR}
	${PROTOBUL_INCLUDE_DIR}
	${ICONV_INCLUDE_DIR}
	${LIBXML_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/Include	
	${CMAKE_SOURCE_DIR}/LibSrvcore
	${CMAKE_SOURCE_DIR}/LibProtocol
	${CMAKE_SOURCE_DIR}/LibNetMysql
	${CMAKE_SOURCE_DIR}/LibNetSocket
)

add_executable(ShiftServer
    ${ShiftServer_SRCS}
)

target_link_libraries(ShiftServer
	LIBMysql
	LIBSocket
	LibSrvcore
)

IF(UNIX)
    target_link_libraries(ShiftServer
        pthread
        rt
        z
        dl
    )

    if( CMAKE_BUILD_TYPE STREQUAL "Debug")
        SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/Debug/)
    else()
        SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/Release/)
    endif()
ENDIF(UNIX)

if( WIN32 )
  if ( MSVC )
    SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/)
  endif()
endif()

# Generate precompiled header
if (USE_COREPCH)
        add_cxx_pch(ShiftServer ${ShiftServer_PCH_HDR} ${ShiftServer_PCH_SRC})
endif ()
