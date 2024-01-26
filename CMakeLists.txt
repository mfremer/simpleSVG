cmake_minimum_required(VERSION 3.10)

project(simpleSVG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(ssvg
    src/main.cpp
    src/SVGFile.cpp
    src/SVGPath.cpp
    src/SVGPathCommand.cpp
    src/SVGPathStyle.cpp
)

target_include_directories(ssvg PRIVATE
    ${PROJECT_SOURCE_DIR}/src
)