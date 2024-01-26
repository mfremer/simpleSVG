#include "SVGPath.hpp"

#include <sstream>

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