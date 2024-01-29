#include "SVGPathStyle.hpp"

#include <iomanip>
#include <sstream>

namespace simpleSVG {

std::string color_to_string(const ColorRGB& color) {
    auto [r, g, b] = color;
    std::stringstream ss;
    ss << "#" << std::hex << std::setfill('0')
       << std::setw(2) << static_cast<int>(r)
       << std::setw(2) << static_cast<int>(g)
       << std::setw(2) << static_cast<int>(b);
    return ss.str();
}

std::string SVGPathStyle::to_string() const {
    std::stringstream ss;
    ss << "style=\""
       << "fill:none;"
       << "stroke:" << color_to_string(m_stroke) << ';'
       << "stroke-width:" << m_stroke_width;
    if (!m_stroke_dasharray.empty()) {
        ss << ";stroke-dasharray:" << m_stroke_dasharray;
    }
    ss << "\"";
    return ss.str();
}

}