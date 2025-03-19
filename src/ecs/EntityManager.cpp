#include "EntityManager.hpp"

namespace sle {

/// @brief Creates a new Entity with the first available ID, if there are any available.
Entity EntityManager::createEntity() {
    SLE_ASSERT(m_entityCount < MAX_ENTITIES, "Cannot create anymore entities! Max number has already been reached");

    m_entityCount++;
    if (m_unusedIDs.empty())
        return Entity{ m_entityCount - 1 };
    EntityID id = m_unusedIDs.front();
    m_unusedIDs.pop();
    return Entity{ m_unusedIDs.front() };
}

/// @brief Destroys the given entity and frees up its ID for use.
void EntityManager::destroyEntity(Entity entity) {
    SLE_ASSERT(entity.id <= m_entityCount, "Cannot destroy entity with invalid ID!");

    m_unusedIDs.push(entity.id);
    m_entityCount--;
}

/**
 * @brief Updates the given entities bitmask to correspond with its new component type.
 * @returns true on success, false otherwise.
 */
template <typename T> bool EntityManager::assignComponent(Entity &entity) {
    const size_t pos = ComponentTypeID::getComponentTypeID<T>();
    if (entity.mask.test(pos))
        return false;
    entity.mask.flip(pos);
    return true;
}

/**
 * @brief Removes the given entities bitmask corresponding with the component type.
 * @returns true on success, false otherwise.
 */
template <typename T> bool EntityManager::removeComponent(Entity &entity) {
    const size_t pos = ComponentTypeID::getComponentTypeID<T>();
    if (!entity.mask.test(pos))
        return false;
    entity.mask.flip(pos);
    return true;
}

} // namespace sle
