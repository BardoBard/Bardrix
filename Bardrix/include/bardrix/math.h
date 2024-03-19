//
// Created by Bard on 19/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {

    /// \brief (180 / pi) constant, used for converting radians to degrees
    INLINE constexpr double M_180_PI = 57.295779513082323;

    /// \brief (pi / 180) constant, used for converting degrees to radians
    INLINE constexpr double M_PI_180 = 0.017453292519943295;

    /// \brief Converts degrees to radians
    /// \param degrees The degrees to convert
    /// \return The degrees in radians
    double degrees_to_radians(double degrees) noexcept;

    /// \brief Converts radians to degrees
    /// \param radians The radians to convert
    /// \return The radians in degrees
    double radians_to_degrees(double radians) noexcept;

} // namespace bardrix
