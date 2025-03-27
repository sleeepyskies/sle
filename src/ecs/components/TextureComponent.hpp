#pragma once

#include "IComponent.hpp"

namespace sle {

struct TextureComponent : IComponent {
    size_t textureIndex;

    explicit TextureComponent(const ComponentID id, const size_t textureIndex)
    : IComponent(id), textureIndex(textureIndex) {}
    ComponentType type() const override { return ComponentType::TEXTURE_COMPONENT; }
};

} // namespace sle
