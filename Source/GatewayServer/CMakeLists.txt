########### DBServer ###############

file(GLOB_RECURSE GatewayServer_SRCS *.h *.hpp *.cpp *.cc)

# precompiled header
if (USE_COREPCH)
  set(GatewayServer_PCH_HDR GatewayServer_PCH.h)
  set(GatewayServer_PCH_SRC GatewayServer_PCH.cpp)
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

add_executable(GatewayServer
    ${GatewayServer_SRCS}
)

target_link_libraries(GatewayServer
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
    target_link_libraries(GatewayServer
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
    add_custom_command(TARGET GatewayServer
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../Conf/serivces.xml $(TargetDir)
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../Conf/serivces.xml ${PROJECT_BINARY_DIR}/GatewayServer
    )
  endif()
endif()

# Generate precompiled header
if (USE_COREPCH)
        add_cxx_pch(GatewayServer ${GatewayServer_PCH_HDR} ${GatewayServer_PCH_SRC})
endif ()
