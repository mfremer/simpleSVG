# simpleSVG
Simple library for writing simple SVGs exclusively made of paths with simple styles.

## Basic use
All code is under the `SimpleSVG` namespace. The four main objects are `SVGFile`, `SVGPath`, `SVGPathCommand` and `SVGPathStyle`.

An `SVGFile` is made of multiple `SVGPath`s, each having an `SVGPathSytle` determining their appearance. Pathss consist of multiple `SVGPathCommands`, which are the basic building blocks. `SVGPathCommands` are created with functions such as `move_to`, `line_to` or `elliptic_arc_to` that determine the geometry of the path.

Path commands are added to a path using `operator<<`. Paths are added to a file in the same fashion.

The following example illustrates a basic use case for the library:
```
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
```

## Notes
- SVGs have their origin at the top-left, with x increasing from left to right and y increasing from top to bottom. This means that for the (x, y, z) basis to be right-handed, z points towards the screen.

## Useful links
- [SVG path element](https://developer.mozilla.org/en-US/docs/Web/SVG/Element/path)
- [SVG path "d" attribute](https://developer.mozilla.org/en-US/docs/Web/SVG/Attribute/d#path_commands)