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
void EntityManager::destroyEntity(const Entity entity) {
    SLE_ASSERT(entity.id <= m_entityCount, "Cannot destroy entity with invalid ID!");

    m_unusedIDs.push(entity.id);
    m_entityCount--;
}

/**
 * @brief Updates the given entities bitmask to correspond with its new component type.
 * @returns true on success, false otherwise.
 */
void EntityManager::assignComponent(Entity &entity, ComponentType type) const {
    const auto pos = static_cast<size_t>(type);
    SLE_ASSERT(entity.mask.test(pos), "This entity already has this component assigned.");
    entity.mask.flip(pos);
}

/**
 * @brief Removes the given entities bitmask corresponding with the component type.
 * @returns true on success, false otherwise.
 */
void EntityManager::removeComponent(Entity &entity, ComponentType type) const {
    const auto pos = static_cast<size_t>(type);
    SLE_ASSERT(!entity.mask.test(pos), "This entity already has this component assigned.");
    entity.mask.flip(pos);
}

} // namespace sle
