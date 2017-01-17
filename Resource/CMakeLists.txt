########### Resource ###############

file(GLOB_RECURSE Resource_SRCS *.txt *.mps *.zps)


IF(UNIX)
    if( CMAKE_BUILD_TYPE STREQUAL "Debug")
        SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/Debug/)
    else()
        SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/../Bin/Release/)
    endif()
ENDIF(UNIX)

if( WIN32 )
  if ( MSVC )
    add_custom_command(TARGET Resource
      POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.txt $(TargetDir)
	  COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/*.xml ${PROJECT_BINARY_DIR}/servers/Resource
    )
  endif()
endif()
