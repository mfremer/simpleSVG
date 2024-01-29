cmake_minimum_required(VERSION 3.10)

project(simpleSVG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic)

add_library(simpleSVG
    src/SVGFile.cpp
    src/SVGPath.cpp
    src/SVGPathCommand.cpp
    src/SVGPathStyle.cpp
)

target_include_directories(simpleSVG PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)