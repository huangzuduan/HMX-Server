########### DBServer ###############

file(GLOB_RECURSE SRCS_1 *.h *.cpp)

# precompiled header
if (USE_COREPCH)
  set(Client_PCH_HDR Client_PCH.h)
  set(Client_PCH_SRC Client_PCH.cpp)
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

add_executable(Client
    ${SRCS_1}
)

target_link_libraries(Client
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
    target_link_libraries(Client
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
    add_custom_command(TARGET Client
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/c_cfg.xml $(TargetDir)
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/c_cfg.xml ${PROJECT_BINARY_DIR}/Client
    )
  endif()
endif()

# Generate precompiled header
if (USE_COREPCH)
        add_cxx_pch(Client ${Client_PCH_HDR} ${Client_PCH_SRC})
endif ()

