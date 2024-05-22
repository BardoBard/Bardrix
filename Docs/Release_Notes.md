# [v0.2.0](https://github.com/BardoBard/Bardrix/releases/tag/v0.2.0)

## Overview

## Code Changes

### Major Changes

### Minor Changes

Small compiler compatibility issues fixed in Raytracer [Example](Examples/Raytracing/README.md).

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