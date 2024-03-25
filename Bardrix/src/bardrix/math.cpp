//
// Created by Bard on 19/03/2024.
//

#include <bardrix/math.h>

namespace bardrix {

    bool nearly_equal(double lhs, double rhs) noexcept {
        return std::abs(lhs - rhs) <= epsilon;
    }

    bool greater_than_or_nearly_equal(double lhs, double rhs) noexcept {
        return lhs > rhs || nearly_equal(lhs, rhs);
    }

    bool less_than_or_nearly_equal(double lhs, double rhs) noexcept {
        return lhs < rhs || nearly_equal(lhs, rhs);
    }

} // namespace bardrix