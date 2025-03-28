#pragma once
#include "types.hpp"

namespace sle {

/**
 * @brief This class is used by components to make sure they receive a unique ID without much overhead. Note that an id
 * of 0 is considered invalid.
 */
class ComponentIDProvider {
public:
    ComponentIDProvider()  = default;
    ~ComponentIDProvider() = default;

    static ComponentID id() { return s_currentId++; }

private:
    static inline ComponentID s_currentId = 1;
};

} // namespace sle
