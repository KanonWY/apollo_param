find_package(OpenSSL REQUIRED)
find_package(Protobuf REQUIRED)
find_package(srpc REQUIRED CONFIG
        HINTS "/home/kanon/Project/srpc")
if (srpc_FOUND)
    message(STATUS "---> srpc Found")
endif ()

find_package(Workflow REQUIRED CONFIG HINTS "/home/kanon/Project/srpc/workflow")
if (Workflow_FOUND)
    message(STATUS "---> WorkFlow FOUND")
endif ()

include_directories(
        ${OPENSSL_INCLUDE_DIR}
        ${CMAKE_CURRENT_BINARY_DIR}
        ${Protobuf_INCLUDE_DIR}
        ${WORKFLOW_INCLUDE_DIR}
        ${SRPC_INCLUDE_DIR}
)

get_filename_component(Protobuf_LIB_DIR ${Protobuf_LIBRARY} DIRECTORY)
link_directories(${SRPC_LIB_DIR} ${WORKFLOW_LIB_DIR} ${Protobuf_LIB_DIR})
set(SRPC_GEN_PROGRAM ${SRPC_BIN_DIR}/srpc_generator)

protobuf_generate_cpp(PROTO_SRCS PROTO_HDRS message.proto)
add_custom_target(
        TURORIAL_GEN ALL
        COMMAND ${SRPC_GEN_PROGRAM} ${CMAKE_CURRENT_SOURCE_DIR}/message.proto ${CMAKE_CURRENT_SOURCE_DIR}
        COMMENT "srpc generator..."
)


set(SRPC_LIB
        workflow
        pthread
        OpenSSL::SSL
        OpenSSL::Crypto
        protobuf
        z
        srpc)
add_library(apollo_param apollo_param_server.cpp srpc_back_server.cpp ${PROTO_SRCS} ${PROTO_HDRS})
target_link_libraries(apollo_param ${SRPC_LIB} apollo_client)
add_dependencies(apollo_param TURORIAL_GEN)


find_package(Boost REQUIRED CONFIG)
add_executable(test_srpc_service test/test_srpc_service.cpp)
target_link_libraries(test_srpc_service apollo_param ${Boost_LIBRARIES})


add_executable(test_srpc_client test/test_srpc_client.cpp)
target_link_libraries(test_srpc_client apollo_param)