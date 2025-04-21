#pragma once

#include "Renderer.hpp"
#include "secs/secs.hpp"
#include "TransformComponent.hpp"
#include "TextureComponent.hpp"
#include "Window.hpp"
#include "assert.hpp"

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
        // need to somehow get the camera component here also, so that we can offset everything for rendering.
        const glm::ivec2 cameraPos;
        for (const auto e : scene.getComponentEntities<TextureComponent, TransformComponent>()) {
            const auto transform = scene.getComponent<TransformComponent>(e);
            auto texture         = scene.getComponent<TextureComponent>(e);
            Renderer::get().stage(texture.textureIndex, transform.position, cameraPos);
        }
    }
};

} // namespace sle