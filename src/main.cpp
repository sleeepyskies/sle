#define SDL_MAIN_HANDLED
#include "Engine.hpp"
#include "Scene.hpp"
#include "TextureComponent.hpp"

int main() {
    // slog::logLevel = slog::Level::TRACE;

    /*
    sle::Engine engine{};
    engine.init();
    engine.run();
    engine.shutdown();
    */

    sle::Scene scene{};
    auto e = scene.createEntity();
    auto textureComponent = sle::TextureComponent(0);
    scene.registerComponent<sle::TextureComponent>(e, textureComponent);
    scene.unregisterComponent<sle::TextureComponent>(e, textureComponent.type());



    return 0;
}
