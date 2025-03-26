#include "SystemManager.hpp"

namespace sle {

template <typename T> ref<ISystem> SystemManager::registerSystem() {
    SLE_ASSERT(!m_registeredSystems.contains(index<T>()), "This System is already registered.");

    auto system                     = std::make_shared<T>();
    m_registeredSystems[index<T>()] = system;
    return system;
}

template <typename T> void SystemManager::unregisterSystem() {
    SLE_ASSERT(m_registeredSystems.contains(index<T>()), "This System is not yet registered.");

    m_registeredSystems.erase(index<T>());
}

} // namespace sle
