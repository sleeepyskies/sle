#define SDL_MAIN_HANDLED
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
    if (scene.getComponent<secs::TextureComponent>(e).id != textureComponent.id) return -1;
    scene.unregisterComponent<secs::TextureComponent>(e, textureComponent.type());
    scene.destroyEntity(e);

    return 0;
}
