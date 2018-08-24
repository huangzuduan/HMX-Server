	if(MSVC)
	
		FIND_PATH(MYSQL_INCLUDE_DIR
          NAMES
            mysql.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/mysql/include
        )
        MARK_AS_ADVANCED(MYSQL_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_MYSQL_COMMON
          NAMES
            libmysql
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/mysql/lib
		  NO_DEFAULT_PATH
        )

        MARK_AS_ADVANCED(LIB_MYSQL_COMMON)
		
		IF( CMAKE_BUILD_TYPE )
		  SET ( MYSQL_LIBRARIES
			debug ${LIB_MYSQL_COMMON}
			optimized ${LIB_MYSQL_COMMON}
		  )
        ELSE()
		  SET ( MYSQL_LIBRARIES
			optimized ${LIB_MYSQL_COMMON}
		  )
		  
        ENDIF()
		
    endif()