#pragma once

#include "../../../external/secs/secs/include/secs/Component.hpp"
#include <SDL.h>

namespace sle {
struct TransformComponent final : secs::Component {
    SDL_Rect position;

    explicit TransformComponent(const SDL_Rect rect)
        : position(rect) {}
};
} // namespace sle
