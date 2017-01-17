########### HelpTools ###############

file(GLOB_RECURSE HelpTools_SRCS *.h *.cpp *.cc)

# precompiled header
if (USE_COREPCH)
  set(HelpTools_PCH_HDR HelpTools_PCH.h)
  set(HelpTools_PCH_SRC HelpTools_PCH.cpp)
endif ()

include_directories(
    ${MYSQL_INCLUDE_DIR}
    ${BOOST_INCLUDE_DIR}
	${PROTOBUL_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/Include	
	${CMAKE_SOURCE_DIR}/LibSrvCore
	${CMAKE_SOURCE_DIR}/LibProtocol
	${CMAKE_SOURCE_DIR}/LibNetMysql
	${CMAKE_SOURCE_DIR}/LibNetSocket
)

add_executable(HelpTools
    ${HelpTools_SRCS}
)

target_link_libraries(HelpTools
	LIBMysql
	LIBSocket
	LibSrvCore
	LibProtocol
    ${MYSQL_LIBRARIES}
    ${BOOST_LIBRARIES}
	${LIB_PROTOBUF_DEBUG}
)

IF(UNIX)
    target_link_libraries(HelpTools
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
	
	add_custom_command(TARGET HelpTools
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/ht_cfg.xml $(TargetDir)
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/ht_cfg.xml ${PROJECT_BINARY_DIR}/HelpTools
    )
	
  endif()
endif()

# Generate precompiled header
if (USE_COREPCH)
        add_cxx_pch(HelpTools ${HelpTools_PCH_HDR} ${HelpTools_PCH_SRC})
endif ()
