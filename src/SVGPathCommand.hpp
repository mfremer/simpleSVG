#pragma once

#include <array>
#include <string>

#include <cstdlib>

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

SVGPathCommand move_to(double x, double y, bool is_relative);
SVGPathCommand line_to(double x, double y, bool is_relative);
// SVGPathCommand cubic_bezier_curve();
// SVGPathCommand quadratic_bezier_curve();
// SVGPathCommand elliptical_arc_curve();
SVGPathCommand close_path();

};