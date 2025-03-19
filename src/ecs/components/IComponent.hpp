#pragma once
#include "types.hpp"

namespace sle {
/// @brief The base Component class that all other Components must implement.
struct IComponent {
    ComponentID id = 0;
};
} // namespace  sle
