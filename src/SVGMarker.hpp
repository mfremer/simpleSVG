/**
 * @file SVGMarker.hpp
 * @author mfremer
 * @date 2024-02-12
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#pragma once

#include "SVGPath.hpp"

#include <string>

namespace simpleSVG {

class SVGMarker {
public:
    SVGMarker(const std::string& id, const SVGPath& path)
        : m_id(id), m_path(path) {};

protected:
    std::string to_string() const;

private:
    std::string m_id;
    SVGPath m_path;
    double m_scale;

    friend class SVGFile;
};

}