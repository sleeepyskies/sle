#pragma once

#include "ComponentManager.hpp"
#include "EntityManager.hpp"
#include "ISystem.hpp"
#include "SystemManager.hpp"
#include "Texture.hpp"

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
    Entity createEntity() { return m_entityManager.createEntity(); }
    /// @brief Destroys the given entity.
    void destroyEntity(Entity entity) { m_entityManager.destroyEntity(entity); }

    /// @brief Creates an internal relation between the Entity and the Component in the system.
    template <typename T> void registerComponent(Entity &entity, const T &component) {
        m_entityManager.assignComponent(entity, component.type());
        m_componentManager.registerComponent<T>(entity, component);
    }
    /// @brief Deletes the relation between the entity and the component of type T.
    template <typename T> void unregisterComponent(Entity &entity, ComponentType type) {
        m_entityManager.removeComponent(entity, type);
        m_componentManager.unregisterComponent<T>(entity);
    }
    /// @brief Gets the component of type T associated with this entity.
    template <typename T> T &getComponent(Entity entity) { return m_componentManager.getComponent<T>(entity); }

    /// @brief Registers a system to be active.
    template <typename T> ref<ISystem> registerSystem() { return m_systemManager.registerSystem<T>(); }
    /// @brief Unregisters a system.
    template <typename T> void unregisterSystem() { m_systemManager.unregisterSystem<T>(); }

private:
    EntityManager m_entityManager;
    ComponentManager m_componentManager;
    SystemManager m_systemManager;

    std::vector<ref<Texture>> m_textures;
};

} // namespace sle
