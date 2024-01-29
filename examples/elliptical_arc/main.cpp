/**
 * @file main.cpp
 * @author mfremer
 * @date 2024-01-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <simpleSVG.hpp>

#include <cstdlib>

using namespace simpleSVG;

int main() {
    SVGFile file(200, 200, SVGUnit::MM, false);
    SVGPathStyle style_red({255, 0, 0}, 0.5);
    SVGPathStyle style_green({0, 255, 0}, 0.5);
    SVGPathStyle style_blue({0, 0, 255}, 0.5);
    SVGPathStyle style_magenta({255, 0, 255}, 0.5);
    
    SVGPath path_red(style_red);
    SVGPath path_green(style_green);
    SVGPath path_blue(style_blue);
    SVGPath path_magenta(style_magenta);

    constexpr double init_x = 60;
    constexpr double init_y = 100;
    constexpr double rx = 60;
    constexpr double ry = 40;
    constexpr double angle_deg = 10;
    constexpr double target_x = 140;
    constexpr double target_y = 100;

    path_red << move_to(init_x, init_y, false)
        << elliptical_arc_to(rx, ry, angle_deg, true, false,
                                target_x, target_y, false);
    path_green << move_to(init_x, init_y, false)
        << elliptical_arc_to(rx, ry, angle_deg, true, true,
                                target_x, target_y, false);
    path_blue << move_to(init_x, init_y, false)
        << elliptical_arc_to(rx, ry, angle_deg, false, true,
                                target_x, target_y, false);
    path_magenta << move_to(init_x, init_y, false)
        << elliptical_arc_to(rx, ry, angle_deg, false, false,
                                target_x, target_y, false);

    file << path_red;
    file << path_green;
    file << path_blue;
    file << path_magenta;

    file.write_file("./elliptical_arc.svg");

    return EXIT_SUCCESS;
}