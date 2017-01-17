########### DBServer ###############

file(GLOB_RECURSE GameServer_SRCS *.h *.cpp)

# precompiled header
if (USE_COREPCH)
  set(GameServer_PCH_HDR GameServer_PCH.h)
  set(GameServer_PCH_SRC GameServer_PCH.cpp)
endif ()

include_directories(
    ${BOOST_INCLUDE_DIR}
	${MYSQL_INCLUDE_DIR}
	${PROTOBUL_INCLUDE_DIR}
	${ICONV_INCLUDE_DIR}
	${LIBXML_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/Include
	${CMAKE_SOURCE_DIR}/LibSrvcore
	${CMAKE_SOURCE_DIR}/LibProtocol
	${CMAKE_SOURCE_DIR}/LibNetMysql
	${CMAKE_SOURCE_DIR}/LibNetSocket
)

add_executable(GameServer
    ${GameServer_SRCS}
)

target_link_libraries(GameServer
	LIBMysql
	LIBSocket
	LibSrvcore
	LibProtocol
    ${BOOST_LIBRARIES}
	${LIB_PROTOBUF_DEBUG}
	${LIB_ICONV_DEBUG}
	${LIB_LIBXML_DEBUG}
)

IF(UNIX)
    target_link_libraries(GameServer
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
        add_cxx_pch(GameServer ${GameServer_PCH_HDR} ${GameServer_PCH_SRC})
endif ()
