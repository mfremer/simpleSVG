/**
 * @file main.cpp
 * @author mfremer
 * @date 2024-04-29
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <simpleSVG.hpp>

#include <array>
#include <vector>

#include <cstdlib>

using namespace simpleSVG;

constexpr double SVG_WIDTH = 200.;
constexpr double SVG_HEIGHT = 50.;

constexpr double TILE_SIZE = 10;
constexpr double TILE_STROKE_WIDTH = 0.5;
constexpr double INIT_POS_X = 10.;
constexpr double INIT_POS_Y = 20.;
constexpr double TILE_SPACING_X = 5.;

std::vector<SVGPath> create_tile(
    double pos_x, double pos_y, double size,
    const SVGPathStyle& base,
    const SVGPathStyle& left, const SVGPathStyle& top,
    const SVGPathStyle& right, const SVGPathStyle& bottom)
{
    SVGPath base_path(base);
    base_path << move_to(pos_x, pos_y, false)
              << line_to(size, 0, true)
              << line_to(0, size, true)
              << line_to(-size, 0, true)
              << line_to(0, -size, true);
    // For some reason results in a square corner instead of round...
    //        << close_path();
    SVGPath left_path(left); // left
    left_path << move_to(pos_x, pos_y, false)
              << line_to(0.5 * size, 0.5 * size, true)
              << line_to(-0.5 * size, 0.5 * size, true)
              << close_path();
    SVGPath top_path(top); // top
    top_path << move_to(pos_x + size, pos_y, false)
             << line_to(-0.5 * size, 0.5 * size, true)
             << line_to(-0.5 * size, -0.5 * size, true)
             << close_path();
    SVGPath right_path(right); // right
    right_path << move_to(pos_x + size, pos_y + size, false)
               << line_to(-0.5 * size, -0.5 * size, true)
               << line_to(0.5 * size, -0.5 * size, true)
               << close_path();
    SVGPath bottom_path(bottom); // bottom
    bottom_path << move_to(pos_x, pos_y + size, false)
                << line_to(0.5 * size, -0.5 * size, true)
                << line_to(0.5 * size, 0.5 * size, true)
                << close_path();
    
    return {left_path, top_path, right_path, bottom_path, base_path};
}

int main() {
    SVGFile file(SVG_WIDTH, SVG_HEIGHT, SVGUnit::MM);

    SVGPathStyle style_base(
        ColorRGB{0, 0, 0}, TILE_STROKE_WIDTH, SVGLineCap::ROUND, SVGLineJoin::ROUND
    );
    SVGPathStyle style0(
        ColorRGB{120, 94, 240}, SVGFillRule::NON_ZERO
    );
    SVGPathStyle style1(
        ColorRGB{220, 38, 127}, SVGFillRule::NON_ZERO
    );
    SVGPathStyle style2(
        ColorRGB{254, 97, 0}, SVGFillRule::NON_ZERO
    );
    SVGPathStyle style3(
        ColorRGB{255, 176, 0}, SVGFillRule::NON_ZERO
    );
    
    std::vector<SVGPathStyle> styles{ style0, style1, style2, style3 };
    std::array<std::array<size_t, 4>, 11> tiles{
        std::array<size_t, 4>{0, 1, 1, 1},
        {0, 2, 1, 2},
        {0, 1, 0, 0},
        {2, 3, 2, 1},
        {2, 2, 2, 3},
        {3, 3, 3, 1},
        {3, 1, 0, 2},
        {1, 2, 3, 2},
        {1, 2, 1, 3},
        {1, 0, 0, 2},
        {0, 1, 3, 1}
    };

    for (size_t i = 0; i < tiles.size(); ++i) {
        const auto& [l, t, r, b] = tiles[i];
        file.begin_group("tile" + std::to_string(i));
        file << create_tile(INIT_POS_X + i * (TILE_SIZE + TILE_SPACING_X), INIT_POS_Y, TILE_SIZE,
                            style_base, styles[l], styles[t], styles[r], styles[b]);
        file.end_group();
    }

    file.write_file("./wang_tiles.svg");

    return EXIT_SUCCESS;
}