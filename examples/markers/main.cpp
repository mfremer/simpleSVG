/**
 * @file main.cpp
 * @author mfremer
 * @date 2024-02-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <simpleSVG.hpp>

#include <cstdlib>

using namespace simpleSVG;

int main() {
    SVGFile file(500, 500, SVGUnit::MM);
    ColorRGB black{0, 0, 0};

    // define arrowhead marker
    SVGPathStyle arrow_style(black, 1.);
    SVGPath arrow_path(arrow_style);
    arrow_path << move_to(-3, -3, false)
               << line_to(0, 0, false)
               << line_to(-3, 3, false);
    SVGMarker arrow("arrow", arrow_path);
    file.add_marker(arrow); // add to file to be able to reference it

    // define triangle marker
    SVGPathStyle triangle_style(black, SVGFillRule::EVEN_ODD);
    SVGPath triangle_path(triangle_style);
    triangle_path << move_to(2, 0, false)
                  << line_to(-1, 1.732, false)
                  << line_to(-1, -1.732, false)
                  << close_path();
    SVGMarker triangle("triangle", triangle_path);
    file.add_marker(triangle); // add to file to be able to reference it

    // create path and add markers
    SVGPathStyle path_style({255, 0, 0}, 0.5);
    path_style.add_marker_start("arrow");
    path_style.add_marker_end("triangle");
    SVGPath path(path_style);
    path << move_to(100, 100, false)
         << line_to(400, 100, false);

    file << path;
    file.write_file("./markers.svg");

    return EXIT_SUCCESS;
}