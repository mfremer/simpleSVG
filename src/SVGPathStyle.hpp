#pragma once

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

std::string color_to_string(const ColorRGB& color);

class SVGPathStyle {
public:
    SVGPathStyle(
        const ColorRGB& stroke_color, double stroke_width)
    : m_stroke(stroke_color), m_stroke_width(stroke_width), m_stroke_dasharray({}) {};
    SVGPathStyle(
        const ColorRGB& stroke_color, double stroke_width,
        const std::string& stroke_dasharray)
    : m_stroke(stroke_color), m_stroke_width(stroke_width),
      m_stroke_dasharray(stroke_dasharray) {};

protected:
    std::string to_string() const;

private:
    ColorRGB m_stroke;
    double m_stroke_width;
    std::string m_stroke_dasharray;

    friend class SVGPath;
};

}