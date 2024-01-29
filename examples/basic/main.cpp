#include <simpleSVG.hpp>

using namespace simpleSVG;

int main() {
    // initializes the file, a path style and a path
    SVGFile file(500, 500, SVGUnit::MM);  // 500x500mm canvas
    SVGPathStyle style({255, 0, 0}, 0.5); // color, thickness
    SVGPath path(style);

    // creates a path representing a 300x300 square
    path << move_to(100, 100, false)
         << line_to(400, 100, false)
         << line_to(400, 400, false)
         << line_to(100, 400, false)
         << close_path();

    // adds the path to the file
    file << path;

    // writes the file to disk
    file.write_file("./basic.svg");
}