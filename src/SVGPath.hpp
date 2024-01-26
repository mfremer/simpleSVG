#pragma once

#include "SVGPathCommand.hpp"
#include "SVGPathStyle.hpp"

#include <string>
#include <vector>

class SVGPath {
public:
    SVGPath(const SVGPathStyle& path_style)
    : m_commands({}), m_style(path_style) {};

    void add_command(const SVGPathCommand& path_command);
    std::string to_string() const;
private:
    std::vector<SVGPathCommand> m_commands;
    SVGPathStyle m_style;
};