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
	${ICONV_INCLUDE_DIR}
	${LIBXML_INCLUDE_DIR}
	${OPENSSL_INCLUDE_DIR}
	${NET_INCLUDE_DIR}
	${PROTOBUL_INCLUDE_DIR}
	${FOUNDATION_INCLUDE_DIR}
	${CURL_INCLUDE_DIR}
	${JSON_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/Common
	${CMAKE_SOURCE_DIR}/Protocol
	${CMAKE_SOURCE_DIR}/LibNetSocket
)

add_executable(LoginServer
    ${LoginServer_SRCS}
)

target_link_libraries(LoginServer
	LIBSocket
	LIBProto
	LIBCommon
    ${MYSQL_LIBRARIES}
    ${BOOST_LIBRARIES}
	${THIRD_LIBRARIES}
	${ICONV_LIBRARIES}
	${CURL_LIBRARIES}
	${LIBXML_LIBRARIES}
	${OPENSSL_LIBRARIES}
	${PROTOBUF_LIBRARIES}
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
    add_custom_command(TARGET LoginServer
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../Conf/serivces.xml $(TargetDir)
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../Conf/serivces.xml ${PROJECT_BINARY_DIR}/LoginServer
    )
  endif()
endif()

# Generate precompiled header
if (USE_COREPCH)
        add_cxx_pch(LoginServer ${LoginServer_PCH_HDR} ${LoginServer_PCH_SRC})
endif ()
