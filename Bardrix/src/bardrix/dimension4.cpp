//
// Created by Bard on 13/03/2024.
//

#include <bardrix/dimension4.h>

namespace bardrix{

    std::ostream& operator<<(std::ostream& os, const dimension4& dimension4) {
        return dimension4.print(os);
    }

    double& dimension4::operator[](axis axis) {
        switch (axis) {
            case axis::x:
                return x;
            case axis::y:
                return y;
            case axis::z:
                return z;
            case axis::w:
                return w;
            default:
                throw std::invalid_argument("Invalid axis");
        }
    }
}