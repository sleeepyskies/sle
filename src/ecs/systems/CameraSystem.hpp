#pragma once

#include "System.hpp"
#include <SDL_keycode.h>
#include <glm/vec2.hpp>
#include "CameraComponent.hpp"
#include "TransformComponent.hpp"
#include "Scene.hpp"


namespace sle {

/**
 * @brief System responsible for handling camera movement based on user input.
 *
 * Process all entities with @ref CameraComponent and @ref TransformComponent,
 * and handles user input of the WASD keys to the camera, scaled by a speed factor.
 *
 * @implements secs::System
 */
class CameraSystem final : public secs::System {

    void update(const double deltaTime, secs::Scene &scene, const secs::InputData &inputData) override {

        for (const auto &e : scene.getComponentEntities<CameraComponent, TransformComponent>()) {
            const auto camera    = scene.getComponent<CameraComponent>(e);
            auto transform = scene.getComponent<TransformComponent>(e);
            glm::vec2 direction{};

            if (inputData.keys.contains(SDLK_w)) {
                direction.y += 1;
            }
            if (inputData.keys.contains(SDLK_a)) {
                direction.x += 1;
            }
            if (inputData.keys.contains(SDLK_s)) {
                direction.y -= 1;
            }
            if (inputData.keys.contains(SDLK_d)) {
                direction.x -= 1;
            }
            if (direction.x == 0 && direction.y == 0) {
                return;
            }
            const glm::ivec2 normalized = camera.speed * normalize(glm::vec2{ direction });
            transform.position.x += normalized.x;
            transform.position.y += normalized.y;
        }
    }
};

} // namespace sle