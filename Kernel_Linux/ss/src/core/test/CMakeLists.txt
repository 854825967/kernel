set(TEST_DIR ${PROJECT_SOURCE_DIR}/src/test)

set(TEST_SHARED_PTR_SOURCES test_shared_ptr.cc)

set(TEST_FUNCTION_SOURCES test_function.cc)

set(TEST_BOUND_RING_QUEUE_SOURCES test_bound_ring_queue.cc)

set(TEST_BOUNDLESS_RING_QUEUE_SOURCES test_boundless_ring_queue.cc)

set(TEST_BOUNDLESS_ENTITY_RING_QUEUE_SOURCES test_boundless_entity_ring_queue.cc)

set(TEST_BOUND_ENTITY_RING_QUEUE_SOURCES test_bound_entity_ring_queue.cc)

set(TEST_TIMING_WHEEL_SIGNAL_SOURCES test_timing_wheel_signal.cc)

set(TEST_SERVER_SOURCES test_server.cc)

set(TEST_CLIENT_SOURCES test_client.cc)

if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)

FILE(MAKE_DIRECTORY ${EXECUTABLE_OUTPUT_PATH}/test)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin/test)

#Build test_shared_ptr
add_executable(test_shared_ptr ${TEST_SHARED_PTR_SOURCES})
target_link_libraries(test_shared_ptr pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

#Build test_function
add_executable(test_function ${TEST_FUNCTION_SOURCES})
target_link_libraries(test_function pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

#Build test_bound_ring_queue
add_executable(test_bound_ring_queue ${TEST_BOUND_RING_QUEUE_SOURCES})
target_link_libraries(test_bound_ring_queue pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

#Build test_boundless_ring_queue
add_executable(test_boundless_ring_queue ${TEST_BOUNDLESS_RING_QUEUE_SOURCES})
target_link_libraries(test_boundless_ring_queue pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

#Build test_boundless_entity_ring_queue
add_executable(test_boundless_entity_ring_queue ${TEST_BOUNDLESS_ENTITY_RING_QUEUE_SOURCES})
target_link_libraries(test_boundless_entity_ring_queue pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

#Build test_bound_entity_ring_queue
add_executable(test_bound_entity_ring_queue ${TEST_BOUND_ENTITY_RING_QUEUE_SOURCES})
target_link_libraries(test_bound_entity_ring_queue pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

#Build test_timing_wheel_signal
add_executable(test_timing_wheel_signal ${TEST_TIMING_WHEEL_SIGNAL_SOURCES})
target_link_libraries(test_timing_wheel_signal pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

#Build test_server
add_executable(test_server ${TEST_SERVER_SOURCES})
target_link_libraries(test_server pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

#Build test_client
add_executable(test_client ${TEST_CLIENT_SOURCES})
target_link_libraries(test_client pthread rt ${PROJECT_BINARY_DIR}/lib/libcore.so)

