#pragma once

#include "IComponent.hpp"

namespace sle {

struct TextureComponent : IComponent {
    size_t textureIndex;

    TextureComponent(const size_t textureIndex) : IComponent(ComponentIDProvider::id()), textureIndex(textureIndex) {}
    ComponentType type() const override { return ComponentType::TEXTURE_COMPONENT; }
};

} // namespace sle
