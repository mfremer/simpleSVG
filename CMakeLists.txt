cmake_minimum_required(VERSION 3.10)

project(simpleSVG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic)

option(simpleSVG_compile_examples "Compile library examples" ON)

if (simpleSVG_compile_examples)
    add_subdirectory(examples)
endif()

add_library(simpleSVG
    ${PROJECT_SOURCE_DIR}/src/SVGFile.cpp
    ${PROJECT_SOURCE_DIR}/src/SVGPath.cpp
    ${PROJECT_SOURCE_DIR}/src/SVGPathCommand.cpp
    ${PROJECT_SOURCE_DIR}/src/SVGPathStyle.cpp
    ${PROJECT_SOURCE_DIR}/src/SVGMarker.cpp
)

target_include_directories(simpleSVG PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)