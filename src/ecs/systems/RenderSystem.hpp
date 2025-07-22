#pragma once

#include "CameraComponent.hpp"
#include "Renderer.hpp"
#include "TextureComponent.hpp"
#include "TransformComponent.hpp"
#include "secs/secs.hpp"

namespace sle {

/**
 * @brief This system handles Rendering all Entities that have the following:
 *
 * Process all entities with @ref TransformComponent and @ref TextureComponent.
 * This system essentially stages all of these entities for rendering by the
 * @ref Renderer.
 *
 * @implements secs::System
 */
class RenderSystem final : public secs::System {
    void update(const double deltaTime, secs::Scene &scene) override {
        // TODO: only render textures that are within the screen.
        const glm::ivec2 cameraPos =
            scene.getComponent<TransformComponent>(scene.entityWithUniqueComponent<CameraComponent>()).position;

        for (const auto e : scene.getComponentEntities<TextureComponent, TransformComponent>()) {
            const auto transform = scene.getComponent<TransformComponent>(e);
            const auto texture   = scene.getComponent<TextureComponent>(e);
            Renderer::get().stage(texture.textureIndex, transform.position, cameraPos);
        }
    }
};

} // namespace sle

