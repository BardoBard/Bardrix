//
// Created by Bard on 13/03/2024.
//

#include <bardrix/dimension3.h>

namespace bardrix{

    std::ostream& operator<<(std::ostream& os, const dimension3& dimension3) {
        return dimension3.print(os);
    }

    double& dimension3::operator[](axis axis) {
        switch (axis) {
            case axis::x:
                return x;
            case axis::y:
                return y;
            case axis::z:
                return z;
            default:
                throw std::invalid_argument("Invalid axis");
        }
    }
}