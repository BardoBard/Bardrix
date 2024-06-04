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

#include <bardrix/math.h>
