#include "Scene.hpp"

namespace sle {

Entity Scene::createEntity() { return m_entityManager.createEntity(); }

void Scene::destroyEntity(Entity entity) { m_entityManager.destroyEntity(entity); }

template <typename T> void Scene::registerComponent(Entity &entity, const IComponent &component) {
    m_entityManager.assignComponent(entity, component.type());
    m_componentManager.registerComponent<T>(entity, component);
}

template <typename T> void Scene::unregisterComponent(Entity &entity, ComponentType type) {
    m_entityManager.removeComponent(entity, type);
    m_componentManager.unregisterComponent<T>(entity);
}

template <typename T> ref<T> Scene::getComponent(Entity entity) { return m_componentManager.getComponent<T>(entity); }

template <typename T> ref<ISystem> Scene::registerSystem() { return m_systemManager.registerSystem<T>(); }

template <typename T> void Scene::unregisterSystem() { m_systemManager.unregisterSystem<T>(); }

} // namespace sle
