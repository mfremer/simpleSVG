cmake_minimum_required(VERSION 3.10)

project(examples)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(basic basic/main.cpp)
target_link_libraries(basic PUBLIC simpleSVG)

add_executable(elliptical_arc elliptical_arc/main.cpp)
target_link_libraries(elliptical_arc PUBLIC simpleSVG)

add_executable(holed_polygon holed_polygon/main.cpp)
target_link_libraries(holed_polygon PUBLIC simpleSVG)

add_executable(markers markers/main.cpp)
target_link_libraries(markers PUBLIC simpleSVG)