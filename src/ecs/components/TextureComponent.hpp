#pragma once

#include "../../../external/secs/secs/include/secs/Component.hpp"

namespace sle {
struct TextureComponent final : secs::Component {
    size_t textureIndex;

    explicit TextureComponent(const size_t textureIndex)
        : textureIndex(textureIndex) {
    }
};
} // namespace sle
