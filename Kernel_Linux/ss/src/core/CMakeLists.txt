#CMakeLists for src directory.

set(UTIL_SOURCE ${UTIL_PATH}/Util.cpp)

set(CORE_BASE_SOURCES
  base/byte_buffer_dynamic.cc
  base/bound_ring_queue.cc
  base/boundless_ring_queue.cc
  base/common.cc
  base/logging.cc
  base/thread.cc)

set(CORE_PACKET_SOURCES
  packet/packet.cc)

set(CORE_TINYXML_SOURCES
  tinyxml/tinystr.cpp
  tinyxml/tinyxml.cpp
  tinyxml/tinyxmlerror.cpp
  tinyxml/tinyxmlparser.cpp)

set(CORE_TOOLS_SOURCES
  tools/EventEngine.cpp
  tools/LogTool.cc
  tools/MemTextFile.cpp
  tools/ScriptCSV.cpp
  tools/ScriptLoader.cpp
  tools/TimerAxis.cpp)

set(CORE_SOURCES
  acceptor.cc
  channel.cc
  client_thread_pool.cc
  connector.cc
  core_config.cc
  epoller.cc
  event_loop.cc
  event_loop_thread_group.cc
  inet_address.cc
  log_loop.cc
  logic_log.cc
  logic_loop.cc
  loop_thread.cc
  network_thread_pool.cc
  schedule_loop.cc
  server_core.cc
  tcp_socket.cc
  tcp_client.cc
  tcp_connection.cc
  tcp_server.cc
  timing_base.cc
  timing_group.cc
  timing_wheel.cc)

#Shared library
add_library(core SHARED
  ${CORE_BASE_SOURCES} ${CORE_PACKET_SOURCES} ${CORE_TINYXML_SOURCES}  ${CORE_SOURCES} ${CORE_TOOLS_SOURCES} ${UTIL_SOURCE}
  )

#Static library
#add_library(core_static STATIC
#  ${CORE_BASE_SOURCES} ${CORE_PACKET_SOURCES} ${CORE_TINYXML_SOURCES} ${CORE_SOURCES} ${CORE_TOOLS_SOURCES}
#  )

#Ensure build both share and static library using same name.
#set_target_properties(core_static PROPERTIES OUTPUT_NAME "core")
set_target_properties(core PROPERTIES CLEAN_DIRECT_OUTPUT 1)
#set_target_properties(core_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)

#Add subdirectory.
#add_subdirectory(test)

