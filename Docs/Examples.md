# Examples

In this section we'll provide explanations and examples of how to use the library.

## 1. Example: Basic Usage

Within this library `vector3` and `point3` are provided, which are used to represent 3D vectors and points respectively.
The following example demonstrates how to use these classes.

```cpp
#include <iostream>
#include <bardrix/vector3.h>
#include <bardrix/point3.h>
```

```cpp
bardrix::vector3 v1(1, 2, 3);
bardrix::vector3 v2(4, 5, 6);
bardrix::point3 p1(1, 2, 3);
bardrix::point3 p2(4, 5, 6);

std::cout << "v1: " << v1 << '\n';
std::cout << "v2: " << v2 << '\n';
std::cout << "p1: " << p1 << '\n';
std::cout << "p2: " << p2 << '\n';
```

You'll be able to do basic mathematical operations with these classes, such as addition, subtraction, multiplication and division.

```cpp
bardrix::vector3 v1(1, 2, 3);
bardrix::vector3 v2(4, 5, 6);
bardrix::point3 p1(1, 2, 3);

// All of these operations are also valid inverted (e.g. 6 - v1)
std::cout << "v1 + v2: " << v1 + v2 << '\n';
std::cout << "v1 - v2: " << v1 - v2 << '\n';
std::cout << "v1 * 2: " << v1 * 2 << '\n';
std::cout << "v1 / 2: " << v1 / 2 << '\n';

// You're able to add a vector to a point, but not a point to a vector
std::cout << "\np1 + v1: " << p1 + v1 << '\n';
// std::cout << "v1 + p1: " << v1 + p1 << '\n'; // This will not compile
```

There are some more advanced operations that can be done with these classes, such as the dot product and cross product.

```cpp
bardrix::vector3 v1(1, 2, 3);
bardrix::vector3 v2(4, 5, 6);

std::cout << "v1 length: " << v1.length() << '\n';
std::cout << "v2 normalized: " << v2.normalized() << '\n';

// Note that the angle is between [-1, 1], if you want to convert it to degrees
// You can use std::acos(angle) * 180 / pi (or bardrix::radians_to_degrees(std::acos(angle)))
const double angle = v1.angle(v2);
std::cout << "v1 angle to v2: " << angle << '\n';
std::cout << "angle in degrees: " << bardrix::radians_to_degrees(std::acos(angle)) << '\n';

std::cout << "\nv1 dot v2: " << v1.dot(v2) << '\n';
std::cout << "v1 cross v2: " << v1.cross(v2) << '\n';
```

These operations are only available for `vector3` objects, and not for `point3` objects. \
This makes sense, as the dot product and cross product are operations that are only valid for vectors. \
It's important to make the distinction between vectors and points, as they have different purposes in 3D space.

Here are some examples of how to use the `point3` class.

```cpp
bardrix::point3 p1(1, 2, 3);
bardrix::point3 p2(4, 5, 6);

std::cout << "p1 distance -> p2: " << p1.distance(p2) << '\n';
std::cout << "p1 midpoint -> p2: " << p1.midpoint(p2) << '\n';
std::cout << "p1 vector -> p2: " << p1.vector_to(p2) << '\n';
```

A point must generally be used as a position in 3D space, and a vector must be used as a direction in 3D space. \
This distinction is important, as it will help you understand how to use these classes in your raytracing applications.

## 2. Example: Raytracing

Raytracing is a technique to render realistic scenes by simulating the way light interacts with objects in a scene. \
You'd need a `camera` object to start raytracing, which is provided by this library.

```cpp
#include <bardrix/camera.h>
```

```cpp
// Initialization
bardrix::vector3 direction(0, 0, 1); // Forward
bardrix::point3 position(0, 0, 0); // Origin
unsigned fov = 90; // 90 degrees
int width = 800;
int height = 600;
int distance = 10;

bardrix::camera cam(position, direction, width, height, fov);

// Now we can use the camera
std::cout << *cam.shoot_ray(width / 2, height / 2, distance) << '\n';

cam.look_at(bardrix::point3(1, 2, 3));
std::cout << "Look at (1, 2, 3); new direction:" << cam.get_direction() << '\n';
```