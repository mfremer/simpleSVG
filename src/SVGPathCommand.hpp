#pragma once

#include <array>
#include <string>

#define PATH_CMD_MAX_ARGS 7

class SVGPathCommand {
public:
    SVGPathCommand(
        char cmd_code, bool is_relative,
        const std::array<double, PATH_CMD_MAX_ARGS>& args)
    : m_cmd_code(cmd_code), m_is_relative(is_relative), m_args(args) {};

    std::string to_string() const;
private:
    char m_cmd_code;
    bool m_is_relative;

    size_t num_args() const;
    std::array<double, PATH_CMD_MAX_ARGS> m_args;
};

SVGPathCommand move_to(double x, double y, bool is_relative);
SVGPathCommand line_to(double x, double y, bool is_relative);
// SVGPathCommand cubic_bezier_curve();
// SVGPathCommand quadratic_bezier_curve();
// SVGPathCommand elliptical_arc_curve();
SVGPathCommand close_path();