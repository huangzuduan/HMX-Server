########### DBServer ###############

file(GLOB_RECURSE PayCenterServer_SRCS *.h *hpp *.cpp *.cc)

# precompiled header
if (USE_COREPCH)
  set(PayCenterServer_PCH_HDR PayCenterServer_PCH.h)
  set(PayCenterServer_PCH_SRC PayCenterServer_PCH.cpp)
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
	${JSON_INCLUDE_DIR}
	${XML_INCLUDE_DIR}
	${UTIL_INCLUDE_DIR}
	${CURL_INCLUDE_DIR}
	${CMAKE_SOURCE_DIR}/Common
	${CMAKE_SOURCE_DIR}/Protocol
	${CMAKE_SOURCE_DIR}/LibNetMysql
	${CMAKE_SOURCE_DIR}/LibNetSocket
)

add_executable(PayCenterServer
    ${PayCenterServer_SRCS}
)

target_link_libraries(PayCenterServer
	LIBMysql
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

if( WIN32 )
	if ( MSVC )
		SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/)
		add_custom_command(TARGET PayCenterServer
			POST_BUILD
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../serivces.xml $(TargetDir)
			COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/../serivces.xml ${PROJECT_BINARY_DIR}/PayCenterServer
		)
	endif()	
endif()

IF(UNIX)
    target_link_libraries(PayCenterServer
        pthread
        rt
    )

    if( CMAKE_BUILD_TYPE STREQUAL "Debug")
        SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/Debug/)
    else()
        SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/Release/)
    endif()
ENDIF(UNIX)

# Generate precompiled header
if (USE_COREPCH)
        add_cxx_pch(PayCenterServer ${PayCenterServer_PCH_HDR} ${PayCenterServer_PCH_SRC})
endif ()
