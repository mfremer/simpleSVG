/**
 * @file SVGPathStyle.cpp
 * @author mfremer
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

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
std::string maybe_color_to_string(const MaybeColorRGB& color) {
    if (!color.has_value()) { return "none"; }
    return color_to_string(color.value());
}
std::string line_cap_to_string(const SVGLineCap& line_cap) {
    switch (line_cap) {
        case SVGLineCap::ROUND:
            return "round";
        case SVGLineCap::BUTT:
            return "butt";
        case SVGLineCap::SQUARE:
            return "square";
    }
    return "none";
}
std::string line_join_to_string(const SVGLineJoin& line_join) {
    switch (line_join) {
        case SVGLineJoin::ROUND:
            return "round";
        case SVGLineJoin::BEVEL:
            return "bevel";
        case SVGLineJoin::MITER:
            return "miter";
    }
    return "none";
}
std::string dash_array_to_string(const std::string& dash_array) {
    if (dash_array.empty()) { return "none"; }
    return dash_array;
}

std::string SVGPathStyle::to_string() const {    
    std::stringstream ss;
    ss << "style=\""
       << "fill:" << maybe_color_to_string(m_fill) << ";"
       << "stroke:" << color_to_string(m_stroke) << ';'
       << "stroke-width:" << m_stroke_width << ";"
       << "stroke-linecap:" << line_cap_to_string(m_stroke_style.line_cap) << ";"
       << "stroke-linejoin:" << line_join_to_string(m_stroke_style.line_join) << ";"
       << "stroke-dasharray:" << dash_array_to_string(m_stroke_style.dash_array)
       << "\"";
    return ss.str();
}

}