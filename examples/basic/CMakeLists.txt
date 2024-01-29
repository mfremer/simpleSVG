cmake_minimum_required(VERSION 3.10)

project(basic)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(basic main.cpp)

target_link_libraries(basic PUBLIC simpleSVG)