//
// Created by Bard on 19/03/2024.
//

#pragma once

#include <bardrix/bardrix.h>

namespace bardrix {

    /// \brief The pi constant
    INLINE constexpr double pi = 3.14159265358979323846;

    /// \brief The pi/2 constant
    INLINE constexpr double _pi_2 = 1.57079632679489661923;

    /// \brief The pi/4 constant
    INLINE constexpr double _pi_4 = 0.78539816339744830962;

    /// \brief The 1/pi constant
    INLINE constexpr double _1_pi = 0.31830988618379067154;

    /// \brief The 2/pi constant
    INLINE constexpr double _2_pi = 0.63661977236758134308;

    /// \brief (180 / pi) constant, used for converting radians to degrees
    INLINE constexpr double _180_pi = 57.295779513082323;

    /// \brief (pi / 180) constant, used for converting degrees to radians
    INLINE constexpr double _pi_180 = 0.017453292519943295;

    /// \brief The epsilon value used for the nearly equal functions
    INLINE double epsilon = 0.0001;

    /// \brief Converts degrees to radians
    /// \param degrees The degrees to convert
    /// \return The degrees in radians
    /// \tparam T The type of the degrees, e.g. int, float, double, etc.
    /// \details T must be an arithmetic type, (https://en.cppreference.com/w/cpp/types/is_arithmetic)
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    double degrees_to_radians(T degrees) noexcept {
        return degrees * _pi_180;
    }

    /// \brief Converts radians to degrees
    /// \param radians The radians to convert
    /// \return The radians in degrees
    /// \tparam T The type of the radians, e.g. int, float, double, etc.
    /// \details T must be an arithmetic type, (https://en.cppreference.com/w/cpp/types/is_arithmetic)
    template<typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    double radians_to_degrees(T radians) noexcept {
        return radians * _180_pi;
    }

    /// \brief Checks if the number is nearly equal to another number
    /// \param lhs The first number
    /// \param rhs The second number
    /// \return True if the numbers are nearly equal, false otherwise
    /// \details It uses the epsilon value to check if the numbers are nearly equal
    NODISCARD bool nearly_equal(double lhs, double rhs) noexcept;

    /// \brief Checks if the number is greater than or nearly equal to another number
    /// \param lhs The first number
    /// \param rhs The second number
    /// \return True if the first number is greater than or nearly equal to the second number, false otherwise
    /// \details It uses the epsilon value to check if the numbers are nearly equal
    NODISCARD bool greater_than_or_nearly_equal(double lhs, double rhs) noexcept;

    /// \brief Checks if the number is less than or nearly equal to another number
    /// \param lhs The first number
    /// \param rhs The second number
    /// \return True if the first number is less than or nearly equal to the second number, false otherwise
    /// \details It uses the epsilon value to check if the numbers are nearly equal
    NODISCARD bool less_than_or_nearly_equal(double lhs, double rhs) noexcept;

} // namespace bardrix