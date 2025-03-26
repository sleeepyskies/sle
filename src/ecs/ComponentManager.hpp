#pragma once

#include "EntityManager.hpp"
#include "IComponent.hpp"
#include "IComponentList.hpp"
#include "assert.hpp"
#include "ecs.hpp"
#include "types.hpp"
#include <set>
#include <typeindex>

namespace sle {
struct Entity;

/**
 * @brief The ComponentManager is responsible for managing which exact Components belong to which
 * Entities. Furthermore, it provides dense lists of each component type.
 */
class ComponentManager {
public:
    ComponentManager()  = default;
    ~ComponentManager() = default;

    /**
     * @brief Registers the given component to the given entity. Caller must ensure entity does not already have this
     * type of component.
     */
    template <typename T> void registerComponent(Entity entity, const IComponent &component);
    /**
     * @brief Unregisters the given component to the given entity. Caller must ensure entity does not already have this
     * type of component.
     */
    template <typename T> void unregisterComponent(Entity entity);

    /// @brief Returns the list of all active components of this type.
    template <typename T> ComponentList<T> &getComponentList() const { return getList<T>(); }

    /// @brief Gets the component of type T associated with the given entity.
    template <typename T> ref<T> getComponent(Entity entity);

    // ------------- PRIVATE FUNCTIONS ---------------
private:
    template <typename T> bool hasComponent(const Entity &entity) {
        return m_entityToComponentIndex[entity.id][index<T>()] != INVALID_INDEX;
    }

    template <typename T> ref<ComponentList<T>> getList() const {
        return static_cast<ComponentList<T>>(m_components[index<T>()]);
    }

    template <typename T> [[nodiscard]] std::type_index index() const { return std::type_index(typeid(T)); }

    // ------------- MEMBER VARIABLES ---------------
private:
    /// @brief The dense blocks of components. Uses class as lookup.
    hashmap<std::type_index, ref<IComponentList>> m_components{};
    /// @brief A map of EntityID to its index for each component list.
    hashmap<EntityID, hashmap<std::type_index, size_t>> m_entityToComponentIndex{};
    /// @brief Map of ComponentID to all Entities who had this component
    hashmap<ComponentID, hashset<EntityID>> m_componentToEntities{};
};
} // namespace sle
