	if(MSVC)
	
		FIND_PATH(PROTOBUL_INCLUDE_DIR
          NAMES
            google/protobuf/any.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/protobuf/include
        )
		MARK_AS_ADVANCED(PROTOBUL_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_PROTOBUF_DEBUG
          NAMES
            libprotobufd
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/protobuf/lib
        )
		MARK_AS_ADVANCED(LIB_PROTOBUF_DEBUG)
		
		FIND_LIBRARY(LIB_PROTOBUF_RELEASE
          NAMES
            libprotobuf
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/protobuf/lib
        )
		MARK_AS_ADVANCED(LIB_PROTOBUF_RELEASE)
		
		IF( CMAKE_BUILD_TYPE )
		  SET ( PROTOBUF_LIBRARIES
			debug ${LIB_PROTOBUF_DEBUG}
			optimized ${LIB_PROTOBUF_RELEASE}
		  )
        ELSE()
		  SET ( PROTOBUF_LIBRARIES
			optimized ${LIB_PROTOBUF_RELEASE}
		  )
		  
        ENDIF()
		
    endif()