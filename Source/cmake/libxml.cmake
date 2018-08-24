	if(MSVC)
	
		FIND_PATH(LIBXML_INCLUDE_DIR
          NAMES
            libxml/list.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/libxml2/include
        )
		MARK_AS_ADVANCED(LIBXML_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_LIBXML_COMMON
          NAMES
            libxml2
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/libxml2/lib
        )
		MARK_AS_ADVANCED(LIB_LIBXML_COMMON)
		
		IF( CMAKE_BUILD_TYPE )
		  SET ( LIBXML_LIBRARIES
			debug ${LIB_LIBXML_COMMON}
			optimized ${LIB_LIBXML_COMMON}
		  )
        ELSE()
		  SET ( LIBXML_LIBRARIES
			optimized ${LIB_LIBXML_COMMON}
		  )
		  
        ENDIF()
		
    endif()