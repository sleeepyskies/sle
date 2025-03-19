#pragma once

#include "ComponentManager.hpp"
#include <vector>

namespace sle {

class IComponentList {
public:
    virtual ~IComponentList()                          = default;
    virtual ref<IComponent> getComponent(size_t index) = 0;
};

/**
 * @brief Used to represent a contiguous block of components of the same type.
 */
template <typename T> class ComponentList : public IComponentList {
public:
    /// @brief Allows an inserting at the back of the array.
    size_t insert(const T component) {
        SLE_ASSERT(m_list.size() < MAX_ENTITIES, "Cannot have anymore Components of this type.");
        m_list.emplace_back(component);

        return m_list.size() - 1;
    }

    /// @brief Allows deletion via index. Also swaps the deleted element with the last element.
    /// Also returns the ID of the component that was swapped.
    [[nodiscard]] ComponentID remove(const size_t index) {
        SLE_ASSERT(index < m_list.size() + 1, "Cannot remove this component due to out of bounds indexing.");
        m_list[index] = m_list[m_list.size() - 1];
        m_list.pop_back();
        return m_list[index].id;
    }

    /// @brief Returns a pointer to the component at the given index.
    ref<IComponent> getComponent(size_t index) override { return std::make_shared<T>(m_list[index]); }

private:
    std::vector<ref<T>> m_list{};
    hashmap<ComponentID, size_t> m_componentToIndex{};
};

} // namespace sle
