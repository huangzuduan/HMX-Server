########### LogServer ###############

file(GLOB_RECURSE LogServer_SRCS *.h *.cpp *.cc)

# precompiled header
if (USE_COREPCH)
  set(LogServer_PCH_HDR LogServer_PCH.h)
  set(LogServer_PCH_SRC LogServer_PCH.cpp)
endif ()

include_directories(
    ${CMAKE_SOURCE_DIR}/Shared/CommonDef
    ${CMAKE_SOURCE_DIR}/Shared/Protocol
    ${CMAKE_SOURCE_DIR}/Shared/Utility
	${CMAKE_SOURCE_DIR}/Shared/Zebra
	
	${CMAKE_SOURCE_DIR}/DyNetSocket
	${CMAKE_SOURCE_DIR}/DyNetMysql
	
    ${MYSQL_INCLUDE_DIR}
    ${BOOST_INCLUDE_DIR}
)

add_executable(LogServer
    ${LogServer_SRCS}
)

target_link_libraries(LogServer
    Shared
	LIBSocket
	LIBMysql
    ${MYSQL_LIBRARIES}
    ${BOOST_LIBRARIES}
)

IF(UNIX)
    target_link_libraries(LogServer
        pthread
        rt
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
        add_cxx_pch(LogServer ${LogServer_PCH_HDR} ${LogServer_PCH_SRC})
endif ()
