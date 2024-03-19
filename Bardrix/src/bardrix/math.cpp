//
// Created by Bard on 19/03/2024.
//

#include <bardrix/math.h>

namespace bardrix {

    double degrees_to_radians(double degrees) noexcept {
        return degrees * M_PI_180;
    }

    double radians_to_degrees(double radians) noexcept {
        return radians * M_180_PI;
    }

} // namespace bardrix