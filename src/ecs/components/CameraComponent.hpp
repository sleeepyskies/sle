#pragma once

#include "secs/secs.hpp"

namespace sle {
struct CameraComponent final : secs::Component {
    float speed = 0.5f;

    explicit CameraComponent(const float speed) : speed(speed) {}
};
} //  namespace sle

