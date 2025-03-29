#pragma once

#include "optional"
#include <glm/vec4.hpp>
#include <memory>
#include <bitset>
#include <limits>

#include <unordered_map>
#include <unordered_set>

namespace sle {
/// @brief A shared pointer for a given type.
template <typename T> using ref = std::shared_ptr<T>;
template <typename T, typename... Args>
ref<T> makeRef(Args&&... args) {
    return std::make_shared<T>(std::forward<Args>(args)...);
}

/// @brief A shared const pointer for a given type.
template <typename T> using cref = std::shared_ptr<const T>;
template <typename T, typename... Args>
cref<T> makeCref(Args&&... args) {
    return std::make_shared<const T>(std::forward<Args>(args)...);
}

/// @brief A weak pointer for a given type.
template <typename T> using wref = std::weak_ptr<T>;

/// @brief A weak pointer for a given type.
template <typename T> using uref = std::unique_ptr<T>;
template <typename T, typename... Args>
uref<T> makeUref(Args&&... args) {
    return std::make_unique<T>(std::forward<Args>(args)...);
}

/// @brief An RGBA color represented as a 4D vector
using Color = glm::u8vec4;

/// @brief An optional return value.
template <typename T> using maybe = std::optional<T>;

/// @brief A hash map aka std::unordered_map
template <typename K, typename V> using hashmap = std::unordered_map<K, V>;

/// @brief A hash set aka std::unordered_set
template <typename K> using hashset = std::unordered_set<K>;

// ----------------- ECS ------------------
constexpr int MAX_COMPONENTS = 32;
constexpr int MAX_ENTITIES   = 1000;
using EntityID               = uint32_t;
using ComponentID            = uint32_t;
using ComponentMask          = std::bitset<MAX_COMPONENTS>;
constexpr ComponentID INVALID_ID = std::numeric_limits<uint32_t>::max();

} // namespace sle
