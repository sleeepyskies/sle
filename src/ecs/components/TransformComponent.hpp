#pragma once

#include "secs/Component.hpp"
#include <SDL.h>

namespace sle {

struct TransformComponent final : secs::Component {
    SDL_Rect position;

    explicit TransformComponent(const SDL_Rect rect)
        : position(rect) {}

    secs::ComponentType type() const override { return secs::ComponentType::POSITION_COMPONENT; }
};

} // namespace sle
