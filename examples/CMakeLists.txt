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

add_executable(groups groups/main.cpp)
target_link_libraries(groups PUBLIC simpleSVG)

add_executable(forbidden_minors forbidden_minors/main.cpp)
target_link_libraries(forbidden_minors PUBLIC simpleSVG)

add_executable(penrose_tiles penrose_tiles/main.cpp)
target_link_libraries(penrose_tiles PUBLIC simpleSVG)