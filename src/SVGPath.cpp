/**
 * @file SVGPath.cpp
 * @author mfremer
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "SVGPath.hpp"

#include <sstream>

namespace simpleSVG {

void SVGPath::add_command(const SVGPathCommand& path_command) {
    m_commands.push_back(path_command);
}

std::string SVGPath::to_string() const {
    std::stringstream ss;
    ss << "<path " << m_style.to_string() << " d=\"";
    for (const auto& path_cmd : m_commands) {
        ss << path_cmd.to_string();
    }
    ss << "\"/>";
    return ss.str();
}

SVGPath& operator<<(SVGPath& path, const SVGPathCommand& path_command) {
    path.add_command(path_command);
    return path;
}

SVGPath& operator<<(SVGPath& path, const std::vector<SVGPathCommand>& path_commands) {
    for (const auto& pc : path_commands) { path.add_command(pc); }
    return path;
}

}