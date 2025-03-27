#pragma once

#include "types.hpp"

namespace sle {

enum class ComponentType {
    TEXTURE_COMPONENT = 0,
    POSITION_COMPONENT = 1
    // ...
};

/// @brief The base Component class that all other Components must implement.
struct IComponent {
    ComponentID id                     = 0;
    explicit IComponent(const ComponentID id) : id(id) {}
    virtual ~IComponent()              = default;
    virtual ComponentType type() const = 0;
};
} // namespace  sle
