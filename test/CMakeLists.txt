add_executable(test_basic_api test_basic_api.cpp)
target_link_libraries(test_basic_api apollo_client ssl crypto)

add_executable(test_notify test_notify.cpp)
target_link_libraries(test_notify apollo_client ssl crypto)
