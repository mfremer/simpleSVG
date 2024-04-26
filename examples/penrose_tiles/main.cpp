/**
 * @file main.cpp
 * @author mfremer
 * @date 2024-04-26
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <simpleSVG.hpp>

#include <vector>

#include <cmath>
#include <cstdlib>

using namespace simpleSVG;

constexpr double deg_to_rad(double angle_deg) {
    return M_PI * angle_deg / 180.;
}
const double COS36 = cos(deg_to_rad(36.));
const double COS72 = cos(deg_to_rad(72.));
const double SIN18 = sin(deg_to_rad(18.));
const double SIN36 = sin(deg_to_rad(36.));
const double SIN72 = sin(deg_to_rad(72.));

// https://en.wikipedia.org/wiki/Penrose_tiling#Kite_and_dart_tiling_(P2)
// Parameters
constexpr double SVG_WIDTH   = 100.;
constexpr double SVG_HEIGHT  = 100.;
constexpr double TILE_SIZE   = 30.;
constexpr double NODE_RADIUS = 0.075 * TILE_SIZE;
constexpr double KITE_POS_X  = 20.; // west point of bounding box
constexpr double KITE_POS_Y  = 50.;
constexpr double DART_POS_X  = 60.; // west point of bounding box
constexpr double DART_POS_Y  = KITE_POS_Y;

// Derived parameters
constexpr double NODE_DIAMETER = 2. * NODE_RADIUS;
const double OTHER_SIZE = TILE_SIZE * SIN36 / SIN72;
const double KITE_WIDTH = TILE_SIZE * COS36 + OTHER_SIZE * COS72;
const double KITE_HEIGHT = 2. * TILE_SIZE * SIN36;
const double DART_WIDTH = TILE_SIZE * COS36;
const double DART_HEIGHT = KITE_HEIGHT;

// Steps (w/ or w/o drawing) in a direction determined by the given angle by a given distance
SVGPathCommand step(double distance, double angle_deg, bool draw) {
    double angle_rad = deg_to_rad(angle_deg);
    if (draw) {
        return line_to(distance * cos(angle_rad), distance * sin(angle_rad), true);
    }
    return move_to(distance * cos(angle_rad), distance * sin(angle_rad), true);
}

// Returns a series of SVGPathCommands to draw a circle of given radius at current point
std::vector<SVGPathCommand> circle_in_place(double radius) {
    double diameter = 2 * radius;
    return {
        move_to(radius, 0., true),
        circular_arc_to(radius, true, true, -diameter, 0., true),
        circular_arc_to(radius, true, true,  diameter, 0., true),
        move_to(-radius, 0., true)
    };
}

int main() {
    SVGFile file(SVG_WIDTH, SVG_HEIGHT, SVGUnit::MM, false);

    // Style definitions
    SVGPathStyle style_tile(
        ColorRGB{64, 64, 64}, 1.5
    );
    SVGPathStyle style_mask(
        ColorRGB{255, 255, 255}, SVGFillRule::NON_ZERO
    );
    SVGPathStyle style_node1(
        ColorRGB{255, 176, 0}, SVGFillRule::NON_ZERO
    );
    SVGPathStyle style_node2(
        ColorRGB{100, 143, 255}, SVGFillRule::NON_ZERO
    );

    /* KITE ---------------------------------------------------------------- */
    // Kite shape
    SVGPath kite(style_tile);
    kite << move_to(KITE_POS_X, KITE_POS_Y, false)
         << step( TILE_SIZE,   36., true)
         << step(OTHER_SIZE,  -72., true)
         << step(OTHER_SIZE, -108., true)
         << close_path();

    // Kite nodes: colored corner circles serving as assembly instructions
    SVGPath kite_nodes1(style_node1);
    kite_nodes1 << move_to(KITE_POS_X, KITE_POS_Y, false)
                << step( TILE_SIZE,   36., false)
                << circle_in_place(NODE_RADIUS)
                << step(OTHER_SIZE,  -72., false)
                << step(OTHER_SIZE, -108., false)
                << circle_in_place(NODE_RADIUS);
    SVGPath kite_nodes2(style_node2);
    kite_nodes2 << move_to(KITE_POS_X, KITE_POS_Y, false)
                << circle_in_place(NODE_RADIUS)
                << step( TILE_SIZE,   36., false)
                << step(OTHER_SIZE,  -72., false)
                << circle_in_place(NODE_RADIUS);

    // Kite mask: rectangle with a kite-shaped hole to crop corner nodes
    SVGPath kite_mask(style_mask);
    double extra_padding = 1.1 * NODE_DIAMETER;
    double kite_width_adapted = KITE_WIDTH + extra_padding;
    double kite_height_adapted = KITE_HEIGHT + extra_padding;
    kite_mask << move_to(KITE_POS_X - 0.5 * extra_padding, KITE_POS_Y, false)
              << line_to(0., -0.5 * kite_height_adapted, true)
              << line_to(kite_width_adapted, 0., true)
              << line_to(0., kite_height_adapted, true)
              << line_to(-kite_width_adapted, 0., true)
              << close_path()  // rectangle done
              << move_to(0.5 * extra_padding, 0., true)
              << step( TILE_SIZE,   36., true)
              << step(OTHER_SIZE,  -72., true)
              << step(OTHER_SIZE, -108., true)
              << close_path(); // hole done
    
    /* DART ---------------------------------------------------------------- */
    // Dart shape
    SVGPath dart(style_tile);
    double dart_adjustment = OTHER_SIZE * SIN18;
    dart << move_to(DART_POS_X + dart_adjustment, DART_POS_Y, false)
         << step(OTHER_SIZE,  108., true)
         << step( TILE_SIZE,  -36., true)
         << step( TILE_SIZE, -144., true)
         << close_path();
    
    SVGPath dart_nodes1(style_node1);
    dart_nodes1 << move_to(DART_POS_X + dart_adjustment, DART_POS_Y, false)
                << circle_in_place(NODE_RADIUS)
                << step(OTHER_SIZE,  108., false)
                << step( TILE_SIZE,  -36., false)
                << circle_in_place(NODE_RADIUS);
    SVGPath dart_nodes2(style_node2);
    dart_nodes2 << move_to(DART_POS_X + dart_adjustment, DART_POS_Y, false)
                << step(OTHER_SIZE,  108., false)
                << circle_in_place(NODE_RADIUS)
                << step( TILE_SIZE,  -36., false)
                << step( TILE_SIZE, -144., false)
                << circle_in_place(NODE_RADIUS);

    // Dart mask: rectangle with a dart-shaped hole to crop corner nodes
    SVGPath dart_mask(style_mask);
    double dart_width_adapted = DART_WIDTH + extra_padding;
    double dart_height_adapted = DART_HEIGHT + extra_padding;
    dart_mask << move_to(DART_POS_X - 0.5 * extra_padding, DART_POS_Y, false)
              << line_to(0., -0.5 * dart_height_adapted, true)
              << line_to(dart_width_adapted, 0., true)
              << line_to(0., dart_height_adapted, true)
              << line_to(-dart_width_adapted, 0., true)
              << close_path()  // rectangle done
              << move_to(dart_adjustment + 0.5 * extra_padding, 0., true)
              << step(OTHER_SIZE,  108., true)
              << step( TILE_SIZE,  -36., true)
              << step( TILE_SIZE, -144., true)
              << close_path(); // hole done
    
    // Adding elements to file
    file.begin_group("Jite");
    file << kite << kite_nodes1 << kite_nodes2 << kite_mask;
    file.end_group();
    file.begin_group("Dart");
    file << dart << dart_nodes1 << dart_nodes2 << dart_mask;
    file.end_group();

    file.write_file("./penrose_tiles.svg");

    return EXIT_SUCCESS;
}