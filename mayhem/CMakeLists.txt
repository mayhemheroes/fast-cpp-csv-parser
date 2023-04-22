project(csv-fuzz)

cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 20)

add_compile_options(-fsanitize=fuzzer,address,undefined)
add_link_options(-fsanitize=fuzzer,address,undefined)

add_executable(csv-fuzz fuzz_lib.cpp)
include_directories(..)



