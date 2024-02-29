/**
 * @file SVGFile.hpp
 * @author mfremer
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "SVGPath.hpp"
#include "SVGMarker.hpp"

#include <string>
#include <tuple>
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
    SVGFile(double width, double height, SVGUnit unit)
    : m_width(width), m_height(height), m_unit(unit), m_flip_y_axis(false) {};

    SVGFile(double width, double height, SVGUnit unit, bool flip_y_axis)
    : m_width(width), m_height(height), m_unit(unit), m_flip_y_axis(flip_y_axis) {};

    void write_file(const std::string& filename) const;
    friend SVGFile& operator<<(SVGFile& file, const SVGPath& path);
    friend SVGFile& operator<<(SVGFile& file, const std::vector<SVGPath>& paths);

    void add_marker(const SVGMarker& marker);
    void begin_group(const std::string& name);
    void end_group();
private:
    void add_path(const SVGPath& path);

    double m_width;
    double m_height;
    SVGUnit m_unit;
    bool m_flip_y_axis;
    std::vector<SVGPath> m_paths;
    std::vector<SVGMarker> m_markers;

    // group variables
    bool m_active_group = false;
    std::string m_group_name;
    size_t m_group_start_id;
    std::vector<std::tuple<std::string, size_t, size_t>> m_groups;
};

}