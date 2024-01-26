#pragma once

#include "SVGPath.hpp"

#include <string>
#include <vector>

enum class SVGUnit {
    CM, // centimeters
    IN, // inches
    PT, // points
    PC, // picas
    MM, // millimeters
    PX  // pixels
};

std::string unit_to_string(SVGUnit unit);

class SVGFile {
public:
    SVGFile(double width, double height, SVGUnit unit)
    : m_width(width), m_height(height), m_unit(unit) {};

    void add_path(const SVGPath& path);
    void write_file(const std::string& filename) const;
private:
    double m_width;
    double m_height;
    SVGUnit m_unit;

    std::vector<SVGPath> m_paths;
};