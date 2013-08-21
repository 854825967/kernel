#Set include paths.
include_directories(
  "${PROJECT_SOURCE_DIR}/src/include"
  "${PROJECT_SOURCE_DIR}/src/common"
  "${PROJECT_SOURCE_DIR}/src/util"
  "${PROJECT_SOURCE_DIR}/db_server/DBServer"
  )

set(UTIL_SOURCE ${UTIL_PATH}/Util.cpp)

set(DB_SERVER_SOURCES
  DBServer.cc  Header.cc  ServerClientSink.cc  ServerConfigure.cc  ServerService.cc  SocketService.cc)

if(COMMAND cmake_policy)
 cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

FILE(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/db_server)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/db_server)

add_executable(db_server ${DB_SERVER_SOURCES} ${UTIL_SOURCE})
target_link_libraries(db_server pthread rt dl mysqlpp ${PROJECT_BINARY_DIR}/lib/libcore.so)
