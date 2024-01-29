/**
 * @file SVGPathCommand.hpp
 * @author mfremer
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <array>
#include <string>

#include <cstdlib>

/* See https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/d#path_commands
 * for SVG path commands documentation */

namespace simpleSVG {

constexpr size_t path_cmd_max_args = 7;

class SVGPathCommand {
public:
    SVGPathCommand(
        char cmd_code, bool is_relative,
        const std::array<double, path_cmd_max_args>& args)
    : m_cmd_code(cmd_code), m_is_relative(is_relative), m_args(args) {};

protected:
    std::string to_string() const;

private:
    char m_cmd_code;
    bool m_is_relative;
    size_t num_args() const;
    std::array<double, path_cmd_max_args> m_args;

    friend class SVGPath;
};

/**
 * @brief Moves current point to the specified target without drawing anything.
 * 
 * @param x Target x-coordinate
 * @param y Target y-coordinate
 * @param is_relative Specifies if the coordinates should be interpreted relative to
 * the previous point or not
 * @return SVGPathCommand 
 */
SVGPathCommand move_to(double x, double y, bool is_relative);

/**
 * @brief Draws a line from the current point to the specified target.
 * 
 * @param x Target x-coordinate
 * @param y Target y-coordinate
 * @param is_relative Specifies if the coordinates should be interpreted relative to
 * the previous point or not
 * @return SVGPathCommand 
 */
SVGPathCommand line_to(double x, double y, bool is_relative);

// SVGPathCommand cubic_bezier_curve();
// SVGPathCommand quadratic_bezier_curve();

/**
 * @brief Draws an elliptical arc from the current point to the specified target.
 * The flags allow selecting which one of the four possible arcs will be drawn.
 * 
 * @param rx Radius of the ellipse along the x-axis
 * @param ry Radius of the ellipse along the x-axis
 * @param angle_deg Rotation of the ellipse in degrees relative to the x-axis
 * @param large_arc_flag Specifies if the long (true) or short (false) arc is chosen.
 * @param clockwise_flag Specifies if the clockwise (true) or counter-clockwise (false) arc is chosen.
 * @param x Target x-coordinate
 * @param y Target y-coordinate
 * @param is_relative Specifies if the coordinates should be interpreted relative to
 * the previous point or not
 * @return SVGPathCommand 
 */
SVGPathCommand elliptical_arc_to(
    double rx, double ry, double angle_deg,
    bool large_arc_flag, bool clockwise_flag,
    double x, double y, bool is_relative);

/**
 * @brief Draws a circular arc from the current point to the specified target.
 * The flags allow selecting which one of the four possible arcs will be drawn.
 * 
 * @param r Radius of the circular arc
 * @param large_arc_flag Specifies if the long (true) or short (false) arc is chosen.
 * @param clockwise_flag Specifies if the clockwise (true) or counter-clockwise (false) arc is chosen.
 * @param x Target x-coordinate
 * @param y Target y-coordinate
 * @param is_relative Specifies if the coordinates should be interpreted relative to
 * the previous point or not
 * @return SVGPathCommand 
 */
SVGPathCommand circular_arc_to(
    double r, bool large_arc_flag, bool clockwise_flag,
    double x, double y, bool is_relative);

/**
 * @brief Closes the current path, drawing a line to the initial point.
 * 
 * @return SVGPathCommand 
 */
SVGPathCommand close_path();

}