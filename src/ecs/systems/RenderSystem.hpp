#pragma once

#include "secs/secs.hpp"
#include "TransformComponent.hpp"
#include "TextureComponent.hpp"

namespace sle {
/**
 * @brief This system handles Rendering all Entities that have the following:
 * - TextureComponent
 * - TransformComponent
 */
class RenderSystem final : public secs::System {
    void update(const double deltaTime, secs::Scene &scene) override {
        for (const auto e : scene.getComponentEntities<TextureComponent, TransformComponent>()) {
            // TODO: Perform Rendering Logic here i guess? Do i even want a renderer like this?
        }
    }
};

} // namespace sle
