/**
 * @file SVGPathCommand.cpp
 * @author mfremer
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "SVGPathCommand.hpp"

#include <iostream>
#include <sstream>

namespace simpleSVG {

size_t SVGPathCommand::num_args() const {
    switch (m_cmd_code) {
        case 'M':
        case 'L':
            return 2;
            break;
        case 'A':
            return 7;
        case 'Z':
            return 0;
            break;
        default:
            std::cerr << "[WARNING]\tnum_args(): unhandled case in switch statement\n";
    }
    return path_cmd_max_args;
}

std::string SVGPathCommand::to_string() const {
    std::stringstream ss;
    ss << static_cast<char>(m_is_relative ? tolower(m_cmd_code) : m_cmd_code) << ' ';
    for (size_t i = 0; i < num_args(); ++i) {
        ss << m_args[i] << ' ';
    }
    return ss.str();
}

SVGPathCommand move_to(double x, double y, bool is_relative) {
    return SVGPathCommand('M', is_relative, {x, y});
}

SVGPathCommand line_to(double x, double y, bool is_relative) {
    return SVGPathCommand('L', is_relative, {x, y});
}

SVGPathCommand close_path() {
    return SVGPathCommand('Z', false, {});
}

SVGPathCommand elliptical_arc_to(
    double rx, double ry, double angle_deg,
    bool large_arc_flag, bool clockwise_flag,
    double x, double y, bool is_relative)
{
    return SVGPathCommand('A', is_relative,
        {rx, ry, angle_deg,
         static_cast<double>(large_arc_flag), static_cast<double>(clockwise_flag),
         x, y});
}

SVGPathCommand circular_arc_to(
    double r, bool large_arc_flag, bool clockwise_flag,
    double x, double y, bool is_relative)
{
    return SVGPathCommand('A', is_relative,
        {r, r, 0.,
         static_cast<double>(large_arc_flag), static_cast<double>(clockwise_flag),
         x, y});
}

}