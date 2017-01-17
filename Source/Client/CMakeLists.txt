########### DBServer ###############

file(GLOB_RECURSE Client_SRCS *.h *.cpp *.cc)

# precompiled header
if (USE_COREPCH)
  set(Client_PCH_HDR Client_PCH.h)
  set(Client_PCH_SRC Client_PCH.cpp)
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

add_executable(Client
    ${Client_SRCS}
)

target_link_libraries(Client
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
