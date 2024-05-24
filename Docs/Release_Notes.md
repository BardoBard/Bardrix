# [v0.2.1](https://github.com/BardoBard/Bardrix/releases/tag/v0.2.1)

## Overview

**Full Changelog**: https://github.com/BardoBard/Bardrix/compare/v0.2.0...v0.2.1

Added [CONTRIBUTING.md](../CONTRIBUTING.md) to help contributors get started with the project. \
Added more documentation to the codebase to help contributors understand the codebase. \
Added a workflow to test the examples, this will help pushing correct code to the repository.

## Documentation Changes

Added inverse square law example to [Raytracing readme](Examples/Raytracing/README.md). \
Added sphere light calculation example to [Raytracing readme](Examples/Raytracing/README.md). \
Added objects (shape, material) to [Bardrix_Reference](Bardrix_Reference.md). \
Added code and visual sphere intersection example to [Raytracing readme](Examples/Raytracing/README.md).

## Code Changes

### Minor Changes

Updated [raytracing example](Examples/Raytracing/main.cpp) and [window.cpp](Examples/Raytracing/window.cpp) now doesn't
give a compiler error when running on an operating system other than Windows, instead it prints out a message that it is
not supported. \
Added [Examples/CMakeLists.txt](Examples/CMakeLists.txt) to include all the examples in one build. \
Renamed `position` to `position_` and made it protected in [sphere](Examples/Raytracing/sphere.h).

## Test Changes

Added a generic workflow for building and testing on multiple platforms. \
Added a workflow for testing if the examples compile.

# [v0.2.0](https://github.com/BardoBard/Bardrix/releases/tag/v0.2.0)

## Overview

**Full Changelog**: https://github.com/BardoBard/Bardrix/compare/v0.1.0...v0.2.0

The changes have backward compatibility issues (comared to v0.1.0), only if you were
using `color::rgba()`, `color::rgba(unsigned)` or `color::color(unsigned)`. \
Color now uses RRGGBBAA format instead of AABBGGRR format. This change was made to have a more consistent base color;
other colors will still be converted to this format and other formats. \
`window.h` when compiling in clang works fine, yet when running on cl (microsft compiler) it does not work. This is due
the encoding, which has now been fixed and updated in [window.h](Examples/Raytracing/window.h).

## Documentation Changes

Updated [Bardrix_Reference](Bardrix_Reference.md) to include `argb()` and `abgr()` in color. \
Added parameters to the math functions like `degrees_to_radians` [Bardrix_Reference](Bardrix_Reference.md)
Updated class diagrams to include `argb()` and `abgr()` in color. \
Updated [Raytracing cpp](Examples/Raytracing/main.cpp) to include the new changes in color and center the screen.

## Code Changes

### Major Changes

Updated `unsigned` to uint32_t in color to always have a 32 bit integer representation. \
Updated color to now represent the correct layout (RRGGBBAA instead of the previous AABBGGRR) for 32 bit integer
representation. This change means that previously used `rgba()` and `rgba(rgba : unsigned)` should be altered to
use `abgr()` instead. \
Added `argb()` and `abgr()` to color (this will help with windows API which uses argb).

### Minor Changes

Fixed small compiler compatibility issues fixed in Raytracer [Example](Examples/Raytracing/README.md). \
Added `#include <cstdint>` to [bardrix.h](../Bardrix/include/bardrix/bardrix.h) to include `uint32_t` for color.

# [v0.1.0](https://github.com/BardoBard/Bardrix/releases/tag/v0.1.0)

## Overview

This release changes to the API have been made, this is due to the fact that `width` and `height` in `camera` are
now `int` instead of `unsigned`. This is due to compatibility with other libraries that use `int` for width and height.
now call `get_width()`, `get_height()`, `set_width(int)`, `set_height(int)`.

`shoot_ray(unsigned, unsigned, double)` in `camera` now takes in `int` instead of `unsigned` for `x` and `y`. For the
same reason `width` and `height` are now `int`.

Added examples for simple raytracing.

## Documentation Changes

Added examples to docs/ for a very simple demonstration of how to use Bardrix and raytracing. \
Updated bardrix-math class diagram since in v0.0.5 it included `reflect` and `refract` instead of `reflection`
and `refraction`. \
Updated bardrix-view class diagram to accommodate the new changes in `camera`. \
Added release notes, this now gives more detail about the api changes happening in each release. \
Added `camera` to the [Bardrix_Reference](Bardrix_Reference.md).

## Code Changes

### Major Changes

Updated `width` and `height` to be `int` in [camera](../Bardrix/include/bardrix/camera.h). This is due to compatibility
with other libraries that use `int` for width and height. This changes does affect the api; due to the fact that now
you've got to call `get_width()`, `get_height()`, `set_width(int)`, `set_height(int)`. \
Updated `shoot_ray(unsigned, unsigned, double)` in [camera](../Bardrix/include/bardrix/camera.h) to take in `int`
instead of `unsigned` for `x` and `y`. This changes does affect the api; due to the fact that now you've got to
call `shoot_ray(int, int, double)`.

### Minor Changes

Added default constructor to [camera](../Bardrix/include/bardrix/camera.h) with position `(0, 0, 0)`, direction
`(0, 0, 1)`, width `800`, height `600` and fov `90`.
Added `<<` operator to [camera](../Bardrix/include/bardrix/camera.h) to print out the camera's components. \
Added `bardrix::` prefix to all the functions and classes in `objects.h` and `camera.h`, sometimes there was an issue
with overriding; when using an external IDE like clion it would not copy with it the pre-fixes.

## Test Changes

Added extra tests for `camera` to test the new changes. \
Removed a print line in `vector3_test.cpp` that was not needed.

# [v0.0.5](https://github.com/BardoBard/Bardrix/releases/tag/v0.0.5)

## Overview

The changes have no backward compatibility issues, as the changes are new features and bug fixes.

## Documentation Changes

Added [Bardrix_Reference](Bardrix_Reference.md) that contains all the functions and classes in Bardrix. \
Added [Mathematics](Mathematics.md) that contains mathematical functions to learn about the mathematics used in
Bardrix. \
Added [Introduction](Introduction.md) that contains a brief introduction to Bardrix. \
Added examples to documentation comments all over the code.
Updated [Conventions](Conventions.md) to include `Class Conventions`, `Testing Conventions`, `Documentation Conventions`
and `Commit Message Conventions`.

## Code Changes

### Major Changes

Added [material](../Bardrix/include/bardrix/objects.h) to create materials for objects.
Added abstract [shape](../Bardrix/include/bardrix/objects.h) class to create shapes for objects; e.g sphere, plane,
triangle, etc.

Added [grayscale](Bardrix_Reference.md#color) and [invert](Bardrix_Reference.md#color) to color.

Added [refraction](Bardrix_Reference.md#vector3) and [reflection](Bardrix_Reference.md#vector3) to vector3. Returning
optional vector3.

### Minor Changes

Added `!=` operator to [ray](Bardrix_Reference.md#ray), for some reason this was missing.

Updated [normalize](Bardrix_Reference.md#vector3) from `vector3` to now return a reference to the changed
vector3. `void` -> `vector3&`. \
Updated [normalize](Bardrix_Reference.md#quaternion) from `quaternion` to now return a reference to the changed
quaternion. `void` -> `quaternion&`.
Updated [conjugate](Bardrix_Reference.md#quaternion) from `quaternion` to now return a reference to the changed
quaternion. `void` -> `quaternion&`. \
Updated [reciprocal](Bardrix_Reference.md#quaternion) from `quaternion` to now return a reference to the changed
quaternion. `void` -> `quaternion&`.
