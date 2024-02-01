/**
 * @file main.cpp
 * @author mfremer
 * @date 2024-02-01
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <simpleSVG.hpp>

#include <cstdlib>

using namespace simpleSVG;

int main() {
    SVGFile file(200, 200, SVGUnit::MM);
    SVGPathStyle black_red({0, 0, 0}, 0.5, {255, 0, 0});
    SVGPath poly_hole(black_red);

    // exterior polygon, clockwise 
    poly_hole << move_to(  50,   50, false)
              << line_to( 100,    0, true)
              << line_to(   0,  100, true)
              << line_to(-100,    0, true)
              << line_to(   0, -100, true);
    // internal polygon, counterclockwise
    poly_hole << move_to(100,  75, false)
              << line_to(-25,  25, true)
              << line_to( 25,  25, true)
              << line_to( 25, -25, true)
              << line_to(-25, -25, true);

    file << poly_hole;

    file.write_file("./hole_polygon.svg");

    return EXIT_SUCCESS;
}