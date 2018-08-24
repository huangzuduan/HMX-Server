########### DBServer ###############

file(GLOB_RECURSE GameServer_SRCS *.h *.hpp *.cpp)

# precompiled header
if (USE_COREPCH)
  set(GameServer_PCH_HDR GameServer_PCH.h)
  set(GameServer_PCH_SRC GameServer_PCH.cpp)
endif ()

include_directories(
    ${MYSQL_INCLUDE_DIR}
    ${BOOST_INCLUDE_DIR}
	${ICONV_INCLUDE_DIR}
	${LIBXML_INCLUDE_DIR}
	${OPENSSL_INCLUDE_DIR}
	${NET_INCLUDE_DIR}
	${PROTOBUL_INCLUDE_DIR}
	${FOUNDATION_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/Common
	${CMAKE_SOURCE_DIR}/Protocol
	${CMAKE_SOURCE_DIR}/LibNetSocket
)

add_executable(GameServer
    ${GameServer_SRCS}
)

target_link_libraries(GameServer
	LIBSocket
	LIBProto
	LIBCommon
    ${MYSQL_LIBRARIES}
    ${BOOST_LIBRARIES}
	${THIRD_LIBRARIES}
	${ICONV_LIBRARIES}
	${LIBXML_LIBRARIES}
	${OPENSSL_LIBRARIES}
	${PROTOBUF_LIBRARIES}
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
    add_custom_command(TARGET GameServer
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../Conf/serivces.xml $(TargetDir)
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../Conf/serivces.xml ${PROJECT_BINARY_DIR}/GameServer
    )
  endif()
endif()

# Generate precompiled header
if (USE_COREPCH)
        add_cxx_pch(GameServer ${GameServer_PCH_HDR} ${GameServer_PCH_SRC})
endif ()
