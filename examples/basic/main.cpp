#include <simpleSVG.hpp>

using namespace simpleSVG;

int main() {
    SVGFile file(1000, 1000, SVGUnit::MM, false);
    SVGPathStyle style({255, 0, 0}, 0.5, "4 2");
    SVGPath path(style);

    path << move_to(100, 100, false)
         << line_to(400, 100, false)
         << line_to(400, 400, false)
         << line_to(100, 400, false)
         << close_path();
    file << path;

    file.write_file("./basic.svg");
}