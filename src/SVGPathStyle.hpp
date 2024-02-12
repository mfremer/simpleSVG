/**
 * @file SVGPathStyle.hpp
 * @author mfremer
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include <optional>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

#include <cstdint>

// https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Fills_and_Strokes

/* Important style attributes
 - fill
 - stroke
 - stroke-width
 - stroke-linecap
 - stroke-linejoin
 - stroke-opacity
 - stroke-opacity
 - stroke-dasharray
*/

namespace simpleSVG {

typedef std::tuple<uint8_t, uint8_t, uint8_t> ColorRGB;
typedef std::optional<ColorRGB> MaybeColorRGB;

enum class SVGLineCap {
    // DEFAULT,
    ROUND,
    BUTT,
    SQUARE
};
enum class SVGLineJoin {
    // DEFAULT,
    ROUND,
    BEVEL,
    MITER
};
enum class SVGFillRule {
    // DEFAULT,
    EVEN_ODD,
    NON_ZERO
};

namespace {
    constexpr SVGLineCap  linecap_default  = SVGLineCap::ROUND;
    constexpr SVGLineJoin linejoin_default = SVGLineJoin::ROUND;
    constexpr SVGFillRule fillrule_default = SVGFillRule::EVEN_ODD;
}

class SVGPathStyle {
public:
    SVGPathStyle(
        const MaybeColorRGB& stroke_color, double stroke_width,
        const SVGLineCap& stroke_linecap, const SVGLineJoin& stroke_linejoin,
        const std::string& stroke_dasharray,
        const MaybeColorRGB& fill_color, const SVGFillRule& fill_rule,
        const std::string& marker_start_id, const std::string& marker_end_id
    ) : m_stroke_color{stroke_color}, m_stroke_width{stroke_width},
        m_stroke_linecap{stroke_linecap}, m_stroke_linejoin{stroke_linejoin},
        m_stroke_dasharray{stroke_dasharray},
        m_fill_color{fill_color}, m_fill_rule{fill_rule},
        m_marker_start_id(marker_start_id), m_marker_end_id(marker_end_id) {}
    
    SVGPathStyle(
        const ColorRGB& stroke_color, double stroke_width
    ) : SVGPathStyle(stroke_color, stroke_width,
                     linecap_default, linejoin_default,
                     {}, {}, fillrule_default, {}, {}) {}
    
    SVGPathStyle(
        const ColorRGB& stroke_color, double stroke_width,
        const SVGLineCap& stroke_linecap, const SVGLineJoin& stroke_linejoin
    ) : SVGPathStyle(stroke_color, stroke_width,
                     stroke_linecap, stroke_linejoin,
                     {}, {}, fillrule_default, {}, {}) {}
    
    SVGPathStyle(
        const ColorRGB& fill_color, const SVGFillRule& fill_rule
    ) : SVGPathStyle({}, 0.,
                     linecap_default, linejoin_default,
                     {}, fill_color, fill_rule, {}, {}) {}

    SVGPathStyle(
        const MaybeColorRGB& stroke_color, double stroke_width,
        const MaybeColorRGB& fill_color, const SVGFillRule& fill_rule
    ) : SVGPathStyle(stroke_color, stroke_width,
                     linecap_default, linejoin_default,
                     {}, fill_color, fill_rule, {}, {}) {}

    void add_marker_start(const std::string& marker_id);
    void add_marker_end(const std::string& marker_id);

protected:
    std::string to_string() const;

private:
    MaybeColorRGB m_stroke_color;
    double m_stroke_width;
    SVGLineCap m_stroke_linecap;
    SVGLineJoin m_stroke_linejoin;
    std::string m_stroke_dasharray;
    MaybeColorRGB m_fill_color;
    SVGFillRule m_fill_rule;
    std::string m_marker_start_id;
    std::string m_marker_end_id;

    friend class SVGPath;
};

}