#pragma once
#include "EntityManager.hpp"
#include "IComponentList.hpp"
#include "assert.hpp"
#include "ecs.hpp"

#include <SDL_image.h>
#include <set>
#include <typeindex>

namespace sle {
struct Entity;

/**
 * @brief The ComponentManager is responsible for managing which exact Components belong to which
 * Entities. Furthermore, they provide lists of
 */
class ComponentManager {

public:
    ComponentManager()  = default;
    ~ComponentManager() = default;

    /**
     * @brief Registers the given component to the given entity. Caller must ensure entity does not already have this
     * type of component.
     */
    template <typename T> void registerComponent(const Entity entity, const IComponent &component) {
        SLE_ASSERT(!hasComponentBit<T>(entity), "This entity already has a component of this type.");
    }

    /**
     * @brief Unregisters the given component to the given entity. Caller must ensure entity does not already have this
     * type of component.
     */
    template <typename T> void unregisterComponent(const Entity entity) {
        SLE_ASSERT(hasComponentBit<T>(entity), "This entity doesnt have a component of this type.");
    }

    /// @brief Cleans up the given component. Must not be in use by any entities. Use getAllEntities() to clean this up.
    template <typename T> void destroyComponent(IComponent &component) {
        SLE_ASSERT(getAllEntities(component).empty(), "This component still has associated entities.");
    }

    /// @brief Returns the list of all active components of this type.
    template <typename T> ComponentList<T> &getComponentList() const { return getList<T>(); }

    /// @brief Gets the component of type T associated with the given entity.
    template <typename T> T &getComponent(Entity entity) {
        SLE_ASSERT(hasComponentBit<T>(entity), "This entity does not have the given component type.");
    }

    /// @brief Gets all components associated with this entity
    std::vector<ref<IComponent>> getAllComponents(const Entity entity) const {
        std::vector<ref<IComponent>> components{};
    }

    /// @brief Gets all entity ID's that have this component.
    std::set<EntityID> getAllEntities(const IComponent &component) const {
        SLE_ASSERT(m_componentToEntity.contains(component.id), "The given component does not exist.");
        return m_componentToEntity.at(component.id);
    }

    // ------------- PRIVATE FUNCTIONS ---------------
private:

    // ------------- MEMBER VARIABLES ---------------
private:
    /// @brief The dense blocks of components. Uses class as lookup.
    hashmap<std::type_index, ref<IComponentList>> m_components{};
    /// @brief A map of EntityID to its index for each component list.
    hashmap<EntityID, std::array<size_t, MAX_COMPONENTS>> m_entityToComponentIndex{};
    /// @brief A map of ComponentID to all Entity IDs associated with it.
    hashmap<ComponentID, std::set<EntityID>> m_componentToEntity{};
};

} // namespace sle
