#include "SystemManager.hpp"

namespace sle {

template <typename T> ref<ISystem> SystemManager::registerSystem() {
    SLE_ASSERT(!m_registeredComponents.contains(index<T>()), "This System is already registered.");

    auto system                        = std::make_shared<T>();
    m_registeredComponents[index<T>()] = system;
    return system;
}

/// @brief Registers and returns a pointer to the new system. There may only be one system of a
/// type active at a time, since systems of the same type have the same functionality anyway.
template <typename T> void SystemManager::unregisterSystem() {
    SLE_ASSERT(m_registeredComponents.contains(index<T>()), "This System is not yet registered.");

    m_registeredComponents.erase(index<T>());
}

} // namespace sle
