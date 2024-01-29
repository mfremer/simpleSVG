#pragma once

#include "SVGPath.hpp"

#include <string>
#include <vector>

namespace simpleSVG {

enum class SVGUnit {
    CM, // centimeters
    IN, // inches
    PT, // points
    PC, // picas
    MM, // millimeters
    PX  // pixels
};

class SVGFile {
public:
    SVGFile(double width, double height, SVGUnit unit, bool flip_y_axis)
    : m_width(width), m_height(height), m_unit(unit), m_flip_y_axis(flip_y_axis) {};

    void write_file(const std::string& filename) const;
    friend SVGFile& operator<<(SVGFile& file, const SVGPath& path);

private:
    void add_path(const SVGPath& path);

    double m_width;
    double m_height;
    SVGUnit m_unit;
    bool m_flip_y_axis;
    std::vector<SVGPath> m_paths;
};

}