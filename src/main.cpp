#include <SVGFile.hpp>
#include <SVGPath.hpp>
#include <SVGPathCommand.hpp>
#include <SVGPathStyle.hpp>

#include <cstdlib>

int main() {
    SVGFile svg(1000, 1000, SVGUnit::MM);

    SVGPath path(SVGPathStyle({255, 0, 0}, 0.5, "4 2"));
    path.add_command(move_to(100, 100, false));
    path.add_command(line_to(400, 100, false));
    path.add_command(line_to(400, 400, false));
    path.add_command(line_to(100, 400, false));
    path.add_command(close_path());
    
    svg.add_path(path);
    svg.write_file("../data/out.svg");
    
    return EXIT_SUCCESS;
}