	if(MSVC)
	
		FIND_PATH(ICONV_INCLUDE_DIR
          NAMES
            iconv.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/iconv/include
        )
		MARK_AS_ADVANCED(ICONV_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_ICONV_COMMON
          NAMES
            iconv
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/iconv/lib
        )
		MARK_AS_ADVANCED(LIB_ICONV_COMMON)
		
		IF( CMAKE_BUILD_TYPE )
		  SET ( ICONV_LIBRARIES
			debug ${LIB_ICONV_COMMON}
			optimized ${LIB_ICONV_COMMON}
		  )
        ELSE()
		  SET ( ICONV_LIBRARIES
			optimized ${LIB_ICONV_COMMON}
		  )
		  
        ENDIF()
		
    endif()