//
// Created by Bardio on 22/05/2024.
//

#include <iostream>
#include <bardrix/vector3.h>
#include <bardrix/point3.h>

int main(){

    //
    // Initialization
    //

    bardrix::vector3 v1(1, 2, 3);
    bardrix::vector3 v2(4, 5, 6);
    bardrix::point3 p1(1, 2, 3);

    std::cout << "v1: " << v1 << '\n';
    std::cout << "v2: " << v2 << '\n';
    std::cout << "p1: " << p1 << "\n\n";

    //
    // Basic operations
    //

    // All of these operations are also valid inverted (e.g. 6 - v1)
    std::cout << "v1 + v2: " << v1 + v2 << '\n';
    std::cout << "v1 - v2: " << v1 - v2 << '\n';
    std::cout << "v1 * 2: " << v1 * 2 << '\n';
    std::cout << "v1 / 2: " << v1 / 2 << '\n';

    // You're able to add a vector to a point, but not a point to a vector
    std::cout << "\np1 + v1: " << p1 + v1 << "\n\n";
    // std::cout << "v1 + p1: " << v1 + p1 << '\n'; // This will not work

    //
    // Advanced operations
    //

    std::cout << "v1 length: " << v1.length() << '\n';
    std::cout << "v1 dot v2: " << v1.dot(v2) << '\n';
    std::cout << "v1 cross v2: " << v1.cross(v2) << "\n\n";

    std::cout << "v1 angle v2: " << v1.angle(v2) << '\n';
    std::cout << "v1 angle v2 (degrees): " << bardrix::radians_to_degrees(std::acos(v1.angle(v2))) << "°\n";
    std::cout << "v1 normalized: " << v1.normalized() << '\n';

    return 0;
}