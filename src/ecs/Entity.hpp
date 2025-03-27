#pragma once

#include "types.hpp"

namespace sle {

/**
 * @brief An Entity in sle is just an unsigned 32-bit integer id, as well as a component mask
 * representing which components this entity has.
 */
struct Entity {
    EntityID id = 0;
    ComponentMask mask{};

    explicit Entity(const EntityID id) : id(id){};
};

} // namespace sle
