#Declare project - "ms_server"
project("ms_server")

#Declare version.
cmake_minimum_required(VERSION 0.1)

#Compile options:
# Take almost all warnining;
# Take warnings as errors;
# Optimization level 2;
#add_definitions("-Wall -Wno-deprecated -Werror -O2")
#add_definitions("-g -Wall -Werror -O2")
#add_definitions("-g -Wall -Werror")
#add_definitions("-g -Wall -Wno-unused-variable -Wno-deprecated -Werror -rdynamic -D_CORE_DEBUG -D_LOGIC_DEBUG")
#add_definitions("-g -Wall -Wno-unused-variable -Wno-deprecated -Werror-rdynamic -D_CORE_DEBUG -DPERFORMANCE_TEST -D_CORE_PERFORM_TEST -fno-inline -fno-strict-aliasing")
#add_definitions("-g -Wall -Wno-unused-variable -Wno-deprecated -Werror -rdynamic")

#Default
set(CMAKE_CXX_FLAGS "$ENV{CXXFLAGS} -g -Wall -Wno-unused-variable -Wno-deprecated -Werror -rdynamic -D_CORE_DEBUG -DPERFORMANCE_TEST -D_CORE_PERFORM_TEST -D_ACTIVITY_TEST -fno-inline -fno-strict-aliasing")
#Debug
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -g -Wall -Wno-unused-variable -Wno-deprecated -Werror -rdynamic -D_CORE_DEBUG -DPERFORMANCE_TEST -D_CORE_PERFORM_TEST -fno-inline -fno-strict-aliasing")
#Release
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -g -Wall -O3 -Wno-unused-variable -Wno-deprecated -Werror -rdynamic -DNDEBUG -fno-strict-aliasing")


#Declare project binary/library directory.
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

set(UTIL_PATH ${PROJECT_SOURCE_DIR}/src/util)

message(STATUS "This is SOURCE dir "${PROJECT_SOURCE_DIR})
message(STATUS "This is SOURCE dir "${PROJECT_BINARY_DIR})

#Set include paths.
include_directories(
  "${PROJECT_SOURCE_DIR}"
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/src"
  "${PROJECT_SOURCE_DIR}/centerserver/server"
  )

#Add subdirectory.
add_subdirectory(src/core)
#add_subdirectory(src/core/test)

add_subdirectory(src/DBEngine)
add_subdirectory(src/db_server/DBProxy)
add_subdirectory(src/db_server/DBServer)

add_subdirectory(src/gateway_server/server)

