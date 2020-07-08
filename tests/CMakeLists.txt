cmake_minimum_required(VERSION 3.2)

find_package(OpenSSL REQUIRED)

set(PROJECT_TEST ${PROJECT_NAME}_test)

add_executable(${PROJECT_TEST} tests.cpp ../ip_filter.cpp)


set_target_properties(${PROJECT_TEST} PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)

# set_target_properties(${PROJECT_TEST} PROPERTIES
#   APPEND PROPERTY COMPILE_DEFINITIONS PROJECT_SOURCE_DIR="${PROJECT_SOURCE_DIR}"
# )


target_include_directories(${PROJECT_TEST} PUBLIC
  ${OPENSSL_INCLUDE_DIR}
)

target_include_directories(${PROJECT_TEST} PUBLIC
    ${PROJECT_SOURCE_DIR}
    ${PROJECT_BINARY_DIR}
)

target_link_libraries(${PROJECT_TEST}
    OpenSSL::SSL
)


# enable_testing()
add_test(main_case ${PROJECT_TEST})
