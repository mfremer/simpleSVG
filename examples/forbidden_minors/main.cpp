/**
 * @file main.cpp
 * @author mfremer
 * @date 2024-02-13
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <simpleSVG.hpp>

#include <algorithm>
#include <complex>
#include <iostream>
#include <vector>

#include <cmath>
#include <cstdlib>

using namespace simpleSVG;

// General settings
constexpr double CANVAS_SIZE = 100;
constexpr double NODE_STROKE_SIZE = 1.0;
constexpr double ARC_STROKE_SIZE = 1.0;
constexpr size_t NODE_POINTS = 32;
constexpr double NODE_RADIUS = 5.;

// K_{3,3} settings
constexpr double K33_CENTER_POS_X = 0.5 * CANVAS_SIZE;
constexpr double K33_CENTER_POS_Y = 0.5 * CANVAS_SIZE;
constexpr double K33_SPACING_ROWS = 20;
constexpr double K33_SPACING_COLS = 40;
constexpr double K33_TOPLEFT_POS_X = K33_CENTER_POS_X - 0.5 * K33_SPACING_COLS;
constexpr double K33_TOPLEFT_POS_Y = K33_CENTER_POS_X - K33_SPACING_ROWS;

// K_5 settings
constexpr double K5_CENTER_POS_X = 0.5 * CANVAS_SIZE;
constexpr double K5_CENTER_POS_Y = 0.5 * CANVAS_SIZE;
constexpr double K5_RADIUS = 25.;

std::vector<std::pair<double, double>> polygon(
    double x, double y, double r, size_t n)
{
    const double step = 2. * M_PI / static_cast<double>(n);
    std::vector<std::pair<double, double>> vs(n + 1);
    std::generate(vs.begin(), vs.end(),
        [&, k = 0]() mutable {
            std::complex z = std::polar(1., (k++) * step);
            return std::pair<double, double>{ x + r * z.real(), y + r * z.imag() };
        });
    return vs;
}

std::vector<SVGPathCommand> create_node(double x, double y, double r, size_t n) {
    std::vector<SVGPathCommand> node_cmds;
    auto node = polygon(x, y, r, n);
    bool first = true;
    for (const auto& [x, y] : node) {
        auto cmd = (first ? move_to(x, y, false) : line_to(x, y, false));
        node_cmds.push_back(cmd);
        first = false;
    }
    return node_cmds;
}

int main() {
    SVGFile file_k33(CANVAS_SIZE, CANVAS_SIZE, SVGUnit::MM, false);
    SVGFile file_k5(CANVAS_SIZE, CANVAS_SIZE, SVGUnit::MM, false);

    ColorRGB black{0, 0, 0};
    ColorRGB white{180, 180, 180};
    SVGPathStyle node_style(black, NODE_STROKE_SIZE, white, SVGFillRule::EVEN_ODD);
    SVGPathStyle arc_style(black, ARC_STROKE_SIZE, SVGLineCap::ROUND, SVGLineJoin::ROUND);

    // K_{3,3}
    std::vector<std::pair<double, double>> node_pos_k33(6);
    for (size_t col = 0; col < 2; ++col) {
        for (size_t row = 0; row < 3; ++row) {
            node_pos_k33[3 * col + row] = 
                { K33_TOPLEFT_POS_X + col * K33_SPACING_COLS,
                  K33_TOPLEFT_POS_Y + row * K33_SPACING_ROWS };
        }
    }
    SVGPath nodes_k33(node_style);
    for (const auto& [x, y] : node_pos_k33) {
        nodes_k33 << create_node(x, y, NODE_RADIUS, NODE_POINTS);
    }
    SVGPath arcs_k33(arc_style);
    for (size_t left = 0; left < 3; ++left) {
        for (size_t right = 0; right < 3; ++right) {
            const auto& [lx, ly] = node_pos_k33[left];
            const auto& [rx, ry] = node_pos_k33[3 + right];
            arcs_k33 << move_to(lx, ly, false) << line_to(rx, ry, false);
        }
    }
    file_k33 << arcs_k33;
    file_k33 << nodes_k33;
    file_k33.write_file("./forbidden_minors_k33.svg");

    // K_5
    std::vector<std::pair<double, double>> node_pos_k5(5);
    std::generate(node_pos_k5.begin(), node_pos_k5.end(),
        [k = 0]() mutable {
            constexpr double step = (2. / 5. * M_PI);
            std::complex z = std::polar(1., (k++ - 0.25) * step);
            return std::pair<double, double>{ 
                K5_CENTER_POS_X + K5_RADIUS * z.real(),
                K5_CENTER_POS_Y + K5_RADIUS * z.imag()};
        });
    
    SVGPath nodes_k5(node_style);
    for (const auto& [x, y] : node_pos_k5) {
        nodes_k5 << create_node(x, y, NODE_RADIUS, NODE_POINTS);
    }
    SVGPath arcs_k5(arc_style);
    for (size_t i = 0; i < 5; ++i) {
        for (size_t j = i + 1; j < 5; ++j) {
            const auto& [ix, iy] = node_pos_k5[i];
            const auto& [jx, jy] = node_pos_k5[j];
            arcs_k5 << move_to(ix, iy, false) << line_to(jx, jy, false);
        }
    }
    file_k5 << arcs_k5;
    file_k5 << nodes_k5;
    file_k5.write_file("./forbidden_minors_k5.svg");
    
    return EXIT_SUCCESS;
}