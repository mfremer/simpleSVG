#include "SVGPathCommand.hpp"

#include <sstream>

size_t SVGPathCommand::num_args() const {
    switch (m_cmd_code) {
        case 'M':
        case 'L':
            return 2;
            break;
        case 'Z':
            return 0;
            break;
    }
    return PATH_CMD_MAX_ARGS;
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