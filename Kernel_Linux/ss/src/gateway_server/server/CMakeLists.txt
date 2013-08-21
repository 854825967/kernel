#Set include paths.
include_directories(
  "${PROJECT_SOURCE_DIR}/src/include"
  "${PROJECT_SOURCE_DIR}/src/common"
  "${PROJECT_SOURCE_DIR}/src/gateway_server/server"
  )

set(GATEWAY_SERVER_SOURCES
  ClientIDGenerator.cpp
  ConnectSinkMgr.cpp
  ConnectStateSink.cpp
  DBServerConfigMgr.cpp
  GameClientMgr.cpp
  GatewayServer.cpp
  GateWayServiceMgr.cpp
  Header.cpp
  MemTextFile.cpp
  RunStateSink.cpp
  ServerConfigure.cpp
  UserClientSinkBase.cpp
  GameClientConn.cpp
  VestibuleLoginSink.cpp
  VestibuleRunSink.cpp)

if(COMMAND cmake_policy)
 cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

FILE(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/gateway_server)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/gateway_server)

add_executable(gateway_server ${GATEWAY_SERVER_SOURCES})
target_link_libraries(gateway_server pthread rt dl ${PROJECT_BINARY_DIR}/lib/libcore.so)

