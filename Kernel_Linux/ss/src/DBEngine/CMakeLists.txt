#Set include paths.
include_directories(
  "${PROJECT_SOURCE_DIR}/src/include"
  "${PROJECT_SOURCE_DIR}/src/common"
  "${PROJECT_SOURCE_DIR}/src/core"
  "/usr/include/mysql"
  "/usr/local/include/mysql++"
  "${PROJECT_SOURCE_DIR}/DBEngine"
  )

set(DBENGINE_SOURCES
  AsynObject.cc  AsynObjectList.cc  DBADO.cc  DBEngine.cc  Header.cc  DBMemTextFile.cc  RequestConfig.cc)

if(COMMAND cmake_policy)
 cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

#Shared library
add_library(DBEngine SHARED ${DBENGINE_SOURCES})

