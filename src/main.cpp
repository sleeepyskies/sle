#define SDL_MAIN_HANDLED
#include "assert.hpp"
#include "Engine.hpp"
#include "secs/Scene.hpp"
#include "secs/components/TextureComponent.hpp"
#include "secs/systems/RenderSystem.hpp"

int main() {
    // slog::logLevel = slog::Level::TRACE;

    /*
    sle::Engine engine{};
    engine.init();
    engine.run();
    engine.shutdown();
    */

    secs::Scene scene{};
    auto e = scene.createEntity();
    auto textureComponent = secs::TextureComponent(0);
    scene.registerComponent<secs::TextureComponent>(e, textureComponent);

    // testing getComponent
    auto &comp = scene.getComponent<secs::TextureComponent>(e);
    SLE_ASSERT(comp.id == textureComponent.id, "IDs do not match.");
    scene.registerSystem<secs::RenderSystem>();

    scene.unregisterComponent<secs::TextureComponent>(e, textureComponent.type());
    scene.destroyEntity(e);

    return 0;
}
