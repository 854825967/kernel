#Set include paths.
include_directories(
  "${PROJECT_SOURCE_DIR}/src/include"
  "${PROJECT_SOURCE_DIR}/src/common"
  "${PROJECT_SOURCE_DIR}/src/core"
  "${PROJECT_SOURCE_DIR}/db_server/DBProxy"
  )

set(DBPROXY_SOURCES
  DataProc.cc  DataProcDirect.cc  DataProcSaveDB.cc  DataProcToken.cc  DataProcUser.cc  DBProxy.cc  Header.cc  SaveDBData.cc  UserData.cc  UserToken.cc)

if(COMMAND cmake_policy)
 cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#Shared library
add_library(DBProxy SHARED ${DBPROXY_SOURCES})

