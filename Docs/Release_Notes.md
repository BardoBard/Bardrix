# [v0.3.1](https://github.com/BardoBard/Bardrix/releases/tag/v0.3.1)

## Overview

Added color blending to `color`. \
Added physics (conversion calculations + gravity calculations). \
Solved issues [36](https://github.com/BardoBard/Bardrix/issues/36) and [37](https://github.com/BardoBard/Bardrix/issues/37).

**Full Changelog**: https://github.com/BardoBard/Bardrix/compare/v0.3.0...v0.3.1

## Documentation Changes

Renamed a classes in [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.3.1/Docs/Bardrix_Reference.md) to
be lowercase instead of uppercase. \
Added color blending and physics
to [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.3.1/Docs/Bardrix_Reference.md). \
Added `#define NOMINMAX`
to [window.h](https://github.com/bardobard/bardrix/blob/v0.3.1/Docs/Examples/Raytracing/window.h) to fix an issue with
`min` and `max` being defined in `windows.h`. \
Updated the versions in examples (cmake).

## Code Changes

### Major Changes

Added color blending to [color](https://github.com/bardobard/bardrix/blob/v0.3.1/Bardrix/include/bardrix/color.h). \
Added physics to [physics](https://github.com/bardobard/bardrix/blob/v0.3.1/Bardrix/include/bardrix/physics.h).

## Test Changes

Added tests for color blending. \
Added tests for physics.

# [v0.3.0](https://github.com/BardoBard/Bardrix/releases/tag/v0.3.0)

Major changes to the API have been made regarding `material` and `vector3::reflection`.

## Overview

**Full Changelog**: https://github.com/BardoBard/Bardrix/compare/v0.2.3...v0.3.0

The changes have backward compatibility issues (compared to v0.2.x), only if you were using `material` class
or `vector3::reflection`.

## Documentation Changes

Updated `Bardrix_Reference` to include `material` and `vector3::reflection` updates. \
Updated `Mathematics` to include the **correct** `vector3::reflection` formula. \
Added readme to [Docs/](https://github.com/bardobard/bardrix/blob/v0.3.0/Docs/). \
Added sphere normal calculation example
to [Raytracing readme](https://github.com/bardobard/bardrix/blob/v0.3.0/Docs/Examples/Raytracing/README.md). \
Added documentation to sphere class
in [sphere example](https://github.com/bardobard/bardrix/blob/v0.3.0/Docs/Examples/Raytracing/sphere.h). \
Made sure that in Release Notes the links are to the versions they are referring to instead of the latest version. \
Added
documentation [Raytracing-Reflections](https://github.com/bardobard/bardrix/blob/v0.3.0/Docs/Examples/Raytracing-Reflections/README.md). \
Solved issue [33](https://github.com/BardoBard/Bardrix/issues/33), where degenerate cases aren't marked as such.

## Code Changes

### Major Changes

Updated shininess in [material](https://github.com/bardobard/bardrix/blob/v0.3.0/Bardrix/include/bardrix/material.h) to
have a limit between \[1, infinity)\] which for some reason wasn't the case. \
Updated diffuse and specular to not be opposites anymore because I thought they were, but they are not. \
Updated [vector3::reflection](https://github.com/bardobard/bardrix/blob/v0.3.0/Bardrix/include/bardrix/vector3.h) to now
actually work instead of returning the inverse of the reflection. Also reflection now doesn't return a unit vector but
instead a vector with the same length as the input vector.

### Minor Changes

Renamed protected variable `bmi` (bitmap info) to `bmi_`, `back_buffer` to `back_buffer_` and `front_buffer` to
`front_buffer_`
in [window example](https://github.com/bardobard/bardrix/blob/v0.3.0/Docs/Examples/Raytracing/window.cpp). \
Added `material` to sphere constructor
in [sphere example](https://github.com/bardobard/bardrix/blob/v0.3.0/Docs/Examples/Raytracing/sphere.h).

## Test Changes

Added tests for `material` and `vector3::reflection` to account for the new changes.
Renamed workflow template from `Build Job` to `Build And Test CMake` to better reflect what it does.

## Documentation Changes

# [v0.2.3](https://github.com/BardoBard/Bardrix/releases/tag/v0.2.3)

Documentation hotfix, wrong formula in example.

## Overview

**Full Changelog**: https://github.com/BardoBard/Bardrix/compare/v0.2.2...v0.2.3

Solved issue [32](https://github.com/BardoBard/Bardrix/issues/32),
where [Mathematics](https://github.com/bardobard/bardrix/blob/v0.2.3/Docs/Mathematics.md) didn't have a table of
contents. \
Updated incorrect formula
in [Raytracing example](https://github.com/bardobard/bardrix/blob/v0.2.3/Docs/Examples/Raytracing/README.md) for
calculating the light intensity at a certain point. \
Updated incorrect formula
in [Raytracing example](https://github.com/bardobard/bardrix/blob/v0.2.3/Docs/Examples/Raytracing/README.md) for
calculating the intersection point of a sphere.

## Documentation Changes

Solved issue [32](https://github.com/BardoBard/Bardrix/issues/32),
where [Mathematics](https://github.com/bardobard/bardrix/blob/v0.2.3/Docs/Mathematics.md) didn't have a table of
contents. \
Updated incorrect formula
in [Raytracing example](https://github.com/bardobard/bardrix/blob/v0.2.3/Docs/Examples/Raytracing/README.md) for
calculating the light intensity at a certain point. \
Updated incorrect formula
in [Raytracing example](https://github.com/bardobard/bardrix/blob/v0.2.3/Docs/Examples/Raytracing/README.md) for
calculating the intersection point of a sphere.
Added next step
to [Introduction](https://github.com/bardobard/bardrix/blob/v0.2.3/Docs/Examples/Introduction/README.md).

# [v0.2.2](https://github.com/BardoBard/Bardrix/releases/tag/v0.2.2)

## Errors

In the [sphere intersection](https://github.com/bardobard/bardrix/blob/v0.2.2/Docs/Examples/Raytracing/sphere.h) it has
an error which means this version (for raytracing example) is unstable.

Very minor changes to documentation.

## Overview

**Full Changelog**: https://github.com/BardoBard/Bardrix/compare/v0.2.1...v0.2.2

Solved issue [30](https://github.com/BardoBard/Bardrix/issues/30), where in the README it doesn't properly link to the
github. \
Updated table of contents
in [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.2.2/Docs/Bardrix_Reference.md) to include objects (
material/shape). \
Updated README
in [Examples/Raytracing](https://github.com/bardobard/bardrix/blob/v0.2.2/Docs/Examples/Raytracing/README.md), forgot to
finish a sentence and updated table of
contents; which now also properly links.

## Documentation Changes

Updated [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.2.2/Docs/Bardrix_Reference.md) to include
objects (material/shape). \
Updated README
in [Examples/Raytracing](https://github.com/bardobard/bardrix/blob/v0.2.2/Docs/Examples/Raytracing/README.md), forgot to
finish a sentence and updated table of
contents; which now also properly links.
Updated name from `light_sphere_example.png` to `light_calculation_example.png` \
Updated [2.1 Light Sphere Intensity](https://github.com/bardobard/bardrix/blob/v0.2.2/Docs/Examples/Raytracing/README.md#21-light-intensity)
to Light Intensity. \
Solved issue [30](https://github.com/BardoBard/Bardrix/issues/30), where in the README it doesn't properly link to the
github.

# [v0.2.1](https://github.com/BardoBard/Bardrix/releases/tag/v0.2.1)

## Errors

In the [sphere intersection](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Examples/Raytracing/sphere.h) it has
an error which means this version (for raytracing example) is unstable.

## Overview

**Full Changelog**: https://github.com/BardoBard/Bardrix/compare/v0.2.0...v0.2.1

Added [CONTRIBUTING.md](https://github.com/bardobard/bardrix/blob/v0.2.1/CONTRIBUTING.md) to help contributors get
started with the project. \
Added more documentation to the codebase to help contributors understand the codebase. \
Added a workflow to test the examples, this will help pushing correct code to the repository.

## Documentation Changes

Added inverse square law example
to [Raytracing readme](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Examples/Raytracing/README.md). \
Added sphere light calculation example
to [Raytracing readme](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Examples/Raytracing/README.md). \
Added objects (shape, material)
to [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Bardrix_Reference.md). \
Added code and visual sphere intersection example
to [Raytracing readme](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Examples/Raytracing/README.md).

## Code Changes

### Minor Changes

Updated [raytracing example](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Examples/Raytracing/main.cpp)
and [window.cpp](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Examples/Raytracing/window.cpp) now doesn't
give a compiler error when running on an operating system other than Windows, instead it prints out a message that it is
not supported. \
Added [Examples/CMakeLists.txt](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Examples/CMakeLists.txt) to
include all the examples in one build. \
Renamed `position` to `position_` and made it protected
in [sphere](https://github.com/bardobard/bardrix/blob/v0.2.1/Docs/Examples/Raytracing/sphere.h).

## Test Changes

Added a generic workflow for building and testing on multiple platforms. \
Added a workflow for testing if the examples compile.

# [v0.2.0](https://github.com/BardoBard/Bardrix/releases/tag/v0.2.0)

## Overview

**Full Changelog**: https://github.com/BardoBard/Bardrix/compare/v0.1.0...v0.2.0

The changes have backward compatibility issues (compared to v0.1.0), only if you were
using `color::rgba()`, `color::rgba(unsigned)` or `color::color(unsigned)`. \
Color now uses RRGGBBAA format instead of AABBGGRR format. This change was made to have a more consistent base color;
other colors will still be converted to this format and other formats. \
`window.h` when compiling in clang works fine, yet when running on cl (microsft compiler) it does not work. This is due
the encoding, which has now been fixed and updated
in [window.h](https://github.com/bardobard/bardrix/blob/v0.2.0/Docs/Examples/Raytracing/window.h).

## Documentation Changes

Updated [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.2.0/Docs/Bardrix_Reference.md) to
include `argb()` and `abgr()` in color. \
Added parameters to the math functions
like `degrees_to_radians` [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.2.0/Docs/Bardrix_Reference.md)
Updated class diagrams to include `argb()` and `abgr()` in color. \
Updated [Raytracing cpp](https://github.com/bardobard/bardrix/blob/v0.2.0/Docs/Examples/Raytracing/main.cpp) to include
the new changes in color and center the screen.

## Code Changes

### Major Changes

Updated `unsigned` to uint32_t in color to always have a 32 bit integer representation. \
Updated color to now represent the correct layout (RRGGBBAA instead of the previous AABBGGRR) for 32 bit integer
representation. This change means that previously used `rgba()` and `rgba(rgba : unsigned)` should be altered to
use `abgr()` instead. \
Added `argb()` and `abgr()` to color (this will help with windows API which uses argb).

### Minor Changes

Fixed small compiler compatibility issues fixed in
Raytracer [Example](https://github.com/bardobard/bardrix/blob/v0.2.0/Docs/Examples/Raytracing/README.md). \
Added `#include <cstdint>`
to [bardrix.h](https://github.com/bardobard/bardrix/blob/v0.2.0/Bardrix/include/bardrix/bardrix.h) to include `uint32_t`
for color.

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
Added `camera` to the [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.1.0/Docs/Bardrix_Reference.md).

## Code Changes

### Major Changes

Updated `width` and `height` to be `int`
in [camera](https://github.com/bardobard/bardrix/blob/v0.1.0/Bardrix/include/bardrix/camera.h). This is due to
compatibility
with other libraries that use `int` for width and height. This changes does affect the api; due to the fact that now
you've got to call `get_width()`, `get_height()`, `set_width(int)`, `set_height(int)`. \
Updated `shoot_ray(unsigned, unsigned, double)`
in [camera](https://github.com/bardobard/bardrix/blob/v0.1.0/Docs/Bardrix/include/bardrix/camera.h) to take in `int`
instead of `unsigned` for `x` and `y`. This changes does affect the api; due to the fact that now you've got to
call `shoot_ray(int, int, double)`.

### Minor Changes

Added default constructor
to [camera](https://github.com/bardobard/bardrix/blob/v0.1.0/Docs/Bardrix/include/bardrix/camera.h) with
position `(0, 0, 0)`, direction
`(0, 0, 1)`, width `800`, height `600` and fov `90`.
Added `<<` operator to [camera](https://github.com/bardobard/bardrix/blob/v0.1.0/Docs/Bardrix/include/bardrix/camera.h)
to print out the camera's components. \
Added `bardrix::` prefix to all the functions and classes in `objects.h` and `camera.h`, sometimes there was an issue
with overriding; when using an external IDE like clion it would not copy with it the pre-fixes.

## Test Changes

Added extra tests for `camera` to test the new changes. \
Removed a print line in `vector3_test.cpp` that was not needed.

# [v0.0.5](https://github.com/BardoBard/Bardrix/releases/tag/v0.0.5)

## Overview

The changes have no backward compatibility issues, as the changes are new features and bug fixes.

## Documentation Changes

Added [Bardrix_Reference](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md) that contains all
the functions and classes in Bardrix. \
Added [Mathematics](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Mathematics.md) that contains mathematical
functions to learn about the mathematics used in
Bardrix. \
Added [Introduction](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Introduction.md) that contains a brief
introduction to Bardrix. \
Added examples to documentation comments all over the code.
Updated [Conventions](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Conventions.md) to
include `Class Conventions`, `Testing Conventions`, `Documentation Conventions`
and `Commit Message Conventions`.

## Code Changes

### Major Changes

Added [material](https://github.com/bardobard/bardrix/blob/v0.0.5/Bardrix/include/bardrix/objects.h) to create materials
for objects.
Added abstract [shape](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix/include/bardrix/objects.h) class to
create shapes for objects; e.g sphere, plane,
triangle, etc.

Added [grayscale](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#color)
and [invert](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#color) to color.

Added [refraction](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#vector3)
and [reflection](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#vector3) to vector3.
Returning optional vector3.

### Minor Changes

Added `!=` operator to [ray](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#ray), for some
reason this was missing.

Updated [normalize](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#vector3) from `vector3`
to now return a reference to the changed
vector3. `void` -> `vector3&`. \
Updated [normalize](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#quaternion)
from `quaternion` to now return a reference to the changed
quaternion. `void` -> `quaternion&`.
Updated [conjugate](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#quaternion)
from `quaternion` to now return a reference to the changed
quaternion. `void` -> `quaternion&`. \
Updated [reciprocal](https://github.com/bardobard/bardrix/blob/v0.0.5/Docs/Bardrix_Reference.md#quaternion)
from `quaternion` to now return a reference to the changed
quaternion. `void` -> `quaternion&`.
