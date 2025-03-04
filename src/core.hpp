#pragma once

#include <memory>

namespace sle {
/// @brief A shared pointer for a given type.
template <typename T> using ref = std::shared_ptr<T>;

/// @brief A shared const pointer for a given type.
template <typename T> using cref = std::shared_ptr<const T>;

/// @brief A weak pointer for a given type.
template <typename T> using wref = std::weak_ptr<T>;
}
