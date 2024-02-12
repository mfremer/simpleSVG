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
#include <iostream>
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
std::string maybecolor_to_string(const MaybeColorRGB& color) {
    if (!color.has_value()) { return "none"; }
    return color_to_string(color.value());
}
std::string linecap_to_string(const SVGLineCap& linecap) {
    switch (linecap) {
        case SVGLineCap::ROUND:
            return "round";
        case SVGLineCap::BUTT:
            return "butt";
        case SVGLineCap::SQUARE:
            return "square";
        default:
            std::cerr << "[WARNING]\tlinecap_to_string(): unhandled case in switch statement";
    }
    return "none";
}
std::string linejoin_to_string(const SVGLineJoin& linejoin) {
    switch (linejoin) {
        case SVGLineJoin::ROUND:
            return "round";
        case SVGLineJoin::BEVEL:
            return "bevel";
        case SVGLineJoin::MITER:
            return "miter";
        default:
            std::cerr << "[WARNING]\tlinejoin_to_string(): unhandled case in switch statement";
    }
    return "none";
}
std::string dasharray_to_string(const std::string& dasharray) {
    if (dasharray.empty()) { return "none"; }
    return dasharray;
}
std::string marker_id_to_string(const std::string& marker_id) {
    if (marker_id.empty()) { return "none"; }
    return "url(#" + marker_id + ")";
}
std::string fillrule_to_string(const SVGFillRule& fillrule) {
    switch (fillrule) {
        case SVGFillRule::EVEN_ODD:
            return "evenodd";
        case SVGFillRule::NON_ZERO:
            return "nonzero";
        default:
            std::cerr << "[WARNING]\tfillrule_to_string(): unhandled case in switch statement";
    }
    return "none";
}

void SVGPathStyle::add_marker_start(const std::string& marker_id) {
    m_marker_start_id = marker_id;
}
void SVGPathStyle::add_marker_end(const std::string& marker_id) {
    m_marker_end_id = marker_id;
}

std::string SVGPathStyle::to_string() const {    
    std::stringstream ss;
    ss << "style=\""
       << "stroke:" << maybecolor_to_string(m_stroke_color) << ';'
       << "stroke-width:" << m_stroke_width << ";"
       << "stroke-linecap:" << linecap_to_string(m_stroke_linecap) << ";"
       << "stroke-linejoin:" << linejoin_to_string(m_stroke_linejoin) << ";"
       << "stroke-dasharray:" << dasharray_to_string(m_stroke_dasharray) << ";"
       << "fill:" << maybecolor_to_string(m_fill_color) << ";"
       << "fill-rule:" << fillrule_to_string(m_fill_rule) << ";"
       << "marker-start:" << marker_id_to_string(m_marker_start_id) << ";"
       << "marker-end:" << marker_id_to_string(m_marker_end_id)
       << "\"";
    return ss.str();
}

}