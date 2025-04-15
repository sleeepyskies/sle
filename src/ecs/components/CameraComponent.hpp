#pragma once

#include "secs/Component.hpp"

namespace sle {

    struct CameraComponent final : public secs::Component {
        float speed = 0.5f;

        CameraComponent(const float speed)
            : speed(speed) {}

        secs::ComponentType type() const override { return secs::ComponentType::CAMERA_COMPONENT; }

    };

} //  namespace sle
