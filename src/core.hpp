#pragma once

#include <glm/vec4.hpp>
#include <memory>
#include "core.hpp"

namespace sle {
/// @brief A shared pointer for a given type.
template <typename T> using ref = std::shared_ptr<T>;

/// @brief A shared const pointer for a given type.
template <typename T> using cref = std::shared_ptr<const T>;

/// @brief A weak pointer for a given type.
template <typename T> using wref = std::weak_ptr<T>;

/// @brief An RGBA color represented as a 4D vector
using Color = glm::u8vec4;

/// @brief An optional return value.
template <typename T> using maybe = std::optional<T>;

} // namespace sle
