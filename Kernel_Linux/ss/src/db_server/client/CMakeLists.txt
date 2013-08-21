#Set include paths.
include_directories(
  "${PROJECT_SOURCE_DIR}/src/include"
  "${PROJECT_SOURCE_DIR}/src/common"
  "${PROJECT_SOURCE_DIR}/db_server/client"
  )

set(DB_CLIENT_SOURCES
  DBClient.cpp
  DBClientMgr.cpp
  DBClientTempSink.cpp
  Header.cpp
  Sorter.cpp)

if(COMMAND cmake_policy)
 cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#Shared library
add_library(db_client SHARED ${DB_CLIENT_SOURCES})

