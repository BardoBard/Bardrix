//
// Created by Bard on 29/02/2024.
//

#pragma once

#include <type_traits>
#include <ostream>
#include <cmath>
#include <cstdint>
#include <utility>
#include <optional>
#include <climits>
#include <algorithm>
#include <memory>
#include <functional>

// C++20 feature
#if __cplusplus > 201703L
    #define UNLIKELY [[unlikely]]
    #define LIKELY [[likely]]
#else
    #define UNLIKELY
    #define LIKELY
#endif

#define NODISCARD [[nodiscard]]
#define INLINE inline

namespace bardrix {
    enum class axis : std::uint8_t {
        none    = 0x00, // No axis
        x       = 0x01, // 1st dimension
        y       = 0x02, // 2nd dimension
        z       = 0x04, // 3rd dimension
        w       = 0x08, // 4th dimension
    };
}

#include <bardrix/math.h>
