#pragma once

#include "EntityManager.hpp"

namespace sle {

/**
 * @brief The Scene class acts as an API for the Entity-Component-System in sle. It manages the lifetime
 * of all ECS related objects, and allows for creation, deletion and updating of these objects.
 */
class Scene {
public:
    Scene()
        : m_entityManager(EntityManager()), m_componentManager(ComponentManager()), m_systemManager(SystemManager()) {}
    ~Scene() = default;

    /// @brief Create and return a brand-new @ref Entity.
    Entity createEntity();
    /// @brief Destroys the given entity.
    void destroyEntity(Entity entity);

    /// @brief Creates an internal relation between the Entity and the Component in the system.
    template <typename T> void registerComponent(Entity &entity, const IComponent &component);
    /// @brief Deletes the relation between the entity and the component of type T.
    template <typename T> void unregisterComponent(Entity &entity, const ComponentType type);
    /// @brief Gets the component of type T associated with this entity.
    template <typename T> ref<T> getComponent(Entity entity);

    /// @brief Registers a system to be active.
    template <typename T> ref<ISystem> registerSystem();
    /// @brief Unregisters a system.
    template <typename T> void unregisterSystem();

private:
    EntityManager m_entityManager;
    ComponentManager m_componentManager;
    SystemManager m_systemManager;
};

} // namespace sle
