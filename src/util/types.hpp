#pragma once

#include "optional"
#include <glm/vec4.hpp>
#include <memory>
#include <bitset>
#include <limits>

#include <unordered_map>

namespace sle {
/// @brief A shared pointer for a given type.
template <typename T> using ref = std::shared_ptr<T>;

/// @brief A shared const pointer for a given type.
template <typename T> using cref = std::shared_ptr<const T>;

/// @brief A weak pointer for a given type.
template <typename T> using wref = std::weak_ptr<T>;

/// @brief A weak pointer for a given type.
template <typename T> using uref = std::unique_ptr<T>;

/// @brief An RGBA color represented as a 4D vector
using Color = glm::u8vec4;

/// @brief An optional return value.
template <typename T> using maybe = std::optional<T>;

/// @brief A hash map aka std::unordered_map
template <typename K, typename V> using hashmap = std::unordered_map<K, V>;

// ----------------- ECS ------------------
constexpr int MAX_COMPONENTS = 32;
constexpr int MAX_ENTITIES   = 1000;
constexpr std::size_t INVALID_INDEX = std::numeric_limits<std::size_t>::max();
using EntityID               = uint32_t;
using ComponentID            = uint32_t;
using ComponentMask          = std::bitset<MAX_COMPONENTS>;

} // namespace sle
