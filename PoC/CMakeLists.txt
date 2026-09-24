cmake_minimum_required(VERSION 3.16)

project(byte_sort_poc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(byte_sort_lib
    src/byte_sort.cpp
)

target_include_directories(byte_sort_lib PUBLIC src)

add_executable(byte_sort_demo
    src/main.cpp
)

target_link_libraries(byte_sort_demo PRIVATE byte_sort_lib)

add_executable(byte_sort_tests
    tests/byte_sort_tests.cpp
)

target_link_libraries(byte_sort_tests PRIVATE byte_sort_lib)

enable_testing()
add_test(NAME byte_sort_tests COMMAND byte_sort_tests)
