cmake_minimum_required(VERSION 3.2)

project(ip_filter VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file("${PROJECT_SOURCE_DIR}/version.h.in" "${PROJECT_BINARY_DIR}/version.h")
configure_file("${PROJECT_SOURCE_DIR}/ip_filter.tsv" "${PROJECT_BINARY_DIR}/ip_filter.tsv" COPYONLY)

add_executable(ip_filter main.cpp ip_filter.cpp)
add_executable(test_main test_main.cpp ip_filter.cpp)


set_target_properties(ip_filter test_main PROPERTIES
  CXX_STANDARD 14
  CXX_STANDARD_REQUIRED ON
  COMPILE_OPTIONS -Wpedantic -Wall -Wextra
)


set_target_properties(test_main PROPERTIES
  COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
  INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
)


target_link_libraries(test_main ${Boost_LIBRARIES})

target_include_directories(ip_filter PUBLIC "${PROJECT_BINARY_DIR}")
target_include_directories(test_main PUBLIC "${PROJECT_BINARY_DIR}")


install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT kolobrod2002@yandex.ru)

include (CPack)

enable_testing()

add_test(split test_main)
add_test(stream_reader test_main)
