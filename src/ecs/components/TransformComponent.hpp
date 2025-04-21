#pragma once

#include "secs/secs.hpp"
#include <glm/vec2.hpp>

namespace sle {
struct TransformComponent final : secs::Component {
    glm::ivec2 position;

    explicit TransformComponent(const glm::ivec2 pos)
        : position(pos) {
    }
};
} // namespace sle