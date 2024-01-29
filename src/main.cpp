#include "simpleSVG.hpp"

#include <cstdlib>

int main() {
    SVGFile svg(1000, 1000, SVGUnit::MM);

    SVGPath path(SVGPathStyle({255, 0, 0}, 0.5, "4 2"));
    path << move_to(100, 100, false)
         << line_to(400, 100, false)
         << line_to(400, 400, false)
         << line_to(100, 400, false)
         << close_path();
    
    svg << path;
    svg.write_file("../data/out.svg");
    
    return EXIT_SUCCESS;
}