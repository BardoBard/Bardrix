# Introduction

Assuming you've read the [Installation](../../Installation.md) guide, you should have Bardrix installed on your system. This guide will help you get started with Bardrix by creating a simple project.

## 1. Understanding 3D space

Before we start, let's understand the 3D space. In Bardrix, the 3D space is represented by the `vector3` and the `point3` classes. These classes have three components: `x`, `y`, and `z`. \
The classes are defined in the `bardrix/` namespace, their function are different, and they are not interchangeable. \
One must include the following headers to use these classes:

```cpp
#include <iostream>
#include <bardrix/vector3.h>
#include <bardrix/point3.h>
```

Now, we can use them for some simple mathematical operations.

```cpp
bardrix::vector3 v1(1, 2, 3);
bardrix::vector3 v2(4, 5, 6);
bardrix::point3 p1(1, 2, 3);

std::cout << "v1: " << v1 << '\n';
std::cout << "v2: " << v2 << '\n';
std::cout << "p1: " << p1 << "\n\n";

// All of these operations are also valid inverted (e.g. 6 - v1)
std::cout << "v1 + v2: " << v1 + v2 << '\n';
std::cout << "v1 - v2: " << v1 - v2 << '\n';
std::cout << "v1 * 2: " << v1 * 2 << '\n';
std::cout << "v1 / 2: " << v1 / 2 << '\n';

// You're able to add a vector to a point, but not a point to a vector
std::cout << "\np1 + v1: " << p1 + v1 << "\n\n";
// std::cout << "v1 + p1: " << v1 + p1 << '\n'; // This will not work
```

```text
Output:
    v1: (1, 2, 3)
    v2: (4, 5, 6)
    p1: (1, 2, 3)
    
    v1 + v2: (5, 7, 9)
    v1 - v2: (-3, -3, -3)
    v1 * 2: (2, 4, 6)
    v1 / 2: (0.5, 1, 1.5)
    
    p1 + v1: (2, 4, 6)
```

As we can see, adding a vector to a point is invalid due to the different purposes of these classes. \
A vector represents a direction in 3D space, it's always relative to the origin (0, 0, 0). \
We can see an example of this below (0.5, 0.5, 1):

![vector_example.png](../../Images/vector_example.png)

A point in contrast represents a position in 3D space, it can be put anywhere but has no direction. \
We can see an example of this below (0.5, 0.5, 1):

![point_example.png](../../Images/point_example.png)

With these things in mind we can start understanding why some operations are only available for `vector3` objects, and not for `point3` objects. \
This makes sense, as the length, angle, etc. are operations that are only valid for vectors; you can't calculate the length of a point. \
It's important to make the distinction between vectors and points, as they have different purposes in 3D space.

## 2. Advanced operations

There are some more advanced operations that can be done with these classes, such as the dot product and cross product. \
You can always check the [Mathematics](../../Mathematics.md) guide for more information on these operations.

```cpp
std::cout << "v1 length: " << v1.length() << '\n';
std::cout << "v1 dot v2: " << v1.dot(v2) << '\n';
std::cout << "v1 cross v2: " << v1.cross(v2) << "\n\n";

std::cout << "v1 angle v2: " << v1.angle(v2) << '\n';
std::cout << "v1 angle v2 (degrees): " << bardrix::radians_to_degrees(std::acos(v1.angle(v2))) << "°\n";
std::cout << "v1 normalized: " << v1.normalized() << '\n';
```

```text
Output:
    v1: (1, 2, 3)
    v2: (4, 5, 6)
    p1: (1, 2, 3)

    v1 length: 3.74166
    v1 dot v2: 32
    v1 cross v2: (-3, 6, -3)
    
    v1 angle v2: 0.974632
    v1 angle v2 (degrees): 12.9332°
    v1 normalized: (0.267261, 0.534522, 0.801784)
```

# Next Steps

We've now covered the basics of 3D objects. \
The next steps would be to learn about `camera`, `ray`, `light` and `sphere` interactions. \
See [Raytracing](../Raytracing/README.md) where it teaches you how to use these classes in a simple raytracing application.