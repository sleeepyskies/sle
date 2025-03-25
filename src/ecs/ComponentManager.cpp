#include "ComponentManager.hpp"

namespace sle {

template<typename T>
void ComponentManager::registerComponent(const Entity entity, const IComponent &component) {
    SLE_ASSERT(!hasComponent<T>(entity), "This entity already has a component of this type.");

    ref<ComponentList<T> > list = getList<T>();
    size_t insertedIndex;
    if (list->contains(component.id)) {
        insertedIndex = list->indexOf(component.id);
    } else {
        insertedIndex = list->insert(component);
    }
    m_entityToComponentIndex[entity.id][index<T>()] = insertedIndex;
    m_componentToEntities[component.id].insert(entity.id);
}

template<typename T>
void ComponentManager::unregisterComponent(const Entity entity) {
    SLE_ASSERT(hasComponent<T>(entity), "This entity doesnt have a component of this type.");

    ref<ComponentList<T> > list = getList<T>();
    const size_t insertedIndex = m_entityToComponentIndex[entity.id][index<T>()];
    const ref<IComponent> component = getComponent<T>(insertedIndex);
    if (m_componentToEntities[component->id].size() > 1) {
        // many entities have this
        m_componentToEntities[component->id].erase(entity.id);
    } else {
        // only 1
        m_entityToComponentIndex[entity.id][index<T>()] = INVALID_INDEX;
        list->remove(insertedIndex);
        m_componentToEntities[component->id].erase(entity.id);
    }
}

/// @brief Gets the component of type T associated with the given entity.
template<typename T>
ref<T> ComponentManager::getComponent(const Entity entity) {
    SLE_ASSERT(hasComponent<T>(entity), "This entity does not have the given component type.");
    const ref<ComponentList<T> > list = getList<T>();
    const size_t insertedIndex = m_entityToComponentIndex[entity.id][index<T>()];
    return list->getComponent(insertedIndex);
}

} // sle