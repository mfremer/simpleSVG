# simpleSVG
Simple C++17 library for writing simple SVGs exclusively made of paths with simple styles.

## Using the library in a project
To use the library in a project, simply add the simpleSVG subdirectory in your `CMakeLists.txt` using `add_subdirectory` and link against the library using `target_link_libraries`.
```CMake
...
add_subdirectory(simpleSVG)
add_executable(<project name> <project sources...>)
target_link_libraries(<project name> PUBLIC simpleSVG)
...
```

## Basic use
All code is under the `SimpleSVG` namespace. The four main objects are `SVGFile`, `SVGPath`, `SVGPathCommand` and `SVGPathStyle`.

An `SVGFile` is made of multiple `SVGPath`s, each having an `SVGPathSytle` determining their appearance. Paths consist of multiple `SVGPathCommands` that determine the geometry of the path, created with functions such as `move_to`, `line_to` or `elliptic_arc_to`.

Path commands are added to a path using `operator<<`. Paths are added to a file in the same fashion.

The following example illustrates a basic use case for the library:
```C++
#include <simpleSVG.hpp>

using namespace simpleSVG;

int main() {
    // initializes the file, a path style and a path
    SVGFile      file(500, 500, SVGUnit::MM); // 500x500mm canvas
    SVGPathStyle style({255, 0, 0}, 0.5);     // color, thickness
    SVGPath      path(style);

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
```

## List of examples
- [basic](/examples/basic/main.cpp): showcases basic operations such as defining and writing to an svg file, creating a simple path style and path.
- [holed_polygon](/examples/holed_polygon/main.cpp): showcases how to create a closed filled polygon with a hole using a single path.
- [elliptical_arc](/examples/elliptical_arc/main.cpp): shows the effects of the boolean flags in the `elliptical_arc` path command that help select which elliptical arc to draw between two given points.
- [markers](/examples/markers/main.cpp): shows how to define markers (arrowhead, triangle), include them in a file and apply them to a path.
- [groups](/examples/groups/main.cpp): shows how to separate paths in the `elliptical_arc` example into two separate groups.
- [forbidden_minors](/examples/forbidden_minors/main.cpp): showcases a more complicated example that generates two graphs, $K_{3,3}$ (complete bipartite graph with $3$ left and $3$ right nodes) and $K_5$ (complete graph with $5$ nodes).

## Notes
- SVGs have their origin at the top-left, with x increasing from left to right and y increasing from top to bottom. This means that for the (x, y, z) basis to be right-handed, z points towards the screen. If you are doing fabrication (plotting or cutting), you might want to flip the y-axis to have the origin at the bottom-left by using the `SVGFile` constructor.
- To create holes in a closed filled path, you need to have two closed paths winding in different directions (clockwise/counterclockwise) within the same `SVGPath`. You might want to change the path's `fill-rule` option if the obtained result is not the desired one.

## TODOs
- [ ] Check path drawing order.
- [ ] Add support for inkscape layers.
- [ ] Add support for transforms.
