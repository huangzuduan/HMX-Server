	if(MSVC)
	
		FIND_PATH(CURL_INCLUDE_DIR
          NAMES
            curl.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/curl/include
        )
		MARK_AS_ADVANCED(CURL_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_CURL_COMMON
          NAMES
            libcurl
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/curl/lib
        )
		MARK_AS_ADVANCED(LIB_CURL_COMMON)
		
		IF( CMAKE_BUILD_TYPE )
		  SET ( CURL_LIBRARIES
			debug ${LIB_CURL_COMMON}
			optimized ${LIB_CURL_COMMON}
		  )
        ELSE()
		  SET ( CURL_LIBRARIES
			optimized ${LIB_CURL_COMMON}
		  )
		  
        ENDIF()
		
    endif()