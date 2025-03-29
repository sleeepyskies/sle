#pragma once

#include "Entity.hpp"
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

    /// @brief Registers the given component to the given entity.
    template <typename T> void registerComponent(const Entity entity, const T &component) {
        SLE_ASSERT(!hasComponent<T>(entity), "This entity already has a component of this type.");

        ComponentList<T> &list = getList<T>();
        if (!list.contains(component.id)) {
            list.insert(component);
        }
        m_entityToComponentID[entity.id][index<T>()] = component.id;
        m_componentToEntities[component.id].insert(entity.id);
    }

    /// @brief Unregisters the given component to the given entity.
    template <typename T> void unregisterComponent(const Entity entity) {
        SLE_ASSERT(hasComponent<T>(entity), "This entity doesnt have a component of this type.");

        const T& component = getComponent<T>(entity);
        m_componentToEntities[component.id].erase(entity.id);
        m_entityToComponentID[entity.id][index<T>()] = INVALID_ID;
        if (m_componentToEntities[component.id].size() <= 1) {
            ComponentList<T> &list = getList<T>();
            list.remove(component.id);
        }
    }

    /// @brief Returns a list reference of type T.
    template <typename T> ComponentList<T> &getList() {
        const std::type_index index = this->index<T>();
        if (!m_components.contains(index)) {
            m_components[index] = makeRef<ComponentList<T>>();
        }
        return static_cast<ComponentList<T> &>(*m_components.at(index));
    }

    /// @brief Gets the component of type T associated with the given entity.
    template <typename T> T &getComponent(const Entity entity) {
        SLE_ASSERT(hasComponent<T>(entity), "This entity does not have the given component type.");

        ComponentList<T> list = getList<T>();
        const ComponentID cid = m_entityToComponentID[entity.id][index<T>()];
        return list.getComponent(cid);
    }

    // ------------- PRIVATE FUNCTIONS ---------------
private:
    /// @brief Checks if the entity has this component type. A ComponentID of 0 is invalid, so we just cast this to a
    /// boolean.
    template <typename T> bool hasComponent(const Entity &entity) {
        return static_cast<bool>(m_entityToComponentID[entity.id][index<T>()]);
    }

    /// @brief Returns the hashmap index for checking which components an entity has.
    template <typename T> [[nodiscard]] std::type_index index() const { return std::type_index(typeid(T)); }

    // ------------- MEMBER VARIABLES ---------------
private:
    /// @brief The dense blocks of components. Uses class as lookup.
    hashmap<std::type_index, ref<IComponentList>> m_components{};
    /// @brief A map of EntityID to its ComponentID.
    hashmap<EntityID, hashmap<std::type_index, ComponentID>> m_entityToComponentID{};
    /// @brief Map of ComponentID to all Entities who had this component
    hashmap<ComponentID, hashset<EntityID>> m_componentToEntities{};
};
} // namespace sle
