#pragma once

#include "secs/Component.hpp"

namespace sle {

struct TextureComponent final : secs::Component {
    size_t textureIndex;

    TextureComponent(const size_t textureIndex)
        : textureIndex(textureIndex) {
    }

    secs::ComponentType type() const override { return secs::ComponentType::TEXTURE_COMPONENT; }
};

} // namespace sle
