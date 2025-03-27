#pragma once

#include "IComponent.hpp"
#include <SDL.h>

namespace sle {

struct PositionComponent : IComponent {
    SDL_Rect position;

    explicit PositionComponent(const ComponentID id, const SDL_Rect rect)
    : IComponent(id), position(rect) {}
    ComponentType type() const override { return ComponentType::POSITION_COMPONENT; }
};

} // namespace sle
