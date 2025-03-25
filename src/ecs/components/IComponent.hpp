#pragma once
#include "types.hpp"

namespace sle {

enum class ComponentType {
    TEXTURE_COMPONENT = 0
    // ...
};

/// @brief The base Component class that all other Components must implement.
struct IComponent {
    ComponentID id                     = 0;
    virtual ~IComponent()              = default;
    virtual ComponentType type() const = 0;
};
} // namespace  sle
