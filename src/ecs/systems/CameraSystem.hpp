#pragma once

#include "KeyboardKey.hpp"
#include <glm/vec2.hpp>
#include "CameraComponent.hpp"
#include "TransformComponent.hpp"
#include "secs/secs.hpp"
#include "Input.hpp"

namespace sle {

/**
 * @brief System responsible for handling camera movement based on user input.
 *
 * Process all entities with @ref CameraComponent and @ref TransformComponent.
 * Handles user input of the WASD keys to the camera, scaled by a speed factor.
 *
 * @implements secs::System
 */
class CameraSystem final : public secs::System {

    void update(const double deltaTime, secs::Scene &scene) override {

        for (const auto &e : scene.getComponentEntities<CameraComponent, TransformComponent>()) {
            const auto camera = scene.getComponent<CameraComponent>(e);
            auto transform    = scene.getComponent<TransformComponent>(e);
            glm::vec2 direction{};

            if (Input::get().keyboardKey(SDLK_w)) {
                direction.y += 1;
            }
            if (Input::get().keyboardKey(SDLK_a)) {
                direction.x += 1;
            }
            if (Input::get().keyboardKey(SDLK_s)) {
                direction.y -= 1;
            }
            if (Input::get().keyboardKey(SDLK_s)) {
                direction.x -= 1;
            }
            if (direction.x == 0 && direction.y == 0) {
                return;
            }
            const glm::ivec2 normalized = static_cast<float>(deltaTime * camera.speed) * normalize(
                                              glm::vec2{ direction });
            transform.position.x += normalized.x;
            transform.position.y += normalized.y;
        }
    }
};

} // namespace sle