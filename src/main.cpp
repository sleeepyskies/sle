#define SDL_MAIN_HANDLED
#include "assert.hpp"
#include "Engine.hpp"
#include "secs/Scene.hpp"
#include "secs/components/TextureComponent.hpp"

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
    secs::TextureComponent &comp = scene.getComponent<secs::TextureComponent>(e);
    SLE_ASSERT(comp.id == textureComponent.id, "IDs do not match.");
    comp.textureIndex = 10;
    SLE_ASSERT(comp.textureIndex == textureComponent.textureIndex, "Texture indices do not match.");

    scene.unregisterComponent<secs::TextureComponent>(e, textureComponent.type());
    scene.destroyEntity(e);

    return 0;
}
