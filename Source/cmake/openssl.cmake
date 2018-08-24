	if(MSVC)
	
		FIND_PATH(OPENSSL_INCLUDE_DIR
          NAMES
            openssl/aes.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/openssl/include
        )
		MARK_AS_ADVANCED(OPENSSL_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_LIBEAY32_COMMON
          NAMES
            libeay32
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/openssl/lib
        )
		MARK_AS_ADVANCED(LIB_LIBEAY32_COMMON)
		
		FIND_LIBRARY(LIB_SSLEAY32_COMMON
          NAMES
            ssleay32
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/openssl/lib
        )
		MARK_AS_ADVANCED(LIB_SSLEAY32_COMMON)
		
		IF( CMAKE_BUILD_TYPE )
		  SET ( OPENSSL_LIBRARIES
			debug ${LIB_LIBEAY32_COMMON}
			debug ${LIB_SSLEAY32_COMMON}
			optimized ${LIB_LIBEAY32_COMMON}
			optimized ${LIB_SSLEAY32_COMMON}
		  )
        ELSE()
		  SET ( OPENSSL_LIBRARIES
			optimized ${LIB_LIBEAY32_COMMON}
			optimized ${LIB_SSLEAY32_COMMON}
		  )
		  
        ENDIF()
		
    endif()