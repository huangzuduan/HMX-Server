########### DBServer ###############

file(GLOB_RECURSE LoginServer_SRCS *.h *.cpp *.cc)

# precompiled header
if (USE_COREPCH)
  set(LoginServer_PCH_HDR LoginServer_PCH.h)
  set(LoginServer_PCH_SRC LoginServer_PCH.cpp)
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

add_executable(LoginServer
    ${LoginServer_SRCS}
)

target_link_libraries(LoginServer
	LIBMysql
	LIBSocket
	LibSrvcore
	LibProtocol
    ${MYSQL_LIBRARIES}
    ${BOOST_LIBRARIES}
	${LIB_PROTOBUF_DEBUG}
	${LIB_ICONV_DEBUG}
	${LIB_LIBXML_DEBUG}
)

IF(UNIX)
    target_link_libraries(LoginServer
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
        add_cxx_pch(LoginServer ${LoginServer_PCH_HDR} ${LoginServer_PCH_SRC})
endif ()
