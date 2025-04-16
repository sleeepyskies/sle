#pragma once

#include "../../../external/secs/secs/include/secs/Component.hpp"

namespace sle {
    struct CameraComponent final : secs::Component {
        float speed = 0.5f;

        explicit CameraComponent(const float speed)
            : speed(speed) {}
    };
} //  namespace sle
