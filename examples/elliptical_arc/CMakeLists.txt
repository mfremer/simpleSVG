cmake_minimum_required(VERSION 3.10)

project(elliptical_arc)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(elliptical_arc main.cpp)

target_link_libraries(elliptical_arc PUBLIC simpleSVG)