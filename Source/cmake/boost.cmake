	if(MSVC)
	
		FIND_PATH(BOOST_INCLUDE_DIR
          NAMES
            boost/unordered_map.hpp
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/include
        )
        MARK_AS_ADVANCED(BOOST_INCLUDE_DIR)

        FIND_LIBRARY(LIB_BOOST_SYSTEM_DEBUG
          NAMES
            libboost_system-vc140-mt-sgd-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
		  NO_DEFAULT_PATH
        )
		
		FIND_LIBRARY(LIB_BOOST_SYSTEM_RELEASE
          NAMES
            libboost_system-vc140-mt-s-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_DATA_TIME_DEBUG
          NAMES
            libboost_date_time-vc140-mt-sgd-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_THREAD_DEBUG
          NAMES
            libboost_thread-vc140-mt-sgd-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_FILESYSTEM_DEBUG
          NAMES
            libboost_filesystem-vc140-mt-sgd-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_PROGRAM_OPTIONS_DEBUG
          NAMES
            libboost_program_options-vc140-mt-sgd-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_CHRONO_DEBUG
          NAMES
            libboost_chrono-vc140-mt-sgd-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_REGEX_DEBUG
          NAMES
            libboost_regex-vc140-mt-sgd-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_DATA_TIME_RELEASE
          NAMES
            libboost_date_time-vc140-mt-s-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_THREAD_RELEASE
          NAMES
            libboost_thread-vc140-mt-s-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_FILESYSTEM_RELEASE
          NAMES
            libboost_filesystem-vc140-mt-s-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_PROGRAM_OPTIONS_RELEASE
          NAMES
            libboost_program_options-vc140-mt-s-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_CHRONO_RELEASE
          NAMES
            libboost_chrono-vc140-mt-s-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        FIND_LIBRARY(LIB_BOOST_REGEX_RELEASE
          NAMES
            libboost_regex-vc140-mt-s-1_60
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/boost/lib
        )

        MARK_AS_ADVANCED(   LIB_BOOST_SYSTEM_DEBUG
                            LIB_BOOST_SYSTEM_RELEASE
                            LIB_BOOST_DATA_TIME_DEBUG
                            LIB_BOOST_DATA_TIME_RELEASE
                            LIB_BOOST_THREAD_DEBUG
                            LIB_BOOST_THREAD_RELEASE
                            LIB_BOOST_FILESYSTEM_DEBUG
                            LIB_BOOST_FILESYSTEM_RELEASE
                            LIB_BOOST_PROGRAM_OPTIONS_DEBUG
                            LIB_BOOST_PROGRAM_OPTIONS_RELEASE
                            LIB_BOOST_CHRONO_DEBUG
                            LIB_BOOST_CHRONO_RELEASE
                            LIB_BOOST_REGEX_DEBUG
                            LIB_BOOST_REGEX_RELEASE)

        IF( CMAKE_BUILD_TYPE )

			SET( BOOST_LIBRARIES
				debug ${LIB_BOOST_SYSTEM_DEBUG}
				debug ${LIB_BOOST_DATA_TIME_DEBUG}
				debug ${LIB_BOOST_THREAD_DEBUG}
				debug ${LIB_BOOST_FILESYSTEM_DEBUG}
				debug ${LIB_BOOST_PROGRAM_OPTIONS_DEBUG}
				debug ${LIB_BOOST_CHRONO_DEBUG}
				debug ${LIB_BOOST_REGEX_DEBUG}
				optimized ${LIB_BOOST_SYSTEM_RELEASE}
				optimized ${LIB_BOOST_DATA_TIME_RELEASE}
				optimized ${LIB_BOOST_THREAD_RELEASE}
				optimized ${LIB_BOOST_FILESYSTEM_RELEASE}
				optimized ${LIB_BOOST_PROGRAM_OPTIONS_RELEASE}
				optimized ${LIB_BOOST_CHRONO_RELEASE}
				optimized ${LIB_BOOST_REGEX_RELEASE}
			) 
		  
        ELSE()
			SET( BOOST_LIBRARIES
				${LIB_BOOST_SYSTEM_RELEASE}
				${LIB_BOOST_DATA_TIME_RELEASE}
				${LIB_BOOST_THREAD_RELEASE}
				${LIB_BOOST_FILESYSTEM_RELEASE}
				${LIB_BOOST_PROGRAM_OPTIONS_RELEASE}
				${LIB_BOOST_CHRONO_RELEASE}
				${LIB_BOOST_REGEX_RELEASE}
			)
        ENDIF()

    endif()