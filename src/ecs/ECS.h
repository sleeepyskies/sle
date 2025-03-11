#pragma once

#include <cstdint>
#include <bitset>

constexpr int MAX_ENTITIES = 32;
using EntityID = uint32_t;
using ComponentMask = std::bitset<MAX_ENTITIES>;

namespace sle {

struct Entity {
    EntityID id;
    ComponentMask mask;
};



class Scene {
    EntityManager em;
};


} // namespace sle

