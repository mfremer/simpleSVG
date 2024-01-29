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

enum class SVGLineJoin {
    ROUND, // default
    BEVEL,
    MITER
};
enum class SVGLineCap {
    ROUND, // default
    BUTT,
    SQUARE
};
struct SVGStrokeStyle {
    SVGLineCap line_cap;
    SVGLineJoin line_join;
    std::string dash_array;
};

class SVGPathStyle {
public:
    SVGPathStyle(
        const ColorRGB& stroke_color, double stroke_width)
    : m_stroke(stroke_color), m_stroke_width(stroke_width),
      m_fill({}), m_stroke_style({}) {};
    SVGPathStyle(
        const ColorRGB& stroke_color, double stroke_width, const ColorRGB& fill_color)
    : m_stroke(stroke_color), m_stroke_width(stroke_width), 
      m_fill(fill_color), m_stroke_style({}) {};
    SVGPathStyle(
        const ColorRGB& stroke_color, double stroke_width, const MaybeColorRGB& fill_color,
        const SVGStrokeStyle& stroke_style)
    : m_stroke(stroke_color), m_stroke_width(stroke_width),
      m_fill(fill_color), m_stroke_style(stroke_style) {};

protected:
    std::string to_string() const;

private:
    ColorRGB m_stroke;
    double m_stroke_width;
    MaybeColorRGB m_fill;
    SVGStrokeStyle m_stroke_style;

    friend class SVGPath;
};

}