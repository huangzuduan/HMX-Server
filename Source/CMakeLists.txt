# The name of our project is "HELLO". CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required (VERSION 2.8)
project (HMX_Server_Cmake)

# build in Release-mode by default if not explicitly set
if( NOT CMAKE_BUILD_TYPE )
    set(CMAKE_BUILD_TYPE "Release")
endif()

IF(MSVC)

   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zm500")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4819")
   set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /wd4996")
   #set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
   
ELSEIF(UNIX)
    IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_DEBUG")
    ELSE()
      SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DNDEBUG")
    ENDIF()
ENDIF()

include(cmake/options.cmake)
include(cmake/FindPCHSupport.cmake)
include(cmake/cxx_flag_overrides.cmake)

include(cmake/boost.cmake)
include(cmake/protobuf.cmake)
include(cmake/libxml.cmake)
include(cmake/mysql.cmake)
include(cmake/curl.cmake)
include(cmake/iconv.cmake)
include(cmake/openssl.cmake)

 foreach(flag_var
         CMAKE_CXX_FLAGS CMAKE_CXX_FLAGS_DEBUG CMAKE_CXX_FLAGS_RELEASE
         CMAKE_CXX_FLAGS_MINSIZEREL CMAKE_CXX_FLAGS_RELWITHDEBINFO)
    if(${flag_var} MATCHES "/MD")
       string(REGEX REPLACE "/MD" "/MT" ${flag_var} "${${flag_var}}")
    endif(${flag_var} MATCHES "/MD")
   
   # # if(${flag_var} MATCHES "/Zi")
      # # string(REGEX REPLACE "/Zi" "/C7" ${flag_var} "${${flag_var}}")
   # # endif(${flag_var} MATCHES "/Zi")
   
 endforeach(flag_var)

# turn off PCH totally if enabled (hidden setting, mainly for devs)
if( NOPCH )
  set(USE_COREPCH 0)
endif()

#find_package(PCHSupport)

# Find Lib path:


IF(WIN32)
    IF(MSVC)
        # /MD and /MDd are the standard values - if someone wants to use
        # others, the libnames have to change here too
        # use also ssl and ssleay32 in debug as fallback for openssl < 0.9.8b
        # TODO: handle /MT and static lib
        # In Visual C++ naming convention each of these four kinds of Windows libraries has it's standard suffix:
        #   * MD for dynamic-release
        #   * MDd for dynamic-debug
        #   * MT for static-release
        #   * MTd for static-debug

        # Implementation details:
        # We are using the libraries located in the VC subdir instead of the parent directory eventhough :
        # libeay32MD.lib is identical to ../libeay32.lib, and
        # ssleay32MD.lib is identical to ../ssleay32.lib
		
		
		###### Include 
		
		FIND_PATH(COMMON_INCLUDE_DIR
          NAMES
            SrvEngine.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/Common
        )
		MARK_AS_ADVANCED(COMMON_INCLUDE_DIR)
		
		FIND_PATH(PROTOCOL_INCLUDE_DIR
          NAMES
            data.pb.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/Protocol
        )
		MARK_AS_ADVANCED(PROTOCOL_INCLUDE_DIR)
		
		FIND_PATH(XML_INCLUDE_DIR
          NAMES
            Poco/XML/XML.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/XML/include
        )
		MARK_AS_ADVANCED(XML_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_XML_DEBUG
          NAMES
            PocoXMLmtd
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/XML/lib
        )
		MARK_AS_ADVANCED(LIB_XML_DEBUG)
		
		FIND_LIBRARY(LIB_XML_RELEASE
          NAMES
            PocoXMLmt
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/XML/lib
        )
		MARK_AS_ADVANCED(LIB_XML_RELEASE)
		
		FIND_PATH(UTIL_INCLUDE_DIR
          NAMES
            Poco/Util/Option.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Util/include
        )
		MARK_AS_ADVANCED(UTIL_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_UTIL_DEBUG
          NAMES
            PocoUtilmtd
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Util/lib
        )
		MARK_AS_ADVANCED(LIB_UTIL_DEBUG)
		
		FIND_LIBRARY(LIB_UTIL_RELEASE
          NAMES
            PocoUtilmt
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Util/lib
        )
		MARK_AS_ADVANCED(LIB_UTIL_RELEASE)
		
		FIND_PATH(FOUNDATION_INCLUDE_DIR
          NAMES
            Poco/Any.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Foundation/include
        )
		MARK_AS_ADVANCED(FOUNDATION_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_FOUNDATION_DEBUG
          NAMES
            PocoFoundationmtd
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Foundation/lib
        )
		MARK_AS_ADVANCED(LIB_FOUNDATION_DEBUG)
		
		FIND_LIBRARY(LIB_FOUNDATION_RELEASE
          NAMES
            PocoFoundationmt
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Foundation/lib
        )
		MARK_AS_ADVANCED(LIB_FOUNDATION_RELEASE)
		
		FIND_PATH(NET_INCLUDE_DIR
          NAMES
            Poco/Net/HTTPServer.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Net/include
        )
		MARK_AS_ADVANCED(NET_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_NET_DEBUG
          NAMES
            PocoNetmtd
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Net/lib
        )
		MARK_AS_ADVANCED(LIB_NET_DEBUG)
		
		FIND_LIBRARY(LIB_NET_RELEASE
          NAMES
            PocoNetmt
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/Net/lib
        )
		MARK_AS_ADVANCED(LIB_NET_RELEASE)
		
		FIND_PATH(JSON_INCLUDE_DIR
          NAMES
            Poco/JSON/JSON.h
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/JSON/include
        )
		MARK_AS_ADVANCED(JSON_INCLUDE_DIR)
		
		FIND_LIBRARY(LIB_JSON_DEBUG
          NAMES
            PocoJSONmtd
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/JSON/lib
        )
		MARK_AS_ADVANCED(LIB_JSON_DEBUG)
		
		FIND_LIBRARY(LIB_JSON_RELEASE
          NAMES
            PocoJSONmt
          PATHS
            ${HMX_Server_Cmake_SOURCE_DIR}/dependence/JSON/lib
        )
		MARK_AS_ADVANCED(LIB_JSON_RELEASE)

        IF( CMAKE_BUILD_TYPE )
		  
		  SET ( THIRD_LIBRARIES
			debug ${LIB_FOUNDATION_DEBUG}
			debug ${LIB_NET_DEBUG}
			debug ${LIB_UTIL_DEBUG}
			debug ${LIB_XML_DEBUG}
			debug ${LIB_JSON_DEBUG}
			optimized ${LIB_FOUNDATION_RELEASE}	
			optimized ${LIB_NET_RELEASE}
			optimized ${LIB_UTIL_RELEASE}
			optimized ${LIB_XML_RELEASE}
			optimized ${LIB_JSON_RELEASE}
		  )
		  
        ELSE()
		  
		  SET ( THIRD_LIBRARIES
			optimized ${LIB_FOUNDATION_RELEASE}
			optimized ${LIB_NET_RELEASE}
			optimized ${LIB_UTIL_RELEASE}
			optimized ${LIB_XML_RELEASE}
			optimized ${LIB_JSON_RELEASE}
		  )
		  
        ENDIF()

    ENDIF(MSVC)
ENDIF(WIN32)


# Recurse into the "Hello" and "Demo" subdirectories. This does not actually
# cause another cmake executable to run. The same process will walk through
# the project's entire directory structure.

#add_subdirectory(Include)
add_subdirectory(Common)
add_subdirectory(LibNetSocket)
#add_subdirectory(LibNetMysql)
add_subdirectory(Protocol)
add_subdirectory(WorldServer)
#add_subdirectory(LogServer)
add_subdirectory(DBServer)
add_subdirectory(GameServer)
add_subdirectory(LoginServer)
add_subdirectory(GatewayServer)
#add_subdirectory(Client)
#add_subdirectory(PayCenterServer)
#add_subdirectory(HelpTools)

