#pragma once

/**
 * @file SVGPath.hpp
 * @author mfremer
 * @date 2024-01-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include "SVGPathCommand.hpp"
#include "SVGPathStyle.hpp"

#include <string>
#include <vector>

namespace simpleSVG {

class SVGPath {
public:
    SVGPath(const SVGPathStyle& path_style)
    : m_commands({}), m_style(path_style) {};

    friend SVGPath& operator<<(SVGPath& path, const SVGPathCommand& path_command);

protected:
    std::string to_string() const;

private:
    void add_command(const SVGPathCommand& path_command);

    std::vector<SVGPathCommand> m_commands;
    SVGPathStyle m_style;

    friend class SVGFile;
    friend class SVGMarker;
};

}