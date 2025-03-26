#pragma once

#include "assert.hpp"
#include "systems/ISystem.h"
#include "types.hpp"
#include <set>
#include <typeindex>

namespace sle {

class SystemManager {
public:
    SystemManager()  = default;
    ~SystemManager() = default;

    /// @brief Registers and returns a pointer to the new system. There may only be one system of a
    /// type active at a time, since systems of the same type have the same functionality anyway.
    template <typename T> ref<ISystem> registerSystem();

    /// @brief Registers and returns a pointer to the new system. There may only be one system of a
    /// type active at a time, since systems of the same type have the same functionality anyway.
    template <typename T> void unregisterSystem();

private:
    template <typename T> [[nodiscard]] std::type_index index() const { return std::type_index(typeid(T)); }

private:
    hashmap<std::type_index, ref<ISystem>> m_registeredSystems{};
};

} // namespace sle
