/**
 * @file SVGFile.cpp
 * @author mfremer
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "SVGFile.hpp"

#include <iostream>
#include <fstream>

#include <cstdlib>

namespace simpleSVG {

std::string unit_to_string(SVGUnit unit) {
    switch (unit) {
        case SVGUnit::CM:
            return "cm";
            break;
        case SVGUnit::IN:
            return "in";
            break;
        case SVGUnit::PT:
            return "pt";
            break;
        case SVGUnit::PC:
            return "pc";
            break;
        case SVGUnit::MM:
            return "mm";
            break;
        case SVGUnit::PX:
            return "px";
            break;
    }
    return "";
}

void SVGFile::add_path(const SVGPath& path) {
    m_paths.push_back(path);
}

void SVGFile::add_marker(const SVGMarker& marker) {
    m_markers.push_back(marker);
}

void SVGFile::begin_group(const std::string& name) {
    m_group_name = name;
    m_group_start_id = m_paths.size();
    m_active_group = true;
}
void SVGFile::end_group() {
    if (m_active_group) {
        m_groups.push_back({m_group_name, m_group_start_id, m_paths.size()});
    }
    m_active_group = false;
}

void SVGFile::write_file(const std::string& filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "[ERROR]\tCould not open file " << filename << '\n';
        exit(EXIT_FAILURE);
    }
    std::string unit_str = unit_to_string(m_unit);
    
    // Write header
    file << "<svg "
         << "width=\"" << m_width << unit_str << "\" "
         << "height=\"" << m_height << unit_str << "\" "
         << "viewBox=\"" << "0 0 " << m_width << " " << m_height << "\" "
         << "xmlns=\"http://www.w3.org/2000/svg\">\n";

    // Flip y-axis if wanted
    if (m_flip_y_axis) {
        file << "<g transform=\"translate(0 " << m_height << ") scale(1 -1)\">\n";
    }

    // Write markers
    file << "<defs>\n";
    for (const auto& marker : m_markers) {
        file << marker.to_string() << '\n';
    }
    file << "</defs>\n";

    // Write paths
    if (m_groups.empty()) {
        for (const auto& path : m_paths) {
            file << path.to_string() << '\n';
        }
    } else {
        for (const auto& [name, start, end] : m_groups) {
            file << "<g id=\"" << name << "\">";
            for (size_t i = start; i < end; ++i) {
                file << m_paths[i].to_string() << '\n';
            }
            file << "</g>\n";
        }
    }



    // End y-axis flip and file
    if (m_flip_y_axis) {
        file << "</g>\n";
    }
    file << "</svg>";
    file.close();
}

SVGFile& operator<<(SVGFile& file, const SVGPath& path) {
    file.add_path(path);
    return file;
}

SVGFile& operator<<(SVGFile& file, const std::vector<SVGPath>& paths) {
    for (const auto& p : paths) { file.add_path(p); }
    return file;
}

}