#pragma once

#include "IComponent.hpp"
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
    /// @brief Inserts a Component into the array, returns the index at which it was inserted.
    [[nodiscard]] size_t insert(const T component) {
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

    /// @brief Checks whether this Component exists in the list or not.
    bool contains(const ComponentID id) const { return m_componentToIndex.contains(id); }
    /// @brief Returns the index the given ComponentID is stored at.
    size_t indexOf(const ComponentID id) const { return m_componentToIndex.at(id); }

    /// @brief Returns a pointer to the component at the given index.
    ref<IComponent> getComponent(size_t index) override { return m_list[index]; }

    /// @brief Returns an iterator begin over the dense list.
    ref<IComponent> begin() { return m_list.begin(); }
    /// @brief Returns an iterator end over the dense list.
    ref<IComponent> end() { return m_list.end(); }

private:
    /// @brief The dense block of Components.
    std::vector<ref<T>> m_list{};
    /// @brief A mapping of @ref ComponentID to its index in the list. Can also be used to test if
    /// the IComponent exists in the list.
    hashmap<ComponentID, size_t> m_componentToIndex{};
};

} // namespace sle
